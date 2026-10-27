#include "Gestion_Hopital.h"

/* =============================================
   SAISIE D'UN PATIENT
   ============================================= */
void saisir_patient(Patient *p) {
    printf("\n  --- Saisie du patient ---\n");

    printf("  Nom           : "); scanf("%49s", p->nom); vider_buffer();
    printf("  Prenom        : "); scanf("%49s", p->prenom); vider_buffer();

    printf("  Date naissance (jj mm aaaa) : ");
    scanf("%d %d %d", &p->date_naissance.jour,
                      &p->date_naissance.mois,
                      &p->date_naissance.annee);
    vider_buffer();

    printf("  Sexe (M/F)    : "); scanf(" %c", &p->sexe); vider_buffer();

    printf("  Adresse       : "); fgets(p->adresse, 100, stdin);
    p->adresse[strcspn(p->adresse, "\n")] = '\0';

    printf("  Telephone     : "); scanf("%19s", p->telephone); vider_buffer();

    printf("  Groupe sanguin (A+/A-/B+/B-/AB+/AB-/O+/O-) : ");
    scanf("%4s", p->groupe_sanguin); vider_buffer();

    printf("  Service (Cardiologie/Pediatrie/Chirurgie/Medecine Generale/...) : ");
    fgets(p->service, 50, stdin);
    p->service[strcspn(p->service, "\n")] = '\0';

    printf("  Poids (kg)         : "); scanf("%f", &p->poids); vider_buffer();
    printf("  Taille (m)         : "); scanf("%f", &p->taille); vider_buffer();
    printf("  Temperature (C)    : "); scanf("%f", &p->temperature); vider_buffer();
    printf("  Tension systolique : "); scanf("%f", &p->tension_systolique); vider_buffer();
    printf("  Tension diastolique: "); scanf("%f", &p->tension_diastolique); vider_buffer();

    printf("  Date consultation (jj mm aaaa) : ");
    scanf("%d %d %d", &p->date_consultation.jour,
                      &p->date_consultation.mois,
                      &p->date_consultation.annee);
    vider_buffer();

    printf("  Diagnostic medical : "); fgets(p->diagnostic, 200, stdin);
    p->diagnostic[strcspn(p->diagnostic, "\n")] = '\0';
}

/* =============================================
   AJOUTER UN PATIENT
   ============================================= */
void ajouter_patient() {
    if (nb_patients >= MAX_PATIENTS) {
        printf("  ERREUR : Capacite maximale atteinte (%d patients).\n", MAX_PATIENTS);
        pause_entree();
        return;
    }
    afficher_titre("AJOUT D'UN PATIENT");
    Patient p;
    p.id = prochain_id();
    printf("  ID attribue automatiquement : %d\n", p.id);
    saisir_patient(&p);
    patients[nb_patients++] = p;
    sauvegarder_auto();
    printf("\n  Patient ajoute avec succes (ID : %d).\n", p.id);
    pause_entree();
}

/* =============================================
   MODIFIER UN PATIENT
   ============================================= */
void modifier_patient() {
    afficher_titre("MODIFICATION D'UN PATIENT");
    int id;
    printf("  Entrez l'ID du patient a modifier : ");
    scanf("%d", &id); vider_buffer();

    Patient *p = rechercher_par_id(id);
    if (!p) {
        printf("  Patient ID %d introuvable.\n", id);
        pause_entree();
        return;
    }
    printf("  Patient trouve : %s %s\n", p->prenom, p->nom);
    if (confirmer_action("Confirmer la modification ?")) {
        int saved_id = p->id;
        saisir_patient(p);
        p->id = saved_id;
        sauvegarder_auto();
        printf("\n  Patient modifie avec succes.\n");
    }
    pause_entree();
}

/* =============================================
   SUPPRIMER UN PATIENT
   ============================================= */
void supprimer_patient() {
    afficher_titre("SUPPRESSION D'UN PATIENT");
    int id;
    printf("  Entrez l'ID du patient a supprimer : ");
    scanf("%d", &id); vider_buffer();

    int idx = -1;
    for (int i = 0; i < nb_patients; i++) {
        if (patients[i].id == id) { idx = i; break; }
    }
    if (idx == -1) {
        printf("  Patient ID %d introuvable.\n", id);
        pause_entree();
        return;
    }
    printf("  Patient : %s %s\n", patients[idx].prenom, patients[idx].nom);
    if (confirmer_action("Confirmer la suppression ?")) {
        for (int i = idx; i < nb_patients - 1; i++)
            patients[i] = patients[i + 1];
        nb_patients--;
        sauvegarder_auto();
        printf("\n  Patient supprime avec succes.\n");
    }
    pause_entree();
}

/* =============================================
   AFFICHER LISTE COMPLETE
   ============================================= */
void afficher_liste_patients() {
    afficher_titre("LISTE COMPLETE DES PATIENTS");
    if (nb_patients == 0) {
        printf("  Aucun patient enregistre.\n");
        pause_entree();
        return;
    }
    printf("  %-5s %-15s %-15s %-5s %-20s %-15s\n",
           "ID", "NOM", "PRENOM", "AGE", "SERVICE", "TEL");
    printf("  ");
    for (int i = 0; i < 75; i++) printf("-");
    printf("\n");
    for (int i = 0; i < nb_patients; i++) {
        printf("  %-5d %-15s %-15s %-5d %-20s %-15s\n",
               patients[i].id,
               patients[i].nom,
               patients[i].prenom,
               calculer_age(patients[i].date_naissance),
               patients[i].service,
               patients[i].telephone);
    }
    printf("\n  Total : %d patient(s).\n", nb_patients);
    pause_entree();
}

/* =============================================
   AFFICHER DOSSIER COMPLET
   ============================================= */
void afficher_dossier_patient(Patient *p) {
    printf("\n");
    for (int i = 0; i < 60; i++) printf("-");
    printf("\n");
    printf("  DOSSIER MEDICAL N° %d\n", p->id);
    for (int i = 0; i < 60; i++) printf("-");
    printf("\n");
    printf("  Nom complet   : %s %s\n", p->prenom, p->nom);
    printf("  Date nais.    : ");
    afficher_date(p->date_naissance);
    printf("  (Age : %d ans)\n", calculer_age(p->date_naissance));
    printf("  Sexe          : %c\n", p->sexe);
    printf("  Adresse       : %s\n", p->adresse);
    printf("  Telephone     : %s\n", p->telephone);
    printf("  Groupe sanguin: %s\n", p->groupe_sanguin);
    printf("  Service       : %s\n", p->service);
    printf("\n  -- Donnees cliniques --\n");
    printf("  Poids         : %.1f kg\n", p->poids);
    printf("  Taille        : %.2f m\n", p->taille);
    float imc = calculer_imc(p);
    printf("  IMC           : %.2f (%s)\n", imc, categorie_imc(imc));
    printf("  Temperature   : %.1f degC\n", p->temperature);
    printf("  Tension art.  : %.0f/%.0f mmHg\n",
           p->tension_systolique, p->tension_diastolique);
    printf("  Date consult. : "); afficher_date(p->date_consultation); printf("\n");
    printf("  Diagnostic    : %s\n", p->diagnostic);
    for (int i = 0; i < 60; i++) printf("-");
    printf("\n");
}

/* =============================================
   REMPLIR FICHIER AVEC DONNEES EXEMPLES
   ============================================= */
void remplir_fichier_exemple() {
    afficher_titre("DONNEES D'EXEMPLE");
    if (nb_patients > 0 && !confirmer_action("Des patients existent deja. Ecraser ?"))
        return;

    nb_patients = 0;
    Patient exemples[] = {
        {1,"DIALLO","Amadou",{15,3,1985},'M',"Dakar","771234567","O+","Cardiologie",78.0f,1.75f,37.2f,120,80,{10,6,2026},"Hypertension legere"},
        {2,"FALL","Fatou",{22,7,1992},'F',"Thies","772345678","A+","Pediatrie",55.0f,1.60f,38.5f,110,70,{10,6,2026},"Fievre infectieuse"},
        {3,"NDIAYE","Oumar",{5,11,1978},'M',"Saint-Louis","773456789","B-","Chirurgie",95.0f,1.70f,36.8f,145,95,{11,6,2026},"Appendicite aigue"},
        {4,"SECK","Mariama",{18,1,2000},'F',"Ziguinchor","774567890","AB+","Medecine Generale",48.0f,1.65f,37.0f,100,65,{11,6,2026},"Anemie moderee"},
        {5,"MBAYE","Ibrahima",{30,9,1965},'M',"Kaolack","775678901","O-","Cardiologie",110.0f,1.80f,36.5f,160,100,{12,6,2026},"Insuffisance cardiaque"},
        {6,"GAYE","Rokhaya",{12,4,1988},'F',"Dakar","776789012","A-","Gynecologie",62.0f,1.62f,38.9f,115,75,{12,6,2026},"Infection urinaire"},
        {7,"DIOUF","Cheikh",{3,6,1975},'M',"Rufisque","777890123","B+","Neurologie",82.0f,1.78f,37.1f,130,85,{12,6,2026},"Migraine chronique"},
        {8,"BADJI","Aissatou",{25,12,2005},'F',"Kolda","778901234","O+","Pediatrie",30.0f,1.45f,39.2f,100,60,{12,6,2026},"Paludisme"},
    };

    int n = sizeof(exemples) / sizeof(Patient);
    for (int i = 0; i < n; i++)
        patients[nb_patients++] = exemples[i];

    enregistrer_patients();
    printf("  %d patients charges avec succes.\n", nb_patients);
    pause_entree();
}
