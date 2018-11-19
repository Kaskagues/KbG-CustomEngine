#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "definitions.h"

extern console * _kontsola;
mezuak *selected_backup=0;

/* function declaration */
void console_initialization();
void console_add(char* mezua);
void console_delLast();
char* console_thisMezua();
char* console_selectLast();
char* console_nextMezua();
char* console_previousMezua();
int console_hasNext();
int console_hasPrevious();
void console_backup_set();
void console_backup_restore();

/* int main(int argc, char** argv) {
    initialization();
    add("Mezua 1");
    add("Mezua 2");
    add("Mezua 3");
    printf("%s\n",previousMezua());
    printf("%s\n",thisMezua());
    printf("%s\n",nextMezua());
    printf("%s\n",nextMezua());
    printf("%s\n",nextMezua());
    delLast();
    printf("%s\n",thisMezua());
    delLast();
    printf("%s\n",thisMezua());
    delLast();
    printf("%s\n",thisMezua());
    return 0;
} */

void console_initialization(){
    _kontsola = (struct console*)malloc(sizeof(struct console)); 
    _kontsola->selected_mezua=0;
    _kontsola->first_mezua=0;
    _kontsola->mezu_kop=0;
}
void console_add(char* text){
    printf("%s\n",text);
    mezuak *mezuBerria=(struct mezuak*)malloc(sizeof(struct mezuak));
    mezuBerria->textua=text;
    if(_kontsola->mezu_kop<1){
        //Hutsa
        mezuBerria->next=mezuBerria;
        mezuBerria->previous=mezuBerria;
        _kontsola->first_mezua=mezuBerria;
        _kontsola->selected_mezua=mezuBerria;
    }
    else{
        mezuBerria->next=_kontsola->first_mezua;
        mezuBerria->previous=_kontsola->first_mezua->previous;
        _kontsola->first_mezua->previous->next=mezuBerria;
        _kontsola->first_mezua->previous=mezuBerria;
    }
    console_nextMezua();
    _kontsola->mezu_kop++;
}
void console_delLast(){
    if(_kontsola->mezu_kop==0){
        printf("Ez dago mezurik");
    }
    else if(_kontsola->mezu_kop==1){
        printf("Geratzen zen mezu bakarra ezabatzen %s\n",_kontsola->first_mezua->textua);
        _kontsola->first_mezua=0;
        _kontsola->selected_mezua=0;
        _kontsola->mezu_kop=0;
    }
    else{
        printf("Azkeneko mezua ezabatzen %s\n",_kontsola->first_mezua->previous->textua);
        mezuak *aux=_kontsola->first_mezua->previous->previous;
        if(_kontsola->selected_mezua->next==_kontsola->first_mezua){
            _kontsola->selected_mezua=aux;
        }
        aux->next=_kontsola->first_mezua;
        _kontsola->first_mezua->previous=aux;
        _kontsola->mezu_kop--;
    }
}
char* console_thisMezua(){
    if(_kontsola->selected_mezua!=0){
        return _kontsola->selected_mezua->textua;
    }
    else{
        return "Ez dago mezurik";
    }
}
char* console_selectLast(){
    if(_kontsola->selected_mezua!=0){
        _kontsola->selected_mezua=_kontsola->first_mezua->previous;
        return _kontsola->selected_mezua->textua;
    }
    else{
        return "Ez dago mezurik";
    }
}
char* console_nextMezua(){
    if(console_hasNext()){
        _kontsola->selected_mezua=_kontsola->selected_mezua->next;
        return console_thisMezua();
    }
    else{
        return "Azkeneko mezuan gaude";
    }
}
char* console_previousMezua(){
    if(console_hasPrevious()){
        _kontsola->selected_mezua=_kontsola->selected_mezua->previous;
        return console_thisMezua();
    }
    else{
        return "Lehenengo mezuan gaude";
    }
}
int console_hasNext(){
    if(_kontsola->first_mezua!=0){
        if(_kontsola->selected_mezua->next==_kontsola->first_mezua){
            return 0;
        }else{
            return 1;
        }
    }
}
int console_hasPrevious(){
    if(_kontsola->selected_mezua==_kontsola->first_mezua){
        return 0;
    }else{
        return 1;
    }
}
void console_backupSet(){
    selected_backup=_kontsola->selected_mezua;
}
void console_backupRestore(){
    _kontsola->selected_mezua=selected_backup;
}