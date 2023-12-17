#include <stdio.h>
#include <stdlib.h>
typedef struct array_faces{
float *** pointer_to_array_of_faces;
int length;
int capacity;
int * brightness;
} array_faces;
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
int main(){
        float translateToOrigin[4][4] = {{1, 0, 0, -50},
                                      {0, 1, 0, -50},
                                      {0, 0, 1, -50},
                                      {0, 0, 0, 1}};
    array_faces triangles;
triangles.length=0;
triangles.capacity=0;
float temp_triangles[][4]={{51,10,10,1},{60,10,10,1},{54,15,10,1}};
add_face(4,temp_triangles,1,&triangles);
update_triangles_matrix(translateToOrigin,&triangles);
output_array_faces(&triangles);
return 0;
}