#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_BLOCK 4096

struct stat v;

int main(int argc, char **argv)  
{ 
    char *buff = malloc(MAX_BLOCK);
    char lit;
    int file;
    int len;
    int nrCifre = 0;
    char path[100];
    int fout;
    
    if(argc != 3) //3 pt ca primul e exe
    {
        printf("\nUsage: <%s> fileIn dirOut\n", argv[0]);
        exit(1);
    }
    
    file = open(argv[1], O_RDONLY);
    
    if(file == (-1))
    {
        printf("\nNu s-a putut citi fisierul!\n");
        exit(2);
    }
    
    
    
    while((len = read(file, buff, MAX_BLOCK)) > 0)
    {
        
        for(int i = 0; i < len; i++)
        {
            if(isdigit(buff[i])) nrCifre++;
            //printf("\nbuff[%d] = %c", i, buffer[i]);
        }
    }
    
    
    
    printf("\nHello, avem %d cifre!\n", nrCifre);
    int ret = close(file);
    
    strcpy(path, argv[2]);
    strcat(path, "/");
    strcat(path, argv[1]);
    
    
    printf("Calea va fi: %s\n", path);
    
    fout = creat(path, S_IRUSR | S_IWUSR);
    
    if(fout == -1)
    {
        printf("\nNu s-a putut crea fisierul!\n");
        exit(3);
    }
    
    
    sprintf(buff, "User: %s Cifre: %d", getUID(), nrCifre);
    //itoa(buff, nrCifre, 10);
    
    int DC = write(fout, buff, strlen(buff));
    
    return close(file);
}

