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

#define delta 0.001f

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

chain hess(bool init, int gn, int DIM,
                      int nPairs, _global(nPairs) float * XP, _global(nPairs) float * YP,
                      _global(DIM) char * DimFlags, int base_offs, int base_size0, int base_size,
                      _local(__planned__.base_size) float * HESS,
                      _global(DIM) float * XS) {
  if (init) {
    int max_work_size, _gn, nn, nbase_size0, nbase_rest, offs;
    int stages = throw_num_stages();
    int stage = throw_stage();
    const char * device_id = get_device_id(stage);
    int sum_units = 0;
    int i;
    
    max_work_size = vector_max_size(device_id);
    for (i = 0; i < stages; i++)
        sum_units += vector_max_units(get_device_id(i));
    for (i = 0, offs = 0; i < stage; i++)
        offs += gn*vector_max_units(get_device_id(i))/sum_units;
    if (stage == stages-1)
       _gn = gn - offs;
    else
       _gn = gn*vector_max_units(device_id)/sum_units;
    nn = __min(_gn, max_work_size);
    nbase_size0 = _gn/nn;
    nbase_rest = _gn%nn;

    for (i = 0; i < nn; i++) {
        int nbase_size = (i < nbase_rest ? nbase_size0+1 : nbase_size0);
        plan_last(false, gn, DIM, nPairs, XP, YP, DimFlags, offs, nbase_size0, nbase_size, HESS+offs, XS);
        offs += nbase_size;
    }
    plan_group_vectorize(device_id);
  } else {
    int id = plan_vector_id();

    int i, j;

    barrier(0);
    for (j = 0; j < base_size; j++) {
        int _j = base_offs + j;
    	int p1 = _j/DIM;
    	int p2 = _j%DIM;

    	float xp[MAX_DIM], xm[MAX_DIM];
    	float fp, fm, fp1, fm1;
        float gp, gm;

        for (i = 0; i < DIM; i++) {
            xp[i] = XS[i];
            xm[i] = XS[i];
        }

    	xp[p1] += delta;
    	if (p1 != p2) xp[p2] += delta;
    	if (j < base_size0) barrier(0);
    	fp = F(j < base_size0, 0, nPairs, XP, YP, xp);
    	xm[p1] -= delta;
    	if (p1 != p2) xm[p2] += delta;
    	if (j < base_size0) barrier(0);
    	fm = F(j < base_size0, 0, nPairs, XP, YP, xm);
    	gp = (fp - fm)/(2.0f*delta);

    	if (p1 == p2)
    	   xp[p1] -= delta;
        else
           xp[p2] -= 2.0f*delta;
    	if (j < base_size0) barrier(0);
    	fp1 = F(j < base_size0, 0, nPairs, XP, YP, xp);
    	xm[p2] -= 2.0f*delta;
    	fm1 = F(j < base_size0, 0, nPairs, XP, YP, xm);
    	gm = (fp1 - fm1)/(2.0f*delta);

    	if (p1 == p2)
   	   HESS[j] = (fp - 2.0f*fp1 + fm)/(delta*delta);
    	else
    	   HESS[j] = (gp - gm)/(2.0f*delta);

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

bool _GetLU(int NN, int * iRow, float * A, float * LU)
{
 int i,j,k;
 try {
   memmove(LU,A,NN*NN*sizeof(float));
   for (i=0;i<NN;i++)
       iRow[i]=i;
   for (i=0;i<NN-1;i++)
     {
      float Big  = fabs(LU[iRow[i]*NN+i]);
      int iBig = i;

      float Kf;

      for (j=i+1;j<NN;j++)
          {
           float size = fabs(LU[iRow[j]*NN+i]);

           if (size>Big)
              {
               Big  = size;
               iBig = j;
              }
          }
      if (iBig!=i)
         {
          int V = iRow[i];
          iRow[i] = iRow[iBig];
          iRow[iBig] = V;
         }
      Kf = 1.0/LU[iRow[i]*NN+i];

      LU[iRow[i]*NN+i] = Kf;
      for (j=i+1;j<NN;j++)
          {
           float Fact = Kf*LU[iRow[j]*NN+i];

           LU[iRow[j]*NN+i] = Fact;
           for (k=i+1;k<NN;k++)
               LU[iRow[j]*NN+k] -= Fact*LU[iRow[i]*NN+k];
          }
     }
   LU[(iRow[NN-1]+1)*NN-1] = 1.0/LU[(iRow[NN-1]+1)*NN-1];
 }
 catch (...) {
   return false;
 }
 return true;
}

bool _SolveLU(int NN, int * iRow, float * LU, float * Y, float * X)
{
 int i,j,k;
 try {
   X[0] = Y[iRow[0]];
   for (i=1;i<NN;i++)
       {
        float V  = Y[iRow[i]];

        for (j=0;j<i;j++)
            V -= LU[iRow[i]*NN+j]*X[j];
        X[i] = V;
       }

   X[NN-1]*=LU[(iRow[NN-1]+1)*NN-1];

   for (i=1,j=NN-2;i<NN;i++,j--)
       {
        float V = X[j];

        for (k=j+1;k<NN;k++)
            V -= LU[iRow[j]*NN+k]*X[k];
        X[j] = V*LU[iRow[j]*NN+j];
       }
 }
 catch (...) {
   return false;
 }
 return true;
}

const double MU = 30.0;

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

  int iRow[MAX_DIM];

  double total_time = 0.0;
  int total_iters = 0;

  int prev_success = 0;

  for (int MASK = 1; MASK < NN; MASK++) {
  	float FF = F(false, 0, nPairs, reinterpret_cast<float *>(XP), YP, X);
  	float eps = 1.0;
  	int iters = 0;

  	float R = R0;

  	while (eps > EPS) {
  		iters++;

  		double _time = omp_get_wtime();

  		float BestX[MAX_DIM];
  		float BestF, PrevBestF;
		float D[MAX_DIM];

  		for (int i = 0; i < DIM; i++)
  			BestX[i] = X[i];
		PrevBestF = FF;
  		BestF = FF;

  		float MIN = 1E30f;
  		float MAX = -1E30f;

  		float * XS;
  		float * FS;
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

		if (success < prev_success) {
			if (R < 0.7)
				R *= 1.1;
		} else
			if (R > 0.1)
				R *= 0.9;

		prev_success = success;

		double _mu = __max(0.0001, MU*success*success/nProbes/nProbes);

       		float * HESS = new float[DIM*DIM];
       		float * LU = new float[DIM*DIM];
		float * GRAD = new float[DIM];

		double ttune;

		int k = 0;
		do {
	       		plan_parallel_chain(1, exN, hess(true, DIM*DIM, DIM, nPairs,
        	                                         reinterpret_cast<float *>(XP), YP,
                	                                 DimFlags, 0, 0, 0,
                        	                         HESS, BestX)
	                );
        	        ttune = 0;
                	for (int i = 0; i < exN; i++) {
	                    double ttunen = last_compile_time(exIDs[i]);
        	            if (ttunen > ttune)
                	       ttune = ttunen;
	                }

			for (int i = 0; i < DIM; i++) {
				HESS[i*DIM+i] += _mu;
				if (DimFlags[i]) {
					float save = BestX[i];
					BestX[i] += delta;
	  				float FP = F(false, 0, nPairs, reinterpret_cast<float *>(XP), YP, BestX);
					BestX[i] -= 2.0*delta;
	  				float FM = F(false, 0, nPairs, reinterpret_cast<float *>(XP), YP, BestX);
					BestX[i] = save;
					GRAD[i] = (FP - FM)/(2.0*delta);
				} else
					GRAD[i] = 0.0f;
			}
			_GetLU(DIM, iRow, HESS, LU);
			_SolveLU(DIM, iRow, LU, GRAD, D);
			// Вычисляем новую точку
			double w = 1.0;
			do {
				for (int i = 0; i < DIM; i++)
					if (DimFlags[i])
						X[i] = BestX[i] - w*D[i];
					else
						X[i] = BestX[i];
				FF = F(false, 0, nPairs, reinterpret_cast<float *>(XP), YP, X);;
				if (FF > BestF) w /= 2.0;
			} while (FF > BestF && w > 1E-6);

	  		eps = fabs(FF - BestF);

			BestF = FF;
			for (int i = 0; i < DIM; i++)
				BestX[i] = X[i];
			k++;
		} while (eps > EPS && k < 35);
 
  		eps = fabs(PrevBestF - BestF);

       		delete[] HESS;
		delete[] LU;
		delete[] GRAD;

  		delete[] XS;
  		delete[] FS;

  		cout<<"Compile kernel times = "<<tprobe<<" and "<<ttune<<endl;
  		total_time += omp_get_wtime() - _time - tprobe - ttune;
  		total_iters++;

  		cout<<"R = "<<R<<endl;
  		cout<<"F = "<<FF<<" at [";
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