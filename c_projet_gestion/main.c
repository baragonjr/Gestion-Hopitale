/*
 * ============================================================
 *  APPLICATION DE GESTION DES PATIENTS - CENTRE HOSPITALIER
 * ============================================================
 *  Projet Langage C - LPTI 1 ESMT  - Annee 2025/2026
 *  Professeur : Dr MOUSTAPHA DER
 * ============================================================
 *
 *  COMPILATION :
 *    gcc main.c utilitaires.c gestion_patients.c recherche.c \
 *        analyse_medicale.c statistiques.c tri.c fichiers.c  \
 *        rendez_vous.c menus.c -o hopital -lm
 *
 *  EXECUTION :
 *    ./hopital
 * ============================================================
 */

#include "Gestion_Hopital.h"

int main(void) {
    menu_principal();
    return 0;
}
