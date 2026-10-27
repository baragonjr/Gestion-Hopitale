#include "Gestion_Hopital.h"

/* =============================================
   MENU GESTION PATIENTS
   ============================================= */
void menu_gestion() {
    int choix;
    do {
        effacer_ecran();
        afficher_titre("GESTION DES PATIENTS");
        printf("  1. Ajouter un patient\n");
        printf("  2. Modifier un patient\n");
        printf("  3. Supprimer un patient\n");
        printf("  4. Afficher la liste complete\n");
        printf("  5. Afficher le dossier d'un patient\n");
        printf("  6. Charger donnees exemples\n");
        printf("  0. Retour au menu principal\n");
        printf("\n  Votre choix : ");
        scanf("%d", &choix); vider_buffer();

        switch (choix) {
            case 1: ajouter_patient(); break;
            case 2: modifier_patient(); break;
            case 3: supprimer_patient(); break;
            case 4: afficher_liste_patients(); break;
            case 5: {
                int id;
                printf("  ID du patient : "); scanf("%d", &id); vider_buffer();
                Patient *p = rechercher_par_id(id);
                if (p) afficher_dossier_patient(p);
                else   printf("  Patient introuvable.\n");
                pause_entree();
                break;
            }
            case 6: remplir_fichier_exemple(); break;
            case 0: break;
            default: printf("  Choix invalide.\n"); pause_entree();
        }
    } while (choix != 0);
}

/* =============================================
   MENU ANALYSE MEDICALE
   ============================================= */
void menu_analyse() {
    int choix;
    do {
        effacer_ecran();
        afficher_titre("ANALYSE MEDICALE");
        printf("  1. Calculer et afficher IMC de tous les patients\n");
        printf("  2. Patients en surpoids ou obesite\n");
        printf("  3. IMC le plus eleve et le plus faible\n");
        printf("  4. Statistiques par categorie IMC\n");
        printf("  5. Patients avec fievre (T > 38 degC)\n");
        printf("  6. Patients avec hypertension arterielle\n");
        printf("  0. Retour\n");
        printf("\n  Votre choix : ");
        scanf("%d", &choix); vider_buffer();

        switch (choix) {
            case 1: {
                afficher_titre("IMC DE TOUS LES PATIENTS");
                printf("  %-5s %-15s %-15s %8s  %s\n","ID","NOM","PRENOM","IMC","CATEGORIE");
                printf("  "); for (int i=0; i<60; i++) printf("-"); printf("\n");
                for (int i = 0; i < nb_patients; i++)
                    afficher_imc_patient(&patients[i]);
                pause_entree();
                break;
            }
            case 2: afficher_surpoids_obesite(); break;
            case 3: afficher_imc_extremes(); break;
            case 4: stats_categories_imc(); break;
            case 5: afficher_fievre(); break;
            case 6: afficher_hypertension(); break;
            case 0: break;
            default: printf("  Choix invalide.\n"); pause_entree();
        }
    } while (choix != 0);
}

/* =============================================
   MENU STATISTIQUES
   ============================================= */
void menu_statistiques() {
    int choix;
    do {
        effacer_ecran();
        afficher_titre("STATISTIQUES");
        printf("  1. Histogramme des IMC\n");
        printf("  2. Histogramme des temperatures\n");
        printf("  3. Repartition par service\n");
        printf("  4. Repartition des groupes sanguins\n");
        printf("  0. Retour\n");
        printf("\n  Votre choix : ");
        scanf("%d", &choix); vider_buffer();

        switch (choix) {
            case 1: histogramme_imc(); break;
            case 2: histogramme_temperature(); break;
            case 3: patients_par_service(); break;
            case 4: repartition_groupes_sanguins(); break;
            case 0: break;
            default: printf("  Choix invalide.\n"); pause_entree();
        }
    } while (choix != 0);
}

/* =============================================
   MENU FICHIERS
   ============================================= */
void menu_fichiers() {
    int choix;
    do {
        effacer_ecran();
        afficher_titre("GESTION DES FICHIERS");
        printf("  1. Enregistrer les patients dans le fichier\n");
        printf("  2. Charger les patients depuis le fichier\n");
        printf("  3. Exporter les donnees en fichier texte\n");
        printf("  0. Retour\n");
        printf("\n  Votre choix : ");
        scanf("%d", &choix); vider_buffer();

        switch (choix) {
            case 1: enregistrer_patients(); pause_entree(); break;
            case 2: charger_patients();    pause_entree(); break;
            case 3: exporter_txt(); break;
            case 0: break;
            default: printf("  Choix invalide.\n"); pause_entree();
        }
    } while (choix != 0);
}

/* =============================================
   MENU TRI
   ============================================= */
void menu_tri() {
    int choix;
    do {
        effacer_ecran();
        afficher_titre("TRI DES PATIENTS");
        printf("  1. Trier par nom\n");
        printf("  2. Trier par age\n");
        printf("  3. Trier par IMC\n");
        printf("  0. Retour\n");
        printf("\n  Votre choix : ");
        scanf("%d", &choix); vider_buffer();

        switch (choix) {
            case 1: trier_par_nom(); break;
            case 2: trier_par_age(); break;
            case 3: trier_par_imc(); break;
            case 0: break;
            default: printf("  Choix invalide.\n"); pause_entree();
        }
    } while (choix != 0);
}

/* =============================================
   MENU RENDEZ-VOUS
   ============================================= */
void menu_rdv() {
    int choix;
    do {
        effacer_ecran();
        afficher_titre("GESTION DES RENDEZ-VOUS");
        printf("  1. Ajouter un rendez-vous\n");
        printf("  2. Afficher tous les rendez-vous\n");
        printf("  3. Supprimer un rendez-vous\n");
        printf("  0. Retour\n");
        printf("\n  Votre choix : ");
        scanf("%d", &choix); vider_buffer();

        switch (choix) {
            case 1: ajouter_rdv(); break;
            case 2: afficher_rdvs(); break;
            case 3: supprimer_rdv(); break;
            case 0: break;
            default: printf("  Choix invalide.\n"); pause_entree();
        }
    } while (choix != 0);
}

/* =============================================
   MENU PRINCIPAL
   ============================================= */
void menu_principal() {
    charger_patients();

    int choix;
    do {
        effacer_ecran();
        printf("\n");
        printf("                                ############################################################\n");
        printf("                                 #                                                       #\n");
        printf("                                   # # #      SYSTEME DE GESTION HOSPITALIERE       # # #\n");
        printf("                                 #                                                       #\n");
        printf("                                ############################################################\n");
        printf("  Patients charges : %d\n\n", nb_patients);

        printf("  1. Gestion des patients\n");
        printf("  2. Recherche de patients\n");
        printf("  3. Analyse medicale (IMC, fievre, tension)\n");
        printf("  4. Statistiques\n");
        printf("  5. Gestion des fichiers\n");
        printf("  6. Tri des patients\n");
        printf("  7. Rendez-vous medicaux\n");
        printf("  0. Quitter\n");
        printf("\n  Votre choix : ");
        scanf("%d", &choix); vider_buffer();

        switch (choix) {
            case 1: menu_gestion(); break;
            case 2: menu_recherche(); break;
            case 3: menu_analyse(); break;
            case 4: menu_statistiques(); break;
            case 5: menu_fichiers(); break;
            case 6: menu_tri(); break;
            case 7: menu_rdv(); break;
            case 0:
                sauvegarder_auto();
                printf("\n  Sauvegarde effectuee. Au revoir !\n\n");
                break;
            default:
                printf("  Choix invalide. Reessayez.\n");
                pause_entree();
        }
    } while (choix != 0);
}
