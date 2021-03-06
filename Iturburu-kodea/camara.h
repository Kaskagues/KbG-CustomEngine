#ifndef CAMARA_H
#define CAMARA_H

void camara_initialization();
void camara_alter_state();
char camara_get_state();
int camara_get_FOV();
float camara_get_zNear();
float camara_get_zFar();
int camara_is_orthogonal();
int camara_is_prespective();
int camara_is_ibiltaria();
void camara_zoom_in();
void camara_zoom_out();
stack* camara_get_stack();
void camara_move(int key, char egoera, char aldaketa);

#endif // CAMARA_H
