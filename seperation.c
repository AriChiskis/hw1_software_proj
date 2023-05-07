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



        length +=1;
        space_left +=-1;
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

        *indexptr = number;
         indexptr +=1;
    }
    // PUTTING THE LENGTH OF THE ARRAY NAD RETURNING THE ARRAY
    printf("finished putting everything\n");
    indexptr = arrayptr;
    printf("address of array is %p\n\n",arrayptr);
    fclose(fp);
    return arrayptr;
    
    }


int main(int* argc, char* argv[]) {
   
    double* array_number;
    double* array_index;
    int* array_positions;
    array_number = get_numbers_array(array_number);
    printf("array memory adress %p\n",array_number);
    array_index = array_number;


    int comma_counter = 0;
    char c;
    char array[100];
    FILE *fp = stdin;
    c = fgetc(stdin);
    for (comma_counter = 0 ; comma_counter < 5; comma_counter++){ 
        printf('\n');
        
        comma_counter +=1;
        printf("%c",c);
        c = fgetc(stdin);
        if (c == (NULL) ){
            printf("yes");
        }
        rewind
    }



    
    printf("dimenstion of a vector is : %d\n\n",comma_counter + 1); 

    


    




    

    printf("its over ladies and gentelman\n\n\n");
    free(array_number);

    


    return 0;
    }














