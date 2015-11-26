/*
Martin Bednar
save and load two dimensional vector of int to a file
*/

#include "stdio.h"
#include <stdlib.h>

#define ROWS 2
#define COLUMNS 2

const char* fname = "map.dat";

void saveToFile(int array[ROWS][COLUMNS])
{
    FILE *f = fopen("file.txt", "wb");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    int i = 0;
    int j = 0;
    const int separator = -1;
    const int endOfStream = -2;
    for(i = 0; i< ROWS; ++i)
    {
        for(j = 0; j< COLUMNS; ++j)
        {
            fwrite(&array[i][j], sizeof(int), 1, f);
        }
        fwrite(&separator, sizeof(int), 1, f);
    }
    fwrite(&endOfStream, sizeof(int), 1, f);
    fclose(f);
}
void loadFromFile()
{
    int* row;
    int **array;
    row = malloc((1)*sizeof(int));
    array = malloc(sizeof(int*));

    FILE *f = fopen("file.txt", "rb");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    int x = 0;
    int i = 0;
    int r = 0; //number of rows

    while(1)
    {
        fread(&x, sizeof(x), 1, f);
        i++;
        if(feof(f))
        {
            break;
        }
        printf("%d\n",x);
        if(x == -1)
        {
            int a;
            for(a = 0; a < i; a++)
            {
                array[a] = malloc(sizeof(int));
                array[r][a] = row[a];
                printf(" re %d\n",array[r][a]);
            }
            r++;
            array = realloc(array, (r+1) * sizeof(int*));
            i = 0;
        }
        row = realloc(row, (i+1) * sizeof(int));
        row[i] = x;
    }


    int k;
    printf("*************\n");
    for(k = 1; k < i; k++)
    {
        printf("%d %d\n",k, row[k]);
    }

    fclose(f);
}

int main(int argc, char **argv)
{
    int array[2][2];
    array[0][0] = 2;
    array[1][0] = 7;
    array[0][1] = 8;
    array[1][1] = 9;
    saveToFile(array);
    loadFromFile();
    return 0;
}
