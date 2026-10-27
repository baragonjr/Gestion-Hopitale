#include "Gestion_Hopital.h"

/* Variables globales */
Patient patients[MAX_PATIENTS];
int nb_patients = 0;
RendezVous rdvs[MAX_PATIENTS];
int nb_rdvs = 0;

/* =============================================
   UTILITAIRES GENERAUX
   ============================================= */

void vider_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void pause_entree() {
    printf("\n  Appuyez sur Entree pour continuer...");
    vider_buffer();
}

void effacer_ecran() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void afficher_titre(const char *titre) {
    int len = strlen(titre);
    int largeur = 60;
    int padding = (largeur - len) / 2;
    printf("\n");
    for (int i = 0; i < largeur; i++) printf("=");
    printf("\n");
    for (int i = 0; i < padding; i++) printf(" ");
    printf("%s\n", titre);
    for (int i = 0; i < largeur; i++) printf("=");
    printf("\n");
}

void afficher_date(Date d) {
    printf("%02d/%02d/%04d", d.jour, d.mois, d.annee);
}

Date date_aujourd_hui() {
    Date d;
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    d.jour  = tm_info->tm_mday;
    d.mois  = tm_info->tm_mon + 1;
    d.annee = tm_info->tm_year + 1900;
    return d;
}

int calculer_age(Date naissance) {
    Date auj = date_aujourd_hui();
    int age = auj.annee - naissance.annee;
    if (auj.mois < naissance.mois ||
       (auj.mois == naissance.mois && auj.jour < naissance.jour))
        age--;
    return age;
}

int confirmer_action(const char *message) {
    char reponse;
    printf("  %s (o/n) : ", message);
    scanf(" %c", &reponse);
    vider_buffer();
    return (reponse == 'o' || reponse == 'O');
}

int id_existe(int id) {
    for (int i = 0; i < nb_patients; i++)
        if (patients[i].id == id) return 1;
    return 0;
}

int prochain_id() {
    int max = 0;
    for (int i = 0; i < nb_patients; i++)
        if (patients[i].id > max) max = patients[i].id;
    return max + 1;
}

int prochain_id_rdv() {
    int max = 0;
    for (int i = 0; i < nb_rdvs; i++)
        if (rdvs[i].id_rdv > max) max = rdvs[i].id_rdv;
    return max + 1;
}
