#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Function prototypes. 
unsigned char * read_card(char * fname, int *size);
void save_jpeg(unsigned char * data, int size, char * fname);
void recover(unsigned char * data, int size);

void recover(unsigned char *data, int size)
{
    int counter=0;
    int picsize ;
    for (int i = 0; i < size; i += 512)
        {
            if (data[i] == 0xff)
        {
            if (data[i+1] == 0xd8)
        {
            if (data[i+2] == 0xff)
        {
            if (data[i+3] == 0xe0 || data[i+3] == 0xe1)
        {
            counter++;
            //look for end of file
            while (data[i] != 0xff && data[i+1] != 0xd9 && data[i+2] != 0) {
            i++;
        }
            //generate file name
            char filename[25];
            sprintf(filename, "image%d.jpg", counter);
            //find picture size
                picsize = i;
                //save file
                save_jpeg(&data[i],picsize/29,filename);
                }
            }
        }
    }
}

printf("%d Images Found\n",counter);
printf("creating...");




}

int main()
{
    // Read the card.raw file into an array of bytes (unsigned char)
    int card_length;
    unsigned char *card = read_card("card.raw", &card_length);
    
    // Recover the images
    recover(card, card_length);
}

unsigned char * read_card(char * fname, int * size)
{

    struct stat st;
    if (stat(fname, &st) == -1)
    {
        fprintf(stderr, "Can't get info about %s\n", fname);
        exit(1);
    }
    int len = st.st_size;
    unsigned char *raw = (unsigned char *)malloc(len * sizeof(unsigned char));
    
    FILE *fp = fopen(fname, "rb");
    if (!fp)
    {
        fprintf(stderr, "Can't open %s for reading\n", fname);
        exit(1);
    }
    
    char buf[512];
    int r = 0;
    while (fread(buf, 1, 512, fp))
    {
        for (int i = 0; i < 512; i++)
        {
            raw[r] = buf[i];
            r++;
        }
    }
    fclose(fp);
    
    *size = len;
    return raw;
}

void save_jpeg(unsigned char * data, int size, char * fname)
{
    FILE *fp = fopen(fname, "wb");
    if (!fp)
    {
        fprintf(stderr, "Can't write to %s\n", fname);
        exit(1);
    }
    
    fwrite(data, 1, size, fp);
    fclose(fp);   
}

