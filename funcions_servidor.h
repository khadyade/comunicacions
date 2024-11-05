/*
 ================================ PROJECTE XARXES ================================
 | Fitxer     : funcions_servidor.h                                              |
 | Autors     : Programador 1, Programador 2, Programador 3                      |
 | Assignatura: Xarxes (Segon curs, Enginyeria Informàtica)                      |
 | Universitat: Universitat Rovira i Virgili                                     |
 | Descripció : Capçalera amb les funcions del servidor                          |
 =================================================================================
*/

#ifndef FUNCIONS_SERVIDOR_H
#define FUNCIONS_SERVIDOR_H

#include <netinet/in.h>

#define MIDA_PAQUET 100
#define MAX_USUARI 30
#define FRIEND_FILE "amistats.txt"
#define USER_FILE "usuaris.txt"

// Estructura per a la informació d'un usuari
typedef struct {
    char nom[MAX_USUARI];
    char contrasenya[MAX_USUARI];
    char sexe[10];
    char estat_civil[20];
    int edat;
    char ciutat[30];
    char descripcio[100];
} usuari_t;

// Funcions per a la gestió del servidor
int configura_socket(int port);
void gestiona_client(int s, struct sockaddr_in contacte_client);

// Funcions de gestió d'usuaris
int verifica_usuari(const char *nom, const char *contrasenya);
const char* veure_perfil(const usuari_t *usuari);
usuari_t get_user_info(const char *nom);

// Funcions per a la gestió d'amistats
const char* veure_amics(const char *nom);
const char* afegir_amic(const char *nom, const char *nou_amic);
const char* eliminar_amic(const char *nom, const char *amic_a_eliminar);

// Funció per a processar opcions del menú
const char* processa_opcio(int opcio, const char *nom, int *continuar);

#endif // FUNCIONS_SERVIDOR_H
