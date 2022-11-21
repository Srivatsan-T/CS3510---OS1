#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<time.h>

struct file_entries
{
    int num_threads;
    int num_elements;
    int *keys;
};

struct thread_arg
{
    int left;
    int right;
    int *keys;
};

struct file_entries read_from_file(char *file_name)
{
    struct file_entries out;
    FILE *fptr;
    fptr = fopen(file_name, "r");
    if (!fptr)
    {
        printf("The file doesn't exist");
    }
    else
    {
        int num_thr;
        int num_ele;
        int *ele;
        fscanf(fptr, "%d", &num_thr);
        fscanf(fptr, "%d", &num_ele);
        ele = malloc(sizeof(int) * num_ele);
        for (unsigned i = 0; i < num_ele; i++)
        {
            fscanf(fptr, "%d", (ele + i));
        }
        out.keys = ele;
        out.num_elements = num_ele;
        out.num_threads = num_thr;
        return out;
    }
}

void write_into_file(char *file_name, int num_threads, int num_elements)
{
    FILE *fptr;
    fptr = fopen(file_name, "w");
    fprintf(fptr, "%d\n",num_threads);
    fprintf(fptr, "%d\n",num_elements);
    for (int i = 0; i < num_elements; i++)
    {
        int num = rand() % 1000 - 500;
        fprintf(fptr, "%d ", num);
    }
}

int *merge(int *arr, int left, int middle, int right)
{
    int *left_array = malloc(sizeof(int) * (middle - left + 1));
    int *right_array = malloc(sizeof(int) * (right - middle));

    for (unsigned i = 0; i < middle - left + 1; i++)
    {
        *(left_array + i) = *(arr + i + left);
    }
    for (unsigned i = 0; i < right - middle; i++)
    {
        *(right_array + i) = *(arr + i + middle + 1);
    }
    int i, j, k;
    i = j = 0;
    k = left;

    while (i < middle - left + 1 && j < right - middle)
    {
        if (*(left_array + i) <= *(right_array + j))
        {
            *(arr + k) = *(left_array + i);
            i++;
        }
        else
        {
            *(arr + k) = *(right_array + j);
            j++;
        }
        k++;
    }

    while (i < middle - left + 1)
    {
        *(arr + k) = *(left_array + i);
        i++;
        k++;
    }
    while (j < right - middle)
    {
        *(arr + k) = *(right_array + j);
        j++;
        k++;
    }

    free(left_array);
    free(right_array);
}

void merge_sort(int *arr, int left, int right)
{
    int middle;
    if (right > left)
    {
        middle = (left + right) / 2;
        merge_sort(arr, left, middle);
        merge_sort(arr, middle + 1, right);
        merge(arr, left, middle, right);
    }
}

void *threaded_merge_sort(void *struc)
{
    struct thread_arg *fp = (struct thread_arg *)struc;
    //printf("%d : %d\n", fp->left, fp->right);
    merge_sort(fp->keys, fp->left, fp->right);
}

void threaded_sort(int *arr, int num_thr, int num_ele)
{
    pthread_attr_t var;
    pthread_attr_init(&var);
    struct thread_arg *fp = malloc(sizeof(struct thread_arg) * num_thr);
    pthread_t *thread_ids = malloc(sizeof(pthread_t *) * num_thr);

    for (unsigned i = 0; i < num_thr - 1; i++)
    {
        (fp + i)->keys = arr;
        (fp + i)->left = i * num_ele / num_thr;
        (fp + i)->right = (i + 1) * (num_ele / num_thr) - 1;
    }
    (fp + num_thr - 1)->keys = arr;
    (fp + num_thr - 1)->left = (num_thr - 1) * (num_ele / num_thr);
    (fp + num_thr - 1)->right = num_ele - 1;
    for (unsigned i = 0; i < num_thr; i++)
    {
        pthread_create(thread_ids + i, &var, threaded_merge_sort, (void *)(fp + i));
    }
    for (int i = 0; i < num_thr; i++)
    {
        pthread_join(*(thread_ids + i), NULL);
    }
    for(unsigned i = 0;i<num_thr - 1;i++)
    {
        merge(arr,0,(fp+i)->right,(fp+i+1)->right);
    }
}



int main()
{
    write_into_file("Random.txt",2,100);
    struct file_entries fp = read_from_file("Random.txt");
    // printf("%d", fp.num_threads);
    // printf("%d", fp.num_elements);
    clock_t start,end;
    start = clock();
    threaded_sort(fp.keys, fp.num_threads, fp.num_elements);
    end = clock();
    printf("Time taken to execute the process is %lf\n",(double)(end-start)/CLOCKS_PER_SEC);
    /*
    for (unsigned i = 0; i < fp.num_elements; i++)
    {
        printf("%d : ", *(fp.keys + i));
    }
    */
}