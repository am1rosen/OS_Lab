#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

#define PICTURES_1 "#!/bin/bash\n\
for pic in $(ls /home/am1rosen/Desktop/pictures_1/*.png)\n\
do\n\
	strings $pic | grep -q ubuntu\n\
	if [ $? -eq 0 ]\n\
	then\n\
   		echo $pic\n\
	fi\n\
done"
	#define PICTURES_2 "#!/bin/bash\n\
for pic in $(ls /home/am1rosen/Desktop/pictures_2/*.png)\n\
do\n\
	strings $pic | grep -q ubuntu\n\
	if [ $? -eq 0 ]\n\
	then\n\
   		echo $pic\n\
	fi\n\
done"
	#define PICTURES_3 "#!/bin/bash\n\
for pic in $(ls /home/am1rosen/Desktop/pictures_3/*.png)\n\
do\n\
	strings $pic | grep -q ubuntu\n\
	if [ $? -eq 0 ]\n\
	then\n\
   		echo $pic\n\
	fi\n\
done"

int main() {

	int pid, pid1, pid2;

	pid = fork();

	if (pid == 0) {

		system(PICTURES_1);
		printf("Subprocess[1] --> pid = %d and ppid = %d\n", getpid(), getppid());
		return 0;
	}

	else {
		pid1 = fork();
		if (pid1 == 0) {
			system(PICTURES_2);
			printf("Subprocess[2] --> pid = %d and ppid = %d\n", getpid(), getppid());
			return 0;
		}
		else {
			pid2 = fork();
			if (pid2 == 0) {
				system(PICTURES_3);
				printf("Subprocess[3] --> pid = %d and ppid = %d\n", getpid(), getppid());
				return 0;
			}
			else {
				for(int i = 0; i < 3; i++)
					wait(NULL);
				
				sleep(3);
				printf("Parent --> pid = %d\n", getpid());
			}
		}
	}

	return 0;
}


