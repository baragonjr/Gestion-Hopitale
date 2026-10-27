#ifndef GESTION_HOPITAL_H
#define GESTION_HOPITAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>

#define MAX_PATIENTS 500
#define FICHIER_PATIENTS "patients.dat"
#define FICHIER_RDV "rendez_vous.dat"

/* =============================================
   STRUCTURES
   ============================================= */

typedef struct {
    int jour, mois, annee;
} Date;

typedef struct {
    int id;
    char nom[50];
    char prenom[50];
    Date date_naissance;
    char sexe;           /* 'M' ou 'F' */
    char adresse[100];
    char telephone[20];
    char groupe_sanguin[5];
    char service[50];
    float poids;         /* kg */
    float taille;        /* mètres */
    float temperature;   /* °C */
    float tension_systolique;
    float tension_diastolique;
    Date date_consultation;
    char diagnostic[200];
} Patient;

typedef struct {
    int id_rdv;
    int id_patient;
    char nom_patient[50];
    char prenom_patient[50];
    Date date_rdv;
    char heure[10];
    char motif[100];
    char medecin[80];
    int confirme;
} RendezVous;

/* Base de données en mémoire */
extern Patient patients[MAX_PATIENTS];
extern int nb_patients;
extern RendezVous rdvs[MAX_PATIENTS];
extern int nb_rdvs;

/* =============================================
   PROTOTYPES - GESTION DES PATIENTS
   ============================================= */
void saisir_patient(Patient *p);
void ajouter_patient();
void modifier_patient();
void supprimer_patient();
void afficher_liste_patients();
void afficher_dossier_patient(Patient *p);
void remplir_fichier_exemple();

/* =============================================
   PROTOTYPES - RECHERCHE
   ============================================= */
Patient* rechercher_par_id(int id);
Patient* rechercher_par_nom(const char *nom);
Patient* rechercher_par_telephone(const char *tel);
void menu_recherche();

/* =============================================
   PROTOTYPES - ANALYSE MEDICALE
   ============================================= */
float calculer_imc(Patient *p);
const char* categorie_imc(float imc);
void afficher_imc_patient(Patient *p);
void afficher_surpoids_obesite();
void afficher_imc_extremes();
void stats_categories_imc();
void afficher_fievre();
void afficher_hypertension();

/* =============================================
   PROTOTYPES - STATISTIQUES
   ============================================= */
void histogramme_imc();
void histogramme_temperature();
float age_moyen();
void patients_par_service();
void repartition_groupes_sanguins();

/* =============================================
   PROTOTYPES - TRI
   ============================================= */
void trier_par_nom();
void trier_par_age();
void trier_par_imc();

/* =============================================
   PROTOTYPES - FICHIERS
   ============================================= */
void enregistrer_patients();
void charger_patients();
void sauvegarder_auto();
void exporter_txt();

/* =============================================
   PROTOTYPES - RENDEZ-VOUS
   ============================================= */
void ajouter_rdv();
void afficher_rdvs();
void supprimer_rdv();

/* =============================================
   PROTOTYPES - UTILITAIRES
   ============================================= */
int calculer_age(Date naissance);
void afficher_date(Date d);
Date date_aujourd_hui();
void vider_buffer();
void pause_entree();
void effacer_ecran();
void afficher_titre(const char *titre);
int confirmer_action(const char *message);
int id_existe(int id);
int prochain_id();
int prochain_id_rdv();

/* =============================================
   PROTOTYPES - MENUS
   ============================================= */
void menu_principal();
void menu_gestion();
void menu_analyse();
void menu_statistiques();
void menu_fichiers();
void menu_rdv();
void menu_tri();

#endif
