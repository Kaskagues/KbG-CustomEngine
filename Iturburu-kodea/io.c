#include "definitions.h"
#include "load_obj.h"
#include <GL/glut.h>
#include <stdio.h>
#include "console.h"
#include "stack.h"

extern object3d * _first_object;
extern object3d * _selected_object;

extern GLdouble _ortho_x_min,_ortho_x_max;
extern GLdouble _ortho_y_min,_ortho_y_max;
extern GLdouble _ortho_z_min,_ortho_z_max;

extern GLdouble *_m;

char egoera = '*';
char aldaketa = 'l';

/**
 * @brief This function just prints information about the use
 * of the keys
 */
void print_help(){
    console_add("KbG Irakasgaiaren Praktika. Programa honek 3D objektuak");
    console_add("aldatzen eta bistaratzen ditu.");

    console_add("Egilea: Andoni Aranguren eta Aritz Ibarra (aibarra022@ehu.es)");
    console_add("Data: Irailak, 2014");
    console_add("FUNTZIO NAGUSIAK");
    console_add("<?> Laguntza hau bistaratu");
    console_add("<ESC> Programatik irten ");
    console_add("<F> Objektua bat kargatu");
    console_add("<I> Hautatutako objektuaren informazioa");
    console_add("<TAB> Kargaturiko objektuen artean bat hautatu");
    console_add("<DEL> Hautatutako objektua ezabatu");
    console_add("<CTRL + -> Bistaratze-eremua handitu");
    console_add("<CTRL + +> Bistaratze-eremua txikitu");
}

/**
 * @brief Callback function to control the basic keys
 * @param key Key that has been pressed
 * @param x X coordinate of the mouse pointer when the key was pressed
 * @param y Y coordinate of the mouse pointer when the key was pressed
 */

void keyboard(unsigned char key, int x, int y) {
    char* fname = malloc(sizeof (char)*128); /* Note that scanf adds a null character at the end of the vector*/
    int read = 0;
    object3d *auxiliar_object = 0;
    GLdouble wd,he,midx,midy;

	switch (key) {
	case 'f':
	case 'F':
		/*Ask for file*/
		console_add(KG_MSSG_SELECT_FILE);
		scanf("%s", fname);
		/*Allocate memory for the structure and read the file*/
		auxiliar_object = (object3d *) malloc(sizeof (object3d));
		read = read_wavefront(fname, auxiliar_object);
		switch (read) {
		/*Errors in the reading*/
		case 1:
		    console_add(KG_MSSG_FILENOTFOUND);
		    break;
		case 2:
		    console_add(KG_MSSG_INVALIDFILE);
		    break;
		case 3:
		    console_add(KG_MSSG_EMPTYFILE);
		    break;
		/*Read OK*/
		case 0:
		    /*Insert the new object in the list*/
		    auxiliar_object->next = _first_object;
		    _first_object = auxiliar_object;
		    _selected_object = _first_object;
            _selected_object->s = stack_initialization();
		    console_add(KG_MSSG_FILEREAD);
		    break;
        }
        break;

	case 'i':
	case 'I':
		/*Objektuaren informazioa lortzeko*/
		if(_selected_object == NULL){
			console_add("Ez dago objekturik hautaturik\n");	
		}
        else{
            console_add(_selected_object->fitx_izena);
            printf("\nHautatutako objektuaren info\nErpin kop: %d \nFitxategiaren izena: %s\n",_selected_object->num_vertices,_selected_object->fitx_izena);
        }
        break;

	case 9: /* <TAB> */
		if(_selected_object == NULL){ }
		else 
		{
			_selected_object = _selected_object->next;
			/*The selection is circular, thus if we move out of the list we go back to the first element*/
			if (_selected_object == 0) _selected_object = _first_object;
		}
        break;

    case 127: /* <SUPR> */
        /*Erasing an object depends on whether it is the first one or not*/
		if(_selected_object == NULL){ 
            console_add("Ez dago irudirik\n");
        }
        else if (_selected_object == _first_object)
        {
            console_add(strcpy(_selected_object->fitx_izena," irudia ezabatzen\n"));
            /*To remove the first object we just set the first as the current's next*/
            _first_object = _first_object->next;
            /*Once updated the pointer to the first object it is save to free the memory*/
            free(_selected_object);
            /*Finally, set the selected to the new first one*/
            _selected_object = _first_object;
        } else {
            console_add(strcpy(_selected_object->fitx_izena," irudia ezabatzen\n"));
            /*In this case we need to get the previous element to the one we want to erase*/
            auxiliar_object = _first_object;
            while (auxiliar_object->next != _selected_object)
                auxiliar_object = auxiliar_object->next;
            /*Now we bypass the element to erase*/
            auxiliar_object->next = _selected_object->next;
            /*free the memory*/
            free(_selected_object);
            /*and update the selection*/
            _selected_object = auxiliar_object;
        }
        break;

    case '-':
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
            console_add("Zoom out");
            /*Increase the projection plane; compute the new dimensions*/
            wd=(_ortho_x_max-_ortho_x_min)/KG_STEP_ZOOM;
            he=(_ortho_y_max-_ortho_y_min)/KG_STEP_ZOOM;
            /*In order to avoid moving the center of the plane, we get its coordinates*/
            midx = (_ortho_x_max+_ortho_x_min)/2;
            midy = (_ortho_y_max+_ortho_y_min)/2;
            /*The the new limits are set, keeping the center of the plane*/
            _ortho_x_max = midx + wd/2;
            _ortho_x_min = midx - wd/2;
            _ortho_y_max = midy + he/2;
            _ortho_y_min = midy - he/2;
        }
        else{
           	if (_selected_object != NULL){
            	stack_add(_selected_object->s,key,egoera,aldaketa);
            }
        }
        break;

    case '+':
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
            console_add("Zoom in");
            /*Increase the projection plane; compute the new dimensions*/
            wd=(_ortho_x_max-_ortho_x_min)*KG_STEP_ZOOM;
            he=(_ortho_y_max-_ortho_y_min)*KG_STEP_ZOOM;
            /*In order to avoid moving the center of the plane, we get its coordinates*/
            midx = (_ortho_x_max+_ortho_x_min)/2;
            midy = (_ortho_y_max+_ortho_y_min)/2;
            /*The the new limits are set, keeping the center of the plane*/
            _ortho_x_max = midx + wd/2;
            _ortho_x_min = midx - wd/2;
            _ortho_y_max = midy + he/2;
            _ortho_y_min = midy - he/2;
        }
        else{
        	if (_selected_object != NULL){
            	stack_add(_selected_object->s,key,egoera,aldaketa);
            }
        }
        break;

    case '?':
        print_help();
        break;

    case 27: /* <ESC> */
        console_add("Agur!");
        exit(0);
        break;
    case 26: /*CTRL + Z*/
        if (_selected_object != NULL){
            console_add("Atzera egiten");
            pop(_selected_object->s);
        }
        break;
    case 25: /*CTRL + Y*/
        if (_selected_object != NULL){
            console_add("Aurrera egiten");
            redo(_selected_object->s);
        }
        break;
    case 114:
        console_add("Orain Z,Y,+,- Sakatu\n");
        break;
    case 'L':
    case 'l':
        aldaketa = 'l';
        break;
    case 'G':
    case 'g':
        aldaketa = 'g';
    case 'M':
    case 'm':
    	egoera = 'm';
        break;
    case 'T':
    case 't':
        egoera = 't';
        break;
    case 'B':
    case 'b':
        egoera = 'b';
        break;
    case 'O':
    case'o':
    	egoera = 'o';
    	break;
    default:
        /*In the default case we just print the code of the key. This is usefull to define new cases*/
        console_add("? sakatu laguntza ikusteko");
    }
    /*In case we have do any modification affecting the displaying of the object, we redraw them*/
    glutPostRedisplay();
}
void keyboardSpecial(int key, int x, int y){
    char* fname = malloc(sizeof (char)*128); /* Note that scanf adads a null character at the end of the vector*/
    int read = 0;
    object3d *auxiliar_object = 0;
    GLdouble wd,he,midx,midy;

	switch (key) {
            
    case 101:
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
            console_previousMezua();
        }
    case 103:
        if (glutGetModifiers() == GLUT_ACTIVE_CTRL){
            console_nextMezua();
        }
    case 100: 
    case 102:  
    case 104:
    case 105:
    case '+':
    case '-':
    case 114:
        if((egoera=='b') || (egoera=='t') || (egoera=='m') || (egoera=='o')){
            if (_selected_object != NULL){
            	stack_add(_selected_object->s,key,egoera,aldaketa);
            }
        }
        else if (glutGetModifiers() != GLUT_ACTIVE_CTRL){
            console_add("Aldaketa mota aukeratu (B/T/M/O)");
        }           
    default:
        /*In the default case we just print the code of the key. This is usefull to define new cases*/
        printf("%d %c\n", key, key);
        break;
    }
    /*In case we have do any modification affecting the displaying of the object, we redraw them*/
    glutPostRedisplay();
};
