#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "definitions.h"
#include "stack.h"
#include "console.h"

extern camara * _kamera;

/* function declaration */
void camara_initialization();
void camara_alter_state();
char camara_get_state();
int camara_get_FOV();
char* camara_get_FOV_s();
float camara_get_zNear();
float camara_get_zFar();
int camara_is_orthogonal();
void camara_zoom_in();
void camara_zoom_out();
stack* camara_get_stack();
void camara_move(int key, char egoera, char aldaketa);

void camara_initialization(){
    _kamera = (struct camara*)malloc(sizeof(struct camara)); 

    _kamera->world_camara = stack_initialization();
    _kamera->objektu_kamara = 0;
    _kamera->FOV=KG_INITIAL_FOV;
    _kamera->zNear=KG_INITIAL_ZNEAR;
    _kamera->zFar=KG_INITIAL_ZFAR;
    _kamera->state='o';
}

void camara_alter_state(){
    if(camara_get_state()=='o'){
        console_add("Kamara perpesktiban");
        _kamera->state='p';
    }else{
        console_add("Kamara ortogonala");
        _kamera->state='o';
    }
}

char camara_get_state(){
    return _kamera->state;
}

int camara_get_FOV(){
    return _kamera->FOV;
}

char* camara_get_FOV_s(){
    char* fov=malloc(sizeof(char)*20);
    sprintf(fov,"Actual FOV: %d",camara_get_FOV());
    return fov;
}

void camara_set_FOV(int angle){
    _kamera->FOV = angle;
}

float camara_get_zNear(){
    return _kamera->zNear;
}

float camara_get_zFar(){
    return _kamera->zFar;
}

int camara_is_orthogonal(){
    return (_kamera->state=='o') ? 1 : 0;
}
void camara_zoom_in(){
    if(camara_get_FOV()>KG_MIN_FOV){
        camara_set_FOV(camara_get_FOV()-KG_STEP_FOV);
    }
    else{
        console_add("FOV minimoan");
        camara_set_FOV(KG_MIN_FOV);
    }
    console_add(camara_get_FOV_s());
}
void camara_zoom_out(){
    if(camara_get_FOV()<KG_MAX_FOV){
        camara_set_FOV(camara_get_FOV()+KG_STEP_FOV);
    }
    else{
        console_add("FOV maximoan");
        camara_set_FOV(KG_MAX_FOV);
    }
    console_add(camara_get_FOV_s());
}

stack* camara_get_stack(){
    return _kamera->world_camara;
}

void camara_move(int key, char egoera, char aldaketa){
    int up = 101;
    int down = 103;
    int left = 100;
    int right = 102;
    switch (key) {
    	case 101:   /*UP*/ 
            if (egoera == 'm'){
                console_add("Y+ mugitzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);   
            }
            else if (egoera == 'b'){
                console_add("X+ biratzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            else if (egoera == 't'){
                console_add("Y+ reeskalatzen");
                stack_add(_kamera->world_camara,down,egoera,aldaketa);  
            }
            else if(egoera == 'o'){
                console_add("Y islatzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            break;
        case 103:   /*DOWN*/
            if (egoera == 'm'){
                console_add("Y- mugitzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            else if (egoera == 'b'){
                console_add("X- biratzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            else if (egoera == 't'){
                console_add("Y- reeskalatzen");
                stack_add(_kamera->world_camara,up,egoera,aldaketa);  
            }
            else if(egoera == 'o'){
                console_add("Y islatzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            break;
        case 100:   /*LEFT*/
            if (egoera == 'm'){
                console_add("X- mugitzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            else if (egoera == 'b'){
                console_add("Y- biratzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            else if (egoera == 't'){
                console_add("X+ reeskalatzen");
                stack_add(_kamera->world_camara,right,egoera,aldaketa);  
            }
            else if(egoera == 'o'){
                console_add("X islatzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            break;
        case 102:   /*RIGHT*/
            if (egoera == 'm'){
                console_add("X+ mugitzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            else if (egoera == 'b'){
                console_add("Y+ biratzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            else if (egoera == 't'){
                console_add("X- reeskalatzen");
                stack_add(_kamera->world_camara,left,egoera,aldaketa);  
            }
            else if(egoera == 'o'){
                console_add("X islatzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            break;
        case 104:   /*REpag*/
            if (egoera == 'm'){
                console_add("Z- mugitzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            else if (egoera == 'b'){
                console_add("Z- biratzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            else if (egoera == 't'){
                console_add("Z+ reeskalatzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            else if(egoera == 'o'){
                console_add("Z islatzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            break;
        case 105:   /*AVpag*/
            if (egoera == 'm'){
                console_add("Z+ mugitzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            else if (egoera == 'b'){
                console_add("Z+ biratzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            else if (egoera == 't'){
                console_add("Z- reeskalatzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            else if(egoera == 'o'){
                console_add("Z islatzen");
                stack_add(_kamera->world_camara,key,egoera,aldaketa);  
            }
            break;
        case '+':
            //io.c-en
            break;
        case '-':
            //io.c-en
            break;
        case 114:
            console_add("Orain Z,Y,+,- Sakatu");
            break;
        default:
            console_add("Stack-era sartzeko komandoa ez da identifikatu");
            break;
    }
}  