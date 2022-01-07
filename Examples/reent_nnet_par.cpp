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

const int N = 8;

const int nProbes = 15000; // 1500;

const float alpha = 0.001f;
const float delta = 1E-4f;

const int N0 = 1;

const int N1 = 6;
const int N2 = 5;
const int N3 = 1;

// 0 = recurrent polynomial
// 1 = exponential sygmoid
// 2 = linear
const char MAP1[N1] = {0, 1, 1, 1, 1, 1};
const char MAP2[N2] = {0, 1, 1, 1, 1};
const char MAP3[N1] = {2};

const int MAX_DIM = 256;

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

float F(int nPairs, __global float * XP, __global float * YP, float * W) {
	float result = 0.0;
	int j;

	for (j = 0; j < nPairs; j++) {
		float x = XP[j];

		float y  = YP[j];

		float _net;

		_net = NET(W, x);

		result += (y-_net)*(y-_net);
	}

	return result;
}

const int MAX_IN_CONTOUR = 64; // 20;

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
            int idx,
            float * XP, float * YP,
            char * DimFlags, float * X, float R, int * rands, int _RAND_MAX,
            float * XS, float * FS) throw(bool init, int idx, float Val, int success) {
  if (init) {
    for (int i = 0; i < nProbes; i++)
        plan_last(false, DIM, nPairs, i, XP, YP, DimFlags, X, R, rands+i*DIM, _RAND_MAX, XS+i*DIM, FS+i);
    plan_group_parallelize;
  } else {
    float BaseX[MAX_DIM];
    float CurX[MAX_DIM];
    int i;

    for (i = 0; i < DIM; i++) {
    	BaseX[i] = X[i];
    }
    for (i = 0; i < DIM; i++) {
    	CurX[i] = BaseX[i];
    	if (DimFlags[i])
    	   CurX[i] += R - 2.0*R*rands[i]/_RAND_MAX;
    	XS[i] = CurX[i];
    }
    *FS = F(nPairs, XP, YP, CurX);
    throw_last(false, idx, *FS, 0);
  }
}

float MINS[256];
int   iMINS[256];
float MAXS[256];
int   iMAXS[256];
float FF;
chain min_max(bool init, int idx, float Val, reduction(+) int &success) {
  if (init) {
     for (int i = 0; i < SMPprocs; i++) {
         MINS[i]    = 1E30f;
         iMINS[i]   = 0;
         MAXS[i]    = -1E30f;
         iMAXS[i]   = 0;
     }
     plan_group_parallelize;
  } else {
     int id = plan_processor_id();
     if (Val < MINS[id]) {
        MINS[id]  = Val;
        iMINS[id] = idx;
     }
     if (Val > MAXS[id]) {
        MAXS[id]  = Val;
        iMAXS[id] = idx;
     }
     success = Val < FF ? 1 : 0;
  }
}

reenterable void tune(bool init, int gn, int _j, int DIM, int _nmax, int nPairs, float * XP, float * YP, char * DimFlags, float * OutX, float * OutF, float * XS) {
  int gn2 = gn*gn;

  if (init) {
    for (int i = 0; i < gn2; i++)
        plan_last(false, gn, i, DIM, _nmax, nPairs, XP, YP, DimFlags, OutX+i*DIM, OutF+i, XS);
    plan_group_parallelize;
  } else {
    int i, k;

    int p1 = _j/gn;
    int p2 = _j%gn;

    int nmax = _nmax;

    float x[MAX_DIM], x1[MAX_DIM];
    float grad[MAX_DIM];
    float f, f1, fx;

    for (i = 0; i < DIM; i++) {
    	x1[i] = 0.5f*(XS[i + p1*DIM]+XS[i + p2*DIM]);
    }
    f1 = F(nPairs, XP, YP, x1);
    
    do {
        for (i = 0; i < DIM; i++)
    	    x[i] = x1[i];
    	f = f1;

        fx = F(nPairs, XP, YP, x);
    	
    	for (i = 0; i < DIM; i++) {
    		float X1[MAX_DIM];
                for (k = 0; k < DIM; k++)
    			X1[k] = x[k];
    		X1[i] += delta;
    	
    		if (DimFlags[i])
                   grad[i] = (F(nPairs, XP, YP, X1) - fx)/delta;
    		else
    		   grad[i] = 0.0f;
    	}
    	
        for (i = 0; i < DIM; i++)
    	    x1[i] = x[i] - alpha*grad[i];
        f1 = F(nPairs, XP, YP, x1);
    } while (--nmax && f1 < f);
    for (i = 0; i < DIM; i++) {
        OutX[i] = x[i];
    }
    *OutF = f;
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

  for (int i = 0; i < nPairs; i++) {
  	XP[i][0] = 2.0f*(XP[i][0] - XPmin)/(XPmax - XPmin) - 1.0f;
  	YP[i] = 2.0f*(YP[i] - YPmin)/(YPmax - YPmin) - 1.0f;
  }

  int NN = 1<<nSegms;

  double total_time = 0.0;
  int total_iters = 0;

  for (int MASK = 1; MASK < NN; MASK++) {
  	float eps = 1.0;
  	int iters = 0;

  	float R = R0;

  	FF = F(nPairs, reinterpret_cast<float *>(XP), YP, X);

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

  		int * rands = new int[DIM*nProbes];

  		for (int j = 0, ptr = 0; j < nProbes; j++)
  			for (int i = 0; i < DIM; i++, ptr++)
  				rands[ptr] = rand();

  		char DimFlags[MAX_DIM];
  		for (int i = 0; i < DIM; i++)
  			DimFlags[i] = (MASK & SEGM_A[i])>0 && (MASK & SEGM_B[i])>0;

  		int success = 0;

		plan_parallel_chain(1,
                	probe(true, DIM, nPairs, 0,
				reinterpret_cast<float *>(XP), YP,
				DimFlags, X, R, rands, RAND_MAX,
				XS, FS),
			min_max(true, 0, 0.0, success)/SMPprocs
		);

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

  		int gn = __min(MAX_IN_CONTOUR, nn[0]);

  		int _nmax = 35 + 25*(nProbes-success)/nProbes;

       		float * XSS = new float[DIM*gn];

       		for (int j = 0; j < gn; j++) {
       			int ptr = idx[0][j];
       			for (int i = 0; i < DIM; i++)
       				XSS[i + j*DIM] = XS[i+ptr*DIM];
       		}

       		float * OutY = new float[gn*gn];
       		float * OutX = new float[DIM*gn*gn];

       		tune(true, gn, 0, DIM, _nmax, nPairs, reinterpret_cast<float *>(XP), YP, DimFlags, OutX, OutY, XSS);
 
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

  		total_time += omp_get_wtime() - _time;
  		total_iters++;

  		cout<<"R = "<<R<<endl;
  		cout<<"F = "<<BestF<<" at [";
  		for (int i = 0; i < DIM; i++) {
  			cout<<X[i];
  			cout<<(i < DIM-1 ? "," : "]");
  		}
  		cout<<endl;
  		cout<<"Avr time per iteration = "<<(total_time/total_iters)<<endl;
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