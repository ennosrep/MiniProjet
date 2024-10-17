#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "player.h"

// ----------------------------------------
//      FORMULAIRE DE CONTACTS
// ----------------------------------------

int main(void) {
    char nom[31];
    char tel[11];
    char t_nom[100][31];
    char t_tel[100][11];
    int choix;
    int id, der = 0;

    do {
        // Affichage du menu
        printf("\nQue voulez-vous faire ?\n\n");
        printf("1 - Ajouter un contact (nom, tel)\n");
        printf("2 - Supprimer un contact par nom\n");
        printf("3 - Supprimer un contact par tel\n");
        printf("4 - Rechercher un contact par nom\n");
        printf("5 - Rechercher un contact par tel\n");
        printf("6 - Montrer tous les contacts\n");
        printf("7 - Quitter le programme\n");
        printf("\nVeuillez saisir votre choix : ");
        readChoice(&choix);

        // Traitement du choix
        switch(choix) {
            // Ajouter un contact (nom, tel)
            case 1 : 
                if(der == 100) printf("Vous avez dépassé votre nombre maximum de contacts. Veuillez d'abord supprimer un contact.\n");
                else {
                    printf("Veuillez saisir le nom du contact à créer : ");
                    readName(nom);  
                    printf("Veuillez saisir le numéro de téléphone : ");
                    readTel(tel);    
                    // Création du contact
                    strcpy(t_nom[der], nom);
                    strcpy(t_tel[der], tel);
                    printf("\nCe contact a été créé : %s - %s\n", nom, tel);
                    // Incrémentation de la variable der 
                    der++;
                }
                break;
            // Supprimer un contact par nom
            case 2 : 
                if (der == 0) printf ("\nIl n'y a aucun contact enregistré.\n");
                else {
                    printf("Veuillez saisir le nom du contact à supprimer : ");
                    readName(nom);
                    // Recherche du contact
                    id = searchContactByName(der, nom, t_nom);
                    if (id != -1) {
                        // Suppression du contact
                        deleteContactById(id, &der, t_nom, t_tel);
                        printf("\nCe contact a été supprimé.\n");
                    } else printf("\nDésolé, ce contact n'existe pas.\n");
                }        
                break;
            // Supprimer un contact par tel
            case 3 : 
                if (der == 0) printf ("\nIl n'y a aucun contact enregistré.\n");
                else {
                    printf("Veuillez saisir le numéro de téléphone du contact à supprimer : ");
                    readTel(tel);
                    // Recherche du contact
                    id = searchContactByTel(der, tel, t_tel);
                    if (id != -1) {
                        // Suppression du contact
                        deleteContactById(id, &der, t_nom, t_tel);
                        printf("\nCe contact a été supprimé.\n");
                    } else printf("\nDésolé, ce contact n'existe pas.\n");
                }
                break;
            // Rechercher un contact par nom
            case 4 : 
                printf("Veuillez saisir le nom du contact à rechercher : ");
                readName(nom);
                // Recherche du contact
                id = searchContactByName(der, nom, t_nom);
                if (id != -1) printf("\nCe contact est le n°%d : %s - %s\n", id+1, t_nom[id], t_tel[id]);
                else printf("\nDésolé, ce contact n'existe pas.\n");
                break;
            // Rechercher un contact par tel
            case 5 : 
                printf("Veuillez saisir le numéro de téléphone du contact à rechercher : ");
                readTel(tel);
                // Recherche du contact
                id = searchContactByTel(der, tel, t_tel);
                if (id != -1) printf("\nCe contact est le n°%d : %s - %s\n", id+1, t_nom[id], t_tel[id]);
                else printf("\nDésolé, ce contact n'existe pas.\n");
                break;
            // Montrer tous les contacts
            case 6 : 
                showAllContacts(der, t_nom, t_tel);
                break;
        }

    } while (choix!=7);

    printf("\nMerci d'avoir utilisé ce programme.\n\n");

    return 0;
    
}