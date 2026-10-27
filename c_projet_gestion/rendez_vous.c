#include "Gestion_Hopital.h"
/* =============================================
   AJOUTER UN RENDEZ-VOUS
   ============================================= */
void ajouter_rdv() {
    afficher_titre("NOUVEAU RENDEZ-VOUS");
    if (nb_rdvs >= MAX_PATIENTS) {
        printf("  Capacite maximale de rendez-vous atteinte.\n");
        pause_entree();
        return;
    }

    RendezVous r;
    r.id_rdv = prochain_id_rdv();

    printf("  ID du patient : ");
    scanf("%d", &r.id_patient); vider_buffer();

    Patient *p = rechercher_par_id(r.id_patient);
    if (!p) {
        printf("  Patient ID %d introuvable.\n", r.id_patient);
        pause_entree();
        return;
    }
    strncpy(r.nom_patient,    p->nom,    50);
    strncpy(r.prenom_patient, p->prenom, 50);

    printf("  Date du RDV (jj mm aaaa) : ");
    scanf("%d %d %d", &r.date_rdv.jour, &r.date_rdv.mois, &r.date_rdv.annee);
    vider_buffer();

    printf("  Heure (ex: 09:30) : ");
    scanf("%9s", r.heure); vider_buffer();

    printf("  Motif : ");
    fgets(r.motif, 100, stdin);
    r.motif[strcspn(r.motif, "\n")] = '\0';

    printf("  Medecin : ");
    fgets(r.medecin, 80, stdin);
    r.medecin[strcspn(r.medecin, "\n")] = '\0';

    r.confirme = 1;
    rdvs[nb_rdvs++] = r;

    printf("\n  Rendez-vous N°%d cree pour %s %s le %02d/%02d/%04d a %s.\n",
           r.id_rdv, r.prenom_patient, r.nom_patient,
           r.date_rdv.jour, r.date_rdv.mois, r.date_rdv.annee, r.heure);
    pause_entree();
}

/* =============================================
   AFFICHER LES RENDEZ-VOUS
   ============================================= */
void afficher_rdvs() {
    afficher_titre("LISTE DES RENDEZ-VOUS");
    if (nb_rdvs == 0) {
        printf("  Aucun rendez-vous planifie.\n");
        pause_entree();
        return;
    }
    printf("  %-5s %-20s %-12s %-8s %-20s\n",
           "ID", "PATIENT", "DATE", "HEURE", "MEDECIN");
    printf("  "); for (int i = 0; i < 70; i++) printf("-"); printf("\n");
    for (int i = 0; i < nb_rdvs; i++) {
        char patient[35];
        snprintf(patient, 35, "%s %s", rdvs[i].prenom_patient, rdvs[i].nom_patient);
        printf("  %-5d %-20s %02d/%02d/%04d %-8s %-20s\n",
               rdvs[i].id_rdv, patient,
               rdvs[i].date_rdv.jour, rdvs[i].date_rdv.mois, rdvs[i].date_rdv.annee,
               rdvs[i].heure, rdvs[i].medecin);
    }
    printf("\n  Total : %d rendez-vous.\n", nb_rdvs);
    pause_entree();
}

/* =============================================
   SUPPRIMER UN RENDEZ-VOUS
   ============================================= */
void supprimer_rdv() {
    afficher_titre("SUPPRESSION D'UN RENDEZ-VOUS");
    printf("  Entrez l'ID du rendez-vous : ");
    int id; scanf("%d", &id); vider_buffer();

    int idx = -1;
    for (int i = 0; i < nb_rdvs; i++) {
        if (rdvs[i].id_rdv == id) { idx = i; break; }
    }
    if (idx == -1) {
        printf("  Rendez-vous ID %d introuvable.\n", id);
    } else if (confirmer_action("Confirmer la suppression ?")) {
        for (int i = idx; i < nb_rdvs - 1; i++)
            rdvs[i] = rdvs[i+1];
        nb_rdvs--;
        printf("  Rendez-vous supprime.\n");
    }
    pause_entree();
}
