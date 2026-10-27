#include "Gestion_Hopital.h"
/* =============================================
   CALCUL IMC
   ============================================= */
float calculer_imc(Patient *p) {
    if (p->taille <= 0) return 0;
    return p->poids / (p->taille * p->taille);
}

const char* categorie_imc(float imc) {
    if (imc < 18.5f)  return "Insuffisance ponderale";
    if (imc < 25.0f)  return "Poids normal";
    if (imc < 30.0f)  return "Surpoids";
    return "Obesite";
}

void afficher_imc_patient(Patient *p) {
    float imc = calculer_imc(p);
    printf("  %-5d %-15s %-15s %6.2f  %s\n",
           p->id, p->nom, p->prenom, imc, categorie_imc(imc));
}

/* =============================================
   LISTE SURPOIDS / OBESITE
   ============================================= */
void afficher_surpoids_obesite() {
    afficher_titre("PATIENTS EN SURPOIDS OU OBESITE");
    printf("  %-5s %-15s %-15s %-8s %s\n", "ID", "NOM", "PRENOM", "IMC", "CATEGORIE");
    printf("  "); for (int i = 0; i < 60; i++) printf("-"); printf("\n");
    int count = 0;
    for (int i = 0; i < nb_patients; i++) {
        float imc = calculer_imc(&patients[i]);
        if (imc >= 25.0f) {
            afficher_imc_patient(&patients[i]);
            count++;
        }
    }
    if (count == 0) printf("  Aucun patient en surpoids ou obesite.\n");
    else printf("\n  Total : %d patient(s).\n", count);
    pause_entree();
}

/* =============================================
   IMC EXTREMES (plus haut / plus bas)
   ============================================= */
void afficher_imc_extremes() {
    afficher_titre("IMC EXTREMES");
    if (nb_patients == 0) {
        printf("  Aucun patient.\n");
        pause_entree();
        return;
    }
    int idx_max = 0, idx_min = 0;
    float imc_max = calculer_imc(&patients[0]);
    float imc_min = imc_max;

    for (int i = 1; i < nb_patients; i++) {
        float imc = calculer_imc(&patients[i]);
        if (imc > imc_max) { imc_max = imc; idx_max = i; }
        if (imc < imc_min) { imc_min = imc; idx_min = i; }
    }

    printf("  IMC le plus eleve :\n");
    printf("    %s %s -> IMC = %.2f (%s)\n",
           patients[idx_max].prenom, patients[idx_max].nom,
           imc_max, categorie_imc(imc_max));

    printf("\n  IMC le plus faible :\n");
    printf("    %s %s -> IMC = %.2f (%s)\n",
           patients[idx_min].prenom, patients[idx_min].nom,
           imc_min, categorie_imc(imc_min));
    pause_entree();
}

/* =============================================
   STATISTIQUES PAR CATEGORIE IMC
   ============================================= */
void stats_categories_imc() {
    afficher_titre("REPARTITION PAR CATEGORIE IMC");
    int insuffisant = 0, normal = 0, surpoids = 0, obese = 0;
    for (int i = 0; i < nb_patients; i++) {
        float imc = calculer_imc(&patients[i]);
        if      (imc < 18.5f) insuffisant++;
        else if (imc < 25.0f) normal++;
        else if (imc < 30.0f) surpoids++;
        else                  obese++;
    }
    int total = nb_patients;
    if (total == 0) { printf("  Aucun patient.\n"); pause_entree(); return; }

    printf("  %-25s : %3d patient(s) (%.1f%%)\n", "Insuffisance ponderale",
           insuffisant, 100.0f * insuffisant / total);
    printf("  %-25s : %3d patient(s) (%.1f%%)\n", "Poids normal",
           normal, 100.0f * normal / total);
    printf("  %-25s : %3d patient(s) (%.1f%%)\n", "Surpoids",
           surpoids, 100.0f * surpoids / total);
    printf("  %-25s : %3d patient(s) (%.1f%%)\n", "Obesite",
           obese, 100.0f * obese / total);
    pause_entree();
}

/* =============================================
   FIEVRE (temperature > 38°C)
   ============================================= */
void afficher_fievre() {
    afficher_titre("PATIENTS AVEC FIEVRE (T > 38 degC)");
    printf("  %-5s %-15s %-15s %s\n", "ID", "NOM", "PRENOM", "TEMP.");
    printf("  "); for (int i = 0; i < 50; i++) printf("-"); printf("\n");
    int count = 0;
    for (int i = 0; i < nb_patients; i++) {
        if (patients[i].temperature > 38.0f) {
            printf("  %-5d %-15s %-15s %.1f degC\n",
                   patients[i].id, patients[i].nom, patients[i].prenom,
                   patients[i].temperature);
            count++;
        }
    }
    if (count == 0) printf("  Aucun patient febrile.\n");
    else printf("\n  Total : %d patient(s).\n", count);
    pause_entree();
}

/* =============================================
   HYPERTENSION (systolique > 140 ou diastolique > 90)
   ============================================= */
void afficher_hypertension() {
    afficher_titre("PATIENTS AVEC HYPERTENSION ARTERIELLE");
    printf("  %-5s %-15s %-15s %s\n", "ID", "NOM", "PRENOM", "TENSION (mmHg)");
    printf("  "); for (int i = 0; i < 55; i++) printf("-"); printf("\n");
    int count = 0;
    for (int i = 0; i < nb_patients; i++) {
        if (patients[i].tension_systolique > 140 ||
            patients[i].tension_diastolique > 90) {
            printf("  %-5d %-15s %-15s %.0f/%.0f\n",
                   patients[i].id, patients[i].nom, patients[i].prenom,
                   patients[i].tension_systolique,
                   patients[i].tension_diastolique);
            count++;
        }
    }
    if (count == 0) printf("  Aucun patient hypertendu.\n");
    else printf("\n  Total : %d patient(s).\n", count);
    pause_entree();
}
