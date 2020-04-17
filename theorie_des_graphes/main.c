#include <stdio.h>
#include <stdlib.h>
#define TAILLE_MAX 1000
#define alphabet "abcdefghijklmnopqrstuvwxyz"
#define false 0
#define true 1

typedef int bool; //Les booléens retournent des entiers

typedef struct arc //On d?finit une structure pour les transitions qui sont compos?es de trois ?l?ments
{
    int EtatInitial;
    int valeur;
    int EtatTerminal;

}arc;

typedef arc* tableau_arc; //On définit un tableau qui regroupera les arcs, donc de type arc*

typedef struct graphe //Structure pour les informations du graphe
{
    int nbrDeSommet;
    int nbrDarc;

    tableau_arc tab;
} graphe;

char* recuperer(char* chaine, int nbrDeSommet)
{
    char* recup;
    recup = malloc(nbrDeSommet*sizeof(char));

    int i;
    int j=0;


    for(i=0; i<nbrDeSommet; i++)
    {
        while(chaine[j]!=' ')
        {
            j++;
        }
        recup[i]=chaine[j+1];
        j++;
    }

    recup[nbrDeSommet]='F';



    return recup;
}

graphe lire_graphe_fichier(char* nom_fichier) //Fonction de lecture
{
    int i;
    printf("On ouvre le fichier %s \n", nom_fichier);
    FILE* fichier=NULL;
    char chaine[TAILLE_MAX]= "";

    fichier = fopen(nom_fichier, "r"); //Ouverture du ficher en mode lecture seule

    if (fichier==NULL) //Si le fichier n'existe pas, on ne l'ouvre pas
    {
        printf("Le graphe sélectionné n'existe pas\n");
        exit(EXIT_FAILURE);
    }

    graphe stock; //On définit un graphe pour stocker les informations du fichier texte

    //Récupération des infos du graphe. Utilisation de la fonction atoi pour convertir les caractères du fichier en entiers

    fgets(chaine, TAILLE_MAX, fichier); //Récupération du nombre de sommet puis nombre d'arcs etc
    stock.nbrDeSommet = atoi(chaine);



    fgets(chaine, TAILLE_MAX, fichier);
    stock.nbrDarc = atoi(chaine);


    /*fgets(chaine, TAILLE_MAX, fichier);
    automate.nbrEtatsInitiaux = atoi(chaine);
    automate.EtatInitial = recuperation(chaine, automate.nbrEtatsInitiaux); //Fonction pour r?cup?rer les ?tats initiaux situ?s apr?s le nombre d'?tats initiaux dans le fichier texte


    fgets(chaine, TAILLE_MAX, fichier);
    automate.nbrEtatsTerminaux = atoi(chaine);
    automate.EtatTerminal = recuperation(chaine, automate.nbrEtatsTerminaux); //Fonction pour r?cup?rer les ?tats terminaux situ?s apr?s le nombre d'?tats terminaux dans le fichier texte


    fgets(chaine, TAILLE_MAX, fichier);
    automate.nbrTransitions = atoi(chaine);*/


    //Récupération des arcs via la structure arc

    tableau_arc tab;
    tab = malloc(sizeof(arc)*stock.nbrDarc); //On définit un tableau qui aura autant de cases qu'il y a d'arcs
    arc nouv;

    for(i=0; i<stock.nbrDarc; i++) //On parcourt toutes les transitions
    {
         fgets(chaine,TAILLE_MAX,fichier); //On stocke l'état initial
         nouv.EtatInitial=atoi(chaine);

         fgets(chaine,TAILLE_MAX,fichier); //Puis la valeur
         nouv.valeur=atoi(chaine);


         fgets(chaine,TAILLE_MAX,fichier); //Puis l'état terminal
         nouv.EtatTerminal=atoi(chaine);


       tab[i]=nouv; //On stocke la variable contenant les 3 informations dans une case du tableau
    }

    //Fermeture fichier + retour du graphe avec toutes ses informations

    fclose(fichier);
    stock.tab = tab;
    return stock;

}

//AFFICHAGE DU GRAPHE




void affichage_graphe(graphe stock)
{
    int i;
    printf("Informations du graphe : \n");





            /*printf("Il y a %d arcs dans le graphe : {",stock.nbrDarc);

            for(i=0;i<stock.nbrDarc;i++)
            {
                printf("muni des valeurs %d \n",stock.tab.valeur[i]); //On affiche les symboles de l'alphabet dans l'ordre comme convenu
            }
            printf("%c}\n",alphabet[i]);*/





            printf("Il y a %d sommets ",stock.nbrDeSommet);

            /*for(i=0;i<automate.nbrEtats-1;i++)
            {
                printf("%d,",i); //On affiche les ?tats de l'automate
            }
            printf("%d}\n",i);

            printf("Il y a %d Etat(s) initial(aux) : {",automate.nbrEtatsInitiaux);
            for(i=0;i<automate.nbrEtatsInitiaux-1;i++)
            {
                printf("%c,",automate.EtatInitial[i]); //On affiche ici tous les ?tats initiaux de l'automate
            }
            printf("%c}\n",automate.EtatInitial[i]);

            printf("Il y a %d Etat(s) terminal(aux) : {",automate.nbrEtatsTerminaux);
            for(i=0;i<automate.nbrEtatsTerminaux-1;i++)
            {
                printf("%c,",automate.EtatTerminal[i]); //On affiche ici tous les états terminaux de l'automate
            }
            printf("%c}\n",automate.EtatTerminal[i]);*/
////////////////////////////

            printf("Il y a %d arc(s))\n\n",stock.nbrDarc);


            for(i=0; i<stock.nbrDarc; i++)
                    {
                        printf("%d ", stock.tab[i].EtatInitial); //On va chercher le champ de l'état initial de la case du tableau

                        printf("%d ", stock.tab[i].valeur); //De même pour la valeur

                        printf("%d ", stock.tab[i].EtatTerminal); //Pareil avec l'état terminal


                        printf("\n");
                    }

            printf("\n");


}


int main()
{
    int numgraphe;
    printf("Quel graphe voulez-vous utiliser ? "); //Récupération du numéro du fichier à ouvrir
    scanf("%d", &numgraphe);

    char nomFichier[50];/*="L3-B3-#.txt"*/; //On stocke dans un tableau le nom du fichier texte qui est le m?me pour tous sauf le num?ro symbolis? ici par #
    snprintf(nomFichier, 50, "L3-B3-%d.txt", numgraphe); //On met le num?ro donn? par l'utilisateur ? la place du # et on a le nom complet du fichier ? ouvrir

    graphe courent;
    courent=lire_graphe_fichier(nomFichier);//on lit le graphe
    affichage_graphe(courent);// et on l'affiche

    return 0;
}
