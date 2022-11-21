#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void write_into_file(char *file_name, int num_threads, int num_elements)
{
    FILE *fptr;
    fptr = fopen("Random.txt", "w");
    fprintf(fptr, "%d\n",num_threads);
    fprintf(fptr, "%d\n",num_elements);
    for (int i = 0; i < num_elements; i++)
    {
        int num = rand() % 1000 - 500;
        fprintf(fptr, "%d ", num);
    }
}

int main()
{
    write_into_file("Random.txt",2,10000);
    return 0;
}