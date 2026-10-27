#include "Gestion_Hopital.h"
/* =============================================
   HISTOGRAMME IMC
   ============================================= */
void histogramme_imc() {
    afficher_titre("HISTOGRAMME DES IMC");
    if (nb_patients == 0) { printf("  Aucun patient.\n"); pause_entree(); return; }

    printf("  %-20s | Valeur  | Histogramme\n", "NOM PRENOM");
    printf("  "); for (int i = 0; i < 55; i++) printf("-"); printf("\n");

    for (int i = 0; i < nb_patients; i++) {
        float imc = calculer_imc(&patients[i]);
        char label[25];
        snprintf(label, 25, "%s %s", patients[i].nom, patients[i].prenom);
        printf("  %-20s | %5.2f   | ", label, imc);
        int barres = (int)(imc / 2);
        for (int j = 0; j < barres; j++) printf("#");
        printf("\n");
    }
    printf("\n  (Chaque # = 2 unites d'IMC)\n");
    pause_entree();
}

/* =============================================
   HISTOGRAMME TEMPERATURES
   ============================================= */
void histogramme_temperature() {
    afficher_titre("HISTOGRAMME DES TEMPERATURES");
    if (nb_patients == 0) { printf("  Aucun patient.\n"); pause_entree(); return; }

    printf("  %-20s | Valeur  | Histogramme\n", "NOM PRENOM");
    printf("  "); for (int i = 0; i < 55; i++) printf("-"); printf("\n");

    for (int i = 0; i < nb_patients; i++) {
        char label[25];
        snprintf(label, 25, "%s %s", patients[i].nom, patients[i].prenom);
        printf("  %-20s | %5.1f C | ", label, patients[i].temperature);
        /* Base a 36°C pour mieux voir les variations */
        int barres = (int)((patients[i].temperature - 36.0f) * 10);
        if (barres < 0) barres = 0;
        for (int j = 0; j < barres; j++) printf("|");
        if (barres == 0) printf(".");
        printf("\n");
    }
    printf("\n  (Base = 36 degC | chaque | = 0.1 degC)\n");
    pause_entree();
}

/* =============================================
   AGE MOYEN
   ============================================= */
float age_moyen() {
    if (nb_patients == 0) return 0;
    float total = 0;
    for (int i = 0; i < nb_patients; i++)
        total += calculer_age(patients[i].date_naissance);
    return total / nb_patients;
}

/* =============================================
   PATIENTS PAR SERVICE
   ============================================= */
void patients_par_service() {
    afficher_titre("REPARTITION PAR SERVICE");
    if (nb_patients == 0) { printf("  Aucun patient.\n"); pause_entree(); return; }

    /* Collecte des services uniques */
    char services[50][50];
    int comptes[50] = {0};
    int nb_services = 0;

    for (int i = 0; i < nb_patients; i++) {
        int trouve = 0;
        for (int j = 0; j < nb_services; j++) {
            if (strcmp(patients[i].service, services[j]) == 0) {
                comptes[j]++;
                trouve = 1;
                break;
            }
        }
        if (!trouve && nb_services < 50) {
            strncpy(services[nb_services], patients[i].service, 50);
            comptes[nb_services] = 1;
            nb_services++;
        }
    }

    printf("  %-30s : Nombre\n", "SERVICE");
    printf("  "); for (int i = 0; i < 40; i++) printf("-"); printf("\n");
    for (int i = 0; i < nb_services; i++) {
        printf("  %-30s : %d\n", services[i], comptes[i]);
    }
    printf("\n  Age moyen des patients : %.1f ans\n", age_moyen());
    pause_entree();
}

/* =============================================
   REPARTITION GROUPES SANGUINS
   ============================================= */
void repartition_groupes_sanguins() {
    afficher_titre("REPARTITION DES GROUPES SANGUINS");
    if (nb_patients == 0) { printf("  Aucun patient.\n"); pause_entree(); return; }

    const char *groupes[] = {"A+","A-","B+","B-","AB+","AB-","O+","O-"};
    int comptes[8] = {0};
    int nb_groupes = 8;

    for (int i = 0; i < nb_patients; i++) {
        for (int j = 0; j < nb_groupes; j++) {
            if (strcmp(patients[i].groupe_sanguin, groupes[j]) == 0) {
                comptes[j]++;
                break;
            }
        }
    }

    printf("  %-8s : Nb  | Graphique\n", "GROUPE");
    printf("  "); for (int i = 0; i < 40; i++) printf("-"); printf("\n");
    for (int j = 0; j < nb_groupes; j++) {
        printf("  %-8s : %3d | ", groupes[j], comptes[j]);
        for (int k = 0; k < comptes[j]; k++) printf("*");
        printf("\n");
    }
    pause_entree();
}
