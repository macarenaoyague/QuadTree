#include "QuadTree.h"

int main() {
    QuadTree quad (1024, 1024);
    quad.insert({2, 5}, black);
    quad.insert({1000, 900}, black);
    quad.generatePDF();
    return 0;
}
