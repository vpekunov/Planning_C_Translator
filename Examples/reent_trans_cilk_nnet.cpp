#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <vector>
#include <stack>
#include <iostream>

#include "transacted.h"

using namespace std;

const char * DAT[] = {
"50.000000	30.527700	5.668866	7.545523	5.262250",
"50.000000	73.533087	9.278161	9.389566	6.232450",
"50.000000	113.129585	12.226620	7.992839	6.706777",
"50.000000	140.698011	14.563167	5.470044	7.006562",
"50.000000	148.354697	15.673319	1.814186	7.476296",
"50.000000	130.455612	15.314189	2.079262	8.117548",
"50.000000	91.031515	13.784235	4.734710	8.842277",
"50.000000	49.234504	11.865142	4.706337	9.430904",
"50.000000	46.936281	10.416550	1.968263	9.196629",
"50.000000	69.428361	9.876998	1.721615	8.376031",
"50.000000	83.819290	9.780172	4.746266	7.671438",
"50.000000	88.113380	9.440227	6.777442	7.108206",
"50.000000	84.793616	8.623801	8.064704	6.606611",
"50.000000	76.283776	7.389450	8.856261	6.114212",
"50.000000	64.715011	5.868827	9.304525	5.621986",
"50.000000	52.313844	4.230963	9.439428	5.183087",
"50.000000	42.101390	2.891794	8.975389	4.949137",
"50.000000	37.467654	4.746471	7.609962	5.091322",
"50.000000	47.145971	4.883696	11.313330	5.191111",
"50.000000	84.944799	3.562475	13.313693	6.125900",
"50.000000	125.107553	2.448307	12.023511	6.909243",
"50.000000	155.349334	2.913388	9.570072	7.556191",
"50.000000	167.066532	6.379858	5.837878	8.259818",
"50.000000	154.686465	10.403473	1.706645	8.643927",
"50.000000	124.357625	12.870164	1.504084	8.950024",
"50.000000	98.601162	13.297852	2.300297	9.430467",
"50.000000	99.349195	12.142069	0.549145	9.859623",
"50.000000	115.581825	10.257901	2.795873	9.725682",
"50.000000	128.079217	8.484015	6.322804	9.169953",
"50.000000	132.019201	7.165898	9.166333	8.480168",
"50.000000	128.987490	6.242759	11.165783	7.828331",
"50.000000	121.691315	5.588492	12.455620	7.264691",
"50.000000	112.606309	5.132128	13.204684	6.803718",
"50.000000	103.831406	4.870891	13.502781	6.482160",
"50.000000	97.060493	4.952151	13.207685	6.327043",
"50.000000	93.350284	11.054537	11.982765	6.105683",
"50.000000	63.923647	7.021543	11.086776	5.646868",
"50.000000	100.109215	4.748063	13.186166	6.538818",
"50.000000	142.473269	3.931237	11.703107	7.376030",
"50.000000	176.726697	3.799083	8.802522	7.967612",
"50.000000	192.848975	6.186698	4.189411	8.394122",
"50.000000	183.285011	9.431953	0.992462	8.560310",
"50.000000	153.657344	10.640407	5.436333	8.804926",
"50.000000	128.304882	9.893718	7.138275	9.200039",
"50.000000	125.164773	8.203438	6.341587	9.663091",
"50.000000	138.612725	6.361091	3.726432	9.745214",
"50.000000	153.013977	4.743920	0.256271	9.419042",
"50.000000	160.985264	3.545905	3.108893	8.882840",
"50.000000	162.101988	2.810610	5.855026	8.316690",
"50.000000	158.422978	2.438083	7.854874	7.804368",
"50.000000	152.346920	2.292278	9.165991	7.378442",
"50.000000	145.895440	2.298859	9.880320	7.053888",
"50.000000	140.521765	2.509360	9.983885	6.747252",
"50.000000	137.182886	14.256179	9.039501	6.199721",
"50.000000	77.747332	8.877712	10.860651	6.129370",
"50.000000	114.977813	6.161305	13.058009	7.023535",
"50.000000	160.758507	5.452228	11.240866	7.837164",
"50.000000	199.305362	4.755071	7.602579	8.265434",
"50.000000	218.406127	5.884114	1.501747	8.308426",
"50.000000	205.848515	8.401457	5.029071	8.153146",
"50.000000	165.906371	8.212129	10.800109	8.269219",
"50.000000	132.843566	5.999536	12.341900	8.335887",
"50.000000	123.829720	3.694848	11.441821	8.426413",
"50.000000	134.458945	2.702672	9.089747	8.622599",
"50.000000	150.548140	2.507002	5.962446	8.717803",
"50.000000	163.219549	2.254800	2.725786	8.610553",
"50.000000	170.087830	1.870679	0.170812	8.360291",
"50.000000	171.886214	1.465540	2.485798	8.056324",
"50.000000	170.354367	1.117007	4.154887	7.762170",
"50.000000	167.253389	0.849620	5.206774	7.497433",
"50.000000	163.988783	0.614241	5.664678	7.093136",
"50.000000	161.611878	16.231929	4.962547	6.206767",
"50.000000	87.123786	10.325583	10.593698	6.489788",
"50.000000	126.819299	7.650905	12.856096	7.399940",
"50.000000	176.298580	6.933859	10.574007	8.159524",
"50.000000	218.486276	5.659042	5.864880	8.425128",
"31.250000	188.376088	5.334301	2.820913	8.112971",
"25.000000	151.737751	8.226626	10.820718	7.572399",
"25.000000	106.291977	7.891007	17.766346	7.582868",
"25.000000	75.347709	4.049001	16.805770	7.289079",
"25.000000	66.273622	1.001206	14.810701	7.155487",
"25.000000	73.716475	3.200742	12.458383	7.577475",
"31.250000	97.184442	4.481223	9.777081	8.120882",
"50.000000	140.211427	4.858594	7.091234	8.468619",
"50.000000	152.867922	4.755492	4.539647	8.593845",
"50.000000	160.558096	4.434283	2.346800	8.576391",
"50.000000	164.206398	4.065534	0.641698	8.495510",
"50.000000	165.106110	3.734692	0.539969	8.370560",
"50.000000	164.479394	3.467980	1.213706	7.919184",
"50.000000	163.382540	16.516845	0.717742	6.616876",
"50.000000	91.528296	11.261411	10.294316	6.692408",
"50.000000	133.996600	8.973701	12.556411	7.604557",
"50.000000	186.184822	8.207675	9.771895	8.289582",
"31.250000	182.144795	6.493511	3.829583	8.417459",
"12.500000	124.335710	4.612526	9.829586	7.893637",
"6.250000	71.792257	16.491654	30.503137	6.947060",
"6.250000	34.126275	12.615664	25.278749	6.996889",
"6.250000	18.457583	5.728688	16.144698	6.506068",
"6.250000	15.193723	3.978149	13.144248	6.316317",
"6.250000	20.010307	6.360844	13.107962	7.038956",
"12.500000	39.493623	6.453033	10.738092	7.652821",
"31.250000	79.215273	6.624466	9.124816	8.252491",
"50.000000	117.604522	6.541195	7.300467	8.664624",
"50.000000	130.376583	6.255548	5.586144	8.941206",
"50.000000	138.741498	5.905062	4.140537	9.121614",
"50.000000	143.477069	5.587984	3.047455	9.193402",
"50.000000	145.491424	5.379416	2.302700	8.806106",
"50.000000	145.714177	15.176623	2.604139	7.288049",
"50.000000	91.353155	11.628437	9.945117	6.752799",
"50.000000	135.773236	9.814554	12.085347	7.658033",
"50.000000	187.973469	8.968915	8.944551	8.259475",
"25.000000	163.245605	7.470336	2.945371	8.259803",
"6.250000	87.706174	13.562305	28.563477	7.845901",
"0.000000	0.000000	18.395867	37.129831	5.797574",
"0.000000	0.000000	7.916217	7.810470	5.817490",
"0.000000	0.000000	3.878966	4.941298	5.233222",
"0.000000	0.000000	3.053257	4.276812	4.797636",
"0.000000	0.000000	4.495150	6.812491	4.217153",
"6.250000	11.926020	6.599962	8.982039	5.448180",
"25.000000	39.800878	6.428518	8.503299	7.026483",
"50.000000	75.954049	6.602676	7.666338	8.025211",
"50.000000	91.721632	6.499767	6.725923	8.662228",
"50.000000	103.289644	6.290492	5.791723	9.114788",
"50.000000	110.893484	6.078785	4.982650	9.367959",
"50.000000	115.050977	5.975452	4.307943	9.120577",
"50.000000	116.438653	12.664810	4.437176	7.755082",
"50.000000	87.742124	11.473641	9.476166	6.721373",
"50.000000	132.449692	9.901322	11.194501	7.630089",
"50.000000	180.185385	8.535338	7.221228	8.129000",
"25.000000	149.901345	6.526602	0.669443	7.955419",
"6.250000	70.529683	14.042641	25.753972	7.770819",
"0.000000	0.000000	14.498879	19.377172	5.835987",
"0.000000	0.000000	0.759603	0.009632	3.333065",
"6.250000	2.685708	3.359892	3.679428	4.324209",
"25.000000	16.377594	4.556251	5.680257	5.847973",
"50.000000	40.353043	5.125284	6.176411	7.035734",
"50.000000	55.662809	5.370538	6.100539	7.898734",
"50.000000	67.900873	5.427456	5.775985	8.529476",
"50.000000	76.670915	5.400194	5.358383	8.918917",
"50.000000	81.994767	5.431917	4.862993	8.809648",
"50.000000	84.175691	9.634530	4.870869	7.721594",
"50.000000	82.004359	10.988360	8.874736	6.661426",
"50.000000	125.759220	9.535379	10.052579	7.577426",
"50.000000	167.288276	7.827181	5.625507	7.918889",
"25.000000	133.939431	6.038410	1.938297	7.611692",
"6.250000	58.958355	13.039183	21.184349	7.729591",
"0.000000	0.000000	11.964494	16.427896	5.793391",
"0.000000	0.000000	0.455031	0.603260	2.412300",
"6.250000	2.205151	1.354493	0.513093	2.904118",
"25.000000	6.019741	2.389221	2.821150	4.192696",
"50.000000	17.947413	3.182530	3.993884	5.480432",
"50.000000	29.190904	3.686051	4.548819	6.531122",
"50.000000	39.418045	3.968115	4.740183	7.331161",
"50.000000	47.461876	4.109245	4.699947	7.842653",
"50.000000	52.782948	4.252993	4.430711	7.867561",
"50.000000	55.238528	6.698536	4.378334	7.073863",
"50.000000	74.755293	10.359151	8.035330	6.620832",
"50.000000	116.805950	9.061275	8.626950	7.502287",
"50.000000	151.947438	7.219597	4.116886	7.616737",
"25.000000	118.474018	5.523821	2.495813	7.232506",
"6.250000	50.588410	11.544819	18.217456	7.635907",
"0.000000	0.000000	10.195408	14.197791	5.751756",
"0.000000	0.000000	0.569257	0.805050	1.605425",
"6.250000	2.846283	0.746033	0.593618	1.696683",
"25.000000	5.682222	1.044621	1.154872	2.556517",
"50.000000	8.322123	1.658441	2.263134	3.666848",
"50.000000	13.260586	2.163645	2.978148	4.737590",
"50.000000	19.879598	2.515693	3.416546	5.621170",
"50.000000	25.917819	2.736358	3.619670	6.220228",
"50.000000	30.336371	2.933894	3.542937	6.379881",
"50.000000	32.605651	4.243821	3.471310	5.863819",
"50.000000	65.477882	9.760733	6.711203	6.617856",
"50.000000	105.662958	8.769396	6.789154	7.359510",
"50.000000	135.365277	6.785882	2.641592	7.241459",
"25.000000	104.426422	4.856680	2.627084	6.887768",
"6.250000	44.587314	9.946797	16.031772	7.436682",
"0.000000	0.000000	8.942932	12.575075	5.777011",
"0.000000	0.000000	0.595276	0.841565	0.993315",
"6.250000	2.975879	0.668814	0.965618	0.913552",
"25.000000	6.755404	0.328499	0.312186	1.387525",
"50.000000	8.096894	0.676502	1.127231	2.172706",
"50.000000	7.196758	1.047952	1.739280	3.032906",
"50.000000	8.857206	1.350402	2.210055	3.823623",
"50.000000	12.008334	1.568974	2.512116	4.411224",
"50.000000	14.956759	1.767362	2.561767	4.643211",
"50.000000	16.729914	2.406176	2.493254	4.341141",
"50.000000	52.288414	9.537894	4.465448	6.608065",
"50.000000	92.172398	8.863106	4.499956	7.066948",
"50.000000	119.063437	6.356905	1.328308	6.868194",
"25.000000	92.749613	3.823478	2.238274	6.701951",
"6.250000	40.798180	8.791020	13.998958	7.196306",
"0.000000	0.000000	8.161895	11.536272	5.926546",
"0.000000	0.000000	0.588027	0.831474	0.687095",
"6.250000	2.939920	0.671776	1.004249	0.676731",
"25.000000	6.908136	0.070656	0.029010	0.877735",
"50.000000	8.952605	0.160282	0.461366	1.322252",
"50.000000	7.332800	0.347732	0.866660	1.878498",
"50.000000	5.710580	0.527549	1.245095	2.440828",
"50.000000	5.086157	0.685860	1.542373	2.896196",
"50.000000	5.815886	0.853586	1.658923	3.114211",
"50.000000	6.814396	1.155755	1.611896	2.956143",
"50.000000	33.998199	9.128853	3.677885	6.345124",
"50.000000	79.220326	11.677191	3.971300	6.549717",
"50.000000	107.104225	12.629647	1.491106	6.645832",
"25.000000	85.230724	13.136371	1.109995	6.808800",
"6.250000	39.123366	14.233952	12.315799	7.045593",
"0.000000	0.000000	7.824681	11.065748	6.227169",
"0.000000	0.000000	0.582161	0.823124	0.631845",
"6.250000	2.910494	1.071990	0.936720	0.702012",
"25.000000	6.694900	0.978056	0.093209	0.812175",
"50.000000	8.980718	0.903500	0.175776	1.037480",
"50.000000	7.728273	0.743304	0.393741	1.327533",
"50.000000	5.981124	0.532969	0.622646	1.642510",
"50.000000	3.984553	0.310989	0.824811	1.925501",
"50.000000	2.232881	0.207330	0.919795	2.092327",
"50.000000	1.662780	0.371148	0.867718	2.041551"
};

const int NI = 4;
const int NR = 216;

const int EPOCHS = 1000;

const int ML = 3;
const int NL[ML-1] = { 3, 5 };

const double EPS = 0.00001;

const double nu = 0.01;

class Neuron;

double sum (double A, double B) {
	return A + B;
};

class Environment {
public:
	TArray<double> * deltas[ML];

	vector< vector<Neuron *> > Neurons;

	double * M[NI];
	double * Y;

	double MMAX[NI];
	double MMIN[NI];
	double NUMIN;
	double NUMAX;

	vector<int> nums;
	vector<int> idxs;

	Environment(int nthreads);

	~Environment();
};

class Runner : public TQueuedObj<Environment> {
public:
	Runner(int nthreads) : TQueuedObj<Environment>(nthreads) {
	}

	double calcNet(int ii, double & y);
	void train(int ii, double delta);
};

class Neuron {
public:
	Environment * Env;

	int nInputs;
	double * W;
	double B;
	double Y;

	Neuron(int nInp, Environment * env) {
		nInputs = nInp;
		Env = env;
		W = new double[nInputs];
		for (int i = 0; i < nInputs; i++)
			W[i] = 1.0*rand()/RAND_MAX;
		B = 1.0*rand()/RAND_MAX;
		Y = 0.0;
	}

	virtual ~Neuron() {
		delete[] W;
	}

	virtual double f(double s) = 0;
	virtual double d(double s) = 0;

	virtual void calc(double * X) {
		Y = B;
		for (int i = 0; i < nInputs; i++)
			Y += W[i]*X[i];
		Y = f(Y);
	}

	virtual void train(double delta, TArray<double> * down_delta, double * X) {
		B += -nu*(delta);
		for (int i = 0; i < nInputs; i++) {
			W[i] += -nu*(delta)*X[i];
			if (down_delta)
				(*down_delta)[i] += d(X[i])*delta*W[i];
		}
	}
};

class LinNeuron : public Neuron {
public:
	LinNeuron(int nInp, Environment * env) : Neuron(nInp, env) {
	}

	virtual double f(double s) {
		return s;
	}

	virtual double d(double s) {
		return 1.0;
	}

};

class ExpNeuron : public Neuron {
public:
	ExpNeuron(int nInp, Environment * env) : Neuron(nInp, env) {
	}

	virtual double f(double s) {
		return 1.0 / (1.0 + exp(-s));
	}

	virtual double d(double ff) {
		return ff*(1.0 - ff);
	}
};

Environment::Environment(int nthreads) {
	for (int i = 0; i < ML-1; i++) {
		deltas[i] = new TArray<double>(NL[i]);
		deltas[i]->setReducer(sum);
	}
	deltas[ML-1] = new TArray<double>(1);
	deltas[ML-1]->setReducer(sum);

	NUMIN = 10000;
	NUMAX = -10000;

	for (int i = 0; i < NI; i++) {
		M[i] = new double[NR];
		MMAX[i] = -10000;
		MMIN[i] = 10000;
	}

	Y = new double[NR];

	for (int i = 0; i < NR; i++) {
		long double VALS[1024];

		char Buf[1024];
		strcpy(Buf, DAT[i]);

		char * next = NULL;
		char * val = strtok(Buf, "\t, ");

		for (int j = 0; j < NI+1; j++) {
			VALS[j] = atof(val);
			val = strtok(NULL, "\t, ");
		}
		for (int j = 0; j < NI; j++) {
			M[j][i] = VALS[j];
			if (M[j][i] > MMAX[j]) MMAX[j] = M[j][i];
			if (M[j][i] < MMIN[j]) MMIN[j] = M[j][i];
		}
		Y[i] = VALS[NI];
		if (Y[i] < NUMIN) NUMIN = Y[i];
		if (Y[i] > NUMAX) NUMAX = Y[i];
	}

	nums.resize(NR);
	idxs.resize(NR);
	for (int i = 0; i < NR; i++)
		nums[i] = i;
	for (int i = 0; i < NR; i++) {
		int idx = (int)(1.0*(nums.size()-1)*rand()/RAND_MAX);
		idxs[i] = nums[idx];
		nums.erase(nums.begin()+idx);
	}

	for (int p = 0; p < NI; p++) {
		double d = MMAX[p]==MMIN[p] ? 1.0 : 2.0/(MMAX[p]-MMIN[p]);
		for (int i = 0; i < NR; i++)
			M[p][i] = -1.0 + (M[p][i]-MMIN[p])*d;
	}

	double nud = NUMAX==NUMIN ? 1.0 : 1.0/(NUMAX-NUMIN);
	for (int i = 0; i < NR; i++)
		Y[i] = (Y[i]-NUMIN)*nud;

	Neurons.resize(ML);
	for (int i = 0; i < ML-1; i++) {
		Neurons[i].resize(NL[i]);
		for (int j = 0; j < NL[i]; j++) {
			Neurons[i][j] = new ExpNeuron(i == 0 ? NI : NL[i-1], this);
		}
	}
	Neurons[ML-1].push_back(new LinNeuron(ML > 1 ? NL[ML-2] : NI, this));
}

Environment::~Environment() {
	for (auto & layer : Neurons)
		for (auto & n : layer)
			delete n;
	for (int i = 0; i < NI; i++)
		delete[] M[i];
	delete[] Y;
	for (int i = 0; i < ML-1; i++)
		delete deltas[i];
	delete deltas[ML-1];
}

double Runner::calcNet(int ii, double & y) {
	int i = idxs[ii];

	double x[NI];
	for (int j = 0; j < NI; j++)
		x[j] = M[j][i];
	y = Y[i];

	int ids[50];
	int prevs[50];

	auto runner = [this, &x] (int j, int p) {
		double xx[50];
		int nInputs = j == 0 ? NI : NL[j-1];
		for (int k = 0; k < nInputs; k++)
			xx[k] = j == 0 ? x[k] : Neurons[j-1][k]->Y;
		Neurons[j][p]->calc(xx);
	};

	if (ML == 1) {
		ids[0] = cilk_spawn Neurons[ML-1][0]->calc(x);
	} else {
		int * pprevs = NULL;
		int nprevs = 0;
		for (int j = 0; j < ML; j++) {
			int NN = j < ML-1 ? NL[j] : 1;
			for (int p = 0; p < NN; p++) {
				ids[p] = cilk_spawn(nprevs, pprevs) runner(=j, =p);
			}
			nprevs = NN;
			pprevs = prevs;
			for (int p = 0; p < NN; p++)
				pprevs[p] = ids[p];
		}
	}
	cilk_sync;

	return Neurons[ML-1][0]->Y;
}

void Runner::train(int ii, double delta) {
	int i = idxs[ii];

	double x[NI];
	for (int j = 0; j < NI; j++)
		x[j] = M[j][i];

	int ids[50];
	int prevs[50];

	auto runner = [this, &x] (int j, int p) {
		double xx[50];
		int nInputs = j == 0 ? NI : NL[j-1];
		for (int k = 0; k < nInputs; k++)
			xx[k] = j == 0 ? x[k] : Neurons[j-1][k]->Y;
		Neurons[j][p]->train(
			(*deltas[j])[p],
			j > 0 ? deltas[j-1] : NULL,
			xx);
	};

	if (ML == 1) {
		ids[0] = cilk_spawn Neurons[ML-1][0]->train(delta, NULL, x);
	} else {
		int * pprevs = NULL;
		int nprevs = 0;

		*deltas[ML-1] = delta;
		for (int j = ML-2; j >= 0; j--)
			*deltas[j] = 0.0;

		for (int j = ML-1; j >= 0; j--) {
			int NN = j < ML-1 ? NL[j] : 1;

			for (int p = 0; p < NN; p++) {
				ids[p] = cilk_spawn(nprevs, pprevs) runner(=j, =p);
			}
			nprevs = NN;
			pprevs = prevs;
			for (int p = 0; p < NN; p++) {
				pprevs[p] = ids[p];
			}
		}
	}
	cilk_sync();
}

int main() {
	srand((unsigned int)time(NULL));

	Runner Env(16);

	for (int epoch = 0; epoch < EPOCHS; epoch++) {
		double err = 0.0;
		for (int ii = 0; ii < NR; ii++) {
			set_jobs_mode(true);

			double y = 0;

			double yy = Env.calcNet(ii, y);
			double delta = yy - y;
			err += delta*delta;

			Env.train(ii, delta);
		}
		cout << "Epoch[" << epoch << "], err^2 = " << err << endl;
	}

	return 0;
}