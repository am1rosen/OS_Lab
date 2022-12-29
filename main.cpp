#include <iostream>
#include <pthread.h>
#include <ctime>
#include <unistd.h>
#include <cstring>

int random_number(int from, int to) {
    return ((rand() % (to - from)) + from);
}

char get_char(int id) {
    if (id == 0)
        return 'A';
    else if (id == 1)
        return 'B';
    else if (id == 2)
        return 'C';
    return '\0';
}

char * get_time() {
    time_t raw_time;
    struct tm * time_info;
    time ( &raw_time );
    time_info = localtime ( &raw_time );
    char * result = asctime(time_info);

    int spaces = 0, count = 0;
    char * only_time = result;
    for (int index = 0; index < strlen(result); index++) {
        if (result[index] == ' ') spaces += 1;
        if (spaces == 3) {
            only_time[count] = result[index + 1];
            count += 1;
        }
    }
    only_time[count - 1] = '\0';
    return only_time;
}

int room_1 = 0, room_2 = 0;
int time_limit[3] = {1, 2, 3};
int income[3] = {1000, 1500, 2000};
int violation[3] = {0, 0, 0};
int penalty[3] = {10, 20, 30};
int total_time[3] = {0, 0, 0};
int times[3] = {random_number(2, 5), random_number(2, 5), random_number(2, 5)};
pthread_mutex_t lock;

void *thread_function(void *id) {

    int *e_id = (int *)id;
    int employee_id = *e_id;

    for (int i = times[employee_id]; i > 0; i--) {
        while (room_1 == 1 && room_2 == 1);
        int free_room = 0;
        if (!room_1) free_room = 1;
        else if (!room_2) free_room = 2;
        if (free_room == 1) room_1 = 1;
        else room_2 = 1;

        if (room_1 == 1 && room_2 == 1)
            pthread_mutex_lock(&lock);

        if (free_room == 0) {
            i += 1;
            break;
        }

        int time_inside = random_number(1, 5);
        total_time[employee_id] += time_inside;
        printf("[%s] Employee %c entered room %d. waiting for %d seconds.\n", get_time(), get_char(employee_id), free_room, time_inside);
        printf("Room %d: lights ON.\n\n", free_room);
        sleep(time_inside);
        if (time_inside > time_limit[employee_id]) {
            printf("Violation! Employee %c waited too long. (%d > %d)\n", get_char(employee_id), time_inside, time_limit[employee_id]);
            income[employee_id] -= penalty[employee_id];
            violation[employee_id] += 1;
        }
        printf("[%s] Employee %c exited from room %d.\n", get_time(), get_char(employee_id), free_room);
        printf("Room %d: lights OFF.\n\n", free_room);



        pthread_mutex_unlock(&lock);
        if (free_room == 1)
            room_1 = 0;
        else
            room_2 = 0;

    }

    return nullptr;
}

int main() {
    printf("Start of program.\n");
    pthread_t tid[3];
    pthread_mutex_init(&lock, nullptr);
    int id[3];
    for (int i = 0; i < 3; i++) {
        id[i] = i;
        pthread_create(&tid[i], nullptr, thread_function, (void *)&id[i]);
    }
    for (unsigned long i : tid)
        pthread_join(i, nullptr);

    income[0] += (times[0] - 2) * 5 * income[0] / 100;
    income[1] += (times[1] - 2) * 5 * income[1] / 100;
    income[2] += (times[2] - 2) * 5 * income[2] / 100;

    printf("                ╔══════════════════════╦══════════════════════════════╦══════════════════════════════╦═════════════════════════╗\n");
    printf("                ║       Employee       ║               A              ║               B              ║            C            ║\n");
    printf("                ╠══════════════════════╬══════════════════════════════╬══════════════════════════════╬═════════════════════════╣\n");
    printf("                ║          ID          ║           MJOyFlxHx7         ║           ThloJt8dtf         ║        hDrx45qZbB       ║\n");
    printf("                ╠══════════════════════╬══════════════════════════════╬══════════════════════════════╬═════════════════════════╣\n");
    printf("                ║      Time Inside     ║             %3d              ║             %3d              ║          %3d            ║\n", total_time[0], total_time[1], total_time[2]);
    printf("                ╠══════════════════════╬══════════════════════════════╬══════════════════════════════╬═════════════════════════╣\n");
    printf("                ║      Base Income     ║              1000            ║              1500            ║           2000          ║\n");
    printf("                ╠══════════════════════╬══════════════════════════════╬══════════════════════════════╬═════════════════════════╣\n");
    printf("                ║     Total Visits     ║             %d(+%2d%)          ║             %d(+%2d%)          ║          %d(+%2d%)        ║\n", times[0],(times[0] - 2) * 5 , times[1], (times[1] - 2) * 5, times[2], (times[2] - 2) * 5);
    printf("                ╠══════════════════════╬══════════════════════════════╬══════════════════════════════╬═════════════════════════╣\n");
    printf("                ║   Total Violations   ║             %d(-%2d)           ║            %d(-%3d)           ║         %d(-%3d)         ║\n", violation[0], violation[0] * 10, violation[1], violation[1] * 20, violation[2], violation[2] * 30);
    printf("                ╠══════════════════════╬══════════════════════════════╬══════════════════════════════╬═════════════════════════╣\n");
    printf("                ║     Total Income     ║              %4d            ║              %4d            ║           %4d          ║\n", income[0], income[1], income[2]);
    printf("                ╚══════════════════════╩══════════════════════════════╩══════════════════════════════╩═════════════════════════╝\n");

    return 0;
}
