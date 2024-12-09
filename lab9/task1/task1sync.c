#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>

int array_size, indices_per_thread;
int *A, *B, *C;
int threads_completed = 0;
int num_of_threads;
pthread_mutex_t lock;

void* addArrays(void* arg){
    int start_index = *(int*)arg; // Pass this from the main thread
    // ========================================================================================================
    // BEGIN YOUR CODE HERE
    //implement this function to perform addition of two arrays A and B, by multiple threads for their assigned indices and store the result in array C.
    if (start_index != -1){
        int diff = (array_size / num_of_threads);
        if (array_size % num_of_threads) diff++;

        for (int i = 0; (i < diff) && (start_index + i < array_size); i++){
            C[start_index + i] = A[start_index + i] + B[start_index + i];
        }
    } 
    pthread_mutex_lock(&lock);
    threads_completed = threads_completed + 1;
    pthread_mutex_unlock(&lock);
    // printf("Thread Complete: %d\n", threads_completed);
    // ========================================================================================================
   usleep(random()%100);//random execution time added
   pthread_exit(NULL);


}

int main(int argc, char* argv[]){
    if(argc != 4) {
        perror("Execution syntax: ./task1 <file_name1> <file_name2> <number_of_parallel_threads>");
        exit(0);
    }

    FILE *file1, *file2;
    file1 = fopen(argv[1], "r");
    file2 = fopen(argv[2], "r");
    if(file1 == NULL || file2 == NULL) {
        perror("Error opening the file");
        exit(0);
    }
    fscanf(file1, "%d", &array_size);
    fscanf(file2, "%d", &array_size);

    num_of_threads = atoi(argv[3]);

    A = malloc(array_size * sizeof(int));
    B = malloc(array_size * sizeof(int));
    C = malloc(array_size * sizeof(int));

    for (int i=0; i<array_size; i++) { 
        fscanf(file1, "%d", &A[i]);
        fscanf(file2, "%d", &B[i]);
    }

    fclose(file1);
    fclose(file2);

    // ========================================================================================================
    // BEGIN YOUR CODE HERE
    // Create num_threads number of threads that will generate the output array.
    // Use mutexes where requried
    // Calculate the sum in the main thread once all other threads have finished execution
    // Print the total sum obtained and the execution time
    clock_t start, end;

    start = clock();

    pthread_t ptid[num_of_threads];
    int diff = (array_size / num_of_threads);
    if (array_size % num_of_threads) diff++;
    int args[num_of_threads];

    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < num_of_threads; i++){
        args[i] = i * diff;
        if (args[i] >= array_size) args[i] = -1;
        pthread_create(&ptid[i], NULL, addArrays, &args[i]);
    }
    while (threads_completed < num_of_threads) usleep(1000);
    pthread_mutex_destroy(&lock);

    int ans = 0;
    for (int i = 0; i < array_size; i++) ans += C[i];

    end = clock();
    double duration = ((double)end - start) * 1000000 / CLOCKS_PER_SEC;
    printf("sum of elements: %d\n", ans);
    printf("Time Spent: %f us\n", duration);

    // ========================================================================================================
    return 0;
}
