/****************************************************************
Author: Chenghao WANG
Contact: chenghao.wang@hds.utc.fr
Institute: Heudiasyc, université de technologie de compiègne
Date: 12/10/2020
*****************************************************************/
#include "../include/TP3.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <limits.h>

/**
 * @brief Ajout d’un soigneur, où la liste des intervalles de temps disponibles pour un nouveau soigneur
 * est initialisée avec un seul intervalle [0, inf[.
 * @param listeSoigneurs une liste de soigneurs laquelle ne doit pas être vide.
 * @param idSoi un identifiant d'un soigneur.
 * @param nom le nom d'un sogineur.
 * @param prenom le prénom d'un soigneur.
 */
T_Soigneur* ajouterSoigneur(T_Soigneur* listeSoigneurs, Index_Soigneur idSoi, char* nom, char* prenom){
    T_Soigneur *nouvSoigneur=malloc(sizeof(T_Soigneur));
    T_Intervalle *listeIntervalle=malloc(sizeof(T_Intervalle));
    listeIntervalle->debut = 0;
    listeIntervalle->fin = INT_MAX;
    listeIntervalle->suivant = NULL;

    nouvSoigneur->id_soi=idSoi;
    nouvSoigneur->nom = malloc(sizeof(char)*40);
    nouvSoigneur->prenom = malloc(sizeof(char)*40);
    strcpy(nouvSoigneur->nom, nom);
    strcpy(nouvSoigneur->prenom, prenom);
    nouvSoigneur->listeIntervalle=listeIntervalle;

    nouvSoigneur->suivant=listeSoigneurs;
    return  nouvSoigneur;

    //return provided_ajouterSoigneur(listeSoigneurs, idSoi, nom, prenom);
}
/**
 * @brief Ajout d'un patient, où la liste de rendez-vous médicaux pour un nouveau patient est initialement vide.
 * @param listePatients une liste de patients laquelle ne doit pas être vide.
 * @param idPat un identifiant d'un patient.
 * @param nom le nom d'un patient.
 * @param prenom le prénom d'un patient.
 */
T_Patient* ajouterPatient(T_Patient* listePatients, Index_Patient idPat, char* nom, char* prenom){
    T_Patient *nouvPatient=malloc(sizeof(T_Patient));

    nouvPatient->id_pat=idPat;
    nouvPatient->nom = malloc(sizeof(char)*40);
    nouvPatient->prenom = malloc(sizeof(char)*40);
    strcpy(nouvPatient->nom, nom);
    strcpy(nouvPatient->prenom, prenom);
    nouvPatient->listeRendezVous = NULL;

    nouvPatient->suivant=listePatients;
    return  nouvPatient;
    //return provided_ajouterPatient(listePatients, idPat, nom, prenom);
}
/**
 * @brief Ajout d’un rendez-vous médical pour un patient.
 * @param listeRdV une liste de Rendezvous laquelle ne doit pas être vide.
 * @param idSoi un identifiant d'un soigneur associé.
 * @param dateDebutSouhaitee  la date de début souhaitée d'un RdV.
 * @param dateFinSouhaitee  la date de fin souhaitée d'un RdV.
 * @param tempsDeplacement la temps de déplacement depuis un RdV précédent.
 * @param desc une discription brève.
 */
T_RendezVous* ajouterRendezVous(T_RendezVous* listeRdV, Index_Soigneur idSoi, Time dateDebutSouhaitee, Time dateFinSouhaitee, Time tempsDeplacement, char* desc){
    //return provided_ajouterRendezVous(listeRdV, idSoi, dateDebutSouhaitee, dateFinSouhaitee, tempsDeplacement, desc);
    T_RendezVous* nouvRendezVous=malloc(sizeof(T_RendezVous));

    nouvRendezVous->id_soi=idSoi;
    nouvRendezVous->debut_souhaitee=dateDebutSouhaitee;
    nouvRendezVous->fin_souhaitee=dateFinSouhaitee;
    nouvRendezVous->debut_affectee=0;
    nouvRendezVous->fin_affectee=0;
    nouvRendezVous->temps_deplacement=tempsDeplacement;
    nouvRendezVous->desc = malloc(sizeof(char)*125);
    strcpy(nouvRendezVous->desc, desc);

    nouvRendezVous->suivant=listeRdV;
    return  nouvRendezVous;
}

/**
 * @brief Modification d’ un rendez-vous médical pour un patient par une date, le temps de déplacement ou une description nouvelle :
 * @param listeRdV une liste de Rendezvous laquelle ne doit pas être vide.
 * @param idSoi un identifiant d'un soigneur associé.
 * @param dateDebutSouhaitee la date de début souhaitée d'un RdV.
 * @param dateFinSouhaitee la date de fin souhaitée d'un RdV.
 * @param tempsDeplacement la temps de déplacement depuis un RdV précédent.
 * @param desc une discription brève.
 */
void modifierRendezVous(T_RendezVous* listeRdV, Index_Soigneur idSoi, Time dateDebutSouhaitee, Time dateFinSouhaitee, Time tempsDeplacement, char* desc){
    //return provided_modifierRendezVous(listeRdV, idSoi, dateDebutSouhaitee, dateFinSouhaitee, tempsDeplacement, desc);
    T_RendezVous* r = listeRdV;
    int trouve = 0;

    while (trouve==0) {
        if (r->id_soi == idSoi) {
            trouve = 1;
        }
        else r = r->suivant;
    }
    if (trouve==0) return;

    r->debut_souhaitee = dateDebutSouhaitee;
    r->fin_souhaitee = dateFinSouhaitee;
    r->temps_deplacement = tempsDeplacement;
    strcpy(r->desc, desc);
    return;
}
/**
 * @brief Suppression d’un rendez-vous médical pour un patient en donnant l’identifiant du soigneur correspondant.
 * Si un rendez-vous, ni premier ni dernier, est enlevé, le temps de déplacement du traitement suivant doit être mis à jour.
 * Par exemple, un patient ayant trois rendez-vous : rendez-vous 1 chez le soigneur A,
 * rendez-vous 2 chez le soigneur B et rendez-vous 3 chez le soigneur C, temps de déplacement de 1 à 2 de 30 mn,
 * temps de déplacement de 2 à 3 de 40 mn, le temps de déplacement de 1 à 3 est défini
 * par sqrt(30^2+40^2)=50mn quand le rendez-vous 2 est supprimé.
 * @param listeRdV une liste de RdV.
 * @param idSoi identifiant d'un soigneur.
 * @return un pointeur vers la tête de la liste de RdV médicaux après une suppression.
 */
T_RendezVous* supprimerRendezVous(T_RendezVous* listeRdV, Index_Soigneur idSoi){
    //return provided_supprimerRendezVous(listeRdV, idSoi);
    T_RendezVous* r = listeRdV;
    int trouve = 0;

    while (r->suivant != NULL) {
        if (r->suivant->id_soi == idSoi) {
            trouve = 1;
            break;
        }
        if (r->suivant->suivant == NULL) break;
        r = r->suivant;
    }
    if (trouve) {
        T_RendezVous* aSupprimer = r->suivant;
        r->suivant = aSupprimer->suivant;
        r->temps_deplacement = sqrt(pow(r->temps_deplacement, 2)+pow(aSupprimer->temps_deplacement, 2));
        free(aSupprimer);
    }

    return listeRdV;
}

/**
 * @brief Afficher tous les soigneurs et leurs intervalles de temps disponibles
 * @param listeSoigneurs une liste de soigneurs.
 */
void affichage_Soigneurs(T_Soigneur* listeSoigneurs){
    //return provided_affichage_Soigneurs(listeSoigneurs);

    if(listeSoigneurs==NULL) printf("Aucun soigneur\n");
    else
    {
        printf("Les informations de soigneurs sont:\n");
        T_Soigneur* s=listeSoigneurs;
        T_Intervalle* i;
        while(s!=NULL)
        {
            i=s->listeIntervalle;
            printf("Id:%d, Nom:%s, Prenom:%s, Intervalles de temps disponible:\n",s->id_soi,s->nom,s->prenom);
            while (i != NULL) {
                printf("[%d, %d[\n",i->debut,i->fin);
                i = i->suivant;
            }
            s=s->suivant;
        }
    }
}

/**
 * @brief Afficher tous les patients et leurs rendez-vous
 * @param listePatients une liste de patients.
 */
void affichage_Patients(T_Patient* listePatients){
    //return provided_affichage_Patients(listePatients);

    if(listePatients==NULL) printf("Aucun patient\n");
    else
    {
        printf("Les informations de patients sont:\n");
        T_Patient* p=listePatients;
        T_RendezVous* r;
        while(p!=NULL)
        {
            r=p->listeRendezVous;
            printf("Id:%d, Nom:%s, Prenom:%s, ses rdv medicaux:\n",p->id_pat,p->nom,p->prenom);
            affichage_RendezVous(r);
            p=p->suivant;
        }
    }
}

/**
 * @brief Afficher un rendez-vous en indiquant l’identifiant du patient et le soigneur correspondant
 * @param rendezVous un rendez-vous.
 */
void affichage_RendezVous(T_RendezVous *rendezVous){
    //return provided_affichage_un_RendezVous(rendezVous);

    if(rendezVous==NULL) printf("Aucun rdv\n");
    else
    {
        T_RendezVous* r=rendezVous;
        while(r!=NULL)
        {
            affichage_un_RendezVous(r);
            r=r->suivant;
        }
    }
}

void affichage_un_RendezVous(T_RendezVous* r) {
    printf("%s, id_soigneur_associe: %d, temps_deplacement_depuis_rdv_precedent:%d\n",r->desc,r->id_soi,r->temps_deplacement);
    printf("\trdv souhaite: [%d, %d[, rdv affecte: [%d, %d[\n\n",r->debut_souhaitee,r->fin_souhaitee,r->debut_affectee,r->fin_affectee);
}

/**
 * @brief Créer une instance de l’ordonnancement en important à partir d’un fichier.
 * @param filename le nom d'un fichier importé.
 * @return un pointeur vers l’instance.
 */
T_Ordonnancement* creerInstance(char* filename){
    FILE* fptr = fopen(filename, "r");
    T_Ordonnancement* o = malloc(sizeof(T_Ordonnancement));
    o->listePatients = NULL;
    o->listeSoigneurs = NULL;

    if (fptr == NULL) {
        printf("Erreur dans l'ouverture du fichier");
        return NULL;
    }

    unsigned int nbPatients = 0, nbSoigneurs = 0;
    fscanf(fptr, "%u", &nbPatients);
    fscanf(fptr, "%u", &nbSoigneurs);
    printf("Read patients and therapists amount: %d, %d\n\n", nbPatients, nbSoigneurs);

    unsigned int idPat, nbRdV, idSoi, dateDebutSouhaitee, dateFinSouhaitee, tempsDeplacement;
    char* nom = malloc(sizeof(char)*40);
    char* prenom = malloc(sizeof(char)*40);
    char* desc = malloc(sizeof(char)*125);
    printf("[Reading patients info]\n");
    for (int i = 0; i < nbPatients; ++i) {
        fscanf(fptr, "%u", &idPat);
        fscanf(fptr, "%u", &nbRdV);
        fscanf(fptr, "%s", nom);
        fscanf(fptr, "%s", prenom);

        printf("Read patient %d with %d appointments, named %s %s\n", idPat, nbRdV, nom, prenom);
        o->listePatients = ajouterPatient(o->listePatients, idPat, nom, prenom);

        for (int j = 0; j < nbRdV; ++j) {
            fscanf(fptr, "%u", &idSoi);
            fscanf(fptr, "%u", &dateDebutSouhaitee);
            fscanf(fptr, "%u", &dateFinSouhaitee);
            fscanf(fptr, "%u", &tempsDeplacement);
            fscanf(fptr, "%s", desc);

            printf("\tRead appointment with therapist %d (%s): starting %d, ending %d, with %d minutes of travel\n", idSoi, desc, dateDebutSouhaitee, dateFinSouhaitee, tempsDeplacement);
            o->listePatients->listeRendezVous = ajouterRendezVous(o->listePatients->listeRendezVous, idSoi, dateDebutSouhaitee, dateFinSouhaitee, tempsDeplacement, desc);
        }
        printf("\n");
    }

    printf("\n[Reading therapists info]\n");
    for (int i = 0; i < nbSoigneurs; ++i) {
        fscanf(fptr, "%u", &idSoi);
        fscanf(fptr, "%s", nom);
        fscanf(fptr, "%s", prenom);

        o->listeSoigneurs = ajouterSoigneur(o->listeSoigneurs, idSoi, nom, prenom);
        printf("Read therapist %d, named %s %s\n", idSoi, nom, prenom);
    }

    fclose(fptr);
    return o;
}

/**
 * @brief Affectation d’un rendez-vous en fonction des intervalles de temps disponibles d’un soigneur
 * (mettre à jour la date de début affectée et la date de fin affectée du rendez-vous ) 
 * @param rdv un RdV.
 * @param soigneur un soigneur.
 */
void affecterRdV(T_RendezVous* rdv, T_Soigneur* soigneur){
    T_Intervalle* intervalle = soigneur->listeIntervalle;
    T_Intervalle* precedent = NULL;

    rdv->debut_affectee = rdv->debut_souhaitee;
    rdv->fin_affectee = rdv->fin_souhaitee;
    while (
        intervalle != NULL
        && (rdv->debut_affectee < intervalle->debut
        || rdv->fin_affectee > intervalle->fin)
    )
    {
        precedent = intervalle;
        intervalle = intervalle->suivant;

        if (intervalle != NULL) {
            if (rdv->debut_affectee < intervalle->debut) {
                rdv->debut_affectee = intervalle->debut + rdv->temps_deplacement;
                rdv->fin_affectee = rdv->debut_affectee + rdv->fin_souhaitee - rdv->debut_souhaitee;
            }
        }
//        printf("%d\n", rdv->debut_affectee);
    } // Chercher un intervalle où le rendez vous rentre
//    printf("Found\n\n");

    if (intervalle != NULL) {
        rdv->fin_affectee = rdv->debut_affectee + rdv->fin_souhaitee - rdv->debut_souhaitee;
        rdv->id_soi = soigneur->id_soi;

        if (intervalle->debut < rdv->debut_affectee) { // Créer un intervalle avant le rendez vous
            T_Intervalle* nouvIntervalle = malloc(sizeof(T_Intervalle));

            nouvIntervalle->debut = intervalle->debut;
            nouvIntervalle->fin = rdv->debut_affectee;

            nouvIntervalle->suivant = intervalle;
            if (precedent != NULL) {
                precedent->suivant = nouvIntervalle;
            } else {
                soigneur->listeIntervalle = nouvIntervalle;
            }
            precedent = nouvIntervalle;
        }

        intervalle->debut = rdv->fin_affectee; //Modifier l'intervalle pour qu'il ne reste que le temps après le rendez vous
        if (intervalle->debut == intervalle->fin) {
            precedent->suivant = intervalle->suivant;
            free(intervalle);
        }
    } else {
        printf("Aucun intervalle de temps valide trouve pour ce rendez vous:\n");
        affichage_un_RendezVous(rdv);
    }
}

/**
 * @brief Ordonnancer les rendez-vous des patients en fonction des intervalles de temps disponibles
 * pour l’ensemble des soigneurs en minimisant la somme des temps d’attente des patients
 * (le temps d’attente est calculé par la date de début affectée – la date de début souhaitée).
 * L’algorithme glouton d'ordonnancement en minimisant la somme du temps d’attente des patients se construit comme suit :
 * Étape 1 : Trier les patients par ordre décroissant de durée totale des rendez-vous
 *  (la durée d’un rendez-vous est calculée par la date de fin souhaitée – la date de début souhaitée)
 * Étape 2 : Affecter les rendez-vous des patients dans l’ordre ci-dessus aux intervalles de temps disponible des soigneurs.
 * @param solution un instance
 */
void ordonnancer(T_Ordonnancement* solution){
    //return provided_ordonnancer(solution);

    //PARTIE 1
    provided_MergeSort(&(solution->listePatients)); //On utilise la fonction mergeSort offerte

    //PARTIE 2
    T_Soigneur* s=solution->listeSoigneurs;
    T_Patient* p=solution->listePatients;
    T_RendezVous* r;

    while(p!=NULL) //On parcours tt les patients
    {
        r=p->listeRendezVous;
        while(r!=NULL) //On parcours tous les rdv
        {
            while(s->id_soi!=r->id_soi) //On cherche le soigneur responsable du RDV
            {
                s=s->suivant;
            }
            affecterRdV(r,s);

            r=r->suivant;
            s=solution->listeSoigneurs;
        }
        p=p->suivant;
    }

}
/**
 * @brief Exporter la solution d’un ordonnancement.
 * Le nom du fichier exporté a sufix de la date de création  d’un ordonnancement, par exemple filename=’solution.txt’,
 * et la date de creation est ‘2020-10-13’, donc le nom de ficher exporté est ‘solution.txt.2020-10-13.txt’.
 * @param solution une solution d'un ordonnancement.
 * @param filename le nom d'un ficher exporté.
 */
void exportSolution(T_Ordonnancement* solution, char* filename){
    //return provided_exportSolution(solution, filename);
    printf("Getting timestamp\n");
    time_t timestamp;
    time(&timestamp);

    printf("Getting filename\n");
    char dateCourante[256], nomFichier[256];
    strftime(dateCourante, 256, ".%Y-%m-%d.txt", localtime(&timestamp));
    printf("Got formatted timestamp as %s, trying to concat it with %s\n", dateCourante, filename);
    strcpy(nomFichier,filename);
    strcat(nomFichier,dateCourante);

    printf("Opening file %s...\n", nomFichier);
    FILE* fichier = fopen(nomFichier, "w");

    if (fichier != NULL)
    {
        printf("File opened\n");
        unsigned int nbPatients=0, nbSoigneurs=0,nbRdV=0;
        nbPatients=compter_nb_patients(solution->listePatients);
        nbSoigneurs=compter_nb_soigneurs(solution->listeSoigneurs);
        fprintf(fichier, "%u ",nbPatients);
        fprintf(fichier, "%u\n",nbSoigneurs);
        printf("Wrote %d patients and %d therapists\n\n", nbPatients, nbSoigneurs);

        printf("[Writing patients]\n");
        T_Patient* p = solution->listePatients;
        for (int i = 0; i < nbPatients; ++i) {
            nbRdV=compter_nb_RdV(p->listeRendezVous);
            fprintf(fichier, "%u %u\n", p->id_pat,nbRdV);
            printf("Wrote patient %d with %d appointments\n", p->id_pat, nbRdV);

            T_RendezVous* r =p->listeRendezVous;
            for (int j = 0; j < nbRdV; ++j) {
                fprintf(fichier, "%u %u %u %u\n", r->id_soi,r->debut_affectee,r->fin_affectee,r->temps_deplacement);
                printf("\tWrote appointment with therapist %d: starting %d, ending %d, %d travel time\n", r->id_soi,r->debut_affectee,r->fin_affectee,r->temps_deplacement);
                r=r->suivant;
            }
            p=p->suivant;
        }
        fclose(fichier);
    } else {
        printf("Impossible d'écrire dans le fichier %s",nomFichier);
    }

    return ;
}

T_Patient* demanderRecherchePatient(T_Ordonnancement* instance) {
    unsigned int idPat;

    printf("Entrez l'identifiant du patient: ");
    scanf("%d", &idPat);

    T_Patient* patient = instance->listePatients;
    while (patient != NULL && patient->id_pat != idPat) {
        patient = patient->suivant;
    }

    if (patient == NULL) {
        printf("Aucun patient n'a été trouvé avec cet identifiant.");
    }

    return patient;
}

T_RendezVous* demanderRechercheRendezVous(T_Patient* patient) {
    unsigned int idSoi;

    printf("Entrez l'identifiant du soigneur: ");
    scanf("%d", &idSoi);

    T_RendezVous* rdv = patient->listeRendezVous;
    while (rdv != NULL && rdv->id_soi != idSoi) {
        rdv = rdv->suivant;
    }

    if (rdv == NULL) {
        printf("Aucun rendez vous avec le soigneur avec cet identifiant n'a ete trouvé.");
    }

    return rdv;
}

/**
 * @brief un menu principal pour le programme.
 */
void menuPrincipal(void){
//    printf("hello world\n");
    // return provided_menu();

    T_Ordonnancement* instance = NULL;

    int choix = 0;
    while (choix != 9) {
        system("cls");
        printf("1 Creer une instance a partir d un fichier\n");
        printf("2 Afficher tous les patients et leurs rendez-vous\n");
        printf("3 Afficher tous les soigneurs et leurs intervalles de temps disponibles\n");
        printf("4 Afficher un rendez-vous\n");
        printf("5 Modifier un rendez-vous\n");
        printf("6 Supprimer un rendez-vous\n");
        printf("7 Ordonnancer l'instance\n");
        printf("8 Exporter la solution\n");
        printf("9 Quitter\n");

        scanf("%d", &choix);
        fflush(stdin);

        switch(choix) {
            case 1:
                printf("Entrez le chemin vers le fichier: ");
                char chemin[256];
                scanf("%s", chemin);

                instance = creerInstance(chemin);
                break;

            case 2:
                if (instance != NULL) {
                    affichage_Patients(instance->listePatients);
                } else {
                    printf("Aucune instance n a ete chargee.");
                }
                break;

            case 3:
                if (instance != NULL) {
                    affichage_Soigneurs(instance->listeSoigneurs);
                } else {
                    printf("Aucune instance n a ete chargee.");
                }
                break;

            case 4:
                if (instance != NULL) {
                    T_Patient* patient = demanderRecherchePatient(instance);
                    if (patient != NULL) {
                        T_RendezVous* rdv = demanderRechercheRendezVous(patient);
                        if (rdv != NULL) affichage_un_RendezVous(rdv);
                    }
                } else {
                    printf("Aucune instance n a ete chargee.");
                }
                break;

            case 5:
                if (instance != NULL) {
                    T_Patient* patient = demanderRecherchePatient(instance);

                    if (patient != NULL) {
                        T_RendezVous* rdv = demanderRechercheRendezVous(patient);
                        if (rdv != NULL) {
                            Time dateDebutSou, dateFinSou, tempsDeplacement;
                            char desc[125];
                            printf("Entrez la nouvelle date de debut, date de fin, temps de deplacement, et description: ");
                            scanf("%d %d %d %s", &dateDebutSou, &dateFinSou, &tempsDeplacement, desc);

                            modifierRendezVous(patient->listeRendezVous, rdv->id_soi, dateDebutSou, dateFinSou, tempsDeplacement, desc);
                            printf("Rendez vous modifie:\n");
                            affichage_un_RendezVous(rdv);
                        }
                    }
                } else {
                    printf("Aucune instance n a ete chargee.");
                }
                break;

            case 6:
                if (instance != NULL) {
                    T_Patient* patient = demanderRecherchePatient(instance);

                    if (patient != NULL) {
                        T_RendezVous* rdv = demanderRechercheRendezVous(patient);
                        if (rdv != NULL) {
                            supprimerRendezVous(patient->listeRendezVous, rdv->id_soi);
                            printf("Rendez-vous supprime.");
                        }
                    }
                } else {
                    printf("Aucune instance n a ete chargee.");
                }
                break;

            case 7:
                if (instance != NULL) {
                    ordonnancer(instance);
                    printf("Instance ordonnancee.");
                } else {
                    printf("Aucune instance n a ete chargee.");
                }
                break;

            case 8:
                if (instance != NULL) {
                    printf("Entrez le nom du fichier: ");
                    char nom[256];
                    scanf("%s", nom);
                    exportSolution(instance, nom);
                    printf("Instance exportee.");
                } else {
                    printf("Aucune instance n a ete chargee.");
                }
                break;

            case 9:
                liberer_ressource(instance);
                printf("Fermeture du programme");
                break;

            default:
                printf("Cette commande n'est pas valide, veuillez entrer un des chiffres demandes");
        }

        printf("\n\n");
        system("pause");
    }
}

void liberer_ressource(T_Ordonnancement* instance) {
    T_Patient* p = instance->listePatients;
    while (p != NULL) {
        T_RendezVous* r = p->listeRendezVous;
        while (r != NULL) {
            free(r);
            r = r->suivant;
        }
        free(p);
        p = p->suivant;
    }

    T_Soigneur* s = instance->listeSoigneurs;
    while (s != NULL) {
        T_Intervalle* i = s->listeIntervalle;
        while (i != NULL) {
            free(i);
            i = i->suivant;
        }
        free(s);
        s = s->suivant;
    }

    free(instance);
}

int compter_nb_patients(T_Patient* listePatients) {
    int amount = 0;
    T_Patient* p = listePatients;
    while (p != NULL) {
        amount++;
        p = p->suivant;
    }

    return amount;
}

int compter_nb_soigneurs(T_Soigneur* listeSoigneurs) {
    int amount = 0;
    T_Soigneur* s = listeSoigneurs;
    while (s != NULL) {
        amount++;
        s = s->suivant;
    }

    return amount;
}

int compter_nb_RdV(T_RendezVous* listeRendezVous) {
    int amount = 0;
    T_RendezVous* r = listeRendezVous;
    while (r != NULL) {
        amount++;
        r = r->suivant;
    }

    return amount;
}

Time provided_sommeDeDurationRendezVous(T_Patient* patient){
    T_RendezVous *header = patient->listeRendezVous;
    Time temps = 0;
    while(header!=NULL){
        temps += header->fin_souhaitee - header->debut_souhaitee;
        header = header->suivant;
    }
    return temps;
}


T_Patient * provided_SortedMerge(T_Patient * a, T_Patient * b){
    T_Patient * result = NULL;

    // condition d'arrêt
    if (a == NULL)
        return (b);
    else if (b == NULL)
        return (a);

    // choisir un ou autre.

    if (provided_sommeDeDurationRendezVous(a)> provided_sommeDeDurationRendezVous(b)) {
        result = a;
        result->suivant = provided_SortedMerge(a->suivant, b);
    }
    else {
        result = b;
        result->suivant = provided_SortedMerge(a, b->suivant);
    }
    return (result);
}

void provided_FrontBackSplit(T_Patient * source, T_Patient ** frontRef, T_Patient ** backRef){
    T_Patient* fast;
    T_Patient* slow;
    slow = source;
    fast = source->suivant;

    // Avancez "fast" de deux nœuds et avancez "slow" d'un nœud
    while (fast != NULL) {
        fast = fast->suivant;
        if (fast != NULL) {
            slow = slow->suivant;
            fast = fast->suivant;
        }
    }

    // "slow" est avant le milieu de la liste, alors divisez-le en deux à ce moment.
    *frontRef = source;
    *backRef = slow->suivant;
    slow->suivant = NULL;
}

void provided_MergeSort(T_Patient ** headRef){
    T_Patient* head = *headRef;
    T_Patient* a;
    T_Patient* b;

    // condition d'arrêt: quand il n'y a qu'une seule élément ou il est vide.
    if ((head == NULL) || (head->suivant == NULL)) {
        return;
    }

    /* Split head into 'a' and 'b' sublists */
    // separer la liste chaînée aux deux sous-listes.
    provided_FrontBackSplit(head, &a, &b);

    /* Recursively sort the sublists */
    provided_MergeSort(&a);
    provided_MergeSort(&b);

    // fusionner les deux sous_lists.
    *headRef = provided_SortedMerge(a, b);
}
