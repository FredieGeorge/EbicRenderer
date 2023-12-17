#include <stdio.h>
#include <stdlib.h>
#include </home/chef/Documents/Project/EbicRenderer/myawesomelibrary.h>
int main(){
        float rotate[4][4];
        constructRotationMatrix(rotate,0.1,0,0);
        for(int i=0;i<4;i++){
            print_vec(rotate[i]);
        }

}