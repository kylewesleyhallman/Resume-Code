#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int start;
    int end;
    int count = 0;

    if (argc < 3)
    {
        printf("Must supply a src and dest file\n");
        exit(1);
    }
    //open first file for reading
    FILE *src = fopen(argv[1], "r"); 
    if (!src)
    {
        printf("Cant open %s for reading\n", argv[1]);
        exit(1);
    }

    //open second file for writing
    FILE *dest = fopen(argv[2], "w");
    if (!dest)
    {
        printf("cant open %s for writing\n", argv[2]);
        exit(2);
    }

    //loop through first file, writing data for second as we go.
    char line[1000];
    while (fgets(line, 1000, src) != NULL)
    {
        char newline[1000];
        int i = 0;
        int j = 0;
        for (i = strlen(line)- 1; i >= 0; i--)
        {
            newline[j++] = line[i];
        
        }
        newline[strlen(line)] = '\0'; // have to make sure the string has the null at the end
        fprintf(dest, "%s", newline);
    }
    fclose(src);
    fclose(dest);
} // to run  ./copy NAMEOFFILETOCOPY.c NEWFILENAME.c