#include "funcions_servidor.h"
#include <stdio.h>
#include <string.h>

const char* processa_opcio(int opcio, const char *nom, int *continuar) {
    const char *resposta;
    usuari_t user;
    switch (opcio) {
        case 1:
            user = get_user_info(nom);
            resposta = (user.nom[0] != '\0') ? veure_perfil(&user) : "Usuari no trobat\n";
            break;
        case 2:
            resposta = veure_amics(nom);
            break;
        case 3:
            resposta = afegir_amic(nom, "nou_amic");
            break;
        case 4:
            resposta = eliminar_amic(nom, "amic_a_eliminar");
            break;
        case 5:
            resposta = "Sortint del programa...";
            *continuar = 0;
            break;
        default:
            resposta = "Opció invàlida.";
    }
    return resposta;
}

const char* eliminar_amic(const char *nom, const char *amic_a_eliminar) {
    static char resposta[100];
    FILE *file = fopen(FRIEND_FILE, "r+");
    FILE *temp_file = fopen("amistats_temp.txt", "w");

    char line[100];
    int found = 0;

    while (fgets(line, sizeof(line), file)) {
        char user1[MAX_USUARI], user2[MAX_USUARI];
        sscanf(line, "%s %s", user1, user2);

        if ((strcmp(user1, nom) == 0 && strcmp(user2, amic_a_eliminar) == 0) ||
            (strcmp(user1, amic_a_eliminar) == 0 && strcmp(user2, nom) == 0)) {
            found = 1;
        } else {
            fputs(line, temp_file);
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(FRIEND_FILE);
    rename("amistats_temp.txt", FRIEND_FILE);

    snprintf(resposta, sizeof(resposta), found ? "Amistat eliminada." : "Amistat no trobada.");
    return resposta;
}
