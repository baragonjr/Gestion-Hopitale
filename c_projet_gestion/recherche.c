#include "Gestion_Hopital.h"

/* =============================================
   RECHERCHE PAR ID
   ============================================= */
Patient* rechercher_par_id(int id) {
    for (int i = 0; i < nb_patients; i++)
        if (patients[i].id == id)
            return &patients[i];
    return NULL;
}

/* =============================================
   RECHERCHE PAR NOM
   ============================================= */
Patient* rechercher_par_nom(const char *nom) {
    for (int i = 0; i < nb_patients; i++) {
        char tmp[50];
        strncpy(tmp, patients[i].nom, 50);
        /* Comparaison insensible a la casse */
        int j = 0;
        while (tmp[j]) { tmp[j] = toupper(tmp[j]); j++; }
        char nom_maj[50];
        strncpy(nom_maj, nom, 50);
        j = 0;
        while (nom_maj[j]) { nom_maj[j] = toupper(nom_maj[j]); j++; }
        if (strcmp(tmp, nom_maj) == 0)
            return &patients[i];
    }
    return NULL;
}

/* =============================================
   RECHERCHE PAR TELEPHONE
   ============================================= */
Patient* rechercher_par_telephone(const char *tel) {
    for (int i = 0; i < nb_patients; i++)
        if (strcmp(patients[i].telephone, tel) == 0)
            return &patients[i];
    return NULL;
}

/* =============================================
   MENU RECHERCHE
   ============================================= */
void menu_recherche() {
    int choix;
    do {
        effacer_ecran();
        afficher_titre("RECHERCHE DE PATIENT");
        printf("  1. Rechercher par ID\n");
        printf("  2. Rechercher par Nom\n");
        printf("  3. Rechercher par Telephone\n");
        printf("  0. Retour\n");
        printf("\n  Votre choix : ");
        scanf("%d", &choix); vider_buffer();

        Patient *p = NULL;
        char buf[100];

        switch (choix) {
            case 1:
                printf("  Entrez l'ID : ");
                int id; scanf("%d", &id); vider_buffer();
                p = rechercher_par_id(id);
                break;
            case 2:
                printf("  Entrez le nom : ");
                scanf("%49s", buf); vider_buffer();
                p = rechercher_par_nom(buf);
                break;
            case 3:
                printf("  Entrez le telephone : ");
                scanf("%19s", buf); vider_buffer();
                p = rechercher_par_telephone(buf);
                break;
            case 0:
                return;
            default:
                printf("  Choix invalide.\n");
        }

        if (choix >= 1 && choix <= 3) {
            if (p)
                afficher_dossier_patient(p);
            else
                printf("\n  Aucun patient trouve.\n");
            pause_entree();
        }
    } while (choix != 0);
}
