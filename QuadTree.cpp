#include "QuadTree.h"

Node :: Node (Point start, Point end) : start(start), end(end) {
    ul = nullptr;
    ur = nullptr;
    dl = nullptr;
    dr = nullptr;
    state = white;
}

bool Node ::childsEmpty() {
    if (ul || ur || dl || dr) return false;
    return true;
}

QuadTree :: QuadTree (int x, int y) {
    root = new Node({0, 0}, {x, y});
}

bool QuadTree :: downRange(Node* node, Point p) {
    // TODO arreglar el caso en el que no sea matriz 2^n
    return p.y >= node->start.y && p.y <= (node->start.y + node->end.y)/2;
}

bool QuadTree :: leftRange(Node* node, Point p) {
    // TODO arreglar el caso en el que no sea matriz 2^n
    return p.x >= node->start.x && p.x <= (node->start.x + node->end.x)/2;
}

void QuadTree::insert(Point p, color c) {
    // TODO añadir el caso en el que se actualice el valor del punto
    if (c == white) return;
    insert_black(root, p);
}

Node* QuadTree :: searchRange(Node* node, Point p){
    bool down = downRange(node, p);
    bool left = leftRange(node, p);
    if (down && left)
        return node->dl;
    else if (down && !left)
        return node->dr;
    else if (!down && left)
        return node->ul;
    else
        return node->ur;

}

// TODO verificar bien esto
void QuadTree :: split(Node* node) {
    node->ul = new Node({node->start.x, (node->start.y + node->end.y)/2 + 1}, {(node->start.x + node->end.x)/2, node->end.y});
    node->ur = new Node({(node->start.x + node->end.x)/2 + 1, (node->start.y + node->end.y) + 1}, {node->end.x, node->end.y});
    node->dl = new Node({node->start.x, node->start.y}, {(node->start.x + node->end.x)/2, (node->start.y + node->end.y)/2});
    node->dr = new Node({(node->start.x + node->end.x)/2 + 1, node->start.y}, {node->end.x, (node->start.y + node->end.y)/2});
    Point current = node->point;
    node->state = white;
    insert_black(node, current);
}

void QuadTree::insert_black(Node * node, Point p) {

    if (node->childsEmpty()) {
        // no colision
        if (node->state == white) {
            node->state = black;
            node->point = p;
        }
        // colision
        else {
            //si es que ya existe el punto y no se debe reemplazar
            if (node->start.x == node->end.x && node->start.y == node->end.y) return;
            split(node);
            insert_black(node, p);
        }
    }
    else {
        auto next = searchRange(node, p);
        insert_black(next, p);
    }

}

void Node :: printNodesConexiones(fstream &file){
    if(this->ul != nullptr){
        file << "\"" << this << "\"->";
        file << "\"" << left << "\";\n";
        this->ul->printNodesConexiones(file);
    }
    if(this->ur != nullptr){
        file << "\"" << this << "\"->";
        file << "\"" << right << "\";\n";
        this->ur->printNodesConexiones(file);
    }
    if(this->dl != nullptr){
        file << "\"" << this << "\"->";
        file << "\"" << left << "\";\n";
        this->dl->printNodesConexiones(file);
    }
    if(this->dr != nullptr){
        file << "\"" << this << "\"->";
        file << "\"" << right << "\";\n";
        this->dr->printNodesConexiones(file);
    }
}

void QuadTree::generatePDF() {
    fstream file("graph.vz", fstream::out | fstream::trunc);
    if (file.is_open()) {
        file << "digraph G\n";
        file << "{\n";
        root->printAllNodes(file);
        root->printNodesConexiones(file);
        file << "}\n";
        file.close();
        system("dot -Tpdf graph.vz -o graph.pdf");
    }
}

void Node :: printAllNodes(fstream &file){
    file << "\"" << this << "\" [\n";
    file << "\tlabel = \"" << this->state <<"\\start: "<<this->start.x <<", " << this->start.y << "\\end: "<<this->end.x <<", " << this->end.y <<" \"\n]\n";
    if(this->ul != nullptr){
        this->ul->printAllNodes(file);
    }
    if(this->ur != nullptr){
        this->ur->printAllNodes(file);
    }
    if(this->dl != nullptr){
        this->dl->printAllNodes(file);
    }
    if(this->dr != nullptr){
        this->dr->printAllNodes(file);
    }
}

