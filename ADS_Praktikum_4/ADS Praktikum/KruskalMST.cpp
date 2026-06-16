#include "KruskalMST.h"

/**
 * Erstellt einen MST zum Graph G mit dem Kruskal Algorithmus
 *
 * \param[in]  G		Kantengewichteter-Graph
 */
KruskalMST::KruskalMST(EdgeWeightedGraph G)
{
	//////////////////////////////////////////////
	//TODO
	//Ausgabe tabletop
	std::cout << std::left << std::setw(8) << "Kante" << "|";
	for (int i = 0; i < G.getV(); i++) {
		std::cout << std::left << std::setw(3) << char(i + 65) << "|";
	}
	std::cout << "\n";
	std::cout << std::string(10 + (G.getV() * 5), '-') << "\n";
	//////
	treeID.resize(G.getV()); //MST maximal so groß wie alle Kanten
	std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq; //sortiert Kantennach gewicht

	std::vector<Edge> e = G.edges();
	for (int i = 0; i < e.size(); i++) pq.push(e[i]); // alle Kanten in pq

	// zu Beginn ist jeder Knoten ein eigener Baum
	for (int i = 0; i < G.getV(); i++) treeID[i] = i;

	while (!pq.empty()) {
		Edge e = pq.top();
		pq.pop();
		int v = e.either();
		int w = e.other(v);
		// Wenn Knoten v und w zu unterschiedlichen Bäumen gehört,
		// können diese mit der Kante e ohne Zykel verbunden werden
		if (treeID[v] != treeID[w]) {
			mst.push_back(e);
			int treeID_w = treeID[w];
			for (int i = 0; i < G.getV(); i++) { // BaumID von v und w
				if (treeID[i] == treeID_w) // angleichen
					treeID[i] = treeID[v];
			}
		}
		
		// Ausgabe Kantenname:
		int either = e.either();
		int other = e.other(e.either());
		int weight = e.weight();
		std::cout << std::left << std::setw(8) << ("(" + std::string(1, char(either + 65)) + "," + std::string(1, char(other + 65)) + "," + std::to_string(weight) + ")") << "|";
		for (int j = 0; j < G.getV(); j++) {
			std::cout << std::left << std::setw(3) << char(65+treeID[j]) << "|";
		}
		std::cout << "\n";
	}
	std::cout << std::string(10 + (G.getV() * 5), '-') << "\n";

	//
	//////////////////////////////////////////////

}

/**
 * Gibt alle Kanten vom MST zurueck
 *
 * \return Vektor mit Kanten des MST
 */
std::vector<Edge> KruskalMST::edges() const
{
	/////////////////////////////////////////////////
	//TODO

	return mst;
	//
	//////////////////////////////////////
}

/**
 * Gibt die Summe aller Gewichte im MST zurueck
 *
 * \return Summe der Gewichte im MST
 */
double KruskalMST::weight() const
{
	///////////////////////////////////
	//TODO
	double totalWeight = 0;
	for (Edge e : mst)
	{
		totalWeight += e.weight();
	}
	return totalWeight;
	//
	////////////////////////////////////
}
