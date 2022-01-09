#include "sun.h"

using namespace std;

#define NP 5

int main() {
    sun(NP) {
       int  MyProcID, nProcs;
       LinkCB_t *PrevLink, *NextLink;
       int error, sizeint;

       MyProcID = GET_ROOT()->ProcRoot->MyProcID;
       nProcs = GET_ROOT()->ProcRoot->nProcs;
       sizeint = sizeof ( int );

       if ( MyProcID == 0 ) 
       {  
         NextLink = ConnectLink ( 1, 1234, &error );
       }
       if ( (MyProcID != 0) && (MyProcID != nProcs-1) )
       {
         NextLink = ConnectLink ( MyProcID+1, 1234, &error );
         PrevLink = ConnectLink ( MyProcID-1, 1234, &error );
       }
       if ( MyProcID == nProcs-1 )
       { 
         PrevLink = ConnectLink ( nProcs-2, 1234, &error );
       }

       if ( MyProcID == 0 )
       {
         int m;
     
         printf ( " Input integer number :\n" );
         scanf ( "%d", &m ); 
         SendLink ( NextLink, (byte *)&m, sizeint );
       }
       else
       { 
         int l;

         RecvLink ( PrevLink, (byte *)&l, sizeint );
         l += MyProcID;
         if ( MyProcID != nProcs-1 ) 
            SendLink ( NextLink, (byte *)&l, sizeint );
         else
           printf ( " MyProcID = %d, sum = %d\n", MyProcID, l );
       }
    };
}