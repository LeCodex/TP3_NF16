/****************************************************************
Author: Chenghao WANG
Contact: chenghao.wang@hds.utc.fr
Institute: Heudiasyc, université de technologie de compiègne
Date: 12/10/2020
*****************************************************************/
#include "../include/TP3.h"
#include <stdlib.h>
#include <time.h>
#include<string.h>

/**
 * @brief Ajout d’un soigneur, où la liste des intervalles de temps disponibles pour un nouveau soigneur
 * est initialisée avec un seul intervalle [0, inf[.
 * @param listeSoigneurs une liste de soigneurs laquelle ne doit pas être vide.
 * @param idSoi un identifiant d'un soigneur.
 * @param nom le nom d'un sogineur.
 * @param prenom le prénom d'un soigneur.
 */
T_Soigneur* ajouterSoigneur(T_Soigneur* listeSoigneurs, Index_Soigneur idSoi, char* nom, char* prenom){
    T_Soigneur *nouvSoigneur=malloc(sizeof(T_Soigneur*));
    T_Intervalle intervalleDefaut={0,32767};
    T_Intervalle *listeIntervalle=malloc(sizeof(T_Intervalle*));
    listeIntervalle=&intervalleDefaut;

    nouvSoigneur->id_soi=idSoi;
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
    T_RendezVous* nouvRendezVous=malloc(sizeof(T_RendezVous*));

    nouvRendezVous->id_soi=idSoi;
    nouvRendezVous->debut_souhaitee=dateDebutSouhaitee;
    nouvRendezVous->fin_souhaitee=dateFinSouhaitee;
    nouvRendezVous->temps_deplacement=tempsDeplacement;
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
        r->suivant = r->suivant->suivant;
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
            printf("%s, id_soigneur_associe: %d, temps_deplacement_depuis_rdv_precedent:%d\n",r->desc,r->id_soi,r->temps_deplacement);
            printf("\t rdv souhaite: [%d, %d[, rdv affecte: [%d, %d[\n\n",r->debut_souhaitee,r->fin_souhaitee,r->debut_affectee,r->fin_affectee);
            r=r->suivant;
        }
    }
}

/**
 * @brief Créer une instance de l’ordonnancement en important à partir d’un fichier.
 * @param filename le nom d'un fichier importé.
 * @return un pointeur vers l’instance.
 */
T_Ordonnancement* creerInstance(char* filename){
    FILE* fptr;
    T_Ordonnancement* o = malloc(sizeof(T_Ordonnancement*));

    if ((fptr = fopen(filename, "r")) == NULL) {
        printf("Erreur dans l'ouverture du fichier");
        exit(1);
    }

    unsigned int nbPatients = 0, nbSoigneurs = 0;
    fscanf(fptr, "%u", &nbPatients);
    fscanf(fptr, "%u", &nbSoigneurs);
    printf("Read patients and doctors amount: %d, %d\n\n", nbPatients, nbSoigneurs);

    unsigned int idPat, nbRdV, idSoi, dateDebutSouhaitee, dateFinSouhaitee, tempsDeplacement;
    char nom[40], prenom[40], desc[125];
    printf("[Reading patients info]\n");
    for (int i = 0; i < nbPatients; ++i) {
        fscanf(fptr, "%u", &idPat);
        fscanf(fptr, "%u", &nbRdV);
        fscanf(fptr, "%s", nom);
        fscanf(fptr, "%s", prenom);

        o->listePatients = ajouterPatient(o->listePatients, idPat, nom, prenom);
        printf("Read patient %d with %d appointments, named %s %s\n", idPat, nbRdV, nom, prenom);

        for (int j = 0; j < nbRdV; ++j) {
            fscanf(fptr, "%u", &idSoi);
            printf("Id %d/", idSoi);
            fscanf(fptr, "%u", &dateDebutSouhaitee);
            printf("Start %d/", dateDebutSouhaitee);
            fscanf(fptr, "%u", &dateFinSouhaitee);
            printf("End %d/", dateFinSouhaitee);
            fscanf(fptr, "%u", &tempsDeplacement);
            printf("Travel %d/", tempsDeplacement);
            fscanf(fptr, "%s", desc);
            printf("Description %s\n", desc);

            printf("  Read appointment with doctor %d (%s): starting %d, ending %d, with %d minutes of travel\n", idSoi, desc, dateDebutSouhaitee, dateFinSouhaitee, tempsDeplacement);
            o->listePatients->listeRendezVous = ajouterRendezVous(o->listePatients->listeRendezVous, idSoi, dateDebutSouhaitee, dateFinSouhaitee, tempsDeplacement, desc);
        }
        printf("\n");
    }

    printf("\n[Reading doctors info]\n");
    for (int i = 0; i < nbSoigneurs; ++i) {
        fscanf(fptr, "%u", &idSoi);
        fscanf(fptr, "%s", nom);
        fscanf(fptr, "%s", prenom);

        o->listeSoigneurs = ajouterSoigneur(o->listeSoigneurs, idSoi, nom, prenom);
        printf("Read doctor %d, named %s %s\n", idSoi, nom, prenom);
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
    rdv->debut_affectee = rdv->debut_souhaitee;

    T_Intervalle* intervalle = soigneur->listeIntervalle;
    while (intervalle != NULL) {
        if (intervalle->fin > rdv->debut_affectee) {
            rdv->debut_affectee = intervalle->fin;
        }
        intervalle = intervalle->suivant;
    }

    rdv->fin_affectee = rdv->debut_affectee - rdv->debut_souhaitee + rdv->fin_souhaitee;
    rdv->id_soi = soigneur->id_soi;
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
        while(r!=NULL) //On parcours tt les rdv
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
    T_Patient* p = (T_Patient*)malloc(sizeof(T_Patient*));
    p=solution->listePatients;

    T_RendezVous* r = malloc(sizeof(T_RendezVous));

    FILE* fichier = NULL;

    time_t timestamp;
    time(&timestamp);

    char dateCourante[256];
    strftime(dateCourante, sizeof(dateCourante), "%Y-%m-%d", localtime(&timestamp));
    char nomFichier[256]="solution.txt.";
    strcat(nomFichier,dateCourante);
    strcat(nomFichier,".txt");
    filename=nomFichier;

    fichier = fopen(nomFichier, "w");

    if (fichier != NULL)
    {
        unsigned int nbPatients=0, nbSoigneurs=0,nbRdV=0;
        nbPatients=provided_compter_nb_patients(solution->listePatients);
        nbSoigneurs=provided_compter_nb_soigneurs(solution->listeSoigneurs);
        fprintf(fichier, "%u ",nbPatients);
        fprintf(fichier, "%u\n",nbSoigneurs);

        for (int i = 0; i < nbPatients; ++i) {
            nbRdV=provided_compter_nb_Rdv_par_patient(p->id_pat,p);
            fprintf(fichier, "%u %u\n", p->id_pat,nbRdV);

            r=p->listeRendezVous;
            for (int j = 0; j < nbRdV; ++j) {
                fprintf(fichier, "%u %u %u %u\n", r->id_soi,r->debut_souhaitee,r->fin_souhaitee,r->temps_deplacement);
                r=r->suivant;
            }
            p=p->suivant;
        }
        fclose(fichier);
    }
    else
    {

        printf("Impossible d'écrire dans le fichier %s",nomFichier);
    }

    return ;

}

/**
 * @brief un menu principal pour le programme.
 */
void menuPrincipal(void){
//    printf("hello world\n");
    return provided_menu();
}
