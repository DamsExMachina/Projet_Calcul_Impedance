#include <stdio.h>
#include <stdlib.h>
//lire
int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;

    // On lit le texte saisi au clavier
    if (fgets(chaine, longueur, stdin) != NULL)  // Pas d'erreur de saisie ?
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
        if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
        {
            *positionEntree = '\0'; // On remplace ce caractère par \0
        }
        return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
    }
    else
    {
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}

long lireLong()
{
    char nombreTexte[100] = {0}; // 100 cases devraient suffire

    if (lire(nombreTexte, 100))
    {
        // Si lecture du texte ok, convertir le nombre en long et le retourner
        return strtol(nombreTexte, NULL, 10);
    }
    else
    {
        // Si problème de lecture, renvoyer 0
        return 0;
    }
}

//I-b demande les valeurs des composants du circuit
void valeurComposant(int numeroCircuit, double*R, double*L, double*C)
{
    switch (numeroCircuit)
    {
    case(1):
        printf("Renseignez la valeur de R:\n");
        //scanf("%lf",R);
        lireLong();
      // *R= lireLong();
        printf("Renseignez la valeur de L:\n");
        lireLong();
      // *L= lireLong();
       // scanf("%lf",L);
        printf("Voici les valeurs de R et L : %lf, %lf", *R, *L);
        break;
    case(3):
        printf("Renseignez la valeur de R:\n");
       // scanf("%lf,%lf",R,L);
        printf("Renseignez la valeur de C:\n");
       // scanf("%lf",C);
        printf("Voici les valeurs de R et C : %lf, %lf", *R, *C);
        break;

    case(5):
        printf("Renseignez la valeur de C:\n");
      //  scanf("%lf",C);
        printf("Renseignez la valeur de L:\n");
      //  scanf("%lf",L);
        printf("Voici les valeurs de L et C : %lf, %lf", *L, *C);
        break;
    default:
        printf("Veuillez Recommencer\n");



    }

}








int main()
{
    double *R=0, *L=0, *C=0;
    valeurComposant(1, R,L,C);
    //printf("Voici les valeurs de R, L et C : %lf, %lf, %lf", *R, *L, *C);


    return 0;
}
