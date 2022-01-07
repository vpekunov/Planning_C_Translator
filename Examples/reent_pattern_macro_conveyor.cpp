#include <functional>
#include <iostream>

#include <stdlib.h>

using namespace std;

template<class... Args>
class ConveyoredFunction;

template<class... Args>
class Conveyor;

#def_module() declare_conveyor(ID,Types,Names,Vars) {
@goal:-brackets_off.

chain @goal:-write(ID),write('_').conveyor(Conveyor<@goal:-write(Types).> * Chief, @goal:-write(Vars).);

template<>
class ConveyoredFunction<@goal:-write(Types).> {
  protected:
    const Conveyor<@goal:-write(Types).> * owner;
    std::function<void(@goal:-write(Types).)> send;
    int stage;
  public:
    ConveyoredFunction(): owner(NULL), stage(0) {
    }

    virtual ConveyoredFunction<@goal:-write(Types).> * clone() = 0;

    void set_owner(const Conveyor<@goal:-write(Types).> * owner) {
       this->owner = owner;
    }

    void set_stage(int stage) {
       this->stage = stage;
    }

    virtual void set_sender(std::function<void(@goal:-write(Types).)> send) {
       this->send = send;
    }

    virtual void run(@goal:-write(Types).) = 0;
};

template<>
class Conveyor<@goal:-write(Types).> {
  private:
    int n;
    ConveyoredFunction<@goal:-write(Types).> ** Fs;
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

    void add_stages(int ns, ConveyoredFunction<@goal:-write(Types).> * F) {
       if (ns <= 0) return;

       int nn = this->n;

       n += ns;

       ConveyoredFunction<@goal:-write(Types).> ** NF = new ConveyoredFunction<@goal:-write(Types).> * [n];
       memmove(NF,Fs,nn*sizeof(ConveyoredFunction<@goal:-write(Types).> *));
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

    ConveyoredFunction<@goal:-write(Types).> * get_stage(int i) {
       if (i < 0 || i >= n) return NULL;

       return Fs[i];
    }

    int get_num_stages() const {
       return n;
    }

    void run() {
       plan_parallel_chain(0, n, @goal:-write(ID),write('_').conveyor(this, -1));
    }
};

chain @goal:-write(ID),write('_').conveyor(Conveyor<@goal:-write(Types).> * Chief, @goal:-write(Vars).) {
    if (Chief == NULL) return;

    std::function<void(@goal:-write(Types).)> send = [&] (@goal:-write(Vars).) {
         throw_last(Chief, A);
    };

    Chief->get_stage(throw_stage())->set_sender(send);
    Chief->get_stage(throw_stage())->run(@goal:-write(Names).);
}

};

declare_conveyor('simple','int','A','int A')

class MyConveyoredFunction: public ConveyoredFunction<int> {
  public:
    virtual ConveyoredFunction<int> * clone() {
       ConveyoredFunction<int> * result = new MyConveyoredFunction();
       result->set_owner(owner);
       result->set_stage(stage);
       return result;
    }

    virtual void run(int A) {
      A += stage;
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