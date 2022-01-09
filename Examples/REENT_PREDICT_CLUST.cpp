#pragma plan clustered

#include <stdlib.h>
#include <omp.h>
#include <time.h>

const bool EXPLICIT_PERCEPTRON = false;

const int N = 26;

chain sender() {
	double seq[N] = { 1.0, 2.0, 3.0, 4.0, 3.0, 2.0, 1.0, 2.0, 3.0, 4.0, 3.0, 1.0, 2.0, 3.0, 5.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0, 2.0, 1.0 };
	cfunneled_predictor_out<double> * out = new cfunneled_predictor_out<double>("FUNNEL", 1, 4, 0.01);
	while (!out->ready());
	for (int i = 0; i < N; i++) {
	    out->put((void *) &seq[i], sizeof(double));
	    Sleep(20);
	}
	delete out;
}

chain receiver() {
	double seq1[N] = { 0 };
       	cfunneled_predictor_in<double> * in = new cfunneled_predictor_in<double>("FUNNEL", 1, 4, 0.01);
       	while (!in->ready());
       	for (int i = 0; i < N; i++) {
       	    if (in->get_timed((void *) &seq1[i], rand() % 30)) {
       	       double buf = 0.0;
       	       in->get_and_correct((void *) &buf);
       	       cout << buf << "[predict=" << seq1[i] << "] ";
            } else
               cout << seq1[i] << " ";
        }
       	delete in;
	plan_topology_quit();
}

int main() {
	srand((unsigned int) time(NULL));

	int IDS[2] = {0,1};

	clustered(IDS)
	plan_topology {
		plan_parallel_chain(sender(),receiver());
	};

	return 0;
}