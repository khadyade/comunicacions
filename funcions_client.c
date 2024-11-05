/*
 ================================ PROJECTE XARXES ================================
 | Fitxer     : funcions_client.c                                                |
 | Autors     : Programador 1, Programador 2, Programador 3                      |
 | Assignatura: Xarxes (Segon curs, Enginyeria Informàtica)                      |
 | Universitat: Universitat Rovira i Virgili                                     |
 | Descripció : Breu descripció del fitxer o mòdul                               |
 =================================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "funcions_servidor.h"


void mostra_titol() {
    printf(" ==============================\n");
    printf(" |      PROJECTE XARXES       |\n");
    printf(" ==============================\n");
}

int connecta_servidor(const char *ip, int port) {
    int s = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in contacte_servidor;
    contacte_servidor.sin_family = AF_INET;
    contacte_servidor.sin_addr.s_addr = inet_addr(ip);
    contacte_servidor.sin_port = htons(port);
    printf("Connectat al servidor %s:%d\n", ip, port);
    return s;
}

void demana_credencials(char *nom, char *contrasenya) {
    printf("Introdueix el teu nom (fins a %d caràcters): ", MAX_USUARI);
    scanf("%s", nom);
    printf("Introdueix la teva contrasenya (fins a %d caràcters): ", MAX_CONTRASENYA);
    scanf("%s", contrasenya);
}

int verifica_credencials(int s) {
    char nom[MAX_USUARI], contrasenya[MAX_CONTRASENYA], paquet[MIDA_PAQUET];
    demana_credencials(nom, contrasenya);

    snprintf(paquet, MIDA_PAQUET, "LOGIN %s %s", nom, contrasenya);
    sendto(s, paquet, MIDA_PAQUET, 0, NULL, sizeof(struct sockaddr_in));
    recvfrom(s, paquet, MIDA_PAQUET, 0, NULL, NULL);

    if (strcmp(paquet, "Usuari verificat") == 0) {
        printf("Benvingut %s!\n", nom);
        return 1;
    } else {
        printf("Credencials incorrectes. Introdueix-les de nou.\n");
        return 0;
    }
}

int mostra_menu() {
    int opcio;
    mostra_titol();
    printf("1. Veure perfil\n");
    printf("2. Veure els meus amics\n");
    printf("3. Afegir amic\n");
    printf("4. Eliminar amic\n");
    printf("5. Sortir\n");
    printf("Selecciona una opció: ");
    scanf("%d", &opcio);
    return opcio;
}

void gestiona_menu(int s) {
    int opcio;
    do {
        opcio = mostra_menu();
        processa_opcio(s, opcio);
    } while (opcio != 5);
}

void processa_opcio(int s, int opcio) {
    char paquet[MIDA_PAQUET], nom_amic[MAX_USUARI];

    switch (opcio) {
        case 1:
            strcpy(paquet, "PERFIL");
            sendto(s, paquet, MIDA_PAQUET, 0, NULL, sizeof(struct sockaddr_in));
            break;
        case 2:
            strcpy(paquet, "AMICS");
            sendto(s, paquet, MIDA_PAQUET, 0, NULL, sizeof(struct sockaddr_in));
            break;
        case 3:
            printf("Introdueix el nom del nou amic: ");
            scanf("%s", nom_amic);
            snprintf(paquet, MIDA_PAQUET, "AFEGIR_AMIC %s", nom_amic);
            sendto(s, paquet, MIDA_PAQUET, 0, NULL, sizeof(struct sockaddr_in));
            break;
        case 4:
            printf("Introdueix el nom de l'amic a eliminar: ");
            scanf("%s", nom_amic);
            snprintf(paquet, MIDA_PAQUET, "ELIMINAR_AMIC %s", nom_amic);
            sendto(s, paquet, MIDA_PAQUET, 0, NULL, sizeof(struct sockaddr_in));
            break;
        case 5:
            printf("Sortint...\n");
            break;
        default:
            printf("Opció no vàlida.\n");
            break;
    }

    recvfrom(s, paquet, MIDA_PAQUET, 0, NULL, NULL);
    printf("Resposta del servidor: %s\n", paquet);
}