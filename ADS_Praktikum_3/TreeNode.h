/*************************************************
 * ADS Praktikum 1.2
 * TreeNode.h
 * Erweiterung um Hilfsattribute und -funktionen gestattet, wenn erforderlich.
 *************************************************/
#pragma once
#include <string>

using namespace std;

class TreeNode
{

private:

    int m_NodeOrderID;
    int m_NodeChronologicalID;
    string m_Name;
    int m_Age;
    double m_Income;
    int m_PostCode;
    TreeNode *m_left;
    TreeNode *m_right;

    //neu:
    bool m_red;
    TreeNode* m_parent;

public:
  
    TreeNode(int, int, string, int, double, int);
    void print();

    int getNodeOrderID() const { return m_NodeOrderID; }
    void setNodeOrderID(int NodeOrderID) { m_NodeOrderID = NodeOrderID; }

    int getNodeChronologicalID() const { return m_NodeChronologicalID; }
    void setNodeChronologicalID(int NodeChronologicalID) { m_NodeChronologicalID = NodeChronologicalID; }

    string getName() const { return m_Name; }
    void setName(string Name) { m_Name = Name; }

    int getAge() const { return m_Age; }
    void setAge(int Age) { m_Age = Age; }

    double getIncome() const { return m_Income; }
    void setIncome(double Income) { m_Income = Income; }

    int getPostCode() const { return m_PostCode; }
    void setPostCode(int PostCode) { m_PostCode = PostCode; }

    TreeNode *getLeft() const { return m_left; }
    void setLeft(TreeNode *left) { m_left = left; }

    TreeNode *getRight() const { return m_right; }
    void setRight(TreeNode *right) { m_right = right; }
  
    //neu:
    bool getRed() const { return m_red; }
    void setRed(bool rb) { m_red = rb; } //rb = red/black

    TreeNode* getParent() const { return m_parent; };
    void setParent(TreeNode* new_parent) { m_parent = new_parent; }
};
