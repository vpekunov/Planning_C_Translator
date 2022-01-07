// Debugged

#include <iostream>

using namespace std;

#def_module() big_loop(Vars, Lows, Highs) {
  @goal:-brackets_off.
  @loop([],[],[]):-!.
  @loop([V|VT],[L|LT],[H|HT]):-
    write('for (int '),write(V),write('='),write(L),write(';'),
                   write(V),write('<='),write(H),write(';'),
                   write(V),write('++) '),
    loop(VT,LT,HT).
  @goal:-loop(Vars,Lows,Highs).
};

int main() {
  big_loop(['i','j','k'],[0,0,0],[2,3,4])
    cout<<"1";

  cout<<endl;

  return 0;
}
