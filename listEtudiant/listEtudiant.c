#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listEtudiant.h"


#define EXIT EXIT_FAILURE

// Vérification si la liste est vide
Bool isEmptyList(List li)
{
	if(li == NULL)
		return true;
	return false;
}

//Nouvelle liste considéré comme null
List initialList(void)
{
	return NULL;
}
// La longueur de la liste
int sizeOfList(char file[100])
{
	int size = 0;
	FILE *fic = fopen(file, "r");
	size = fgetc(fic) - '0';
	return size;

}

// Affichage de la liste

void printList(char file[100])
{
	List li = getList(file);
	//Affichage de la liste chainé après remplissage des éléments
	if(isEmptyList(li)){
		printf("Aucun n'affichage disponible, la liste est vide\n");
		return;
	}
 	printf("Nom\t|\t  Prenoms \t |  | Carte Etudiant | \t\tMoyenne \n");
	while(li!=NULL)
	{
		printf("\n%s\t\t   %s   \t   %d   \t\t%d\n", li->etudiant.nom,  li->etudiant.prenom,  li->etudiant.numeroCarte, li->etudiant.moyenneExamen );
		li = li->SUIV;
		printf("-------------------------------------------------------------------------------\n");
	}
	printf("\n");
}			

// Affichage de la liste à travers un paramètre en liste
void dispList(List li)
{
	printf("Nom\t|\t  Prenoms \t |  | Carte Etudiant | \t\tMoyenne \n");
	while(!isEmptyList(li))
	{
		printf("\n%s\t\t   %s   \t   %d   \t\t%d\n", li->etudiant.nom,  li->etudiant.prenom,  li->etudiant.numeroCarte, li->etudiant.moyenneExamen );
		li = li->SUIV;
		printf("-------------------------------------------------------------------------------\n");
	}
	printf("\n");
}

//Fonction permettant d'Ajouter des éléments à la liste des étudiants
List addElement(List li, Etudiant e)
{	

	listEtudiant *lEtudiant;

	lEtudiant = malloc(sizeof(*lEtudiant));
	
	if(lEtudiant == NULL)
	{
		printf("L'allocation a échoué...\n");
		exit(EXIT);
	}
	
	lEtudiant->etudiant = e;
	if(isEmptyList(li))
	{
		lEtudiant->SUIV = NULL;
	}
	else{
		lEtudiant->SUIV = li;
	}

	return lEtudiant;
}
// -----------------------------------La fameuse fonction qui ajoute les éléments dans nôtre BD--------------------------------------
//Ajouter de la donnée Etudiant dans le fichier
Bool Ajouter(char file[100], Etudiant e)
{
	if(strlen(file) > 99){
		fprintf(stderr, "La taille du fichier doit être < 99 caratères\n");
		exit(1);
	}

	FILE *fic = fopen(file,"a+");
	if(fic == NULL)
		exit(1);

	fprintf(fic, "%s %s %d %d\n",e.nom, e.prenom, e.numeroCarte, e.moyenneExamen);

	//Fermetture du fichier
	fclose(fic);
	return true;
}

// ---------------------------Proccedure pour mettre à jour le fichier .crypt qui correspond au nombre d'Etudiant -----------------------------

void majSize(char ops) 
//destiné de mettre à jour le nombre d'Etudiant dans la liste soit en incrémentant soit en décrémentant
//grace à un opérateur appelé 'ops'[qui est soit +/-]
{
	int sizeList = sizeOfList("nb.crypt");
	if(ops == '+'){
		sizeList++;
	}else if(ops == '-'){
		sizeList--;
	}else{
		fprintf(stderr, "[Erreur] le caractère doit être (+/-)\n");
		exit(EXIT);
	}
	FILE *fic = fopen("nb.crypt", "w+");
	char c = sizeList + '0';
	fputc(c,fic);
	fclose(fic);
}
// --------------------------Fontion qui vérifie si le fichier des données est vide ----------------------------------------
Bool fileEmpty(char file[100])
{
	FILE *fic = fopen(file, "r");
	char c = fgetc(fic) + '0';
	fclose(fic);
	if(c == '/') //Ce caractère dans le fichier, montre que celui-ci est vraiment vide
		return true;
	else 
		return false;
}

// ------------------------------------Fonction qui charge les éléments de la liste------------------------------------

//Charger les données depuis le fichier les contenants
List getList(char file[100]){

int size = 0;

	//Vérifier si le fichier est vide
	if(fileEmpty("nb.crypt")) // Si le ficher est vide alors on crée un fichier et l'on n'y ajoute un 0 afin de pouvoir recuppérer ce 0
	{
		FILE *fila = fopen("nb.crypt", "w+");
		fputc('0', fila);
		fclose(fila);
		printf("Aucun élément...\n");
		exit(1);
	}

	Etudiant e;
	List li = initialList();
	FILE *fic = fopen(file, "r");
	
	if(fic == NULL)
	{
		printf("Aucun fichier de ce nom\n");
		exit(EXIT);
	}
	size = sizeOfList("nb.crypt");
	if(size == 0)
	{
		li = initialList();
	}else{
		for(int i = 0; i<size; i++)
		{
			fscanf(fic, "%s%s%d%d", e.nom, e.prenom, &e.numeroCarte, &e.moyenneExamen);
			li = addElement(li, e);
		}	
	}
	fclose(fic); // fermetture du fichier
	return li;
 }

// ------------------------------------------------------------------------------------------

Bool Supprimer(char file[100], int numeroCarte)
{
	List li = getList(file);
	Bool found = false; 

	// Vérifier si la liste est deja vide ou si le fichier est vide
	if(isEmptyList(li) || fileEmpty(file))
	{
		printf("La liste est vide\n");
		return false;
	}
	char nom[25];
	listEtudiant *Etudiant;
	List temp;
	if(li->etudiant.numeroCarte == numeroCarte) //Si le numero de la carte corresppond au premier élément de la liste
	{
		temp = li;
		li = li->SUIV;
		free(temp);
		temp = NULL;
		if(li == NULL) //Si la liste est null après avoir enlevé ce premier élément alors on vide le fichier en écrivant juste un caractère space
		{
			majSize('-'); // mis à jour de la nouvelle taille après avoir rétiré l'élément de la liste
			FILE *fic = fopen("etudiant.data", "w+");
			if(fic == NULL)
				fputc(' ',fic);
			fclose(fic);
			return true;
		}
		remove(file);
		while(li != NULL)
		{
			Ajouter(file, li->etudiant);
			li = li->SUIV;
		}
		majSize('-');
		return true;
	}else
	{
		Etudiant = li;
		temp = li->SUIV;
		while(temp != NULL)
		{
			if(temp->etudiant.numeroCarte == numeroCarte)
			{
				Etudiant->SUIV = temp->SUIV;
				free(temp);
				found = true;
				majSize('-');
				break;
			}
			Etudiant = temp;
			temp = temp->SUIV;
		}
		remove(file);
		while(li != NULL)
		{
			Ajouter(file, li->etudiant);
			li = li->SUIV;
		}
	}
	return found;
	// while(li!= NULL)
	// 	{	strcpy(nom, li->etudiant.nom);
	// 		if(li->etudiant.numeroCarte == numeroCarte)
	// 		{
	// 			printf("%s %s %d %d\n",nom , li->etudiant.prenom, li->etudiant.numeroCarte, li->etudiant.moyenneExamen );
	// 			if(li->SUIV!=NULL)
	// 			{	

	// 				Etudiant = malloc(sizeof(*Etudiant));
	// 				if(Etudiant == NULL)
	// 				{
	// 					fprintf(stderr, "problème d'allocation de la mémoire\n");
	// 					exit(EXIT);
	// 				}

	// 				Etudiant = li->SUIV;
	// 				free(li);
	// 				li = NULL;
	// 				// Reécriture dans le fichier, cette fois en mode w+(retire le précédent et Ajoutere ce qui est là)
	// 					//Suppression de l'ancien fichier 
	// 				remove(file);
	// 				while(Etudiant != NULL)
	// 				{
	// 					Ajouter(file, Etudiant->etudiant);
	// 					Etudiant = Etudiant->SUIV;
	// 				}
	// 				majSize('-');
	// 				return true;
	// 			}
	// 			//Puisqu'il y'a un seul élément dans la liste alors on supprime le fichier contenant la donnée et on en crée un autre
	// 			else if(li->SUIV == NULL)
	// 			{	
	// 				free(li);
	// 				li = NULL;
	// 				majSize('-');
	// 				FILE *fic = fopen("etudiant.data", "w+");
	// 				if(fic == NULL)
	// 					fputc(' ',fic);
	// 				fclose(fic);
	// 				return true;

	// 			}
	// 		}
	// 		li = li->SUIV;
	// 	}

}
// ------------------------------------------------------------------------------------------
// Fonction  pour effectuer le Tri sur la liste
//Ici, on effectue un passage par reférence avec le pointeur qui pointe sur le premier élément de notre liste chainé
void Tri(listEtudiant *firstElement)
{
	Etudiant e;

	//Allocation dynamique pour éviter l'erreur d'acces à une mémoire non reservé
	listEtudiant *temp1 = malloc(sizeof(*temp1)); 
	listEtudiant *temp2 = malloc(sizeof(*temp2));

	for(temp1 = firstElement; temp1 != NULL; temp1 = temp1->SUIV) 
	{
		for(temp2 = temp1->SUIV; temp2 != NULL; temp2 = temp2->SUIV)
		{
			int tester = strcmp(temp1->etudiant.nom, temp2->etudiant.nom);
			if(tester > 0)
			{
				e = temp1->etudiant; //Stocke l'étudiant dans une variable tempon
				temp1->etudiant = temp2->etudiant; //permutation
				temp2->etudiant = e;
			}
		}
	}
	free(temp1);
	free(temp2);
	// List li = getList("etudiant.data");
	// permutation = false;
	// int sizeList = sizeOfList("nb.crypt");
	
	// if(isEmptyList(li) || sizeList == 1) //Si la liste est vide ou si elle contient un seul élément
	// {
	// 	printf("La liste est vide ou contient un seul élément, tri impossible\n");
	// 	return li;
	// }
	// //Créer deux list éléments qui vont pointer vers la liste en question
	// List start = malloc(sizeof(*start));
	// start = li; //temp pointe sur l'élément courant 
	
	// List currentElement = malloc(sizeof(*currentElement));
	// currentElement = start; //temp1 pointe sur l'élément suivant

	// List follower  = malloc(sizeof(*follower)); //Le tampon qui sera l'interface entre les deux pointeurs
	// follower = start->SUIV;


	// //Vider la mémoire alloué avec la fonction malloc
	// free(follower);
	// free(start);
	// //Plus de précuation, on les initialise à NULL
	// currentElement = NULL;
	// follower = NULL;
	// temp = NULL;

	// while(follower!=NULL)
	// {
	// 	int tester = strcmp(currentElement->etudiant.nom, follower->etudiant.nom); //Comparer les differentes données;
	// 	if(tester > 0)//verifie si nôtre test nous donne un chiffre positif alors l'étudiant 1 vient avant l'étudiant suivant
	// 	{
	// 		temp = currentElement; // on stocke  l'élément ou le maillon courant dans la variable temporaire
	// 		currentElement = follower; //L'élement courant pointe maitenant vers l'élément suivant
	// 		follower = temp;
	// 	}
	// 	currentElement = currentElement->SUIV;
	// 	follower = follower->SUIV;
	// }
	// return li;

}
// Fonction permettant d'inverser liste, elle ne fonctionne que si la liste a déja été trié
/*
	Le principe est d'utiliser le une variable temporaire qui va pointer sur l'élement suivant de la liste.
	Ensuite, faire pointer l'élément suivant de la liste vers la nouvelle liste afin de recuperer à chaque instant l'élément précédant.
	Par la suite, faire pointer la nouvelle liste vers l'élement qui précède l'élement suivant de la vraie liste.
	Enfin faire pointer la vraie liste sur son élément suivant
*/
List InverserListe(List li)
{
	List nouvelleList = malloc(sizeof(*nouvelleList));
	List temp;
	while(li != NULL)
	{
		temp = li->SUIV;
		li->SUIV = nouvelleList;
		nouvelleList = li;
		li = temp;
	}
	free(temp); //Liberer la mémoire alloué 
	temp = NULL; //Pointer vers null pour plus de précaution
	return nouvelleList; // retour de la nouvelle liste
}



//Fonction en cours de dévéloppement, elle ne modifie pas la liste en question dans la normal mais affiche les éléments de plus de 12 de moyenne
void PromoFinale(List li)
{
	printf("Nom\t|\t  Prenoms \t |  | Carte Etudiant | \t\tMoyenne \n");

	while(li != NULL)
	{
		if(li->etudiant.moyenneExamen >= 12)
		{			
			printf("\n%s\t\t   %s   \t   %d   \t\t%d\n", li->etudiant.nom,  li->etudiant.prenom,  li->etudiant.numeroCarte, li->etudiant.moyenneExamen );
			li = li->SUIV;
			printf("-------------------------------------------------------------------------------\n");
		}
	}
	printf("\n");
}