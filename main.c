#include <stdio.h>
#include <stdlib.h>

//I-b demande les valeurs des composants du circuit
void valeurComposant(int numeroCircuit, double*R, double*L, double*C)
{
    switch (numeroCircuit)
    {
    case(1||2):
        printf("Renseignez la valeur de R");
        scanf("%d",R);
        printf("Renseignez la valeur de L");
        scanf("%d",L);
        break;
    case(3||4):
        printf("Renseignez la valeur de R");
        scanf("%d",R);
        printf("Renseignez la valeur de C");
        scanf("%d",C);
        break;

    case(5||6):
        printf("Renseignez la valeur de C");
        scanf("%d",C);
        printf("Renseignez la valeur de L");
        scanf("%d",L);
        break;
    default:
        printf("Veuillez Recommencer");



    }

}








int main()
{
    int *R, *L, *C;
    valeurComposant(3, R,L,C);
    printf("Voici les valeurs de R, L et C : %d, %d, %d", R, L, C);


    return 0;
}
