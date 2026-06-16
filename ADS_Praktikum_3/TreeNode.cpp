/*************************************************
 * ADS Praktikum 1.2
 * TreeNode.cpp
 * Erweiterung um Hilfsfunktionen gestattet.
 *************************************************/
#include "TreeNode.h"
#include <iostream>
#include <string>
#include <iomanip>


////////////////////////////////////
// Ihr Code hier:

TreeNode::TreeNode(int    nNodePos,
                   int    id,
                   string name,
                   int    alter,
                   double einkommen,
                   int    plz)
{
    this->m_NodeOrderID	= nNodePos;
    this->m_NodeChronologicalID = id;
    this->m_Name = name;
    this->m_Age	= alter;
    this->m_Income = einkommen;
    this->m_PostCode = plz;
    this->m_left = nullptr;
    this->m_right = nullptr;
}

void TreeNode::print(){

    std::cout.width(3);
    std::cout << this->getNodeChronologicalID() << "|";
    std::cout.width(19);
    std::cout << this->getName() << "|";
    std::cout.width(5);
    std::cout << this->getAge() << "|";
    std::cout.width(9);
    std::cout << this->getIncome() << "|";
    std::cout.width(9);
    std::cout << this->getPostCode() << "|";
    std::cout.width(7);
    std::cout << this->getNodeOrderID();
}

//neu:

