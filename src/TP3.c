/****************************************************************
Author: Chenghao WANG
Contact: chenghao.wang@hds.utc.fr
Institute: Heudiasyc, université de technologie de compiègne
Date: 12/10/2020
*****************************************************************/
#include "../include/TP3.h"

/**
 * @brief Ajout d’un soigneur, où la liste des intervalles de temps disponibles pour un nouveau soigneur
 * est initialisée avec un seul intervalle [0, inf[.
 * @param listeSoigneurs une liste de soigneurs laquelle ne doit pas être vide.
 * @param idSoi un identifiant d'un soigneur.
 * @param nom le nom d'un sogineur.
 * @param prenom le prénom d'un soigneur.
 */
T_Soigneur* ajouterSoigneur(T_Soigneur* listeSoigneurs, Index_Soigneur idSoi, char* nom, char* prenom){
    //return provided_ajouterSoigneur(listeSoigneurs, idSoi, nom, prenom);
    T_Soigneur* s = (T_Soigneur*)malloc(sizeof(T_Soigneur));
    s->id_soi = idSoi;
    s->nom = (char*)malloc(sizeof(char)*(strlen(nom)+1));
    s->prenom = (char*)malloc(sizeof(char)*(strlen(prenom)+1));
    strcopy(s->nom, nom);
    strcopy(s->prenom, prenom);
    
    T_Intervalle intervalleDefaut={0,32767};
    T_Intervalle *listeIntervalle=(T_Intervalle*)malloc(sizeof(T_Intervalle));
    listeIntervalle=&intervalleDefaut;
    s->listeIntervalle = listeIntervalle;

    s->suivant = listeSoigneurs;
    return s;
}
/**
 * @brief Ajout d'un patient, où la liste de rendez-vous médicaux pour un nouveau patient est initialement vide.
 * @param listePatients une liste de patients laquelle ne doit pas être vide.
 * @param idPat un identifiant d'un patient.
 * @param nom le nom d'un patient.
 * @param prenom le prénom d'un patient.
 */
T_Patient* ajouterPatient(T_Patient* listePatients, Index_Patient idPat, char* nom, char* prenom){
    //return provided_ajouterPatient(listePatients, idPat, nom, prenom);
    T_Patient* p = (T_Patient*)malloc(sizeof(T_Patient));
    p->id_pat = idPat;
    p->nom = (char*)malloc(sizeof(char)*(strlen(nom)+1));
    p->prenom = (char*)malloc(sizeof(char)*(strlen(prenom)+1));
    strcopy(p->nom, nom);
    strcopy(p->prenom, prenom);
    p->listeRendezVous = NULL;

    p->suivant = listePatients;
    return p;
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
    T_RendezVous* r = (T_RendezVous*)malloc(sizeof(T_RendezVous));
    r->id_soi = idSoi;
    r->debut_souhaitee = dateDebutSouhaitee;
    r->fin_souhaitee = dateFinSouhaitee;
    r->temps_deplacement = tempsDeplacement;
    r->desc = (char*)malloc(sizeof(char)*(strlen(desc)+1));
    strcopy(r->desc, desc);

    r->suivant = listeRdV;
    return r;
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
    T_RendezVous* r = listeRdv;
    int trouve = 0;

    while (r->suivant != NULL) {
        if (r->id_soi == idSoi) {
            trouve = 1;
            break;
        }
        r = r->suivant;
    }
    if (!trouve) return;

    r->debut_souhaitee = dateDebutSouhaitee;
    r->fin_souhaitee = dateFinSouhaitee;
    r->temps_deplacement = tempsDeplacement;
    strcopy(r->desc, desc);
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
    T_RendezVous* r = listeRdv;
    int trouve = 0;

    while (r->suivant != NULL) {
        if (r->suivant->idSoi == idSoi) {
            trouve = 1;
            break;
        }
        if (r->suivant->suivant == NULL) break;
        r = r->suivant;
    }
    if (trouve) {
        T_RendezVous* aSupprimer = curr->suivant;
        r->suivant = curr->suivant->suivant;
        free(aSupprimer);
    }

    return listeRdV;
}

/**
 * @brief Afficher tous les soigneurs et leurs intervalles de temps disponibles
 * @param listeSoigneurs une liste de soigneurs.
 */
void affichage_Soigneurs(T_Soigneur* listeSoigneurs){
    return provided_affichage_Soigneurs(listeSoigneurs);
}

/**
 * @brief Afficher tous les patients et leurs rendez-vous
 * @param listePatients une liste de patients.
 */
void affichage_Patients(T_Patient* listePatients){
    return provided_affichage_Patients(listePatients);
}

/**
 * @brief Afficher un rendez-vous en indiquant l’identifiant du patient et le soigneur correspondant
 * @param rendezVous un rendez-vous.
 */
void affichage_RendezVous(T_RendezVous *rendezVous){
    return provided_affichage_un_RendezVous(rendezVous);
}

/**
 * @brief Créer une instance de l’ordonnancement en important à partir d’un fichier.
 * @param filename le nom d'un fichier importé.
 * @return un pointeur vers l’instance.
 */
T_Ordonnancement* creerInstance(char* filename){
    return provided_creerInstance(filename);
}

/**
 * @brief Affectation d’un rendez-vous en fonction des intervalles de temps disponibles d’un soigneur
 * (mettre à jour la date de début affectée et la date de fin affectée du rendez-vous ) 
 * @param rdv un RdV.
 * @param soigneur un soigneur.
 */
void affecterRdV(T_RendezVous* rdv, T_Soigneur* soigneur){
    return provided_affecterRdV(rdv, soigneur);
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
    T_Patient* p=(T_Patient*)malloc(sizeof(T_Patient));
    p=solution->listePatients;
    
    int tabTempsAttente[1000], index=0;
    
    while(p!=NULL)
    {
        T_RendezVous* rdv=(T_RendezVous*)malloc(sizeof(T_RendezVous));
        rdv=p->listeRendezVous;
        while(rdv!=NULL)
        {
            tabTempsAttente[index]+=
        }
    }
    p=solution->listePatients;
    
    /*
    i = 0; // variable Index de la boucle
    d = 0 ; // variable de décalage Index de boucle 
    tmp = 0;
    for(d=0; d < tailleTableau; d++)
        for(i=d; i < tailleTableau; i++)

            if (tableau [i]>= tableau [d])
            {
            tmp = tableau [d];
            tableau [d]= tableau [i];
            tableau [i] = tmp;
            }

    */
    
    
    
    
    
    
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
}

/**
 * @brief un menu principal pour le programme.
 */
void menuPrincipal(void){
//    printf("hello world\n");
    return provided_menu();
}
