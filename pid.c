#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <malloc.h>
#include <signal.h>

#define  READ_BUF_SIZE 100


void * xmalloc (size_t size)
{
    register void *value = malloc(size);
    if (value == 0)
        perror("virtual memory exhausted");

    return value;
}

void * xrealloc(void *ptr, size_t size)
{
    register void *value = realloc(ptr, size);
    if (value == 0)
        perror("virtual memory exhausted");

    return value;
}



static pid_t get_pid_by_name(char *process)
{
    DIR *dir;
    struct dirent *next;
    long* pidList = NULL;
    int i = 0;
    char *pidName;
    pid_t retval;

    pidName = process;

    dir = opendir("/proc");
    if (!dir)
        printf("Cannot open /proc");

    while ((next = readdir(dir)) != NULL)
    {
       // printf(" Entering the while loop \n");
        
    FILE *status;
        char filename[READ_BUF_SIZE];
        char buffer[READ_BUF_SIZE];
        char name[READ_BUF_SIZE];

        /* Must skip ".." since that is outside /proc */
        if (strcmp(next->d_name, "..") == 0)
            continue;

        /* If it isn't a number, we don't want it */
        if (!isdigit(*next->d_name))
            continue;
        //printf(" searching");
        
    sprintf(filename, "/proc/%s/status", next->d_name);
        
    if (! (status = fopen(filename, "r")) )
        {
            continue;
        }
         if (fgets(buffer, READ_BUF_SIZE-1, status) == NULL)
        {
            fclose(status);
            continue;
        }
        fclose(status);

        /* Buffer should contain a string like "Name:   binary_name" */
        sscanf(buffer, "%*s %s", name);
        if (strcmp(name, pidName) == 0)
        {
            pidList=(long *)xrealloc( pidList, sizeof(long) * (i+2));
            pidList[i++]=strtol(next->d_name, NULL, 0);
        }
    }
    if (pidList)
        pidList[i]=0;
    else
    {
        pidList=(long *)xrealloc( pidList, sizeof(long));
        pidList[0]=-1;
    }

    retval = (pid_t)pidList[0];
    free(pidList);
    return retval;
}


int main()
{  char buf[100]; 
    printf("please input :\n");
    scanf("%s",buf);
    pid_t pid;

    pid = get_pid_by_name(buf);

    printf(" pid is:%d \n",pid);

    return 0;
}
