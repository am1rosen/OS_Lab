#include <iostream>
#include <unistd.h>

int random_number(int from, int to) {
    return ((rand() % (to - from)) + from);
}

int a = random_number(1, 1000), b = random_number(1, 1000), c = random_number(1, 1000);
clock_t start, end;
double execution_time;


int is_prime(int num) {
    for(int i = 2; i <= num / 2; i++)
        if(num % i == 0)
            return 0;
    return 1;
}

int min(int x, int y) {
    if (x < y)
        return x;
    return y;
}

void *thread_function(void *id) {
    int *t = (int *)id;
    int t_id = *t;


    if (t_id == 0) {
        start = clock();
        for (int i = a - 1; i > 0; i--) {
            if (is_prime(i)) {
                end = clock();
                execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
                printf("[Thread] Biggest prime number smaller than a(%d) is %d. time = %fs\n", a, i, execution_time);
                return nullptr;
            }
        }
        end = clock();
        execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
        printf("[Thread] There is no prime number smaller than a(%d). time = %fs\n", a, execution_time);

    } else if (t_id == 1) {
        start = clock();
        for (int i = min(b, c); i >= 1; i--) {
            if (b % i == 0 && c % i == 0) {
                end = clock();
                execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
                printf("[Thread] GCD of b(%d) and c(%d) is %d. time = %fs\n", b, c, i, execution_time);
                return nullptr;
            }
        }
    } else {
        start = clock();
        int result = 1;
        for (int i = 1; i <= min(b, c); i++)
            if (b % i == 0 && c % i == 0)
                result *= i;
        end = clock();
        execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
        printf("[Thread] Multiplication of all common dividers of b(%d) and c(%d) is %d. time = %fs\n", b, c, result, execution_time);

    }

    return nullptr;
}

int main() {


    // using process
    int pid1 = fork();
    if (pid1 == 0) {
        start = clock();
        for (int i = a - 1; i > 0; i--) {
            if (is_prime(i)) {
                end = clock();
                execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
                printf("[Process] Biggest prime number smaller than a(%d) is %d. time = %fs\n", a, i, execution_time);
                return 0;
            }
        }
        end = clock();
        execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
        printf("[Process] There is no prime number smaller than a(%d). time = %fs\n", a, execution_time);
        return 0;
    } else {
        int pid2 = fork();
        if (pid2 == 0) {
            start = clock();
            for (int i = min(b, c); i >= 1; i--) {
                if (b % i == 0 && c % i == 0) {
                    end = clock();
                    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
                    printf("[Process] GCD of b(%d) and c(%d) is %d. time = %fs\n", b, c, i, execution_time);
                    return 0;
                }
            }


        } else {
            start = clock();
            int result = 1;
            for (int i = 1; i <= min(b, c); i++)
                if (b % i == 0 && c % i == 0)
                    result *= i;
            end = clock();
            execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
            printf("[Process] Multiplication of all common dividers of b(%d) and c(%d) is %d. time = %fs\n", b, c, result, execution_time);

        }
    }
    sleep(1);
    printf("\n\n");

    //using threads
    pthread_t tid[3];
    int id[3];
    for (int i = 0; i < 3; i++) {
        id[i] = i;
        pthread_create(&tid[i], nullptr, thread_function, (void *)&id[i]);
    }
    for (unsigned long i : tid)
        pthread_join(i, nullptr);




    return 0;
}
