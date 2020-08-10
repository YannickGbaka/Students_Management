#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listEtudiant.h"
#include "etudiant.h"


//Menu d'affichage 
//Pour plus d'infos veuillez acceder au fichier listEtudiant qui presente la documentation complète des ces fonctions
void Menu(void)
{
		printf("**********************************************************\n");
		printf("1- \tAFFICHER LA LISTE DES ETUDIANTS\n");
		printf("2- \tTRIER LA LISTE \n");
		printf("3- \tINVERSER LA LISTE\n");
		printf("4- \tAJOUTER UN ETUDIANT\n");
		printf("5- \tSUPPRIMER UN ETUDIANT\n");
		printf("6- \tLISTE DE LA PROMO FINALE\n");
		printf("7- \tCONSULTER LE NOMBRE D'ETUDIANT DANS LA LISTE\n");
		printf("0- \tQUITTER L'APPLICATION\n");
		printf("**********************************************************\n");
		printf("Choix : \n");
}

int main(void)
{

	#define FILE "etudiant.data"
	Bool quit = false;
	int choix = 0;
	char nom[25];
	char prenom[100];
	int numero = 0;
	int moyenne  = 0;
	List li = initialList();
	Etudiant e;
	Bool res = false; // La variable boolean qui va nous aider dans la véracité de nos statements

do{
		printf("\t\tGESTION DES ETUDIANT\n\n");
		Menu();
		scanf("%d", &choix);
		switch(choix)
		{
			case 1 : //Affichage de la liste
				printList(FILE);
			break;

			case 2: //Tri de la liste ainsi que l'affichage
				
				li = getList(FILE);
				Tri(li);
				dispList(li);
			break;

			case 3: //Inversion de la liste

				li = getList(FILE);
				Tri(li);
				li = InverserListe(li);
				List temp = malloc(sizeof(*temp)); 
				temp = li;
				printf("Nom\t|\t  Prenoms \t |  | Carte Etudiant | \t\tMoyenne \n");
				while(!isEmptyList(temp->SUIV))
				{
					printf("\n%s\t\t   %s   \t   %d   \t\t%d\n", temp->etudiant.nom,  temp->etudiant.prenom,  temp->etudiant.numeroCarte, temp->etudiant.moyenneExamen );
					temp = temp->SUIV;
					printf("-------------------------------------------------------------------------------\n");
				}
				printf("\n");
				free(temp);
			break;

			case 4:
				printf("Entrez les informations sur l'etudiant\n");
				
				printf("Nom : \n");
				scanf("%s", nom);
				
				printf("Prenoms[sans espace svp] : (remplacez l'espace par un  _  ) \n");
				scanf("%s", prenom);
				
				printf("Numero de la carte : \n");
				scanf("%d" ,&numero);
				
				printf("La moyenne : \n");
				scanf("%d", &moyenne);
				
				strcpy(e.nom, nom);
				strcpy(e.prenom, prenom);
				
				e.numeroCarte = numero;
				e.moyenneExamen = moyenne;

				li = addElement(li, e);
				res = Ajouter(FILE, e);
				if(res)
				{
					majSize('+');
					printf("Donnée Ajouté avec success\n");

				}else{
					printf("Non ajouté\n");
				}
			break;

			case 5:
				printList(FILE);
				int cardNumber = 0;

				printf("Entrez le numero de la carte de l'etudiant à supprimer : \n");
				scanf("%d", &cardNumber);

				res = Supprimer(FILE, cardNumber);

				if(res)
					printf(" [ Etudiant supprimé avec succès ]\n");
				else
					printf("L'élément n'appartient pas à la liste\n");
			break;

			case 6:
				printf("LISTE DES ADMIS : \n");
				li = getList(FILE);
				if(isEmptyList(li))
					printf("Liste vide !\n\n");
				else
					PromoFinale(li);
				break;

			case 7:
				printf(" la liste compte exactement : %d Etudiant(s)\n\n", sizeOfList("nb.crypt") );
				break;
			case 0:
				printf("à bientôt ...\n");
				quit = true;
				break;
			default:
				printf("Erreur, touche invalide\n");
				break;
		}

	}while(quit == false);
	
	return 0;
}

	/* 

		Ces commentaires sont des test qui m'ont permit de me retrouver lors de la contruction du programme principal
	
	*/

	// printList("etudiant.data");
	// Etudiant e = { "BABO" ,"IBRAHIM", 3001, 16 };

	// List li = initialList();
	// li = getList("etudiant.data");
	// Tri(li);
	// listEtudiant *temp = li; 
	// while(temp != NULL)
	// 	{
	// 		printf("%s\n", temp->etudiant.nom );
	// 		temp = temp->SUIV;
	// 	}
	// printf("\n+++++++++++++++++++++++++++++++++++\n");
	// li = InverserListe(li);
	// temp = li; 
	// while(temp->SUIV != NULL)
	// 	{
	// 		printf("%s | %s \n", temp->etudiant.nom, temp->etudiant.prenom );
	// 		temp = temp->SUIV;
	// 	}
	// printf("\n+++++++++++++++++++++++++++++++++++\n");

	// PromoFinale(li);
	// while(li!= NULL)
	// 	{
	// 		printf("%s | %s \n", li->etudiant.nom, li->etudiant.prenom );
	// 		li = li->SUIV;
	// 	}
	// printf("\n+++++++++++++++++++++++++++++++++++\n");
	

	// Bool res = Ajouter("etudiant.data", e);
	// if(res){
	// 	majSize('+');
	// 	printf("Donnée Ajouteré avec success\n");
	// 	printList("etudiant.data");
	// }
	// printf("%s p\n",li->etudiant.nom);
	// li = li->SUIV;
	// printf("%s p\n",li->etudiant.nom);
	// if(isEmptyList(li)){
	// 	printf("vide\n");
	// }else{
	// 	printf("non vide\n");
	// }
	// List li = initialList();
	// li = addElement(li, e);
	// Bool res = Ajouter("etudiant.data", e);
	// if(res){
	// 	majSize('+');
	// 	printf("Donnée Ajouteré avec success\n");
	// 	printList("etudiant.data");
	// }
	// else
	// 	printf("non Ajouteré\n");
	// Bool res = Supprimer("etudiant.data", 2706);
	// if(res)
	// {
	// 	printf("Supprimé avec success\n");
	// 	printList("etudiant.data");
	// }else{
	// 	printf("L'élément n'existe pas\n");
	// }
	// printf("++++================================\n");
	// res = Supprimer("etudiant.data", 14);
	// printList("etudiant.data");