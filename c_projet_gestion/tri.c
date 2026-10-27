#include "Gestion_Hopital.h"
/* =============================================
   TRI PAR NOM (tri a bulles)
   ============================================= */
void trier_par_nom() {
    afficher_titre("TRI DES PATIENTS PAR NOM");
    Patient temp;
    for (int i = 0; i < nb_patients - 1; i++) {
        for (int j = 0; j < nb_patients - i - 1; j++) {
            if (strcmp(patients[j].nom, patients[j+1].nom) > 0) {
                temp = patients[j];
                patients[j] = patients[j+1];
                patients[j+1] = temp;
            }
        }
    }
    printf("  Patients tries par nom.\n");
    sauvegarder_auto();
    afficher_liste_patients();
}

/* =============================================
   TRI PAR AGE (croissant)
   ============================================= */
void trier_par_age() {
    afficher_titre("TRI DES PATIENTS PAR AGE");
    Patient temp;
    for (int i = 0; i < nb_patients - 1; i++) {
        for (int j = 0; j < nb_patients - i - 1; j++) {
            int age_j  = calculer_age(patients[j].date_naissance);
            int age_j1 = calculer_age(patients[j+1].date_naissance);
            if (age_j > age_j1) {
                temp = patients[j];
                patients[j] = patients[j+1];
                patients[j+1] = temp;
            }
        }
    }
    printf("  Patients tries par age.\n");
    sauvegarder_auto();
    afficher_liste_patients();
}

/* =============================================
   TRI PAR IMC (croissant)
   ============================================= */
void trier_par_imc() {
    afficher_titre("TRI DES PATIENTS PAR IMC");
    Patient temp;
    for (int i = 0; i < nb_patients - 1; i++) {
        for (int j = 0; j < nb_patients - i - 1; j++) {
            float imc_j  = calculer_imc(&patients[j]);
            float imc_j1 = calculer_imc(&patients[j+1]);
            if (imc_j > imc_j1) {
                temp = patients[j];
                patients[j] = patients[j+1];
                patients[j+1] = temp;
            }
        }
    }
    printf("  Patients tries par IMC.\n");
    sauvegarder_auto();

    printf("  %-5s %-15s %-15s %8s  %s\n", "ID","NOM","PRENOM","IMC","CATEGORIE");
    printf("  "); for (int i = 0; i < 60; i++) printf("-"); printf("\n");
    for (int i = 0; i < nb_patients; i++) {
        float imc = calculer_imc(&patients[i]);
        printf("  %-5d %-15s %-15s %8.2f  %s\n",
               patients[i].id, patients[i].nom, patients[i].prenom,
               imc, categorie_imc(imc));
    }
    pause_entree();
}
