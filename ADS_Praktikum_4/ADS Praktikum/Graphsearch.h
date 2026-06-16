#pragma once
#include "EdgeWeightedDigraph.h"
#include "EdgeWeightedGraph.h"
#include <iostream>

namespace Graphsearch {

	/**
		* Fuehrt eine rekursive Tiefensuche im Graphen G,
		* ab dem Knoten v aus und markiert alle besuchten
		* Knoten in marked.
		* Alle besuchten Knoten werden ausgegeben.
		*
		* \param[in]	 G			Graph
		* \param[in]	 v			Startknoten
		* \param[in/out] marked		Bereits besuchte Knoten
		* \param[in/out] edgeTo		Vektor mit dem Nachfolgeknoten zu jedem Knoten
		*/

	//////////////////////////////////////////
	void DFS_recursive(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {
		marked[v] = true; //Jeden Knoten den wir finden auf true setzten
		for (auto w : G.getAdj(v)){//Wir gehen alle Adjazenten Kanten von V durch und schauen ob die Knoten am anderen Ende schon markiert wurden oder nicht
			if (!marked[w.other(v)]){ //Wenn wir einen Knoten finden der eine Kante zu v hat und noch nicht markiert wird gehen wir hier rein
				edgeTo[w.other(v)] = v; //Speichert den Vorgänger vom letzten Knoten
				/*
				if (edgeTo[v] == -1) {
					std::cout << v;
				}
				else {
					std::cout << " -> " << v;
				}*/
				DFS_recursive(G, w.other(v), marked, edgeTo); 
			}
		}
		return;
	}
	//////////////////////////////////////

	/**
		* Fuehrt eine rekursive Tiefensuche im Graphen g, ab dem Knoten v aus.
		* Alle besuchten Knoten werden ausgegeben.
		* Starterfunktion zu DFS_recursive(EdgeWeigtedGraph, int, std::vector<bool>, std::vector<int>)
		*
		* \param[in]  G			Graph
		* \param[out] marked	Bereits besuchte Knoten
		* \param[out] edgeTo	Vektor mit dem Nachfolgeknoten zu jedem Knoten
		* \param[in]  v			Startknoten
		* \return	  true		Graph ist zusammenhaengend
		*			  false		Graph ist nicht zusammenhaengend
		*/

	//////////////////////////////////////
	bool DFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {
		
		std::vector<int> tmp(G.getV(), -1);
		edgeTo = tmp; //Bei jedem Durchlauf muss edgeTo & marked neu intialisiert werden
		std::vector<bool> tmp2 (G.getV(), false);
		marked = tmp2;
		DFS_recursive(G, v, marked, edgeTo); //Rufe die DFS_recursive Funktion auf
		std::cout << std::endl;
		//Überprüfen:
		for (int i = 0; i < G.getV(); i++) {
			if (marked[i] == false) {
				return false; //Wenn wir irgendwo einen Wert haben der false ist, wissen wir dass der Graph nicht zusammenhängend ist
			}
		}
		return true;
	}
	//////////////////////////////////////

	/**
		* Fuehrt eine iterative Breitensuche im Graphen g, ab dem Knoten v aus.
		* Alle besuchten Knoten werden ausgegeben.
		*
		* \param[in]  G			Graph
		* \param[in]  v			Startknoten
		* \param[out] marked	Gibt an welche Knoten besucht wurden bei der Suche
		* \param[out] edgeTo	Gibt den Nachfolgerknoten eines Knoten an
		* \return	  true		Graph ist zusammenhaengend
		*			  false		Graph ist nicht zusammenhaengend
		*/
	bool BFS(const EdgeWeightedGraph& G, int v, std::vector<bool>& marked, std::vector<int>& edgeTo) {
		/////////////////////////////////
		std::vector<int> tmp(G.getV(), -1);
		edgeTo = tmp;
		std::vector<bool> tmp2(G.getV(), false);
		marked = tmp2;

		std::queue<int> q;
		q.push(v);//Eintrag mit dem besucht wird in die Queue pushen //FIFO Wie bei Levelorder
		marked[v] = true; //Eintrag mit dem besucht wird als True markieren

		while (!q.empty()) {
			v = q.front(); //v wird zum ersten Eintrag in der Queue
			q.pop();
			//Ausgabe Besuchreihenfolge:
			if (edgeTo[v] == -1) {
				std::cout << char(65+v);
			}
			else {
				std::cout << " -> " << char(65+v);
			}

			for (auto w : G.getAdj(v)) { //Für jede Kante die adjazent zu v ist
				if (!marked[w.other(v)]) { //Solange der Knoten am anderen Ende der Kante nicht markiert ist besuchen wir ihn
					edgeTo[w.other(v)] = v; //Dabei speichern wir erst mit welchem Knoten wird den zukünftigen besucht haben
					marked[w.other(v)] = true; //Setzen dann den zukünftigen auf True. Das machen wir damit der Vorgängerknoten in der EdgeTo Liste nicht nochmal verändert werden kann
					//Bsp: Wir besuchen Knoten 3 der eine Kante zu Knoten 2 & 5 hat. Daraufhin arbeiten wir den nächsten Knoten z.B. 7 ab. Dieser hat auch eine Kante zu 2. Wenn wir jetzt alle Knoten die adjazente Kanten zu 7 haben besuchen, finden wir auch die 2 und setzten in der EdgeTo Datei als Vorgänger die 7 obwohl wir die 2 davor mit der 3 gefunden haben.
					q.push(w.other(v)); //Dann natürlich auch alle gefunden Knoten in die Queue packen
				}
			}

		}
		std::cout << std::endl;
		bool print = false; //Print boolean, dann muss man nicht jedes Mal auskommentieren
		if (print) {
			std::cout << std::endl << "Knoten marked edgeTo: " << std::endl;
			for (int i = 0; i < edgeTo.size(); i++) {
				std::cout << char(65+i) << ": " << marked[i] << " " << edgeTo[i] << std::endl;
			}
		}

		for (auto b : marked) { //Schauen ob alle Einträge in marked true sind
			if (!b) {
				return false;
			}
		}
		
		return true;
		//////////////////////////////// Yannick
	}
}
