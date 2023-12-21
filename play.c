#include <stdio.h>
#include <stdlib.h>
typedef struct vertices{
            float** pointer_to_array_of_vertices;
            int no_of_values;
            int length;
            int capacity;
        }vertices;
typedef struct array_faces{
float *** pointer_to_array_of_faces;
int length;
int capacity;
int * brightness;
} array_faces;
void init_vertices(vertices* x,int no){
    x->pointer_to_array_of_vertices=(float **) malloc(sizeof(float*));
    x->capacity=1;
    x->length=0;
    x->no_of_values=no;
}
void add_vertex(vertices* x,float* vertex){
if (x->length==x->capacity){
    x->pointer_to_array_of_vertices=(float**) realloc(x->pointer_to_array_of_vertices,2*(x->capacity)*sizeof(float*));
    x->capacity=2*(x->capacity);
}
x->pointer_to_array_of_vertices[(x->length)]=(float*) malloc((x->no_of_values)*sizeof(float));
for(int i=0;i<(x->no_of_values);i++){
    x->pointer_to_array_of_vertices[(x->length)][i]=vertex[i];
}
x->length++;
}
void free_vertices(vertices*x){
    for(int i=0;i<(x->length);i++){
        free(x->pointer_to_array_of_vertices[i]);
    }
    free(x->pointer_to_array_of_vertices);
    x->length=0;
}
void print_vertices(vertices *x){

for(int i=0;i<(x->length);i++){
    printf("%d %f %f %f \n",i,x->pointer_to_array_of_vertices[i][0],x->pointer_to_array_of_vertices[i][1],x->pointer_to_array_of_vertices[i][2]);
}
}


int main(){
vertices eeee;
float temp_vertex[4]={1.2,12.213,123.2,1};
init_vertices(&eeee,4);
    FILE *file = fopen("teapot.obj", "r");
    if (file == NULL) {
        return 1;
    }

    char line[256];
    //first extract vertices to an arrays
    while (fgets(line, sizeof(line), file)) {
        printf("im in the file \n");
        if (line[0]=='v'){
        sscanf(line, "v %f %f %f",temp_vertex,temp_vertex+1,temp_vertex+2);
        add_vertex(&eeee,temp_vertex);
        }
    }
    fclose(file);
    print_vertices(&eeee);
    free_vertices(&eeee);
    return 0;
}