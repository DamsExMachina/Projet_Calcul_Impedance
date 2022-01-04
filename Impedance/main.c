#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846 //On crée une constante avec la valeur de PI

void valeurComposant(int numeroCircuit, double*R, double*L, double*C)
{
    switch (numeroCircuit)
    {
    case(1):
    case(2):
        printf("Renseignez la valeur de R en Ohm:\n");
        scanf("%lf",R);
        printf("Renseignez la valeur de L en H:\n");
        scanf("%lf",L);
        printf("Voici les valeurs de R et L : %lf Ohm, %lf H \n", *R, *L);
        break;
    case(3):
    case(4):
        printf("Renseignez la valeur de R en Ohms:\n");
        scanf("%lf",R);
        printf("Renseignez la valeur de C en F:\n");
        scanf("%lf",C);
        printf("Voici les valeurs de R et C : %lf Ohm, %lf F\n", *R, *C);
        break;

    case(5):
    case(6):
        printf("Renseignez la valeur de C en F:\n");
        scanf("%lf",C);
        printf("Renseignez la valeur de L en H:\n");
        scanf("%lf",L);
        printf("Voici les valeurs de L et C : %lf H, %lf F\n", *L, *C);
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

double *choixFrequences (int* nbFreq)
{
    double f_min, f_max, pas_freq; 
    double *t_freq = NULL;
    int type_pas;
    printf("Pour combien de frequences voulez vous calculer l'impedance ? \n");
    scanf("%d",nbFreq);
    if(*nbFreq==1){ //Lorsqu'il n'y a qu'une seule fréquence on ne demande que f_min
        printf("Quelle est votre frequence minimale ?\n");
        scanf("%lf", &f_min);
        // printf("La frequence minimale est : %lf \n",f_min);
        t_freq = malloc(*nbFreq*sizeof(double));
        t_freq[0]=f_min;
        return t_freq;
    }
    else {
        printf("Quelle type de pas souhaitez vous avoir ?\n1 : Lineaire\n2 : Logarithmique\n");
        scanf("%d", &type_pas);
        printf("Quelle est votre frequence minimale ?\n");
        scanf("%lf", &f_min);
        printf("Quelle est votre frequence maximale ? \n");
        scanf("%lf", &f_max);

        t_freq = malloc(sizeof(double)*(*nbFreq)); // On fait une allocation dynamique pour un tableau de nbFreq valeurs de type double
        if(t_freq==NULL) // On vérifie que l'allocation s'est bien déroulée
            exit(0);

        if (type_pas==1){ //En fonction du type de pas on a une formule différente pour la création du tableau de fréquence
            pas_freq = (f_max-f_min)/(*nbFreq-1); 
            for(int i=0; i<*nbFreq; i++){
                t_freq[i]=f_min+(pas_freq*i); //Pour un pas linéaire on incrémente du pas constant
            }
        }
        else if(type_pas==2){
            pas_freq = f_max/f_min;
            for(int i=0; i<*nbFreq; i++){
                t_freq[i]=f_min*pow(pas_freq, (double)i/(*nbFreq-1)); // Pour un pas logarithminque on multiplie par une puissance incrémenté d'un pas constant
            }
        }
    }    
    return t_freq;
}

void calculImpedance(double **pt_module_tab , double **pt_phase_tab , double *tab_freq , int choixCircuit , int nbfreq , double R , double L , double C)
{
    // On prend en entrée les pointeurs des tableaux qui contiendrons les valeurs d'impédance dans le main

    double* module_tab; // On crée les pointeurs des tableau qui contiendront les valeurs des modules et phases dans cette méthode
    double* phase_tab;
    module_tab = malloc(nbfreq*sizeof(double));
    phase_tab = malloc(nbfreq*sizeof(double));
    if(module_tab==NULL || phase_tab==NULL)
        exit(0);

    for(int i = 0 ; i<nbfreq; i++)
    {
        switch (choixCircuit) // En fonction du circuit choisi par l'utilisateur on a un calcul d'impédence différent
        {
        case (1):
            module_tab[i] = sqrt(pow(R,2)+pow(L*2*PI*tab_freq[i],2));
            phase_tab[i] = atan((L*2*M_PI*tab_freq[i])/R);
            break;
        case(2):
            module_tab[i] = (R*L*2*PI*tab_freq[i])/sqrt(pow(R,2)+pow(L*2*PI*tab_freq[i],2));
            phase_tab[i] = PI/2-atan(L*2*PI*tab_freq[i]/R);
            break;
        case(3):
            module_tab[i] = sqrt(pow(R,2)+pow(1/(C*2*M_PI*tab_freq[i]),2));
            phase_tab[i] = atan(-1/(C*2*M_PI*tab_freq[i])/R);
            break;
        case(4):
            module_tab[i] = (R/(2*PI*C*tab_freq[i]))/sqrt(pow(R,2)+pow(1/(C*2*PI*tab_freq[i]),2));
            phase_tab[i] = -PI/2-atan(-1/R*C*2*PI*tab_freq[i]);
            break;
        case(5):
            module_tab[i] = sqrt(pow((L*2*M_PI*tab_freq[i])-1/(C*2*M_PI*tab_freq[i]),2));
            if(L*C*pow(2*PI*tab_freq[i],2)<1){
                phase_tab[i]=-PI/2;
            }
            else if(L*C*pow(2*PI*tab_freq[i],2)>1){
                phase_tab[i] = PI/2;
            }
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
    *pt_module_tab = module_tab; // On fait assigner aux pointeurs, vers lesquels redirigent les pointeurs en entrée, les adresses où l'on a les valeurs calculées 
    *pt_phase_tab = phase_tab;
}


void creationFichier(int nbFreq ,double* frequence_tab, double* module_tab, double* phase_tab)
{
    FILE* fichierDonnees = NULL;
    fichierDonnees = fopen("Impedance.dat", "w+"); // On ouvre le fichier en w+ pour effacer toutes les données issues d'une exécution précédente du programme
    if (fichierDonnees != NULL)
    {
        for(int i=0; i<nbFreq; i++){
            fprintf(fichierDonnees, "%lf %lf %lf\n", frequence_tab[i], module_tab[i], phase_tab[i]); // On écrit dans le fichier ligne par ligne
        }
        fclose(fichierDonnees);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier Impedance.dat");
    }

}

void afficheResulat(int nbFreq ,double* frequence_tab, double* module_tab, double* phase_tab)
{
    printf("Quel type d'affichage souhaitez vous?\n");
    printf("Affichage sous forme de liste :             1\n");
    printf("Affichage sous forme de diagramme de Bode : 2\n");
    int choixAffichage=0;
    scanf("%d", &choixAffichage);
    if (choixAffichage==2)
    {   
        system("gnuplot graph.p");
    }
    else if(choixAffichage==1)
    {
        for (int i = 0; i <nbFreq; i++)
            {
                printf("Le module de l'impedance pour la frequence %lf Hz est %lf ohms et la phase %lf rads. \n", frequence_tab[i], module_tab[i], phase_tab[i]);
            }
    }
}

int main()
{
    //test valeur RLC
    double R=0, L=0, C=0;
    int numCircuit = choix_circuit();
    valeurComposant(numCircuit, &R,&L,&C);

    double *t_freq;
    int nb_freq;

    t_freq = choixFrequences(&nb_freq);

    double *module_tab = NULL;
    double *phase_tab = NULL;

    calculImpedance(&module_tab, &phase_tab, t_freq, numCircuit, nb_freq, R, L, C);

    creationFichier(nb_freq, t_freq, module_tab, phase_tab);

    afficheResulat(nb_freq, t_freq, module_tab, phase_tab);

    free(module_tab);
    free(t_freq);
    free(phase_tab);

    return 0;
}
