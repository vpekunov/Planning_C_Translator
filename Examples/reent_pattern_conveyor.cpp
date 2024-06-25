#include <functional>
#include <iostream>

#include <stdlib.h>

using namespace std;

template<class... Args>
class ConveyoredFunction;

template<class... Args>
class Conveyor;

chain conveyor(Conveyor<int> * Chief, int A);

template<class... Args>
class Conveyor {
  private:
    int n;
    ConveyoredFunction<Args...> ** Fs;
  public:
    Conveyor() {
       this->n = 0;
       Fs = NULL;
    }

    ~Conveyor() {
       for (int i = 0; i < n; i++)
           delete Fs[i];
       delete[] Fs;
    }

    void add_stages(int ns, ConveyoredFunction<Args...> * F) {
       if (ns <= 0) return;

       int nn = this->n;

       n += ns;

       ConveyoredFunction<Args...> ** NF = new ConveyoredFunction<Args...> * [n];
       memmove(NF,Fs,nn*sizeof(ConveyoredFunction<Args...> *));
       delete[] Fs;
       Fs = NF;

       Fs[nn] = F;
       F->set_owner(this);
       F->set_stage(nn);

       for (int i = nn + 1; i < n; i++) {
           Fs[i] = F->clone();
           Fs[i]->set_stage(i);
       }
    }

    ConveyoredFunction<Args...> * get_stage(int i) {
       if (i < 0 || i >= n) return NULL;

       return Fs[i];
    }

    int get_num_stages() const {
       return n;
    }

    void run() {
       plan_parallel_chain(0, n, conveyor(this, -1));
    }
};

template<class... Args>
class ConveyoredFunction {
  protected:
    const Conveyor<Args...> * owner;
    std::function<void(Args...)> send;
    int stage;
  public:
    ConveyoredFunction(): owner(NULL), stage(0) {
    }

    virtual ConveyoredFunction<Args...> * clone() = 0;

    void set_owner(const Conveyor<Args...> * owner) {
       this->owner = owner;
    }

    void set_stage(int stage) {
       this->stage = stage;
    }

    virtual void set_sender(std::function<void(Args...)> send) {
       this->send = send;
    }

    virtual void run(Args...) = 0;
};

chain conveyor(Conveyor<int> * Chief, int A) {
    if (Chief == NULL) return;

    std::function<void(int)> send = [&] (int A) {
         throw_last(Chief, A);
    };

    Chief->get_stage(throw_stage())->set_sender(send);
    Chief->get_stage(throw_stage())->run(A);
}

class MyConveyoredFunction: public ConveyoredFunction<int> {
  public:
    virtual ConveyoredFunction<int> * clone() {
       ConveyoredFunction<int> * result = new MyConveyoredFunction();
       result->set_owner(owner);
       result->set_stage(stage);
       return result;
    }

    virtual void run(int A) {
      plan_critical(topology) {
        A += stage;
      }
      if (stage == owner->get_num_stages() - 1) cout << A << endl;
      else send(A);
    }
};

int main() {
    Conveyor<int> C;
    ConveyoredFunction<int> * F = new MyConveyoredFunction();

    C.add_stages(5, F);

    C.run();
}