#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <GL/glut.h>
#include "definitions.h"
#include "console.h"
#include "camara.h"

stack* stack_initialization(){
    stack *s =(stack*) malloc(sizeof(stack));
    s->selected = 0;
    s->matrizeak[KG_STACK_MAX_SIZE];
    return s;
};

GLdouble* matrix_multiplication(GLdouble* m1, GLdouble* m2){
    GLdouble *emaitza=0;
    emaitza =(GLdouble*)malloc(sizeof(GLdouble)*16);
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
                float bat = 0.0;
                for (int k = 0; k < 4; k++){
                    bat += m1[i * 4 + k] * m2[k * 4 +j];
                }
                emaitza[i * 4 +j] = bat;
        }
    }
    return emaitza;
}

void matrix_into_stack(GLdouble* m1,GLdouble* m2,stack* s,char aldaketa){
    if (s->selected  < KG_STACK_MAX_SIZE-1) {
        if (aldaketa=='g'){
            s->matrizeak[++s->selected] = matrix_multiplication(m1,m2);
        }
        else if (aldaketa=='l'){
            s->matrizeak[++s->selected] = matrix_multiplication(m2,m1);
        }
        ++s->upto;
    }
    else {
        printf("Stack-aren kapazitate maximora heldu zara\n");
    }
}

GLdouble* identity_matrix(){
        GLdouble* ident = malloc(sizeof(GLdouble)*16);
        ident[0] = ident[5] = ident[10] = ident[15] = 1.;
        ident[1] = ident[2] = ident[3] = ident[4] = ident[6] = ident[7] = ident[8] = ident[9] = ident[11] = ident[12] = ident[13] = ident[14] = 0.;
        return ident;  
}

GLdouble* peak(stack* s){
    if (s->selected == 0){  
        return identity_matrix();
    }
    return s->matrizeak[s->selected];
}

void pop(stack* s){
    if (s->selected > 0){
        s->matrizeak[--s->selected];
    }
}
void redo(stack* s){
    if(s->selected < s->upto){
        s->matrizeak[++s->selected];
    }
}
GLdouble* matrix_move(char axis, int direction){

    char* msg = malloc(sizeof(char)*20);
    sprintf(msg,direction>0?"%c+ mugitzen":"%c- mugitzen",axis);
    console_add(msg);

    GLdouble* m= malloc(sizeof(GLdouble)*16);
    m=identity_matrix();

    switch (axis){
        case 'x': case 'X':
            m[12] = direction*KG_STEP_MOVE;
            break;
        case 'y': case 'Y':
            m[13] = direction*KG_STEP_MOVE;
            break;
        case 'z': case 'Z':
            m[14] = direction*KG_STEP_MOVE;
            break;
        default:
            break;
    }
    return m;
}
GLdouble* matrix_rotate(char axis, int direction){

    char* msg = malloc(sizeof(char)*20);
    sprintf(msg,direction>0?"%c+ biratzen":"%c- biratzen",axis);
    console_add(msg);

    GLdouble* m= malloc(sizeof(GLdouble)*16);
    m=identity_matrix();

    switch (axis){
        case 'x': case 'X':
                m[5] = (direction == 1) ? (cos(2*KG_STEP_ROTATE)+1) / (2*cos(KG_STEP_ROTATE)) : cos(KG_STEP_ROTATE);
                m[6] = (-direction)*sin(KG_STEP_ROTATE );
                m[9] = (direction)*sin(KG_STEP_ROTATE );
                m[10] = cos(KG_STEP_ROTATE );
            break;
        case 'y': case 'Y':
                m[0] = (direction == -1) ? (cos(2*KG_STEP_ROTATE)+1) / (2*cos(KG_STEP_ROTATE)) : cos(KG_STEP_ROTATE);
                m[2] = (-direction)*sin(KG_STEP_ROTATE );
                m[8] = (direction)*sin(KG_STEP_ROTATE );
                m[10] = cos(KG_STEP_ROTATE );
            break;
        case 'z': case 'Z':
                m[0] = (direction == 1) ? (cos(2*KG_STEP_ROTATE)+1) / (2*cos(KG_STEP_ROTATE)) : cos(KG_STEP_ROTATE);
                m[1] = (-direction)*sin(KG_STEP_ROTATE );
                m[4] = (direction)*sin(KG_STEP_ROTATE );
                m[5] = cos(KG_STEP_ROTATE );
            break;
        default:
            break;
    }
    return m;
}
GLdouble* matrix_rescale(char axis, int direction){

    char* msg = malloc(sizeof(char)*20);
    sprintf(msg,direction>0?"%c+ berreskalatzen":"%c- berreskalatzen",axis);
    console_add(msg);

    GLdouble* m= malloc(sizeof(GLdouble)*16);
    m=identity_matrix();

    switch (axis){
        case 'x': case 'X':
                m[5] = (direction == 1) ? 1/KG_STEP_ZOOM : KG_STEP_ZOOM;
            break;
        case 'y': case 'Y':
                m[0] = (direction == 1) ? 1/KG_STEP_ZOOM : KG_STEP_ZOOM;
            break;
        case 'z': case 'Z':
                m[10] = (direction == 1) ? 1/KG_STEP_ZOOM : KG_STEP_ZOOM;
            break;
        default:
                m[5] = (direction == 1) ? 1/KG_STEP_ZOOM : KG_STEP_ZOOM;
                m[0] = (direction == 1) ? 1/KG_STEP_ZOOM : KG_STEP_ZOOM;
                m[10] = (direction == 1) ? 1/KG_STEP_ZOOM : KG_STEP_ZOOM;
            break;
    }
    return m;
}
GLdouble* matrix_mirror(char axis){

    char* msg = malloc(sizeof(char)*20);
    sprintf(msg,"%c islatzen",axis);
    console_add(msg);

    GLdouble* m= malloc(sizeof(GLdouble)*16);
    m=identity_matrix();

    switch (axis){
        case 'x': case 'X':
                m[0] = -1;
            break;
        case 'y': case 'Y':
                m[5] = -1;
            break;
        case 'z': case 'Z':
                m[10] = -1;
            break;
        default:
            break;
    }
    return m;
}
void stack_add(stack *s, int code, char egoera, char aldaketa){
    GLdouble* m= malloc(sizeof(GLdouble)*16);
    switch (code) {
    	case 101:   /*UP*/ 
            if (camara_is_ibiltaria()==1)
            {
                matrix_into_stack(peak(s),matrix_move('Z',-1.),s,aldaketa);
            }
            else if (egoera == 'm'){
                matrix_into_stack(peak(s),matrix_move('Y',1.),s,aldaketa);
            }
            else if (egoera == 'b'){
                matrix_into_stack(peak(s),matrix_rotate('X',1.),s,aldaketa);
            }
            else if (egoera == 't'){
                matrix_into_stack(peak(s),matrix_rescale('Y',-1.),s,aldaketa);
            }
            else if(egoera == 'o'){
                matrix_into_stack(peak(s),matrix_mirror('Y'),s,aldaketa);
            }
            break;
        case 103:   /*DOWN*/
            if (camara_is_ibiltaria()==1)
            {
                matrix_into_stack(peak(s),matrix_move('Z',1.),s,aldaketa);
            }
            else if (egoera == 'm'){
                matrix_into_stack(peak(s),matrix_move('Y',-1.),s,aldaketa);
            }
            else if (egoera == 'b'){
                matrix_into_stack(peak(s),matrix_rotate('X',-1.),s,aldaketa);
            }
            else if (egoera == 't'){
                matrix_into_stack(peak(s),matrix_rescale('Y',1.),s,aldaketa);
            }
            else if(egoera == 'o'){
                console_add("Y islatzen");
                matrix_into_stack(peak(s),matrix_mirror('Y'),s,aldaketa);
            }
            break;
        case 100:   /*LEFT*/
            if (camara_is_ibiltaria()==1)
            {
                matrix_into_stack(peak(s),matrix_move('X',-1.),s,aldaketa);
            }
            else if (egoera == 'm'){
                matrix_into_stack(peak(s),matrix_move('X',-1.),s,aldaketa);
            }
            else if (egoera == 'b'){
                matrix_into_stack(peak(s),matrix_rotate('Y',-1.),s,aldaketa);
            }
            else if (egoera == 't'){
                matrix_into_stack(peak(s),matrix_rescale('X',1.),s,aldaketa);
            }
            else if(egoera == 'o'){
                matrix_into_stack(peak(s),matrix_mirror('X'),s,aldaketa);
            }
            break;
        case 102:   /*RIGHT*/
            if (camara_is_ibiltaria()==1){
                matrix_into_stack(peak(s),matrix_move('X',1.),s,aldaketa);
            }
            else if (egoera == 'm'){}
                matrix_into_stack(peak(s),matrix_move('X',1.),s,aldaketa);
            }
            else if (egoera == 'b'){
                matrix_into_stack(peak(s),matrix_rotate('Y',1.),s,aldaketa);
            }
            else if (egoera == 't'){
                matrix_into_stack(peak(s),matrix_rescale('X',-1.),s,aldaketa);
            }
            else if(egoera == 'o'){
                matrix_into_stack(peak(s),matrix_mirror('X'),s,aldaketa);
            }
            break;
        case 104:   /*REpag*/
            if (camara_is_ibiltaria()==1){
                matrix_into_stack(peak(s),matrix_rotate('X',1.),s,aldaketa);
            }
            else if (egoera == 'm'){
                matrix_into_stack(peak(s),matrix_move('Z',1.),s,aldaketa);
            }
            else if (egoera == 'b'){
                matrix_into_stack(peak(s),matrix_rotate('Z',-1.),s,aldaketa);
            }
            else if (egoera == 't'){
                matrix_into_stack(peak(s),matrix_rescale('Z',1.),s,aldaketa);
            }
            else if(egoera == 'o'){
                matrix_into_stack(peak(s),matrix_mirror('Z'),s,aldaketa);
            }
            break;
        case 105:   /*AVpag*/
            if (camara_is_ibiltaria()==1){
                matrix_into_stack(peak(s),matrix_rotate('X',-1.),s,aldaketa);
            }
            else if (egoera == 'm'){
                matrix_into_stack(peak(s),matrix_move('Z',-1.),s,aldaketa);
            }
            else if (egoera == 'b'){
                matrix_into_stack(peak(s),matrix_rotate('Z',1.),s,aldaketa);
            }
            else if (egoera == 't'){
                matrix_into_stack(peak(s),matrix_rescale('Z',-1.),s,aldaketa);
            }
            else if(egoera == 'o'){
                matrix_into_stack(peak(s),matrix_mirror('Z'),s,aldaketa);
            }
            break;
        case '+':
            matrix_into_stack(peak(s),matrix_rescale('G',1.),s,aldaketa);
            break;
        case '-':
            matrix_into_stack(peak(s),matrix_rescale('G',-1.),s,aldaketa);
            break;
        case 114:
            console_add("Orain Z,Y,+,- Sakatu");
            break;
        default:
            console_add("Stack-era sartzeko komandoa ez da identifikatu");
            break;
    }
}

void inprimatu_matrizea(GLdouble *m){
    for(int i=0; i<4; i++){
        printf("%f %f %f %f \n",m[i],m[i+4],m[i+8],m[i+12]);
    }
    printf("\n");
}