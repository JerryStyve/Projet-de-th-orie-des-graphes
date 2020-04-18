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

    //Récupération des arcs via la structure arc

    tableau_arc tab;
    tab = malloc(sizeof(arc)*stock.nbrDarc); //On définit un tableau qui aura autant de cases qu'il y a d'arcs
    arc nouv;

    for(i=0; i<stock.nbrDarc; i++) //On parcourt toutes les transitions
    {
         fgets(chaine,TAILLE_MAX,fichier); //On stocke l'état initial
         nouv.EtatInitial=atoi(chaine);


         fgets(chaine,TAILLE_MAX,fichier); //Puis l'état terminal
         nouv.EtatTerminal=atoi(chaine);


          fgets(chaine,TAILLE_MAX,fichier); //Puis la valeur
         nouv.valeur=atoi(chaine);

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


            printf("Il y a %d sommets ",stock.nbrDeSommet);


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

int** matrices_d_adjacence(graphe stock)
{

    int i,j,k;
    int** matrice;

    matrice=malloc(sizeof(int*)*stock.nbrDeSommet);

    for(j=0;j<stock.nbrDeSommet;j++){
    matrice[j]=malloc(sizeof(int)*stock.nbrDeSommet);
    }


    for(i=0;i<stock.nbrDeSommet;i++){
        for(j=0; j<stock.nbrDeSommet;j++){
            matrice[i][j]=0;
        }
    }


    for (i=0; i<stock.nbrDarc; i++)
        {

        for(j=0; j<stock.nbrDeSommet;j++)
            {


            if (stock.tab[i].EtatTerminal==j)//verification de l'état d'adjacence effectif entre les sommets courants
                {
                    matrice[stock.tab[i].EtatInitial][j]=1;

                }
        }
        }
            return matrice;

}

void affichage_des_matrices(int** matrice,graphe stock)
{
    int i,j,k;

      for (k=0; k< stock.nbrDeSommet;k++)// boucle de la 1ere ligne affichant les sommets
        {
        printf("  %d",k);
        }
        printf("\n");
        for(i=0;i<stock.nbrDeSommet;i++)
        {
                        printf("%d",i);

            for(j=0;j<stock.nbrDeSommet;j++){
            printf("  %d",matrice[i][j]);
        }
            printf("\n");

        }


}

int main()
{
    int numgraphe;
    int** matrice;

    printf("Quel graphe voulez-vous utiliser ? "); //Récupération du numéro du fichier à ouvrir
    scanf("%d", &numgraphe);

    char nomFichier[50];/*="L3-B3-#.txt"*/; //On stocke dans un tableau le nom du fichier texte qui est le même pour tous sauf le num?ro symbolis? ici par #
    snprintf(nomFichier, 50, "L3-B3-%d.txt", numgraphe); //On met le numéro donné par l'utilisateur à la place du # et on a le nom complet du fichier ? ouvrir

    graphe courent;
    courent=lire_graphe_fichier(nomFichier);//on lit le graphe
    affichage_graphe(courent);// et on l'affiche
    matrice=matrices_d_adjacence(courent);
    affichage_des_matrices(matrice,courent);

    return 0;
}
