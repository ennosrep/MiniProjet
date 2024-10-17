#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

// --------------------
//      Fonctions 
// --------------------

void emptyBuffer(void) {
    // Vide le buffer après une saisie clavier
    // (ne convient pas après la lecture d'un fichier)
    while (getchar() != '\n');
}

void readChoice(int *p_choix) {
    // Boucle jusqu'à ce qu'un entier compris entre 1 et 7 soit saisi au clavier 
    while (scanf("%d", p_choix) != 1 || *p_choix<1 || *p_choix>7) {
        emptyBuffer();
        printf("Merci d'entrer un nombre compris entre 1 et 7 : ");
    }
    emptyBuffer();
}

void readName(char *p_nom) {
    // Boucle jusqu'à ce qu'une chaine de caractères (30 max) soit saisie au clavier 
    while (scanf("%30[^\n]", p_nom)!= 1){
        emptyBuffer();
        printf("Erreur lors de la saisie. Merci de recommencer : ");
    }
    emptyBuffer();
}

void readTel(char *p_tel) {
    // Boucle jusqu'à ce qu'un numéro de tel à dix chiffres sans espace soit saisi au clavier 
    regex_t regex;
    regcomp(&regex, "^[0-9]{10}$", REG_EXTENDED);
    while (scanf("%10s", p_tel)!= 1 || regexec(&regex, p_tel, 0, NULL, 0)!= 0) {
        emptyBuffer();
        printf("Merci de saisir un numéro de téléphone à dix chiffres sans espace : ");
    }
    regfree(&regex);
    emptyBuffer();
}

int searchContactByName(int nbContacts, char nom[31], char t_nom[100][31]){
    // Boucle jusqu'à ce que le nom soit trouvé, sinon retourne -1
    for (int i = 0; i < nbContacts; i++)
        if (strcmp(nom, t_nom[i]) == 0) return i;
    return -1;
}

int searchContactByTel(int nbContacts, char tel[11], char t_tel[100][11]){
    // Boucle jusqu'à ce que le tel soit trouvé, sinon retourne -1
    for (int i = 0; i < nbContacts; i++)
        if (strcmp(tel, t_tel[i]) == 0) return i;
    return -1;
}

// Fonction pour supprimer un contact sur les deux tableaux en fonction de l'id
void deleteContactById(int id, int *p_nbContacts, char t_nom[100][31], char t_tel[100][11]) {
    for (int i = id; i < *p_nbContacts; i++) {
        // Décale tous les contacts d'une position
        strcpy(t_nom[i], t_nom[i+1]);
        strcpy(t_tel[i], t_tel[i+1]);
    }
    // décrémente la variable nbContacts du main
    (*p_nbContacts)--;
}

// Fonction pour montrer tous les contacts
void showAllContacts(int nbContacts, char t_nom[100][31], char t_tel[100][11]) {
    if (nbContacts == 0) printf ("\nIl n'y a aucun contact enregistré.\n");
    else {
        printf("\nListe des contacts :\n");
        for (int i = 0; i < nbContacts; i++)
            printf("%d. %s - %s\n", i+1, t_nom[i], t_tel[i]);
    }
}