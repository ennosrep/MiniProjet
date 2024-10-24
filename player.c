#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "player.h"

// --------------------
//      Fonctions 
// --------------------

void emptyBuffer(void) {
    // Vide le buffer après une saisie clavier
    // (ne convient pas après la lecture d'un fichier)
    while (getchar() != '\n');
}

void readChoice(int *p_choix, int nbChoix) {
    // Boucle jusqu'à ce qu'un entier compris entre 1 et 7 soit saisi au clavier 
    while (scanf("%d", p_choix) != 1 || *p_choix<1 || *p_choix>nbChoix) {
        emptyBuffer();
        printf("Merci d'entrer un nombre compris entre 1 et %d : ", nbChoix);
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
    // Compilation de l'expression régulière
    regex_t regex;
    regcomp(&regex, "^[0-9]{10}$", REG_EXTENDED);
    // Boucle jusqu'à ce qu'un numéro de tel à dix chiffres sans espace soit saisi au clavier 
    while (scanf("%10s", p_tel)!= 1 || regexec(&regex, p_tel, 0, NULL, 0)!= 0) {
        emptyBuffer();
        printf("Merci de saisir un numéro de téléphone à dix chiffres sans espace : ");
    }
    regfree(&regex);
    emptyBuffer();
}

int searchContactByName(int nbContacts, char nom[31], Contact t_contact[100]){
    // Boucle jusqu'à ce que le nom soit trouvé, sinon retourne -1
    for (int i = 0; i < nbContacts; i++)
        if (strcmp(nom, t_contact[i].nom) == 0)
            return i;
    return -1;
}

int searchContactByTel(int nbContacts, char tel[11], Contact t_contact[100]){
    // Boucle jusqu'à ce que le tel soit trouvé, sinon retourne -1
    for (int i = 0; i < nbContacts; i++)
        if (strcmp(tel, t_contact[i].tel) == 0)
            return i;
    return -1;
}

// Fonction pour supprimer un contact en fonction de l'id
void deleteContactById(int id, int *p_nbContacts, Contact t_contact[100]) {
    // décrémente la variable nbContacts du main
    (*p_nbContacts)--;
    // Décale tous les contacts d'une position 
    for (int i = id; i < *p_nbContacts; i++) {        
        strcpy(t_contact[i].nom, t_contact[i+1].nom);
        strcpy(t_contact[i].tel, t_contact[i+1].tel);
    }    
}
