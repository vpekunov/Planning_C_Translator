#include <ostream>

using namespace std;

#include <omp.h>

 /* LU - разложение  с выбором максимального элемента по диагонали */
 bool GetLU(int NN, int * iRow, long double * A, long double * LU)
 {
  int i,j,k;
  try {
    memmove(LU,A,NN*NN*sizeof(long double));
    for (i=0;i<NN;i++)
        iRow[i]=i;
    for (i=0;i<NN-1;i++)
      {
       long double Big  = fabs(LU[iRow[i]*NN+i]);
       int iBig = i;
       long double Kf;
       for (j=i+1;j<NN;j++)
           {
            long double size = fabs(LU[iRow[j]*NN+i]);
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
            long double Fact = Kf*LU[iRow[j]*NN+i];
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
 /* Метод LU - разложения */
 bool SolveLU(int NN, int * iRow, long double * LU, long double * Y, long double * X)
 {
  int i,j,k;
  try {
    X[0] = Y[iRow[0]];
    for (i=1;i<NN;i++)
        {
         long double V  = Y[iRow[i]];
         for (j=0;j<i;j++)
             V -= LU[iRow[i]*NN+j]*X[j];
         X[i] = V;
        }
    X[NN-1]*=LU[(iRow[NN-1]+1)*NN-1];
    for (i=1,j=NN-2;i<NN;i++,j--)
        {
         long double V = X[j];
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
 /* Метод Гаусса-Зейделя  с выбором максимального элемента по диагонали */
 bool SolveGaussZeidel(int NN, int * iRow, long double * A, long double * LU, long double * Y, long double * X) {
  int i, j;
  double prev_eps, eps;
  int grow;
  int iters;
  try {
    for (i=0;i<NN;i++)
        iRow[i]=i;
    for (i=0;i<NN-1;i++)
      {
       long double Big  = fabs(A[iRow[i]*NN+i]);
       int iBig = i;
       for (j=i+1;j<NN;j++)
           {
            long double size = fabs(A[iRow[j]*NN+i]);
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
      }
    for (i=0;i<NN;i++)
        X[i]=0.5;
    eps = 1E300;
    grow = 0;
    for (iters = 0; eps > 1E-8 && iters < NN; iters++) {
        prev_eps = eps;
        eps = 0.0;
        for (i=0;i<NN;i++) {
            long double V = Y[iRow[i]];
            double d = X[i];
            for (j=0;j<NN;j++)
                if (j != i)
                   V -= A[iRow[i]*NN+j]*X[j];
            X[i] = V/A[iRow[i]*NN+i];
            d -= X[i];
            eps += d*d;
        }
        eps = sqrt(eps);
        if (eps > prev_eps)
           grow++;
        else
           grow = 0;
    }
    return eps <= 1E-8;
  }
  catch (...) {
    return false;
  }
 }

const bool EXPLICIT_PERCEPTRON = false;

const int N = 200;

int main() {
	double seq[N] = { 1.0, 0.0 };
	double seq1[N] = { 0 };

	seq[N-1] = 2.0;

       	vector<_funnel<double> *> r;

	funneled_perceptron_out<double> * outbb = new funneled_perceptron_out<double>(true, false, r, "bbPFUNNEL", N, 1E-5, 3);
	funneled_perceptron_out<double> * outpi = new funneled_perceptron_out<double>(EXPLICIT_PERCEPTRON, false, r, "iPFUNNEL", N, 1E-5, 3);

       	funneled_perceptron_in<double> * inbb = new funneled_perceptron_in<double>(true, false, r, "bbPFUNNEL", N, 1E-5, 3);
       	r.push_back(inbb->getRef());
       	funneled_perceptron_in<double> * inpi = new funneled_perceptron_in<double>(EXPLICIT_PERCEPTRON, false, r, "iPFUNNEL", N, 1E-5, 3);
       	inpi->getRef()->switchLU(false);

	while (!outpi->ready());
       	while (!inpi->ready());

       	if (EXPLICIT_PERCEPTRON)
       	   cout << "EXPLICIT";
       	else
       	   cout << "IMPLICIT";
       	cout<<" (FORECAST)"<<endl;

        int * iRow = new int[N];
        long double * A = new long double[N*N];
	long double * LU = new long double[N*N];
        long double * Y = new long double[N];
        long double * X = new long double[N];
	double * seqn = new double[N];
	double * b = new double[N];
       	double * seqp = new double[N];
       	double * bb = new double[N];
        double * seqpp = new double[N];

       	double tlearn = 0.0;
	for (int i = 0; i < N + 50; i++) {
	    for (int j = 0; j < N; j++)
	        b[j] = sin(0.25*(i+j)/(N-1));
	    outbb->put((void *) b, N*sizeof(double));
            seqn[0] = seq[0];
            seqn[N-1] = seq[N-1];
            for (int j = 1; j < N-1; j++)
                seqn[j] = seq[j] + 0.0025*(seq[j-1] - 2.0*seq[j] + seq[j+1] - b[j]);
            for (int j = 1; j < N-1; j++)
                seq[j] = seqn[j];
	    outpi->put((void *) seqn, N*sizeof(double));

       	    double t = omp_get_wtime();
       	    inbb->get((void *) bb, N*sizeof(double));
       	    if (inpi->get_timed((void *) seqp, -1.0)) {
       	       double buf[N];
       	       inpi->get_and_correct((void *) buf);
            }
            tlearn += omp_get_wtime() - t;
	}

	double tpredict = omp_get_wtime();
	for (int i = N + 50; i < N+300; i++) {
	    for (int j = 0; j < N; j++)
	        b[j] = sin(0.25*(i+j)/(N-1));
	    outbb->put((void *) b, N*sizeof(double));
	    outpi->put((void *) seqn, N*sizeof(double));

       	    inbb->get((void *) bb, N*sizeof(double));
       	    if (inpi->get_timed((void *) seqpp, -1.0)) {
       	       inpi->cancel_and_push((void *) seqpp);
            } else
               cout << "NO PREDICTION!" << endl;
	}
	tpredict = omp_get_wtime() - tpredict;

    	cout << "PREDICTED: ";
   	for (int j = 0; j < N; j++)
   	    cout << seqpp[j] << " ";
   	cout << endl;

        memset(A, 0, N*N*sizeof(long double));
        A[0*N+0] = 1.0;
        for (int j = 1; j < N-1; j++) {
            A[j*N+j] = 1.0 + 2.0*0.0025;
            A[j*N+j-1] = -0.0025;
            A[j*N+j+1] = -0.0025;  
        }
        A[(N-1)*N+N-1] = 1.0;

   	double tcalc = omp_get_wtime();
	for (int i = N + 50; i < N+300; i++) {
	    double seqn[N];
	    double b[N];
	    for (int j = 0; j < N; j++)
	        b[j] = sin(0.25*(i+j)/(N-1));
	    if (EXPLICIT_PERCEPTRON) {
               seqn[0] = seq[0];
               seqn[N-1] = seq[N-1];
               for (int j = 1; j < N-1; j++)
                   seqn[j] = seq[j] + 0.0025*(seq[j-1] - 2.0*seq[j] + seq[j+1] - b[j]);
               for (int j = 1; j < N-1; j++)
                   seq[j] = seqn[j];
            } else {
               Y[0] = seq[0];
               for (int j = 1; j < N-1; j++) {
                   Y[j] = seq[j] - 0.0025*b[j];
               }
               Y[N-1] = seq[N-1];
               SolveGaussZeidel(N, iRow, (long double *) A, (long double *) LU, Y, X) ||
                 GetLU(N, iRow, (long double *)A, (long double *)LU) &&
                 SolveLU(N, iRow, (long double *)LU, Y, X);
               for (int j = 0; j < N; j++)
                   seq[j] = X[j];
            }
	}
	tcalc = omp_get_wtime() - tcalc;

	cout << "CALCULATED: ";
	for (int j = 0; j < N; j++)
       	    cout << seq[j] << " ";
       	cout << endl;

       	cout << "Learning = " << tlearn << " sec." << endl;
       	cout << "Predicting = " << tpredict << " sec." << endl;
       	cout << "Equivalent calculating = " << tcalc << " sec." << endl;

	delete outpi;
	delete outbb;

       	delete inpi;
       	delete inbb;

        delete[] iRow;
        delete[] A;
        delete[] LU;
        delete[] Y;
        delete[] X;
        delete[] seqn;
        delete[] b;
        delete[] seqp;
        delete[] bb;
        delete[] seqpp;

	return 0;
}