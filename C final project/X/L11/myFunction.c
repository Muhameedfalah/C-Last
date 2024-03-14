#include "myFunction.h"
#include <stdio.h>
#include <unistd.h>
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
void delete(char *str) {
   
    if (str[0] == '"' && str[strlen(str) - 1] == '"') {
      
        char newPath[strlen(str)];
        int j = 0;
        for (int i = 1; i < strlen(str) - 1; i++) {
            newPath[j] = str[i];
            j++;
        }
        newPath[j] = '\0'; 
       
        if (unlink(newPath) != 0)
            printf("-myShell: unlink: %s: No such file or directory\n", newPath);
    } else {
        
        
        if (unlink(str) != 0)
            printf("-myShell: unlink: %s: No such file or directory\n", str);
    }
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
void mypipe(char **argv1, char **argv2) {
    int i = 0;
   
    printf("Argv1: ");
    while (strcmp(argv1[i], "|") != 0 && argv1[i] != NULL) {
        printf("%s ", argv1[i]);
        i++;
    }
    printf("\n");

    i++; 

   
    printf("Argv2: ");
    while (argv1[i] != NULL) {
        printf("%s ", argv1[i]);
        i++;
    }
    printf("\n");
}


void move(char **args) {
   
    if (args[1] == NULL || args[2] == NULL) {
        printf("-myShell: move: missing source or destination path\n");
        return;
    }

    
    FILE *source = fopen(args[1], "rb");
    if (source == NULL) {
        printf("-myShell: move: cannot open source file %s\n", args[1]);
        return;
    }

    
    FILE *destination = fopen(args[2], "wb");
    if (destination == NULL) {
        printf("-myShell: move: cannot open destination file %s\n", args[2]);
        fclose(source);
        return;
    }

    
    int ch;
    while ((ch = fgetc(source)) != EOF) {
        fputc(ch, destination);
    }

    
    fclose(source);
    fclose(destination);

    
    if (remove(args[1]) != 0) {
        printf("-myShell: move: cannot remove source file %s\n", args[1]);
    }
}

void echoorite(char **args)
{
   
    if (args[1] == NULL || args[2] == NULL || args[3] != NULL)
    {
        printf("-myShell: echoorite: Invalid number of arguments\n");
        return;
    }

    
    FILE *file = fopen(args[2], "w");
    if (file == NULL)
    {
        printf("-myShell: echoorite: Unable to open file %s\n", args[2]);
        return;
    }

  
    fprintf(file, "%s\n", args[1]);

    
    fclose(file);
}


void read(char **args)
{
    if (args[1] == NULL || args[2] != NULL)
    {
        printf("-myShell: read: Invalid number of arguments\n");
        return;
    }

    FILE *file = fopen(args[1], "r");
    if (file == NULL)
    {
        printf("-myShell: read: Unable to open file %s\n", args[1]);
        return;
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        printf("%s", buffer);
    }

    fclose(file);
}

void wordCount(char **args)
{
    if (args[1] == NULL || args[2] == NULL || args[3] != NULL)
    {
        printf("-myShell: wordCount: Invalid number of arguments\n");
        return;
    }

    FILE *file = fopen(args[2], "r");
    if (file == NULL)
    {
        printf("-myShell: wordCount: Unable to open file %s\n", args[2]);
        return;
    }

    int count = 0;
    char buffer[1024];
    if (strcmp(args[1], "-l") == 0)
    {
        while (fgets(buffer, sizeof(buffer), file) != NULL)
        {
            count++;
        }
        printf("Number of lines in %s: %d\n", args[2], count);
    }
    else if (strcmp(args[1], "-w") == 0)
    {
        while (fscanf(file, "%s", buffer) != EOF)
        {
            count++;
        }
        printf("Number of words in %s: %d\n", args[2], count);
    }
    else
    {
        printf("-myShell: wordCount: Invalid option %s\n", args[1]);
    }

    fclose(file);
}
