#include <stdio.h>
#include <stdlib.h>



//I-b demande les valeurs des composants du circuit
void valeurComposant(int numeroCircuit, double*R, double*L, double*C)
{
    switch (numeroCircuit)
    {
    case(1):
    case(2):
        printf("Renseignez la valeur de R:\n");
        scanf("%lf",R);
        printf("Renseignez la valeur de L:\n");
        scanf("%lf",L);
        printf("Voici les valeurs de R et L : %lf, %lf\n", *R, *L);
        break;
    case(3):
    case(4):
        printf("Renseignez la valeur de R:\n");
        scanf("%lf",R);
        printf("Renseignez la valeur de C:\n");
        scanf("%lf",C);
        printf("Voici les valeurs de R et C : %lf, %lf\n", *R, *C);
        break;

    case(5):
    case(6):
        printf("Renseignez la valeur de C:\n");
        scanf("%lf",C);
        printf("Renseignez la valeur de L:\n");
        scanf("%lf",L);
        printf("Voici les valeurs de L et C : %lf, %lf\n", *L, *C);
        break;
    default:
        printf("Veuillez Recommencer\n");



    }

}
int choix_circuit()
{
    printf("Veuillez indiquer le numero du circuit pour lequel vous voulez calculer l'impedance\n");
    printf("RL serie : 1\n");
    printf("RL //    : 2\n");
    printf("RC serie : 3\n");
    printf("RC //    : 4\n");
    printf("LC serie : 5\n");
    printf("LC //    : 6\n");
    int nbCircuit=0;
    scanf("%d",&nbCircuit);
    return nbCircuit;

}








int main()
{
    //test valeur RLC
    double R=0, L=0, C=0;
    int numCircuit = choix_circuit();
    valeurComposant(numCircuit, &R,&L,&C);






    return 0;
}
