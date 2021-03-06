#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "display.h"
#include "io.h"
#include "definitions.h"
#include "console.h"
#include "camara.h"

//gcc -o KbGprograma *.c -lGL -lGLU -lm -lglut
//./KbGprograma

/** GLOBAL VARIABLES **/

GLdouble _window_ratio;                     /*Control of window's proportions */
GLdouble _ortho_x_min,_ortho_x_max;         /*Variables for the control of the orthographic projection*/
GLdouble _ortho_y_min ,_ortho_y_max;        /*Variables for the control of the orthographic projection*/
GLdouble _ortho_z_min,_ortho_z_max;         /*Variables for the control of the orthographic projection*/

object3d * _first_object= 0;                /*List of objects*/
object3d * _selected_object = 0;            /*Object currently selected*/

console *_kontsola=0;
camara * _kamera=0;

GLdouble * _m = 0;

GLdouble* hasierako_puntua;

/** GENERAL INITIALIZATION **/
void initialization (){
    hasierako_puntua = malloc(sizeof(GLdouble)*16);
    hasierako_puntua[0] = hasierako_puntua[1] = hasierako_puntua[4] = hasierako_puntua[3] = hasierako_puntua[7] = hasierako_puntua[9] = hasierako_puntua[15] = 0.;
    hasierako_puntua[3] = hasierako_puntua[7] = hasierako_puntua[9] = hasierako_puntua[10] = hasierako_puntua[11] = hasierako_puntua[13] = hasierako_puntua[14] = hasierako_puntua[15] = 1.;
    hasierako_puntua[6] = -5.;
    /*Initialization of all the variables with the default values*/
    _ortho_x_min = KG_ORTHO_X_MIN_INIT;
    _ortho_x_max = KG_ORTHO_X_MAX_INIT;
    _ortho_y_min = KG_ORTHO_Y_MIN_INIT;
    _ortho_y_max = KG_ORTHO_Y_MAX_INIT;
    _ortho_z_min = KG_ORTHO_Z_MIN_INIT;
    _ortho_z_max = KG_ORTHO_Z_MAX_INIT;

    _window_ratio = (GLdouble) KG_WINDOW_WIDTH / (GLdouble) KG_WINDOW_HEIGHT;
	
    /*Definition of the background color*/
    glClearColor(KG_COL_BACK_R, KG_COL_BACK_G, KG_COL_BACK_B, KG_COL_BACK_A);

    /*Argiak sartzeko*/
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    /*Definition of the method to draw the objects*/
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    //Kamara
    camara_initialization();

    //Matrizeen 
    _m =malloc(sizeof(GLdouble)*16);
    _m[0] =_m[5] =_m[10] =_m[15] = 1.;
    _m[1] =_m[2] =_m[3] =_m[4] =_m[6] =_m[7] =_m[8] =_m[9] =_m[11] =_m[12] =_m[13] =_m[14] = 0.;
    
    console_initialization();
}


/** MAIN FUNCTION **/
int main(int argc, char** argv) {

    /* glut initializations */
    glutInit(&argc, argv);
    glutInitWindowSize(KG_WINDOW_WIDTH, KG_WINDOW_HEIGHT);
    glutInitWindowPosition(KG_WINDOW_X, KG_WINDOW_Y);
    glutCreateWindow(KG_WINDOW_TITLE);

    /* set the callback functions */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);

    /* this initialization has to be AFTER the creation of the window */
    initialization();

    /*Print the help information*/
    print_help();

    /* start the main loop */
    glutMainLoop();
    return 0;
}
