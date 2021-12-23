#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

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
    printf("Veuillez indiquer le numero du circuit pour lequel vous voulez calculer l'impedance \n");
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


//lire

//I-b demande les valeurs des composants du circuit


double *choixFrequences (int* nbFreq){
    double f_min, f_max, pas_freq;
    double *t_freq = NULL;
    printf("Pour combien de frequences voulez vous calculer l'impedance ? \n");
    scanf("%d",nbFreq);
    printf("Quelle est votre frequence minimale ?\n");
    if(*nbFreq==1){
        scanf("%lf", &f_min);
        // printf("La frequence minimale est : %lf \n",f_min);
        t_freq = malloc(*nbFreq*sizeof(double));
        t_freq[0]=f_min;
        return t_freq;
    }
    else {
        scanf("%lf", &f_min);
        // printf("La frequence minimale est : %lf \n",f_min);
        printf("Quelle est votre frequence maximale ? \n");
        scanf("%lf", &f_max);
        // printf("La frequence maximale est : %lf \n", f_max);
        pas_freq = (f_max-f_min)/(*nbFreq-1);
        // printf("Le pas est : %lf \n",pas_freq);
        // printf("Le nombre d'octets du tableau est : %d \n",sizeof(double)*(*nbFreq));
        t_freq = malloc(sizeof(double)*(*nbFreq));
        if(t_freq==NULL)
            exit(0);

        for(int i=0; i<*nbFreq; i++){
            t_freq[i]=f_min+(pas_freq*i);
            // printf("La frequence %lf est : %lf \n", i, t_freq[i]);
        }
    }    
    
    return t_freq;
}

void calculImpedance(double **pt_module_tab , double **pt_phase_tab , double *tab_freq , int choixCircuit , int nbfreq , double R , double L , double C)
{
    double* module_tab;
    double* phase_tab;
    module_tab = malloc(nbfreq*sizeof(double));
    phase_tab = malloc(nbfreq*sizeof(double));
    if(module_tab==NULL || phase_tab==NULL)
        exit(0);

    // for(int i=0; i<2; i++){
    //     *pt_module_tab[i] = i*3;
    // }
    int nbCalc = 0;
    for(int i = 0 ; i<nbfreq; i++)
    {
        switch (choixCircuit)
        {
        case (1):
            break;
        case(2):
            module_tab[i] = (R*L*2*PI*tab_freq[i])/sqrt(pow(R,2)+pow(L*2*PI*tab_freq[i],2));
            phase_tab[i] = PI/2-atan(L*2*PI*tab_freq[i]/R);
            break;
        case(3):
            break;
        case(4):
            module_tab[i] = (R/(2*PI*C*tab_freq[i]))/sqrt(pow(R,2)+pow(1/(C*2*PI*tab_freq[i]),2));
            phase_tab[i] = -PI/2-atan(-1/R*C*2*PI*tab_freq[i]);
            break;
        case(5):
            break;
        case(6):
            module_tab[i] = (L/C)/sqrt(pow(L*2*PI*tab_freq[i]-1/(C*2*PI*tab_freq[i]),2));
            if(L*C!=1/2*PI*tab_freq[i]){
                phase_tab[i] = PI/2;
            }
            break;
        default :
            break;
        }
    }
    *pt_module_tab = module_tab;
    *pt_phase_tab = phase_tab;
}


int main()
{
    //test valeur RLC
    double R=0, L=0, C=0;
    int numCircuit = choix_circuit();
    valeurComposant(numCircuit, &R,&L,&C);

    double *t_freq = NULL;
    int nb_freq;

    t_freq = choixFrequences(&nb_freq);

    // for (int i = 0; i <nb_freq; i++)
    // {
    //     printf("La frequence n°%lf est : \n", i, t_freq[i]);
    // }

    double *module_tab = NULL;
    double *phase_tab = NULL;


    calculImpedance(&module_tab, &phase_tab, t_freq, numCircuit, nb_freq, R, L, C);


    for (int i = 0; i <nb_freq; i++)
    {
        printf("Le module de l'impedance pour la frequence %lf Hz est %lf ohms et la phase %lf rads \n", t_freq[i], module_tab[i], phase_tab[i]);
        printf("\n");
    }    

    free(module_tab);
    free(t_freq);
    free(phase_tab);

    return 0;
}
