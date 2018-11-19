#include "definitions.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "console.h"
#include "stack.h"

/** EXTERNAL VARIABLES **/

extern GLdouble _window_ratio;
extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern object3d *_first_object;
extern object3d *_selected_object;

extern GLdouble * _m;

void printTestua(float x, float y,float z, char *string);

/**
 * @brief Function to draw the axes
 */
void draw_axes()
{
    char *c=0;
    int min = 1;
    int max = 9;
    /*Draw X axis*/
    glBegin(GL_LINES);
    glColor3f(KG_COL_X_AXIS_R,KG_COL_X_AXIS_G,KG_COL_X_AXIS_B);
    glVertex3d(0,0,0);
    glVertex3d(_ortho_x_max/2,0,0);
    glEnd();
	printTestua(_ortho_x_max/2,0,0,"X");
    for(int i=min;i<=max;i++){
        c=(i + '0');
	    printTestua(i,0,0,&(c));
    }
    /*Draw Y axis*/
    glBegin(GL_LINES);
    glColor3f(KG_COL_Y_AXIS_R,KG_COL_Y_AXIS_G,KG_COL_Y_AXIS_B);
    glVertex3d(0,0,0);
    glVertex3d(0,_ortho_y_max/2,0);
    glEnd();
	printTestua(0,_ortho_y_max/2,0,"Y");
    for(int i=min;i<=max;i++){
        c=(i + '0');
	    printTestua(0,i,0,&(c));
    }
    /*Draw Z axis*/
    glBegin(GL_LINES);
    glColor3f(KG_COL_Z_AXIS_R,KG_COL_Z_AXIS_G,KG_COL_Z_AXIS_B);
    glVertex3d(0,0,0);
    glVertex3d(0,0,_ortho_z_max/2);
    glEnd();
	printTestua(0,0,_ortho_z_max/2,"Z");
    for(int i=min;i<=max;i++){
        c=(i + '0');
	    printTestua(0,0,i,&(c));
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
			glVertex3f(x,floor,z);
			glVertex3f(x,floor,-z);
			
			if(z<KG_FLOOR_SIZE-KG_FLOOR_STEPS){

				glColor3f(1.,1.,1.);
				glVertex3f(x,floor,z+KG_FLOOR_STEPS);
				glVertex3f(x,floor,-z);
			}
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
    printTestua(_ortho_x_max*0.60,-_ortho_y_max*0.50,0,"Console______________");
    int i =1;
    console_backupSet();
    printTestua(_ortho_x_max*0.60,-_ortho_y_max+_ortho_y_max*0.05*i,0,console_thisMezua());
    while(console_hasPrevious()==1 && i<8){
        i++;
        console_previousMezua();
        printTestua(_ortho_x_max*0.60,-_ortho_y_max+_ortho_y_max*0.05*i,0,console_thisMezua());
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


/**
 * @brief Callback display function
 */
void display(void) {
    GLint v_index, v, f;
    object3d *aux_obj = _first_object;

    /* Clear the screen */
    glClear(GL_COLOR_BUFFER_BIT);

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
        glOrtho(midpt - (wd / 2), midpt + (wd / 2), _ortho_y_min, _ortho_y_max, _ortho_z_min, _ortho_z_max);
    } else {/* In the opposite situation we extend the Y axis */
        /* New height */
        GLdouble he = (_ortho_x_max - _ortho_x_min) / _window_ratio;
        /* Midpoint in the Y axis */
        GLdouble midpt = (_ortho_y_min + _ortho_y_max) / 2;
        /*Definition of the projection*/
        glOrtho(_ortho_x_min, _ortho_x_max, midpt - (he / 2), midpt + (he / 2), _ortho_z_min, _ortho_z_max);
    }

    /* Now we start drawing the object */
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /*First, we draw the axes*/
    draw_axes();

	/*Sorua marrazteko*/
	draw_floor();

	/*Konsola bat*/
	konsolaBistaratu();

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
        glMultMatrixd(peak(aux_obj->s));
        for (f = 0; f < aux_obj->num_faces; f++) {
            glBegin(GL_POLYGON);
            for (v = 0; v < aux_obj->face_table[f].num_vertices; v++) {
                v_index = aux_obj->face_table[f].vertex_table[v];
                glVertex3d(aux_obj->vertex_table[v_index].coord.x,
                        aux_obj->vertex_table[v_index].coord.y,
                        aux_obj->vertex_table[v_index].coord.z);

            }
            glEnd();
        }
        aux_obj = aux_obj->next;
    }
    /*Do the actual drawing*/
    glFlush();
}
