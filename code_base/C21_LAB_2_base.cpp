#include <conio.h>
#include <iomanip>
#include <iostream>
#include <string>
#include <windows.h>

#include "cvm_23.h"

using namespace std;

const size_t CLIENTS_MAX = 70; // nombre maximal de clients
const size_t COMPTES_MAX = 3;  // nombre de comptes par client

const double MARGE_CREDIT_MAX =
    10000; // marge de crédit maximun d'un compte du client
const double SOLDE_COMPTE_MAX =
    1000000; // maximun à ne pas dépasser dans un compte d'un client

enum class Commandes {
    AJOUTER,
    QUITTER,
    INCONNUE
}; // à compléter avec les autres commandes...
using Cmd = Commandes;

struct Nom // nom d'un client
{
    string prenom;
    string nom;
};

struct Adresse // adresse d'un client
{
    string noCivique;
    string rue;
    string ville;
    string codePostal;
};

struct Personne // informations personnelles d'un client
{
    Nom nom;
    Adresse adresse;
    string telephone;
    string nas;
};

struct Compte // un compte d'un client
{
    double solde;
    double margeCredit;
};

struct Client // informations relatives à un client
{
    Personne info;
    Compte comptes[COMPTES_MAX];
    time_t date; // date d'ajout du client
};

struct Banque // La banque de clients
{
    size_t cpt = 0; // cpt: compteur de client [0..CLIENTS_MAX]
    Client clients[CLIENTS_MAX];
};

/* ----------------------------------- */
/* LES VARIABLES GLOBALES DU PROGRAMME */
/* ----------------------------------- */

// ATTENTION: les variables globales ne sont pas permises dans ce TP

/* ------------------------------------------ */
/* LES DÉCLARATIONS (PROTOTYPES) DE FONCTIONS */
/* ------------------------------------------ */

void io_bip();
void io_clean();
double
io_round(double v,
         size_t p = 2); // par defaut la précision est à deux décimales (p = 2)

/*
        Suggestion de fonctions
        La banque est créée dans main().
        Aucune variable globale n’est permise.
        Les fonctions doivent donc recevoir la banque (b) en paramètre,
        par référence (Banque& ou const Banque& selon le cas).

        Exemples :
                size_t lireNoClientValide(const Banque& b);
                size_t lireNoCompteValide(const Client& client);
                double lireMontantValide(double maxMontant);
                void afficherComptesClient(const Client& client);
*/

// écrire ici toutes vos déclarations de fonctions ...
// ...

/* ------------------------------------- */
/* FONCTIONS TRÈS GÉNÉRALES DU PROGRAMME */
/* ------------------------------------- */

void io_bip() { Beep(200, 300); }

void io_clean() // pour vider les 2 tampons d'input
{
    cin.clear(); // s'assure que le cin est remis en marche
    cin.ignore(cin.rdbuf()->in_avail()); // vide le tampon du cin
    while (_kbhit())
        (void)_getch(); // vide le tampon de la console

    //  En détail:
    //  cin.rdbuf() retourne le tampon qui contient les caractères déjà tapés
    //  mais non lus
    //  ->in_avail() in_avail() retourne le nombre de caractères
    //  cin.rdbuf()->in_avail() ne lit rien, mais compte simplement combien de
    //  caractères sont encore dans le tampon et retourne ce nombre à cin.ignore
    //  afin qu'il sache combien de caractères il faut supprimer
}

double
io_round(double v,
         size_t p) // tous les montants lus devront être arrondis à 2 décimales
                   // avec cette fonction (v:valeur et p:précision)
{                  // ex: montant = io_round(montant,2);
    double e = pow(10, p);
    return round(v * e) / e;
}

/* ----------------------------------------------------------------------- */
/* FONCTIONS GÉNÉRALES POUR L'INTERFACE USAGER (UI) EN LECTURE OU ÉCRITURE */
/* ----------------------------------------------------------------------- */

void afficherMenu() {
    cout << "Je suis le menu";
    // afficher le menu ...
}

Commandes lireChoixMenu() {
    Commandes cmd = Cmd::INCONNUE; // commande par défaut

    char c;

    do {
        c = _getch();
        switch (c) {
            // clang-format off
            case '1': cmd = Cmd::AJOUTER; break;
            case 'Q': cmd = Cmd::QUITTER; break;
            // clang-format on
        }
    }
    /*
            FAIRE

                    lire une touche (cmd?)

            TANT QUE (cmd == Cmd::inconnue)
    */

    return cmd;
}

/* ------------------------------------------------------------ */
/* LES FONCTIONS OBLIGATOIRES POUR CHAQUE COMMANDE DU PROGRAMME */
/* ------------------------------------------------------------ */

void cmd_ajouter( /* Paramètre ? indice: cette fonction doit avoir accès à la variable b de main */ )
{
    // Écrire le code ici ...
}

void cmd_afficher(/* Paramètres ? */) {
    // Écrire le code ici ...
}

void cmd_deposer(/* Paramètres ? */) {
    // Écrire le code ici ...
}

void cmd_retirer(/* Paramètres ? */) {
    // Écrire le code ici ...
}

void cmd_virer(/* Paramètres ? */) {
    // Écrire le code ici ...
}

void cmd_lister(/* Paramètres ? */) {
    // Écrire le code ici ...
}

void cmd_supprimer(/* Paramètres ? */) {
    // Écrire le code ici ...
}

void cmd_quitter(/* Paramètres ? */) {
    // Écrire le code ici ...
}

/* ---------------------- */
/* LA FONCTION PRINCIPALE */
/* ---------------------- */

int main() {
    setcp(1252); // permet de faire un 'cout' avec les accents directement
    cout << fixed
         << setprecision(
                2); // tous les montants sont affichés avec une précision à 2

    Cmd cmd = Cmd::INCONNUE;

    Banque b; // cout << b.cpt;    ==> afficherait le nombre actuel de client
    do {
        afficherMenu();
        cmd = lireChoixMenu();

        switch (cmd) {
        case Cmd::AJOUTER:
            cmd_ajouter(
                /* cette fonction doit avoir accès à la variable b de main */);
            break;

            //...

        case Cmd::QUITTER:
            cmd_quitter();
            break;
        }

    } while (cmd != Cmd::QUITTER);
}
