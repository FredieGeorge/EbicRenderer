#include <ncurses.h>
#include <stdlib.h>
#include <math.h>
#define THETA 1
#define CENTRE 20
#define SIDE 10
#define X_TRANSLATE 30
#define Y_TRANSLATE -10
#define piec_wise_ceil(a) a==0? 1:1+(int) floor(a)
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

typedef struct array_faces{
float *** pointer_to_array_of_faces;
int length;
int capacity;
int * brightness;
} array_faces;
int calculate_brightness(float** a,float * camera_vec){

    float normal[3];
    normal[0] = a[0][1]*a[1][2]+a[1][1]*a[2][2] +a[2][1]*a[0][2] -(a[0][2]*a[1][1]+a[1][2]*a[2][1]+a[2][2]*a[0][1]);
    normal[1] = a[0][2]*a[1][0]+a[1][2]*a[2][0] +a[2][2]*a[0][0] -(a[0][0]*a[1][2]+a[1][0]*a[2][2]+a[2][0]*a[0][2]);
    normal[2] = a[0][0]*a[1][1]+a[1][0]*a[2][1] +a[2][0]*a[0][1] -(a[0][1]*a[1][0]+a[1][1]*a[2][0]+a[2][1]*a[0][0]);
double brightness_magnitude = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
double camera_vec_magnitude=sqrt(camera_vec[0]*camera_vec[0]+camera_vec[1]*camera_vec[1]+camera_vec[2]*camera_vec[2]);
// Check if the magnitude is non-zero before dividing
if (brightness_magnitude != 0.0) {
    double brightness = normal[0] * camera_vec[0] + normal[1] * camera_vec[1] + normal[2] * camera_vec[2];
    brightness = brightness /(brightness_magnitude*camera_vec_magnitude);
    
    // map brightness if it's positive to an index of ^,\";:Ili!>~+_?-][]}[{1)(/tjrxnucvzXYUJCLQ0OZmwbqdkhdbMo*#MW&8B@M8$

    return    (int) (64.0 * brightness);
} else {
    // Handle the case where the magnitude is zero (division by zero)
    return 0;
}



}
float dot_product(float a[4],float b[4]){


    return (a[0]*b[0]+a[1]*b[1]+a[2]*b[2]+a[3]*b[3]);
}
void matrix_vector_multi(float a[4][4],  float b[4],float* returned){
    ////printf("got into the matrix function");
    for(int i=0;i<4;i++){
        ////printf("lein 31");
        returned[i]= dot_product(a[i],b);
    }
}
void print_vec(float a[4]){
    for(int i=0;i<4;i++){

        printf("%f ",a[i]);
    }
    ////printf("\n");
}
// void rotation_matrix(float theta,float b[4][4]){

void draw_triangle(float** ver,char obj){
    //sort ver based on ver[i][1] and then draw lines
    float * temp_1;
    float x_left;
    float x_right;
    for(int j=0;j<2;j++){
    for(int i=0;i<2;i++){
        if (ver[i][1]<ver[i+1][1]){
            temp_1=ver[i];
            ver[i]=ver[i+1];
            ver[i+1]=temp_1;

        }}}


if ((ver[0][1]==ver[1][1])&&(ver[2][1]==ver[1][1])){
    x_left=min(ver[0][0],min(ver[1][0],ver[2][0]));
    x_right=max(ver[0][0],max(ver[1][0],ver[2][0]));
    move(ver[0][1]+Y_TRANSLATE,ceil(x_left)+X_TRANSLATE);
    hline(obj,piec_wise_ceil(abs(x_left-x_right)));


}
else if (ver[0][1]==ver[1][1]){
for(int i=ver[0][1];i>=ver[2][0];i--){
        x_left=ver[0][0]+(i-ver[0][1])*(((float)(ver[2][0]-ver[0][0]))/(ver[2][1]-ver[0][1]));
        x_right=ver[1][0]+(i-ver[1][1])*(((float)(ver[2][0]-ver[1][0]))/(ver[2][1]-ver[1][1]));
        move(i+Y_TRANSLATE,ceil((min(x_left,x_right)))+X_TRANSLATE);
        hline(obj,piec_wise_ceil(abs(x_left-x_right)));


}}
else if (ver[1][1]==ver[2][1]){
    for(int i=ver[0][1];i>=ver[1][1];i--){
        x_left=ver[0][0]+(i-ver[0][1])*(((float)(ver[1][0]-ver[0][0]))/(ver[1][1]-ver[0][1]));
        x_right=ver[0][0]+(i-ver[0][1])*(((float)(ver[2][0]-ver[0][0]))/(ver[2][1]-ver[0][1]));
        //printf("%f \n",x_left-x_right);
        move(i+Y_TRANSLATE,ceil((min(x_left,x_right)))+X_TRANSLATE);
        hline(obj,piec_wise_ceil(abs(x_left-x_right)));

    }
}
else{
    for(int i=ver[0][1];i>=ver[1][1];i--){
        x_left=ver[0][0]+(i-ver[0][1])*(((float)(ver[1][0]-ver[0][0]))/(ver[1][1]-ver[0][1]));
        x_right=ver[0][0]+(i-ver[0][1])*(((float)(ver[2][0]-ver[0][0]))/(ver[2][1]-ver[0][1]));
        //printf("%f \n",x_left-x_right);
        move(i+Y_TRANSLATE,ceil((min(x_left,x_right)))+X_TRANSLATE);
        hline(obj,piec_wise_ceil(abs(x_left-x_right)));


    }
        for(int i=ver[1][1];i>=ver[2][1];i--){
        x_left=ver[1][0]+(i-ver[1][1])*(((float)(ver[2][0]-ver[1][0]))/(ver[2][1]-ver[1][1]));
        x_right=ver[0][0]+(i-ver[0][1])*(((float)(ver[2][0]-ver[0][0]))/(ver[2][1]-ver[0][1]));
        //printf("%f \n",x_left-x_right);
        move(i+Y_TRANSLATE,ceil((min(x_left,x_right)))+X_TRANSLATE);
        hline(obj,piec_wise_ceil(abs(x_left-x_right)));

    }
}}
void add_face(int no_of_values, float a[3][no_of_values],int brightn, array_faces *x)
{  
    if (x->capacity == 0)
    {   x->brightness=malloc(sizeof(int));
        x->pointer_to_array_of_faces = malloc(sizeof(float **));
        x->capacity = 1;
        x->brightness[x->length]=brightn;
        (x->pointer_to_array_of_faces)[x->length] = (float **)calloc(3, sizeof(float *));
        for (int i = 0; i < 3; i++)
        {
            (x->pointer_to_array_of_faces)[x->length][i] = (float *)calloc(no_of_values, sizeof(float));
            for (int j = 0; j < no_of_values; j++)
            {

                *((x->pointer_to_array_of_faces)[x->length][i] + j) = a[i][j];
            }
        }
        (x->length)++;
    }

    else
    {
        if (x->length == x->capacity)
        {   x->brightness=realloc(x->brightness,2*(x->capacity)*sizeof(int));
            x->pointer_to_array_of_faces = realloc(x->pointer_to_array_of_faces, 2 * (x->capacity) * sizeof(float **));
            x->capacity *= 2;
        }
        x->brightness[x->length]=brightn;
        (x->pointer_to_array_of_faces)[x->length] = (float **)calloc(3, sizeof(float *));
        for (int i = 0; i < 3; i++)
        {(x->pointer_to_array_of_faces)[x->length][i] = (float *)calloc(no_of_values, sizeof(float));
            for (int j = 0; j < no_of_values; j++)
            {

                *(*(((x->pointer_to_array_of_faces)[x->length]) + i) + j) = a[i][j];
            }
        }
        (x->length)++;
    }
}
void update_triangles_matrix(float placeholder[4][4],array_faces* do_me){
    float * result = (float *) calloc(4,sizeof(float));
    float* temp;
    for(int i=0;i<(do_me->length);i++){
        for(int j=0;j<3;j++){
    matrix_vector_multi(placeholder,(do_me->pointer_to_array_of_faces)[i][j],result);
    temp=result;
result=(do_me->pointer_to_array_of_faces)[i][j];
(do_me->pointer_to_array_of_faces)[i][j]=temp;
        }
    }
    free(result);
}


void free_array_faces_entries(array_faces* x){

        for(int i=0;i<x->length;i++){
        for(int j=0;j<3;j++){
            free(x->pointer_to_array_of_faces[i][j]);
        }
        free(x->pointer_to_array_of_faces[i]);
    }
    // free(x->pointer_to_array_of_faces);
    // free(x->brightness);
    // x->length=0;
    // x->capacity=0;


}
void free_array_faces( array_faces* x){
        for(int i=0;i<x->length;i++){
        for(int j=0;j<3;j++){
            free(x->pointer_to_array_of_faces[i][j]);
        }
        free(x->pointer_to_array_of_faces[i]);
    }
    x->length=0;
    x->capacity=0;



}
void output_array_faces( array_faces* x){
//append it to a file
FILE *f = fopen("output.txt", "w");
if (f == NULL)
{
    printf("Error opening file!\n");
    exit(1);
}

/* print integers and floats */
for (int i = 0; i < x->length; i++)
{
    for(int j=0;j<3;j++){
    for(int k=0;k<3;k++){
    fprintf(f, "%f ", x->pointer_to_array_of_faces[i][j][k]);
    }
    fprintf(f, "\n");
    }
    fprintf(f,"%d",x->brightness[i]);
        fprintf(f,"----------------------------------------------------------------------");

    fprintf(f, "\n");
}

fclose(f);



}
void constructRotationMatrix(float rotationMatrix[4][4], float angleX, float angleY, float angleZ) {
    // Convert angles to radians
    angleX = angleX * M_PI / 180.0;
    angleY = angleY * M_PI / 180.0;
    angleZ = angleZ * M_PI / 180.0;

    // Identity matrix
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            rotationMatrix[i][j] = (i == j) ? 1.0 : 0.0;

    // Translate to origin
    float translateToOrigin[4][4] = {{1, 0, 0, 0},
                                      {0, 1, 0, 0},
                                      {0, 0, 1, 0},
                                      {-50, -60, -15, 1}};

    // Rotate
    float rotationX[4][4] = {{1, 0, 0, 0},
                                {0, cos(angleX), -sin(angleX), 0},
                                {0, sin(angleX), cos(angleX), 0},
                                {0, 0, 0, 1}};

    float rotationY[4][4] = {{cos(angleY), 0, sin(angleY), 0},
                                {0, 1, 0, 0},
                                {-sin(angleY), 0, cos(angleY), 0},
                                {0, 0, 0, 1}};

    float rotationZ[4][4] = {{cos(angleZ), -sin(angleZ), 0, 0},
                                {sin(angleZ), cos(angleZ), 0, 0},
                                {0, 0, 1, 0},
                                {0, 0, 0, 1}};

    // Translate back
    float translateBack[4][4] = {{1, 0, 0, 0},
                                  {0, 1, 0, 0},
                                  {0, 0, 1, 0},
                                  {50, 60, 15, 1}};

    // Combine transformations
    multiplyMatrices(translateToOrigin, rotationMatrix, rotationX);
    multiplyMatrices(rotationMatrix, rotationMatrix, rotationY);
    multiplyMatrices(rotationMatrix, rotationMatrix, rotationZ);
    multiplyMatrices(rotationMatrix, rotationMatrix, translateBack);
}

// Function to multiply two matrices
void multiplyMatrices(float result[4][4], float mat1[4][4], float mat2[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
}