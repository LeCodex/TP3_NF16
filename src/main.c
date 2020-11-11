#include <stdio.h>
#include "../include/TP3.h"

int main() {
    //menuPrincipal();

    /*
//    TEST DE AJOUTERSOIGNEUR
    T_Soigneur* listeSoigneurs=NULL;
    listeSoigneurs=ajouterSoigneur(listeSoigneurs,1,"John","Doe");
    listeSoigneurs=ajouterSoigneur(listeSoigneurs,2,"Michel","Platini");
    listeSoigneurs=ajouterSoigneur(listeSoigneurs,3,"Jean-claude","Jarre");
    affichage_Soigneurs(listeSoigneurs);
    */

    /*
    //TEST DE AJOUTERPATIENT
    T_Patient* listePatients=NULL;
    listePatients=ajouterPatient(listePatients,1,"Roger","Dupont");
    listePatients=ajouterPatient(listePatients,2,"Fabrice","Cagri");
    listePatients=ajouterPatient(listePatients,3,"Kylian","Valois");
    affichage_Patients(listePatients);
    */

    /*
    //TEST DE AJOUTERRENDEZVOUS
    T_RendezVous* listeRendezVous=NULL;
    listeRendezVous=ajouterRendezVous(listeRendezVous,1,20,40,5,"Operation");
    listeRendezVous=ajouterRendezVous(listeRendezVous,2,10,53,7,"Scanner");
    listeRendezVous=ajouterRendezVous(listeRendezVous,3,47,59,3,"Consultation");
    T_RendezVous* ptr3=listeRendezVous;
    while(ptr3!=NULL)
    {
        printf("%s\n",ptr3->desc);
        ptr3=ptr3->suivant;
    }
    */

    /*
    //TEST DE MODIFIERRENDEZVOUS
    T_RendezVous* listeRendezVous2=NULL;
    listeRendezVous2=ajouterRendezVous(listeRendezVous2,4,20,40,5,"Reeducation");
    modifierRendezVous(listeRendezVous2,4,20,35,7,"Examen final");
    T_RendezVous* ptr4=listeRendezVous2;
    while(ptr4!=NULL)
    {
        printf("%s\n",ptr4->desc);
        ptr4=ptr4->suivant;
    }
    */

    //TEST DE CREERINSTANCE
//    T_Ordonnancement* o = creerInstance("./instance1.txt");
//    affichage_Patients(o->listePatients);
//    affichage_Soigneurs(o->listeSoigneurs);

    return 0;
}
