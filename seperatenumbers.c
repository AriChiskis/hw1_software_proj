#include <stdio.h>
#include<stdlib.h>



 

double * get_numbers_array(double* arrayptr){
    // DELARING VARIABLES FOR THE FUNCTION
    double number;
    int length = 0
    int starting_spcae = 4096;
    int spcae_left= starting_space;
    //double* arrayptr;
    double* tmp;
    double* indexptr;

    // ALLOCATING MEMORY 
    
    arrayptr = (double*)malloc((starting_spcae)*sizeof(double));
    indexptr = arrayptr;
    if (arrayptr == NULL) {
        printf("Memory not allocated :(\n");
        exit(0);
    }

    //StARTING TO GET THE ARRAY FROM STDIN (STANDART INPUT) 
    FILE *fp = stdin;

    while ((fscanf(fp,"%lf,",&number) == 1)) {
        printf("array %p\n", arrayptr);
        printf("index %p\n", indexptr);

        length +=1;
        spcae_left +=-1;
        printf("space-left is %d\n",spcae_left);

        if (spcae_left == 0){

            // THERE IS NO MORE MEMORY AVAILABE SO WE WILL HAVE TO REALLOCATE THE ARRAY.
            starting_spcae = starting_spcae*2;
            
           tmp = (double*)realloc(arrayptr,(starting_spcae)*sizeof(double));
           if (tmp == NULL) {
            printf("Memory not reallocated :(\n");
            exit(1);
                    }  

            printf("memory added 200\n ");
            arrayptr = tmp;
            spcae_left = starting_spcae;
        }
        //printf("nmumber %d\n is %lf\n",length,number);
        *indexptr = number;
        printf("%d index value %lf\n",length ,*indexptr);
        indexptr +=1;

    }
    // PUTTING THE LENGTH OF THE ARRAY NAD RETURNING THE ARRAY
    printf("finished putting everything\n");

    //printf("total length is %d\n", *length_of_array);
    //array_ptr = arrayptr;
    //printf("adders of ptr is %p\n",array_ptr);
    free(indexptr);

    return arrayptr;
    
    }





int main(int* argc, char* argv[]) {
   
    double* array_number;
    int* array_length;
    array_number = get_numbers_array(array_number);
    printf("array memory adress %p",array_number);

    //free(array_length);
    free(array_number);

    


    return 0;
    }
















        // FILE *fp = stdin;
    //  if (fp == NULL){
    //      fprintf(stderr, "Cannot open %s\n", "numbers.txt");
    //      return 1;
    //  }
    // int count = 0;
    // double d, sum = 0.0;
    // while ((fscanf(fp,"%lf,",&d) == 1)) {
    //     printf("%.4lf",d);
    //     printf("\n");
    //     sum += d;
    //     count++;
    // }
    // printf("read %d numbers, sum: %g\n", count, sum);
    // return 0;