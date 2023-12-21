#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses.h>
#define X_TRANSLATE 30
#define Y_TRANSLATE 5
#define Z_correction 10
#define piec_wise_ceil(a) a==0? 1:1+(int) floor(a)
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

typedef struct vertices{
            float** pointer_to_array_of_vertices;
            int no_of_values;
            int length;
            int capacity;
        }vertices;
typedef struct fb{
float *** pointer_to_array_of_faces;
int length;
int capacity;
int * brightness;
} fb;
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

void init_fb(fb* x){
    x->pointer_to_array_of_faces=(float***) malloc(sizeof(float**));
    x->brightness=(int*) malloc(sizeof(int));
    x->capacity=1;
}
void add_face(fb* x,float * a,float *b,float *c,int bright){
if (x->length==x->capacity){
    x->pointer_to_array_of_faces=(float***) realloc(x->pointer_to_array_of_faces,2*(x->capacity)*sizeof(float*));
    x->brightness=(int*) realloc(x->brightness,2*(x->capacity)*sizeof(int));
    x->capacity=2*(x->capacity);
    printf("problem not in increasing cap");
}
x->brightness[x->length]=bright;
x->pointer_to_array_of_faces[x->length]=(float**) malloc(3*sizeof(float*));
x->pointer_to_array_of_faces[x->length][0]=a;
x->pointer_to_array_of_faces[x->length][1]=b;
x->pointer_to_array_of_faces[x->length][2]=c;
x->length++;
}
void free_fb(fb *x){
for(int i=0;i<(x->length);i++){
    free(x->pointer_to_array_of_faces[i]);

}}
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

float update_vertices_multiplication(float matrix[4][4],vertices* x){
float temp[4];
for(int i=0;i<(x->length);i++){
matrix_vector_multi(matrix,x->pointer_to_array_of_vertices[i],temp);
for(int j=0;j<4;j++){
    x->pointer_to_array_of_vertices[i][j]=temp[j];
}
}
}



void draw_triangle(float** ver,char obj){
    //sort ver based on ver[i][1] and then draw lines
    for(int i=0;i<3;i++){
        if (isnan(ver[i][1])){
            return;
        }

    }
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




int main(){
int index_1;
int index_2;
int index_3;
vertices eeee;
vertices ffff;
fb framebuffer;
fb framebuffer_3d;
    const char* density = "^,\";:Ili!>~+_?-][]}[{1)(/tjrxnucvzXYUJCLQ0OZmwbqdkhdbMo*#MW&8B@M8$";

float camera_vec[3]={0,0,1};
float temp_vertex[4]={1.2,12.213,123.2,1};
float temp_vertex_2d[2];
float* array_for_brightness[3];
float focus=100;
init_fb(&framebuffer);
init_vertices(&eeee,4);
init_vertices(&ffff,2);
    FILE *file = fopen("teapot.obj", "r");
    if (file == NULL) {
        return 1;
    }

    char line[256];
    //first extract vertices to an arrays
    while (fgets(line, sizeof(line), file)) {
        if (line[0]=='v'){
        sscanf(line, "v %f %f %f",temp_vertex,temp_vertex+1,temp_vertex+2);
        temp_vertex[2]+=Z_correction;
        add_vertex(&eeee,temp_vertex);
        if (temp_vertex[2]!=0){
            temp_vertex_2d[0]=focus*temp_vertex[0]/temp_vertex[2];
            temp_vertex_2d[1]=focus*temp_vertex[1]/temp_vertex[2];
        }
        else{
            temp_vertex_2d[0]=NAN;
            temp_vertex_2d[1]=NAN;
        }
        add_vertex(&ffff,temp_vertex_2d);
        }
        else if (line[0]=='f'){
        sscanf(line, "f %d %d %d",&index_1,&index_2,&index_3);
        array_for_brightness[0]=eeee.pointer_to_array_of_vertices[index_1-1];
                array_for_brightness[1]=eeee.pointer_to_array_of_vertices[index_2-1];
        array_for_brightness[2]=eeee.pointer_to_array_of_vertices[index_3-1];
    
        add_face(&framebuffer,ffff.pointer_to_array_of_vertices[index_1-1],ffff.pointer_to_array_of_vertices[index_2-1],ffff.pointer_to_array_of_vertices[index_3-1],calculate_brightness(array_for_brightness,camera_vec));
        printf("added face \n");

        }
    }
    fclose(file);
    initscr();
	raw();
	noecho();
    cbreak();

for(int i=0;i<framebuffer.length;i++){
    draw_triangle(framebuffer.pointer_to_array_of_faces[i],density[framebuffer.brightness[i]]);
}


    getch();
clear();
endwin();
    print_vertices(&ffff);
    free_vertices(&eeee);
    free_vertices(&ffff);
    free_fb(&framebuffer);
    return 0;
}