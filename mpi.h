#ifndef MPI_INCLUDED
#define MPI_INCLUDED

#include <omp.h>
#include <stdlib.h>
#include <stdio.h>

#include <map>
#include <vector>

using namespace std;

typedef int MPI_Datatype;

enum {
 MPI_CHAR = 1,          
 MPI_SIGNED_CHAR,    
 MPI_UNSIGNED_CHAR,  
 MPI_BYTE,           
 MPI_SHORT,          
 MPI_UNSIGNED_SHORT, 
 MPI_INT,            
 MPI_UNSIGNED,       
 MPI_LONG,           
 MPI_UNSIGNED_LONG,  
 MPI_FLOAT,          
 MPI_DOUBLE,         
 MPI_LONG_DOUBLE,    
 MPI_LONG_LONG_INT,  
 MPI_UNSIGNED_LONG_LONG,
 MPI_LONG_LONG,

 MPI_PACKED,
 MPI_LB,
 MPI_UB
};

class __Comm__ {
 public:
  int size;
  int * ranks;
  volatile int  barN;
  volatile bool barFlag;
  plan_lock_t barrier1;
  plan_lock_t barrier2;
  volatile int refs;

  __Comm__() {
    size  = 0;
    ranks = NULL;
    barN  = 0;
    barFlag = false;
    refs = 0;
    plan_init_lock(&barrier1);
    plan_init_lock(&barrier2);
  }
  __Comm__(int _size) {
    size  = _size;
    ranks = new int[_size];
    barN  = 0;
    barFlag = false;
    refs = 0;
    plan_init_lock(&barrier1);
    plan_init_lock(&barrier2);
  }
  ~__Comm__() {
    delete ranks;
    plan_destroy_lock(&barrier1);
    plan_destroy_lock(&barrier2);
  }
};

typedef __Comm__ * MPI_Comm;

const MPI_Comm MPI_COMM_WORLD = (MPI_Comm) 1;
const MPI_Comm MPI_COMM_SELF  = (MPI_Comm) 2;

typedef struct {
  int size;
  int * ranks;
} __Group__;

typedef __Group__ * MPI_Group;

const MPI_Group MPI_GROUP_EMPTY = (MPI_Group) 1;

typedef int MPI_Op;

enum {
 MPI_MAX = 1,
 MPI_MIN,
 MPI_SUM,
 MPI_PROD,
 MPI_LAND,
 MPI_BAND,
 MPI_LOR,
 MPI_BOR,
 MPI_LXOR,
 MPI_BXOR,
 MPI_REPLACE 
};

class __Win__ {
  public:
    __Comm__ * comm;

    char * bases[__NPROCS__];
    int    sizes[__NPROCS__];
    int    disp_unit_sizes[__NPROCS__];

    plan_lock_t exclusive_lock[__NPROCS__];
    volatile unsigned char locks[__NPROCS__][__NPROCS__];

    volatile int  barN;
    volatile bool barFlag;
    plan_lock_t   barrier1;
    plan_lock_t   barrier2;
    volatile int  refs;

    __Win__(__Comm__ * comm) {
      for (int i = 0; i < __NPROCS__; i++) {
          plan_init_lock(&exclusive_lock[i]);
          for (int j = 0; j < __NPROCS__; j++)
              locks[i][j] = 0;
      }
      this->comm = comm;
      refs = 0;
      barN  = 0;
      barFlag = false;
      plan_init_lock(&barrier1);
      plan_init_lock(&barrier2);
    };
    void _barrier() {
      plan_set_lock(&barrier1);
      barN++;
      if (barN == comm->size)
         barFlag = true;
      plan_unset_lock(&barrier1);

      plan_set_lock(&barrier2);
      while (!barFlag)
        _Yield();
      barN--;
      if (barN == 0)
         barFlag = false;
      plan_unset_lock(&barrier2);

      while (barFlag)
        _Yield();
    };
    ~__Win__() {
      plan_destroy_lock(&barrier1);
      plan_destroy_lock(&barrier2);
      for (int i = 0; i < __NPROCS__; i++)
          plan_destroy_lock(&exclusive_lock[i]);
    };
};

typedef __Win__ * MPI_Win;
#define MPI_WIN_NULL ((MPI_Win)0)

typedef int MPI_Info;
#define MPI_INFO_NULL ((MPI_Info)0)

#define MPI_COMM_NULL      ((MPI_Comm)0)
#define MPI_OP_NULL        ((MPI_Op)0)
#define MPI_GROUP_NULL     ((MPI_Group)0)
#define MPI_DATATYPE_NULL  ((MPI_Datatype)0)
#define MPI_REQUEST_NULL   ((MPI_Request)0)

#define MPI_MAX_PROCESSOR_NAME 128
#define MPI_MAX_ERROR_STRING  1024 
#define MPI_MAX_PORT_NAME      256
#define MPI_MAX_OBJECT_NAME    128

#define MPI_PROC_NULL   (-1)
#define MPI_ANY_SOURCE 	(-2)
#define MPI_ROOT        (-3)
#define MPI_ANY_TAG     (-1)

#define MPI_LOCK_EXCLUSIVE  2
#define MPI_LOCK_SHARED     1

class __Request__ {
 public:
   bool receiving;
   bool complete;
   bool persistent;

   bool any_tag;
   bool any_source;

   void * buf;

   int  rank;
   int  tag;
   int  type;
   int  items;

   __Comm__ * comm;

   __Request__ * next;
   __Request__ * prev;

   __Request__(int Rank, __Comm__ * Comm, int Tag, int Type, int Items, void * Buf, bool Persistent) {
     complete = false;

     rank  = Rank;
     comm  = Comm;
     tag   = Tag;
     type  = Type;
     items = Items;
     buf   = Buf;

     persistent = Persistent;

     any_tag    = tag  == MPI_ANY_TAG;
     any_source = rank == MPI_ANY_SOURCE;

     prev = NULL;
     next = NULL;
   };
};

class iRequest : public __Request__ {
 public:
   iRequest(int Rank, __Comm__ * Comm, int Tag, int Type, int Items, void * Buf, bool Persistent):
            __Request__(Rank, Comm, Tag, Type, Items, Buf, Persistent) {
     this->receiving = true;
   };
};

class oRequest : public __Request__ {
 public:
   oRequest(int Rank, __Comm__ * Comm, int Tag, int Type, int Items, void * Buf, bool Persistent):
            __Request__(Rank, Comm, Tag, Type, Items, Buf, Persistent) {
     this->receiving = false;
   };
};

typedef __Request__ * MPI_Request;

typedef int MPI_Aint;
typedef int MPI_Fint;

#define MPI_VERSION    1
#define MPI_SUBVERSION 0

typedef struct MPI_Status {
    int count;
    int cancelled;
    int MPI_SOURCE;
    int MPI_TAG;
    int MPI_ERROR;
} MPI_Status;

#define MPI_STATUS_IGNORE (MPI_Status *)1
#define MPI_STATUSES_IGNORE (MPI_Status *)1
#define MPI_ERRCODES_IGNORE (int *)0

#define MPI_ARGV_NULL (char **)0
#define MPI_ARGVS_NULL (char ***)0

#define MPI_BOTTOM      (void *)0
#define MPI_UNDEFINED   (-32766)
#define MPI_UNWEIGHTED  ((int *)0)

/* MPI's error classes */
#define MPI_SUCCESS          0      /* Successful return code */
/* Communication argument parameters */
#define MPI_ERR_BUFFER       1      /* Invalid buffer pointer */
#define MPI_ERR_COUNT        2      /* Invalid count argument */
#define MPI_ERR_TYPE         3      /* Invalid datatype argument */
#define MPI_ERR_TAG          4      /* Invalid tag argument */
#define MPI_ERR_COMM         5      /* Invalid communicator */
#define MPI_ERR_RANK         6      /* Invalid rank */
#define MPI_ERR_ROOT         7      /* Invalid root */
#define MPI_ERR_TRUNCATE    14      /* Message truncated on receive */

/* MPI Objects (other than COMM) */
#define MPI_ERR_GROUP        8      /* Invalid group */
#define MPI_ERR_OP           9      /* Invalid operation */
#define MPI_ERR_REQUEST     19      /* Invalid mpi_request handle */

/* Special topology argument parameters */
#define MPI_ERR_TOPOLOGY    10      /* Invalid topology */
#define MPI_ERR_DIMS        11      /* Invalid dimension argument */

/* All other arguments.  This is a class with many kinds */
#define MPI_ERR_ARG         12      /* Invalid argument */

/* Other errors that are not simply an invalid argument */
#define MPI_ERR_OTHER       15      /* Other error; use Error_string */

#define MPI_ERR_UNKNOWN     13      /* Unknown error */
#define MPI_ERR_INTERN      16      /* Internal error code    */

/* Multiple completion has two special error classes */
#define MPI_ERR_IN_STATUS   17      /* Look in status for error value */
#define MPI_ERR_PENDING     18      /* Pending request */

/* New MPI-2 Error classes */
#define MPI_ERR_FILE        27      /* */
#define MPI_ERR_ACCESS      20      /* */
#define MPI_ERR_AMODE       21      /* */
#define MPI_ERR_BAD_FILE    22      /* */
#define MPI_ERR_FILE_EXISTS 25      /* */
#define MPI_ERR_FILE_IN_USE 26      /* */
#define MPI_ERR_NO_SPACE    36      /* */
#define MPI_ERR_NO_SUCH_FILE 37     /* */
#define MPI_ERR_IO          32      /* */
#define MPI_ERR_READ_ONLY   40      /* */
#define MPI_ERR_CONVERSION  23      /* */
#define MPI_ERR_DUP_DATAREP 24      /* */
#define MPI_ERR_UNSUPPORTED_DATAREP   43  /* */

/* MPI_ERR_INFO is NOT defined in the MPI-2 standard.  I believe that
   this is an oversight */
#define MPI_ERR_INFO        28      /* */
#define MPI_ERR_INFO_KEY    29      /* */
#define MPI_ERR_INFO_VALUE  30      /* */
#define MPI_ERR_INFO_NOKEY  31      /* */

#define MPI_ERR_NAME        33      /* */
#define MPI_ERR_NO_MEM      34      /* Alloc_mem could not allocate memory */
#define MPI_ERR_NOT_SAME    35      /* */
#define MPI_ERR_PORT        38      /* */
#define MPI_ERR_QUOTA       39      /* */
#define MPI_ERR_SERVICE     41      /* */
#define MPI_ERR_SPAWN       42      /* */
#define MPI_ERR_UNSUPPORTED_OPERATION 44 /* */
#define MPI_ERR_WIN         45      /* */

#define MPI_ERR_BASE        46      /* */
#define MPI_ERR_LOCKTYPE    47      /* */
#define MPI_ERR_KEYVAL      48      /* Erroneous attribute key */
#define MPI_ERR_RMA_CONFLICT 49     /* */
#define MPI_ERR_RMA_SYNC    50      /* */ 
#define MPI_ERR_SIZE        51      /* */
#define MPI_ERR_DISP        52      /* */
#define MPI_ERR_ASSERT      53      /* */

#define MPI_ERR_LASTCODE    0x3fffffff  /* Last valid error code for a 
					   predefined error class */
/* End of MPI's error classes */

/* presents */ int MPI_Send(void*, int, MPI_Datatype, int, int, MPI_Comm);
/* presents */ int MPI_Recv(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Status *);
int MPI_Get_count(MPI_Status *, MPI_Datatype, int *);
int MPI_Bsend(void*, int, MPI_Datatype, int, int, MPI_Comm);
/* presents */ int MPI_Ssend(void*, int, MPI_Datatype, int, int, MPI_Comm);
int MPI_Rsend(void*, int, MPI_Datatype, int, int, MPI_Comm);
int MPI_Buffer_attach( void*, int);
int MPI_Buffer_detach( void*, int *);
/* presents */ int MPI_Isend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *);
int MPI_Ibsend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *);
int MPI_Issend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *);
int MPI_Irsend(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *);
/* presents */ int MPI_Irecv(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *);
/* presents */ int MPI_Wait(MPI_Request *, MPI_Status *);
/* presents */ int MPI_Test(MPI_Request *, int *, MPI_Status *);
/* presents */ int MPI_Request_free(MPI_Request *);
/* presents */ int MPI_Waitany(int, MPI_Request *, int *, MPI_Status *);
/* presents */ int MPI_Testany(int, MPI_Request *, int *, int *, MPI_Status *);
/* presents */ int MPI_Waitall(int, MPI_Request *, MPI_Status *);
/* presents */ int MPI_Testall(int, MPI_Request *, int *, MPI_Status *);
/* presents */ int MPI_Waitsome(int, MPI_Request *, int *, int *, MPI_Status *);
/* presents */ int MPI_Testsome(int, MPI_Request *, int *, int *, MPI_Status *);
/* presents */ int MPI_Iprobe(int, int, MPI_Comm, int *, MPI_Status *);
/* presents */ int MPI_Probe(int, int, MPI_Comm, MPI_Status *);
int MPI_Cancel(MPI_Request *);
int MPI_Test_cancelled(MPI_Status *, int *);
/* presents */ int MPI_Send_init(void*, int, MPI_Datatype, int, int, MPI_Comm, MPI_Request *);
int MPI_Bsend_init(void*, int, MPI_Datatype, int,int, MPI_Comm, MPI_Request *);
int MPI_Ssend_init(void*, int, MPI_Datatype, int,int, MPI_Comm, MPI_Request *);
int MPI_Rsend_init(void*, int, MPI_Datatype, int,int, MPI_Comm, MPI_Request *);
/* presents */ int MPI_Recv_init(void*, int, MPI_Datatype, int,int, MPI_Comm, MPI_Request *);
/* presents */ int MPI_Start(MPI_Request *);
/* presents */ int MPI_Startall(int, MPI_Request *);
/* presents */ int MPI_Sendrecv(void *, int, MPI_Datatype,int, int, void *, int, MPI_Datatype, int, int, MPI_Comm, MPI_Status *);
int MPI_Sendrecv_replace(void*, int, MPI_Datatype, int, int, int, int, MPI_Comm, MPI_Status *);
int MPI_Type_contiguous(int, MPI_Datatype, MPI_Datatype *);
int MPI_Type_vector(int, int, int, MPI_Datatype, MPI_Datatype *);
int MPI_Type_indexed(int, int *, int *, MPI_Datatype, MPI_Datatype *);
int MPI_Type_size(MPI_Datatype, int *);
int MPI_Type_commit(MPI_Datatype *);
int MPI_Type_free(MPI_Datatype *);
int MPI_Get_elements(MPI_Status *, MPI_Datatype, int *);
int MPI_Pack(void*, int, MPI_Datatype, void *, int, int *,  MPI_Comm);
int MPI_Unpack(void*, int, int *, void *, int, MPI_Datatype, MPI_Comm);
int MPI_Pack_size(int, MPI_Datatype, MPI_Comm, int *);
/* presents */ int MPI_Barrier(MPI_Comm );
/* presents */ int MPI_Bcast(void*, int, MPI_Datatype, int, MPI_Comm );
/* presents */ int MPI_Gather(void* , int, MPI_Datatype, void*, int, MPI_Datatype, int, MPI_Comm); 
/* presents */ int MPI_Gatherv(void* , int, MPI_Datatype, void*, int *, int *, MPI_Datatype, int, MPI_Comm); 
/* presents */ int MPI_Scatter(void* , int, MPI_Datatype, void*, int, MPI_Datatype, int, MPI_Comm);
/* presents */ int MPI_Scatterv(void* , int *, int *,  MPI_Datatype, void*, int, MPI_Datatype, int, MPI_Comm);
/* presents */ int MPI_Allgather(void* , int, MPI_Datatype, void*, int, MPI_Datatype, MPI_Comm);
/* presents */ int MPI_Allgatherv(void* , int, MPI_Datatype, void*, int *, int *, MPI_Datatype, MPI_Comm);
/* presents */ int MPI_Alltoall(void* , int, MPI_Datatype, void*, int, MPI_Datatype, MPI_Comm);
/* presents */ int MPI_Alltoallv(void* , int *, int *, MPI_Datatype, void*, int *, int *, MPI_Datatype, MPI_Comm);
/* presents */ int MPI_Reduce(void* , void*, int, MPI_Datatype, MPI_Op, int, MPI_Comm);
/* presents */ int MPI_Allreduce(void* , void*, int, MPI_Datatype, MPI_Op, MPI_Comm);
int MPI_Reduce_scatter(void* , void*, int *, MPI_Datatype, MPI_Op, MPI_Comm);
int MPI_Scan(void* , void*, int, MPI_Datatype, MPI_Op, MPI_Comm );
/* presents */ int MPI_Group_size(MPI_Group, int *);
/* presents */ int MPI_Group_rank(MPI_Group, int *);
int MPI_Group_translate_ranks (MPI_Group, int, int *, MPI_Group, int *);
int MPI_Group_compare(MPI_Group, MPI_Group, int *);
/* presents */ int MPI_Comm_group(MPI_Comm, MPI_Group *);
int MPI_Group_union(MPI_Group, MPI_Group, MPI_Group *);
int MPI_Group_intersection(MPI_Group, MPI_Group, MPI_Group *);
int MPI_Group_difference(MPI_Group, MPI_Group, MPI_Group *);
/* presents */ int MPI_Group_incl(MPI_Group, int, int *, MPI_Group *);
/* presents */ int MPI_Group_excl(MPI_Group, int, int *, MPI_Group *);
int MPI_Group_range_incl(MPI_Group, int, int [][3], MPI_Group *);
int MPI_Group_range_excl(MPI_Group, int, int [][3], MPI_Group *);
/* presents */ int MPI_Group_free(MPI_Group *);
/* presents */ int MPI_Comm_size(MPI_Comm, int *);
/* presents */ int MPI_Comm_rank(MPI_Comm, int *);
int MPI_Comm_compare(MPI_Comm, MPI_Comm, int *);
int MPI_Comm_dup(MPI_Comm, MPI_Comm *);
/* presents */ int MPI_Comm_create(MPI_Comm, MPI_Group, MPI_Comm *);
int MPI_Comm_split(MPI_Comm, int, int, MPI_Comm *);
/* presents */ int MPI_Comm_free(MPI_Comm *);
int MPI_Comm_test_inter(MPI_Comm, int *);
int MPI_Comm_remote_size(MPI_Comm, int *);
int MPI_Comm_remote_group(MPI_Comm, MPI_Group *);
int MPI_Intercomm_create(MPI_Comm, int, MPI_Comm, int, int, MPI_Comm * );
int MPI_Intercomm_merge(MPI_Comm, int, MPI_Comm *);
int MPI_Attr_put(MPI_Comm, int, void*);
int MPI_Attr_get(MPI_Comm, int, void *, int *);
int MPI_Attr_delete(MPI_Comm, int);
int MPI_Topo_test(MPI_Comm, int *);
int MPI_Cart_create(MPI_Comm, int, int *, int *, int, MPI_Comm *);
int MPI_Dims_create(int, int, int *);
int MPI_Graph_create(MPI_Comm, int, int *, int *, int, MPI_Comm *);
int MPI_Graphdims_get(MPI_Comm, int *, int *);
int MPI_Graph_get(MPI_Comm, int, int, int *, int *);
int MPI_Cartdim_get(MPI_Comm, int *);
int MPI_Cart_get(MPI_Comm, int, int *, int *, int *);
int MPI_Cart_rank(MPI_Comm, int *, int *);
int MPI_Cart_coords(MPI_Comm, int, int, int *);
int MPI_Graph_neighbors_count(MPI_Comm, int, int *);
int MPI_Graph_neighbors(MPI_Comm, int, int, int *);
int MPI_Cart_shift(MPI_Comm, int, int, int *, int *);
int MPI_Cart_sub(MPI_Comm, int *, MPI_Comm *);
int MPI_Cart_map(MPI_Comm, int, int *, int *, int *);
int MPI_Graph_map(MPI_Comm, int, int *, int *, int *);
/* presents */ int MPI_Get_processor_name(char *, int *);
int MPI_Get_version(int *, int *);
int MPI_Error_string(int, char *, int *);
int MPI_Error_class(int, int *);
/* presents */ double MPI_Wtime(void);
/* presents */ double MPI_Wtick(void);
/* presents */ int MPI_Init(int *, char ***);
/* presents */ int MPI_Finalize(void);
int MPI_Initialized(int *);
/* presents */ int MPI_Abort(MPI_Comm, int);

/* presents */ int MPI_Accumulate(void *, int, MPI_Datatype, int, MPI_Aint, int, 
		   MPI_Datatype,  MPI_Op, MPI_Win);
/* presents */ int MPI_Get(void *, int, MPI_Datatype, int, MPI_Aint, int, MPI_Datatype, 
	    MPI_Win);
/* presents */ int MPI_Put(void *, int, MPI_Datatype, int, MPI_Aint, int, MPI_Datatype, 
	    MPI_Win);
int MPI_Win_complete(MPI_Win);
/* presents */ int MPI_Win_create(void *, MPI_Aint, int, MPI_Info, MPI_Comm, MPI_Win *);
/* presents */ int MPI_Win_fence(int, MPI_Win);
/* presents */ int MPI_Win_free(MPI_Win *);
int MPI_Win_get_group(MPI_Win, MPI_Group *);
/* presents */ int MPI_Win_lock(int, int, int, MPI_Win);
int MPI_Win_post(MPI_Group, int, MPI_Win);
int MPI_Win_start(MPI_Group, int, MPI_Win);
int MPI_Win_test(MPI_Win, int *);
/* presents */ int MPI_Win_unlock(int, MPI_Win);
int MPI_Win_wait(MPI_Win);
 
int __Wait(int HowMany, int N, MPI_Request * Requests);

int MPI_Request_delete(MPI_Request * Request);

class cObject {
 public:
  __Request__ * queue;

  cObject() {
    queue = NULL;
  }
  bool Completed() {
    bool result = true;
    __Request__ * cur = queue;

    while (result && cur)
      if (cur->complete)
         cur = cur->next;
      else
         result = false;

    return result;
  }
  void Wait(int __id__) {
    __Request__ * cur = queue;

    while (cur)
      if (cur->complete)
         cur = cur->next;
      else
         __Wait(1, 1, &cur);
  }
  void add_queue(__Request__ * item) {
    if (queue == NULL)
       queue = item;
    else {
       __Request__ * cur = queue;
       while (cur->next)
         cur = cur->next;
       cur->next  = item;
       item->prev = cur;
    }
  }
  ~cObject() {
     while (queue) {
       __Request__ * then = queue->next;
       delete queue;
       queue = then;
     }
  }
};

class iObject: public cObject {
 public:
  funnel(in, char) * in;

  iObject(char * LINK): cObject() {
     in = new funnel(in, char)(LINK, __BUF_SIZE__*1024);
  }
  ~iObject() {
     delete in;
  }
};

class oObject: public cObject {
 public:
  funnel(out, char) * out;

  oObject(char * LINK) {
     out = new funnel(out, char)(LINK, __BUF_SIZE__*1024);
  }
  ~oObject() {
     delete out;
  }
};

typedef map<int, iObject *> i_funnels;
typedef map<int, oObject *> o_funnels;

namespace mpi {
  const int __sizes[MPI_UB+1] = { 1, sizeof(char), sizeof(signed char), sizeof(unsigned char), sizeof(unsigned char),
        sizeof(short), sizeof(unsigned short), sizeof(int), sizeof(unsigned int), sizeof(long),
        sizeof(unsigned long), sizeof(float), sizeof(double), sizeof(long double), sizeof(long long int),
        sizeof(unsigned long long), sizeof(long long), 1, 1, 1 };

  vector<i_funnels *> __inps[__NPROCS__];
  vector<o_funnels *> __outs[__NPROCS__];

  __Comm__ __world(__NPROCS__);

  __Group__ __empty = {0, NULL};

  plan_lock_t __iolock__;
  plan_lock_t __comm_lock__;
  plan_lock_t __group_lock__;
  plan_lock_t __win_lock__;

  void *       __bufs[__NPROCS__];
  void *       __rbufs[__NPROCS__];
  int          __items[__NPROCS__];
  int          __dsizes[__NPROCS__];
  int *        p__items[__NPROCS__];
  MPI_Datatype __types[__NPROCS__];
  int          __roots[__NPROCS__];
  MPI_Op       __ops[__NPROCS__];

  map<MPI_Comm, __Comm__ *> __comms;
  map<MPI_Group, __Group__ *> __groups;
  map<MPI_Request, __Request__ *> __requests;
  map<MPI_Win, __Win__ *> __wins;
}

using namespace mpi;

iObject * iGetOrCreate(bool lock, int Rank, int Tag) {
  if (lock) plan_set_lock(&__iolock__);
  iObject * f = (*__inps[__id__][Rank])[Tag];
  if (f == NULL) {
     char LINK[128];
     sprintf(LINK,"%i_%i_%i", Rank, __id__, Tag);
     f = new iObject(LINK);
     (*__inps[__id__][Rank])[Tag] = f;
  }
  if (lock) plan_unset_lock(&__iolock__);
  return f;
}

oObject * oGetOrCreate(bool lock, int Rank, int Tag) {
  if (lock) plan_set_lock(&__iolock__);
  oObject * f = (*__outs[__id__][Rank])[Tag];
  if (f == NULL) {
     char LINK[128];
     sprintf(LINK,"%i_%i_%i", __id__, Rank, Tag);
     f = new oObject(LINK);
     (*__outs[__id__][Rank])[Tag] = f;
  }
  if (lock) plan_unset_lock(&__iolock__);
  return f;
}

void ioConnecting() {
  plan_set_lock(&__iolock__);
  for (int i = 0; i < __NPROCS__; i++) {
      i_funnels * inp = __inps[i][__id__];
      o_funnels * out = __outs[__id__][i];
      i_funnels::iterator iinp;
      for (iinp = inp->begin(); iinp != inp->end(); iinp++)
          if (out->find(iinp->first) == out->end())
             oGetOrCreate(false, i, iinp->first); 
  }
  for (int i = 0; i < __NPROCS__; i++) {
      i_funnels * inp = __inps[__id__][i];
      o_funnels * out = __outs[i][__id__];
      o_funnels::iterator iout;
      for (iout = out->begin(); iout != out->end(); iout++)
          if (inp->find(iout->first) == inp->end())
             iGetOrCreate(false, i, iout->first); 
  }
  plan_unset_lock(&__iolock__);
}

void ioPromoteAsyncs() {
  for (int i = 0; i < __NPROCS__; i++) {
      i_funnels * inp = __inps[__id__][i];
      i_funnels::iterator iinp;
      for (iinp = inp->begin(); iinp != inp->end(); iinp++) {
          iObject * fi = iinp->second;
          __Request__ * cur = fi->queue;
          while (cur && cur->complete)
            cur = cur->next;
          if (cur && fi->in->ready() && !fi->in->empty()) {
             fi->in->get(cur->buf, cur->items*__sizes[cur->type]);
             cur->complete = true;
          }
      }
  }
  for (int i = 0; i < __NPROCS__; i++) {
      o_funnels * out = __outs[__id__][i];
      o_funnels::iterator iout;
      for (iout = out->begin(); iout != out->end(); iout++) {
          oObject * fo = iout->second;
          __Request__ * cur = fo->queue;
          while (cur && cur->complete)
            cur = cur->next;
          if (cur && fo->out->ready() && fo->out->empty()) {
             fo->out->put(cur->buf, cur->items*__sizes[cur->type]);
             cur->complete = true;
          }
      }
  }
}

#define makeOp(Type, a1, a2) \
  switch(Op) { \
   case MPI_MAX: a1 = max(a1, a2); break; \
   case MPI_MIN: a1 = min(a1, a2); break; \
   case MPI_SUM: a1 += a2; break; \
   case MPI_PROD: a1 *= a2; break; \
   case MPI_LAND: a1 = static_cast<Type>((a1 != (Type)0) && (a2 != (Type)0)); break; \
   case MPI_BAND: a1 = static_cast<Type>((long long)a1 & (long long)a2); break; \
   case MPI_LOR: a1 = static_cast<Type>((a1 != (Type)0) || (a2 != (Type)0)); break; \
   case MPI_BOR: a1 = static_cast<Type>((long long)a1 | (long long)a2); break; \
   case MPI_LXOR: a1 = static_cast<Type>((a1 != (Type)0) ^ (a2 != (Type)0)); break; \
   case MPI_BXOR: a1 = static_cast<Type>((long long)a1 ^ (long long)a2); break; \
   case MPI_REPLACE: a1 = a2; break; \
  }

void applyOp(char * recv_item, char * second_item, MPI_Datatype Type, MPI_Op Op) {
  switch (Type) {
   case MPI_CHAR: {
         char & a1 = *reinterpret_cast<char *>(recv_item);
         char & a2 = *reinterpret_cast<char *>(second_item);
         makeOp(char, a1, a2);
         break;
   }      
   case MPI_SIGNED_CHAR: {   
         signed char & a1 = *reinterpret_cast<signed char *>(recv_item);
         signed char & a2 = *reinterpret_cast<signed char *>(second_item);
         makeOp(signed char, a1, a2);
         break;
   }      
   case MPI_UNSIGNED_CHAR: { 
         unsigned char & a1 = *reinterpret_cast<unsigned char *>(recv_item);
         unsigned char & a2 = *reinterpret_cast<unsigned char *>(second_item);
         makeOp(unsigned char, a1, a2);
         break;
   }      
   case MPI_BYTE: {          
         unsigned char & a1 = *reinterpret_cast<unsigned char *>(recv_item);
         unsigned char & a2 = *reinterpret_cast<unsigned char *>(second_item);
         makeOp(unsigned char, a1, a2);
         break;
   }      
   case MPI_SHORT: {         
         short & a1 = *reinterpret_cast<short *>(recv_item);
         short & a2 = *reinterpret_cast<short *>(second_item);
         makeOp(short, a1, a2);
         break;
   }      
   case MPI_UNSIGNED_SHORT: {
         unsigned short & a1 = *reinterpret_cast<unsigned short *>(recv_item);
         unsigned short & a2 = *reinterpret_cast<unsigned short *>(second_item);
         makeOp(unsigned short, a1, a2);
         break;
   }      
   case MPI_INT: {           
         int & a1 = *reinterpret_cast<int *>(recv_item);
         int & a2 = *reinterpret_cast<int *>(second_item);
         makeOp(int, a1, a2);
         break;
   }      
   case MPI_UNSIGNED: {      
         unsigned int & a1 = *reinterpret_cast<unsigned int *>(recv_item);
         unsigned int & a2 = *reinterpret_cast<unsigned int *>(second_item);
         makeOp(unsigned int, a1, a2);
         break;
   }      
   case MPI_LONG: {          
         long & a1 = *reinterpret_cast<long *>(recv_item);
         long & a2 = *reinterpret_cast<long *>(second_item);
         makeOp(long, a1, a2);
         break;
   }      
   case MPI_UNSIGNED_LONG: { 
         unsigned long & a1 = *reinterpret_cast<unsigned long *>(recv_item);
         unsigned long & a2 = *reinterpret_cast<unsigned long *>(second_item);
         makeOp(unsigned long, a1, a2);
         break;
   }      
   case MPI_FLOAT: {         
         float & a1 = *reinterpret_cast<float *>(recv_item);
         float & a2 = *reinterpret_cast<float *>(second_item);
         makeOp(float, a1, a2);
         break;
   }      
   case MPI_DOUBLE: {        
         double & a1 = *reinterpret_cast<double *>(recv_item);
         double & a2 = *reinterpret_cast<double *>(second_item);
         makeOp(double, a1, a2);
         break;
   }      
   case MPI_LONG_DOUBLE: {  
         long double & a1 = *reinterpret_cast<long double *>(recv_item);
         long double & a2 = *reinterpret_cast<long double *>(second_item);
         makeOp(long double, a1, a2);
         break;
   }      
   case MPI_LONG_LONG_INT: { 
         long long int & a1 = *reinterpret_cast<long long int *>(recv_item);
         long long int & a2 = *reinterpret_cast<long long int *>(second_item);
         makeOp(long long int, a1, a2);
         break;
   }      
   case MPI_UNSIGNED_LONG_LONG: {
         unsigned long long & a1 = *reinterpret_cast<unsigned long long *>(recv_item);
         unsigned long long & a2 = *reinterpret_cast<unsigned long long *>(second_item);
         makeOp(unsigned long long, a1, a2);
         break;
   }      
   case MPI_LONG_LONG: {
         long long & a1 = *reinterpret_cast<long long *>(recv_item);
         long long & a2 = *reinterpret_cast<long long *>(second_item);
         makeOp(long long, a1, a2);
         break;
   }      
  }
}

void __Barrier(__Comm__ * comm) {
  plan_set_lock(&comm->barrier1);
  comm->barN++;
  if (comm->barN == comm->size)
     comm->barFlag = true;
  plan_unset_lock(&comm->barrier1);

  plan_set_lock(&comm->barrier2);
  while (!comm->barFlag)
    _Yield();
  comm->barN--;
  if (comm->barN == 0)
     comm->barFlag = false;
  plan_unset_lock(&comm->barrier2);

  while (comm->barFlag)
    _Yield();
}

int MPI_Get(void * Buf, int Items, MPI_Datatype Type, int Rank, MPI_Aint tDisp, int tItems, MPI_Datatype tType, MPI_Win Win) {
  plan_set_lock(&__win_lock__);
  __Win__ * win;
  if (Win == MPI_WIN_NULL) {
     plan_unset_lock(&__win_lock__);
     return MPI_SUCCESS;
  } else
     win = __wins[Win];
  plan_unset_lock(&__win_lock__);
  if (win == NULL) {
     return MPI_ERR_WIN;
  }
  if (Buf == NULL && Items != 0)
     return MPI_ERR_BUFFER;
  if (Type < 0 || Type > MPI_UB || tType != Type)
     return MPI_ERR_TYPE;
  if (Items < 0 || tItems != Items)
     return MPI_ERR_COUNT;
  if (tDisp < 0)
     return MPI_ERR_DISP;
  if (Rank < 0 || Rank >= win->comm->size)
     return MPI_ERR_RANK;

  int rid = win->comm->ranks[Rank];

  memmove(Buf, win->bases[rid]+tDisp*win->disp_unit_sizes[rid], Items*__sizes[Type]);

  ioConnecting();
  ioPromoteAsyncs();

  return MPI_SUCCESS;
}

int MPI_Put(void * Buf, int Items, MPI_Datatype Type, int Rank, MPI_Aint tDisp, int tItems, MPI_Datatype tType, MPI_Win Win) {
  plan_set_lock(&__win_lock__);
  __Win__ * win;
  if (Win == MPI_WIN_NULL) {
     plan_unset_lock(&__win_lock__);
     return MPI_SUCCESS;
  } else
     win = __wins[Win];
  plan_unset_lock(&__win_lock__);
  if (win == NULL) {
     return MPI_ERR_WIN;
  }
  if (Buf == NULL && Items != 0)
     return MPI_ERR_BUFFER;
  if (Type < 0 || Type > MPI_UB || tType != Type)
     return MPI_ERR_TYPE;
  if (Items < 0 || tItems != Items)
     return MPI_ERR_COUNT;
  if (tDisp < 0)
     return MPI_ERR_DISP;
  if (Rank < 0 || Rank >= win->comm->size)
     return MPI_ERR_RANK;

  int rid = win->comm->ranks[Rank];

  memmove(win->bases[rid]+tDisp*win->disp_unit_sizes[rid], Buf, Items*__sizes[Type]);

  ioConnecting();
  ioPromoteAsyncs();

  return MPI_SUCCESS;
}

int MPI_Accumulate(void * Buf, int Items, MPI_Datatype Type, int Rank, MPI_Aint tDisp, int tItems,
                   MPI_Datatype tType, MPI_Op Op, MPI_Win Win) {
  plan_set_lock(&__win_lock__);
  __Win__ * win;
  if (Win == MPI_WIN_NULL) {
     plan_unset_lock(&__win_lock__);
     return MPI_SUCCESS;
  } else
     win = __wins[Win];
  plan_unset_lock(&__win_lock__);
  if (win == NULL) {
     return MPI_ERR_WIN;
  }
  if (Buf == NULL && Items != 0)
     return MPI_ERR_BUFFER;
  if (Type < 0 || Type > MPI_UB || tType != Type)
     return MPI_ERR_TYPE;
  if (Items < 0 || tItems != Items)
     return MPI_ERR_COUNT;
  if (tDisp < 0)
     return MPI_ERR_DISP;
  if (Rank < 0 || Rank >= win->comm->size)
     return MPI_ERR_RANK;
  if (Op < 0 || Op > MPI_REPLACE)
     return MPI_ERR_OP;

  int rid = win->comm->ranks[Rank];

  for (int j = 0; j < Items; j++)
      applyOp(win->bases[rid]+tDisp*win->disp_unit_sizes[rid], (char *)Buf+j*__sizes[Type], Type, Op);

  ioConnecting();
  ioPromoteAsyncs();

  return MPI_SUCCESS;
}

int MPI_Win_create(void * Base, MPI_Aint Size, int DispUnit, MPI_Info Info, MPI_Comm Comm, MPI_Win * Win) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if (Base == NULL && Size != 0)
     return MPI_ERR_BUFFER;
  if (Size < 0)
     return MPI_ERR_SIZE;
  if (DispUnit <= 0)
     return MPI_ERR_DISP;
  if (Info != MPI_INFO_NULL)
     return MPI_ERR_INFO;

  __bufs[__id__]  = Base;
  __items[__id__] = Size;
  __dsizes[__id__] = DispUnit;
  __Barrier(comm);
  if (__id__ == comm->ranks[0]) {
     plan_set_lock(&__win_lock__);
     *Win = new __Win__(comm);
     // Fill ranks
     __wins[*Win] = *Win;
     for (int i = 0; i < comm->size; i++) {
         int loc_id = comm->ranks[i];
         (*Win)->bases[loc_id] = (char *) __bufs[loc_id];
         (*Win)->sizes[loc_id] = __items[loc_id];
         (*Win)->disp_unit_sizes[loc_id] = __dsizes[loc_id];
     }
     plan_unset_lock(&__win_lock__);
     __bufs[__id__] = *Win;
  }
  __Barrier(comm);
  *Win = (MPI_Win) __bufs[comm->ranks[0]];
   plan_set_lock(&__win_lock__);
   (*Win)->refs++;
   plan_unset_lock(&__win_lock__);
  __Barrier(comm);

  ioConnecting();
  ioPromoteAsyncs();

  return MPI_SUCCESS;
}

int MPI_Win_free(MPI_Win * Win) {
  plan_set_lock(&__win_lock__);
  __Win__ * win;
  if (*Win == MPI_WIN_NULL) {
     plan_unset_lock(&__win_lock__);
     return MPI_SUCCESS;
  } else
     win = __wins[*Win];
  plan_unset_lock(&__win_lock__);
  if (win == NULL) {
     return MPI_ERR_WIN;
  }
  __Comm__ * comm = win->comm;
  int root = comm->ranks[0];
  win->_barrier();
  plan_set_lock(&__win_lock__);
  win->refs--;
  if (win->refs <= 0) {
     delete win;
     map<MPI_Win, __Win__ *>::iterator it = __wins.find(*Win);
     __wins.erase(it);
  }
  plan_unset_lock(&__win_lock__);
  *Win = MPI_WIN_NULL;
  __Barrier(comm);

  ioConnecting();
  ioPromoteAsyncs();

  return MPI_SUCCESS;
}

int MPI_Win_fence(int Assert, MPI_Win Win) {
  plan_set_lock(&__win_lock__);
  __Win__ * win;
  if (Win == MPI_WIN_NULL) {
     plan_unset_lock(&__win_lock__);
     return MPI_SUCCESS;
  } else
     win = __wins[Win];
  plan_unset_lock(&__win_lock__);
  if (win == NULL) {
     return MPI_ERR_WIN;
  }
  __Barrier(win->comm);

  ioConnecting();
  ioPromoteAsyncs();

  return MPI_SUCCESS;
}

int MPI_Win_lock(int LockType, int Rank, int Assert, MPI_Win Win) {
  plan_set_lock(&__win_lock__);
  __Win__ * win;
  if (Win == MPI_WIN_NULL) {
     plan_unset_lock(&__win_lock__);
     return MPI_SUCCESS;
  } else
     win = __wins[Win];
  plan_unset_lock(&__win_lock__);
  if (win == NULL) {
     return MPI_ERR_WIN;
  }
  if (LockType != MPI_LOCK_SHARED && LockType != MPI_LOCK_EXCLUSIVE)
     return MPI_ERR_ARG;
  if (Rank < 0 || Rank >= win->comm->size)
     return MPI_ERR_RANK;

  ioConnecting();
  ioPromoteAsyncs();

  int rid = win->comm->ranks[Rank];

  if (win->locks[rid][__id__] != 0)
     return MPI_ERR_OTHER;
  plan_set_lock(&win->exclusive_lock[rid]);
  if (LockType == MPI_LOCK_SHARED) {
     win->locks[rid][__id__] = MPI_LOCK_SHARED;
     plan_unset_lock(&win->exclusive_lock[rid]);
  } else {
     int locked;
     do {
        locked = 0;
        for (int i = 0; !locked && i < win->comm->size; i++)
            if (win->locks[rid][win->comm->ranks[i]])
               locked = 1;
        if (locked) {
           plan_unset_lock(&win->exclusive_lock[rid]);
           _Yield();
           plan_set_lock(&win->exclusive_lock[rid]);
        }
     } while (locked != 0);
     win->locks[rid][__id__] = MPI_LOCK_EXCLUSIVE;
  }

  return MPI_SUCCESS;
}

int MPI_Win_unlock(int Rank, MPI_Win Win) {
  plan_set_lock(&__win_lock__);
  __Win__ * win;
  if (Win == MPI_WIN_NULL) {
     plan_unset_lock(&__win_lock__);
     return MPI_SUCCESS;
  } else
     win = __wins[Win];
  plan_unset_lock(&__win_lock__);
  if (win == NULL) {
     return MPI_ERR_WIN;
  }
  if (Rank < 0 || Rank >= win->comm->size)
     return MPI_ERR_RANK;

  ioConnecting();
  ioPromoteAsyncs();

  int rid = win->comm->ranks[Rank];

  if (win->locks[rid][__id__] == 0)
     return MPI_ERR_OTHER;
  if (win->locks[rid][__id__] == MPI_LOCK_SHARED) {
     plan_set_lock(&win->exclusive_lock[rid]);
  }
  win->locks[rid][__id__] = 0;
  plan_unset_lock(&win->exclusive_lock[rid]);

  return MPI_SUCCESS;
}

int MPI_Init(int *, char ***) {
  __inps[__id__].resize(__NPROCS__);
  __outs[__id__].resize(__NPROCS__);
  for (int i = 0; i < __NPROCS__; i++) {
      __inps[__id__][i] = new i_funnels();
      __outs[__id__][i] = new o_funnels();
  }
  if (__id__ == 0) {
     plan_init_lock(&__iolock__);
     plan_init_lock(&__comm_lock__);
     plan_init_lock(&__group_lock__);
     plan_init_lock(&__win_lock__);
     for (int i = 0; i < __NPROCS__; i++)
         __world.ranks[i] = i;
     __comms[MPI_COMM_WORLD] = &__world;
     __groups[MPI_GROUP_EMPTY] = &__empty;
  }
  MPI_Barrier(MPI_COMM_WORLD); 
  return MPI_SUCCESS;
}

int MPI_Comm_size(MPI_Comm Comm, int * psize) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  ioConnecting();
  ioPromoteAsyncs();
  *psize = comm->size;
  return MPI_SUCCESS;
}

int MPI_Comm_rank(MPI_Comm Comm, int * prank) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  for (int i = 0; i < comm->size; i++)
      if (comm->ranks[i] == __id__) {
         *prank = i;
         return MPI_SUCCESS;
      }
  ioConnecting();
  ioPromoteAsyncs();
  *prank = MPI_UNDEFINED;
  return MPI_SUCCESS;
}

int __TranslateRank(__Comm__ * comm, int id) {
  for (int i = 0; i < comm->size; i++)
      if (comm->ranks[i] == id)
         return i;
  return MPI_UNDEFINED;
}

double MPI_Wtime(void) {
  return omp_get_wtime();
}

double MPI_Wtick(void) {
  return omp_get_wtick();
}

int MPI_Send(void * Buf, int Items, MPI_Datatype Type, int Rank, int Tag, MPI_Comm Comm) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if (Buf == NULL && Items != 0)
     return MPI_ERR_BUFFER;
  if (Type < 0 || Type > MPI_UB)
     return MPI_ERR_TYPE;
  if (Items < 0)
     return MPI_ERR_COUNT;
  if (Tag < 0)
     return MPI_ERR_TAG;
  if (Rank < 0 || Rank >= comm->size)
     return MPI_ERR_RANK;
  Rank = comm->ranks[Rank];
  ioConnecting();
  ioPromoteAsyncs();
  oObject * f = oGetOrCreate(true, Rank, Tag);
  f->Wait(__id__);
  f->out->put(Buf, Items*__sizes[Type]);
  return MPI_SUCCESS;
}

int MPI_Ssend(void * Buf, int Items, MPI_Datatype Type, int Rank, int Tag, MPI_Comm Comm) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if (Buf == NULL && Items != 0)
     return MPI_ERR_BUFFER;
  if (Type < 0 || Type > MPI_UB)
     return MPI_ERR_TYPE;
  if (Items < 0)
     return MPI_ERR_COUNT;
  if (Tag < 0)
     return MPI_ERR_TAG;
  if (Rank < 0 || Rank >= comm->size)
     return MPI_ERR_RANK;
  Rank = comm->ranks[Rank];
  ioConnecting();
  ioPromoteAsyncs();
  oObject * f = oGetOrCreate(true, Rank, Tag);
  f->Wait(__id__);
  f->out->put(Buf, Items*__sizes[Type]);
  while (!f->out->empty())
    _Yield();
  return MPI_SUCCESS;
}

void iCheckAnySourceTag(__Comm__ * comm, int &Rank, int &Tag, bool Wait) {
  ioConnecting();
  if (Rank == MPI_ANY_SOURCE && Tag == MPI_ANY_TAG) {
     do {
        for (int i = 0; Tag == MPI_ANY_TAG && i < comm->size; i++) {
            i_funnels * inp = __inps[__id__][comm->ranks[i]];
            i_funnels::iterator iinp;
            for (iinp = inp->begin(); Tag == MPI_ANY_TAG && iinp != inp->end(); iinp++) {
                iObject * f = iGetOrCreate(true, comm->ranks[i], iinp->first);
                if (f->Completed() && !f->in->empty()) {
                   Rank = comm->ranks[i];
                   Tag  = iinp->first;
                }
            }
        }
        ioConnecting();
     } while (Tag == MPI_ANY_TAG && Wait);
  } else if (Tag == MPI_ANY_TAG) {
     i_funnels * inp = __inps[__id__][Rank];
     i_funnels::iterator iinp;
     do {
        for (iinp = inp->begin(); Tag == MPI_ANY_TAG && iinp != inp->end(); iinp++) {
            iObject * f = iGetOrCreate(true, Rank, iinp->first);
            if (f->Completed() && !f->in->empty())
               Tag = iinp->first;
        }
        ioConnecting();
     } while (Tag == MPI_ANY_TAG && Wait);
  } else if (Rank == MPI_ANY_SOURCE) {
     do {
        for (int i = 0; Rank == MPI_ANY_SOURCE && i < comm->size; i++) {
            iObject * f = iGetOrCreate(true, comm->ranks[i], Tag);
            if (f->Completed() && !f->in->empty())
               Rank = comm->ranks[i];
        }
     } while (Rank == MPI_ANY_SOURCE && Wait);
  }
}

int MPI_Recv(void * Buf, int Items, MPI_Datatype Type, int Rank, int Tag, MPI_Comm Comm, MPI_Status * Status) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if (Buf == NULL && Items != 0)
     return MPI_ERR_BUFFER;
  if (Type < 0 || Type > MPI_UB)
     return MPI_ERR_TYPE;
  if (Items < 0)
     return MPI_ERR_COUNT;
  if (Tag < 0 && Tag != MPI_ANY_TAG)
     return MPI_ERR_TAG;
  if (Rank < 0 && Rank != MPI_ANY_SOURCE || Rank >= comm->size)
     return MPI_ERR_RANK;
  if (Rank != MPI_ANY_SOURCE)
     Rank = comm->ranks[Rank];
  iCheckAnySourceTag(comm, Rank, Tag, true);
  ioPromoteAsyncs();
  iObject * f = iGetOrCreate(true, Rank, Tag);
  f->Wait(__id__);
  f->in->get(Buf, Items*__sizes[Type]);
  if (Status != MPI_STATUS_IGNORE) {
     Status->count      = Items;
     Status->cancelled  = 0;
     Status->MPI_SOURCE = __TranslateRank(comm, Rank);
     Status->MPI_TAG    = Tag;
     Status->MPI_ERROR  = MPI_SUCCESS;
  }
  return MPI_SUCCESS;
}

int MPI_Sendrecv(void * SendBuf, int SendItems, MPI_Datatype SendType, int DestRank, int SendTag,
                 void * RecvBuf, int RecvItems, MPI_Datatype RecvType, int RecvRank, int RecvTag,
                 MPI_Comm Comm, MPI_Status * Status) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if (SendBuf == NULL && SendItems != 0)
     return MPI_ERR_BUFFER;
  if (SendType < 0 || SendType > MPI_UB)
     return MPI_ERR_TYPE;
  if (SendItems < 0)
     return MPI_ERR_COUNT;
  if (SendTag < 0)
     return MPI_ERR_TAG;
  if (DestRank < 0 || DestRank >= comm->size)
     return MPI_ERR_RANK;

  DestRank = comm->ranks[DestRank];

  if (RecvBuf == NULL && RecvItems != 0)
     return MPI_ERR_BUFFER;
  if (RecvType < 0 || RecvType > MPI_UB)
     return MPI_ERR_TYPE;
  if (RecvItems < 0)
     return MPI_ERR_COUNT;
  if (RecvTag < 0 && RecvTag != MPI_ANY_TAG)
     return MPI_ERR_TAG;
  if (RecvRank < 0 && RecvRank != MPI_ANY_SOURCE || RecvRank >= comm->size)
     return MPI_ERR_RANK;
  if (RecvRank != MPI_ANY_SOURCE)
     RecvRank = comm->ranks[RecvRank];

  oObject * fo = oGetOrCreate(true, DestRank, SendTag);

  iCheckAnySourceTag(comm, RecvRank, RecvTag, true);

  iObject * fi = iGetOrCreate(true, RecvRank, RecvTag);

  MPI_Request Requests[2] = { MPI_REQUEST_NULL, MPI_REQUEST_NULL };
  MPI_Status  Statuses[2];
  bool requesting = false;

  __Request__ * req = fi->queue;
  while (req) {
    if (!req->complete) {
       Requests[0] = req;
       requesting = true;
    }
    req = req->next;
  }
  req = fo->queue;
  while (req) {
    if (!req->complete) {
       Requests[1] = req;
       requesting = true;
    }
    req = req->next;
  }
  if (requesting)
     MPI_Waitall(2, Requests, Statuses);

  while (!fi->in->ready() || !fo->out->ready())
    _Yield();

  bool sent     = false;
  bool received = false;

  while (!sent || !received) {
    if (!sent && fo->out->empty()) {
       fo->out->put(SendBuf, SendItems*__sizes[SendType]);
       sent = true;
    }
    if (!received && !fi->in->empty()) {
       fi->in->get(RecvBuf, RecvItems*__sizes[RecvType]);
       received = true;
    }
  }

  if (Status != MPI_STATUS_IGNORE) {
     Status->count      = RecvItems;
     Status->cancelled  = 0;
     Status->MPI_SOURCE = __TranslateRank(comm, RecvRank);
     Status->MPI_TAG    = RecvTag;
     Status->MPI_ERROR  = MPI_SUCCESS;
  }

  return MPI_SUCCESS;
}

int MPI_Probe(int Rank, int Tag, MPI_Comm Comm, MPI_Status * Status) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if (Tag < 0 && Tag != MPI_ANY_TAG)
     return MPI_ERR_TAG;
  if (Rank < 0 && Rank != MPI_ANY_SOURCE || Rank >= comm->size)
     return MPI_ERR_RANK;
  if (Rank != MPI_ANY_SOURCE)
     Rank = comm->ranks[Rank];
  iCheckAnySourceTag(comm, Rank, Tag, true);
  ioPromoteAsyncs();
  iObject * f = iGetOrCreate(true, Rank, Tag);
  f->Wait(__id__);
  while (f->in->empty())
    _Yield();
  if (Status != MPI_STATUS_IGNORE) {
     Status->count      = -1;
     Status->cancelled  = 0;
     Status->MPI_SOURCE = __TranslateRank(comm, Rank);
     Status->MPI_TAG    = Tag;
     Status->MPI_ERROR  = MPI_SUCCESS;
  }
  return MPI_SUCCESS;
}

int MPI_Iprobe(int Rank, int Tag, MPI_Comm Comm, int * present, MPI_Status * Status) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if (Tag < 0 && Tag != MPI_ANY_TAG)
     return MPI_ERR_TAG;
  if (Rank < 0 && Rank != MPI_ANY_SOURCE || Rank >= comm->size)
     return MPI_ERR_RANK;
  if (Rank != MPI_ANY_SOURCE)
     Rank = comm->ranks[Rank];
  iCheckAnySourceTag(comm, Rank, Tag, false);
  ioPromoteAsyncs();
  if (Rank == MPI_ANY_SOURCE) {
     *present = 0;
     return MPI_SUCCESS;
  }
  iObject * f = iGetOrCreate(true, Rank, Tag);
  *present = f->Completed() && !f->in->empty();
  if (*present && Status != MPI_STATUS_IGNORE) {
     Status->count      = -1;
     Status->cancelled  = 0;
     Status->MPI_SOURCE = __TranslateRank(comm, Rank);
     Status->MPI_TAG    = Tag;
     Status->MPI_ERROR  = MPI_SUCCESS;
  }
  return MPI_SUCCESS;
}

int __Isend_create(bool Persistent, oObject * &f, void * Buf, int Items, MPI_Datatype Type, int Rank, int Tag, MPI_Comm Comm, MPI_Request * Request) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if (Buf == NULL && Items != 0)
     return MPI_ERR_BUFFER;
  if (Type < 0 || Type > MPI_UB)
     return MPI_ERR_TYPE;
  if (Items < 0)
     return MPI_ERR_COUNT;
  if (Tag < 0)
     return MPI_ERR_TAG;
  if (Rank < 0 || Rank >= comm->size)
     return MPI_ERR_RANK;

  ioConnecting();
  ioPromoteAsyncs();
  f = oGetOrCreate(true, comm->ranks[Rank], Tag);
  *Request = new oRequest(Rank, comm, Tag, Type, Items, Buf, Persistent);
  __requests[*Request] = *Request;
  
  return MPI_SUCCESS;
}

int MPI_Isend(void * Buf, int Items, MPI_Datatype Type, int Rank, int Tag, MPI_Comm Comm, MPI_Request * Request) {
  oObject * f;
  int result = __Isend_create(false, f, Buf, Items, Type, Rank, Tag, Comm, Request);
  if (result == MPI_SUCCESS)
     f->add_queue(reinterpret_cast<__Request__ *>(*Request));
  return result;
}

int __Irecv_create(bool Persistent, iObject * &f, void * Buf, int Items, MPI_Datatype Type, int Rank, int Tag, MPI_Comm Comm, MPI_Request * Request) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if (Buf == NULL && Items != 0)
     return MPI_ERR_BUFFER;
  if (Type < 0 || Type > MPI_UB)
     return MPI_ERR_TYPE;
  if (Items < 0)
     return MPI_ERR_COUNT;
  if (Tag < 0 && Tag != MPI_ANY_TAG)
     return MPI_ERR_TAG;
  if (Rank < 0 && Rank != MPI_ANY_SOURCE || Rank >= comm->size)
     return MPI_ERR_RANK;

  if (Persistent) {
     ioConnecting();
     f = NULL;
     *Request = new iRequest(Rank, comm, Tag, Type, Items, Buf, Persistent);
  } else if (Rank == MPI_ANY_SOURCE || Tag == MPI_ANY_TAG) {
     iCheckAnySourceTag(comm, Rank, Tag, true);
     f = iGetOrCreate(true, Rank, Tag);
     *Request = new iRequest(__TranslateRank(comm, Rank), comm, Tag, Type, Items, Buf, Persistent);
  } else {
     ioConnecting();
     f = iGetOrCreate(true, comm->ranks[Rank], Tag);
     *Request = new iRequest(Rank, comm, Tag, Type, Items, Buf, Persistent);
  }
  __requests[*Request] = *Request;
  ioPromoteAsyncs();

  return MPI_SUCCESS;
}

int MPI_Irecv(void * Buf, int Items, MPI_Datatype Type, int Rank, int Tag, MPI_Comm Comm, MPI_Request * Request) {
  iObject * f;
  int result = __Irecv_create(false, f, Buf, Items, Type, Rank, Tag, Comm, Request);
  if (result == MPI_SUCCESS)
     f->add_queue(reinterpret_cast<__Request__ *>(*Request));
  return result;
}

int MPI_Send_init(void * Buf, int Items, MPI_Datatype Type, int Rank, int Tag, MPI_Comm Comm, MPI_Request * Request) {
  oObject * f;
  return __Isend_create(true, f, Buf, Items, Type, Rank, Tag, Comm, Request);
}

int MPI_Recv_init(void * Buf, int Items, MPI_Datatype Type, int Rank, int Tag, MPI_Comm Comm, MPI_Request * Request) {
  iObject * f;
  return __Irecv_create(true, f, Buf, Items, Type, Rank, Tag, Comm, Request);
}

int MPI_Start(MPI_Request * Request) {
  return MPI_Startall(1, Request);
}

int MPI_Startall(int N, MPI_Request * Requests) {
  for (int i = 0; i < N; i++)
      if (Requests[i] == MPI_REQUEST_NULL || __requests.find(Requests[i]) == __requests.end() || !Requests[i]->persistent)
         return MPI_ERR_REQUEST;
  for (int i = 0; i < N; i++) {
      Requests[i]->complete = false;
      if (Requests[i]->receiving) {
         if (Requests[i]->any_tag || Requests[i]->any_source) {
            if (Requests[i]->any_tag) Requests[i]->tag = MPI_ANY_TAG;
            if (Requests[i]->any_source) Requests[i]->rank = MPI_ANY_SOURCE;
            iCheckAnySourceTag(Requests[i]->comm, Requests[i]->rank, Requests[i]->tag, true);
            Requests[i]->rank = __TranslateRank(Requests[i]->comm, Requests[i]->rank);
         }
         iObject * fi = iGetOrCreate(true, Requests[i]->comm->ranks[Requests[i]->rank], Requests[i]->tag);
         fi->add_queue(reinterpret_cast<__Request__ *>(Requests[i]));
      } else {
         oObject * fo = oGetOrCreate(true, Requests[i]->comm->ranks[Requests[i]->rank], Requests[i]->tag);
         fo->add_queue(reinterpret_cast<__Request__ *>(Requests[i]));
      }
  }
  ioConnecting();
  ioPromoteAsyncs();
  return MPI_SUCCESS;
}

int MPI_Wait(MPI_Request * Request, MPI_Status * Status) {
  if (Status == MPI_STATUS_IGNORE)
     Status = MPI_STATUSES_IGNORE;
  return MPI_Waitall(1, Request, Status);
}

int __Wait(int HowMany, int N, MPI_Request * Requests) {
/* HowMany == 0 => wait some, else wait HowMany */
  int completed;
  int nonnulled = N;
  for (int i = 0; i < N; i++)
      if (Requests[i] == MPI_REQUEST_NULL)
         nonnulled--;
  do {
      ioConnecting();
      ioPromoteAsyncs();
      completed = 0;
      for (int i = 0; i < N; i++)
          if (Requests[i] != MPI_REQUEST_NULL && Requests[i]->complete)
             completed++;
      if (HowMany == 0 && completed || HowMany != 0 && completed >= HowMany)
         break;
      if (completed < nonnulled) {
         for (int i = 0; i < N; i++)
             if (Requests[i] != MPI_REQUEST_NULL && !Requests[i]->complete)
                if (Requests[i]->receiving) {
                   iObject * f = iGetOrCreate(true, Requests[i]->comm->ranks[Requests[i]->rank], Requests[i]->tag);
                   if (f->in->ready() && !f->in->empty()) {
                      f->in->get(Requests[i]->buf, Requests[i]->items*__sizes[Requests[i]->type]);
                      Requests[i]->complete = true;
                   }
                } else {
                   oObject * f = oGetOrCreate(true, Requests[i]->comm->ranks[Requests[i]->rank], Requests[i]->tag);
                   if (f->out->ready() && f->out->empty()) {
                      f->out->put(Requests[i]->buf, Requests[i]->items*__sizes[Requests[i]->type]);
                      Requests[i]->complete = true;
                   }
                }
     }
  } while (completed < nonnulled);
  return MPI_SUCCESS;
}

int __WaitSmart(int HowMany, int N, MPI_Request * Requests, int * num, int * indices, MPI_Status * Statuses) {
/* HowMany == 0 => wait some, else wait HowMany */
  for (int i = 0; i < N; i++)
      if (Requests[i] != MPI_REQUEST_NULL && __requests.find(Requests[i]) == __requests.end())
         return MPI_ERR_REQUEST;
  MPI_Request * wave = new MPI_Request[N];
  int nonnulled = 0;
  for (int i = 0; i < N; i++)
    if (Requests[i] != MPI_REQUEST_NULL) {
       wave[i] = Requests[i];
       while (wave[i]->prev)
         wave[i] = wave[i]->prev;
       while (wave[i] != Requests[i] && wave[i]->complete)
         wave[i] = wave[i]->next;
       nonnulled++;
    } else
       wave[i] = MPI_REQUEST_NULL;
  int completed;
  do {
     completed = 0;
     for (int i = 0; i < N; i++)
         if (wave[i] != MPI_REQUEST_NULL && wave[i] == Requests[i] && wave[i]->complete) {
            indices[completed++] = i;
            if (HowMany != 0 && completed == HowMany)
               break;
         }
     if (HowMany == 0 && completed)
        break;
     if (completed < nonnulled)
        __Wait(HowMany, N, wave);
  } while (completed < nonnulled);
  delete[] wave;
  if (completed == 0) {
     *num = MPI_UNDEFINED;
     return MPI_SUCCESS;
  }
  *num = completed;
  if (HowMany == N) { // Wait, Waitall
     for (int i = 0; i < N; i++)
         if (Requests[i] != MPI_REQUEST_NULL) {
            if (Statuses != MPI_STATUSES_IGNORE) {
               Statuses[i].count      = Requests[i]->items;
               Statuses[i].cancelled  = 0;
               Statuses[i].MPI_SOURCE = Requests[i]->rank;
               Statuses[i].MPI_TAG    = Requests[i]->tag;
               Statuses[i].MPI_ERROR  = MPI_SUCCESS;
            }
            if (!Requests[i]->persistent)
               MPI_Request_free(&Requests[i]);
            else
               MPI_Request_delete(&Requests[i]);
         }
  } else { // Waitany, Waitsome
     for (int i = 0; i < completed; i++) {
         int idx = indices[i];
         if (Statuses != MPI_STATUSES_IGNORE) {
            Statuses[i].count      = Requests[idx]->items;
            Statuses[i].cancelled  = 0;
            Statuses[i].MPI_SOURCE = Requests[idx]->rank;
            Statuses[i].MPI_TAG    = Requests[idx]->tag;
            Statuses[i].MPI_ERROR  = MPI_SUCCESS;
         }
         if (!Requests[idx]->persistent)
            MPI_Request_free(&Requests[idx]);
         else
            MPI_Request_delete(&Requests[idx]);
     }
  }
  return MPI_SUCCESS;
}

int MPI_Waitany(int N, MPI_Request * Requests, int * index, MPI_Status * Status) {
  if (N > 0) {
     int count;

     int * indices = new int[N];

     if (Status == MPI_STATUS_IGNORE)
        Status = MPI_STATUSES_IGNORE;

     int result = __WaitSmart(1, N, Requests, &count, indices, Status);

     *index = indices[0];

     delete[] indices;

     return result;
  }
  return MPI_SUCCESS;
}

int MPI_Waitsome(int N, MPI_Request * Requests, int * num, int * indices, MPI_Status * Statuses) {
  if (N > 0) {
     return __WaitSmart(0, N, Requests, num, indices, Statuses);
  }
  return MPI_SUCCESS;
}

int MPI_Waitall(int N, MPI_Request * Requests, MPI_Status * Statuses) {
  if (N > 0) {
     int count;

     int * indices = new int[N];

     int result = __WaitSmart(N, N, Requests, &count, indices, Statuses);

     delete[] indices;

     return result;
  }
  return MPI_SUCCESS;
}

int MPI_Test(MPI_Request * Request, int * Flag, MPI_Status * Status) {
  if (Status == MPI_STATUS_IGNORE)
     Status = MPI_STATUSES_IGNORE;
  return MPI_Testall(1, Request, Flag, Status);
}

int __TestSmart(int HowMany, int N, MPI_Request * Requests, int * num, int * indices, MPI_Status * Statuses) {
/* HowMany == 0 => test some, else test HowMany */
  for (int i = 0; i < N; i++)
      if (Requests[i] != MPI_REQUEST_NULL && __requests.find(Requests[i]) == __requests.end())
         return MPI_ERR_REQUEST;

  ioConnecting();
  ioPromoteAsyncs();

  int completed = 0;
  for (int i = 0; i < N; i++)
      if (Requests[i] != MPI_REQUEST_NULL && Requests[i]->complete) {
         indices[completed++] = i;
         if (HowMany != 0 && completed == HowMany)
            break;
      }
  if (completed == 0) {
     *num = MPI_UNDEFINED;
     return MPI_SUCCESS;
  }
  *num = completed;
  if (HowMany == 0 || completed == HowMany)
     for (int i = 0; i < completed; i++) {
         int idx = indices[i];
         if (Statuses != MPI_STATUSES_IGNORE) {
            Statuses[i].count      = Requests[idx]->items;
            Statuses[i].cancelled  = 0;
            Statuses[i].MPI_SOURCE = Requests[idx]->rank;
            Statuses[i].MPI_TAG    = Requests[idx]->tag;
            Statuses[i].MPI_ERROR  = MPI_SUCCESS;
         }
         if (!Requests[idx]->persistent)
            MPI_Request_free(&Requests[idx]);
         else
            MPI_Request_delete(&Requests[idx]);
     }
  return MPI_SUCCESS;
}

int MPI_Testany(int N, MPI_Request * Requests, int * index, int * Flag, MPI_Status * Status) {
  if (N > 0) {
     int count;

     int * indices = new int[N];

     if (Status == MPI_STATUS_IGNORE)
        Status = MPI_STATUSES_IGNORE;

     int result = __TestSmart(1, N, Requests, &count, indices, Status);

     if (count == MPI_UNDEFINED || count == 0)
        *Flag = 0;
     else {
        *index = indices[0];
        *Flag  = 1;
     }

     delete[] indices;

     return result;
  }
  return MPI_SUCCESS;
}

int MPI_Testall(int N, MPI_Request * Requests, int * Flag, MPI_Status * Statuses) {
  if (N > 0) {
     int count;

     int * indices = new int[N];

     int result = __TestSmart(N, N, Requests, &count, indices, Statuses);
     *Flag = count == N;

     delete[] indices;

     return result;
  }
  return MPI_SUCCESS;
}

int MPI_Testsome(int N, MPI_Request * Requests, int * num, int * indices, MPI_Status * Statuses) {
  if (N > 0) {
     return __TestSmart(0, N, Requests, num, indices, Statuses);
  }
  return MPI_SUCCESS;
}

int MPI_Request_delete(MPI_Request * Request) {
  if (*Request != MPI_REQUEST_NULL && __requests.find(*Request) == __requests.end())
     return MPI_ERR_REQUEST;
  if (*Request != MPI_REQUEST_NULL) {
     if ((*Request)->receiving) {
        iObject * fi = iGetOrCreate(true, (*Request)->comm->ranks[(*Request)->rank], (*Request)->tag);
        if (fi->queue == *Request) fi->queue = (*Request)->next;
     } else {
        oObject * fo = oGetOrCreate(true, (*Request)->comm->ranks[(*Request)->rank], (*Request)->tag);
        if (fo->queue == *Request) fo->queue = (*Request)->next;
     }
     if ((*Request)->prev) (*Request)->prev->next = (*Request)->next;
     if ((*Request)->next) (*Request)->next->prev = (*Request)->prev;
  }
  ioConnecting();
  ioPromoteAsyncs();
  return MPI_SUCCESS;
}

int MPI_Request_free(MPI_Request * Request) {
  if (*Request != MPI_REQUEST_NULL && __requests.find(*Request) == __requests.end())
     return MPI_ERR_REQUEST;
  if (*Request != MPI_REQUEST_NULL) {
     MPI_Request_delete(Request);
     map<MPI_Request, __Request__ *>::iterator ireq = __requests.find(*Request);
     __requests.erase(ireq);
     delete *Request;
     *Request = MPI_REQUEST_NULL;
  }
  ioConnecting();
  ioPromoteAsyncs();
  return MPI_SUCCESS;
}

int MPI_Get_processor_name(char * name, int * namelen) {
  char Buf[MPI_MAX_PROCESSOR_NAME];
  sprintf(Buf,"Virtual Planning C node #%i", __id__);
  *namelen = strlen(Buf) + 1;
  memmove(name, Buf, *namelen);
  return MPI_SUCCESS;
}

int MPI_Barrier(MPI_Comm Comm) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;

  __Barrier(comm);

  return MPI_SUCCESS;
}

int MPI_Group_size(MPI_Group Group, int * size) {
  __Group__ * group;
  if (Group == MPI_GROUP_EMPTY)
     group = &__empty;
  else {
    plan_set_lock(&__group_lock__);
    group = __groups[Group];
    plan_unset_lock(&__group_lock__);
  }
  if (group == NULL)
     return MPI_ERR_GROUP;
  ioConnecting();
  ioPromoteAsyncs();
  *size = group->size;
  return MPI_SUCCESS;
}

int MPI_Group_rank(MPI_Group Group, int * prank) {
  __Group__ * group;
  if (Group == MPI_GROUP_EMPTY)
     group = &__empty;
  else {
    plan_set_lock(&__group_lock__);
    group = __groups[Group];
    plan_unset_lock(&__group_lock__);
  }
  if (group == NULL)
     return MPI_ERR_GROUP;
  for (int i = 0; i < group->size; i++)
      if (group->ranks[i] == __id__) {
         *prank = i;
         return MPI_SUCCESS;
      }
  ioConnecting();
  ioPromoteAsyncs();
  *prank = MPI_UNDEFINED;
  return MPI_SUCCESS;
}

int __Group_incl_excl(bool incl, MPI_Group Group, int n, int * ranks, MPI_Group * NewGroup) {
  __Group__ * group;
  if (Group == MPI_GROUP_EMPTY)
     group = &__empty;
  else {
    plan_set_lock(&__group_lock__);
    group = __groups[Group];
    plan_unset_lock(&__group_lock__);
  }
  if (group == NULL)
     return MPI_ERR_GROUP;
  for (int i = 0; i < n; i++)
      if (ranks[i] >= 0 && ranks[i] < group->size) {
         // Check repetitions
         for (int j = i+1; j < n; j++)
             if (ranks[i] == ranks[j])
                return MPI_ERR_ARG;
      } else
         return MPI_ERR_ARG;
  *NewGroup = new __Group__;
  if (incl) {
     (*NewGroup)->size  = n;
     (*NewGroup)->ranks = new int[n];
     for (int i = 0; i < n; i++)
         (*NewGroup)->ranks[i] = group->ranks[ranks[i]];
  } else {
     (*NewGroup)->size  = group->size - n;
     (*NewGroup)->ranks = new int[group->size - n];
     int k = 0;
     for (int i = 0; i < group->size; i++) {
         bool found = false;
         for (int j = 0; !found && j < n; j++)
             if (ranks[j] == i)
                found = true;
         if (!found) {
            (*NewGroup)->ranks[k] = group->ranks[i];
            k++;
         }
     }
  }
  plan_set_lock(&__group_lock__);
  __groups[*NewGroup] = *NewGroup;
  plan_unset_lock(&__group_lock__);
  ioConnecting();
  ioPromoteAsyncs();
  return MPI_SUCCESS;
}

int MPI_Group_incl(MPI_Group Group, int n, int * ranks, MPI_Group * NewGroup) {
  return __Group_incl_excl(true, Group, n, ranks, NewGroup);
}

int MPI_Group_excl(MPI_Group Group, int n, int * ranks, MPI_Group * NewGroup) {
  return __Group_incl_excl(false, Group, n, ranks, NewGroup);
}

int MPI_Group_free(MPI_Group * Group) {
  plan_set_lock(&__group_lock__);
  __Group__ * group;
  if (*Group == MPI_GROUP_EMPTY) {
     plan_unset_lock(&__group_lock__);
     return MPI_ERR_GROUP;
  } else
     group = __groups[*Group];
  if (group == NULL) {
     plan_unset_lock(&__group_lock__);
     return MPI_ERR_GROUP;
  }
  delete[] group->ranks;
  delete group;
  map<MPI_Group, __Group__ *>::iterator it = __groups.find(*Group);
  __groups.erase(it);
  *Group = MPI_GROUP_NULL;
  plan_unset_lock(&__group_lock__);
  ioConnecting();
  ioPromoteAsyncs();
  return MPI_SUCCESS;
}

int MPI_Comm_group(MPI_Comm Comm, MPI_Group * Group) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  *Group = new __Group__;
  (*Group)->size  = comm->size;
  (*Group)->ranks = new int[comm->size];
  for (int i = 0; i < comm->size; i++)
      (*Group)->ranks[i] = comm->ranks[i];
  plan_set_lock(&__group_lock__);
  __groups[*Group] = *Group;
  plan_unset_lock(&__group_lock__);
  ioConnecting();
  ioPromoteAsyncs();
  return MPI_SUCCESS;
}

int MPI_Comm_create(MPI_Comm Comm, MPI_Group Group, MPI_Comm * NewComm) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  __Group__ * group;
  if (Group == MPI_GROUP_EMPTY)
     group = &__empty;
  else {
    plan_set_lock(&__group_lock__);
    group = __groups[Group];
    plan_unset_lock(&__group_lock__);
  }
  if (group == NULL)
     return MPI_ERR_GROUP;
  // Check that group is subset of parent communicator
  for (int i = 0; i < group->size; i++) {
      bool found = false;
      for (int j = 0; !found && j < comm->size; j++)
          if (comm->ranks[j] == group->ranks[i])
             found = true;
      if (!found)
         return MPI_ERR_ARG;
  }
  MPI_Barrier(Comm);
  bool presents = false;
  for (int i = 0; !presents && i < group->size; i++)
      if (__id__ == group->ranks[i])
         presents = true;
  int root = __NPROCS__;
  for (int i = 0; i < group->size; i++)
      if (group->ranks[i] < root)
         root = group->ranks[i];
  if (presents && __id__ == root) {
     plan_set_lock(&__comm_lock__);
     *NewComm = new __Comm__(group->size);
     // Fill ranks
     memmove((*NewComm)->ranks, group->ranks, group->size*sizeof(int));
     __comms[*NewComm] = *NewComm;
     plan_unset_lock(&__comm_lock__);
     __bufs[__id__] = *NewComm;
  }
  MPI_Barrier(Comm);
  if (presents) {
     plan_set_lock(&__comm_lock__);
     *NewComm = (MPI_Comm) __bufs[root];
     (*NewComm)->refs++;
     plan_unset_lock(&__comm_lock__);
  } else
     *NewComm = MPI_COMM_NULL;
  MPI_Barrier(Comm);
  ioConnecting();
  ioPromoteAsyncs();
  return MPI_SUCCESS;
}

int MPI_Comm_free(MPI_Comm * Comm) {
  plan_set_lock(&__comm_lock__);
  __Comm__ * comm;
  if (*Comm == MPI_COMM_WORLD) {
     plan_unset_lock(&__comm_lock__);
     return MPI_ERR_COMM;
  } else
     comm = __comms[*Comm];
  if (comm == NULL) {
     plan_unset_lock(&__comm_lock__);
     return MPI_ERR_COMM;
  }
  comm->refs--;
  if (comm->refs <= 0) {
     delete comm;
     map<MPI_Comm, __Comm__ *>::iterator it = __comms.find(*Comm);
     __comms.erase(it);
  }
  *Comm = MPI_COMM_NULL;
  plan_unset_lock(&__comm_lock__);
  ioConnecting();
  ioPromoteAsyncs();
  return MPI_SUCCESS;
}

int MPI_Bcast(void * Buf, int Items, MPI_Datatype Type, int Root, MPI_Comm Comm) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if (Buf == NULL && Items != 0)
     return MPI_ERR_BUFFER;
  if (Type < 0 || Type > MPI_UB)
     return MPI_ERR_TYPE;
  if (Items < 0)
     return MPI_ERR_COUNT;
  if (Root < 0 || Root >= comm->size)
     return MPI_ERR_ROOT;
  __bufs[__id__]  = Buf;
  __items[__id__] = Items;
  __types[__id__] = Type;
  __roots[__id__] = Root;
  MPI_Barrier(Comm);
  for (int i = 1; i < comm->size; i++)
      if (__roots[comm->ranks[0]] != __roots[comm->ranks[i]])
         return MPI_ERR_ROOT;
  for (int i = 0; i < comm->size; i++)
      if (i != Root) {
         if (__types[comm->ranks[i]] != __types[comm->ranks[Root]])
            return MPI_ERR_TYPE;
         if (__items[comm->ranks[i]] != __items[comm->ranks[Root]])
            return MPI_ERR_COUNT;
      }
  if (__id__ != comm->ranks[Root])
     memmove(__bufs[__id__], __bufs[comm->ranks[Root]], Items*__sizes[Type]);
  MPI_Barrier(Comm);
  ioConnecting();
  ioPromoteAsyncs();
  return MPI_SUCCESS;
}

int __Gatherv(void * SendBuf, int SendItems, MPI_Datatype SendType,
              void * RecvBuf, int * RecvItems, int * Disps, MPI_Datatype RecvType,
              int Root, MPI_Comm Comm, __Comm__ * comm) {
  __bufs[__id__]  = SendBuf;
  __items[__id__] = SendItems;
  __types[__id__] = SendType;
  __roots[__id__] = Root;
  MPI_Barrier(Comm);
  for (int i = 1; i < comm->size; i++)
      if (__roots[comm->ranks[0]] != __roots[comm->ranks[i]])
         return MPI_ERR_ROOT;
  for (int i = 0; i < comm->size; i++) {
      if (__types[comm->ranks[i]] != __types[comm->ranks[Root]])
         return MPI_ERR_TYPE;
  }
  if (__id__ == comm->ranks[Root])
     if (RecvItems == NULL)
        for (int i = 0; i < comm->size; i++)
            memmove((char *)RecvBuf+i*SendItems*__sizes[SendType], __bufs[comm->ranks[i]], SendItems*__sizes[SendType]);
     else
        for (int i = 0; i < comm->size; i++)
            memmove((char *)RecvBuf+Disps[i]*__sizes[SendType], __bufs[comm->ranks[i]], RecvItems[i]*__sizes[SendType]);
  MPI_Barrier(Comm);
  ioConnecting();
  ioPromoteAsyncs();
  return MPI_SUCCESS;
}

int MPI_Gather(void * SendBuf, int SendItems, MPI_Datatype SendType,
               void * RecvBuf, int RecvItems, MPI_Datatype RecvType,
               int Root, MPI_Comm Comm) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if (SendBuf == NULL && SendItems != 0)
     return MPI_ERR_BUFFER;
  if (SendType < 0 || SendType > MPI_UB || RecvType != SendType)
     return MPI_ERR_TYPE;
  if (SendItems < 0 || RecvItems != SendItems)
     return MPI_ERR_COUNT;
  if (Root < 0 || Root >= comm->size)
     return MPI_ERR_ROOT;
  return __Gatherv(SendBuf, SendItems, SendType, RecvBuf, NULL, NULL, RecvType, Root, Comm, comm);
}

int MPI_Gatherv(void * SendBuf, int SendItems, MPI_Datatype SendType,
                void * RecvBuf, int * RecvItems, int * Disps, MPI_Datatype RecvType,
                int Root, MPI_Comm Comm) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if (SendBuf == NULL && SendItems != 0)
     return MPI_ERR_BUFFER;
  if (SendType < 0 || SendType > MPI_UB || RecvType != SendType)
     return MPI_ERR_TYPE;
  if (SendItems < 0)
     return MPI_ERR_COUNT;
  if (__id__ == comm->ranks[Root] && (RecvItems == NULL || Disps == NULL))
     return MPI_ERR_ARG;
  if (Root < 0 || Root >= comm->size)
     return MPI_ERR_ROOT;
  return __Gatherv(SendBuf, SendItems, SendType, RecvBuf, RecvItems, Disps, RecvType, Root, Comm, comm);
}

int __Scatterv(void * SendBuf, int * SendItems, int * Disps, MPI_Datatype SendType,
               void * RecvBuf, int RecvItems, MPI_Datatype RecvType,
               int Root, MPI_Comm Comm, __Comm__ * comm) {
  __bufs[__id__]  = RecvBuf;
  __items[__id__] = RecvItems;
  __types[__id__] = RecvType;
  __roots[__id__] = Root;
  MPI_Barrier(Comm);
  for (int i = 1; i < comm->size; i++)
      if (__roots[comm->ranks[0]] != __roots[comm->ranks[i]])
         return MPI_ERR_ROOT;
  for (int i = 0; i < comm->size; i++) {
      if (__types[comm->ranks[i]] != __types[comm->ranks[Root]])
         return MPI_ERR_TYPE;
  }
  if (__id__ == comm->ranks[Root])
     if (SendItems == NULL)
        for (int i = 0; i < comm->size; i++)
            memmove(__bufs[comm->ranks[i]], (char *)SendBuf+i*RecvItems*__sizes[SendType], RecvItems*__sizes[SendType]);
     else
        for (int i = 0; i < comm->size; i++)
            memmove(__bufs[comm->ranks[i]], (char *)SendBuf+Disps[i]*__sizes[SendType], SendItems[i]*__sizes[SendType]);
  MPI_Barrier(Comm);
  ioConnecting();
  ioPromoteAsyncs();
  return MPI_SUCCESS;
}

int MPI_Scatterv(void * SendBuf, int * SendItems, int * Disps, MPI_Datatype SendType,
                 void * RecvBuf, int RecvItems, MPI_Datatype RecvType,
                 int Root, MPI_Comm Comm) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if (RecvBuf == NULL && RecvItems != 0)
     return MPI_ERR_BUFFER;
  if (SendType < 0 || SendType > MPI_UB || RecvType != SendType)
     return MPI_ERR_TYPE;
  if (RecvItems < 0)
     return MPI_ERR_COUNT;
  if (__id__ == comm->ranks[Root] && (SendItems == NULL || Disps == NULL))
     return MPI_ERR_ARG;
  if (Root < 0 || Root >= comm->size)
     return MPI_ERR_ROOT;
  return __Scatterv(SendBuf, SendItems, Disps, SendType, RecvBuf, RecvItems, RecvType, Root, Comm, comm);
}

int MPI_Scatter(void * SendBuf, int SendItems, MPI_Datatype SendType,
                void * RecvBuf, int RecvItems, MPI_Datatype RecvType,
                int Root, MPI_Comm Comm) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if (RecvBuf == NULL && RecvItems != 0)
     return MPI_ERR_BUFFER;
  if (SendType < 0 || SendType > MPI_UB || RecvType != SendType)
     return MPI_ERR_TYPE;
  if (RecvItems < 0 || RecvItems != SendItems)
     return MPI_ERR_COUNT;
  if (Root < 0 || Root >= comm->size)
     return MPI_ERR_ROOT;
  return __Scatterv(SendBuf, NULL, NULL, SendType, RecvBuf, RecvItems, RecvType, Root, Comm, comm);
}

int __Allreduce(bool all, void * SendBuf, void * RecvBuf, int Items, MPI_Datatype Type, MPI_Op Op, int Root, MPI_Comm Comm) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if ((SendBuf == NULL || RecvBuf == NULL) && Items != 0)
     return MPI_ERR_BUFFER;
  if (Type < 0 || Type > MPI_UB)
     return MPI_ERR_TYPE;
  if (Items < 0)
     return MPI_ERR_COUNT;
  if (!all && (Root < 0 || Root >= comm->size))
     return MPI_ERR_ROOT;
  if (Op < 0 || Op > MPI_REPLACE)
     return MPI_ERR_OP;
  __bufs[__id__]  = SendBuf;
  __rbufs[__id__] = RecvBuf;
  __items[__id__] = Items;
  __types[__id__] = Type;
  __ops[__id__]   = Op;
  __roots[__id__] = Root;
  MPI_Barrier(Comm);
  for (int i = 1; i < comm->size; i++)
      if (__roots[comm->ranks[0]] != __roots[comm->ranks[i]])
         return MPI_ERR_ROOT;
  for (int i = 0; i < comm->size; i++)
      if (i != Root) {
         if (__types[comm->ranks[i]] != __types[comm->ranks[Root]])
            return MPI_ERR_TYPE;
         if (__items[comm->ranks[i]] != __items[comm->ranks[Root]])
            return MPI_ERR_COUNT;
         if (__ops[comm->ranks[i]] != __ops[comm->ranks[Root]])
            return MPI_ERR_OP;
      }
  if (all) {
     int rank = __TranslateRank(comm, __id__);
     for (int j = rank; j < Items; j += comm->size) {
        applyOp(((char *)RecvBuf+j*__sizes[Type]), (char *)SendBuf+j*__sizes[Type], Type, MPI_REPLACE);
        for (int i = 0; i < comm->size; i++)
            if (i != rank)
               applyOp((char *)RecvBuf+j*__sizes[Type], (char *)__bufs[comm->ranks[i]]+j*__sizes[Type], Type, Op);
     }
     MPI_Barrier(Comm);
     for (int j = 0; j < Items; j++) {
         int __proc_id__ = comm->ranks[j % comm->size];
         if (__proc_id__ != __id__)
            memmove(((char *)RecvBuf+j*__sizes[Type]), (char *)__rbufs[__proc_id__]+j*__sizes[Type], __sizes[Type]);
     }
  } else if (__id__ == comm->ranks[Root])
     for (int j = 0; j < Items; j++) {
        applyOp(((char *)RecvBuf+j*__sizes[Type]), (char *)SendBuf+j*__sizes[Type], Type, MPI_REPLACE);
        for (int i = 0; i < comm->size; i++)
            if (i != Root)
               applyOp((char *)RecvBuf+j*__sizes[Type], (char *)__bufs[comm->ranks[i]]+j*__sizes[Type], Type, Op);
     }
  MPI_Barrier(Comm);
  ioConnecting();
  ioPromoteAsyncs();
  return MPI_SUCCESS;
}

int MPI_Reduce(void * SendBuf, void * RecvBuf, int Items, MPI_Datatype Type, MPI_Op Op, int Root, MPI_Comm Comm) {
  return __Allreduce(false, SendBuf, RecvBuf, Items, Type, Op, Root, Comm);
}

int MPI_Allreduce(void * SendBuf, void * RecvBuf, int Items, MPI_Datatype Type, MPI_Op Op, MPI_Comm Comm) {
  return __Allreduce(true, SendBuf, RecvBuf, Items, Type, Op, 0, Comm);
}

int __Allgatherv(void * SendBuf, int SendItems, MPI_Datatype SendType,
                 void * RecvBuf, int * RecvItems, int * Disps, MPI_Datatype RecvType,
                 MPI_Comm Comm, __Comm__ * comm) {
  __bufs[__id__]  = SendBuf;
  __items[__id__] = SendItems;
  __types[__id__] = SendType;
  MPI_Barrier(Comm);
  for (int i = 0; i < comm->size; i++) {
     if (__types[comm->ranks[i]] != __types[comm->ranks[0]])
        return MPI_ERR_TYPE;
     if (RecvItems != NULL && RecvItems[i] != __items[comm->ranks[i]] || RecvItems == NULL && __items[comm->ranks[i]] != __items[comm->ranks[0]])
        return MPI_ERR_COUNT;
  }
  if (RecvItems == NULL || Disps == NULL)
     for (int i = 0; i < comm->size; i++)
         memmove((char *)RecvBuf+i*SendItems*__sizes[SendType], __bufs[comm->ranks[i]], SendItems*__sizes[SendType]);
  else
     for (int i = 0; i < comm->size; i++)
         memmove((char *)RecvBuf+Disps[i]*__sizes[SendType], __bufs[comm->ranks[i]], RecvItems[i]*__sizes[SendType]);
  MPI_Barrier(Comm);
  ioConnecting();
  ioPromoteAsyncs();
  return MPI_SUCCESS;
}

int MPI_Allgatherv(void * SendBuf, int SendItems, MPI_Datatype SendType,
                   void * RecvBuf, int * RecvItems, int * Disps, MPI_Datatype RecvType,
                   MPI_Comm Comm) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if ((SendBuf == NULL || RecvBuf == NULL) && SendItems != 0)
     return MPI_ERR_BUFFER;
  if (RecvItems == NULL || Disps == NULL)
     return MPI_ERR_ARG;
  if (SendType < 0 || SendType > MPI_UB || RecvType != SendType)
     return MPI_ERR_TYPE;
  if (SendItems < 0)
     return MPI_ERR_COUNT;
  return __Allgatherv(SendBuf, SendItems, SendType, RecvBuf, RecvItems, Disps, RecvType, Comm, comm);
}

int MPI_Allgather(void * SendBuf, int SendItems, MPI_Datatype SendType,
                  void * RecvBuf, int RecvItems, MPI_Datatype RecvType,
                  MPI_Comm Comm) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if (SendBuf == NULL && SendItems != 0 || RecvBuf == NULL && RecvItems != 0)
     return MPI_ERR_BUFFER;
  if (SendType < 0 || SendType > MPI_UB || RecvType != SendType)
     return MPI_ERR_TYPE;
  if (SendItems < 0 || RecvItems != SendItems)
     return MPI_ERR_COUNT;
  return __Allgatherv(SendBuf, SendItems, SendType, RecvBuf, NULL, NULL, RecvType, Comm, comm);
}

int __Alltoallv(void * SendBuf, int * SendItems, int * SendDisps, MPI_Datatype SendType,
                void * RecvBuf, int * RecvItems, int * RecvDisps, MPI_Datatype RecvType, MPI_Comm Comm,
                __Comm__ * comm) {
  __bufs[__id__]   = SendBuf;
  p__items[__id__] = SendItems;
  __types[__id__]  = SendType;
  MPI_Barrier(Comm);
  for (int i = 0; i < comm->size; i++) {
     if (__types[comm->ranks[i]] != __types[comm->ranks[0]])
        return MPI_ERR_TYPE;
     if ((SendDisps != NULL && RecvDisps != NULL) && RecvItems[i] != p__items[comm->ranks[i]][__TranslateRank(comm, __id__)])
        return MPI_ERR_COUNT;
  }
  if (SendDisps == NULL || RecvDisps == NULL)
     for (int i = 0; i < comm->size; i++)
         memmove((char *)RecvBuf+i*(*RecvItems)*__sizes[RecvType],
                 (char *)__bufs[comm->ranks[i]]+__TranslateRank(comm,__id__)*(*SendItems)*__sizes[SendType],
                 (*RecvItems)*__sizes[RecvType]);
  else
     for (int i = 0; i < comm->size; i++)
         memmove((char *)RecvBuf+RecvDisps[i]*__sizes[RecvType],
                 (char *)__bufs[comm->ranks[i]]+SendDisps[__TranslateRank(comm,__id__)]*__sizes[SendType],
                 RecvItems[i]*__sizes[RecvType]);
  MPI_Barrier(Comm);
  ioConnecting();
  ioPromoteAsyncs();
  return MPI_SUCCESS;
}

int MPI_Alltoall(void * SendBuf, int SendItems, MPI_Datatype SendType,
                 void * RecvBuf, int RecvItems, MPI_Datatype RecvType, MPI_Comm Comm) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if (SendBuf == NULL && SendItems != 0 || RecvBuf == NULL && RecvItems != 0)
     return MPI_ERR_BUFFER;
  if (SendType < 0 || SendType > MPI_UB || RecvType != SendType)
     return MPI_ERR_TYPE;
  if (SendItems < 0 || RecvItems != SendItems)
     return MPI_ERR_COUNT;
  return __Alltoallv(SendBuf, &SendItems, NULL, SendType, RecvBuf, &RecvItems, NULL, RecvType, Comm, comm);
}

int MPI_Alltoallv(void * SendBuf, int * SendItems, int * SendDisps, MPI_Datatype SendType,
                  void * RecvBuf, int * RecvItems, int * RecvDisps, MPI_Datatype RecvType, MPI_Comm Comm) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  if (SendBuf == NULL || RecvBuf == NULL)
     return MPI_ERR_BUFFER;
  if (SendType < 0 || SendType > MPI_UB || RecvType != SendType)
     return MPI_ERR_TYPE;
  if (SendItems == NULL || RecvItems == NULL)
     return MPI_ERR_COUNT;
  if (SendDisps == NULL || RecvDisps == NULL)
     return MPI_ERR_ARG;
  return __Alltoallv(SendBuf, SendItems, SendDisps, SendType, RecvBuf, RecvItems, RecvDisps, RecvType, Comm, comm);
}

int MPI_Abort(MPI_Comm Comm, int code) {
  __Comm__ * comm;
  if (Comm == MPI_COMM_WORLD)
     comm = &__world;
  else {
    plan_set_lock(&__comm_lock__);
    comm = __comms[Comm];
    plan_unset_lock(&__comm_lock__);
  }
  if (comm == NULL)
     return MPI_ERR_COMM;
  exit(code);
  return MPI_SUCCESS;
}

int MPI_Finalize(void) {
  MPI_Barrier(MPI_COMM_WORLD);
  if (__id__ == 0) {
     plan_destroy_lock(&__iolock__);
     plan_destroy_lock(&__comm_lock__);
     plan_destroy_lock(&__group_lock__);
     plan_destroy_lock(&__win_lock__);
     map<MPI_Comm, __Comm__ *>::iterator icomms;
     for (icomms = __comms.begin(); icomms != __comms.end(); icomms++) {
         if (icomms->first != MPI_COMM_WORLD)
            delete icomms->second;
     }
     map<MPI_Group, __Group__ *>::iterator igroups;
     for (igroups = __groups.begin(); igroups != __groups.end(); igroups++) {
         delete[] igroups->second->ranks;
         if (igroups->first != MPI_GROUP_EMPTY)
            delete igroups->second;
     }
     map<MPI_Request, __Request__ *>::iterator ireqs;
     for (ireqs = __requests.begin(); ireqs != __requests.end(); ireqs++) {
         if (ireqs->first != MPI_REQUEST_NULL)
            delete ireqs->second;
     }
     map<MPI_Win, __Win__ *>::iterator iwins;
     for (iwins = __wins.begin(); iwins != __wins.end(); iwins++) {
         if (iwins->first != MPI_WIN_NULL)
            delete iwins->second;
     }
  }
  for (int i = 0; i < __NPROCS__; i++) {
      i_funnels * inp = __inps[__id__][i];
      i_funnels::iterator iinp;
      for (iinp = inp->begin(); iinp != inp->end(); iinp++)
          delete iinp->second;
      delete inp;
      o_funnels * out = __outs[__id__][i];
      o_funnels::iterator iout;
      for (iout = out->begin(); iout != out->end(); iout++)
          delete iout->second;
      delete out;
  }   
  return MPI_SUCCESS;
}

#endif
