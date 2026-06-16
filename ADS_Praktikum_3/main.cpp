/*************************************************
 * ADS Praktikum 1.2
 * main.cpp
 *
 *************************************************/
#define CATCH_CONFIG_RUNNER
#include "Tree.h"
#include "catch.h"
#include <iostream>

using namespace std;


//Meine Methoden, bis auf print Level Methode. Kann ich jetzt was ändern?

///////////////////////////////////////
// Hilfsmethoden fürs Menü hier:

/***************************
 ** Vorgegebene  Funktion **
 ***************************
   "mainscreen_addTreeCSV"

Importiert CSV Datei in bestehenden Baum.
Bei Aufruf in der main() Methode, muss der Pointer auf den Anker des Baums, als Parameter übergeben werden.
Es wird die im gleichen Verzeichnis liegende Datei "ExportZielanalyse.csv" geladen.
****************************/

void mainscreen_addTreeCSV(Tree*& ref)
{
	char j;
	cout << "+ Moechten Sie die Daten aus der Datei ExportZielanalyse.csv "
		"importieren(j / n) ? >";
	cin >> j;
	if (j == 'j')
	{
		ifstream csvread;
		csvread.open("ExportZielanalyse.csv", ios::in);
		if (!csvread.is_open())
		{
			cout << "Fehler beim Lesen!" << endl;
			return;
		}
		else
		{
			string name, age, postcode, income;

			while (!csvread.eof())
			{
				getline(csvread, name, ';');
				getline(csvread, age, ';');
				getline(csvread, income, ';');
				getline(csvread, postcode, '\n');
				ref->addNode(name, stoi(age), stod(income), stoi(postcode));
			}
			csvread.close();
		}
		cout << "+ Daten wurden dem Baum hinzugefuegt." << endl;
	}
}

//
///////////////////////////////////////
int main()
{

	int result = Catch::Session().run();
	std::cout << "============================================" << endl;
	std::cout << "ADS - ELK - Stack v1.9, by 25th Bam " << std::endl;
	std::cout << "============================================" << endl;
	///////////////////////////////////////
	// Ihr Code hier:
	Tree tree1;
	Tree* tree_ptr = &tree1;
	bool run = true;
	while (run)
	{
		std::cout << "\n\n============================================" << endl;
		std::cout << "1) Datensatz einfuegen, manuell" << std::endl;
		std::cout << "2) Datensatz einfuegen, CSV Datei" << std::endl;
		std::cout << "3) Suchen" << std::endl;
		std::cout << "4) Ausgabe in Level-Order" << std::endl;
		std::cout << "5) Ausgabe in Level-Order (mit Niveauauswahl)" << std::endl;
		std::cout << "6) Beenden" << std::endl;
		std::cout << "============================================" << endl;
		std::cout << "?> ";

		string s;
		int selection;
		while (true) {
			std::getline(cin, s);
			try {
				selection = stoi(s);
				break;
			}
			catch (const invalid_argument& e) {
				std::cout << "Ungueltige Auswahl, bitte nochmal eingeben." << std::endl;
				cin.clear();
			}
		}
		int level_eingabe = 0;
		switch (selection)
		{
		//
		case 1:
		{
			std::cout << "+ Bitte geben Sie den Datensatz ein: " << std::endl;
			std::cout << "Name ?> ";
			string Name;
			std::getline(cin, Name);
			string tmp;
			int Age;
			while (true)
			{
				std::cout << "Alter ?> ";
				std::getline(cin, tmp);
				try{
					Age = stoi(tmp);
					break;
				}
				catch (const invalid_argument& e){
					std::cout << "Ungueltiges Alter, bitte nochmal eingeben." << std::endl;
				}
			}
			double Income;
			while (true)
			{
				std::cout << "Einkommen ?> ";
				std::getline(cin, tmp);
				try
				{
					Income = stod(tmp);
					break;
				}
				catch (const invalid_argument& e) {
					std::cout << "Ungueltiges Einkommen, bitte nochmal eingeben." << std::endl;
				}
			}
			int PostCode;
			while (true)
			{
				std::cout << "PLZ ?> ";
				std::getline(cin, tmp);
				try{
					PostCode = stoi(tmp);
					break;
				}
				catch (const invalid_argument& e) {
					std::cout << "Ungueltige PLZ, bitte nochmal eingeben." << std::endl;
				}
			}
			tree1.addNode(Name, Age, Income, PostCode);
			std::cout << "+ Ihr Datensatz wurde eingefuegt." << std::endl;
			break;
		}
		
		case 2: //Input CSV Datei
			mainscreen_addTreeCSV(tree_ptr);
			break;

		case 3: //Suchen
		{
			std::cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << std::endl;
			string tmp;
			std::cout << "Name ?>";
			std::getline(cin, tmp);
			if (tree1.searchNode(tmp) == false)
			{
				std::cout << "Keine Datensaetze mit passendem Namen gefunden" << std::endl;
			}
			break;
		}
		case 4: //LevelOrder Alle
		{
			std::cout << "Ausgabenreihenfolge in Levelorder:" << std::endl;
			tree1.printAll();
			tree1.printLevelOrder();
			break;
		}
		case 5: //LevelOrder nach Niveau
		{
			std::cout << "Ausgabe in Levelorder (mit Niveauauswahl):\n?>";
			while (true)
			{

				cin >> level_eingabe;
				if (!cin.fail())
				{
					break;
				}
				else
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "[Falsche Eingabe] Bitte geben Sie eine Zahl ein.\n";
				}

			}
			tree1.printLevelOrder(level_eingabe);
			break;
		}
		case 6: //Beenden
		{
			run = false;
			std::cout << "\n+Das Programm wird beendet.\n";
			break;
		}
		default:
		{
			std::cout << "Keine Auswahl mit dieser Nummer." << std::endl;
			break;
		}
		}
	}
	//
	///////////////////////////////////////
	return 0;
}
