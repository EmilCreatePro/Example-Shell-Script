#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

#define MAX_BLOCK 4096

struct stat v;

void readFolder(char *numeFolder, int *contor)
{
    
    int len;
    struct dirent *pDirent;
    DIR *pDir;
    
    DIR *pSubDir;
    
    char path[100];
    
    struct stat buf;
    
    pDir = opendir (numeFolder);
    
    if (pDir == NULL) 
    {
            printf("Argument is not directory!\n");
            exit(3);
    }
    
    while((pDirent = readdir(pDir)) != NULL)
    {
        strcpy(path, numeFolder);
        strcat(path, "/");
        strcat(path, pDirent->d_name);
        
        if(lstat(path, &buf) == 0)
        {
                if(S_ISDIR(buf.st_mode))
                    {
                        if((strcmp(pDirent->d_name,".") != 0) && (strcmp(pDirent->d_name,"..")))
                        //printf("%s is directoy\n", pDirent->d_name);
                            readFolder( path, contor);
                            
                    }   
                    else
                    {
                        printf("%s is a file\n", pDirent->d_name);
                        if((S_ISREG(buf.st_mode)) && (buf.st_mode & S_IROTH) == 0)
                        (*contor)++;
                    }
                
        }
    }
    
    closedir(pDir);
    
}

int main(int argc, char **argv)  
{ 
    int contor = 0;
    
    int len;
    struct dirent *pDirent;
    DIR *pDir;
        
    if(argc != 2)
    {
        printf("Only one argument!\n");
        exit(1);
    }
    
    
    pDir = opendir (argv[1]);
    
    if (pDir == NULL) 
    {
            printf("Argument is not directory!\n");
            exit(3);
    }
    
    readFolder(argv[1], &contor);
    //pDir = opendir (argv[1]);
    
    
    printf("Avem %d fisiere de drept de READ pt altii.\n", contor);
    return 0;   
}
