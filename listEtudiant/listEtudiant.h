#include "etudiant.h"
#ifndef __LIST__EUTIDIANT__
#define __LIST__EUTIDIANT__

typedef enum
{
	false,
	true
}Bool;


// verifier si la liste est vide

typedef struct listEtudiant{

	Etudiant etudiant;
	struct listEtudiant *SUIV;

}listEtudiant, *List;


Bool isEmptyList(List li); //verifier si la liste est vide
List initialList(void); //Initialiser la liste

int sizeOfList(char file[100]); // Acceder à la taille de la liste
void printList(char file[100]); // Afficher la liste

void dispList(List li); //Affichage après recup de la liste
List addElement(List li, Etudiant e); // ajouter une élément(debut de la liste)
Bool Ajouter(char file[100], Etudiant e); // ajout des données

void majSize(char ops); //Mise à jour du fichier de dépot des données grace à un ops(+/-)
Bool fileEmpty(char file[100]); //Fonction pour vérifier si un fichier est vide

List getList(char file[100]);
Bool Supprimer(char file[100], int numeroCarte); //Fonction qui supprime un élément n'importe ou dans la liste chainée en précisant le numero de la carte de l'etudiant

void Tri(listEtudiant *li); //la fonction de tri, qui est basé sur un tri a bulle
List InverserListe(List li);  // fonction d'inverse, de façon itératif

void PromoFinale(List li); //Afficher la liste des étudiants apte à passer en annéé sup
#endif