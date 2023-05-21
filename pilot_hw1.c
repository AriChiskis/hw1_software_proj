#include<stdio.h>
#include<stdlib.h>


char* dynamically_read_line(int* line_length){
    int counter = 0;
    int MORE_CHARS = 512;
    char c = 'a';
    size_t num_of_chars_left = MORE_CHARS;
    char* line;
    FILE* file = stdin;
 

     if (file == NULL){
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




double* convert_line_string_to_double_array(char* line,int* length_line, int* num_of_double_elements,int extracting_row,int* row_dimenstion){
    char* pointer;
    double number;
    double * double_array = (double*)malloc(*(length_line)*sizeof(double));


    number = strtod(((const char*)line),&pointer);
    double_array[*(num_of_double_elements)] = number;

 
    while(*pointer != '\0'){
        *(num_of_double_elements) +=1;
        pointer +=1; 


        number = strtod( (const char*)(pointer),&pointer);
        double_array[*(num_of_double_elements)] = number;


    }

    *(num_of_double_elements) +=1;

    double_array = realloc(double_array,*(num_of_double_elements)*sizeof(double));

    if (extracting_row) {
        *(row_dimenstion) = *(num_of_double_elements);

    }

    return double_array;

}




double ** create_matrix(int* num_rows_in_matrix_ptr,int* dimension_ptr){

    int MORE_LINES = 1024;
    int line_len = 0;
    int* line_len_ptr = &line_len;

    int num_double_elements = 0;
    int* num_double_element_ptr = & num_double_elements;
    char* LINE;
    
    int number_of_rows_that_are_free = MORE_LINES;

    double** MATRIX;

    

    MATRIX = (double**)malloc((MORE_LINES)*(sizeof(double*)));

    if (MATRIX == NULL){
        printf("failed to allocate memory :(\n");
        exit(1);
    }

    

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
                printf("failed to REALLOCATE MEMORY in matrix");
                exit(1);

            }    

            number_of_rows_that_are_free = MORE_LINES;

        }


        *(line_len_ptr) = 0;
        free(LINE);

        LINE = dynamically_read_line(&line_len);


    }


    return MATRIX;

    }






double LENGTH(double* V1, double* V2,int dimension){

    double RESULT = 0;
    double SUBTRACTION = 0;
    int i = 0;

    for( i = 0; i < dimension ; i++){
        SUBTRACTION = V1[i] - V2[i];

        RESULT +=  ( (SUBTRACTION)*(SUBTRACTION) );
    }


    return RESULT;

}





int CLASSIFY_CENTROID(double* X_i,int K, int dimension,double* CENTROIDS){


    int RESULT = -1;
    double MINIMUM = __DBL_MAX__;
    double MINIMUM_CONTENDER;
    int j = 0;
    double* centroids_number_j_ptr;

    for( j = 0; j < K ; j++) {

    centroids_number_j_ptr = CENTROIDS + j*(dimension);
        
        MINIMUM_CONTENDER = LENGTH(X_i , centroids_number_j_ptr , dimension);

        if (MINIMUM_CONTENDER < MINIMUM) {
            MINIMUM = MINIMUM_CONTENDER;
            RESULT = j;
        }
        
    }

    return RESULT;

}


int UPDATE_CENTROIDS(double** matrix, int k, int dimension,int num_rows ,double* centroids ,double* new_centroids, int* num_of_elem_in_cluster){
    int enough_precision = 0;
 
    long double EPSILON = 0.000001;

    int i = 0;
    int j = 0;
    int a = 0;
    int b = 0;
    int index = 0;



    for ( i = 0; i < k ; i++){
        num_of_elem_in_cluster[i] = 0;
    }

    
    for( a = 0 ; a < k ; a++){
            for ( b = 0; b < dimension ; b ++){
                new_centroids[a*(dimension) + b] = 0;
            }
    }


    for( i = 0 ; i < num_rows ; i++ ){

        index = CLASSIFY_CENTROID(matrix[i],k,dimension,centroids);
        num_of_elem_in_cluster[index] +=1;

        for ( j = 0; j < dimension ; j++){
            new_centroids[index*(dimension) + j] += matrix[i][j];

        }

    }



    for ( i = 0 ; i < k ; i++){
        for (  j =0 ; j < dimension ; j++){
            new_centroids[i*(dimension) + j] = ( (new_centroids[i*(dimension) + j])*((double) 1 / (double) ( num_of_elem_in_cluster[i])) );

        }
    }

        for( i = 0; i < k ; i++){
            if (LENGTH(centroids + i*dimension , new_centroids + i*dimension , dimension) >= EPSILON) {
                enough_precision = 1;

            }
        }
    
    for ( i = 0 ; i < k ; i++){
        for (  j =0 ; j < dimension ; j++){
            centroids[i*(dimension) + j] = ((new_centroids[i*(dimension) + j]));

        }

    }

return enough_precision;

}


   




int main(int argc, char* argv[]){

    int k;
    int iteration = 200;
    int num_of_rows = 0;
    int dimension = 0;
    int i = 0;
    int j = 0;
    int a = 0;
    int precision = 1;
    int* num_of_rows_ptr = & num_of_rows;
    int* dimension_ptr = & dimension;

    double** MATRIX;
    
    double* centroids;
    double* new_centroids;
    int* num_of_elem_in_kluster;

    int kluster_times_dimensions;

    MATRIX = create_matrix(&num_of_rows, &dimension);
    

    k = atoi(argv[1]);
    if ( (k <=1) || ( k >= (*(num_of_rows_ptr)) ) ){
        printf("invalid number of clusters\n");
        exit(1);
    }

    if (argc > 2 ){
        iteration = atoi(argv[2]);
        if ( (iteration <= 1) || (iteration >= 1000) ){
             printf("invalid number of iterations\n");
            exit(1);

        }

    }
    


    kluster_times_dimensions = *(dimension_ptr)*k;

    centroids = malloc(kluster_times_dimensions*sizeof(double));

    if (centroids ==NULL){
        printf("failed to allocate memory centroids\n");
        exit(1);
    }

    new_centroids = malloc(kluster_times_dimensions*sizeof(double));

      if (new_centroids ==NULL){
        printf("failed to allocate memory new centroids\n");
        exit(1);
    }

    num_of_elem_in_kluster = malloc(k*sizeof(int));

      if (num_of_elem_in_kluster ==NULL){
        printf("failed to allocate memory klusters\n");
        exit(1);
    }






    for(  i = 0 ; i < k ; i++){

        for ( j = 0 ; j < *(dimension_ptr) ; j++) {

 
            centroids[i*(*dimension_ptr) + j] = MATRIX[i][j];
                    
            }

    }





    i  = 0;
    j = 0;
    a = 0;

  
    while ( i < iteration && precision == 1){
        precision = UPDATE_CENTROIDS(MATRIX,k,*(dimension_ptr),*(num_of_rows_ptr),centroids,new_centroids,num_of_elem_in_kluster);
        i +=1;
    
    }

    for(  a = 0 ; a < k ; a++){

        for ( j = 0 ; j < *(dimension_ptr) ; j++) {

            if (j == (*(dimension_ptr) - 1) ){
                printf("%.4f\n",centroids[a*(*(dimension_ptr)) + j]);

            }
            else{
                printf("%.4f,",centroids[a*(*(dimension_ptr)) + j]);
            }


        }
    }
    printf("\n");    


    for( i = 0; i < *(num_of_rows_ptr) ; i++) {
    free(MATRIX[i]);
    }

    free(num_of_elem_in_kluster);
    free(centroids);
    free(new_centroids);
    free(MATRIX);

    return 0;
}


