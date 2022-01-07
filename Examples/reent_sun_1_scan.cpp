#include "sun.h"

using namespace std;

#define NP 5

int main() {
    sun(NP) {
       int nProcs   = GET_ROOT()->ProcRoot->nProcs;
       int MyProcID = GET_ROOT()->ProcRoot->MyProcID;

       int error;

       if (MyProcID == 0) {
          LinkCB_t ** LinkList = (LinkCB_t **) malloc((nProcs-1)*sizeof(LinkCB_t *));
          Option_t *  Options  = (Option_t *)  malloc((nProcs-1)*sizeof(Option_t));

          int   Slave;
          int   f,g,v;
          int   sum = 0;

          for (f=0;f<nProcs-1;f++)
              {
               LinkList[f] = ConnectLink(f+1,1234,&error);
               Options[f]  = ReceiveOption(LinkList[f]);
              }

          for (g=0;g<nProcs-1;g++)
              {
                Slave = SelectList(nProcs-1,Options);
                RecvLink(LinkList[Slave],(byte *) &v, sizeof(v));
                sum += v;
              }
          printf("Sum = %i\n", sum);

          free (LinkList);
          free (Options);
       } else {
          LinkCB_t * L = ConnectLink(0,1234,&error);
          SendLink(L,(byte *) &MyProcID, sizeof(MyProcID));
       }
    };
}