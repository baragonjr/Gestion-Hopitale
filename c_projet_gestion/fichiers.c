#include "Gestion_Hopital.h"
/* =============================================
   ENREGISTRER PATIENTS DANS LE FICHIER
   ============================================= */
void enregistrer_patients() {
    FILE *f = fopen(FICHIER_PATIENTS, "wb");
    if (!f) {
        printf("  ERREUR : Impossible d'ouvrir le fichier '%s'.\n", FICHIER_PATIENTS);
        return;
    }
    fwrite(&nb_patients, sizeof(int), 1, f);
    fwrite(patients, sizeof(Patient), nb_patients, f);
    fclose(f);
    printf("  %d patient(s) enregistre(s) dans '%s'.\n", nb_patients, FICHIER_PATIENTS);
}

/* =============================================
   CHARGER PATIENTS DEPUIS LE FICHIER
   ============================================= */
void charger_patients() {
    FILE *f = fopen(FICHIER_PATIENTS, "rb");
    if (!f) {
        printf("  INFO : Fichier '%s' absent. Demarrage avec base vide.\n", FICHIER_PATIENTS);
        nb_patients = 0;
        return;
    }
    int lu = fread(&nb_patients, sizeof(int), 1, f);
    if (lu != 1 || nb_patients < 0 || nb_patients > MAX_PATIENTS) {
        printf("  ERREUR : Fichier corrompu. Base reinitalisee.\n");
        nb_patients = 0;
        fclose(f);
        return;
    }
    fread(patients, sizeof(Patient), nb_patients, f);
    fclose(f);
    printf("  %d patient(s) charge(s) depuis '%s'.\n", nb_patients, FICHIER_PATIENTS);
}

/* =============================================
   SAUVEGARDE AUTOMATIQUE
   ============================================= */
void sauvegarder_auto() {
    FILE *f = fopen(FICHIER_PATIENTS, "wb");
    if (!f) return;
    fwrite(&nb_patients, sizeof(int), 1, f);
    fwrite(patients, sizeof(Patient), nb_patients, f);
    fclose(f);
}

/* =============================================
   EXPORT TEXTE
   ============================================= */
void exporter_txt() {
    afficher_titre("EXPORT DES DONNEES EN TEXTE");
    char nom_fichier[100];
    printf("  Nom du fichier d'export (sans extension) : ");
    scanf("%99s", nom_fichier); vider_buffer();
    strcat(nom_fichier, ".txt");

    FILE *f = fopen(nom_fichier, "w");
    if (!f) {
        printf("  ERREUR : Impossible de creer '%s'.\n", nom_fichier);
        pause_entree();
        return;
    }

    fprintf(f, "========================================\n");
    fprintf(f, " EXPORT DOSSIERS MEDICAUX - %d patient(s)\n", nb_patients);
    fprintf(f, "========================================\n\n");

    for (int i = 0; i < nb_patients; i++) {
        Patient *p = &patients[i];
        fprintf(f, "--- Dossier N° %d ---\n", p->id);
        fprintf(f, "Nom         : %s %s\n", p->prenom, p->nom);
        fprintf(f, "Naissance   : %02d/%02d/%04d (Age : %d ans)\n",
                p->date_naissance.jour, p->date_naissance.mois,
                p->date_naissance.annee, calculer_age(p->date_naissance));
        fprintf(f, "Sexe        : %c\n", p->sexe);
        fprintf(f, "Telephone   : %s\n", p->telephone);
        fprintf(f, "Groupe sg.  : %s\n", p->groupe_sanguin);
        fprintf(f, "Service     : %s\n", p->service);
        float imc = calculer_imc(p);
        fprintf(f, "IMC         : %.2f (%s)\n", imc, categorie_imc(imc));
        fprintf(f, "Temperature : %.1f degC\n", p->temperature);
        fprintf(f, "Tension     : %.0f/%.0f mmHg\n",
                p->tension_systolique, p->tension_diastolique);
        fprintf(f, "Diagnostic  : %s\n\n", p->diagnostic);
    }
    fclose(f);
    printf("  Export reussi dans '%s'.\n", nom_fichier);
    pause_entree();
}
