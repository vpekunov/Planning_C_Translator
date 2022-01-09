Unit Topo;

Interface

{$IFDEF FPC}
{$MODE ObjFPC}
{$ENDIF}
{$H+}

Uses Common, Consts, Classes;

Type TLink = Record
        First, Last: Integer;
        Rev: Boolean
     End;

Type TLinks = Array Of TLink;

Procedure CreateTopology(Var Out: TextFile; Const ClusteredArrID: String;
                         Chain, Topology: TStringList; NProcs: String);

Function GenerateTopology(IsTopological: Boolean {True for topology};
                          Const ClusteredArrID: String;
                          Const Parallelize {'1+2' for topology},
                                ChainInit {'1' for topology}: String;
                          NProcs: String;
                          Const VectorNum {'0' for topology}: String;
                          ChainIsVector: Boolean {False for topology};
                          Chain, ChainItems: TStringList;
                          Const Links: TLinks
): String;

Const Topologies: PChar =
'#define input_proc unsigned long long'+CRLF+
'#define empty_proc (0)'+CRLF+
'inline void * input_addr(input_proc SRC) {'+CRLF+
'  return (void *) (SRC>>32);'+CRLF+
'}'+CRLF+
''+CRLF+
'inline int input_index(input_proc SRC) {'+CRLF+
'  return SRC & 0xFFFFFFFF;'+CRLF+
'}'+CRLF+
''+CRLF+
'#define plan_linear_num() __plan_linear_num()'+CRLF+
'#define plan_topology_num() __plan_topology_num()'+CRLF+
'#define plan_topology_quit() __plan_topology_quit()'+CRLF+
''+CRLF+
'#ifdef _OPENMP'+CRLF+
'#define __plan_linear_num() ((__nprocs__)>>17)'+CRLF+
'#define __plan_topology_num() (((__nprocs__)>>10) & 0x1F)'+CRLF+
'#define __plan_topology_quit() __quit_topology(plan_topology_num())'+CRLF+
''+CRLF+
'#define __plan_register(ID,GroupID) \'+CRLF+
'   __add_group_node(plan_topology_num(),#GroupID,reinterpret_cast<void *>(&_call_##ID),plan_linear_num(),__event_list__,__plan_lock__,__signaler__)'+CRLF+
'#define plan_neighbours(incoming, Ref, n, refs) \'+CRLF+
'   __plan_neighbours(plan_topology_num(), incoming, Ref, n, refs)'+CRLF+
'#else'+CRLF+
'#define __plan_linear_num() (throw_stage()+1)'+CRLF+
'#define __plan_topology_num() (-1)'+CRLF+
'#define __plan_topology_quit() ;'+CRLF+
''+CRLF+
'#define __plan_register(ID,GroupID) ;'+CRLF+
'#define plan_neighbours(incoming, Ref, n, refs) { \'+CRLF+
'   *n = 0; \'+CRLF+
'   }'+CRLF+
'#endif'+CRLF+
''+CRLF+
'#ifdef _OPENMP'+CRLF+
''+CRLF+
'typedef struct {'+CRLF+
'  int idx;'+CRLF+
'  unsigned int ref;'+CRLF+
'} __Address;'+CRLF+
''+CRLF+
'typedef union {'+CRLF+
'  __Address  ref_idx;'+CRLF+
'  unsigned long long single;'+CRLF+
'} __Address_union;'+CRLF+
''+CRLF+
'class __Group;'+CRLF+
''+CRLF+
'class __Node {'+CRLF+
'  public:'+CRLF+
'    void * Plan;'+CRLF+
'    plan_lock_t * LockPlan;'+CRLF+
'    __reent_event * SignalPlan;'+CRLF+
'    __Group * barriered;'+CRLF+
'    int id;'+CRLF+
''+CRLF+
'    __Node(): Plan(NULL), LockPlan(NULL), SignalPlan(NULL), id(-1), barriered(NULL) {'+CRLF+
'    }'+CRLF+
'    void set(void * __event_list__, plan_lock_t * __plan_lock__, __reent_event * __signaler__) {'+CRLF+
'      Plan = __event_list__;'+CRLF+
'      LockPlan = __plan_lock__;'+CRLF+
'      SignalPlan = __signaler__;'+CRLF+
'    }'+CRLF+
'};'+CRLF+
''+CRLF+
'class __OutLinks {'+CRLF+
'  private:'+CRLF+
'    map<unsigned long long,void *> Links;'+CRLF+
'  public:'+CRLF+
'    void add_link(void * Dest, int idx) {'+CRLF+
'      __Address_union A;'+CRLF+
''+CRLF+
'      A.ref_idx.ref = (unsigned long long)Dest & 0xFFFFFFFF;'+CRLF+
'      A.ref_idx.idx = idx;'+CRLF+
''+CRLF+
'      if (Links.find(A.single) == Links.end())'+CRLF+
'         Links[A.single] = NULL;'+CRLF+
'    }'+CRLF+
'    bool find_link(input_proc Dest) {'+CRLF+
'      return Links.find(Dest) != Links.end();'+CRLF+
'    }'+CRLF+
'    unsigned long long get_single_link() {'+CRLF+
'      if (Links.size() == 1)'+CRLF+
'         return Links.begin()->first;'+CRLF+
'      else'+CRLF+
'         return 0;'+CRLF+
'    }'+CRLF+
'    void export_links(int * n, unsigned long long * links) {'+CRLF+
'      int i = 0;'+CRLF+
''+CRLF+
'      *n = Links.size();'+CRLF+
''+CRLF+
'      map<unsigned long long,void *>::iterator it = Links.begin();'+CRLF+
'      for (; it != Links.end(); it++)'+CRLF+
'          links[i++] = it->first;'+CRLF+
'    }'+CRLF+
'};'+CRLF+
''+CRLF+
'class __Group {'+CRLF+
'  private:'+CRLF+
'    map<__Node *,void *> Nodes;'+CRLF+
'    volatile int BN;'+CRLF+
'    volatile int BCounter;'+CRLF+
'    volatile bool BFlag;'+CRLF+
'  public:'+CRLF+
'    __Group() {'+CRLF+
'      BN = 0;'+CRLF+
'      BCounter = 0;'+CRLF+
'      BFlag = false;'+CRLF+
'    }'+CRLF+
'    bool find(__Node * node) {'+CRLF+
'      return Nodes.find(node) != Nodes.end();'+CRLF+
'    }'+CRLF+
'    void enter_barrier() {'+CRLF+
'      BCounter--;'+CRLF+
'      if (BCounter <= 0) {'+CRLF+
'         BCounter = 0;'+CRLF+
'         BFlag = true;'+CRLF+
'      }'+CRLF+
'    }'+CRLF+
'    void wait_barrier() {'+CRLF+
'      while (!BFlag) {'+CRLF+
'        _Yield();'+CRLF+
'      }'+CRLF+
'      BCounter++;'+CRLF+
'      if (BCounter >= BN) {'+CRLF+
'         BCounter = BN;'+CRLF+
'         BFlag = false;'+CRLF+
'      }'+CRLF+
'    }'+CRLF+
'    void leave_barrier() {'+CRLF+
'      while (BFlag) {'+CRLF+
'        _Yield();'+CRLF+
'      }'+CRLF+
'    }'+CRLF+
'    void add_node(__Node * node, void * __event_list__, plan_lock_t * __plan_lock__, __reent_event * __signaler__) {'+CRLF+
'      if (node) {'+CRLF+
'         if (Nodes.find(node) == Nodes.end())'+CRLF+
'            Nodes[node] = NULL;'+CRLF+
'         node->set(__event_list__, __plan_lock__, __signaler__);'+CRLF+
'         BN = Nodes.size();'+CRLF+
'         BCounter = BN;'+CRLF+
'         BFlag = false;'+CRLF+
'      }'+CRLF+
'    }'+CRLF+
'};'+CRLF+
''+CRLF+
'const int gcAddGroupNode = 0;'+CRLF+
'const int gcBarrier      = 1;'+CRLF+
'typedef struct {'+CRLF+
'  char group[60];'+CRLF+
'  int  command;'+CRLF+
'} __group_struct;'+CRLF+
''+CRLF+
'class __Topology {'+CRLF+
'  public:'+CRLF+
'    map<unsigned long long,__Node *> Nodes;'+CRLF+
'    map<unsigned long long,__OutLinks *> OutLinks;'+CRLF+
'    map<string,__Group *> Groups;'+CRLF+
'    volatile int Barrier;'+CRLF+
'    volatile bool BarrierFlag;'+CRLF+
'    volatile int nBarrier;'+CRLF+
'    bool clustered;'+CRLF+
'  protected:'+CRLF+
'    int tag;'+CRLF+
'    bool exited;'+CRLF+
'    char __parallelize__;'+CRLF+
'    int * __counter__;'+CRLF+
'    omp_lock_t * __counter_lock__;'+CRLF+
'  public:'+CRLF+
'    __Topology(char parallelize, int * counter, omp_lock_t * counter_lock, bool _clustered) {'+CRLF+
'      clustered        = _clustered;'+CRLF+
'      __parallelize__  = parallelize;'+CRLF+
'      __counter__      = counter;'+CRLF+
'      __counter_lock__ = counter_lock;'+CRLF+
'      Barrier = 0;'+CRLF+
'      BarrierFlag = false;'+CRLF+
'      nBarrier = 0;'+CRLF+
'      tag = 0;'+CRLF+
'      exited = false;'+CRLF+
'    }'+CRLF+
'    char get_parallelize() { return __parallelize__; }'+CRLF+
'    void set_topology_tag(int tag) { this->tag = tag; }'+CRLF+
'    int  get_topology_tag() { return tag; }'+CRLF+
'    bool is_exited() { return exited; }'+CRLF+
'    bool is_clustered() { return clustered; }'+CRLF+
'    void process_group_messages() {'+CRLF+
'#ifdef __REENT_MPI__'+CRLF+
'      if (!clustered) return;'+CRLF+
'      map<unsigned long long,__Node *>::iterator itNodes = Nodes.begin();'+CRLF+
'      for (; itNodes != Nodes.end(); itNodes++)'+CRLF+
'          if (itNodes->second->id != __cluster_id__ && itNodes->second->barriered == NULL) {'+CRLF+
'             MPI_Status status;'+CRLF+
'             int received = 1;'+CRLF+
'             while (received && itNodes->second->barriered == NULL) {'+CRLF+
'               MPI_Iprobe(itNodes->second->id, 1236, MPI_COMM_WORLD, &received, &status);'+CRLF+
'               if (received) {'+CRLF+
'                  __group_struct gs;'+CRLF+
'                  MPI_Status status1;'+CRLF+
'                  MPI_Recv(&gs, sizeof(gs), MPI_BYTE, itNodes->second->id, 1236, MPI_COMM_WORLD, &status1);'+CRLF+
'                  if (gs.command == gcAddGroupNode) {'+CRLF+
'                     if (Groups.find(gs.group) == Groups.end())'+CRLF+
'                        Groups[gs.group] = new __Group();'+CRLF+
'                     Groups[gs.group]->add_node(itNodes->second, NULL, NULL, NULL);'+CRLF+
'                  } else if (gs.command == gcBarrier) {'+CRLF+
'                     map<string,__Group *>::iterator itGroups = Groups.find(gs.group);'+CRLF+
'                     if (itGroups == Groups.end()) {'+CRLF+
'                        cout<<"Barrier: Group ''"<<gs.group<<"'' does not exist"<<endl;'+CRLF+
'                        exit(-1);'+CRLF+
'                     }'+CRLF+
'                     itNodes->second->barriered = itGroups->second;'+CRLF+
'                  }'+CRLF+
'               }'+CRLF+
'             }'+CRLF+
'          }'+CRLF+
'#endif'+CRLF+
'    }'+CRLF+
'    void quit() {'+CRLF+
'      exited = true;'+CRLF+
'      if (__parallelize__ & 2) {'+CRLF+
'         if (__counter_lock__) {'+CRLF+
'            omp_set_lock(__counter_lock__);'+CRLF+
'            *__counter__ = -1;'+CRLF+
'            omp_unset_lock(__counter_lock__);'+CRLF+
'         }'+CRLF+
'         map<unsigned long long,__Node *>::iterator itNodes;'+CRLF+
'#ifdef __REENT_MPI__'+CRLF+
'         for (itNodes = Nodes.begin(); itNodes != Nodes.end(); itNodes++)'+CRLF+
'             if (itNodes->second->id != __cluster_id__)'+CRLF+
'                MPI_Send(NULL, 0, MPI_BYTE, itNodes->second->id, tag, MPI_COMM_WORLD);'+CRLF+
'#endif'+CRLF+
'         for (itNodes = Nodes.begin(); itNodes != Nodes.end(); itNodes++) {'+CRLF+
'             __Node * node = itNodes->second;'+CRLF+
'             if (node->SignalPlan) {'+CRLF+
'                __signal_reent_event(node->SignalPlan);'+CRLF+
'                __instead_signal_yield();'+CRLF+
'             }'+CRLF+
'         }'+CRLF+
'      }'+CRLF+
'    }'+CRLF+
'    ~__Topology() {'+CRLF+
'      process_group_messages();'+CRLF+
'      map<unsigned long long,__Node *>::iterator itNodes;'+CRLF+
'      map<unsigned long long,__OutLinks *>::iterator itOutLinks;'+CRLF+
'      map<string,__Group *>::iterator itGroups;'+CRLF+
'      for (itNodes = Nodes.begin(); itNodes != Nodes.end(); itNodes++)'+CRLF+
'          delete itNodes->second;'+CRLF+
'      for (itOutLinks = OutLinks.begin(); itOutLinks != OutLinks.end(); itOutLinks++)'+CRLF+
'          delete itOutLinks->second;'+CRLF+
'      for (itGroups = Groups.begin(); itGroups != Groups.end(); itGroups++)'+CRLF+
'          delete itGroups->second;'+CRLF+
'    }'+CRLF+
'};'+CRLF+
''+CRLF+
'vector<__Topology *> __TopologyStack;'+CRLF+
'plan_lock_t * __topo_lock__ = NULL;'+CRLF+
''+CRLF+
'void __process_group_messages(int topo) {'+CRLF+
'  plan_set_lock(__topo_lock__);'+CRLF+
'  __Topology * top = __TopologyStack[topo];'+CRLF+
'  top->process_group_messages();'+CRLF+
'  plan_unset_lock(__topo_lock__);'+CRLF+
'}'+CRLF+
''+CRLF+
'void __quit_topology(int topo) {'+CRLF+
'  plan_set_lock(__topo_lock__);'+CRLF+
'  __Topology * top = __TopologyStack[topo];'+CRLF+
'  top->quit();'+CRLF+
'  plan_unset_lock(__topo_lock__);'+CRLF+
'}'+CRLF+
''+CRLF+
'int __get_num_stages(int topo) {'+CRLF+
'  plan_set_lock(__topo_lock__);'+CRLF+
'  __Topology * top = __TopologyStack[topo];'+CRLF+
'  int result = top->Nodes.size();'+CRLF+
'  plan_unset_lock(__topo_lock__);'+CRLF+
'  return result;'+CRLF+
'}'+CRLF+
''+CRLF+
'bool __exited_topology(int topo) {'+CRLF+
'  plan_set_lock(__topo_lock__);'+CRLF+
'  __Topology * top = __TopologyStack[topo];'+CRLF+
'  bool result = top->is_exited();'+CRLF+
'  plan_unset_lock(__topo_lock__);'+CRLF+
'  return result;'+CRLF+
'}'+CRLF+
''+CRLF+
'int __clustered_topology(int topo) {'+CRLF+
'  int result;'+CRLF+
'  plan_set_lock(__topo_lock__);'+CRLF+
'  __Topology * top = __TopologyStack[topo];'+CRLF+
'  result = top->is_clustered();'+CRLF+
'  plan_unset_lock(__topo_lock__);'+CRLF+
'  return result;'+CRLF+
'}'+CRLF+
''+CRLF+
'void __topology_barrier(int topo) {'+CRLF+
'  __Topology * top = __TopologyStack[topo];'+CRLF+
'#ifdef __REENT_MPI__'+CRLF+
' if (top->clustered) {'+CRLF+
'    const char * GroupID = "topology";'+CRLF+
'    plan_set_lock(__topo_lock__);'+CRLF+
'    __group_struct gs;'+CRLF+
'    memmove(gs.group, GroupID, strlen(GroupID)+1);'+CRLF+
'    gs.command = gcBarrier;'+CRLF+
''+CRLF+
'    __Group * Group = top->Groups.find(GroupID)->second;'+CRLF+
'    map<unsigned long long,__Node *>::iterator itNodes;'+CRLF+
'    for (itNodes = top->Nodes.begin(); itNodes != top->Nodes.end(); itNodes++)'+CRLF+
'        if (itNodes->second->id != __cluster_id__)'+CRLF+
'           MPI_Send(&gs, sizeof(gs), MPI_BYTE, itNodes->second->id, 1236, MPI_COMM_WORLD);'+CRLF+
'        else'+CRLF+
'           itNodes->second->barriered = Group;'+CRLF+
'    bool passed;'+CRLF+
'    do {'+CRLF+
'        plan_unset_lock(__topo_lock__);'+CRLF+
'        _Yield();'+CRLF+
'        plan_set_lock(__topo_lock__);'+CRLF+
'        top->process_group_messages();'+CRLF+
'        passed = true;'+CRLF+
'        for (itNodes = top->Nodes.begin(); passed && itNodes != top->Nodes.end(); itNodes++)'+CRLF+
'            if (itNodes->second->barriered != Group)'+CRLF+
'               passed = false;'+CRLF+
'    } while (!passed);'+CRLF+
'    for (itNodes = top->Nodes.begin(); itNodes != top->Nodes.end(); itNodes++)'+CRLF+
'        itNodes->second->barriered = NULL;'+CRLF+
'    plan_unset_lock(__topo_lock__);'+CRLF+
' } else {'+CRLF+
'#endif'+CRLF+
'    if (top->nBarrier <= 0) return;'+CRLF+
'    #pragma omp critical(__init_barrier1)'+CRLF+
'    {'+CRLF+
'      top->Barrier--;'+CRLF+
'      if (top->Barrier == 0)'+CRLF+
'         top->BarrierFlag = true;'+CRLF+
'    }'+CRLF+
'    #pragma omp critical(__init_barrier2)'+CRLF+
'    {'+CRLF+
'      while (!top->BarrierFlag) {'+CRLF+
'        _Yield();'+CRLF+
'      }'+CRLF+
'      top->Barrier++;'+CRLF+
'      if (top->Barrier == top->nBarrier)'+CRLF+
'         top->BarrierFlag = false;'+CRLF+
'    }'+CRLF+
'    while (top->BarrierFlag) {'+CRLF+
'      _Yield();'+CRLF+
'    }'+CRLF+
'#ifdef __REENT_MPI__'+CRLF+
' }'+CRLF+
'#endif'+CRLF+
'}'+CRLF+
''+CRLF+
'int __push_topology(char __parallelize__, int * __counter__, omp_lock_t * __counter_lock__, bool clustered) {'+CRLF+
'  __Topology * topo = new __Topology(__parallelize__, __counter__, __counter_lock__, clustered);'+CRLF+
'  int result = 0;'+CRLF+
'  plan_set_lock(__topo_lock__);'+CRLF+
'  while (result < __TopologyStack.size() && __TopologyStack[result]) result++;'+CRLF+
'  if (result < __TopologyStack.size()) {'+CRLF+
'     __TopologyStack[result] = topo;'+CRLF+
'  } else if (__TopologyStack.size() == 32) {'+CRLF+
'     cout<<"Number of topologies can''t exceed 32."<<endl;'+CRLF+
'     exit(-1);'+CRLF+
'  } else {'+CRLF+
'     __TopologyStack.push_back(topo);'+CRLF+
'  }'+CRLF+
'  plan_unset_lock(__topo_lock__);'+CRLF+
'  return result;'+CRLF+
'}'+CRLF+
''+CRLF+
'void __add_topology_link(int topo, void * Src, int SrcIdx, void * Dest, int DestIdx) {'+CRLF+
'  plan_set_lock(__topo_lock__);'+CRLF+
'  __Topology * top = __TopologyStack[topo];'+CRLF+
'  __Address_union A1, A2;'+CRLF+
'  '+CRLF+
'  auto add_node = [&](void * Src, int idx, __Address_union & A) {'+CRLF+
'    A.ref_idx.ref = (unsigned long long)Src & 0xFFFFFFFF;'+CRLF+
'    A.ref_idx.idx = idx;'+CRLF+
''+CRLF+
'    if (top->Nodes.find(A.single) == top->Nodes.end())'+CRLF+
'       top->Nodes[A.single] = new __Node();'+CRLF+
'  };'+CRLF+
''+CRLF+
'  add_node(Src,  SrcIdx,  A1);'+CRLF+
'  add_node(Dest, DestIdx, A2);'+CRLF+
'  if (top->OutLinks.find(A1.single) == top->OutLinks.end())'+CRLF+
'     top->OutLinks[A1.single] = new __OutLinks();'+CRLF+
'  top->OutLinks[A1.single]->add_link(Dest, DestIdx);'+CRLF+
'  plan_unset_lock(__topo_lock__);'+CRLF+
'}'+CRLF+
''+CRLF+
'__Node * get_topology_link(int topo, void * Src, int Idx, input_proc Dest) {'+CRLF+
'  plan_set_lock(__topo_lock__);'+CRLF+
'  __Topology * top = __TopologyStack[topo];'+CRLF+
'  __Address_union A;'+CRLF+
''+CRLF+
'  A.ref_idx.ref = (unsigned long long)Src & 0xFFFFFFFF;'+CRLF+
'  A.ref_idx.idx = Idx;'+CRLF+
'  map<unsigned long long,__OutLinks *>::iterator itSrc = top->OutLinks.find(A.single);'+CRLF+
'  if (itSrc == top->OutLinks.end() || !itSrc->second->find_link(Dest)) {'+CRLF+
'     cout<<"Throw: Undefined link: "<<Src<<"["<<Idx<<"] to "<<input_addr(Dest)<<"["<<input_index(Dest)<<"]"<<endl;'+CRLF+
'     exit(-1);'+CRLF+
'  } {'+CRLF+
'     __Node * result = top->Nodes[Dest];'+CRLF+
'     plan_unset_lock(__topo_lock__);'+CRLF+
'     return result;'+CRLF+
'  }'+CRLF+
'}'+CRLF+
''+CRLF+
'void set_topology_tag(int topo, int tag) {'+CRLF+
'  plan_set_lock(__topo_lock__);'+CRLF+
'  __Topology * top = __TopologyStack[topo];'+CRLF+
'  top->set_topology_tag(tag);'+CRLF+
'  plan_unset_lock(__topo_lock__);'+CRLF+
'}'+CRLF+
''+CRLF+
'int get_topology_tag(int topo) {'+CRLF+
'  int result;'+CRLF+
'  plan_set_lock(__topo_lock__);'+CRLF+
'  __Topology * top = __TopologyStack[topo];'+CRLF+
'  result = top->get_topology_tag();'+CRLF+
'  plan_unset_lock(__topo_lock__);'+CRLF+
'  return result;'+CRLF+
'}'+CRLF+
''+CRLF+
'void __plan_neighbours(int topo, bool incoming, input_proc Ref, int * n, input_proc * refs) {'+CRLF+
'  plan_set_lock(__topo_lock__);'+CRLF+
'  __Topology * top = __TopologyStack[topo];'+CRLF+
''+CRLF+
'  if (incoming) {'+CRLF+
'     map<unsigned long long,__OutLinks *>::iterator it = top->OutLinks.begin();'+CRLF+
'     *n = 0;'+CRLF+
'     for (; it != top->OutLinks.end(); it++)'+CRLF+
'         if (it->second->find_link(Ref))'+CRLF+
'            refs[(*n)++] = it->first;'+CRLF+
'  } else {'+CRLF+
'     map<unsigned long long,__OutLinks *>::iterator it = top->OutLinks.find(Ref);'+CRLF+
'     if (it != top->OutLinks.end()) {'+CRLF+
'        it->second->export_links(n, refs);'+CRLF+
'     } else {'+CRLF+
'        *n = 0;'+CRLF+
'     }'+CRLF+
'  }'+CRLF+
''+CRLF+
'  plan_unset_lock(__topo_lock__);'+CRLF+
'}'+CRLF+
''+CRLF+
'char __add_group_node(int topo, const char * GroupID, void * Src, int Idx, void * __event_list__,'+CRLF+
'                      plan_lock_t * __plan_lock__, __reent_event * __signaler__) {'+CRLF+
'  plan_set_lock(__topo_lock__);'+CRLF+
'  __Topology * top = __TopologyStack[topo];'+CRLF+
'  __Address_union A;'+CRLF+
''+CRLF+
'  A.ref_idx.ref = (unsigned long long)Src & 0xFFFFFFFF;'+CRLF+
'  A.ref_idx.idx = Idx;'+CRLF+
''+CRLF+
'  if (top->Groups.find(GroupID) == top->Groups.end())'+CRLF+
'     top->Groups[GroupID] = new __Group();'+CRLF+
'  top->Groups[GroupID]->add_node(top->Nodes[A.single], __event_list__, __plan_lock__, __signaler__);'+CRLF+
'  char result = top->get_parallelize();'+CRLF+
'#ifdef __REENT_MPI__'+CRLF+
'  if (top->clustered) {'+CRLF+
'     __group_struct gs;'+CRLF+
'     memmove(gs.group, GroupID, strlen(GroupID)+1);'+CRLF+
'     gs.command = gcAddGroupNode;'+CRLF+
''+CRLF+
'     map<unsigned long long,__Node *>::iterator itNodes;'+CRLF+
'     for (itNodes = top->Nodes.begin(); itNodes != top->Nodes.end(); itNodes++)'+CRLF+
'         if (itNodes->second->id != __cluster_id__)'+CRLF+
'            MPI_Send(&gs, sizeof(gs), MPI_BYTE, itNodes->second->id, 1236, MPI_COMM_WORLD);'+CRLF+
'  }'+CRLF+
'#endif'+CRLF+
'  plan_unset_lock(__topo_lock__);'+CRLF+
'  return result;'+CRLF+
'}'+CRLF+
''+CRLF+
'void __set_node_id(int topo, void * Src, int Idx, int omp_id) {'+CRLF+
'  plan_set_lock(__topo_lock__);'+CRLF+
'  __Topology * top = __TopologyStack[topo];'+CRLF+
'  __Address_union A;'+CRLF+
''+CRLF+
'  A.ref_idx.ref = (unsigned long long)Src & 0xFFFFFFFF;'+CRLF+
'  A.ref_idx.idx = Idx;'+CRLF+
''+CRLF+
'  if (top->Nodes.size() > 0)'+CRLF+
'     if (top->Nodes.find(A.single) == top->Nodes.end()) {'+CRLF+
'        cout<<"Probably isolated node in topology "<<Src<<"["<<Idx<<"]"<<endl;'+CRLF+
'        exit(-1);'+CRLF+
'     } else'+CRLF+
'        top->Nodes[A.single]->id = omp_id;'+CRLF+
'  else {'+CRLF+
'     cout<<"Warning: single or isolated node in topology "<<Src<<"["<<Idx<<"]"<<endl;'+CRLF+
'     top->Nodes[A.single] = new __Node();'+CRLF+
'     top->Nodes[A.single]->id = omp_id;'+CRLF+
'  }'+CRLF+
'  top->Barrier++;'+CRLF+
'  top->nBarrier++;'+CRLF+
'  plan_unset_lock(__topo_lock__);'+CRLF+
'}'+CRLF+
''+CRLF+
'int __get_next_node_id(int topo, void * Src, int Idx) {'+CRLF+
'  int result = -1;'+CRLF+
'  plan_set_lock(__topo_lock__);'+CRLF+
'  __Topology * top = __TopologyStack[topo];'+CRLF+
'  __Address_union A;'+CRLF+
''+CRLF+
'  A.ref_idx.ref = (unsigned long long)Src & 0xFFFFFFFF;'+CRLF+
'  A.ref_idx.idx = Idx;'+CRLF+
'  map<unsigned long long,__OutLinks *>::iterator itSrc = top->OutLinks.find(A.single);'+CRLF+
'  if (itSrc != top->OutLinks.end()) {'+CRLF+
'    unsigned long long next_node = itSrc->second->get_single_link();'+CRLF+
'    result = next_node == 0 ? -1 : top->Nodes[next_node]->id;'+CRLF+
'  }'+CRLF+
'  plan_unset_lock(__topo_lock__);'+CRLF+
'  return result;'+CRLF+
'}'+CRLF+
''+CRLF+
'int __get_next_node_id(int topo, int mpi_id, int & self_idx) {'+CRLF+
'  plan_set_lock(__topo_lock__);'+CRLF+
'  __Topology * top = __TopologyStack[topo];'+CRLF+
'  map<unsigned long long,__Node *>::iterator itNodes;'+CRLF+
''+CRLF+
'  self_idx = -1;'+CRLF+
'  for (itNodes = top->Nodes.begin(); itNodes != top->Nodes.end(); itNodes++)'+CRLF+
'      if (itNodes->second->id == mpi_id) {'+CRLF+
'         __Address_union A;'+CRLF+
'         A.single = itNodes->first;'+CRLF+
'         self_idx = A.ref_idx.idx;'+CRLF+
'         plan_unset_lock(__topo_lock__);'+CRLF+
'         return __get_next_node_id(topo, reinterpret_cast<void *>(A.ref_idx.ref), A.ref_idx.idx);'+CRLF+
'      }'+CRLF+
'  plan_unset_lock(__topo_lock__);'+CRLF+
'  return -1;'+CRLF+
'}'+CRLF+
''+CRLF+
'void __pop_topology(int topo) {'+CRLF+
'  plan_set_lock(__topo_lock__);'+CRLF+
'  delete __TopologyStack[topo];'+CRLF+
'  __TopologyStack[topo] = NULL;'+CRLF+
'  plan_unset_lock(__topo_lock__);'+CRLF+
'}'+CRLF+
'#endif';

Implementation

Uses SysUtils, Lexique;

Function GenerateTopology(IsTopological: Boolean {True for topology};
                          Const ClusteredArrID: String;
                          Const Parallelize {'1+2' for topology},
                                ChainInit {'1' for topology}: String;
                          NProcs: String;
                          Const VectorNum {'0' for topology}: String;
                          ChainIsVector: Boolean {False for topology};
                          Chain, ChainItems: TStringList;
                          Const Links: TLinks
): String;
// Chain = [ProcedureID] -> Ldecl #0 Lparm
// ChainItems = [ProcedureCall] -> index of call
Var L: TAnalyser;
    Ldecl, Lparm: String;
    ChainInitPrm: String;
    LL: TLink;
    ID: String;
    H,K: Integer;
Begin
  L:=TAnalyser.Create(IdentSet,[Space,Tabulation]);
  Result := '';
  If Length(ClusteredArrID) > 0 Then
     Result:=Result+'#ifdef __REENT_MPI__'+CRLF+
                    'if ((int *)'+ClusteredArrID+' == NULL)'+CRLF+
                    '#endif'+CRLF;
  Result:=Result+'do {;'+CRLF;
  If IsTopological Then
     Result:=Result+'char __chain_init__  = 1;'+CRLF
  Else
     Result:=Result+'char __chain_init__  = '+ChainInit+';'+CRLF;
  Result:=Result+'#ifdef _OPENMP'+CRLF;
  Result:=Result+'char __parallelize__ = '+Parallelize+'/* && !omp_in_parallel() */;'+CRLF;
  Result:=Result+'if (__parallelize__ && __chain_init__) __parallelize__ += 4;'+CRLF;
  Result:=Result+'#else'+CRLF;
  If IsTopological Then
     Result:=Result+'#error Topology does not work in non-parallel mode'+CRLF
  Else
     Result:=Result+'char __parallelize__ = 0;'+CRLF;
  Result:=Result+'#endif'+CRLF;
  Result:=Result+'int __nthreads__    = __parallelize__ ? ';
  If Length(NProcs) > 0 Then
     Result:=Result+NProcs
  Else If ChainIsVector Then
     Result:=Result+VectorNum
  Else
     Result:=Result+IntToStr(ChainItems.Count);
  Result:=Result+' : 1;'+CRLF;
  Result:=Result+'int __i__;'+CRLF;
  With ChainItems Do
    If Count>0 Then
      Begin
        For H:=0 To Count-1 Do
          Begin
            L.AnlzLine:=Strings[H];
            ID:=L.GetBefore(True,[LeftBracket]);
            K:=_IndexOf(Chain, ID);
            If K<0 Then
               L.MakeError('"'+ID+'" is not declared as a throwing procedure')
            Else
               Begin
                 Ldecl:=PString(Chain.Objects[K])^;
                 K:=Pos(#0,Ldecl);
                 Lparm:=Copy(Ldecl,K+1,Length(Ldecl));
                 Ldecl:=Copy(Ldecl,1,K-1)
               End;
            If Not ChainIsVector Then
               Result:=Result+Ldecl+'<_params_'+ID+'> __LIST__'+IntToStr(H)+' = '+Ldecl+'<_params_'+ID+'>'+Lparm+';'+CRLF;
          End;
        If ChainIsVector Then
           Begin
             Result:=Result+'int __N__ = '+VectorNum+';'+CRLF;
             Result:=Result+'void ** __LIST__ = (void **) malloc(sizeof(void *)*__N__);'+CRLF;
             Result:=Result+'for (__i__=0; __i__<__N__; __i__++)'+CRLF;
             Result:=Result+'    __LIST__[__i__] = new '+Ldecl+'<_params_'+ID+'>'+Lparm+';'+CRLF
           End
        Else
           Begin
             Result:=Result+'void * __LIST__['+IntToStr(Count)+'] = {';
             For H:=0 To Count-1 Do
                 Result:=Result+'&__LIST__'+IntToStr(H)+',';
             Result[Length(Result)] := '}';
             Result:=Result+';'+CRLF
           End;
        Result:=Result+'#ifdef _OPENMP'+CRLF;
        Result:=Result+'int __counter__ = 0;'+CRLF;
        Result:=Result+'omp_lock_t __counter_lock__;'+CRLF;
        Result:=Result+'omp_init_lock(&__counter_lock__);'+CRLF;
        If ChainIsVector Then
           Begin
             Result:=Result+'plan_lock_t * __LOCKS__ = (plan_lock_t *) malloc(sizeof(plan_lock_t)*__N__);'+CRLF;
             Result:=Result+'__reent_event * __SIGNALERS__ = (__reent_event *) malloc(sizeof(__reent_event)*__N__);'+CRLF;
             Result:=Result+'for (__i__ = 0; __i__ < __N__; __i__++)'+CRLF;
             Result:=Result+'    {'+CRLF;
             Result:=Result+'     plan_init_lock(&__LOCKS__[__i__]);'+CRLF;
             Result:=Result+'     __init_reent_event(&__SIGNALERS__[__i__]);'+CRLF;
             Result:=Result+'    }'+CRLF;
             Result:=Result+'int topo = __push_topology(__parallelize__, &__counter__, &__counter_lock__, false);'+CRLF;
             Result:=Result+'for (__i__ = 0; __i__ < __N__-1; __i__++)'+CRLF;
             Result:=Result+'    __add_topology_link(topo,reinterpret_cast<void *>(&_call_'+ID+'), __i__+1, reinterpret_cast<void *>(&_call_'+ID+'), __i__+2);'+CRLF;
             Result:=Result+'for (__i__ = 0; __i__ < __N__; __i__++)'+CRLF;
             Result:=Result+'    __set_node_id(topo,reinterpret_cast<void *>(&_call_'+ID+'),__i__+1,__i__);'+CRLF;
             Result:=Result+'#pragma omp parallel for schedule(static,1) num_threads(__nthreads__) if(__parallelize__)'+CRLF;
             L.AnlzLine:=Strings[0];
             ID:=L.GetBefore(True,[LeftBracket]);
             Result:=Result+'for (__i__ = 0; __i__ < __N__; __i__++) {'+CRLF;
             Result:=Result+'     int id = omp_get_thread_num();'+CRLF;
             Result:=Result+'     __chain_call_'+ID+'__(id,__parallelize__,__chain_init__ || id==0, __LIST__[id],&__LOCKS__[id],'+
                    '&__SIGNALERS__[id],id==__N__-1 ? NULL : &__SIGNALERS__[id+1],id==__N__-1 ? NULL : __LIST__[id+1],id==__N__-1 ? NULL : &__LOCKS__[id+1]';
             Result:=Result+',&__counter__,&__counter_lock__';
             L.Check(LeftBracket);
             If Not L.IsNext(RightBracket) Then
                Result:=Result+',('+L.GetBalancedListItem(False,[Comma,RightBracket])+')+((topo<<10)&0x7C00)+((id+1)<<17)+0x8000';
             Result:=Result+L.AnlzLine+';'+CRLF;
             Result:=Result+'    }'+CRLF;
             Result:=Result+'__pop_topology(topo);'+CRLF;
             Result:=Result+'for (__i__=0; __i__<__N__; __i__++)'+CRLF;
             Result:=Result+'    delete reinterpret_cast<'+Ldecl+'<_params_'+ID+'> *>(__LIST__[__i__]);'+CRLF;
             Result:=Result+'free(__LIST__);'+CRLF;
           End
        Else
           Begin
             Result:=Result+'plan_lock_t __LOCKS__['+IntToStr(Count)+'];'+CRLF;
             Result:=Result+'__reent_event __SIGNALERS__['+IntToStr(Count)+'];'+CRLF;
             Result:=Result+'for (__i__ = 0; __i__ < '+IntToStr(Count)+'; __i__++)'+CRLF;
             Result:=Result+'    {'+CRLF;
             Result:=Result+'     plan_init_lock(&__LOCKS__[__i__]);'+CRLF;
             Result:=Result+'     __init_reent_event(&__SIGNALERS__[__i__]);'+CRLF;
             Result:=Result+'    }'+CRLF;
             Result:=Result+'int topo = __push_topology(__parallelize__, &__counter__, &__counter_lock__, false);'+CRLF;
             If IsTopological Then
                For H:=0 To Length(Links)-1 Do
                    Begin
                      LL := Links[H];
                      L.AnlzLine := Strings[LL.First];
                      ID:=L.GetIdent(False);
                      Result:=Result+'__add_topology_link(topo,reinterpret_cast<void *>(&_call_'+ID+'),'+IntToStr(TObjectToInteger(Objects[LL.First]))+', ';
                      L.AnlzLine := Strings[LL.Last];
                      ID:=L.GetIdent(False);
                      Result:=Result+'reinterpret_cast<void *>(&_call_'+ID+'),'+IntToStr(TObjectToInteger(Objects[LL.Last]))+');'+CRLF;
                    End
             Else
               For H:=0 To Count-2 Do
                 Begin
                   L.AnlzLine:=Strings[H];
                   ID:=L.GetBefore(True,[LeftBracket]);
                   L.AnlzLine:=Strings[H+1];
                   Result:=Result+'__add_topology_link(topo,reinterpret_cast<void *>(&_call_'+ID+'),'+IntToStr(TObjectToInteger(Objects[H]))+', reinterpret_cast<void *>(&_call_'+L.GetBefore(True,[LeftBracket])+'),'+IntToStr(TObjectToInteger(Objects[H+1]))+');'+CRLF;
                 End;
             For H:=0 To Count-1 Do
                 Begin
                   L.AnlzLine:=Strings[H];
                   ID:=L.GetBefore(False,[LeftBracket]);
                   Result:=Result+'__set_node_id(topo,reinterpret_cast<void *>(&_call_'+ID+'),'+IntToStr(TObjectToInteger(Objects[H]))+','+IntToStr(H)+');'+CRLF
                 End;
             Result:=Result+'#pragma omp parallel for num_threads(__nthreads__) if(__parallelize__)'+CRLF;
             Result:=Result+'for (__i__=0; __i__ < '+IntToStr(Count)+'; __i__++)'+CRLF;
             Result:=Result+' switch (__i__) {'+CRLF;
             For H:=0 To Count-1 Do
               Begin
                 L.AnlzLine:=Strings[H];
                 ID:=L.GetBefore(True,[LeftBracket]);
                 L.Check(LeftBracket);
                 If H=0 Then
                    ChainInitPrm:='1'
                 Else
                    ChainInitPrm:='__chain_init__';
                 If IsTopological Then
                    Begin
                      Result:=Result+'  case '+IntToStr(H)+': {'+CRLF;
                      Result:=Result+'    int next_id = __get_next_node_id(topo,reinterpret_cast<void *>(&_call_'+ID+'),'+IntToStr(TObjectToInteger(Objects[H]))+');'+CRLF;
                      Result:=Result+'    __chain_call_'+ID+'__('+IntToStr(H)+',__parallelize__,'+ChainInitPrm+',__LIST__['+IntToStr(H)+'],&__LOCKS__['+IntToStr(H)+'],';
                      Result:=Result+'&__SIGNALERS__['+IntToStr(H)+'],';
                      Result:=Result+'next_id < 0 ? NULL : &__SIGNALERS__[next_id],';
                      Result:=Result+'next_id < 0 ? NULL : __LIST__[next_id],';
                      Result:=Result+'next_id < 0 ? NULL : &__LOCKS__[next_id]';
                      Result:=Result+',&__counter__,&__counter_lock__';
                      If Not L.IsNext(RightBracket) Then
                         Result:=Result+',('+L.GetBalancedListItem(False,[Comma,RightBracket])+')+((topo<<10)&0x7C00)+(('+IntToStr(TObjectToInteger(Objects[H]))+')<<17)+0x8000';
                      Result:=Result+L.AnlzLine+';'+CRLF;
                      Result:=Result+'    break;'+CRLF;
                      Result:=Result+'  }'+CRLF
                    End
                 Else
                    Begin
                      Result:=Result+'  case '+IntToStr(H)+': __chain_call_'+ID+'__('+IntToStr(H)+',__parallelize__,'+ChainInitPrm+',__LIST__['+IntToStr(H)+'],&__LOCKS__['+IntToStr(H)+'],';
                      If H=Count-1 Then
                         Result:=Result+'NULL,NULL,NULL,NULL'
                      Else
                         Result:=Result+'&__SIGNALERS__['+IntToStr(H)+'],&__SIGNALERS__['+IntToStr(H+1)+'],__LIST__['+IntToStr(H+1)+'],&__LOCKS__['+IntToStr(H+1)+']';
                      Result:=Result+',&__counter__,&__counter_lock__';
                      If Not L.IsNext(RightBracket) Then
                         Result:=Result+',('+L.GetBalancedListItem(False,[Comma,RightBracket])+')+((topo<<10)&0x7C00)+(('+IntToStr(TObjectToInteger(Objects[H]))+')<<17)+0x8000';
                      Result:=Result+L.AnlzLine+'; break;'+CRLF
                    End
               End;
             Result:=Result+' }'+CRLF;
             Result:=Result+'__pop_topology(topo);'+CRLF
           End;
        Result:=Result+'omp_destroy_lock(&__counter_lock__);'+CRLF;
        If ChainIsVector Then
           Result:=Result+'for (__i__ = 0; __i__ < __N__; __i__++)'+CRLF
        Else
           Result:=Result+'for (__i__ = 0; __i__ < '+IntToStr(Count)+'; __i__++)'+CRLF;
        Result:=Result+'    {'+CRLF;
        Result:=Result+'     plan_destroy_lock(&__LOCKS__[__i__]);'+CRLF;
        Result:=Result+'     __destroy_reent_event(&__SIGNALERS__[__i__]);'+CRLF;
        Result:=Result+'    }'+CRLF;
        If ChainIsVector Then
           Begin
             Result:=Result+'free(__LOCKS__);'+CRLF;
             Result:=Result+'free(__SIGNALERS__);'+CRLF
           End;
        If Not IsTopological Then
           Begin
              Result:=Result+'#else'+CRLF;
              If ChainIsVector Then
                 Begin
                   L.AnlzLine:=Strings[0];
                   ID:=L.GetBefore(True,[LeftBracket]);
                   Result:=Result+'for (__i__ = 0; __i__ < __N__; __i__++)'+CRLF;
                   Result:=Result+'    __chain_call_'+ID+'__(__N__,__i__,__chain_init__ || __i__==0, __LIST__[__i__],__i__==__N__-1 ? NULL : __LIST__[__i__+1]';
                   L.Check(LeftBracket);
                   If Not L.IsNext(RightBracket) Then
                      Result:=Result+',';
                   Result:=Result+L.AnlzLine+';'+CRLF;
                   Result:=Result+'for (__i__=0; __i__<__N__; __i__++)'+CRLF;
                   Result:=Result+'    delete reinterpret_cast<'+Ldecl+'<_params_'+ID+'> *>(__LIST__[__i__]);'+CRLF;
                   Result:=Result+'free(__LIST__);'+CRLF
                 End
              Else
                 For H:=0 To Count-1 Do
                   Begin
                     L.AnlzLine:=Strings[H];
                     ID:=L.GetBefore(True,[LeftBracket]);
                     L.Check(LeftBracket);
                       If H=0 Then
                          ChainInitPrm:='1'
                       Else
                          ChainInitPrm:='__chain_init__';
                     Result:=Result+'__chain_call_'+ID+'__('+IntToStr(Count)+','+IntToStr(H)+','+ChainInitPrm+',__LIST__['+IntToStr(H)+'],';
                     If H=Count-1 Then
                        Result:=Result+'NULL'
                     Else
                        Result:=Result+'__LIST__['+IntToStr(H+1)+']';
                     If Not L.IsNext(RightBracket) Then
                        Result:=Result+',';
                     Result:=Result+L.AnlzLine+';'+CRLF
                   End;
           End;
        Result:=Result+'#endif'+CRLF
      End;
  Result:=Result+'} while(0)'+CRLF;
  If Length(ClusteredArrID) > 0 Then
     Begin
       Result:=Result+'#ifdef __REENT_MPI__'+CRLF+
                      '; else'+CRLF;
       Result:=Result+'do {;'+CRLF;
       Result:=Result+'int * __ids = (int *) '+ClusteredArrID+';'+CRLF;
       If IsTopological Then
          Result:=Result+'char __chain_init__  = 1;'+CRLF
       Else
          Result:=Result+'char __chain_init__  = '+ChainInit+';'+CRLF;
       Result:=Result+'char __parallelize__ = '+Parallelize+';'+CRLF;
       Result:=Result+'if (__parallelize__ && __chain_init__) __parallelize__ += 4;'+CRLF;
       Result:=Result+'int __nprocesses__    = __parallelize__ ? ';
       If Length(NProcs) > 0 Then
          Begin
            WriteLn('Warning: "/'+NProcs+'" statement is ignored on clustered topology/chain/vector');
            NProcs := ''
          End;
       If ChainIsVector Then
          Result:=Result+VectorNum
       Else
          Result:=Result+IntToStr(ChainItems.Count);
       Result:=Result+' : 1;'+CRLF;
       With ChainItems Do
         If Count>0 Then
           Begin
             For H:=0 To Count-1 Do
               Begin
                 L.AnlzLine:=Strings[H];
                 ID:=L.GetBefore(True,[LeftBracket]);
                 K:=_IndexOf(Chain, ID);
                 If K<0 Then
                    L.MakeError('"'+ID+'" is not declared as a throwing procedure')
                 Else
                    Begin
                      Ldecl:=PString(Chain.Objects[K])^;
                      K:=Pos(#0,Ldecl);
                      Lparm:=Copy(Ldecl,K+1,Length(Ldecl));
                      Ldecl:=Copy(Ldecl,1,K-1)
                    End;
                 If Not ChainIsVector Then
                    Result:=Result+Ldecl+'<_params_'+ID+'> __LIST__'+IntToStr(H)+' = '+Ldecl+'<_params_'+ID+'>'+Lparm+';'+CRLF;
               End;
             If ChainIsVector Then
                Begin
                  Result:=Result+'int __i__;'+CRLF;
                  Result:=Result+'int __N__ = '+VectorNum+';'+CRLF;
                  Result:=Result+'void ** __LIST__ = (void **) malloc(sizeof(void *)*__N__);'+CRLF;
                  Result:=Result+'for (__i__=0; __i__<__N__; __i__++)'+CRLF;
                  Result:=Result+'    __LIST__[__i__] = new '+Ldecl+'<_params_'+ID+'>'+Lparm+';'+CRLF
                End
             Else
                Begin
                  Result:=Result+'void * __LIST__['+IntToStr(Count)+'] = {';
                  For H:=0 To Count-1 Do
                      Result:=Result+'&__LIST__'+IntToStr(H)+',';
                  Result[Length(Result)] := '}';
                  Result:=Result+';'+CRLF
                End;
             If ChainIsVector Then
                Begin
                  Result:=Result+'plan_lock_t __LOCK__;'+CRLF;
                  Result:=Result+'plan_init_lock(&__LOCK__);'+CRLF;
                  Result:=Result+'int topo = __push_topology(__parallelize__, NULL, NULL, true);'+CRLF;
                  Result:=Result+'for (__i__ = 0; __i__ < __N__-1; __i__++)'+CRLF;
                  Result:=Result+'    __add_topology_link(topo,reinterpret_cast<void *>(&_call_'+ID+'), __i__+1, reinterpret_cast<void *>(&_call_'+ID+'), __i__+2);'+CRLF;
                  Result:=Result+'for (__i__ = 0; __i__ < __N__; __i__++)'+CRLF;
                  Result:=Result+'    __set_node_id(topo,reinterpret_cast<void *>(&_call_'+ID+'),__i__+1,__ids[__i__]);'+CRLF;
                  L.AnlzLine:=Strings[0];
                  ID:=L.GetBefore(True,[LeftBracket]);
                  Result:=Result+'int stage = -1;'+CRLF;
                  Result:=Result+'for (int i = 0; stage < 0 && i < __nprocesses__; i++)'+CRLF;
                  Result:=Result+'    if (__cluster_id__ == __ids[i])'+CRLF;
                  Result:=Result+'       stage = i;'+CRLF;
                  Result:=Result+'if (stage >= 0) {'+CRLF;
                  Result:=Result+'   int tag_base;'+CRLF;
                  Result:=Result+'   if (__cluster_id__ == __ids[0]) {'+CRLF;
                  Result:=Result+'      do {'+CRLF;
                  Result:=Result+'        tag_base = rand() & 0xFFFFFFFC;'+CRLF;
                  Result:=Result+'      } while (tag_base >= 1232 && tag_base < 1240);'+CRLF;
                  Result:=Result+'      for (int i = 1; i < __nprocesses__; i++)'+CRLF;
                  Result:=Result+'          MPI_Ssend(&tag_base, 1, MPI_INT, __ids[i], 1234, MPI_COMM_WORLD);'+CRLF;
                  Result:=Result+'   } else {'+CRLF;
                  Result:=Result+'      MPI_Status status;'+CRLF;
                  Result:=Result+'      MPI_Recv(&tag_base, 1, MPI_INT, __ids[0], 1234, MPI_COMM_WORLD, &status);'+CRLF;
                  Result:=Result+'   }'+CRLF;
                  Result:=Result+'   int self_linear_num;'+CRLF;
                  Result:=Result+'   set_topology_tag(topo, tag_base);'+CRLF;
                  Result:=Result+'   int mpi_next_id = __get_next_node_id(topo,__cluster_id__,self_linear_num);'+CRLF;
                  Result:=Result+'   mpi__chain_call_'+ID+'__(stage,__parallelize__,__chain_init__ || stage==0, __LIST__[stage],&__LOCK__,'+
                         'NULL,NULL,reinterpret_cast<void *>(mpi_next_id),NULL,tag_base';
                  L.Check(LeftBracket);
                  If Not L.IsNext(RightBracket) Then
                     Result:=Result+',('+L.GetBalancedListItem(False,[Comma,RightBracket])+')+((topo<<10)&0x7C00)+((self_linear_num)<<17)+0x10000';
                  Result:=Result+L.AnlzLine+';'+CRLF;
                  Result:=Result+'};'+CRLF;
                  Result:=Result+'__pop_topology(topo);'+CRLF;
                  Result:=Result+'for (__i__=0; __i__<__N__; __i__++)'+CRLF;
                  Result:=Result+'    delete reinterpret_cast<'+Ldecl+'<_params_'+ID+'> *>(__LIST__[__i__]);'+CRLF;
                  Result:=Result+'free(__LIST__);'+CRLF;
                End
             Else
                Begin
                  Result:=Result+'plan_lock_t __LOCK__;'+CRLF;
                  Result:=Result+'plan_init_lock(&__LOCK__);'+CRLF;
                  Result:=Result+'int topo = __push_topology(__parallelize__, NULL, NULL, true);'+CRLF;
                  If IsTopological Then
                     For H:=0 To Length(Links)-1 Do
                         Begin
                           LL := Links[H];
                           L.AnlzLine := Strings[LL.First];
                           ID:=L.GetIdent(False);
                           Result:=Result+'__add_topology_link(topo,reinterpret_cast<void *>(&_call_'+ID+'),'+IntToStr(TObjectToInteger(Objects[LL.First]))+', ';
                           L.AnlzLine := Strings[LL.Last];
                           ID:=L.GetIdent(False);
                           Result:=Result+'reinterpret_cast<void *>(&_call_'+ID+'),'+IntToStr(TObjectToInteger(Objects[LL.Last]))+');'+CRLF;
                         End
                  Else
                    For H:=0 To Count-2 Do
                      Begin
                        L.AnlzLine:=Strings[H];
                        ID:=L.GetBefore(True,[LeftBracket]);
                        L.AnlzLine:=Strings[H+1];
                        Result:=Result+'__add_topology_link(topo,reinterpret_cast<void *>(&_call_'+ID+'),'+IntToStr(TObjectToInteger(Objects[H]))+', reinterpret_cast<void *>(&_call_'+L.GetBefore(True,[LeftBracket])+'),'+IntToStr(TObjectToInteger(Objects[H+1]))+');'+CRLF;
                      End;
                  For H:=0 To Count-1 Do
                      Begin
                        L.AnlzLine:=Strings[H];
                        ID:=L.GetBefore(False,[LeftBracket]);
                        Result:=Result+'__set_node_id(topo,reinterpret_cast<void *>(&_call_'+ID+'),'+IntToStr(TObjectToInteger(Objects[H]))+',__ids['+IntToStr(H)+']);'+CRLF
                      End;
                  Result:=Result+'int stage = -1;'+CRLF;
                  Result:=Result+'for (int i = 0; stage < 0 && i < __nprocesses__; i++)'+CRLF;
                  Result:=Result+'    if (__cluster_id__ == __ids[i])'+CRLF;
                  Result:=Result+'       stage = i;'+CRLF;
                  Result:=Result+'if (stage >= 0) {'+CRLF;
                  Result:=Result+'   int tag_base;'+CRLF;
                  Result:=Result+'   if (__cluster_id__ == __ids[0]) {'+CRLF;
                  Result:=Result+'      do {'+CRLF;
                  Result:=Result+'        tag_base = rand() & 0xFFFFFFFC;'+CRLF;
                  Result:=Result+'      } while (tag_base >= 1232 && tag_base < 1240);'+CRLF;
                  Result:=Result+'      for (int i = 1; i < __nprocesses__; i++)'+CRLF;
                  Result:=Result+'          MPI_Ssend(&tag_base, 1, MPI_INT, __ids[i], 1234, MPI_COMM_WORLD);'+CRLF;
                  Result:=Result+'   } else {'+CRLF;
                  Result:=Result+'      MPI_Status status;'+CRLF;
                  Result:=Result+'      MPI_Recv(&tag_base, 1, MPI_INT, __ids[0], 1234, MPI_COMM_WORLD, &status);'+CRLF;
                  Result:=Result+'   }'+CRLF;
                  Result:=Result+'   int self_linear_num;'+CRLF;
                  Result:=Result+'   set_topology_tag(topo, tag_base);'+CRLF;
                  Result:=Result+'   int mpi_next_id = __get_next_node_id(topo,__cluster_id__,self_linear_num);'+CRLF;
                  Result:=Result+'   switch (stage) {'+CRLF;
                  For H:=0 To Count-1 Do
                    Begin
                      L.AnlzLine:=Strings[H];
                      ID:=L.GetBefore(True,[LeftBracket]);
                      L.Check(LeftBracket);
                      If H=0 Then
                         ChainInitPrm:='1'
                      Else
                         ChainInitPrm:='__chain_init__';
                      Result:=Result+'     case '+IntToStr(H)+': mpi__chain_call_'+ID+'__(stage,__parallelize__,'+ChainInitPrm+',__LIST__[stage],&__LOCK__,';
                      Result:=Result+'NULL,NULL,reinterpret_cast<void *>(mpi_next_id),NULL';
                      Result:=Result+',tag_base';
                      If Not L.IsNext(RightBracket) Then
                         Result:=Result+',('+L.GetBalancedListItem(False,[Comma,RightBracket])+')+((topo<<10)&0x7C00)+((self_linear_num)<<17)+0x10000';
                      Result:=Result+L.AnlzLine+'; break;'+CRLF
                    End;
                  Result:=Result+'   }'+CRLF;
                  Result:=Result+'};'+CRLF;
                  Result:=Result+'__pop_topology(topo);'+CRLF
                End;
             Result:=Result+'plan_destroy_lock(&__LOCK__);'+CRLF
           End;
       Result:=Result+'} while(0)'+CRLF;
       Result:=Result+'#endif'+CRLF
     End;
  L.Free
End;

Procedure CreateTopology(Var Out: TextFile; Const ClusteredArrID: String; Chain, Topology: TStringList; NProcs: String);

Var L, L1:TAnalyser;
    ID, Params, NP, Dir: String;
    Idx: Real;
    nItems, MaxItems: Integer;
    Reverse: Boolean;
    ChainItems: TStringList;
    Links: TLinks;
    PassedNodes, VisitedNodes: Array Of Boolean;
    LineNum: Integer;
    nLinks: Integer;
    Wave0, Wave1: Array Of Integer;
    Found, Dupl: Boolean;
    Prev: Integer;
    F,G,K,N:Integer;
Begin
  L := TAnalyser.Create(IdentSet,[Space,Tabulation]);
  L1 := TAnalyser.Create(IdentSet,[Space,Tabulation]);
  ChainItems := TStringList.Create;
  nLinks := 0;
  SetLength(Links, 0);
  With Topology Do
    For F := 0 To Count-1 Do
      Begin
        L.AnlzLine := Strings[F];
        LineNum := TObjectToInteger(Objects[F]);
        Dir := L.GetIdent(True);
        If Dir = idplan_parallel_chain Then
           Begin
             MaxItems := MaxInt;
             Reverse := False
           End
        Else If Dir = idplan_parallel_reverse Then
           Begin
             MaxItems := 2;
             Reverse := True
           End
        Else
           Begin
             WriteLn('''',idplan_parallel_chain,''' or ''',idplan_parallel_reverse,''' expected',TLine(Lines.Objects[LineNum-1]).GetDescription);
             Halt(-1)
           End;
        L.Check(LeftBracket);
        nItems := 0;
        Prev := -1;
        While Not (L.IsNext(RightBracket) Or L.Empty Or L.Error Or (nItems > MaxItems)) Do
          Begin
            ID := L.GetIdent(False);
            If L.IsNext(LeftSqrBracket) Then
               Begin
                 L.Check(LeftSqrBracket);
                 Idx := 0.0;
                 L.GetNumber(True, Idx);
                 L.Check(RightSqrBracket)
               End
            Else
               Idx := 1.0;
            L.DelSpaces;
            Params := L.GetBalancedListItem(False,[Slash,Comma,Dash,RightBracket]);
            If L.IsNext(Slash) Then
               Begin
                 L.Check(Slash);
                 NP := L.GetBalancedListItem(False,[Comma,Dash,RightBracket])
               End
            Else
               NP := '0';
            If L.IsNext(Comma) Then
               L.Check(Comma)
            Else If L.IsNext(Dash) Then
               Begin
                 L.Check(Dash); L.Check(Greater)
               End
            Else If Not L.IsNext(RightBracket) Then
               Begin
                 L.Check(RightBracket);
                 Halt(-1)
               End;
            If (Length(Params)>1) And (Params[1] = LeftBracket) Then
               If Length(Params) = 2 Then
                  System.Insert(NP, Params, 2)
               Else
                   System.Insert(NP+',', Params, 2)
            Else
               Begin
                 WriteLn('Parameter list of ''',ID,''' is incorrect',TLine(Lines.Objects[LineNum-1]).GetDescription);
                 Halt(-1)
               End;
            Found := False;
            G := 0;
            While (G < ChainItems.Count) And Not Found Do
              Begin
                L1.AnlzLine := ChainItems.Strings[G];
                If (L1.GetIdent(False) = ID) And (Round(Idx) = TObjectToInteger(ChainItems.Objects[G])) Then
                   Found := True
                Else
                  Inc(G)
              End;
            If Not Found Then
               G := ChainItems.AddObject(ID+Params,IntegerToTObject(Integer(Round(Idx))));
            If Prev >= 0 Then
               Begin
                 If nLinks = Length(Links) Then
                    SetLength(Links, nLinks+10);
                 Links[nLinks].First := Prev;
                 Links[nLinks].Last := G;
                 Links[nLinks].Rev := Reverse;
                 Inc(nLinks)
               End;
            Prev := G;
            Inc(nItems)
          End;
        If nItems > MaxItems Then
           Begin
             WriteLn(Dir,' can''t contain more than ', MaxItems, ' calls',TLine(Lines.Objects[LineNum-1]).GetDescription);
             Halt(-1)
           End;
        L.Check(RightBracket)
      End;
  SetLength(Links, nLinks);
  // Check cycles without reverse edges
  SetLength(VisitedNodes, ChainItems.Count);
  SetLength(PassedNodes, ChainItems.Count);
  For F := 0 To ChainItems.Count-1 Do
      VisitedNodes[F] := False;
  Repeat
    F := 0;
    Found := False;
    While (F < Length(VisitedNodes)) And Not Found Do
      If VisitedNodes[F] Then
         Inc(F)
      Else
         Found := True;
    If Found Then
       Begin
         SetLength(Wave0, 1);
         Wave0[0] := F;
         VisitedNodes[F] := True;
         For G := 0 To ChainItems.Count-1 Do
             PassedNodes[G] := False;
         PassedNodes[F] := True;
         While Length(Wave0) > 0 Do
           Begin
              N := 0;
              SetLength(Wave1, 100);
              For F := 0 To Length(Wave0)-1 Do
                  Begin
                    For G := 0 To nLinks-1 Do
                        If Not Links[G].Rev Then
                           If Links[G].First = Wave0[F] Then
                              Begin
                                K := 0;
                                Dupl := False;
                                While (K < N) And Not Dupl Do
                                  If Wave1[K] = Links[G].Last Then
                                     Dupl := True
                                  Else
                                     Inc(K);
                                If Not Dupl Then
                                   If PassedNodes[Links[G].Last] Then
                                      Begin
                                        WriteLn('Topology: ',
                                                ChainItems.Strings[Links[G].First],'[',TObjectToInteger(ChainItems.Objects[Links[G].First]),']->',
                                                ChainItems.Strings[Links[G].Last],'[',TObjectToInteger(ChainItems.Objects[Links[G].Last]),']',
                                                ' is not marked as reverse. Loop detected');
                                        Halt(-1)
                                      End
                                   Else
                                      Begin
                                        If N = Length(Wave1) Then
                                           SetLength(Wave1, N+100);
                                        Wave1[N] := Links[G].Last;
                                        Inc(N)
                                      End
                              End
                  End;
              For F := 0 To N-1 Do
                  Begin
                    VisitedNodes[Wave1[F]] := True;
                    PassedNodes[Wave1[K]] := True
                  End;
              SetLength(Wave0, N);
              For F := 0 To N-1 Do
                  Wave0[F] := Wave1[F]
           End
       End
  Until Not Found;
  // Generate
  If Length(NProcs) = 0 Then
     NProcs := IntToStr(ChainItems.Count);
  WriteLn(Out, GenerateTopology(True, ClusteredArrID, '(1+2)', '1',
                         NProcs, '0', False,
                         Chain, ChainItems,
                         Links)
  );
  L.Free;
  L1.Free;
  ChainItems.Free
End;

End.
