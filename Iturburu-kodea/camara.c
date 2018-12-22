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
void camara_move(char key, char egoera, char aldaketa);

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
