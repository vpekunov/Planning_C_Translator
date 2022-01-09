#include <ostream>

using namespace std;

#include <omp.h>

const bool EXPLICIT_PERCEPTRON = true;

const int N = 26;

int main() {
	double seq[N] = { 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, 2.0, 3.0, 4.0, 3.0, 1.0, 2.0, 3.0, 5.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0 };
	double seq1[N] = { 0 };

	funneled_predictor_out<double> * out = new funneled_predictor_out<double>("FUNNEL", 1, 4, 0.01);
       	funneled_predictor_in<double> * in = new funneled_predictor_in<double>("FUNNEL", 1, 4, 0.01);

       	while (!in->ready());
	while (!out->ready());

	for (int i = 0; i < N; i++) {
	    out->put((void *) &seq[i], sizeof(double));

       	    if (in->get_timed((void *) &seq1[i], -1.0)) {
       	       double buf = 0.0;
       	       in->get_and_correct((void *) &buf);
       	       cout << buf << "[predict=" << seq1[i] << "] ";
            } else
               cout << seq1[i] << " ";
	}

       	delete in;
	delete out;

       	vector<_funnel<double> *> r;

	funneled_perceptron_out<double> * outb = new funneled_perceptron_out<double>(true, true, r, "bPFUNNEL", N, 1E-5);
	funneled_perceptron_out<double> * outp = new funneled_perceptron_out<double>(true, false, r, "PFUNNEL", N, 1E-5);
       	funneled_perceptron_in<double> * inb = new funneled_perceptron_in<double>(true, true, r, "bPFUNNEL", N, 1E-5);
       	r.push_back(inb->getRef());
       	funneled_perceptron_in<double> * inp = new funneled_perceptron_in<double>(true, false, r, "PFUNNEL", N, 1E-5);

       	while (!inp->ready());
	while (!outp->ready());

       	cout<<endl<<"EXPLICIT (ONE-STEP PREDICTION)"<<endl;

	for (int i = 0; i < N + 50; i++) {
	    double seqn[N];
	    double b[N];
	    for (int j = 0; j < N; j++)
	        b[j] = sin(0.25*(i+j)/(N-1));
	    outb->put((void *) b, N*sizeof(double));
            seqn[0] = seq[0];
            seqn[N-1] = seq[N-1];
            for (int j = 1; j < N-1; j++)
                seqn[j] = seq[j] + 0.0025*(seq[j-1] - 2.0*seq[j] + seq[j+1] - b[j]);
            for (int j = 1; j < N-1; j++)
                seq[j] = seqn[j];
	    outp->put((void *) seqn, N*sizeof(double));

       	    double seqp[N];
       	    double bb[N];
       	    inb->get((void *) bb, N*sizeof(double));
       	    if (inp->get_timed((void *) seqp, -1.0)) {
       	       double buf[N];
       	       inp->get_and_correct((void *) buf);
       	       for (int j = 0; j < N; j++)
       	           cout << buf[j] << " ";
               cout << " [predict=";
       	       for (int j = 0; j < N; j++)
       	           cout << seqp[j] << " ";
               cout << "] " << endl;
            } else {
       	       for (int j = 0; j < N; j++)
       	           cout << seqp[j] << " ";
               cout << endl;
       	    }
	}

	delete outp;
	delete outb;
       	delete inp;
       	delete inb;

	r.clear();

	funneled_perceptron_out<double> * outbb = new funneled_perceptron_out<double>(true, false, r, "bbPFUNNEL", N, 1E-5);
	funneled_perceptron_out<double> * outpi = new funneled_perceptron_out<double>(EXPLICIT_PERCEPTRON, false, r, "iPFUNNEL", N, 1E-5);

       	funneled_perceptron_in<double> * inbb = new funneled_perceptron_in<double>(true, false, r, "bbPFUNNEL", N, 1E-5);
       	r.push_back(inbb->getRef());
       	funneled_perceptron_in<double> * inpi = new funneled_perceptron_in<double>(EXPLICIT_PERCEPTRON, false, r, "iPFUNNEL", N, 1E-5);
       	inpi->getRef()->switchLU(false);

	while (!outpi->ready());
       	while (!inpi->ready());

       	if (EXPLICIT_PERCEPTRON)
       	   cout << "EXPLICIT";
       	else
       	   cout << "IMPLICIT";
       	cout<<" (FORECAST)"<<endl;

	for (int i = 0; i < N + 50; i++) {
	    double seqn[N];
	    double b[N];
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

       	    double seqp[N];
       	    double bb[N];
       	    inbb->get((void *) bb, N*sizeof(double));
       	    if (inpi->get_timed((void *) seqp, -1.0)) {
       	       double buf[N];
       	       inpi->get_and_correct((void *) buf);
       	       for (int j = 0; j < N; j++)
       	           cout << buf[j] << " ";
               cout << " [predict=";
       	       for (int j = 0; j < N; j++)
       	           cout << seqp[j] << " ";
               cout << "] " << endl;
            } else {
       	       for (int j = 0; j < N; j++)
       	           cout << seqp[j] << " ";
               cout << endl;
       	    }
	}

        double seqpp[N];
	for (int i = N + 50; i < 300; i++) {
	    double seqn[N];
	    double b[N];
	    for (int j = 0; j < N; j++)
	        b[j] = sin(0.25*(i+j)/(N-1));
	    outbb->put((void *) b, N*sizeof(double));
	    outpi->put((void *) seqn, N*sizeof(double));

       	    double bb[N];
       	    inbb->get((void *) bb, N*sizeof(double));
       	    if (inpi->get_timed((void *) seqpp, -1.0)) {
       	       inpi->cancel_and_push((void *) seqpp);
            } else
               cout << "NO PREDICTION!" << endl;
	}

    	cout << "PREDICTED: ";
   	for (int j = 0; j < N; j++)
   	    cout << seqpp[j] << " ";
   	cout << endl;

	for (int i = N + 50; i < 300; i++) {
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
               int iRow[N];
               long double A[N][N] = {0.0}, LU[N][N];
               long double Y[N];
               long double X[N] = { 0.0 };
               A[0][0] = 1.0; Y[0] = seq[0];
               for (int j = 1; j < N-1; j++) {
                   A[j][j] = 1.0 + 2.0*0.0025;
                   A[j][j-1] = -0.0025;
                   A[j][j+1] = -0.0025;  
                   Y[j] = seq[j] - 0.0025*b[j];
               }
               A[N-1][N-1] = 1.0; Y[N-1] = seq[N-1];
               _GetLU(N, iRow, (long double *)A, (long double *)LU);
               _SolveLU(N, iRow, (long double *)LU, Y, X);
               for (int j = 0; j < N; j++)
                   seq[j] = X[j];
            }
	}
	cout << "CALCULATED: ";
	for (int j = 0; j < N; j++)
       	    cout << seq[j] << " ";
       	cout << endl;

	delete outpi;
	delete outbb;

       	delete inpi;
       	delete inbb;

	return 0;
}