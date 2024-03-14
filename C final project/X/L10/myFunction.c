#include "myFunction.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/utsname.h>
#include <stdlib.h>
#include <string.h>

char *getInputFromUser()
{
    char ch;
    int size = 1;
    int index = 0;
    char *str = (char *)malloc(size * sizeof(char));
    while ((ch = getchar()) != '\n')
    {
        *(str + index) = ch;
        size++;
        index++;
        str = (char *)realloc(str, size * sizeof(char));
    }
    *(str + index) = '\0';

    return str;
}
char** splitArguments(char* str) {
    
    int argumentSize = 2;
    int index = 0;
    char** argumentArray = (char**)malloc(argumentSize * sizeof(char*));

    
    char* subStr = strtok(str, " ");
    *(argumentArray + index) = subStr;
    while ((subStr = strtok(NULL, " ")) != NULL) {
        index++;
        argumentSize++;
        argumentArray = (char**)realloc(argumentArray, argumentSize * sizeof(char*));
        *(argumentArray + index) = subStr;
    }
    *(argumentArray + index + 1) = NULL; 

    return argumentArray;
}

void getLocation()
{
    char location[BUFF_SIZE];

    if (getcwd(location, BUFF_SIZE) == NULL)
    {
        puts("Error");
    }
    else
    {
        bold();
        blue();
        printf("%s", location);
        reset();
        printf("$ ");
    }
}
void logout(char *str) {
    
    char exitString[] = "exit";

   
    char *exitPtr = strstr(str, exitString);

    
    if (exitPtr == NULL) {
        printf("Error: Invalid command\n");
        return;
    }

    
    if (strlen(exitPtr) != strlen(str)) {
        printf("Error: Invalid command\n");
        return;
    }

    printf("Exiting...\n");
    exit(0);
}
void echo(char **arg)
{
    while (*(++arg))
        printf("%s ", *arg);
    puts("");
}

void cd(char **args) {
    char *newPath;
    int i = 1;

    
    if (args[i][0] == '"') {
        int endIdx = i;
        while (args[endIdx] != NULL && args[endIdx][strlen(args[endIdx])-1] != '"') {
            endIdx++;
        }

        
        newPath = (char *)malloc(sizeof(char) * 1024);
        newPath[0] = '\0';

        
        for (int j = i; j <= endIdx; j++) {
            strcat(newPath, args[j]);
            strcat(newPath, " ");
        }
        
        newPath[strlen(newPath)-1] = '\0';
    }
    else {
       
        newPath = args[1];
    }

   
    if (chdir(newPath) != 0) {
        printf("-myShell: cd: %s: No such file or directory\n", newPath);
    }

    
    free(newPath);
}

int main() {
    char *args[] = {"cd", "OneDrive", "- Ariel University\"", NULL};
    cd(args);
    return 0;
}


void cp(char **args) {
    
    if (args[1] == NULL || args[2] == NULL) {
        printf("-myShell: cp: missing file operand\n");
        return;
    }

    
    char *sourcePath = args[1];
    char *destinationPath = args[2];

    
    if (sourcePath[0] == '"') {
        sourcePath++;
        sourcePath[strlen(sourcePath)-1] = '\0';
    }
    if (destinationPath[0] == '"') {
        destinationPath++;
        destinationPath[strlen(destinationPath)-1] = '\0';
    }

    char command[1024];
    sprintf(command, "cp \"%s\" \"%s\"", sourcePath, destinationPath);

    
    system(command);
}

void get_dir()
{
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir("./")) == NULL)
    {
        /* could not open directory */
        perror("");
        return;
    }
    /* print all the files and directories within directory */
    while ((ent = readdir(dir)) != NULL)
    {
        printf("%s ", ent->d_name);
    }
    puts("");
    closedir(dir);
}
void delete(char **arg)
{
    if (unlink(arg[1]) != 0)
        printf("-myShell: unlink: %s: No such file or directory\n", arg[1]);
}
void systemCall(char **arg)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        printf("fork err\n");
        return;
    }
    if (pid == 0 && execvp(arg[0], arg) == -1)
        exit(1);
}

// cd ba kms
// input =  ['c','d', '\0', ' ', ' ', ' ', ' ','"', 'b', 'a', '\0', 'k', 'm', 's','"',  '\0']
//['"', 'b', 'a', ' ', 'k', 'm', 's','"',  '\0']
// arguments[input,input+7,input+11,NULL]

// cd "ba kms"
// cd(arg[1][])
// cp "bbb bbb" "bbb bb1"
