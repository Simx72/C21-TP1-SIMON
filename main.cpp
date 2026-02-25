#include <cctype>
#include <cmath>
#include <conio.h>
#include <cstddef>
#include <cstdint>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <windows.h>

#include "cvm_23.h"

using namespace std;

const size_t CLIENTS_MAX = 70;                              // nombre maximal de clients
const size_t COMPTES_MAX = 3;                               // nombre de comptes par client

const double MARGE_CREDIT_MAX =
10000;                                                      // marge de crédit maximun d'un compte du client
const double SOLDE_COMPTE_MAX =
1000000;                                                    // maximun à ne pas dépasser dans un compte d'un client

enum class Commandes {
  AJOUTER,
  AFFICHER,
  DEPOSER,
  RETIRER,
  VIRER,
  LISTER,
  SUPPRIMER,
  QUITTER,
  INCONNUE
};                                                         // à compléter avec les autres commandes...
using Cmd = Commandes;

struct Nom                                                  // nom d'un client
{
  string prenom;
  string nom;
};

struct Adresse                                              // adresse d'un client
{
  string noCivique;
  string rue;
  string ville;
  string codePostal;
};

struct Personne                                             // informations personnelles d'un client
{
  Nom nom;
  Adresse adresse;
  string telephone;
  string nas;
};

struct Compte                                               // un compte d'un client
{
  double solde;
  double margeCredit;
};

struct Client                                               // informations relatives à un client
{
  Personne info;
  Compte comptes[COMPTES_MAX];
  time_t date;                                              // date d'ajout du client
};

struct Banque                                               // La banque de clients
{
  size_t cpt = 0;                                           // cpt: compteur de client [0..CLIENTS_MAX]
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
         size_t p = 2);

// Mes déclarations des fonctions

string recupererString(string question);
double recupererArgent(string question, double min, double max);
void printDate(time_t time);
bool ajouterClient(Banque &b, const Client& c);

// Mes définitions des fonctions

string recupererString(string question) {
  const uint32_t width = 19;
  string reponse;
  cout << left << setw(width) << question << " : ";
  struct { size_t x, y; } pos = { wherex(), wherey() };
  do {
    gotoxy(pos.x, pos.y);
    clreol();
    getline(cin, reponse);
  } while (reponse.empty());
  return reponse;
};

double recupererArgent(string question, double min, double max) {
  const uint32_t width = 19;
  double reponse = 0.0;
  cout << left << setw(width) << question << " : ";
  size_t x = wherex(), y = wherey();
  bool result = false;
  do {
    gotoxy(x, y);
    clreol();
    gotoxy(x, y);
    io_clean();
    gotoxy(x, y); // it works, dont question my methods, but my results
    result = (bool) (cin >> reponse);
    continue;
  } while (cin.fail() || !result || cin.bad() || (reponse > max) || (reponse < min));
  reponse = io_round(reponse, 2);

  gotoxy(x, y);
  clreol();

  cout << fixed << reponse << endl;
  return reponse;
}

void printDate(time_t t) {
  struct tm timeinfo;
  localtime_s(&timeinfo, &t);
  cout << put_time(&timeinfo, "%d/%m/%Y");
}

bool ajouterClient(Banque &b, const Client& c) {
  if (b.cpt < CLIENTS_MAX) {
    b.clients[b.cpt] = c;
    b.cpt++;
    return true;
  } else {
    return false;
  }
}

bool questionOuiNon(string question) {
  int x = wherex(), y = wherey();
  while(true) {
    gotoxy(x, y);
    clreol();
    gotoxy(x, y);
    io_clean();
    gotoxy(x, y);
    cout << question << " (O/N) ";
    int ch = _getch();
    if (ch == 'O') {
      return true;
    } else if (ch == 'N') {
      return false;
    }/* else {
      continue;
    }*/
  };
}

/*
 * Suggestion de fonctions
 * La banque est créée dans main().
 * Aucune variable globale n’est permise.
 * Les fonctions doivent donc recevoir la banque (b) en paramètre,
 * par référence (Banque& ou const Banque& selon le cas).
 *
 * Exemples :
 * size_t lireNoClientValide(const Banque& b);
 * size_t lireNoCompteValide(const Client& client);
 * double lireMontantValide(double maxMontant);
 * void afficherComptesClient(const Client& client);
 */

// écrire ici toutes vos déclarations de fonctions ...
// ...

/* ------------------------------------- */
/* FONCTIONS TRÈS GÉNÉRALES DU PROGRAMME */
/* ------------------------------------- */

void io_bip() { Beep(200, 300); }

void io_clean()                                             // pour vider les 2 tampons d'input
{
  cin.clear();                                              // s'assure que le cin est remis en marche
  // your function didn't work and it's not standard
  // https://www.geeksforgeeks.org/cpp/how-to-use-cin-fail-method-in-cpp/
  cin.ignore(numeric_limits<streamsize>::max(), '\n');      // vide le tampon du cin
  while (_kbhit())
    (void)_getch();                                           // vide le tampon de la console

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
         size_t p)                                                 // tous les montants lus devront être arrondis à 2 décimales
// avec cette fonction (v:valeur et p:précision)
{                                                           // ex: montant = io_round(montant,2);
  double e = pow(10, p);
  return round(v * e) / e;
}

/* ----------------------------------------------------------------------- */
/* FONCTIONS GÉNÉRALES POUR L'INTERFACE USAGER (UI) EN LECTURE OU ÉCRITURE */
/* ----------------------------------------------------------------------- */

void afficherMenu() {
  const size_t indent = 18;

  //  options
  int optionsMenu[8];
  optionsMenu[(size_t)Cmd::AJOUTER] = '1';
  optionsMenu[(size_t)Cmd::AFFICHER] = '2';
  optionsMenu[(size_t)Cmd::DEPOSER] = '3';
  optionsMenu[(size_t)Cmd::RETIRER] = '4';
  optionsMenu[(size_t)Cmd::VIRER] = '5';
  optionsMenu[(size_t)Cmd::LISTER] = '6';
  optionsMenu[(size_t)Cmd::SUPPRIMER] = '7';
  optionsMenu[(size_t)Cmd::QUITTER] = 'Q';

  // textes a montrer
  char const * textesMenu[9];
  textesMenu[(size_t)Cmd::AJOUTER] = "Ajouter un client";
  textesMenu[(size_t)Cmd::AFFICHER] = "Afficher les informations d'un client";
  textesMenu[(size_t)Cmd::DEPOSER] = "Deposer";
  textesMenu[(size_t)Cmd::RETIRER] = "Retrait";
  textesMenu[(size_t)Cmd::VIRER] = "Virement";
  textesMenu[(size_t)Cmd::LISTER] = "Lister les clients et leur credit actuel";
  textesMenu[(size_t)Cmd::SUPPRIMER] = "Supprimer un client";
  textesMenu[(size_t)Cmd::QUITTER] = "Quitter";

  clrscr();

  cout << left;
  cout << setw(indent) <<  "" << "BANQUE CVM - Succ C21\n\n\n";

  for (size_t i = 0; i < 8; i++) {
    cout << setw(indent) << "";
    cout << (char) optionsMenu[i] <<  ". ";
    cout << textesMenu[i];
    cout << "\n\n";
  }

  cout << "\n\n\n";
  cout << setw(indent) << "" << "Entrez votre choix: ";

}

Commandes lireChoixMenu() {
  Commandes cmd = Cmd::INCONNUE;                            // commande par défaut

  char c;

  do {
    c = toupper(_getch());
    switch (c) {
      // clang-format off
      case '1': cmd = Cmd::AJOUTER; break;
      case '2': cmd = Cmd::AFFICHER; break;
      case '3': cmd = Cmd::DEPOSER; break;
      case '4': cmd = Cmd::RETIRER; break;
      case '5': cmd = Cmd::VIRER; break;
      case '6': cmd = Cmd::LISTER; break;
      case '7': cmd = Cmd::SUPPRIMER; break;
      case 'Q': cmd = Cmd::QUITTER; break;
      default: cmd = Cmd::INCONNUE; break;
      // clang-format on
    }
  } while (cmd == Cmd::INCONNUE);
  /*
   *  FAIRE
   *
   *  lire une touche (cmd?)
   *
   *  TANT QUE (cmd == Cmd::inconnue)
   */

  return cmd;
}

/* ------------------------------------------------------------ */
/* LES FONCTIONS OBLIGATOIRES POUR CHAQUE COMMANDE DU PROGRAMME */
/* ------------------------------------------------------------ */

void cmd_ajouter(Banque & b)
{
  clrscr();
  cout << "CMD - ajouter un client\n\n";
  cout << "Creation d'un client #1\n\n";

  // Créer un client temporaire
  Client client = {};

  // Demander les informations
  client.info.nom.prenom = recupererString("Prenom");
  client.info.nom.nom = recupererString("Nom");
  cout << "\n";
  client.info.adresse.noCivique = recupererString("Numero civique");
  client.info.adresse.rue = recupererString("Rue");
  client.info.adresse.ville = recupererString("Ville");
  client.info.adresse.codePostal = recupererString("Code postal");
  client.info.telephone = recupererString("Telephone");
  cout << "\n";
  client.info.nas = recupererString("No d'assurance sociale");
  cout << "\n";
  for (uint8_t i = 0; i < 3; i++) {
    client.comptes[i].margeCredit = recupererArgent(
      "Marge de credit du compte #" + to_string(i + 1)
      + " (Max de 10000.00 $)", 0,  10000.0
    );
    client.comptes[i].solde = 0;
  }

  // Prendre la date actuelle
  client.date = time(nullptr);
  cout << "Date de creation du dossier: ";
  printDate(client.date);
  cout << "\n\n";

  // Save ?
  bool enregistrer = questionOuiNon("Enregistrer? ");
  if (enregistrer) {
    ajouterClient(b, client);
  }
}

void cmd_afficher(/* Paramètres ? */) {
  clrscr();

  cout << "Vous etes dans Afficher";

  _getch();
}

void cmd_deposer(/* Paramètres ? */) {
  clrscr();

  cout << "Vous etes dans Deposer";

  _getch();
}

void cmd_retirer(/* Paramètres ? */) {
  clrscr();

  cout << "Vous etes dans Retirer";

  _getch();
}

void cmd_virer(/* Paramètres ? */) {
  clrscr();

  cout << "Vous etes dans Virer";

  _getch();
}

void cmd_lister(/* Paramètres ? */) {
  clrscr();

  cout << "Vous etes dans Lister";

  _getch();
}

void cmd_supprimer(/* Paramètres ? */) {
  clrscr();

  cout << "Vous etes dans Supprimer";

  _getch();
}

void cmd_quitter(/* Paramètres ? */) {
  clrscr();
  gotoxy(10,  20);
  cout <<  "Au revoir!";
  Sleep(1000);
}

/* ---------------------- */
/* LA FONCTION PRINCIPALE */
/* ---------------------- */

int main() {
  // permet de faire un 'cout' avec les accents directement
  setcp(1252);
  // tous les montants sont affichés avec une précision à 2
  cout << fixed << setprecision(2);

  Cmd cmd = Cmd::INCONNUE;

  Banque b;                                                 // cout << b.cpt;    ==> afficherait le nombre actuel de client

  do {
    afficherMenu();
    cmd = lireChoixMenu();

    cout << (int)cmd;

    switch (cmd) {
      case Cmd::AJOUTER:      cmd_ajouter(b); break;
      case Cmd::AFFICHER:     cmd_afficher(); break;
      case Cmd::DEPOSER:      cmd_deposer(); break;
      case Cmd::RETIRER:      cmd_retirer(); break;
      case Cmd::VIRER:        cmd_virer(); break;
      case Cmd::LISTER:       cmd_lister(); break;
      case Cmd::SUPPRIMER:    cmd_supprimer(); break;
      case Cmd::QUITTER:      cmd_quitter(); break;
      case Cmd::INCONNUE: /* Pas de commande */ break;
    }

  } while (cmd != Cmd::QUITTER);
}
