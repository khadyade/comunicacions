/*
 ================================ PROJECTE XARXES ================================
 | Fitxer     : client.c                                                         |
 | Autors     : Programador 1, Programador 2, Programador 3                      |
 | Assignatura: Xarxes (Segon curs, Enginyeria Informàtica)                      |
 | Universitat: Universitat Rovira i Virgili                                     |
 | Descripció : Breu descripció del fitxer o mòdul                               |
 =================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "funcions_client.h"

#define MIDA_PAQUET 100
#define MAX_USUARI 30
#define MAX_CONTRASENYA 30

/**
 * @brief Funció principal del client per connectar-se al servidor, verificar credencials i mostrar el menú
 *
 * @param argc Nombre d'arguments passats per línia de comandes (haurien de ser 3)
 * @param argv Vector de cadenes amb els arguments (IP i port del servidor)
 * @return int Retorna 0 al final de l'execució correcte
 *
 * Aquesta funció crea un socket de connexió amb el servidor, demana les credencials de l'usuari
 * i les envia per a la verificació. Si la verificació és correcta, mostra un menú que permet a l'usuari
 * interactuar amb diferents opcions fins que decideixi sortir.
 */


int main(int argc, char **argv) {
    if (argc != 3) {
        printf("Ús: %s <IP> <PORT>\n", argv[0]);
        return -1;
    }

    int s = connecta_servidor(argv[1], atoi(argv[2]));
    if (s < 0) return -1;

    if (verifica_credencials(s)) {
        gestiona_menu(s);
    }

    close(s);
    return 0;
}