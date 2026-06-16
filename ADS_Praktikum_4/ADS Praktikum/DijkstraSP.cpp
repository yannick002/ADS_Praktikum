#include <assert.h>
#include "DijkstraSP.h"

/**
 * Füge eine Kante mit minimalen Kosten hinzu, die von einem
 * Baumknoten zu einem Nicht-Baumknoten verläuft und deren
 * Ziel w dem Startknoten s am nächsten ist.
 *
 * \param[in]  G		Kantengewichteter-Digraph
 * \param[in]  v		Zielknoten
 */
void DijkstraSP::relax(EdgeWeightedDigraph G, int v)
{
	//////////////////////////////////////////////
	//TODO

	std::vector<DirectedEdge> edges = G[v];		//vek mit edges von v
	for (DirectedEdge e : edges)
	{
		int w = e.to();							//w = Zielknoten
		if (distToVect[w] > distToVect[v] + e.weight()) //neuer Weg kürzer als alter Weg
		{
			distToVect[w] = distToVect[v] + e.weight();
			edgeTo[w] = e;

			if (pq.contains(w))
			{
				pq.change(w, distToVect[w]);
			}
			else
			{
				pq.push(w, distToVect[w]); //push addierten Knotenwert/Edgewert
			}
		}
	}
	//
	//////////////////////////////////////////
}

/**
 * Fuert den Dijkstra Algorithmus von s, im Graph G aus.
 *
 * \param[in]  G		Kantengewichteter-Digraph
 * \param[in]  s		Startknoten
 */
DijkstraSP::DijkstraSP(EdgeWeightedDigraph G, int s)
{
	//////////////////////////////////
	//TODO
	this->distToVect.resize(G.getV());         //max Diszanz ist Anzahl aller Knoten

	for (int v = 0; v < G.getV(); v++) {
		this->distToVect[v] = DBL_MAX;			//DBL_max == Unendlich
	}
	distToVect[s] = 0.0;						//Startpkt auf null
	pq.push(s, 0.0);
	while (!pq.empty())
	{
		int min_node = pq.top().value;				
		pq.pop();
		// Füge immer eine Kante mit minimalen Pfadkosten zu s hinzu
		relax(G, min_node);
	}
	//
	/////////////////////////////////
}

/**
 * Gibt die Distanz von s zum Knoten v zurueck
 *
 * \param[in]  v		Zielknoten
 * \return Summe der Gewichte auf dem Pfad zu v
 */
double DijkstraSP::distTo(int v) const
{
	/////////////////////////////////
	//TODO
	return this->distToVect[v];
	//
	/////////////////////////////////
	//return 0.0;
}

/**
 * Gibt zurueck ob es einen Pfad zu v von s aus gibt
 *
 * \param[in]  v		Zielknoten
 * \return true, wenn es einen Pfad von s nach v gibt, sonst false
 */
bool DijkstraSP::hasPathTo(int v) const
{
	//////////////////////////////////
	//TODO
	if (this->distToVect[v] != DBL_MAX)
	{
		return true;
	}
	else{
		return false;
	}
	//
	/////////////////////////////////
	
}

/**
 * Gibt den Pfad von s nach v als Vektor zurueck
 *
 * \param[in]  v		Zielknoten
 * \return Vektor mit allen Kanten des Pfades von s nach v
 */
std::vector<DirectedEdge> DijkstraSP::pathTo(int v) 
{
	////////////////////////////////////////
	//TODO

	assert(("Es gibt keinen Pfad von s nach v!", this->hasPathTo(v)));
	//assert(("Vertex is out of bounds!", false));

	std::vector<DirectedEdge> path;
	DirectedEdge e = edgeTo[v];
	while (true)
	{
		path.push_back(e);
		if (edgeTo.count(e.from()) > 0)
		{
			e = edgeTo[e.from()];
		}
		else
		{
			break;
		}
	}

	std::reverse(path.begin(), path.end());

	return path;
	//
	///////////////////////////////////////////
	//return std::vector<DirectedEdge>();
}

std::map<int, DirectedEdge> DijkstraSP::getEdgeTo() {
	return this->edgeTo;
}
