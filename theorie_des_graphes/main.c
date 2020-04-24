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
//calcul de la matrice  d'adjacence

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

// matrice des valeurs



//calcul des rangs

int* calcul_des_rangs(int** matrice, graphe stock) {

     int* rang;
     int* tampon;
     int i,j,k,l,n,z,t;
     int m=0;

    rang=malloc(sizeof(int)*stock.nbrDeSommet);
    tampon=malloc(sizeof(int)*stock.nbrDeSommet);


    for (n=0; n<stock.nbrDeSommet;n++){//initialisation du tableau des rangs à -1
        rang[n]=-1;
    }
for(z=0;z<stock.nbrDeSommet;z++){

for (n=0; n<stock.nbrDeSommet;n++){//initialisation du tableau tampon à 0
        tampon[n]=0;}

for(j=0;j<stock.nbrDeSommet;j++){//on fait la somme de chaque colonne pour ensuite vérifier celle qui sont nulle
    for(i=0;i<stock.nbrDeSommet;i++){
        tampon[j]=tampon[j] + matrice[i][j];
    }
}

for(k=0;k<stock.nbrDeSommet;k++){
    if(tampon[k]==0){//vérification !
        for(l=0;l<stock.nbrDeSommet;l++){
            matrice[k][l]=0;
        }
        if (rang[k]==-1){//attribution du rang si la somme sur les colonnes de la colonne de la matrice d'adjacence du sommet est nulle.
            rang[k]=m;
            m++;
        }
    }
}
}

return rang;

}

//affichage des rangs

void affich_rang(int* rang, graphe stock){
    int p,r;
    printf("\n le tableau des rangs est : \n");
    for(r=0;r<stock.nbrDeSommet;r++){
        printf("%d ",r);
    }
    printf("\n");
for(p=0; p<stock.nbrDeSommet; p++){
    printf("%d ", rang[p]);
}
}

//affichage des matrices
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
    int* tab_rang;

    printf("Quel graphe voulez-vous utiliser ? "); //Récupération du numéro du fichier à ouvrir
    scanf("%d", &numgraphe);

    char nomFichier[50];/*="L3-B3-#.txt"*/; //On stocke dans un tableau le nom du fichier texte qui est le même pour tous sauf le num?ro symbolis? ici par #
    snprintf(nomFichier, 50, "L3-B3-%d.txt", numgraphe); //On met le numéro donné par l'utilisateur à la place du # et on a le nom complet du fichier ? ouvrir

    graphe courent;
    courent=lire_graphe_fichier(nomFichier);//on lit le graphe
    affichage_graphe(courent);// et on l'affiche
    matrice=matrices_d_adjacence(courent);
    affichage_des_matrices(matrice,courent);
    tab_rang=calcul_des_rangs(matrice,courent);
    affich_rang(tab_rang,courent);

    return 0;
}
