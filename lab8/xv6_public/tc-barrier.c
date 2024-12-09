#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

struct barrier{

    // ******************************
    // WPTHREAD -- START
    // ******************************

    // Add counters, semaphore variables, thread number, whatever you might need here.
    int counter;
    int sem1, sem2;
    int sem_protect;
    int thread_num;

    // ******************************
    // WPTHREAD -- END
    // ******************************
};

struct barrier bar;

void barrier_init(struct barrier* bar, int num_threads){

    // ******************************
    // WPTHREAD -- START
    // ******************************

    // Initialize the variables in struct barrier.
    bar->counter = 0;
    bar->thread_num = num_threads;
    bar->sem1 = semaphore_init(0);
    bar->sem2 = semaphore_init(0);
    bar->sem_protect = semaphore_init(1);

    // ******************************
    // WPTHREAD -- END
    // ******************************
}

void barrier_place(struct barrier* bar){

    // ******************************
    // WPTHREAD -- START
    // ******************************

    // Stop all threads till required number of threads arrive, and
    // then allow all threads to pass.

    // Also make sure that the barrier is restored to original state since it is 
    // begin called multiple times.

    // As long as functionality is correct, you can implement it any way you like.
    
    semaphore_down(bar->sem_protect);
    bar->counter++;
    if (bar->counter == bar->thread_num){
        for(int i = 0; i < bar->thread_num; i++) semaphore_up(bar->sem1);
    }
    semaphore_up(bar->sem_protect);
    semaphore_down(bar->sem1);


    semaphore_down(bar->sem_protect);
    bar->counter--;
    if (bar->counter == 0){
        for(int i = 0; i < bar->thread_num; i++) semaphore_up(bar->sem2);
    }
    semaphore_up(bar->sem_protect);
    semaphore_down(bar->sem2);

    // ******************************
    // WPTHREAD -- END
    // ******************************
}

void work(int *thread_num){

    for(int i=0;i<3;i++){

        barrier_place(&bar);

        printf(1,"LOOP %d | Section 1 of code | Thread Number: %d\n",i,*thread_num);

        barrier_place(&bar);

        printf(1,"LOOP %d | Section 2 of code | Thread Number: %d\n",i,*thread_num);

    }

    exit();
}

int main(int argc, char *argv[]) {

    int N = 5;

    barrier_init(&bar,N);

    int ind[N];

    for(int i=0;i<N;i++){

        ind[i]=i+1;
    }

    for(int i=0;i<N;i++) {
        create_thread(work, &ind[i]);
    }

    for(int i=0;i<N;i++) {
        join();
    }

    printf(1, "All threads joined, code completed\n");
    exit();
}