#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "player.h"

// ----------------------------------------
//      FORMULAIRE DE CONTACTS
// ----------------------------------------

int main(void) {
    char nom[31], tel[11];
    Contact t_contact[100];
    int choix, id, nbContacts = 0;

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
                if(nbContacts == 100)
                    printf("Vous avez dépassé votre nombre maximum de contacts. Veuillez d'abord supprimer un contact.\n");
                else {
                    printf("Veuillez saisir le nom du contact à créer : ");
                    readName(nom);  
                    if (searchContactByName(nbContacts, nom, t_contact)!=-1)
                        printf("\nErreur : ce nom est déjà dans la liste des contacts.\n");
                    else {
                        printf("Veuillez saisir le numéro de téléphone : ");
                        readTel(tel);
                        if (searchContactByTel(nbContacts, tel, t_contact)!=-1)
                            printf("\nErreur : ce numéro de téléphone est déjà dans la liste des contacts.\n");
                        else {  
                            // Création du contact
                            strcpy(t_contact[nbContacts].nom, nom);
                            strcpy(t_contact[nbContacts].tel, tel);
                            printf("\nCe contact a été créé : %s - %s\n", nom, tel);
                            // Incrémentation de la variable nbContacts 
                            nbContacts++;
                        }
                    }
                }
                break;
            // Supprimer un contact par nom
            case 2 : 
                if (nbContacts == 0)
                    printf ("\nIl n'y a aucun contact enregistré.\n");
                else {
                    printf("Veuillez saisir le nom du contact à supprimer : ");
                    readName(nom);
                    // Recherche du contact
                    id = searchContactByName(nbContacts, nom, t_contact);
                    if (id != -1) {
                        // Suppression du contact
                        deleteContactById(id, &nbContacts, t_contact);
                        printf("\nCe contact a été supprimé.\n");
                    } else printf("\nDésolé, ce contact n'existe pas.\n");
                }        
                break;
            // Supprimer un contact par tel
            case 3 : 
                if (nbContacts == 0)
                    printf ("\nIl n'y a aucun contact enregistré.\n");
                else {
                    printf("Veuillez saisir le numéro de téléphone du contact à supprimer : ");
                    readTel(tel);
                    // Recherche du contact
                    id = searchContactByTel(nbContacts, tel, t_contact);
                    if (id != -1) {
                        // Suppression du contact
                        deleteContactById(id, &nbContacts, t_contact);
                        printf("\nCe contact a été supprimé.\n");
                    } else printf("\nDésolé, ce contact n'existe pas.\n");
                }
                break;
            // Rechercher un contact par nom
            case 4 : 
                if (nbContacts == 0) printf ("\nIl n'y a aucun contact enregistré.\n");
                else {
                    printf("Veuillez saisir le nom du contact à rechercher : ");
                    readName(nom);
                    // Recherche du contact
                    id = searchContactByName(nbContacts, nom, t_contact);
                    if (id != -1)
                        printf("\nCe contact est le n°%d : %s - %s\n", id+1, t_contact[id].nom, t_contact[id].tel);
                    else printf("\nDésolé, ce contact n'existe pas.\n");
                }
                break;
            // Rechercher un contact par tel
            case 5 : 
                if (nbContacts == 0) printf ("\nIl n'y a aucun contact enregistré.\n");
                else {
                    printf("Veuillez saisir le numéro de téléphone du contact à rechercher : ");
                    readTel(tel);
                    // Recherche du contact
                    id = searchContactByTel(nbContacts, tel, t_contact);
                    if (id != -1)
                        printf("\nCe contact est le n°%d : %s - %s\n", id+1, t_contact[id].nom, t_contact[id].tel);
                    else printf("\nDésolé, ce contact n'existe pas.\n");
                }
                break;
            // Montrer tous les contacts
            case 6 : 
                if (nbContacts == 0) printf ("\nIl n'y a aucun contact enregistré.\n");
                else {
                    printf("\nListe des contacts :\n");
                    for (int i = 0; i < nbContacts; i++)
                        printf("%d. %s - %s\n", i+1, t_contact[i].nom, t_contact[i].tel);
                }
                break;
        }

    } while (choix!=7);

    printf("\nMerci d'avoir utilisé ce programme.\n\n");

    return 0;
    
}