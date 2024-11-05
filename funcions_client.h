/*
 ================================ PROJECTE XARXES ================================
 | Fitxer     : funcions_client.h                                                |
 | Autors     : Programador 1, Programador 2, Programador 3                      |
 | Assignatura: Xarxes (Segon curs, Enginyeria Informàtica)                      |
 | Universitat: Universitat Rovira i Virgili                                     |
 | Descripció : Capçalera amb les funcions del client                            |
 =================================================================================
*/

#ifndef FUNCIONS_CLIENT_H
#define FUNCIONS_CLIENT_H

#include <netinet/in.h>

#define MIDA_PAQUET 100
#define MAX_USUARI 30
#define MAX_CONTRASENYA 30

// Funcions per a la gestió de la connexió amb el servidor
int connecta_servidor(const char *ip, int port);
void gestiona_menu(int s);

// Funcions per a la gestió del menú i credencials
void mostra_titol();
void demana_credencials(char *nom, char *contrasenya);
int mostra_menu();
int verifica_credencials(int s);
void processa_opcio(int s, int opcio);

#endif // FUNCIONS_CLIENT_H
