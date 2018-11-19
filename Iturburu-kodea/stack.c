#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>
#include <GL/glut.h>
#include "definitions.h"

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
                    bat = bat + m1[i * 4 + k] * m2[k * 4 +j];
                }
                emaitza[i * 4 +j] = bat;
        }
    }
    return emaitza;
}

GLdouble* peak(stack* s){
    if (s->selected == 0){
        GLdouble* ident = malloc(sizeof(GLdouble)*16);
        ident[0] = ident[5] = ident[10] = ident[15] = 1.;
        ident[1] = ident[2] = ident[3] = ident[4] = ident[6] = ident[7] = ident[8] = ident[9] = ident[11] = ident[12] = ident[13] = ident[14] = 0.;
        return ident;    
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
void stack_add(stack *s, int code, char egoera, char aldaketa){
    GLdouble* m= malloc(sizeof(GLdouble)*16);
    switch (code) {
    	case 101:
            if (egoera == 'm'){
                /*UP*/ 
                console_add("Y+ mugitzen");
                m[0] = m[5] = m[10] = m[15] = 1.;
                m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
                m[12] = 0.;
                m[13] = KG_STEP_MOVE;
                m[14] = 0.;
                if (aldaketa=='g'){
                    s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
                }
                else if (aldaketa=='l'){
                    s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
                }
                ++s->upto;
            }
            else if (egoera == 'b'){
                /*UP*/
                console_add("Y+ biratzen");
                m[0] = m[5] = m[10] = m[15] = 1.;
                m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
                m[5] = (cos(2*KG_STEP_ROTATE )+1)/(2*cos(KG_STEP_ROTATE ));
                m[6] = -sin(KG_STEP_ROTATE );
                m[9] = sin(KG_STEP_ROTATE );
                m[10] = cos(KG_STEP_ROTATE );
                if (aldaketa=='g'){
                    s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
                }
                else if (aldaketa=='l'){
                    s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
                }
                ++s->upto;
            }
            else if (egoera == 't'){
                console_add("Y+ reeskalatzen");
                m[0] = m[5] = m[10] = m[15] = 1.;
                m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
                m[0] = KG_STEP_ZOOM;
                if (aldaketa=='g'){
                    s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
                }
                else if (aldaketa=='l'){
                    s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
                }
                ++s->upto;
            }
            break;
        case 103:
            if (egoera == 'm'){
                /*DOWN*/
                console_add("Y- mugitzen");
                m[0] = m[5] = m[10] = m[15] = 1.;
                m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
                m[12] = 0;
                m[13] = -KG_STEP_MOVE;
                m[14] = 0.;
                if (aldaketa=='g'){
                    s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
                }
                else if (aldaketa=='l'){
                    s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
                }
                ++s->upto;
            }
            else if (egoera == 'b'){
                /*DOWN*/
                console_add("Y- biratzen");
                m[0] = m[5] = m[10] = m[15] = 1.;
                m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
                m[5] = cos(KG_STEP_ROTATE );
                m[6] = sin(KG_STEP_ROTATE );
                m[9] = -sin(KG_STEP_ROTATE );
                m[10] = cos(KG_STEP_ROTATE );
                if (aldaketa=='g'){
                    s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
                }
                else if (aldaketa=='l'){
                    s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
                }
                ++s->upto;
            }
            else if (egoera == 't'){
                console_add("Y- reeskalatzen");
                m[0] = m[5] = m[10] = m[15] = 1.;
                m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
                m[0] = 1/KG_STEP_ZOOM;
                if (aldaketa=='g'){
                    s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
                }
                else if (aldaketa=='l'){
                    s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
                }
                ++s->upto;
            }
            break;
        case 100:
            if (egoera == 'm'){
                /*LEFT*/
                console_add("X- mugitzen");
                m[0] = m[5] = m[10] = m[15] = 1.;
                m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
                m[12] = -KG_STEP_MOVE;
                m[13] = 0.;
                m[14] = 0.;
                if (aldaketa=='g'){
                    s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
                }
                else if (aldaketa=='l'){
                    s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
                }
                ++s->upto;
            }
            else if (egoera == 'b'){
                /*LEFT*/
                console_add("X- biratzen");
                m[0] = m[5] = m[10] = m[15] = 1.;
                m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
                m[0] = (cos(2*KG_STEP_ROTATE )+1)/(2*cos(KG_STEP_ROTATE ));
                m[2] = sin(KG_STEP_ROTATE );
                m[8] = -sin(KG_STEP_ROTATE );
                m[10] = cos(KG_STEP_ROTATE );
                if (aldaketa=='g'){
                    s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
                }
                else if (aldaketa=='l'){
                    s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
                }
                ++s->upto;
            }
            else if (egoera == 't'){
                console_add("X- reeskalatzen");
                m[0] = m[5] = m[10] = m[15] = 1.;
                m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
                m[5] = KG_STEP_ZOOM;
                if (aldaketa=='g'){
                    s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
                }
                else if (aldaketa=='l'){
                    s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
                }
                ++s->upto;
            }
            break;
        case 102:
            if (egoera == 'm'){
                /*RIGHT*/
                console_add("X+ mugitzen");
                m[0] = m[5] = m[10] = m[15] = 1.;
                m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
                m[12] = KG_STEP_MOVE;
                m[13] = 0.;
                m[14] = 0.;
                if (aldaketa=='g'){
                    s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
                }
                else if (aldaketa=='l'){
                    s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
                }
                ++s->upto;
            }
            else if (egoera == 'b'){
                /*RIGHT*/
                console_add("X+ biratzen");
                m[0] = m[5] = m[10] = m[15] = 1.;
                m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
                m[0] = cos(KG_STEP_ROTATE );
                m[2] = -sin(KG_STEP_ROTATE );
                m[8] = sin(KG_STEP_ROTATE );
                m[10] = cos(KG_STEP_ROTATE );
                if (aldaketa=='g'){
                    s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
                }
                else if (aldaketa=='l'){
                    s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
                }
                ++s->upto;
            }
            else if (egoera == 't'){
                console_add("X+ reeskalatzen");
                m[0] = m[5] = m[10] = m[15] = 1.;
                m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
                m[5] = 1/KG_STEP_ZOOM;
                if (aldaketa=='g'){
                    s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
                }
                else if (aldaketa=='l'){
                    s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
                }
                ++s->upto;
            }
            break;
        case 104:
            if (egoera == 'm'){
                /*REpag*/
                console_add("Z+ mugitzen");
                m[0] = m[5] = m[10] = m[15] = 1.;
                m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
                m[12] = 0;
                m[13] = 0;
                m[14] = +KG_STEP_MOVE;
                if (aldaketa=='g'){
                    s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
                }
                else if (aldaketa=='l'){
                    s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
                }
                ++s->upto;
            }
            else if (egoera == 'b'){
                /*REpag*/
                console_add("Z+ biratzen");
                m[0] = m[5] = m[10] = m[15] = 1.;
                m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
                m[0] = cos(KG_STEP_ROTATE );
                m[1] = sin(KG_STEP_ROTATE );
                m[4] = -sin(KG_STEP_ROTATE );
                m[5] = cos(KG_STEP_ROTATE );
                if (aldaketa=='g'){
                    s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
                }
                else if (aldaketa=='l'){
                    s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
                }
                ++s->upto;
            }
            else if (egoera == 't'){
                console_add("Z+ reeskalatzen");
                m[0] = m[5] = m[10] = m[15] = 1.;
                m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
                m[10] = KG_STEP_ZOOM;
                if (aldaketa=='g'){
                    s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
                }
                else if (aldaketa=='l'){
                    s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
                }
                ++s->upto;
            }
            break;
        case 105:
            if (egoera == 'm'){
                /*AVpag*/
                console_add("Z- mugitzen");
                m[0] = m[5] = m[10] = m[15] = 1.;
                m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
                m[12] = 0.;
                m[13] = 0.;
                m[14] = -KG_STEP_MOVE;
                if (aldaketa=='g'){
                    s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
                }
                else if (aldaketa=='l'){
                    s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
                }
                ++s->upto;
            }
            else if (egoera == 'b'){
                /*AVpag*/
                console_add("Z- biratzen");
                m[0] = m[5] = m[10] = m[15] = 1.;
                m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
                m[0] = (cos(2*KG_STEP_ROTATE )+1)/(2*cos(KG_STEP_ROTATE ));
                m[1] = -sin(KG_STEP_ROTATE );
                m[4] = sin(KG_STEP_ROTATE );
                m[5] = cos(KG_STEP_ROTATE );
                if (aldaketa=='g'){
                    s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
                }
                else if (aldaketa=='l'){
                    s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
                }
                ++s->upto;
            }
            else if (egoera == 't'){
                console_add("Z- reeskalatzen");
                m[0] = m[5] = m[10] = m[15] = 1.;
                m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
                m[10] = 1/KG_STEP_ZOOM;
                if (aldaketa=='g'){
                    s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
                }
                else if (aldaketa=='l'){
                    s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
                }
                ++s->upto;
            }
            break;
        case '+':
            console_add("Reeskalaketa+ orokorra");
            m[0] = m[5] = m[10] = m[15] = 1.;
            m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
            m[0] = 1/KG_STEP_ZOOM;
            m[5] = 1/KG_STEP_ZOOM;
            m[10] = 1/KG_STEP_ZOOM;
            if (aldaketa=='g'){
                s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
            }
            else if (aldaketa=='l'){
                s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
            }
            ++s->upto;
            break;
        case '-':
            console_add("Reeskalaketa- orokorra");
            m[0] = m[5] = m[10] = m[15] = 1.;
            m[1] = m[2] = m[3] = m[4] = m[6] = m[7] = m[8] = m[9] = m[11] = m[12] = m[13] = m[14] = 0.;
            m[0] = KG_STEP_ZOOM;
            m[5] = KG_STEP_ZOOM;
            m[10] = KG_STEP_ZOOM;
            if (aldaketa=='g'){
                s->matrizeak[++s->selected] = matrix_multiplication(peak(s),m);
            }
            else if (aldaketa=='l'){
                s->matrizeak[++s->selected] = matrix_multiplication(m,peak(s));
            }
            ++s->upto;
            break;
        case 114:
            printf("Orain Z,Y,+,- Sakatu\n");
            break;
        default:
            printf("Stack-era sartzeko komandoa ez da identifikatu");
            break;
    }
}

void inprimatu_matrizea(GLdouble *m){
    for(int i=0; i<4; i++){
        printf("%f %f %f %f \n",m[i],m[i+4],m[i+8],m[i+12]);
    }
    printf("\n");
}
