#include <iostream>

using namespace std;

chain B() {
  cout<<"1";
  plan_registered_barrier(topology);
  cout<<"2";
  plan_registered_barrier(topology);
  cout<<"3";
  plan_registered_barrier(topology);
  cout<<"4";
  plan_registered_barrier(topology);
  cout<<"5";
  for (int i = 0; i < 10; i++)
  {
    if (i == 0) Sleep(i*10);
    else if (i == 2) Sleep((10-i)*10);
    plan_registered_barrier(topology);
  }
}

int main() {
  plan_parallel_chain(1,8,B());
  cout<<endl;

  plan_sem_t sem;
  plan_sem_init(&sem,3);
  #pragma omp parallel num_threads(5)
  {
     cout<<"E("<<omp_get_thread_num()<<")";
     plan_sem_wait(&sem);
     cout<<"I("<<omp_get_thread_num()<<")";
     Sleep((omp_get_thread_num()+1)*1000);
     plan_sem_release(&sem);
     cout<<"O("<<omp_get_thread_num()<<")";
  }
  plan_sem_destroy(&sem);
  return 0;
}