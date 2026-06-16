#define CATCH_CONFIG_RUNNER
#include "catch.h"
#include <iostream>
#include "EdgeWeightedGraph.h"
#include "PrimMST.h"
#include "Graphsearch.h"
#include "KruskalMST.h"
#include "DijkstraSP.h"
using namespace std;

void printGraph(vector<int>); //Bevor eine Print Methode implementiert werden kann muss erstmal eine Einlese Funktion funktionieren

int main() {
	// Starte Unit-Tests
	Catch::Session().run();

	//------------------------------------------------------------------------
	// 1. Ausgabe eines Graphen als Adjazenzliste implementieren
	//------------------------------------------------------------------------
	

	//------------------------------------------------------------------------
	// 2. Suche in Graphen
	//------------------------------------------------------------------------
	// Verwenden Sie hierfür die Vorlagen in Graphsearch.h
	//
	// Beispielaufruf der Tiefensuche: 
	// std::vector<bool> marked;
	// std::vector<int>  edgeTo;
	// bool connected = Graphsearch::DFS(G1, start, marked, edgeTo);



	//------------------------------------------------------------------------
	// 3. Minimaler Spannbaum mit Prim und Kruskal
	//------------------------------------------------------------------------
	// Vorlage für Prim ist die Klasse PrimMST (PrimMST.h + PrimMST.cpp)
	// Vorlage für Kruskal ist die Klasse KruskalMST (KruskalMST.h + KruskalMST.cpp)
	//
	// Beispielaufruf von Prim:
	// PrimMST prim(G, 0);



	//------------------------------------------------------------------------
	// 4. Kuerzeste Wege mit Dijkstra
	//------------------------------------------------------------------------
	// Beispielaufruf von Dijkstra
	//
	// EdgeWeightedDigraph G1_directed("graph1.txt");
	// Dijkstra dijkstra(G1_directed, start);
	// path = dijkstra.pathTo(target);



	//------------------------------------------------------------------------
	// 5. Menü für Benutzereingaben
	//------------------------------------------------------------------------
	// Alle Funktionalitäten aus der Aufgabenstellung muessen umgesetzt werde
	std::cout << "Praktikum 5: Graphenalgorithem:\n\n";
	bool run = true;
	EdgeWeightedGraph G(0);
	EdgeWeightedDigraph DG(0);
	while (run)
	{
		std::cout << "===============================================================================\n"
			<< "1) Graph einlesen\n"
			<< "2) Tiefensuche\n"
			<< "3) Breitensuche\n"
			<< "4) MST nach Prim(Eingabe: Startknoten)\n"
			<< "5) MST nach Kruskal\n"
			<< "6) Kuerzeste Wege nach Dijkstra(Eingabe: Startknoten)\n"
			<< "7) Ausgabe der Adjazenzliste\n"
			<< "8) Kante loeschen\n"
			<< "9) Kante hinzufuegen\n"
			<< "10)Programm beenden\n"
			<< "===============================================================================\n"
			<< " ? >";

		int eingabe;
		cin >> eingabe;
		while (cin.fail() || (eingabe < 1 || eingabe > 10)) {
			cout << "[Falsche Eingabe]\n" << " ? >";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin >> eingabe;
		}
		if ((eingabe > 1 && eingabe < 10) && G.getV() == 0) {
			cout << "[Fehler] Lesen Sie zuerst einen Graph ein!\n";
			continue;
		}

		switch (eingabe) {
			case 1: //Graphen einlesen
			{
				int graph_num = 0;
				cout << "Welcher Graph soll importiert werden? 1, 2 oder 3?\n ? >";
				cin >> graph_num;
				while (cin.fail() || (graph_num < 1 || graph_num > 3)) {
					cout << "[Falsche Eingabe]\n" << " ? >";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> graph_num;
				}
				switch (graph_num) {
					case 1:
					{
						EdgeWeightedGraph G1("graph1.txt");
						EdgeWeightedDigraph DG1("graph1.txt");
						G = G1;
						DG = DG1;
						cout << "+graph1.txt wurde eingelesen\n";
						break;
					}
					case 2:
					{
						EdgeWeightedGraph G2("graph2.txt");
						EdgeWeightedDigraph DG2("graph2.txt");
						G = G2;
						DG = DG2;
						cout << "+graph2.txt wurde eingelesen\n";
						break;
					}
					case 3:
					{
						EdgeWeightedGraph G3("graph3.txt");
						EdgeWeightedDigraph DG3("graph3.txt");
						G = G3;
						DG = DG3;
						cout << "+graph3.txt wurde eingelesen\n";
						break;
					}
				}
				break;
			}
			case 2: //Tiefensuche
			{
				cout << "Bei welchem Knoten moechten Sie anfangen?\nStartknoten > ";
				int v;
				cin >> v;
				while (cin.fail() || (v<0 || v>G.getV())) {
					cout << "[Falsche Eingabe]\n" << "Startknoten > ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> v;
				}
				vector<bool> marked(42,false);
				vector<int> edgeTo(42,-1);
				cout << "Tiefensuche (Depth-First-Search(DFS)) - Startknoten: " << v << endl;
				cout << "Besuchsreihenfolge: " << endl;
				bool zusammenhaengend = Graphsearch::DFS(G,v,marked,edgeTo);
				cout << char(65+v);
				int pos = v; //Anfang bei Startpunkt
				for (int i = 0; i < edgeTo.size(); i++) {
					for(int j = 0; j < edgeTo.size();j++)
						if (edgeTo[j] == pos) {
							cout << " -> " << char(65+j);
							pos = j; //Nachfolger von Nachfolger suchen
					}
				}
				cout << "\n";
				cout << "EdgeTo_Array: " << endl;
				for (int i = 0; i < edgeTo.size(); i++) {
					if (edgeTo[i] == -1) {
						cout << char(65 + i) << " -> " << "- (Startknoten)" << endl;
					}
					else {
						cout << char(65 + i) << " -> " << char(65 + edgeTo[i]) << endl;
					}
				}
				cout << endl << "Marked_Array: " << endl;
				for (int i = 0; i < marked.size(); i++) {
					if (i != v) {
						cout << char(65+i) << " -> " << marked[i] << endl;
					}
					else {
						cout << char(65+i) << " -> " << marked[i] << " (Startknoten)" << endl;
					}
				}
				if (zusammenhaengend) {
					cout << endl << "Graph ist zusammenhaengend" << endl;
				}
				else {
					cout << endl << "Graph ist nicht zusammenhaengend" << endl;
				}
				break;
			}
			case 3: //Breitensuche
			{
				cout << "Bei welchem Knoten moechten Sie anfangen?\nStartknoten > ";
				int v;
				cin >> v;
				while (cin.fail() || (v<0 || v>G.getV())) {
					cout << "[Falsche Eingabe]\n" << "Startknoten > ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> v;
				}
				vector<bool> marked(42, false);
				vector<int> edgeTo(42, -1);
				cout << "Breitensuche (Breadth-First-Search(DFS)) - Startknoten: " << v << endl;
				cout << "Besuchsreihenfolge: " << endl;
				bool zusammenhaengend = Graphsearch::BFS(G, v, marked, edgeTo);
				cout << "EdgeTo_Array: " << endl;
				for (int i = 0; i < edgeTo.size(); i++) {
					if (i != v) {
						cout << i << " -> " << char(65+edgeTo[i]) << endl;
					}
					else {
						cout << i << " -> " <<  "- (Startknoten)" << endl;
					}
				}
				cout << endl << "Marked_Array: " << endl;
				for (int i = 0; i < marked.size(); i++) {
					if (i != v) {
						cout << char(65+i) << " -> " << marked[i] << endl;
					}
					else {
						cout << char(65+i) << " -> " << marked[i] << " (Startknoten)" << endl;
					}
				}
				if (zusammenhaengend) {
					cout << endl << "Graph ist zusammenhaengend" << endl;
				}
				else {
					cout << endl << "Graph ist nicht zusammenhaengend" << endl;
				}
				break;
			}
			case 4: //MST nach Prim
			{
				cout << "Minimaler Spannbaum (MST) nach Prim: " << endl;
				cout << "Startknoten >";
				int v;
				cin >> v;
				while (cin.fail() || (v<0 || v>=G.getV())) {
					cout << "[Falsche Eingabe]\n" << " ? >";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> v;
				}
				PrimMST p(G, v);
				vector<Edge> mst = p.edges();
				cout << "Gewicht: " << p.weight() << endl;
				cout << "Adjazenzliste: " << endl; 


				std::vector<std::vector<Edge>> adjList(mst.size());
				for (int i = 0; i < adjList.size(); i++)
				{
					for (int j = 0; j < mst.size(); j++)
					{
						Edge e = mst[j];
						if (e.either() == i)
						{
							adjList[i].push_back(e); //Füge alle Kanten die im MST mit dem i verbunen sind hinzu
						}
					}
				}

				for (int i = 0; i < adjList.size(); i++)
				{
					if (!adjList[i].empty())
					{
						std::cout << char(65+i);
						std::vector<Edge> temp = adjList[i];
						for (const Edge e : adjList[i])
						{
							int other = e.other(e.either());
							std::cout << "-> " << char(65+other) << "[" << e.weight() << "]";
						}
						std::cout << "\n";
					}
				}
				
				break;
			}
			case 5: //MST nach Kruskal
			{
				///////////////////////////
				cout << "Minimaler Spannbaum (MST) nach Kruskal: " << endl;
				KruskalMST k(G);
				vector<Edge> mst = k.edges();
				cout << "Gesamt Gewicht: " << k.weight() << endl;
				cout << "Adjazenzliste: " << endl;


				std::vector<std::vector<Edge>> adjList(mst.size());
				for (int i = 0; i < adjList.size(); i++)
				{
					for (int j = 0; j < mst.size(); j++)
					{
						Edge e = mst[j];
						if (e.either() == i)
						{
							adjList[i].push_back(e); //Füge alle Kanten die im MST mit dem i verbunden sind hinzu
						}
					}
				}

				for (int i = 0; i < adjList.size(); i++)
				{
					if (!adjList[i].empty())
					{
						std::cout << char(65+i);
						std::vector<Edge> temp = adjList[i];
						for (const Edge e : adjList[i])
						{
							int other = e.other(e.either());
							std::cout << "-> " << char(65+other) << "[" << e.weight() << "]";
						}
						std::cout << "\n";
					}
				}
				break;
			}
			case 6: //Kuerzester Wege nach Dijkstra
			{
				cout << "Von welchem Knoten moechten Sie starten?\n" << "Startknoten > ";
				int s;
				cin >> s;
				while (cin.fail() || (s < 0 || s >= G.getV())) {
					cout << "[Falsche Eingabe]\n Startknoten > ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> s;
				}

				DijkstraSP d(DG, s);

				// Kopfzeile der Tabelle
				cout << "Knoten i  | ";
				for (int i = 0; i < G.getV(); i++) {
					cout << setw(3) << i << " ";
				}
				cout << endl << string(11+ G.getV() * 4, '-') << endl;

				// edgeTo[i] Zeile
				cout << "edgeTo[i] | ";
				for (int i = 0; i < G.getV(); i++) {
					if (i == s) {
						cout << setw(3) << "-" << " ";
					}
					else {
						cout << setw(3) << d.getEdgeTo()[i].from() << " ";
					}
				}
				cout << endl << string(11 + G.getV() * 4, '-') << endl;

				// distTo[i] Zeile
				cout << "distTo[i] | ";
				for (int i = 0; i < G.getV(); i++) {
					if (d.distTo(i) > 1000000000) {
						cout << setw(3) << "x   ";
					}
					else {
						cout << setw(3) << d.distTo(i) << " ";
					}	
				}
				cout << endl << endl;

				cout << "Bitte geben Sie den Knoten ein, zu dem Sie den kuerzesten Pfad angezeigt bekommen wollen:\n" << "Zielknoten >";
				int v;
				cin >> v;
				while (cin.fail() || (v < 0 || v >= G.getV())) {
					cout << "[Falsche Eingabe]\n Zielknoten > ";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> v;
				}

				cout << "Kuerzester Weg (Dijkstra): " << endl;
				cout << "Start:  " << char(65+s) << endl;
				cout << "Ziel:   " << char(65+v) << endl;
				cout << "Pfad:   ";
				for (int i = 0; i < d.pathTo(v).size(); i++) {
					cout << char(65+d.pathTo(v)[i].from()) << " [" << d.pathTo(v)[i].weight() << "] -> ";
				}
				cout << char(65+v) << endl;
				cout << "Kosten: " << d.distTo(v) << endl;
				break;
			}
			case 7: //Ausgabe der Adjazentenliste
			{//65(A)-90(Z)
				cout << "Adjazentenliste:\n";
				for (int i = 0; i < G.getAdj().size(); i++) {
					cout << char(i + 65) << " -> ";
					for (int j = 0; j < G.getAdj(i).size(); j++) {
						cout << char(G.getAdj(i)[j].other(i) + 65) << " [" << G.getAdj(i)[j].weight() << "]";
						if (j < G.getAdj(i).size() - 1)
							cout << " -> ";
					}
					cout << "\n";
				}
				break;
			}
			case 8: //Kante loeschen
			{
				//Eingabe:
				std::cout << "Kante loeschen:\n"
					<< "Welche Kante soll geloescht werden?\nKante zwischen v >";
				int v;
				cin >> v;
				while (cin.fail() || (v < 0 || v >= G.getV())) {
					cout << "[Falsche Eingabe]\n" << "v >";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> v;
				}
				std::cout << "und w > ";
				int w;
				cin >> w;
				while (cin.fail() || (w < 0 || w >= G.getV())) {
					cout << "[Falsche Eingabe]\n" << "w >";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> w;
				}
				//Überprüfen ob vorhanden:
				std::vector<Edge>v_adj = G.getAdj(v);
				std::vector<DirectedEdge>v_adj_directed = DG.getAdj(v);
				bool vorhanden = false;
				bool vorhanden_directed = false;
				for (int i = 0; i < v_adj.size(); i++)
				{
					if (v_adj[i].either() == v && v_adj[i].other(v) == w) {
						vorhanden = G.del_Edge(v_adj[i]);
						vorhanden_directed = DG.del_Edge(v_adj_directed[i]);
					}
				}
				if (vorhanden && vorhanden_directed) {//&& vorhanden_directed
					cout << "+Kante erfolgreich in beiden Graphen geloescht\n";
				}/*
				else if (vorhanden && !vorhanden_directed) {
					cout << "+Kante konnte nur in ungewichteten Graph gelöscht werden.\n"
				}*/
				else{
					std::cout << "[Fehler] zu loeschende Kante ist nicht vorhanden!\n";
				}

				break;
				
			}
			case 9: //Kante hinzufuegen
			{
				std::cout << "Kante hinzufuegen:\n"
					<< "Welche zwei Knoten moechtest du verbinden?\nv >";
				int v;
				cin >> v;
				while (cin.fail() || (v<0 || v>=G.getV())) {
					cout << "[Falsche Eingabe]\n" << "v >";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> v;
				}
				std::cout << "w > ";
				int w;
				cin >> w;
				while (cin.fail() || (w < 0 || w >= G.getV())) {
					cout << "[Falsche Eingabe]\n" << "w >";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> w;
				}
				std::cout << "weight > ";
				int weight;
				cin >> weight;
				while (cin.fail()){
					cout << "[Falsche Eingabe]\n" << "weight >";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> weight;
				}
				std::vector<Edge>v_adj = G.getAdj(v);
				bool schon_vorhanden = false;
				for (int i = 0; i < v_adj.size(); i++)
				{
					if ((v_adj[i].either() == v && v_adj[i].other(v) == w) || (v_adj[i].either() == w && v_adj[i].other(w) == v)) {
						std::cout << "[Fehler] Kante ist bereits vorhanden!\n";
						schon_vorhanden = true;
						break;
					}
				}
				if (!schon_vorhanden) {
					Edge newEdge( v, w, weight);
					DirectedEdge newDirectedEdge(v, w, weight);
					G.add(newEdge);
					DG.add(newDirectedEdge);
					std::cout << "+Neue Kante eingefuegt\n";
				}
				break;
			}
			case 10: //Programm beenden:
			{	
				run = false;
				cout << "+Programm wird beendet\n\n";
				break;
			}
		}
	}
	system("PAUSE");
	return 0;
}

void printGraph(vector<int> kantenliste) { //Viel komplizierter als ich gedacht habe, ist noch nicht fertig
	for (int i = 2; i < kantenliste[1]; i++) {
		std::cout << 'A' + kantenliste[i]<<" -> "<< 'A' + kantenliste[i+1]<<"["<<kantenliste[i+2]<<"]";
	}
}