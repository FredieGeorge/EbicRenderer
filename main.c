#include </home/chef/Documents/Project/graphics/myawesomelibrary.h>


// }
int main()
{	const float camera_vector[4]={1,2,3};//has to be a unit vectir
    const char* density = "^,\";:Ili!>~+_?-][]}[{1)(/tjrxnucvzXYUJCLQ0OZmwbqdkhdbMo*#MW&8B@M8$";
    float focus=6;
float position[4]={4,3,2,1};
float persp_transform_matrix[4][4]={{focus,0,0,0},{0,focus,0,0},{0,0,0,0},{0,0,1,0}};
float rotation[4][4]={{1,0,0,0},{0,cos(THETA),-1*sin(THETA),0},{0,sin(THETA),cos(THETA),0},{0,0,0,1}};
float translate[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
char star='*';
//printf("didnt dump yet line 154");

array_faces framebuffer;
framebuffer.length=0;
framebuffer.capacity=0;
array_faces triangles;
triangles.length=0;
triangles.capacity=0;

int brightn;
float temp_frame_buffer[][2]={{1,10},{10,10},{4,15}};
float temp_triangles[][4]={{51,10,10,1},{60,10,10,1},{54,15,10,1}};
//printf("didnt dump yet line 158");
// add_face(3,temp_triangles,&triangles);


    FILE *file = fopen("proj.obj", "r");
    if (file == NULL) {
        //printf("Could not open filrefre\n");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        if (line[0]=='f'){
        sscanf(line, "f %f/%f/%f %f/%f/%f %f/%f/%f",&temp_triangles[0][0],&temp_triangles[0][1],&temp_triangles[0][2],&temp_triangles[1][0],&temp_triangles[1][1],&temp_triangles[1][2],&temp_triangles[2][0],&temp_triangles[2][1],&temp_triangles[2][2]);
        add_face(4,temp_triangles,0,&triangles);}
    }
    fclose(file);




	initscr();
	raw();
	noecho();
    cbreak();
for (int j=0;j<triangles.length;j++){
        brightn=calculate_brightness(triangles.pointer_to_array_of_faces[j],camera_vector);

    for (int i=0;i<3;i++){
        // temp_frame_buffer[i][0] = ceil(((triangles.pointer_to_array_of_faces)[j][i][0] ));
        // temp_frame_buffer[i][1] =  ceil(((triangles.pointer_to_array_of_faces)[j][i][1] ));
        temp_frame_buffer[i][0] = (((float)triangles.pointer_to_array_of_faces[j][i][0] * focus) / (float)triangles.pointer_to_array_of_faces[j][i][2]);
        temp_frame_buffer[i][1] = (((float)triangles.pointer_to_array_of_faces[j][i][1] * focus) / (float)triangles.pointer_to_array_of_faces[j][i][2]);
        

    } add_face(2,temp_frame_buffer,brightn,&framebuffer);}
char o[]={'e','o'};
int counter=0;
while (1){

// update_triangles_matrix(translate,&triangles);
free_array_faces(&framebuffer);
for (int j=0;j<triangles.length;j++){
        brightn=calculate_brightness(triangles.pointer_to_array_of_faces[j],camera_vector);

    for (int i=0;i<3;i++){
        temp_frame_buffer[i][0] = ((triangles.pointer_to_array_of_faces[j][i][0] * focus) / triangles.pointer_to_array_of_faces[j][i][2]);
        temp_frame_buffer[i][1] = ((triangles.pointer_to_array_of_faces[j][i][1] * focus) / triangles.pointer_to_array_of_faces[j][i][2]);
        

    } add_face(2,temp_frame_buffer,brightn,&framebuffer);
  
}
for(int i=0 ; i<framebuffer.length;i++){
    if (framebuffer.brightness[i]>0){
    draw_triangle(framebuffer.pointer_to_array_of_faces[i],density[framebuffer.brightness[i]]);   
    }}
    
    
refresh();
erase();
output_array_faces(&framebuffer);
// mvprintw(0,0,'%d',counter);
napms(100);
counter++;
}
getch();
clear();
endwin();
//printf("didnt dump yet line 154");
//


  
  free_array_faces(&framebuffer);
  free_array_faces(&triangles);


// for(int i ;i<4;i++){
// print_vec(rotation[i]);


// }
return 0;

}