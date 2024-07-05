#include <iostream>
#include <chrono>

#include "RBtree.h"

using namespace std;
using namespace std::chrono;

int main()
{
    
    //Exemplo 1, com insertNodeDESBALANCEADO
    Node* root = nullptr;
    
    //utilizanto a biblioteca chrono para medir tempo.
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 100000; i++) 
    {
        root = insertNodeDESBALANCEADO(root, i);
    }
    
    cout << "=================================================================" << endl;
    
    auto end = std::chrono::high_resolution_clock::now() - start;
    long long resultadoNano = std::chrono::duration_cast<std::chrono::nanoseconds>(end).count();
    cout << "tempo de inserção sem balanceamento: " << resultadoNano << endl;
    
    //utilizanto a biblioteca chrono para medir tempo.
    auto start_2 = std::chrono::high_resolution_clock::now();
    
    Node* Testing_searchNode = searchNode(root, 99999); 
    cout << "endereço do nó procurado pela função: " << Testing_searchNode << endl;
    
    auto end_2 = std::chrono::high_resolution_clock::now() - start_2;
    long long resultadoNano_2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_2).count();
    cout << "tempo de busca sem balanceamento: " << resultadoNano_2 << endl;
    
    int AlturaArvore = treeHeight(root);
    cout << "A altura ad árvore é: " << AlturaArvore << endl;
    
    cout << "=================================================================" << endl;
    
    
    //Exemplo 2, com insertNode
    Node* root_2 = nullptr;
    
    //utilizanto a biblioteca chrono para medir tempo.
    auto start_3 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 100000; i++) 
    {
        root_2 = insertNode(root_2, i);
    }
    
    cout << "=================================================================" << endl;
    
    auto end_3 = std::chrono::high_resolution_clock::now() - start_3;
    long long resultadoNano_3 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_3).count();
    cout << "tempo de inserção com balanceamento: " << resultadoNano_3 << endl;
    
    //utilizanto a biblioteca chrono para medir tempo.
    auto start_4 = std::chrono::high_resolution_clock::now();
    
    Node* Testing_searchNode_2 = searchNode(root_2, 99999); 
    cout << "endereço do nó procurado pela função: " << Testing_searchNode_2 << endl;
    
    auto end_4 = std::chrono::high_resolution_clock::now() - start_4;
    long long resultadoNano_4 = std::chrono::duration_cast<std::chrono::nanoseconds>(end_4).count();
    cout << "tempo de busca com balanceamento: " << resultadoNano_4 << endl;
    
    int AlturaArvore_2 = treeHeight(root_2);
    cout << "A altura ad árvore é: " << AlturaArvore_2 << endl;
    
    cout << "=================================================================" << endl;
   
  
    //traverseInOrder(root);

   
    return 0;
}

















