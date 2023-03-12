// 04 processors

/* example of MPI_Allgatherv; doesn't make much sense if you don't
 * run it on exactly 4 processors. */
#include "mpi.h"
#include <stdio.h>

static int array[4] = {1,2,3,4};
static int _rank() {
  int r;
  MPI_Comm_rank(MPI_COMM_WORLD, &r);
  return r;
}

int main() {
  MPI_Init(NULL, NULL);
  /* this next line changes the array on each processor into:
   *   proc 0: {42,  2,  3,  4}
   *   proc 1: { 1, 43,  3,  4}
   *   proc 2: { 1,  2, 44,  4}
   *   proc 3: { 1,  2,  3, 45}
   * the fact that Nprocessors == 4 && the length of this array is 4 is a
   * coincidence; the array can easily be longer than 4 elements---but it could
   * not be shorter. */
  array[_rank()] = _rank() + 42;
  /* where do these data exist, as offsets, per-process?  note that there 4
   * entries here, one per process. */
  static int offsets[4] = {0,1,2,3};
  /* how many values does each process have?  again, one value per-process.
   * and, because our array is 4 elements long, that value is always 1 (each
   * processor has one value) */
  static int num[4] = {1,1,1,1};

  /* now do the actual gatherv. */
  MPI_Allgatherv(&array[offsets[_rank()]], num[_rank()], MPI_INT,
                 array, num, offsets, MPI_INT, MPI_COMM_WORLD);
  /* because every element of num[] is exactly the same, we actually could have
   * simplified a bit and used 'MPI_Allgather' (no 'v'). */

  /* Now let's have everybody output the array to make sure it is what we think
   * it is---which should be:
   *   proc 0: {42, 43, 44, 45}
   *   proc 1: {42, 43, 44, 45}
   *   proc 2: {42, 43, 44, 45}
   *   proc 3: {42, 43, 44, 45} */
  printf("%d: [%d, %d, %d, %d]\n", _rank(), array[0], array[1], array[2],
         array[3]);
  MPI_Finalize();
  return 0;
}