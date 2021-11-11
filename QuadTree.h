#ifndef QUADTREE_QUADTREE_H
#define QUADTREE_QUADTREE_H

#include <fstream>
using namespace std;

enum color {
    black,
    white
};

struct Point {
    int x;
    int y;
};

class Node {

public:

    Node* ul;
    Node* ur;
    Node* dl;
    Node* dr;

    color state;
    Point start;
    Point end;
    Point point;

    Node (Point start, Point end);

    bool childsEmpty ();
    void printAllNodes(fstream &file);
    void printNodesConexiones(fstream &file);

};

class QuadTree {

    Node* root;
    void insert_black (Node* node, Point p);
    void split(Node* node);
    Node* searchRange(Node* node, Point p);
    bool downRange(Node* node, Point p);
    bool leftRange(Node* node, Point p);

public:

    QuadTree (int x, int y);
    void insert (Point p, color c);
    void generatePDF();

};


#endif //QUADTREE_QUADTREE_H
