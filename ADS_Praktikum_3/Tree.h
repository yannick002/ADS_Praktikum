/*************************************************
 * ADS Praktikum 1.2
 * Tree.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include "TreeNode.h"
#include "catch.h"
#include <string>
#include <queue>

using namespace std;

class Tree
{

private:
    ///////////////////////////////////////
    // Ihr Code hier:
    TreeNode * m_anker = nullptr;
    int m_currentNodeChronologicalID;
    void printPreOrder();
    void printInOrder();
    void printPostOrder();
    void printPreOrderHelper(TreeNode *);
    void printInOrderHelper(TreeNode *);
    void printPostOrderHelper(TreeNode *);
    void searchNodeHelper(TreeNode*, string, bool&);
    void printHelper(TreeNode*);
    //neu:
    void balance(TreeNode*);
    bool split4Node(TreeNode*);
    int proofRBCriterionRec(TreeNode*);
    bool rotateTreeRight(TreeNode*);
    bool rotateTreeLeft(TreeNode*);
    //
    ////////////////////////////////////

public:
    ///////////////////////////////////////
    // Ihr Code hier:
    Tree();
    ~Tree();
    bool addNode(string, int, double, int); //Rückgabetyp angepasst
    bool searchNode(string); 
    void printAll();
    //?
    void printLevelOrder();
    //neu:
    void printLevelOrder(int);
    int proofRBCriterion(TreeNode*);

    
    //
    ////////////////////////////////////
    // friend-Funktionen sind für die Tests erforderlich und müssen unangetastet
    // bleiben!
    friend TreeNode* get_anker(Tree& TN);
};
