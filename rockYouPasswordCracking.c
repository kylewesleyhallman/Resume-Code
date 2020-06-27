#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "md5.h"

const int PASS_LEN=50;        // Maximum any password can be
const int HASH_LEN=33;        // Length of MD5 hash strings

typedef struct // create struct
    {
        char *word;
        char *hash;
    } Entry;

int stringcmp(const void *a, const void *b)  // fuction for comparing the wordlist strings
    {
        Entry *aa = (Entry*)a;
        Entry *bb = (Entry*)b;
        return strcmp(aa->hash,bb->hash);
    }

int hashcmp(const void *key, const void *element) // function for comparing the hashed passwords
    {
        char *kk = (char *) key;
        Entry *ee = (Entry *) element;
        return strcmp(kk, ee->hash);
    }

    Entry *read_dictionary(char *filename, int *size) // passes in dictionary strings
    {
        struct stat info;
    if (stat(filename, &info) == -1) 
        {
            printf("Can't stat the file"); //file read fail check
            exit(1);
        }
  int filesize = info.st_size;
  
  FILE * d;
  if ((d = fopen(filename, "r")) == NULL) 
    {
      printf("File %s could not be opened for reading\n", filename); //file open fail check
      exit(1);
    }
  
  char *contents = malloc(filesize + 1); // allocate memory space for the file
  fread(contents, 1, filesize, d); // bring in file data
  fclose(d); // close file
  contents[filesize] = '\0';


*size = 0;
for (int i = 0; i < filesize; i++)  //parse through till the end of the file
{
    if (contents[i] == '\n') 
    {
        (*size)++;
    }
}

Entry *dictionary = malloc(sizeof(Entry)*(*size)); // allocate memory for entry

int x = 1;
dictionary[0].word = strtok(contents,"\n"); //tokenize contents
dictionary[0].hash = md5(dictionary[0].word,strlen(dictionary[0].word));

while ((dictionary[x].word = strtok(NULL, "\n")) != NULL) 
{
    dictionary[x].hash = md5(dictionary[x].word,strlen(dictionary[x].word)); // hashes dictionary lists
    x++;
}
return dictionary;
}

int main(int argc, char *argv[])
{
    if (argc < 3) 
    {
        printf("Usage: %s hash_file dict_file\n", argv[0]); //fail safe check
        exit(1);
    }

    int dictsize;
    Entry *dict = read_dictionary(argv[2], &dictsize); //read in dictionary file
    char * frees = dict[0].word;

    qsort(dict, dictsize, sizeof(Entry), stringcmp); // sort 

    FILE *h = fopen(argv[1], "r");
    if (!h) 
    {
        printf("Can't open %s for reading\n", argv[1]);
        exit(1);
    }

    char hash[34];
    Entry *found;
    while (fgets(hash, 34, h) != NULL) 
    {
        *strchr(hash, '\n') = '\0';
        found = bsearch(hash, dict, dictsize, sizeof(Entry), hashcmp); // compares the hashes
        if (found) 
        {
            printf("Hash: %s for Password: %s\n", found->hash, found->word); // when match is found prtin found and the plaintext
        }
        else 
        {
            printf("No hashes found"); // fail check
        }
    }
fclose(h);

free(frees);
for (int i = 0; i < dictsize; i++) 
{
    free (dict[i].hash);//free all
}
free(dict); //free memory 
}