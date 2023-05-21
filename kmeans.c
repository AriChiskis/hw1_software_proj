#include<stdio.h>
#include<stdlib.h>




char* dynamically_read_line(int* line_length){
    int counter = 0;
    int MORE_CHARS = 512;
    char c = 'a';
    size_t num_of_chars_left = MORE_CHARS;
    char* line;
    FILE* file = stdin;
 

     if (file == NULL)
  {
    printf("Error opening file.\n");
    exit(1);
  }

    line = (char*)malloc((MORE_CHARS)*(sizeof(char)));
    if (line == NULL){
        printf("failed to allocate memory :(\n");
        exit(1);
    }

    while((c != '\n' )){

        c = fgetc(file);

        if (ferror(file)){
            printf("there is an error in reading the file :(\n");
            exit(1);
        }
        

        if ( feof(file) ){
            // we have reached the end of the file and we didnt have an empty string
                line = realloc(line,*(line_length) + 1);
                line[*(line_length)] = '\0';
                return line;



        }

        if (c == '\n'){

            line = realloc(line,*(line_length) + 1);
                line[*(line_length)] = '\0';
            return line;

            

        }


        
        if (num_of_chars_left == 0){
            num_of_chars_left = MORE_CHARS*2;
            line = realloc(line,*(line_length) + MORE_CHARS*2);


        }



        line[*(line_length)] = c; 
        *(line_length) +=1;
        num_of_chars_left +=-1;  
        counter +=1;    
        

    }

    printf("fail\n");
    

    return line;
    

}


// STAGE 2

double* convert_line_string_to_double_array(char* line,int* length_line, int* num_of_double_elements,int extracting_row,int* row_dimenstion){
    char* pointer;
    double number;
    double * double_array = (double*)malloc(*(length_line)*sizeof(double));




    number = strtod(((const char*)line),&pointer);
    double_array[*(num_of_double_elements)] = number;

 
    while(*pointer != '\0'){
        *(num_of_double_elements) +=1;
        pointer +=1; // we jump after ',' to go to the next number !


        number = strtod( (const char*)(pointer),&pointer);
        double_array[*(num_of_double_elements)] = number;


    }

    *(num_of_double_elements) +=1;

 
    

    //double_array = realloc(double_array,*(num_of_double_elements)*sizeof(double));

    if (extracting_row) {
        *(row_dimenstion) = *(num_of_double_elements);

    }

    
    double_array = (double*)realloc(double_array,(*(num_of_double_elements))*sizeof(double));

    return double_array;

}


// STAGE 3

double ** create_matrix(int* num_rows_in_matrix_ptr,int* dimension_ptr){

    // VARIABLE DECLERATIONS//

    //GENERAL
    int MORE_LINES = 1024;

    // FOR GEETING THE LINES
    int line_len = 0;
    int* line_len_ptr = &line_len;



    //FOR CONVERTING LINE TO DOUBLE ARRAY

    int num_double_elements = 0;
    int* num_double_element_ptr = & num_double_elements;
    char* LINE;


    // FOR MATRIX
    int number_of_rows_that_are_free = MORE_LINES;

    double** MATRIX;

    // LETS START

    MATRIX = (double**)malloc((MORE_LINES)*(sizeof(double*)));
    if (MATRIX == NULL){
        printf("failed to allocate memory :(\n");
        exit(1);
    }

    ////////////////////////////////////

    LINE = dynamically_read_line(&line_len);
     

    while( *(line_len_ptr) != 0 ){


        if (*(dimension_ptr) == 0 ){
        MATRIX[*(num_rows_in_matrix_ptr)] = convert_line_string_to_double_array(LINE,&line_len,&num_double_elements,1,dimension_ptr);

        }

        else{
            MATRIX[*(num_rows_in_matrix_ptr)] = convert_line_string_to_double_array(LINE,&line_len,&num_double_elements,0,dimension_ptr);
            
            }


        *(num_rows_in_matrix_ptr) +=1;
        number_of_rows_that_are_free += -1;
        *(line_len_ptr) = 0;
        *(num_double_element_ptr) = 0;

        if ( (number_of_rows_that_are_free)  == 0 ) {

            MATRIX = (double**) realloc(MATRIX,(*(num_rows_in_matrix_ptr) + MORE_LINES)*sizeof(double*));

            if (MATRIX == NULL) {
                printf("failed to REALLOCATE MEMORY");
                exit(1);

            }


            number_of_rows_that_are_free = MORE_LINES;

        }

    // FINISHED READING THIS LINE. NOW NEED TO FREE IT AND READ ANOTHERONE

        *(line_len_ptr) = 0;
        free(LINE);

        LINE = dynamically_read_line(&line_len);


    }

    //FINISHED TO GER ALL THE MATRIX ROWS. NOW REACLLOCATE IT TO THE PROPER AMOUNT OF ROWS THAT THERE ARE
   
    

    printf(" returning :   %p matrix \n",MATRIX);

    return MATRIX;

    }




// LENGTH FUNCTION

double LENGTH(double* V1, double* V2,int dimension){

    double RESULT = 0;
    double SUBTRACTION = 0;
    int i =0;
    for(i = 0; i < dimension ; i++){
        SUBTRACTION = V1[i] - V2[i];
        RESULT +=  ( (SUBTRACTION)*(SUBTRACTION) );
    }


    return RESULT;

}


// CLASSIFY FUNCTION

int CLASSIFY_CENTROID(double* X_i,int K, int dimension,double* CENTROIDS){
    // printf("passed\n");

    int RESULT = -1;
    double MINIMUM = __DBL_MAX__;
    double MINIMUM_CONTENDER;
    int j = 0;

    for(j = 0; j < K ; j++) {

        MINIMUM_CONTENDER = LENGTH(X_i,(CENTROIDS + j*K),dimension);
        // printf("passed\n");
        if (MINIMUM_CONTENDER < MINIMUM) {
            MINIMUM = MINIMUM_CONTENDER;
            RESULT = j;
        }
        
    }

    
    return RESULT;

}


// UPDATE CENTROID FUNCTION

int UPDATE_CENTROIDS(double** matrix,int k,int dimension,int num_rows, double* centroids,double* new_centroids , int* numbers_of_elements_in_each_kluster  ){
    // printf("passed\n");

    printf("\nprinting addresses :centroids  %p \n",centroids);


    printf("printing addresses : new_centroids  %p\n",new_centroids);
    printf("printing addresses : num_elements  %p\n",numbers_of_elements_in_each_kluster);

    printf("\n");


    

    int enough_precision = 0;
    long double EPSILON = 0.000001;

    int i = 0;
    int j = 0;
    int index = 0;

    for (i = 0; i < k ; i++){
        numbers_of_elements_in_each_kluster[i] = 0;
    }

    for(i= 0 ; i < k ; i++){
        // printf("passed\n");
            for (j= 0; j < dimension ; j ++){
            new_centroids[i*k + j] = 0;
            }
    }


    for(i = 0 ; i < num_rows ; i++ ){
        // printf("[assed\n");
        index = CLASSIFY_CENTROID(matrix[i],k,dimension,&centroids[0]);
        numbers_of_elements_in_each_kluster[index] +=1;

        for (j = 0; j < dimension ; j++){
            new_centroids[index*k + j] += matrix[i][j];
        }

    }



//        printf("printing addresses : new_centroids  %p\n",new_centroids);

//         for(i = 0 ; i < k ; i++){

//         for (j = 0 ; j < (dimension) ; j++) {
//             printf("%.4f ",new_centroids[i*k + j]);
//         }

//     printf("\n");
//     }
// exit(1);
//     printf("printing addresses : num_elements  %p\n",numbers_of_elements_in_each_kluster);

//         for(i = 0 ; i < k ; i++){

//             printf("%d ",numbers_of_elements_in_each_kluster[i]);
        
//     }
//     printf("\n");

// exit(1);
    // printf("passed\n");

    for (i = 0 ; i < k ; i++){
        for (j =0 ; j < dimension ; j++){
            new_centroids[i*k + j] = ( (new_centroids[i*k + j])*((double) 1 / (double) ( numbers_of_elements_in_each_kluster[i])) );

        }
    }

    for(i = 0; i < k ; i++){
        if (LENGTH(centroids + i*k , new_centroids + i*k , dimension) >= EPSILON) {
            enough_precision = 1;

        }
    }
    
    for (i = 0 ; i < k ; i++){
        for (j =0 ; j < dimension ; j++){
            centroids[i*k + j] = new_centroids[i*k + j];

        }

    }


// printf("printing addresses :centroids  %p \n",centroids);

//         for(i = 0 ; i < k ; i++){

//         for (j = 0 ; j < (dimension) ; j++) {
//             printf("%.4f ",centroids[i*k + j]);
//         }

//     printf("\n");
//     }
//     printf("\n");

//     printf("printing addresses : new_centroids  %p\n",new_centroids);

//         for(i = 0 ; i < k ; i++){

//         for (j = 0 ; j < (dimension) ; j++) {
//             printf("%.4f ",new_centroids[i*k + j]);
//         }

//     printf("\n");
//     }
//     printf("\n");



//     printf("printing addresses : num_elements  %p\n",numbers_of_elements_in_each_kluster);

//         for(i = 0 ; i < k ; i++){

//             printf("%d ",numbers_of_elements_in_each_kluster[i]);
        
//     }
//     printf("\n");




//     exit(1);





return enough_precision;

}







int main(int argc, char* argv[]){

    int k = 15;
    int num_of_rows = 0;
    int* num_of_rows_ptr = & num_of_rows;
    int dimension = 0;
    int* dimension_ptr = & dimension;
    int k_dimen;
    double* centroids;
    double* new_centroids;
    int* numbers_of_elements_in_each_kluster;

    int i = 0;
    int j = 0;
    int precision = 1;

    // INITIALIZE CENTROIDS
   
    double** MATRIX = create_matrix(&num_of_rows, &dimension);
     k_dimen = k*(*dimension_ptr);

         printf("\n\n\n\n returning :   %p matrix \n\n\n\n",MATRIX);


    numbers_of_elements_in_each_kluster = (int*)malloc(k*sizeof(int));
    if (numbers_of_elements_in_each_kluster == NULL){
        printf("failed Allocating Memory :( \n");
        exit(1);
    }


    centroids = (double*)malloc((k_dimen)*sizeof(double));
    if (centroids == NULL){
        printf("we have a problem allocating centroids dog (: \n");
        exit(1);
    }


    new_centroids = (double*)malloc((k_dimen)*sizeof(double));
    if (new_centroids == NULL){
        printf("we have a problem allocating centroids dog (: \n");
        exit(1);
    }

  


    for(i = 0 ; i < k ; i++){
        for (j = 0 ; j < *(dimension_ptr) ; j++) {
            centroids[i*k + j] = MATRIX[i][j];
        }

    }

    for(i = 0 ; i < k ; i++){

        for (j = 0 ; j < *(dimension_ptr) ; j++) {
            printf("%.4f ",centroids[i*k + j]);
        }

    printf("\n");
    }

printf("\n\n\n");
    /////////////////////////////////////////////
    
    // ALGORITHM

    printf("printing addresses :centroids  %p \n",centroids);

        for(i = 0 ; i < k ; i++){

        for (j = 0 ; j < *(dimension_ptr) ; j++) {
            printf("%.4f ",centroids[i*k + j]);
        }

    printf("\n");
    }
    printf("\n");

    // printf("printing addresses : new_centroids  %p\n",new_centroids);

    //     for(i = 0 ; i < k ; i++){

    //     for (j = 0 ; j < *(dimension_ptr) ; j++) {
    //         printf("%.4f ",new_centroids[i*k + j]);
    //     }

    // printf("\n");
    // }
    // printf("\n");



    // printf("printing addresses : num_elements  %p\n",numbers_of_elements_in_each_kluster);

    //     for(i = 0 ; i < k ; i++){

    //         printf("%d ",numbers_of_elements_in_each_kluster[i]);
        

    
    // }




    while ( i < 200 && precision == 1){
        precision = UPDATE_CENTROIDS( MATRIX ,k,*(dimension_ptr),*(num_of_rows_ptr),centroids,new_centroids,
        numbers_of_elements_in_each_kluster);
        i +=1;
        // printf(" i is :: %d \n",i);


    //     // printf("printing addresses :centroids  %p \n",centroids);

    //     for(i = 0 ; i < k ; i++){

    //     for (j = 0 ; j < *(dimension_ptr) ; j++) {
    //         printf("%.4f ",centroids[i*k + j]);
    //     }

    // printf("\n");
    // }
    // printf("\n");

    // printf("printing addresses : new_centroids  %p\n",new_centroids);

    //     for(i = 0 ; i < k ; i++){

    //     for (j = 0 ; j < *(dimension_ptr) ; j++) {
    //         printf("%.4f ",new_centroids[i*k + j]);
    //     }

    // printf("\n");
    // }
    // printf("\n");

    // // exit(1);
    }

    for( i = 0 ; i < k ; i++){
        // printf("adress of centroid number %d is %p \n",a, & centroids[a]);

        for (j = 0 ; j < *(dimension_ptr) ; j++) {
            printf("%.4f ",centroids[i*k + j]);
        }
        printf("\n");
    }
    printf("\n");


    
    // FREE ALL THE ROWS

    printf("%p matrix \n",MATRIX);

    for(i = 0; i < *(num_of_rows_ptr) ; i++) {
        //  printf("%d \n", i);
        printf("%d\n",i);
        if (i == 1000){
        }
        free(*(MATRIX + i));
    }

    printf("free everybody\n\n\n");

    printf("the buggg\n\n");

    printf("%p matrix \n",MATRIX);

    free(numbers_of_elements_in_each_kluster);
    printf("free everybody\n\n\n");
    free(new_centroids);
    printf("kaka");
    printf("free everybody\n\n\n");
    free(centroids);
    printf("free everybody\n\n\n");
    free(MATRIX);
    printf("free everybody\n\n\n");
 

    return 0;
}
