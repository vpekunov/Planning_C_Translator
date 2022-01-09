// Debugged

// Reenterable reent_planning.cpp reent1.cpp
// g++ -o reent reent1.cpp -fopenmp -fgnu-tm -fpermissive -std=c++0x -lm -lpthread -lOpenCL

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/timeb.h>

#include <math.h>

int _time(time_t * Arg) {
  return time(Arg);
}

double time() {
#ifdef _MSC_VER
  struct _timeb timebuf;
  _ftime(&timebuf);
#else
  struct timeb timebuf;
  ftime(&timebuf);
#endif
  return (double) timebuf.time + (double) timebuf.millitm/1000;
}

int ArrayN = 0;
reenterable[20] static Array(int Data)
{
 ArrayN-- > 0 && plan_first(Data) && plan_last(Data) || plan_stop;
}

plan_type(Array) GenArray(int N) {
 plan_type(Array) Empty;
 ArrayN = N;
 *Array = Empty;
 auto callArray = [&] ()->bool {
   Array(0);
   return true;
 };
 N > 0 && callArray();
 return *Array;
}

reenterable int _DelArrayItem(plan_type(Array) & A, int index) {
  A[index] = A[index+1];
  index < _size(A)-2 && plan_last(A, index+1);
  return 1;
}

void DelArrayItem(plan_type(Array) & A, int index) {
  index < _size(A)-1 && _DelArrayItem(A, index);
  plan_item_type(Array) dummy;
  A>>dummy;
}

int ArrayN1 = 0;
int ArrayN2 = 0;

reenterable[20] static Array2D(const plan_type(Array) Line) {
 auto if_body = [&] ()->int {
   plan_first(Line);
   plan_last(GenArray(ArrayN2));
   return 1;
 };

 ArrayN1-- > 0 && if_body() || plan_stop;
}

plan_type(Array2D) GenArray2D(int N1, int N2) {
 auto if_body = [&] ()->int {
   plan_type(Array2D) Empty;
   plan_type(Array) Dummy;
   ArrayN1 = N1;
   ArrayN2 = N2;
   *Array2D = Empty;
   Array2D(Dummy);
   return 1;
 };
 N1 > 0 && if_body();
 return *Array2D;
}

int ListN = 0;
reenterable static List(int Data)
{
 auto if_body = [&] ()->int {
   plan_first(Data);
   plan_last(Data);
   return 1;
 };

 ListN-- > 0 && if_body() || plan_stop;
}

plan_type(List) GenList(int N) {
 auto if_body = [&] ()->int {
   plan_type(List) Empty;
   ListN = N;
   *List = Empty;
   List(0);
   return 1;
 };
 N > 0 && if_body();
 return *List;
}

reenterable int _DelListItemMove(plan_type(List) & L, int N) {
  auto if_body = [&] ()->int {
    plan_item_type(List) item;
    item<<L;
    L<<item;
    plan_last(L, N-1);
    return 1;
  };
  N > 0 && if_body();
  return 1;
}

reenterable _DelListItem(plan_type(List) & L, int rest, int i) {
  plan_item_type(List) item;
  item<<L;
  auto else_body = [&] ()->int {
    L<<item;
    plan_last(L, rest-1, i-1);
    return 1;
  };
  i == 0 && _DelListItemMove(L, rest-1) || else_body();
}

void DelListItem(plan_type(List) & L, int index) {
  _DelListItem(L, _size(L), index);
}

reenterable int OutArray(plan_type(Array) &A, int j) {
 auto if_body = [&] ()->int {
   printf("%i ", A[j].Data);
   plan_first(A, j+1);
   return 1;
 };
 j < _size(A) && if_body();
 return 1;
}

reenterable OutArray2D(plan_type(Array2D) &A, int i) {
 i < _size(A) && OutArray(A[i].Line, 0) && printf("\n") && plan_first(A, i+1);
}

reenterable int OutList(plan_type(List) &L, int rest) {
 auto if_body = [&] ()->int {
   plan_item_type(List) item;
   item<<L;
   L<<item;
   printf("%i ", item.Data);
   plan_first(L, rest-1);
   return 1;
 };
 rest > 0 && if_body();
 return 1;
}

reenterable static ByExternal(int A) {
  printf("%i ", A);
}

reenterable static External(int A, double X, int B) {
  printf("(%i _ %i) ", A, B);
}

int main(int argc, char ** argv)
{
 plan_type(Array) ARRAY = GenArray(5);
 plan_item_type(Array) ITEM = *Array[1];
 ARRAY[0] = ITEM;

 OutArray(ARRAY, 0);
 printf("\n\n");

 ITEM.Data = 1;
 ITEM>>ARRAY;
 ITEM.Data = 2;
 ARRAY<<ITEM;
 printf("%i-%i\n\n",(++ARRAY).Data,(ARRAY++).Data);

 DelArrayItem(ARRAY, 2);

 OutArray(ARRAY, 0);
 printf("\n\n");

 plan_type(Array2D) ARRAY2D = GenArray2D(3, 4);

 OutArray2D(ARRAY2D, 0);
 printf("\n\n");

 plan_type(List) L = GenList(0);
 plan_item_type(List) IL;
 IL.Data = 6;
 IL>>L;
 IL.Data = 7;
 L<<IL;

 OutList(L, _size(L));
 printf("\n\n");

 printf("Simple external planning\n");
 for (int i = 0; i < 10; i++) {
     plan_item_type(ByExternal) S;
     S.A = i;
     *ByExternal<<S;
 }
// continue ByExternal(-1);
 ByExternal([-1]);
 printf("\n");

 printf("Plan<=>array external planning\n");
 int array[10];
 for (int i = 0; i < 10; i++)
     array[i] = i;
 *External<<[array[],_,1];
 int array2[10] = {0};
 *External>>[array2[]];
 // continue External(-1, 0.0, -1);
 External([-1, 0.0, -1]);
 printf("\n");
 for (int i = 0; i < 10; i++)
     printf("%i ", array2[i]);
 printf("\n");

 printf("FINISH\n");

 return 0;
}
//---------------------------------------------------------------------------
