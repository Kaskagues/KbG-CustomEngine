#ifndef CONSOLE_H
#define CONSOLE_H

void console_initialization();
void console_add(char* mezua);
void console_delLast();
char* console_thisMezua();
char* console_selectLast();
char* console_nextMezua();
char* console_previousMezua();
int console_hasNext();
int console_hasPrevious();
void console_backupSet();
void console_backupRestore();


#endif // CONSOLE_H
