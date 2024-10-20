#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include "player.h"

// ----------------------------------------
//      FORMULAIRE DE CONTACTS
// ----------------------------------------

// Pour l'exercice, on considère que si le nom ou le prénom existe déjà, le contact est un doublon

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
        printf("7 - Charger les contacts depuis un fichier\n");   
        printf("8 - Sauvegarder les contacts dans un fichier\n");  
        printf("9 - Quitter le programme\n");
        printf("\nVeuillez saisir votre choix : ");
        readChoice(&choix, 9);

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
            // Charger les contacts depuis un fichier
            case 7 :
                // Ouverture du fichier
                FILE *lecture = fopen("contacts.txt", "r");
                if (lecture == NULL) {
                    printf("\nErreur lors de l'ouverture du fichier à charger.\n");
                } else {
                    // Gestion du cas où des contacts sont déjà présents dans le tableau
                    if(nbContacts > 0) {
                        printf("Vous avez déjà des contacts dans le tableau. Que voulez-vous faire ?\n");
                        printf("1 - Charger le fichier et écraser les contacs existant\n");  
                        printf("2 - Garder les contacts existants et charger le fichier\n");
                        printf("3 - Ne pas charger le fichier\n");
                        printf("\nVeuillez saisir votre choix : ");                            
                        readChoice(&choix, 3);
                    }
                    if(choix == 1) 
                        nbContacts = 0;
                    else if(choix == 3)
                        break; 
                    if(nbContacts == 100)
                        printf("Vous avez dépassé votre nombre maximum de contacts. Veuillez d'abord supprimer un contact.\n");
                    else {
                        id = nbContacts;
                        // Compilation de l'expression régulière
                        regex_t regex;
                        regcomp(&regex, "^[0-9]{10}$", REG_EXTENDED);
                        // Lecture des contacts dans le fichier
                        while (fscanf(lecture, "%10s %30[^\n]", tel, nom) != EOF && nbContacts < 100) {
                            if(regexec(&regex, tel, 0, NULL, 0)!= 0)
                                printf("\nUn numéro de téléphone n'est pas au format requis. La ligne est ignorée.");
                            else if (searchContactByName(nbContacts, nom, t_contact)!=-1 || searchContactByTel(nbContacts, tel, t_contact)!=-1)
                                printf("\nCe contact existe déjà. La ligne est ignorée.");
                            else
                            {
                                // Enregistrement de ce contact valide dans le tableau
                                strcpy(t_contact[nbContacts].tel, tel);
                                strcpy(t_contact[nbContacts].nom, nom);
                                nbContacts++;
                            }
                        }
                        if(nbContacts == id)
                            printf("\nIl n'y avait aucun nouveau contact valide à charger depuis ce fichier.\n");
                        else 
                            printf("\nLes contacts ont été chargés depuis le fichier.\n");
                        if(nbContacts == 100)
                            printf("Le nombre maximum de contacts a été atteint.\n");
                        if(fscanf(lecture, "%10s %30[^\n]", tel, nom) != EOF)    
                            printf("Les dernières lignes ont été ignorées.\n");
                        // Fermeture du fichier
                        fclose(lecture);
                        regfree(&regex);
                    }
                }
                break;
            // Sauvegarder les contacts dans un fichier
            // Pour l'exercice, si un fichier de contacts existe déjà, il sera écrasé
            // Dans l'absolu, il faudrait vérifier si le fichier existe déjà et s'il contient des contacts
            // Puis le cas échéant, demander à l'utilisateur ce qu'il veut vraiment faire
            // S'il veut les ajouter au fichier, vérifier si on n'ajoute pas des doublons et si on ne dépasse pas 100
            // On aurait pu laisser à l'utilisateur le choix de nommer le fichier et d'en avoir plusieurs
            // On aurait pu permettre plus de 100 contacts avec une allocation dynamique de mémoire
            case 8 :
                // Ouverture du fichier
                FILE *ecriture = fopen("contacts.txt", "w");
                if (ecriture == NULL)
                    printf("\nErreur lors de l'ouverture du fichier de sauvegarde.\n");
                else {
                    // Ecriture des contacts dans le fichier
                    for (int i = 0; i < nbContacts; i++)
                        fprintf(ecriture, "%s %s\n", t_contact[i].tel, t_contact[i].nom);
                    // Fermeture du fichier
                    fclose(ecriture);
                    printf("\nLes contacts ont été sauvegardés dans le fichier.\n");
                }            
        }

    } while (choix!=9);

    printf("\nMerci d'avoir utilisé ce programme.\n\n");

    return 0;
    
}