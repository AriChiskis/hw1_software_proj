#include <stdio.h>



int main() 
{   int result;
    char str1[200];
    char str2[200];
    char str3[200];
    char str4[200];
    char str5[200];
    char str6[200];

    int i;
    char* p;
    int length;
    int length2;
    length = fscanf("%s",str1);
    while(length != EOF){

        p = str1;
        printf("%s",str1);
        printf("\n");
        printf("length is %d",length);
        length = scanf("%s",str1);
        printf("\n");

        // for(int i =0 ; i < 100;i++){
        //     // if (*p == NULL){
        //     //     printf("NULL");
        //     //     exit(1);
        //     // }
        //     printf("%c",*p);
        //     printf("\n");
        //     p++;
        // }
        //printf("\n");
    }
    // length2 = scanf("%s",str2);
    // if(length2!= EOF){
    //     printf("%s",str2);
    //     printf("\n");
    //     printf("length is %d",length2);
    //     printf("\n");
    // }
    // int length3;
    // length3 = scanf("%s",str3);
    // if(length3!= EOF){
    //     printf("%s",str3);
    //     printf("\n");
    //     printf("length is %d",length3);
    //     printf("\n");
    // }

    // if(scanf("%s",str4) != EOF){
    //     printf("%s",str4);
    //     printf("\n");
    // }
    // else{
    //     printf("failed");
    //     printf("\n");
    // }

    // if(scanf("%s",str5) != EOF){
    //     printf("%s",str5);
    //     printf("\n");
    // }
    // else{
    //     printf("failed");
    //     printf("\n");
    // }

    // scanf("%s",str2);
    // printf("%s",str2);
    // printf("\n");
    // scanf("%s",str3);
    // printf("%s",str3);
    // printf("\n");
    // scanf("%s",str4);
    // printf("%s",str4);
    // printf("\n");
    // scanf("%s",str5);
    // printf("%s",str5);
    // scanf("%c",&str6[0]);
    // printf("%s",str6);
   
    
    printf("length is %d",length);
    printf("\n");


    return 0;
}  




#include <stdio.h>
#include<stdlib.h>

int length = 0;
double * get_numbers_array(double* arrayptr){
    // DELARING VARIABLES FOR THE FUNCTION
    double number;
    int starting_space = 4096;
    int space_left = starting_space;
    double* tmp;
    double* indexptr;

    // ALLOCATING MEMORY 
    
    arrayptr = (double*)malloc((starting_space)*sizeof(double));
    indexptr = arrayptr;
    if (arrayptr == NULL) {
        printf("Memory not allocated :(\n");
        exit(0);
    }

    //StARTING TO GET THE ARRAY FROM STDIN (STANDART INPUT) 

    FILE *fp = stdin;
    printf("address of array is %p\n\n",arrayptr);
    while ((fscanf(fp,"%lf,",&number) == 1)) {
        // printf("array %p\n", arrayptr);
        // printf("index %p\n", indexptr);

        length +=1;
        space_left +=-1;
        // printf("space-left is %d\n",space_left);

        if (space_left == 0){

            // THERE IS NO MORE MEMORY AVAILABE SO WE WILL HAVE TO REALLOCATE THE ARRAY.
            starting_space = starting_space*2;
            
           arrayptr = (double*)realloc(arrayptr,(starting_space)*sizeof(double));
           if (arrayptr == NULL) {
            printf("Memory not reallocated :(\n");
            exit(1);
                    }  

            printf("memory added %d\n ",starting_space);
            
            space_left = starting_space;
        }
        // printf("nmumber %d\n is %lf\n",length,number);
        *indexptr = number;
        // printf("%d index value %lf\n",length ,*indexptr);
        indexptr +=1;

    }
    // PUTTING THE LENGTH OF THE ARRAY NAD RETURNING THE ARRAY
    printf("finished putting everything\n");

    //printf("total length is %d\n", *length_of_array);
    //array_ptr = arrayptr;
    //printf("adders of ptr is %p\n",array_ptr);

    indexptr = arrayptr;
 
    printf("address of array is %p\n\n",arrayptr);


    return arrayptr;
    
    }


int main(int* argc, char* argv[]) {
   
    double* array_number;
    double* array_index;
    int* array_positions;
    array_number = get_numbers_array(array_number);
    printf("array memory adress %p\n",array_number);
    array_index = array_number;
    // for (int i = 0; i < length; i++){
    //     printf("number %d is : %lf\n",i,*array_index);
    //     array_index++;
    // }


    




    

    printf("its over ladies and gentelman\n\n\n");
    free(array_number);

    


    return 0;
    }














