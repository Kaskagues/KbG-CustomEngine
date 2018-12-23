#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <GL/gl.h>

/** DEFINITIONS **/

#define KG_WINDOW_TITLE                     "KbG/Motore grafikoa - Andoni eta Aritz"
#define KG_WINDOW_WIDTH                     720
#define KG_WINDOW_HEIGHT                    480
#define KG_WINDOW_X                         600
#define KG_WINDOW_Y                         300

#define KG_MSSG_SELECT_FILE                 "Idatz ezazu fitxategiaren path-a: "
#define KG_MSSG_FILENOTFOUND                "Fitxategi hori ez da existitzen!!"
#define KG_MSSG_INVALIDFILE                 "Arazoren bat egon da fitxategiarekin ..."
#define KG_MSSG_EMPTYFILE                   "Fitxategia utsik dago"
#define KG_MSSG_FILEREAD                    "Fitxategiaren irakurketa buruta"

#define KG_STEP_MOVE                        0.25f
#define KG_STEP_ROTATE                      0.25f
#define KG_STEP_ZOOM                        0.75f
#define KG_STEP_CAMERA_ANGLE                0.25f
#define KG_INITIAL_ZNEAR                    0.1f
#define KG_INITIAL_ZFAR                     100.f
#define KG_INITIAL_FOV                      100.f
#define KG_MIN_FOV                          45.f
#define KG_MAX_FOV                          135.f
#define KG_STEP_FOV                         5.f
#define KG_INITIAL_STATE                    'o'

#define KG_ORTHO_X_MIN_INIT                -5
#define KG_ORTHO_X_MAX_INIT                 5
#define KG_ORTHO_Y_MIN_INIT                -5
#define KG_ORTHO_Y_MAX_INIT                 5
#define KG_ORTHO_Z_MIN_INIT                -100
#define KG_ORTHO_Z_MAX_INIT                 10000

#define KG_COL_BACK_R                       0.1f
#define KG_COL_BACK_G                       0.1f
#define KG_COL_BACK_B                       0.6f
#define KG_COL_BACK_A                       1.00f

#define KG_COL_SELECTED_R                   1.00f
#define KG_COL_SELECTED_G                   1.00f
#define KG_COL_SELECTED_B                   1.00f

#define KG_COL_NONSELECTED_R                0.50f
#define KG_COL_NONSELECTED_G                0.00f
#define KG_COL_NONSELECTED_B                0.00f

#define KG_COL_X_AXIS_R                     0.9f
#define KG_COL_X_AXIS_G                     0.0f
#define KG_COL_X_AXIS_B                     0.4f

#define KG_COL_Y_AXIS_R                     0.0f
#define KG_COL_Y_AXIS_G                     0.8f
#define KG_COL_Y_AXIS_B                     0.65f

#define KG_COL_Z_AXIS_R                     0.55f
#define KG_COL_Z_AXIS_G                     0.95f
#define KG_COL_Z_AXIS_B                     0.0f

#define KG_FLOOR_SIZE			            100
#define KG_FLOOR_STEPS			            10

#define KG_MAX_DOUBLE                       10E25
              
#define KG_STACK_MAX_SIZE                   1024


/** STRUCTURES **/

/****************************
 * Structure to store the   *
 * coordinates of 3D points *
 ****************************/
typedef struct {
    GLdouble x, y, z;
} point3;

/*****************************
 * Structure to store the    *
 * coordinates of 3D vectors *
 *****************************/
typedef struct {
    GLdouble x, y, z;
} vector3;

/****************************
 * Structure to store the   *
 * colors in RGB mode       *
 ****************************/
typedef struct {
    GLfloat r, g, b;
} color3;

/****************************
 * Structure to store       *
 * objects' vertices         *
 ****************************/
typedef struct {
    point3 coord;                       /* coordinates,x, y, z */
    GLint num_faces;                    /* number of faces that share this vertex */
} vertex;

/****************************
 * Structure to store       *
 * objects' faces or        *
 * polygons                 *
 ****************************/
typedef struct {
    GLint num_vertices;                 /* number of vertices in the face */
    GLint *vertex_table;                /* table with the index of each vertex */
} face;

/****************************
 * Structure to store       *
 * kontsolarako info        *
 ****************************/
struct mezuak{
    struct mezuak *next;
    struct mezuak *previous;
    char* textua;
    //GOGORATU BETI ARRAY-AK AZKENEKO LERROAN JARTZEA
    //bestela C-ek struct-a kopiatzean array-a eraldatzen du
};

typedef struct mezuak mezuak;

struct console{
    int mezu_kop;
    struct mezuak * selected_mezua;
    struct mezuak * first_mezua;
};

typedef struct console console;

struct stack {
    GLdouble *matrizeak[KG_STACK_MAX_SIZE];
    int selected;
    int upto;
};

typedef struct stack stack;

/****************************
 * Structure to store a     *
 * pile of 3D objects       *
 ****************************/
struct object3d{
    char *fitx_izena;                 /* objektuaren fitxategiaren izena*/
    GLint num_vertices;                 /* number of vertices in the object*/
    vertex *vertex_table;               /* table of vertices */
    GLint num_faces;                    /* number of faces in the object */
    face *face_table;                   /* table of faces */
    point3 min;                         /* coordinates' lower bounds */
    point3 max;                         /* coordinates' bigger bounds */
    struct object3d *next;              /* next element in the pile of objects */
    stack *s;
    stack *kamara_s;
};

typedef struct object3d object3d;

/****************************
 * Structure to store a     *
 * the camera settings      *
 ****************************/
struct camara{
    stack *perspective;                //Kamara munduari 
    stack *world_camara;                /*Kamara munduari begira dagoenerako*/
    struct object3d *objektu_kamara;    /*Kamara objektu bat jarraitzen duenerako*/
    int FOV;
    int zNear;
    int zFar;
    char state;
};

typedef struct camara camara;

#endif // DEFINITIONS_H
 
