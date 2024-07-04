#include <iostream>
#include <chrono>

#include "RBtree.h"

using namespace std;
using namespace std::chrono;

int main()
{
    
    //Exemplo 3, com insertNode
    Node* root = nullptr;
    root = insertNode(root, 25);
    root = insertNode(root, 7);
    root = insertNode(root, 66);
    root = insertNode(root, 1);
    root = insertNode(root, 11);
    traversePreOrder(root);
    cout << endl;
    lesserLeaf(root);
    biggerLeaf(root);
    
    Node* Testing_searchNode = searchNode(root, 11);
    cout << "endereço do nó procurado pela função: " << Testing_searchNode << endl;
    
    int AlturaArvore = treeHeight(root);
    cout << "A altura ad árvore é: " << AlturaArvore << endl;
   

   
    return 0;
}

















