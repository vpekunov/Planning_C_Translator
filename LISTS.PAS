Const CircularList: PChar =
'template<class Type>'+CRLF+
'  class circular_list : public __abstract_list<Type> {'+CRLF+
'    protected:'+CRLF+
'      Type * Data;'+CRLF+
'      volatile int Begin;'+CRLF+
'      volatile int End;'+CRLF+
'      int    N;'+CRLF+
'    public:'+CRLF+
'      struct iterator {'+CRLF+
'        friend class circular_list<Type>;'+CRLF+
'        protected:'+CRLF+
'          circular_list<Type> * Ref;'+CRLF+
'          volatile int Position;'+CRLF+
'        public:'+CRLF+
'          iterator() {};'+CRLF+
'          iterator(circular_list<Type> * _Ref, int _Position) : Ref(_Ref), Position(_Position) {};'+CRLF+
'          Type& operator * () { return Ref->Data[Position]; };'+CRLF+
'          iterator& operator ++ () { Position = (Position+1)%Ref->N; return *this; };'+CRLF+
'          iterator& operator -- () { Position = (Position+Ref->N-1)%Ref->N; return *this; };'+CRLF+
'          int  operator - (const iterator V) { return (Position-V.Position+Ref->N)%Ref->N; };'+CRLF+
'          bool operator == (const iterator V) { return Ref==V.Ref && Position==V.Position; };'+CRLF+
'          bool operator != (const iterator V) { return Ref!=V.Ref || Position!=V.Position; };'+CRLF+
'      };'+CRLF+
'      circular_list(): __abstract_list<Type>(0, NULL, NULL) {'+CRLF+
'        N = 10;'+CRLF+
'        Data  = new Type[N];'+CRLF+
'        Begin = N/2;'+CRLF+
'        End   = Begin;'+CRLF+
'      };'+CRLF+
'      circular_list(int nF, int * sF, int * oF): __abstract_list<Type>(nF, sF, oF) {'+CRLF+
'        N = 10;'+CRLF+
'        Data  = new Type[N];'+CRLF+
'        Begin = N/2;'+CRLF+
'        End   = Begin;'+CRLF+
'      };'+CRLF+
'      explicit circular_list(int _NN, int nF = 0, int * sF = NULL, int * oF = NULL): __abstract_list<Type>(nF, sF, oF) {'+CRLF+
'        N     = _NN+1;'+CRLF+
'        Data  = new Type[N];'+CRLF+
'        Begin = N/2;'+CRLF+
'        End   = Begin;'+CRLF+
'      };'+CRLF+
'      circular_list<Type>& operator =(const circular_list<Type> & obj) {'+CRLF+
'        this->nFields    = obj.nFields;'+CRLF+
'        this->sizeFields = obj.sizeFields;'+CRLF+
'        this->offsFields = obj.offsFields;'+CRLF+
'        N     = obj.N;'+CRLF+
'        Data  = new Type[N];'+CRLF+
'        for (int i = 0; i < N; i++) Data[i] = obj.Data[i];'+CRLF+
'        Begin = obj.Begin;'+CRLF+
'        End   = obj.End;'+CRLF+
'        return *this;'+CRLF+
'      };'+CRLF+
'      circular_list(const circular_list<Type> & obj): __abstract_list<Type>(obj) {'+CRLF+
'        N     = obj.N;'+CRLF+
'        Data  = new Type[N];'+CRLF+
'        for (int i = 0; i < N; i++) Data[i] = obj.Data[i];'+CRLF+
'        Begin = obj.Begin;'+CRLF+
'        End   = obj.End;'+CRLF+
'      }'+CRLF+
'      ~circular_list() { delete[] Data; };'+CRLF+
'      Type& operator [](int index) { return Data[(Begin+index)%N]; };'+CRLF+
'      const Type& operator [](int index) const { return Data[(Begin+index)%N]; };'+CRLF+
'      Type& front()    { return Data[Begin]; };'+CRLF+
'      Type& back()     { return Data[(End+N-1)%N]; };'+CRLF+
'      void pop_front() { Begin = (Begin+1)%N; };'+CRLF+
'      void pop_back()  { End = (End+N-1)%N; };'+CRLF+
'      void push_front(const Type Item) {'+CRLF+
'        if (empty()) push_back(Item);'+CRLF+
'        else Data[Begin = (Begin+N-1)%N] = Item;'+CRLF+
'      };'+CRLF+
'      void push_back(const Type Item)  { Data[End] = Item; End = (End+1)%N; };'+CRLF+
'      int  empty() { return End==Begin; };'+CRLF+
'      int  size()  { return (End-Begin+N)%N; };'+CRLF+
'      void clear() { End=Begin; };'+CRLF+
'      iterator erase(iterator Ptr) {'+CRLF+
'        int L = Ptr-begin();'+CRLF+
'        int R = (end()-Ptr)-1;'+CRLF+
'        if (L<R) {'+CRLF+
'           if (Ptr.Position>Begin) memmove(&Data[Begin+1],&Data[Begin],(Ptr.Position-Begin)*sizeof(Type));'+CRLF+
'           else if (Ptr.Position<Begin) {'+CRLF+
'             if (Ptr.Position>0) memmove(&Data[1],&Data[0],Ptr.Position*sizeof(Type));'+CRLF+
'             Data[0] = Data[N-1];'+CRLF+
'             if (Begin<N-1) memmove(&Data[Begin+1],&Data[Begin],((N-1)-Begin)*sizeof(Type));'+CRLF+
'           }'+CRLF+
'           pop_front();'+CRLF+
'           return ++Ptr;'+CRLF+
'        } else {'+CRLF+
'          pop_back();'+CRLF+
'          if (Ptr.Position<End) memmove(&Data[Ptr.Position],&Data[Ptr.Position+1],(End-Ptr.Position)*sizeof(Type));'+CRLF+
'          else if (Ptr.Position>End) {'+CRLF+
'            if (Ptr.Position<N-1) memmove(&Data[Ptr.Position],&Data[Ptr.Position+1],((N-1)-Ptr.Position)*sizeof(Type));'+CRLF+
'            Data[N-1] = Data[0];'+CRLF+
'            if (End>0) memmove(&Data[0],&Data[1],End*sizeof(Type));'+CRLF+
'          }'+CRLF+
'          return Ptr;'+CRLF+
'        }'+CRLF+
'      };'+CRLF+
'      iterator begin() { iterator Result = iterator(this,Begin); return Result; };'+CRLF+
'      iterator end()   { iterator Result = iterator(this,End); return Result; };'+CRLF+
'  };'+CRLF;

Const ReentList: PChar =
'#include <vector>'+CRLF+
'using namespace std;'+CRLF+
''+CRLF+
'typedef enum {li_int, li_uint, li_float, li_double, li_ldouble, li_str, li_array, li_empty} li_types;'+CRLF+
''+CRLF+
'typedef struct {'+CRLF+
'  li_types _vtype;'+CRLF+
'  int      _vdims;'+CRLF+
'  int      _vsize_item;'+CRLF+
'  int      _vsize_total;'+CRLF+
'  union {'+CRLF+
'    signed long long   _vint;'+CRLF+
'    unsigned long long _vuint;'+CRLF+
'    float              _vfloat;'+CRLF+
'    double             _vdouble;'+CRLF+
'    long double        _vldouble;'+CRLF+
'    const char *       _vstr;'+CRLF+
'    void *             _vpntr;'+CRLF+
'  };'+CRLF+
'} __list_item__;'+CRLF+
''+CRLF+
'class __obj_array__ {'+CRLF+
'  protected:'+CRLF+
'    __list_item__ * data;'+CRLF+
'  public:'+CRLF+
'    __obj_array__(void * arr, int dims, int size_item, int size_total) {'+CRLF+
'      data = new __list_item__;'+CRLF+
'      data->_vtype = li_array;'+CRLF+
'      data->_vdims = dims;'+CRLF+
'      data->_vsize_item = size_item;'+CRLF+
'      data->_vsize_total = size_total;'+CRLF+
'      data->_vpntr = arr;'+CRLF+
'    };'+CRLF+
'    __list_item__ * get_data() { return data; }'+CRLF+
'};'+CRLF+
''+CRLF+
'class __obj_var__ {'+CRLF+
'  protected:'+CRLF+
'    __list_item__ * data;'+CRLF+
'  public:'+CRLF+
'    __obj_var__(void * item, int size_item) {'+CRLF+
'      data = new __list_item__;'+CRLF+
'      data->_vtype = li_array;'+CRLF+
'      data->_vdims = 1;'+CRLF+
'      data->_vsize_item = size_item;'+CRLF+
'      data->_vsize_total = size_item;'+CRLF+
'      data->_vpntr = item;'+CRLF+
'    };'+CRLF+
'    __list_item__ * get_data() { return data; }'+CRLF+
'};'+CRLF+
''+CRLF+
'class __obj_empty__ {'+CRLF+
'  protected:'+CRLF+
'    __list_item__ * data;'+CRLF+
'  public:'+CRLF+
'    __obj_empty__() {'+CRLF+
'      data = new __list_item__;'+CRLF+
'      data->_vtype = li_empty;'+CRLF+
'    };'+CRLF+
'    __list_item__ * get_data() { return data; };'+CRLF+
'};'+CRLF+
''+CRLF+
'class __obj_list__ {'+CRLF+
'  protected:'+CRLF+
'    vector<__list_item__ *> * items;'+CRLF+
'  public:'+CRLF+
'    __obj_list__() {'+CRLF+
'      items = new vector<__list_item__ *>();'+CRLF+
'    };'+CRLF+
'    __obj_list__ & operator << (__list_item__ * item) {'+CRLF+
'      items->push_back(item);'+CRLF+
'      return *this;'+CRLF+
'    };'+CRLF+
'    __obj_list__ & operator << (signed char vint8) {'+CRLF+
'      __list_item__ * v = new __list_item__;'+CRLF+
'      v->_vtype = li_int;'+CRLF+
'      v->_vsize_item = sizeof(vint8);'+CRLF+
'      v->_vint = vint8;'+CRLF+
'      items->push_back(v);'+CRLF+
'      return *this;'+CRLF+
'    };'+CRLF+
'    __obj_list__ & operator << (unsigned char vuint8) {'+CRLF+
'      __list_item__ * v = new __list_item__;'+CRLF+
'      v->_vtype = li_uint;'+CRLF+
'      v->_vsize_item = sizeof(vuint8);'+CRLF+
'      v->_vuint = vuint8;'+CRLF+
'      items->push_back(v);'+CRLF+
'      return *this;'+CRLF+
'    };'+CRLF+
'    __obj_list__ & operator << (signed short vint16) {'+CRLF+
'      __list_item__ * v = new __list_item__;'+CRLF+
'      v->_vtype = li_int;'+CRLF+
'      v->_vsize_item = sizeof(vint16);'+CRLF+
'      v->_vint = vint16;'+CRLF+
'      items->push_back(v);'+CRLF+
'      return *this;'+CRLF+
'    };'+CRLF+
'    __obj_list__ & operator << (unsigned short vuint16) {'+CRLF+
'      __list_item__ * v = new __list_item__;'+CRLF+
'      v->_vtype = li_uint;'+CRLF+
'      v->_vsize_item = sizeof(vuint16);'+CRLF+
'      v->_vuint = vuint16;'+CRLF+
'      items->push_back(v);'+CRLF+
'      return *this;'+CRLF+
'    };'+CRLF+
'    __obj_list__ & operator << (signed int vint32) {'+CRLF+
'      __list_item__ * v = new __list_item__;'+CRLF+
'      v->_vtype = li_int;'+CRLF+
'      v->_vsize_item = sizeof(vint32);'+CRLF+
'      v->_vint = vint32;'+CRLF+
'      items->push_back(v);'+CRLF+
'      return *this;'+CRLF+
'    };'+CRLF+
'    __obj_list__ & operator << (unsigned int vuint32) {'+CRLF+
'      __list_item__ * v = new __list_item__;'+CRLF+
'      v->_vtype = li_uint;'+CRLF+
'      v->_vsize_item = sizeof(vuint32);'+CRLF+
'      v->_vuint = vuint32;'+CRLF+
'      items->push_back(v);'+CRLF+
'      return *this;'+CRLF+
'    };'+CRLF+
'    __obj_list__ & operator << (signed long long vint64) {'+CRLF+
'      __list_item__ * v = new __list_item__;'+CRLF+
'      v->_vtype = li_int;'+CRLF+
'      v->_vsize_item = sizeof(vint64);'+CRLF+
'      v->_vint = vint64;'+CRLF+
'      items->push_back(v);'+CRLF+
'      return *this;'+CRLF+
'    };'+CRLF+
'    __obj_list__ & operator << (unsigned long long vuint64) {'+CRLF+
'      __list_item__ * v = new __list_item__;'+CRLF+
'      v->_vtype = li_uint;'+CRLF+
'      v->_vsize_item = sizeof(vuint64);'+CRLF+
'      v->_vuint = vuint64;'+CRLF+
'      items->push_back(v);'+CRLF+
'      return *this;'+CRLF+
'    };'+CRLF+
'    __obj_list__ & operator << (float vfloat) {'+CRLF+
'      __list_item__ * v = new __list_item__;'+CRLF+
'      v->_vtype = li_float;'+CRLF+
'      v->_vsize_item = sizeof(vfloat);'+CRLF+
'      v->_vfloat = vfloat;'+CRLF+
'      items->push_back(v);'+CRLF+
'      return *this;'+CRLF+
'    };'+CRLF+
'    __obj_list__ & operator << (double vdouble) {'+CRLF+
'      __list_item__ * v = new __list_item__;'+CRLF+
'      v->_vtype = li_double;'+CRLF+
'      v->_vsize_item = sizeof(vdouble);'+CRLF+
'      v->_vdouble = vdouble;'+CRLF+
'      items->push_back(v);'+CRLF+
'      return *this;'+CRLF+
'    };'+CRLF+
'    __obj_list__ & operator << (long double vldouble) {'+CRLF+
'      __list_item__ * v = new __list_item__;'+CRLF+
'      v->_vtype = li_ldouble;'+CRLF+
'      v->_vsize_item = sizeof(vldouble);'+CRLF+
'      v->_vldouble = vldouble;'+CRLF+
'      items->push_back(v);'+CRLF+
'      return *this;'+CRLF+
'    };'+CRLF+
'    __obj_list__ & operator << (const char * vstr) {'+CRLF+
'      __list_item__ * v = new __list_item__;'+CRLF+
'      v->_vtype = li_str;'+CRLF+
'      v->_vsize_item = sizeof(vstr);'+CRLF+
'      v->_vstr = vstr;'+CRLF+
'      items->push_back(v);'+CRLF+
'      return *this;'+CRLF+
'    };'+CRLF+
'    vector<__list_item__ *> * get_items() { return items; };'+CRLF+
'};'+CRLF+
''+CRLF+
'template<class Type>'+CRLF+
'class __abstract_list {'+CRLF+
'  protected:'+CRLF+
'    int nFields;'+CRLF+
'    int * sizeFields;'+CRLF+
'    int * offsFields;'+CRLF+
'  public:'+CRLF+
'    virtual void push_front(const Type Item) = 0;'+CRLF+
'    virtual void push_back(const Type Item) = 0;'+CRLF+
'    virtual Type& front()    = 0;'+CRLF+
'    virtual Type& back()     = 0;'+CRLF+
'    virtual void pop_front() = 0;'+CRLF+
'    virtual void pop_back()  = 0;'+CRLF+
'    virtual int  empty() = 0;'+CRLF+
'    virtual int  size() = 0;'+CRLF+
'    virtual void clear() = 0;'+CRLF+
'    void operator << (vector<__list_item__ *> * items) {'+CRLF+
'      int n = 0;'+CRLF+
'      for (int i = 0; i < items->size(); i++) {'+CRLF+
'          int _NN = 0;'+CRLF+
'          if ((*items)[i]->_vtype == li_array)'+CRLF+
'             _NN = (*items)[i]->_vsize_total/(*items)[i]->_vsize_item;'+CRLF+
'          else if ((*items)[i]->_vtype != li_empty)'+CRLF+
'             _NN = 1;'+CRLF+
'          if (_NN > n) n = _NN;'+CRLF+
'      }'+CRLF+
'      int * counters = new int[items->size()];'+CRLF+
'      memset(counters, 0, items->size()*sizeof(int));'+CRLF+
'      for (int i = 0; i < n; i++) {'+CRLF+
'          Type item;'+CRLF+
'          for (int j = 0; j < nFields; j++) {'+CRLF+
'              void * base = NULL;'+CRLF+
'              if (j < items->size())'+CRLF+
'                 if ((*items)[j]->_vtype == li_array) {'+CRLF+
'                    base = reinterpret_cast<void *>( (char *)(*items)[j]->_vpntr + counters[j] );'+CRLF+
'                    if (counters[j] < (*items)[j]->_vsize_total - (*items)[j]->_vsize_item) {'+CRLF+
'                       counters[j] += (*items)[j]->_vsize_item;'+CRLF+
'                    }'+CRLF+
'                 } else if ((*items)[j]->_vtype != li_empty) {'+CRLF+
'                    switch ((*items)[j]->_vtype) {'+CRLF+
'                      case li_int:     base = &(*items)[j]->_vint; break;'+CRLF+
'                      case li_uint:    base = &(*items)[j]->_vuint; break;'+CRLF+
'                      case li_float:   base = &(*items)[j]->_vfloat; break;'+CRLF+
'                      case li_double:  base = &(*items)[j]->_vdouble; break;'+CRLF+
'                      case li_ldouble: base = &(*items)[j]->_vldouble; break;'+CRLF+
'                      case li_str:     base = &(*items)[j]->_vstr; break;'+CRLF+
'                    }'+CRLF+
'                 }'+CRLF+
'              if (base) {'+CRLF+
'                 memmove((char *)&item + offsFields[j], base, sizeFields[j]);'+CRLF+
'              } else {'+CRLF+
'                 memset((char *)&item + offsFields[j], 0, sizeFields[j]);'+CRLF+
'              }'+CRLF+
'          }'+CRLF+
'          push_back(item);'+CRLF+
'      }'+CRLF+
'      delete[] counters;'+CRLF+
'      for (int i = 0; i < items->size(); i++)'+CRLF+
'          delete (*items)[i];'+CRLF+
'      delete items;'+CRLF+
'    };'+CRLF+
'    void operator >> (vector<__list_item__ *> * items) {'+CRLF+
'      int n = size();'+CRLF+
'      int * counters = new int[items->size()];'+CRLF+
'      memset(counters, 0, items->size()*sizeof(int));'+CRLF+
'      for (int i = 0; i < n; i++) {'+CRLF+
'          Type item = front();'+CRLF+
'          pop_front();'+CRLF+
'          push_back(item);'+CRLF+
'          for (int j = 0; j < nFields; j++) {'+CRLF+
'              void * base = NULL;'+CRLF+
'              if (j < items->size())'+CRLF+
'                 if ((*items)[j]->_vtype == li_array) {'+CRLF+
'                    if (sizeFields[j] != (*items)[j]->_vsize_item) {'+CRLF+
'                       cout<<"Plan>>[arrays/vars] parameter #"<<(j+1)<<" error: var/array item and parameter has different sizes"<<endl;'+CRLF+
'                       exit(-1);'+CRLF+
'                    }'+CRLF+
'                    if (counters[j] < (*items)[j]->_vsize_total) {'+CRLF+
'                       base = reinterpret_cast<void *>( (char *)(*items)[j]->_vpntr + counters[j] );'+CRLF+
'                       counters[j] += (*items)[j]->_vsize_item;'+CRLF+
'                    }'+CRLF+
'                 } else if ((*items)[j]->_vtype != li_empty) {'+CRLF+
'                    cout<<"Plan>>[arrays/vars] parameter #"<<(j+1)<<" translation error: can''t export to constant"<<endl;'+CRLF+
'                    exit(-1);'+CRLF+
'                 }'+CRLF+
'              if (base) {'+CRLF+
'                 memmove(base, (char *)&item + offsFields[j], sizeFields[j]);'+CRLF+
'              }'+CRLF+
'          }'+CRLF+
'      }'+CRLF+
'      delete[] counters;'+CRLF+
'      for (int i = 0; i < items->size(); i++)'+CRLF+
'          delete (*items)[i];'+CRLF+
'      delete items;'+CRLF+
'    };'+CRLF+
'    __abstract_list(int nF, int * sF, int * oF) {'+CRLF+
'      nFields    = nF;'+CRLF+
'      sizeFields = sF;'+CRLF+
'      offsFields = oF;'+CRLF+
'    }'+CRLF+
'    __abstract_list(const __abstract_list<Type> & obj) {'+CRLF+
'      nFields    = obj.nFields;'+CRLF+
'      sizeFields = obj.sizeFields;'+CRLF+
'      offsFields = obj.offsFields;'+CRLF+
'    }'+CRLF+
'};'+CRLF+
''+CRLF+
'template<class Type>'+CRLF+
'class reent_list : public __abstract_list<Type> {'+CRLF+
'  protected:'+CRLF+
'    struct item {'+CRLF+
'      Type Data;'+CRLF+
'      struct item * Prev;'+CRLF+
'      struct item * Next;'+CRLF+
'    };'+CRLF+
'    struct item * Begin;'+CRLF+
'    struct item * End;'+CRLF+
'    volatile int N;'+CRLF+
'  public:'+CRLF+
'    struct iterator {'+CRLF+
'      friend class reent_list<Type>;'+CRLF+
'      protected:'+CRLF+
'        reent_list<Type> * Ref;'+CRLF+
'        struct item * Cur;'+CRLF+
'        struct iterator * PREV;'+CRLF+
'      public:'+CRLF+
'        iterator() { PREV = NULL; };'+CRLF+
'        iterator(reent_list<Type> * _Ref, void * Position) : Ref(_Ref), Cur((struct item *)Position) { PREV = NULL; };'+CRLF+
'        ~iterator() { delete PREV; };'+CRLF+
'        Type& operator * () { return Cur->Data; };'+CRLF+
'        iterator& operator ++ () { if (Cur) Cur = Cur->Next; return *this; };'+CRLF+
'        iterator& operator ++ (int) {'+CRLF+
'          if (PREV) PREV->Cur = Cur;'+CRLF+
'          else PREV = new iterator(Ref,Cur);'+CRLF+
'          if (Cur) Cur = Cur->Next;'+CRLF+
'          return *PREV;'+CRLF+
'        };'+CRLF+
'        iterator& operator -- () { if (Cur) Cur = Cur->Prev; return *this; };'+CRLF+
'        bool operator == (const iterator V) { return Ref==V.Ref && Cur==V.Cur; };'+CRLF+
'        bool operator != (const iterator V) { return Ref!=V.Ref || Cur!=V.Cur; };'+CRLF+
'    };'+CRLF+
'    reent_list(): __abstract_list<Type>(0, NULL, NULL) {'+CRLF+
'      N     = 0;'+CRLF+
'      Begin = NULL;'+CRLF+
'      End   = NULL;'+CRLF+
'    };'+CRLF+
'    reent_list(int nF, int * sF, int * oF): __abstract_list<Type>(nF, sF, oF) {'+CRLF+
'      N     = 0;'+CRLF+
'      Begin = NULL;'+CRLF+
'      End   = NULL;'+CRLF+
'    };'+CRLF+
'    explicit reent_list(int _NN, int nF = 0, int * sF = NULL, int * oF = NULL): __abstract_list<Type>(nF, sF, oF) {'+CRLF+
'      Type Data;'+CRLF+
'      memset(Data, 0, sizeof(Type));'+CRLF+
'      N     = 0;'+CRLF+
'      Begin = NULL;'+CRLF+
'      End   = NULL;'+CRLF+
'      for (int i = 0; i < _NN; i++)'+CRLF+
'          push_back(Data);'+CRLF+
'    };'+CRLF+
'    explicit reent_list(int _NN, Type & Data, int nF = 0, int * sF = NULL, int * oF = NULL): __abstract_list<Type>(nF, sF, oF) {'+CRLF+
'      N     = 0;'+CRLF+
'      Begin = NULL;'+CRLF+
'      End   = NULL;'+CRLF+
'      for (int i = 0; i < _NN; i++)'+CRLF+
'          push_back(Data);'+CRLF+
'    };'+CRLF+
'    reent_list<Type>& operator =(const reent_list<Type> & obj) {'+CRLF+
'      struct item * begin = obj.Begin;'+CRLF+
'      N     = 0;'+CRLF+
'      Begin = NULL;'+CRLF+
'      End   = NULL;'+CRLF+
'      this->nFields    = obj.nFields;'+CRLF+
'      this->sizeFields = obj.sizeFields;'+CRLF+
'      this->offsFields = obj.offsFields;'+CRLF+
'      while (begin) { push_back(begin->Data); begin = begin->Next; }'+CRLF+
'      return *this;'+CRLF+
'    };'+CRLF+
'    reent_list(const reent_list<Type> & obj): __abstract_list<Type>(obj) {'+CRLF+
'      struct item * begin = obj.Begin;'+CRLF+
'      N     = 0;'+CRLF+
'      Begin = NULL;'+CRLF+
'      End   = NULL;'+CRLF+
'      while (begin) { push_back(begin->Data); begin = begin->Next; }'+CRLF+
'    }'+CRLF+
'    ~reent_list() {'+CRLF+
'      clear();'+CRLF+
'    };'+CRLF+
'    Type& front()    { return Begin->Data; };'+CRLF+
'    Type& back()     { return End->Data; };'+CRLF+
'    void pop_front() {'+CRLF+
'      if (Begin) {'+CRLF+
'         if (Begin == End) {'+CRLF+
'            delete Begin;'+CRLF+
'            Begin = NULL;'+CRLF+
'            End = NULL;'+CRLF+
'         } else {'+CRLF+
'            struct item * This = Begin;'+CRLF+
'            Begin       = Begin->Next;'+CRLF+
'            Begin->Prev = NULL;'+CRLF+
'            delete This;'+CRLF+
'         }'+CRLF+
'         N--;'+CRLF+
'      }'+CRLF+
'    };'+CRLF+
'    void pop_back()  {'+CRLF+
'      if (End) {'+CRLF+
'         if (Begin == End) {'+CRLF+
'            delete Begin;'+CRLF+
'            Begin = NULL;'+CRLF+
'            End = NULL;'+CRLF+
'         } else {'+CRLF+
'            struct item * This = End;'+CRLF+
'            End       = End->Prev;'+CRLF+
'            End->Next = NULL;'+CRLF+
'            delete This;'+CRLF+
'         }'+CRLF+
'         N--;'+CRLF+
'      }'+CRLF+
'    };'+CRLF+
'    void push_front(const Type Item) {'+CRLF+
'      if (empty()) push_back(Item);'+CRLF+
'      else {'+CRLF+
'         struct item * NEW = new struct item;'+CRLF+
'         NEW->Data   = Item;'+CRLF+
'         NEW->Prev   = NULL;'+CRLF+
'         NEW->Next   = Begin;'+CRLF+
'         Begin->Prev = NEW;'+CRLF+
'         Begin = NEW;'+CRLF+
'         N++;'+CRLF+
'      }'+CRLF+
'    };'+CRLF+
'    void push_back(const Type Item)  {'+CRLF+
'      struct item * NEW = new struct item;'+CRLF+
'      NEW->Data   = Item;'+CRLF+
'      if (empty()) {'+CRLF+
'         NEW->Prev = NULL;'+CRLF+
'         NEW->Next = NULL;'+CRLF+
'         Begin = NEW;'+CRLF+
'         End   = NEW;'+CRLF+
'      } else {'+CRLF+
'         NEW->Prev   = End;'+CRLF+
'         NEW->Next   = NULL;'+CRLF+
'         End->Next   = NEW;'+CRLF+
'         End = NEW;'+CRLF+
'      }'+CRLF+
'      N++;'+CRLF+
'    };'+CRLF+
'    int  empty() { return N==0; };'+CRLF+
'    int  size()  { return N; };'+CRLF+
'    void clear() {'+CRLF+
'      while (Begin) {'+CRLF+
'        struct item * next = Begin->Next;'+CRLF+
'        delete Begin;'+CRLF+
'        Begin = next;'+CRLF+
'      }'+CRLF+
'      N   = 0;'+CRLF+
'      End = 0;'+CRLF+
'    };'+CRLF+
'    iterator erase(iterator Ptr) {'+CRLF+
'      if (Ptr.Cur == Begin && Ptr.Cur == End) {'+CRLF+
'         clear();'+CRLF+
'         return end();'+CRLF+
'      } else {'+CRLF+
'        iterator next = iterator(Ptr.Ref, Ptr.Cur->Next);'+CRLF+
'        if (Ptr.Cur->Prev) Ptr.Cur->Prev->Next = Ptr.Cur->Next;'+CRLF+
'        else Begin = Begin->Next;'+CRLF+
'        if (Ptr.Cur->Next) Ptr.Cur->Next->Prev = Ptr.Cur->Prev;'+CRLF+
'        else End = End->Prev;'+CRLF+
'        delete Ptr.Cur;'+CRLF+
'        N--;'+CRLF+
'        return next;'+CRLF+
'      }'+CRLF+
'    };'+CRLF+
'    iterator begin() { iterator Result = iterator(this,Begin); return Result; };'+CRLF+
'    iterator end()   { iterator Result = iterator(this,NULL); return Result; };'+CRLF+
'};';

