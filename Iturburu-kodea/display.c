#include "definitions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "console.h"
#include "camara.h"
#include "stack.h"

/** EXTERNAL VARIABLES **/

extern GLdouble _window_ratio;
extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern object3d *_first_object;
extern object3d *_selected_object;

extern GLdouble * _m;
extern GLdouble * hasierako_puntua;
void printTestua(float x, float y,float z, char *string);

/**
 * @brief Function to draw the axes
 */
void draw_axes()
{
    char buffer [100];
    float steps = 0.25;
    float min = 0;
    float max = 9;
    /*Draw X axis*/
    glBegin(GL_LINES);
    glColor3f(KG_COL_X_AXIS_R,KG_COL_X_AXIS_G,KG_COL_X_AXIS_B);
    glVertex3d(0,0,0);
    max=_ortho_x_max*0.75;
    glVertex3d(max,0,0);
    glEnd();
	printTestua(max,0,0,"X");
    for(float i=min;i<=max*0.9;i+=(max-min)*steps){
        snprintf ( buffer, 100, "%.0e",i);
	    printTestua(i,0,0,buffer);
    }
    /*Draw Y axis*/
    glBegin(GL_LINES);
    glColor3f(KG_COL_Y_AXIS_R,KG_COL_Y_AXIS_G,KG_COL_Y_AXIS_B);
    glVertex3d(0,0,0);
    glVertex3d(0,max,0);
    glEnd();
	printTestua(0,max,0,"Y");
    for(float i=min;i<=max*0.9;i+=(max-min)*steps){
        snprintf ( buffer, 100, "%.0e",i);
	    printTestua(0,i,0,buffer);
    }
    /*Draw Z axis*/
    glBegin(GL_LINES);
    glColor3f(KG_COL_Z_AXIS_R,KG_COL_Z_AXIS_G,KG_COL_Z_AXIS_B);
    glVertex3d(0,0,0);
    glVertex3d(0,0,max);
    glEnd();
	printTestua(0,0,max,"Z");
    for(float i=min;i<=max*0.9;i+=(max-min)*steps){
        snprintf ( buffer, 100, "%.0e",i);
	    printTestua(0,0,i,buffer);
    }
    
}

void draw_floor(){
	glBegin(GL_LINES);
	int floor= -10;

	for(int x=0;x<=KG_FLOOR_SIZE;x+=KG_FLOOR_STEPS) {
		for(int z=0;z<=KG_FLOOR_SIZE;z+=KG_FLOOR_STEPS){
			glColor3f(1.,1.,1.);
			glVertex3f(x,floor,z);
			glVertex3f(-x,floor,z);

			glColor3f(1.,1.,1.);
			glVertex3f(x,floor,-z);
			glVertex3f(-x,floor,-z);

			glColor3f(1.,1.,1.);
			glVertex3f(x,floor,-z);
			glVertex3f(x,floor,z);

            glColor3f(1.,1.,1.);
			glVertex3f(-x,floor,-z);
			glVertex3f(-x,floor,z);
			
			
		}
	}
	glEnd();
}

void printTestua(float x, float y,float z, char *string)
{
	//set the position of the text in the window using the x and y coordinates
	glRasterPos3f(x,y,z);
	//get the length of the string to display
	int len = (int) strlen(string);

	//loop to display character by character
	for (int i = 0; i < len; i++) 
	{
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13,string[i]);
	}
};
void konsolaBistaratu(){
    console_backupSet();

    if(camara_is_orthogonal()==1){
        printTestua(-_ortho_x_max*1.5,-_ortho_y_max+_ortho_y_max*0.5,0,"Console______________");
        int i =1;
        printTestua(-_ortho_x_max*1.5,-_ortho_y_max+_ortho_y_max*0.05*i,0,console_thisMezua());
        while(console_hasPrevious()==1 && i<8){
            i++;
            console_previousMezua();
            printTestua(-_ortho_x_max*1.5,-_ortho_y_max+_ortho_y_max*0.05*i,0,console_thisMezua());
        }
    }
    else{
        printTestua(-_ortho_x_max*1.5,-_ortho_y_max+_ortho_y_max*0.5,-KG_INITIAL_ZNEAR*10,"Console______________");
        int i =1;
        printTestua(-_ortho_x_max*1.5,-_ortho_y_max+_ortho_y_max*0.05*i,-KG_INITIAL_ZNEAR*10,console_thisMezua());
        while(console_hasPrevious()==1 && i<8){
            i++;
            console_previousMezua();
            printTestua(-_ortho_x_max*1.5,-_ortho_y_max+_ortho_y_max*0.05*i,-KG_INITIAL_ZNEAR*10,console_thisMezua());
        }
    }

    console_backupRestore();
    
}

/**
 * @brief Callback reshape function. We just store the new proportions of the window
 * @param width New width of the window
 * @param height New height of the window
 */
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    /*  Take care, the width and height are integer numbers, but the ratio is a GLdouble so, in order to avoid
     *  rounding the ratio to integer values we need to cast width and height before computing the ratio */
    _window_ratio = (GLdouble) width / (GLdouble) height;
}

void lights(){
    GLfloat horia[4] = {0.0, 1.0, 1.0, 1.0};
    GLfloat grisa[4] = {0.2, 0.2, 0.2, 1.0};
    GLfloat txuria[4] = {0.0, 0.0, 0.0, 1.0};

    char mota='e';
    if(mota=='b'){
        GLfloat kokapena[4]= {0.0, 10.0, 0.0, 1.0};
        glLightfv(GL_LIGHT0, GL_POSITION, kokapena);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 180.0);
    }
    else if(mota=='e'){
        GLfloat norabidea[4]= {1.0, 0.0, 0.0, 0.0};
        glLightfv(GL_LIGHT0, GL_POSITION, norabidea);
    }
    else if(mota=='f'){
        GLfloat kokapena[4]= {0.0, 10.0, 0.0, 1.0};
        GLfloat norabidea[4]= {1.0, 0.0, 0.0, 0.0};
        glLightfv(GL_LIGHT0, GL_POSITION, kokapena);
        glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, norabidea);
        glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 20.0);
        glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 1.0);
        
    }
    /* glLightfv(GL_LIGHT0, GL_AMBIENT, grisa);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, horia);
    glLightfv(GL_LIGHT0, GL_SPECULAR, txuria);

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 1.0); */

}

/**
 * @brief Callback display function
 */
void display(void) {
    GLint v_index, v, f;
    object3d *aux_obj = _first_object;
    GLdouble* egungo_bista = malloc(sizeof (GLdouble)*16);
    /* Clear the screen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Define the projection */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /*When the window is wider than our original projection plane we extend the plane in the X axis*/
    if ((_ortho_x_max - _ortho_x_min) / (_ortho_y_max - _ortho_y_min) < _window_ratio) {
        /* New width */
        GLdouble wd = (_ortho_y_max - _ortho_y_min) * _window_ratio;
        /* Midpoint in the X axis */
        GLdouble midpt = (_ortho_x_min + _ortho_x_max) / 2;
        /*Definition of the projection*/
        if(camara_is_orthogonal()==1){
            //Ortogonala
            glOrtho(midpt - (wd / 2), midpt + (wd / 2), _ortho_y_min, _ortho_y_max, _ortho_z_min, _ortho_z_max);
        }else{
            //Perspektiba
            gluPerspective(camara_get_FOV(),_window_ratio,camara_get_zNear(),camara_get_zFar());
        }
        
    } else {/* In the opposite situation we extend the Y axis */
        /* New height */
        GLdouble he = (_ortho_x_max - _ortho_x_min) / _window_ratio;
        /* Midpoint in the Y axis */
        GLdouble midpt = (_ortho_y_min + _ortho_y_max) / 2;
        /*Definition of the projection*/
        if(camara_is_orthogonal()==1){
            //Ortogonala
            glOrtho(_ortho_x_min, _ortho_x_max, midpt - (he / 2), midpt + (he / 2), _ortho_z_min, _ortho_z_max);
        }else{
            //Perspektiba
            gluPerspective(camara_get_FOV(),_window_ratio,camara_get_zNear(),camara_get_zFar());
        }        
    }

    /* Now we start drawing the object */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(camara_is_orthogonal()!=1){
        egungo_bista = matrix_multiplication(hasierako_puntua,peak(camara_get_stack()));
        //glMultMatrixd(peak(camara_get_stack()));
        gluLookAt(egungo_bista[0],egungo_bista[1],egungo_bista[2],egungo_bista[4],egungo_bista[5],egungo_bista[6],egungo_bista[8],egungo_bista[9],egungo_bista[10]);
    }

    //lights();
    /*First, we draw the axes*/
    glLoadIdentity();
    draw_axes();

	/*Sorua marrazteko*/
	draw_floor();

    /*Now each of the objects in the list*/
    while (aux_obj != 0) {
        /* Select the color, depending on whether the current object is the selected one or not */
        if (aux_obj == _selected_object){
            glColor3f(KG_COL_SELECTED_R,KG_COL_SELECTED_G,KG_COL_SELECTED_B);
        }else{
            glColor3f(KG_COL_NONSELECTED_R,KG_COL_NONSELECTED_G,KG_COL_NONSELECTED_B);
        }

        /* Draw the object; for each face create a new polygon with the corresponding vertices */
        glLoadIdentity();
        if(camara_is_orthogonal()!=1){
            gluLookAt(egungo_bista[0],egungo_bista[1],egungo_bista[2],egungo_bista[4],egungo_bista[5],egungo_bista[6],egungo_bista[8],egungo_bista[9],egungo_bista[10]);
        }
        glMultMatrixd(peak(aux_obj->s));
        for (f = 0; f < aux_obj->num_faces; f++) {
            glBegin(GL_POLYGON);  
            for (v = 0; v < aux_obj->face_table[f].num_vertices; v++) {
                v_index = aux_obj->face_table[f].vertex_table[v];
                glNormal3d(aux_obj->normal_table[f].x,
                                aux_obj->normal_table[f].y,
                                aux_obj->normal_table[f].z);
                glVertex3d(aux_obj->vertex_table[v_index].coord.x,
                        aux_obj->vertex_table[v_index].coord.y,
                        aux_obj->vertex_table[v_index].coord.z);
                
            }
            glEnd();
        }
        char* msg = malloc(sizeof(char)*30);
        sprintf(msg,"%s, %d polygons",aux_obj->fitx_izena,aux_obj->num_faces);
        printTestua(0,aux_obj->max.y+1,0,msg);

        aux_obj = aux_obj->next;
    }

    /*Konsola bat*/
    glLoadIdentity();
    konsolaBistaratu();

    /*Do the actual drawing*/
    glFlush();


}
