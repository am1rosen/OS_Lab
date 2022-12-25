#include <stdio.h>
#include <string.h>
#include<time.h>
#include<pthread.h>
#include <unistd.h>

char* path_1 = "/home/am1rosen/Desktop/d1.csv";
char* path_2 = "/home/am1rosen/Desktop/d2.csv";
char* path_3 = "/home/am1rosen/Desktop/d3.csv";

int words(const char sentence[]) {
    int counted = 0; // result

    const char* it = sentence;
    int inword = 0;

    do switch(*it) {
            case '\0':
            case ' ': case '\t': case '\n': case '\r':
                if (inword) { inword = 0; counted++; }
                break;
            default: inword = 1;
        } while(*it++);

    return counted;
}

void count_words(char* path, char* method, int id) {
    FILE* fp = fopen(path, "r");
    if (!fp)
        printf("Can't open file\n");
    else {
        char buffer[2500];
        int row = 0;
        while (fgets(buffer, 2500, fp)) {
            row++;
            if (row == 1)
                continue;
            char* value = strtok(buffer, "\n");
            while (value) {
                *(value + (strlen(value) - 4)) = '\0';
//                printf("%s\t\tnumber of words: %d", value, words(value));
                printf("[%s%d] [line: %d] number of words = %d\n",method, id, row, words(value));
                value = strtok(NULL, "\n");
            }
//            printf("\n");
        }
        fclose(fp);
    }
}

void *thread_function(void *arg) {
    int *id = (int *)arg;
    int thread_id = *id;

    if(thread_id == 0)
        count_words(path_1, "thread", 1);
    else if(thread_id == 1)
        count_words(path_2, "thread", 2);
    else
        count_words(path_3, "thread", 3);
}

int main() {
    clock_t start, end;
    double execution_time;
    start = clock();

    // Functions
    count_words(path_1, "function", 1);
    count_words(path_2, "function", 2);
    count_words(path_3, "function", 3);
    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("\n%f",execution_time);


//    processes
//    int pid1 = fork();
//    if (pid1 == 0) {
//        count_words(path_1, "process", 1);
//        return 0;
//    } else {
//        int pid2 = fork();
//        if(pid2 == 0) {
//            count_words(path_2, "process", 2);
//            return 0;
//        } else
//            count_words(path_3, "process", 3);
//    }
//    end = clock();
//    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
//    printf("\n%f",execution_time);


    //threads
//    pthread_t tid[3];
//    int id[3];
//    for (int i = 0; i < 3; i++) {
//        id[i] = i;
//        pthread_create(&tid[i], NULL, thread_function, (void *)&id[i]);
//    }
//    sleep(1);



    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("\n%f",execution_time);



    return 0;
}