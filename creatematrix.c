#include<stdio.h>
#include<stdlib.h>



// STAGE 1

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
                line = (char *)realloc(line,(*(line_length) + 1)*sizeof(char));

                if (line == NULL){
                    printf("failed to allocate memory :(\n");
                    exit(1);
                }

                line[*(line_length)] = '\0';
                return line;

        }

        if (c == '\n'){

            line = (char *)realloc(line,(*(line_length) + 1)*sizeof(char));

             if (line == NULL){
                printf("failed to allocate memory :(\n");
                exit(1);
            }               

                line[*(line_length)] = '\0';
            return line;

        }


        
        if (num_of_chars_left == 0){
            num_of_chars_left = MORE_CHARS*2;
            line = realloc(line,*(line_length) + MORE_CHARS*2);

            if (line == NULL){
                printf("failed to allocate memory :(\n");
                exit(1);
            }

        }

        line[*(line_length)] = c; 
        *(line_length) +=1;
        num_of_chars_left +=-1;  
        counter +=1;            

    }
    
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

 
    double_array = (double*) realloc(double_array,*(num_of_double_elements)*sizeof(double));

    if (double_array == NULL){
        printf("failed to reallocate memory :(\n");
        exit(1);
    }

    if (extracting_row) {
        *(row_dimenstion) = *(num_of_double_elements);

    }

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
    // double* double_line_ellements_array;
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
        // printf("completed number of %d iterations\n",*(num_rows_in_matrix_ptr));


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
            printf("i am getting the bug !\n");
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

    

    return MATRIX;

    }




// LENGTH FUNCTION

double LENGTH(double* V1, double* V2,int dimension,double* array_row_centroid){

    double RESULT = 0;
    double SUBTRACTION = 0;
    double SUBTRACTION2 = 0;
    int i = 0;

    double* ptr_to_array = array_row_centroid;
    double* tmp;
 

    for(i = 0; i < dimension ; i++){
        // SUBTRACTION = V1[i] - V2[i];
        // /printf("\n"); 
        tmp = ptr_to_array + i;
        SUBTRACTION2 = V1[i] - *(tmp);
        printf("printing vector: %.4f  %p",*tmp , tmp);
        // RESULT +=  ( (SUBTRACTION)*(SUBTRACTION) );
        RESULT +=  ( (SUBTRACTION2)*(SUBTRACTION2) );


    }
    printf("\n");
    // exit(1);
    return RESULT;

}


// CLASSIFY FUNCTION

int CLASSIFY_CENTROID(double* X_i,int K, int dimension,double CENTROIDS[K][dimension],double* array_centroid){
    // can not use double[][] so we need to do some pointer shit !

    /////////////////////////////////////////
    double* ptr_to_array = array_centroid;
    printf("the address is classify function is : %p  \n",ptr_to_array);
    //////////////////////////////////////////

    int RESULT = -1;
    double MINIMUM = __DBL_MAX__;
    double MINIMUM_CONTENDER;

    for(int j = 0; j < K ; j++) {

        MINIMUM_CONTENDER = LENGTH(X_i,CENTROIDS[j],dimension,&array_centroid[(j*K)]);
        if (MINIMUM_CONTENDER < MINIMUM) {
            MINIMUM = MINIMUM_CONTENDER;
            RESULT = j;
        }
        
    }

    return RESULT;

}


// UPDATE CENTROID FUNCTION

int UPDATE_CENTROIDS(double** matrix,int k,int dimension,int num_rows, double centroids[k][dimension] , double *array_centroids ){
    int enough_precision = 0;

    long double EPSILON = 0.000001;

    double* ptr_to_array = array_centroids;
    printf("the address is UPDATE function is : %p  \n",ptr_to_array);
    //////////////////////////////////////////
    // INITIALIZE NUMBERS IN EACH CLUSTER IN 0

    int numbers_of_elements_in_each_kluster[k];
    for (int i = 0; i < k ; i++){
        numbers_of_elements_in_each_kluster[i] = 0;
    }

    double new_centroids[k][dimension];

    for(int a = 0 ; a < k ; a++){
            for (int b = 0; b < dimension ; b ++){
                new_centroids[a][b] = 0;
            }
    }

    int index;

    for(int i = 0 ; i < num_rows ; i++ ){
        index = CLASSIFY_CENTROID(matrix[i],k,dimension,centroids,&array_centroids[0]);
        numbers_of_elements_in_each_kluster[index] +=1;

        for (int j = 0; j < dimension ; j++){
            new_centroids[index][j] += matrix[i][j];

        }

    }

    for (int i = 0 ; i < k ; i++){
        for ( int j =0 ; j < dimension ; j++){
            new_centroids[i][j] = ( (new_centroids[i][j])*((double) 1 / (double) ( numbers_of_elements_in_each_kluster[i])) );

        }
    }

        for(int i = 0; i < k ; i++){
            if (LENGTH(centroids[i],new_centroids[i],dimension,&array_centroids[i*k]) >= EPSILON) {
                enough_precision = 1;

            }
        }
    
    // SET NEW CENTROIDS
    for (int i = 0 ; i < k ; i++){
        for ( int j =0 ; j < dimension ; j++){
            // centroids[i][j] = ((new_centroids[i][j]));
            array_centroids[(i*k) + j] = 0;
            // *(ptr_to_array + k*i + j) = ((new_centroids[i][j]));
        }

    }

return enough_precision;

}



int main(int argc, char* argv[]){
    int k = 3;
    

    long int iterations = 200; // DEFUALT NUMBER
    
    
    printf("\nk is :  %d\n",k);
    int num_of_rows = 0;
    int* num_of_rows_ptr = & num_of_rows;
    int dimension = 0;
    int* dimension_ptr = & dimension;
    
    /////////////////////////////////////

    double** MATRIX = create_matrix(&num_of_rows, &dimension);

    // INITIALIZE CENTROIDS
    double * Centoirds = (double*)malloc(k*(*dimension_ptr)*sizeof(double));

    if (Centoirds == NULL) {
                printf("failed to ALLOCATE MEMORY");
                exit(1);
            }

    double  centroids[k][*(dimension_ptr)];

    printf("\n\ninizializing centroids \n\n");

    for( int i = 0 ; i < k ; i++){

        for (int j = 0 ; j < *(dimension_ptr) ; j++) {
            centroids[i][j] = MATRIX[i][j];
            // do for the pointer
            double* tmp = Centoirds + i*k + j;
            *(tmp) = MATRIX[i][j];
            printf("%.4lf %p  ",Centoirds[(i*k) + j],&Centoirds[(i*k) + j]);

        }
        printf("\n");


    }

    /////////////////////////////////////////////
    
    // ALGORITHM

    int i = 0;
    int precision = 1;
    while ( i < (iterations) && precision == 1){
        precision = UPDATE_CENTROIDS( MATRIX ,k,*(dimension_ptr),*(num_of_rows_ptr),centroids,&Centoirds[0]);
        // printf("\n iteration %d is completed \n",i);
        i +=1;
    
    }

    printf("\nwhy does it not print\n");
    for( int a = 0 ; a < k ; a++){
        // printf("adress of centroid number %d is %p \n",a, & centroids[a]);
        printf(" diemnsion ptr is %d\n",*(dimension_ptr));
        for (int j = 0 ; j < *(dimension_ptr) ; j++) {
            // printf("%.4lf ",centroids[a][j]);
            printf("%.4lf %p  ",Centoirds[(a*k) + j],&Centoirds[(a*k) + j]);

        }
        printf("\n");
    }
    printf("\n");
    
    // FREE ALL THE ROWS

    for(int i = 0; i < *(num_of_rows_ptr) ; i++) {
    free(MATRIX[i]);
    }

    printf("free everybody\n\n\n");
    free(MATRIX);
    free(Centoirds);

    return 0;
}

