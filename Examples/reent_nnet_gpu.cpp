#pragma plan vectorized

#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <iostream>

#include <omp.h>

using namespace std;

const int SMPprocs = 16;

#pragma plan common begin

#define N 8
// 1500
#define nProbes 6000

#define alpha 0.001f
#define delta 1E-4f

#define N0 1

#define N1 6
#define N2 5
#define N3 1

// 0 = recurrent polynomial
// 1 = exponential sygmoid
// 2 = linear
__constant char MAP1[N1] = {0, 1, 1, 1, 1, 1};
__constant char MAP2[N2] = {0, 1, 1, 1, 1};
__constant char MAP3[N1] = {2};

#define MAX_DIM 96

#ifndef __min
#define __min(a,b) ((a)<(b) ? (a) : (b))
#endif
#ifndef __max
#define __max(a,b) ((a)>(b) ? (a) : (b))
#endif

float NET(float * W, float x) {
	int p = 0;
	int k, r, i;

	float s1[N], y1[N], s2[N], y2[N], s3[N], y3[N];

	for (k = 0; k < N1; k++) {
		s1[k] = W[p++]*x;
	}

	for (k = 0; k < N1; k++)
		switch (MAP1[k]) {
			case 0: {
				float ai = W[p++];
				for (i = N - 1; i >= 0; i--) {
					float bi = W[p++];
					float ki = s1[k]/(i + 1);
					ai = bi + ki*ai;
				}
				y1[k] = ai;
				break;
			}
			case 1: {
				y1[k] = 1.0/(1.0+exp(-(s1[k]+W[p++])));
				break;
			}
			case 2: {
				y1[k] = s1[k] + W[p++];
				break;
			}
		}

	for (k = 0; k < N2; k++) {
		s2[k] = 0.0;
		for (r = 0; r < N1; r++)
			s2[k] += W[p++]*y1[r];
	}

	for (k = 0; k < N2; k++)
		switch (MAP2[k]) {
			case 0: {
				float ai = W[p++];
				for (i = N - 1; i >= 0; i--) {
					float bi = W[p++];
					float ki = s2[k]/(i + 1);
					ai = bi + ki*ai;
				}
				y2[k] = ai;
				break;
			}
			case 1: {
				y2[k] = 1.0/(1.0+exp(-(s2[k]+W[p++])));
				break;
			}
			case 2: {
				y2[k] = s2[k] + W[p++];
				break;
			}
		}

	s3[0] = 0.0;
	for (k = 0; k < N2; k++) {
		s3[0] += W[p++]*y2[k];
	}

	for (k = 0; k < N3; k++)
		switch (MAP3[k]) {
			case 0: {
				float ai = W[p++];
				for (i = N - 1; i >= 0; i--) {
					float bi = W[p++];
					float ki = s3[k]/(i + 1);
					ai = bi + ki*ai;
				}
				y3[k] = ai;
				break;
			}
			case 1: {
				y3[k] = 1.0/(1.0+exp(-(s3[k]+W[p++])));
				break;
			}
			case 2: {
				y3[k] = s3[k] + W[p++];
				break;
			}
		}

	return y3[0];
}

float F(int barriered, float * val, int nPairs, __global float * XP, __global float * YP, float * W) {
	int id = plan_vector_id();

	float result = 0.0;
	int j;

	for (j = 0; j < nPairs; j++) {
		int ptr = (j + id)%nPairs;
		float x = XP[ptr];

		float y  = YP[ptr];

		float _net;

		if (barriered) barrier(0);
		_net = val ? 0.0f : NET(W, x);
		if (barriered) barrier(0);

		result += (y-_net)*(y-_net);
	}

	return val ? *val : result;
}

#pragma plan common end

const int MAX_IN_CONTOUR = 64; // 20

const int NDIV = __max(20, nProbes/(2*MAX_IN_CONTOUR));

const float EPS = 1E-4f;

const float R0 = 0.2f;

const int max_nPairs = 1000;

int nPairs = 0;

float XP[max_nPairs][1];
float YP[max_nPairs];

int DIM = 0;

// Bit masks. Values = 1, 2, 4, 8 ...
int nSegms = 3;
int SEGM1[N1] = {1, 2, 2, 4, 4, 4};
int SEGM2[N2] = {1, 2, 2, 4, 4};
int SEGM3[N3] = {1+2+4};

chain probe(bool init, int DIM, int nPairs,
                       _global(nPairs) float * XP, _global(nPairs) float * YP,
                       _global(DIM) char * DimFlags,
                       _global(DIM) float * X, float R,
                       _local(DIM*__planned__.base_size) int * rands,
                       int _RAND_MAX, int base_size0, int base_size,
                       _local(DIM*__planned__.base_size) float * XS, _local(__planned__.base_size) float * FS) {
  if (init) {
    int max_work_size, _nProbes, nn, nbase_size0, nbase_rest, offs;
    int stages = throw_num_stages();
    int stage = throw_stage();
    const char * device_id = get_device_id(stage);
    int sum_units = 0;
    int i;
    
    max_work_size = vector_max_size(device_id);
    for (i = 0; i < stages; i++)
        sum_units += vector_max_units(get_device_id(i));
    for (i = 0, offs = 0; i < stage; i++)
        offs += (long)nProbes*vector_max_units(get_device_id(i))/sum_units;
    if (stage == stages-1)
       _nProbes = nProbes - offs;
    else
       _nProbes = (long)nProbes*vector_max_units(device_id)/sum_units;
    nn = __min(_nProbes, max_work_size);
    nbase_size0 = _nProbes/nn;
    nbase_rest = _nProbes%nn;

    for (i = 0; i < nn; i++) {
        int nbase_size = (i < nbase_rest ? nbase_size0+1 : nbase_size0);
        plan_last(false, DIM, nPairs, XP, YP, DimFlags, X, R, rands+offs*DIM, _RAND_MAX, nbase_size0, nbase_size, XS+offs*DIM, FS+offs);
        offs += nbase_size;
    }
    plan_group_vectorize(device_id);
  } else {
    int id = plan_vector_id();

    float BaseX[MAX_DIM];
    float CurX[MAX_DIM];
    int i, j;

    barrier(0);
    for (i = 0; i < DIM; i++) {
    	j = (i+id)%DIM;
    	BaseX[j] = X[j];
    }
    barrier(0);
    for (j = 0; j < base_size; j++) {
    	for (i = 0; i < DIM; i++) {
    		CurX[i] = BaseX[i];
    		if (DimFlags[i])
    		   CurX[i] += R - 2.0*R*rands[j*DIM + (i + id)%DIM]/_RAND_MAX;
    		if (j < base_size0) barrier(0);
    		XS[i + j*DIM] = CurX[i];
    		if (j < base_size0) barrier(0);
    	}
    	FS[j] = F(j < base_size0, 0, nPairs, XP, YP, CurX);
    	if (j < base_size0) barrier(0);
    }
    barrier(0);
  }
}

chain tune(bool init, int gn, int DIM, int _nmax,
                      int nPairs, _global(nPairs) float * XP, _global(nPairs) float * YP,
                      _global(DIM) char * DimFlags, int base_offs, int base_size0, int base_size,
                      _local(DIM*__planned__.base_size) float * OutX, _local(__planned__.base_size) float * OutF,
                      _global(DIM*gn) float * XS) {
  long gn2 = gn*gn;

  if (init) {
    int max_work_size, _gn2, nn, nbase_size0, nbase_rest, offs;
    int stages = throw_num_stages();
    int stage = throw_stage();
    const char * device_id = get_device_id(stage);
    int sum_units = 0;
    int i;
    
    max_work_size = vector_max_size(device_id);
    for (i = 0; i < stages; i++)
        sum_units += vector_max_units(get_device_id(i));
    for (i = 0, offs = 0; i < stage; i++)
        offs += gn2*vector_max_units(get_device_id(i))/sum_units;
    if (stage == stages-1)
       _gn2 = gn2 - offs;
    else
       _gn2 = gn2*vector_max_units(device_id)/sum_units;
    nn = __min(_gn2, max_work_size);
    nbase_size0 = _gn2/nn;
    nbase_rest = _gn2%nn;

    for (i = 0; i < nn; i++) {
        int nbase_size = (i < nbase_rest ? nbase_size0+1 : nbase_size0);
        plan_last(false, gn, DIM, _nmax, nPairs, XP, YP, DimFlags, offs, nbase_size0, nbase_size, OutX+offs*DIM, OutF+offs, XS);
        offs += nbase_size;
    }
    plan_group_vectorize(device_id);
  } else {
    int id = plan_vector_id();

    int i, j, k;

    barrier(0);
    for (j = 0; j < base_size; j++) {
        int _j = base_offs + j;
    	int p1 = _j/gn;
    	int p2 = _j%gn;

    	int nmax = _nmax;

    	float x[MAX_DIM], x1[MAX_DIM];
    	float grad[MAX_DIM];
    	float f, f1, fx;

    	for (i = 0; i < DIM; i++) {
    		x1[i] = 0.5f*(XS[i + p1*DIM]+XS[i + p2*DIM]);
    		if (j < base_size0) barrier(0);
    	}
    	f1 = F(j < base_size0, 0, nPairs, XP, YP, x1);
    	
        bool stopped = false;
    	do {
    		if (!stopped) {
                   for (i = 0; i < DIM; i++)
    		       x[i] = x1[i];
    		   f = f1;
    		}

                fx = F(j < base_size0, stopped ? &fx : 0, nPairs, XP, YP, x);
    		
    		for (i = 0; i < DIM; i++) {
    			float X1[MAX_DIM];
    			if (!stopped) {
                           for (k = 0; k < DIM; k++)
    				X1[k] = x[k];
    			   X1[i] += delta;
    			}
    		
    			if (DimFlags[i])
                           grad[i] = (F(j < base_size0, stopped ? &grad[i] : 0, nPairs, XP, YP, X1) - fx)/delta;
    			else
    			   grad[i] = 0.0f;
    			if (j < base_size0)
                           barrier(0);
    		}
    		
    		if (!stopped)
                   for (i = 0; i < DIM; i++)
    		       x1[i] = x[i] - alpha*grad[i];
                f1 = F(j < base_size0, stopped ? &f1 : 0, nPairs, XP, YP, x1);
                stopped = f1 >= f;
    	} while (--nmax);
    	for (i = 0; i < DIM; i++) {
    	    OutX[i+j*DIM] = x[i];
    	    if (j < base_size0) barrier(0);
    	}
    	OutF[j] = f;
    	if (j < base_size0) barrier(0);
    }
    barrier(0);
  }
}

float MINS[256];
int   iMINS[256];
float MAXS[256];
int   iMAXS[256];
float FF;
reenterable min_max(bool init, int idx, float * FS, reduction(+) int &success) {
  if (init) {
     for (int i = 0; i < SMPprocs; i++) {
         MINS[i]    = 1E30f;
         iMINS[i]   = 0;
         MAXS[i]    = -1E30f;
         iMAXS[i]   = 0;
     }
     for (int j = 0; j < nProbes; j++)
         plan_last(false, j, FS+j, 0);
     plan_group_parallelize;
  } else {
     int id = plan_processor_id();
     if (*FS < MINS[id]) {
        MINS[id]  = *FS;
        iMINS[id] = idx;
     }
     if (*FS > MAXS[id]) {
        MAXS[id]  = *FS;
        iMAXS[id] = idx;
     }
     success = *FS < FF ? 1 : 0;
  }
}

reenterable void histo(bool init, float gap, float MIN, int i, float * FS, int ** idx, int * nn) {
  if (init) {
     for (int j = 0; j < nProbes; j++)
         plan_last(false, gap, MIN, j, FS+j, idx, nn);
     plan_group_atomize;
  } else {
     int k = (int)((*FS-MIN)/gap);
     if (k < 0) k = 0;
     if (k >= NDIV) k = NDIV-1;
     idx[k][nn[k]++] = i;
  }
}

int main() {
  srand((unsigned int) time(NULL));

  int SEGM_A[MAX_DIM];
  int SEGM_B[MAX_DIM];

  DIM = N0*N1;
  for (int i = 0; i < N1; i++)
  	switch (MAP1[i]) {
  		case 0: DIM += N+1; break;
  		case 1: DIM++; break;
  		case 2: DIM++; break;
  	}
  DIM += N1*N2;
  for (int i = 0; i < N2; i++)
  	switch (MAP2[i]) {
  		case 0: DIM += N+1; break;
  		case 1: DIM++; break;
  		case 2: DIM++; break;
  	}
  DIM += N2*N3;
  for (int i = 0; i < N3; i++)
  	switch (MAP3[i]) {
  		case 0: DIM += N+1; break;
  		case 1: DIM++; break;
  		case 2: DIM++; break;
  	}

  int p = 0;
  for (int k = 0; k < N1; k++) {
  	SEGM_A[p] = SEGM1[k];
  	SEGM_B[p++] = SEGM1[k];
  }

  for (int k = 0; k < N1; k++)
  	switch (MAP1[k]) {
  		case 0: {
  			SEGM_A[p] = SEGM1[k];
  			SEGM_B[p++] = SEGM1[k];
  			for (int i = N - 1; i >= 0; i--) {
  				SEGM_A[p] = SEGM1[k];
  				SEGM_B[p++] = SEGM1[k];
  			}
  			break;
  		}
  		case 1: {
  			SEGM_A[p] = SEGM1[k];
  			SEGM_B[p++] = SEGM1[k];
  			break;
  		}
  		case 2: {
  			SEGM_A[p] = SEGM1[k];
  			SEGM_B[p++] = SEGM1[k];
  			break;
  		}
  	}

  for (int k = 0; k < N2; k++) {
  	for (int r = 0; r < N1; r++) {
  		SEGM_A[p] = SEGM1[r];
  		SEGM_B[p++] = SEGM2[k];
  	}
  }

  for (int k = 0; k < N2; k++)
  	switch (MAP2[k]) {
  		case 0: {
  			SEGM_A[p] = SEGM2[k];
  			SEGM_B[p++] = SEGM2[k];
  			for (int i = N - 1; i >= 0; i--) {
  				SEGM_A[p] = SEGM2[k];
  				SEGM_B[p++] = SEGM2[k];
  			}
  			break;
  		}
  		case 1: {
  			SEGM_A[p] = SEGM2[k];
  			SEGM_B[p++] = SEGM2[k];
  			break;
  		}
  		case 2: {
  			SEGM_A[p] = SEGM2[k];
  			SEGM_B[p++] = SEGM2[k];
  			break;
  		}
  	}

  for (int k = 0; k < N2; k++) {
  	SEGM_A[p] = SEGM2[k];
  	SEGM_B[p++] = SEGM3[0];
  }

  for (int k = 0; k < N3; k++)
  	switch (MAP3[k]) {
  		case 0: {
  			SEGM_A[p] = SEGM3[0];
  			SEGM_B[p++] = SEGM3[0];
  			for (int i = N - 1; i >= 0; i--) {
  				SEGM_A[p] = SEGM3[0];
  				SEGM_B[p++] = SEGM3[0];
  			}
  			break;
  		}
  		case 1: {
  			SEGM_A[p] = SEGM3[0];
  			SEGM_B[p++] = SEGM3[0];
  			break;
  		}
  		case 2: {
  			SEGM_A[p] = SEGM3[0];
  			SEGM_B[p++] = SEGM3[0];
  			break;
  		}
  	}

  float X[MAX_DIM];

  for (int i = 0; i < DIM; i++)
  	X[i] = ((SEGM_A[i]^SEGM_B[i]) == 0) ? 1.0f-2.0f*rand()/RAND_MAX : 0.0f;

  FILE * DAT = fopen("water_ir_far.dat", "rt");
  float XPmin = 1E30f, XPmax = -1E30f;
  float YPmin = 1E30f, YPmax = -1E30f;
  while (!feof(DAT)) {
  	float micron, np, kp;
  	fscanf(DAT, "%f %f %f\n", &micron, &np, &kp);
  	XP[nPairs][0] = micron;
  	YP[nPairs] = np;
  	if (micron < XPmin) XPmin = micron;
  	if (micron > XPmax) XPmax = micron;
  	if (np < YPmin) YPmin = np;
  	if (np > YPmax) YPmax = np;
  	nPairs++;
  }
  fclose(DAT);

  int exN = 0;
  char * exIDs[256] = {NULL};
  while ((exIDs[exN] = (char *) get_device_id(exN)) != NULL)
    exN++;

  for (int i = 0; i < nPairs; i++) {
  	XP[i][0] = 2.0f*(XP[i][0] - XPmin)/(XPmax - XPmin) - 1.0f;
  	YP[i] = 2.0f*(YP[i] - YPmin)/(YPmax - YPmin) - 1.0f;
  }

  int NN = 1<<nSegms;

  double total_time = 0.0;
  int total_iters = 0;

  for (int MASK = 1; MASK < NN; MASK++) {
  	float FF = F(false, 0, nPairs, reinterpret_cast<float *>(XP), YP, X);
  	float eps = 1.0;
  	int iters = 0;

  	float R = R0;

  	while (eps > EPS) {
  		iters++;

  		double _time = omp_get_wtime();

  		float BestX[MAX_DIM];
  		float BestF;

  		for (int i = 0; i < DIM; i++)
  			BestX[i] = X[i];
  		BestF = FF;

  		float MIN = 1E30f;
  		float MAX = -1E30f;

  		float * XS;
  		float * FS;
  		int * nn = new int[NDIV];
  		int ** idx = new int * [NDIV];
  		for (int i = 0; i < NDIV; i++) {
  			idx[i] = new int[nProbes];
  			nn[i] = 0;
  		}
  		XS = new float[DIM*nProbes];
  		FS = new float[nProbes];

  		int success = 0;

  		int * rands = new int[DIM*nProbes];

  		for (int j = 0, ptr = 0; j < nProbes; j++)
  			for (int i = 0; i < DIM; i++, ptr++)
  				rands[ptr] = rand();

  		char DimFlags[MAX_DIM];
  		for (int i = 0; i < DIM; i++)
  			DimFlags[i] = (MASK & SEGM_A[i])>0 && (MASK & SEGM_B[i])>0;

                plan_parallel_chain(1, exN, probe(true, DIM, nPairs,
                                                  reinterpret_cast<float *>(XP), YP,
                                                  DimFlags, X, R, rands, RAND_MAX, 0, 0,
                                                  XS, FS)
                );
                double tprobe = 0;
                for (int i = 0; i < exN; i++) {
                    double tproben = last_compile_time(exIDs[i]);
                    if (tproben > tprobe)
                       tprobe = tproben;
                }

		min_max(true, 0, FS, success)/SMPprocs;

  		int imin = 0;
		int imax = 0;
		for (int j = 1; j < SMPprocs; j++) {
  			if (MINS[j] < MINS[imin]) imin = j;
  			if (MAXS[j] > MAXS[imax]) imax = j;
  		}
		MIN = MINS[imin];
		MAX = MAXS[imax];
  		if (MIN < BestF) {
  			BestF = MIN;
  			for (int i = 0; i < DIM; i++)
  				BestX[i] = XS[i+iMINS[imin]*DIM];
  		}

  		delete[] rands;

  		float gap = (MAX-MIN)/NDIV;

		histo(true, gap, MIN, 0, FS, idx, nn);

  		int gn = __min(MAX_IN_CONTOUR, nn[0] < 4*exN ? nn[0] : (nn[0] - nn[0]%(4*exN)));

  		int _nmax = 35 + 25*(nProbes-success)/nProbes;

       		float * XSS = new float[DIM*gn];

       		for (int j = 0; j < gn; j++) {
       			int ptr = idx[0][j];
       			for (int i = 0; i < DIM; i++)
       				XSS[i + j*DIM] = XS[i+ptr*DIM];
       		}

       		float * OutY = new float[gn*gn];
       		float * OutX = new float[DIM*gn*gn];

       		plan_parallel_chain(1, exN, tune(true, gn, DIM, _nmax, nPairs,
                                                 reinterpret_cast<float *>(XP), YP,
                                                 DimFlags, 0, 0, 0,
                                                 OutX, OutY, XSS)
                );
                double ttune = 0;
                for (int i = 0; i < exN; i++) {
                    double ttunen = last_compile_time(exIDs[i]);
                    if (ttunen > ttune)
                       ttune = ttunen;
                }
 
       		bool enhanced = false;
       		for (int j = 0; j < gn*gn; j++) {
       			if (BestF > OutY[j]) {
       				BestF = OutY[j];
       				for (int i = 0; i < DIM; i++)
       					BestX[i] = OutX[i + j*DIM];
       				enhanced = true;
       			}
       		}
       		if (enhanced) cout<<"Gradient-enhanced result"<<endl;

       		delete[] OutX;
       		delete[] OutY;
       		delete[] XSS;

  		if (1.0*success/nProbes > 0.5)
  			R *= 0.9f;
  		else if (1.0*success/nProbes < 0.01)
  			R *= 1.1f;

  		for (int i = 0; i < NDIV; i++)
  			delete[] idx[i];
  		delete[] idx;
  		delete[] nn;
  		delete[] XS;
  		delete[] FS;

  		eps = fabs(FF - BestF);
  		for (int i = 0; i < DIM; i++)
  			X[i] = BestX[i];
  		FF = BestF;

  		cout<<"Compile kernel times = "<<tprobe<<" and "<<ttune<<endl;
  		total_time += omp_get_wtime() - _time - tprobe - ttune;
  		total_iters++;

  		cout<<"R = "<<R<<endl;
  		cout<<"F = "<<BestF<<" at [";
  		for (int i = 0; i < DIM; i++) {
  			cout<<X[i];
  			cout<<(i < DIM-1 ? "," : "]");
  		}
  		cout<<endl;
  		cout<<"Avr (pure) time per iteration = "<<(total_time/total_iters)<<endl;
  	}

  	cout<<MASK<<". Min F = "<<FF<<" at [";
  	for (int i = 0; i < DIM; i++) {
  		cout<<X[i];
  		cout<<(i < DIM-1 ? "," : "]");
  	}
  	cout<<endl;
  	cout<<"Total time = "<<(total_time)<<endl;
  	cout<<"Avr time per iteration = "<<(total_time/total_iters)<<endl;
  }

  FILE * _OUT = fopen("water_ir_far.new", "w+t");
  for (int j = 0; j < nPairs; j++) {
  	float micron = XPmin + (XPmax - XPmin)*0.5f*(XP[j][0] + 1.0f);
  	float np = YPmin + (YPmax - YPmin)*0.5f*(NET(X, XP[j][0]) + 1.0f);
  	fprintf(_OUT, "%f %f\n", micron, np);
  }
  fclose(_OUT);

  return 0;
}