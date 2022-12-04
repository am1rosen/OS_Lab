#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<dirent.h>
#include<string.h>
#include <sys/wait.h>

void recursiveSMethod(int depth, char *path, int argc, char* argv[]);

int check(const char *str){
    int count = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if ('.' == str[i])
            ++count;
    }
    return count;
}

int countDirNumbers(char *path, int argc, char* argv[]){
    int count = 0;
    struct dirent **namelist;
    int n; if(argc < 1) {
        exit(EXIT_FAILURE);
    } else if (argc == 1) {
        n = scandir(path,&namelist,NULL,alphasort);
    } else {
        n = scandir(argv[1], &namelist, NULL, alphasort);
    } if(n < 0) {
        perror("scandir");
        exit(EXIT_FAILURE);
    } else {
        while (n--)
        {
            int response = check(namelist[n]->d_name);
            if(response == 0){
                count++;
            }
            free(namelist[n]);
        } free(namelist);
    }
    return count;
}

void ls(int depth, char *path, int argc, char* argv[], int state){
    struct dirent **namelist;
    int n; if(argc < 1) {
        exit(EXIT_FAILURE);
    } else if (argc == 1) {
        n=scandir(path,&namelist,NULL,alphasort);
    } else {
        n = scandir(argv[1], &namelist, NULL, alphasort);
    } if(n < 0) {
        perror("scandir");
        exit(EXIT_FAILURE);
    } else {
        int isFileCat = 0;
        while (n--)
        {
            int response = check(namelist[n]->d_name);
            if(response == 0){
                if(state == 1) {
                    pid_t pid = fork();
                    if (pid == 0) {
                        recursiveSMethod(depth + 1, strcat(strcat(path,"/"),namelist[n]->d_name), argc, argv);
                        exit(EXIT_SUCCESS);
                    }
                }else{
                    recursiveSMethod(depth + 1, strcat(strcat(path,"/"),namelist[n]->d_name), argc, argv);
                    break;
                }
            }else if(isFileCat==0){
                isFileCat = 1;
                char src[100];
                strcpy(src, "bash /home/am1rosen/Desktop/sortFiles.sh ");
                system(strcat(src,path));
            }
            free(namelist[n]);
        } free(namelist);
    }
    exit(EXIT_SUCCESS);
}

void recursiveSMethod(int depth, char *path, int argc, char* argv[]){
    if (depth <= 3) {
        char cwd[1024];
        chdir(path);
        getcwd(cwd, sizeof(cwd));
        if (countDirNumbers(path, argc, argv) >= 1) {
            if(countDirNumbers(path, argc, argv) > 1) {
                ls(depth,path,argc, argv,1);
            }else{
                ls(depth,path,argc, argv,0);
            }
        } else {
            char src[100];
            strcpy(src, "bash /home/am1rosen/Desktop/q3.sh ");
            system(strcat(src,path));
        }
    }else{
        char src[100];
        strcpy(src, "bash /home/am1rosen/Desktop/q3.sh ");
        system(strcat(src,path));
    }
}

int main(int argc, char* argv[]) {
    char src[100];
    strcpy(src, "/home/am1rosen/Desktop/Categorized");
    recursiveSMethod(1,src,argc,argv);
    system("find /home/am1rosen/Desktop/Categorized -empty -type d -delete");
    return 0;
}
