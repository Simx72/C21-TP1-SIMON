#include <iostream>
#include <conio.h>
#include <string>

using namespace std;

// EXEMPLE POUR AFFICHER LA DATE, L'HEURE ET LE JOUR DE LA SEMAINE

int main ()
{
	string jours[] = { "dimanche", "lundi", "mardi", "mercredi", "jeudi", "vendredi", "samedi" };

	time_t secondes = time(NULL);		// obtenir la date et l'heure sous forme de secondes écoulées depuis 01/01/1970
	cout << secondes << endl;
	//tm date;							// tm est une structure de windows pour ranger les informations temporelle
	//localtime_s(&date, &secondes);		// pour obtenir les informations temporelle à partir des secondes
	//
	//// jj-mm-aaaa
	//cout << "\n\n";
	//cout << "date     : " << date.tm_mday << "-" << date.tm_mon + 1 << "-" << date.tm_year + 1900 << "\n\n";

	//// hh:mm:ss
	//cout << "heure    : " << date.tm_hour << ":" << date.tm_min << ":" << date.tm_sec << "\n\n";

	//// jour
	//cout << "jour     : " << jours[date.tm_wday] << "\n\n";

	//// secondes
	//cout << "secondes : " << secondes << " (depuis le 1 janvier 1970)" ;

	_getch();
}