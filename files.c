/*
Martin Bednar
save and load two dimensional vector of int to a file
*/

#include "stdio.h"
#include <stdlib.h>

#define ROWS 3
#define COLUMNS 2

const char* fname = "map.dat";

void saveToFile(int array[ROWS][COLUMNS])
{
    FILE *f = fopen(fname, "wb");
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
    array = malloc((1)*sizeof(int*));

    FILE *f = fopen(fname, "rb");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    int x = 0;
    int i = 0;
    int r = 0; //number of rows

    int rows;
    int columns;
    int num_of_sep = 0;

    while(1)
    {
        fread(&x, sizeof(x), 1, f);
        i++;
        if(feof(f))
        {
            break;
        }
        if(x == -2)
        {
            break;
        }
        if(x == -1)
        {
            num_of_sep++;
            int a;
            for(a = 0; a < i ; a++)
            {
                array[a] = realloc(array[a],(1)*sizeof(int*));
                array[r][a] = row[a+1];
            }
            r++;
            array = realloc(array, (r+1) * sizeof(int*));
            rows = i -1 ;
            i = 0;
        }
        row = realloc(row, (i+1) * sizeof(int));
        row[i] = x;
        columns = num_of_sep;
    }

    int c,d;
    for(c = 0; c< columns; c++)
    {
        for(d = 0; d< rows; d++)
        {
            printf("Loaded a[%d][%d] = %d\n",c,d,array[c][d]);
        }
    }
    fclose(f);
}

int main(int argc, char **argv)
{
    int array[ROWS][COLUMNS];
    array[0][0] = 2;
    array[1][0] = 7;
    array[0][1] = 8;
    array[1][1] = 9;
    array[2][0] = 10;
    array[2][1] = 12;
    saveToFile(array);
    loadFromFile();
    return 0;
}
