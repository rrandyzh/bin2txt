/*************************************************************************
  > File Name: bin2c.c
  > Author: randy 
  > Mail: rrandy@163.com
  > Created Time: 2016-09-06 17:41:25
 ************************************************************************/

#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main ( int argc, char** argv  )
{
    int i = 0;
    int target_fd = 0;
    unsigned char ch = '\0';
    unsigned long data_length = 0x00;
    char outputFileName[100];

    if ( 2 != argc  ) {
        printf( "\n    Usage: bin2c <file> \n\n"  );
        return 1;
    }

    FILE *binfile = fopen( argv[1], "rb"  );

    // get file name for array's name
    while ( '.' != argv[1][i++]  );
    argv[1][ i-1  ] = 0;
    sprintf(outputFileName,"%s.txt", argv[1]);
    FILE *cfile = fopen(outputFileName, "w");
    if(cfile == NULL)
    {
        printf(" create file failed\n");
        return 1;
    }

    printf("start...\n");

    //get file data and change to const unsigned char array's data
    i = 1;
    //while ( EOF != (ch = fgetc(binfile)))
    while(!feof(binfile))
    {
        ch = fgetc(binfile);
        if(i < 16) {
            fprintf(cfile, "0x%02X, ", (unsigned char)ch);
        }
        else if(i==16) {
            fprintf(cfile, "0x%02X,", (unsigned char)ch);
            fprintf(cfile,"\n");
            i = 0;
        }
        i++;
    }

    fflush(cfile);
    fseek(cfile,0L,SEEK_END);
    data_length=ftell(cfile);
    printf("file size: %ld\n", data_length);
    fclose(cfile);

    fclose(binfile);
    truncate(outputFileName, data_length-6);
    printf("Done. %s is ready!\n",outputFileName);
    return 0;
}

