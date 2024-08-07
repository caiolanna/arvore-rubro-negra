#include <iostream>
#include "RBtree.h"

using namespace std;

//Criando um novo nó
Node* createNode(int iValue)
{
    //usando malloc para alocar memória
    Node* tmp = (Node*) malloc(sizeof(Node));
    
    //codigo de erro caso nao consigo alocar memória.
    if (tmp == nullptr)
    {
        cerr << "Erro em createNode: malloc" << endl;
        exit(1);
    }
    
    tmp->iPayload = iValue;
    tmp->ptrLeft = nullptr;
    tmp->ptrRight = nullptr;
    tmp->ptrParent=nullptr;
    
    tmp->color = RED; // sempre começa em RED.
    
    return tmp;
}


Node* insertNode(Node* root, int iData)
{
    Node* newNode = createNode(iData); //cria o no que vai ser inserido.
    if (root == nullptr)
    {
        newNode->color = BLACK; //A raiz é sempre Preta.
        return newNode;
    }

    Node* ParentTemp = nullptr;
    Node* temp = root;
    
    while(temp != nullptr)
    {   
        //dessa forma sempre salvamos o ponteiro anterior a temp como ParentTemp.
        ParentTemp = temp;
        if (iData < temp->iPayload)
        {
            temp = temp->ptrLeft;
        } else {temp = temp->ptrRight;}
        
    }
    
    //Agora apontamos pro ponteiro anterior
    newNode->ptrParent = ParentTemp;
    
    if (iData < ParentTemp->iPayload)
        ParentTemp->ptrLeft = newNode;
    else
        ParentTemp->ptrRight = newNode;
    
    
    corrigeInsert(root, newNode);  // FUNÇÃO QUE CORRIGE A INSERÇÃO PARA NAO QUEBRAR AS REGRAS DA RBtree.
    return root;

} 


//travessia inorder com recursão.
void traverseInOrder(Node* ptrStartingNode)
{
    if (ptrStartingNode != nullptr)
    {
        traverseInOrder(ptrStartingNode->ptrLeft);
        cout << " " << ptrStartingNode->iPayload;
        traverseInOrder(ptrStartingNode->ptrRight);
    }
}



//Encontrar o nó mínimo.
Node* lesserLeaf(Node* startingNode)
{
    Node* ptrCurrent = startingNode;
    
    //Caminha na árvore indo pra esquerda
    while (ptrCurrent && ptrCurrent->ptrLeft != nullptr) ptrCurrent = ptrCurrent->ptrLeft;
    
    cout << "O menor nó é : " << ptrCurrent->iPayload << endl;
    return ptrCurrent;
}

//Encontrar o nó maximo.
Node* biggerLeaf(Node* startingNode)
{
    Node* ptrCurrent = startingNode;
 
    //Caminha na árvore indo pra direita.
    while (ptrCurrent && ptrCurrent->ptrRight != nullptr) ptrCurrent = ptrCurrent->ptrRight;
    
    cout << "O maior nó é : " << ptrCurrent->iPayload << endl;
    return ptrCurrent;
}

//Encontrar um nó específico de forma recursiva
Node* searchNode(Node* startingNode, int iData)
{
    if(startingNode == nullptr) return nullptr;
    else if(iData == startingNode->iPayload) return startingNode;
    else if(iData < startingNode->iPayload) return searchNode(startingNode->ptrLeft, iData);
    else return searchNode(startingNode->ptrRight, iData);
}

//Econtrar altura de forma recursiva.
int treeHeight(Node* startingNode)
{
    if (startingNode == nullptr) return 0;
    else
    {
        int iLeftHeight = treeHeight(startingNode->ptrLeft);
        int iRightHeight = treeHeight(startingNode->ptrRight);
        
        return max(iLeftHeight, iRightHeight) + 1;
    }
}





void rotateLeft(Node*& root, Node*& modifiedNode) 
{
    Node* modifiedNodeRight = modifiedNode->ptrRight; //Armazena o filho direito do nó
    modifiedNode->ptrRight = modifiedNodeRight->ptrLeft;

    if (modifiedNodeRight->ptrLeft != nullptr) 
    {
        modifiedNodeRight->ptrLeft->ptrParent = modifiedNode;
    }

    modifiedNodeRight->ptrParent = modifiedNode->ptrParent;
    
    //ve se o nó que estamos modificando era a raiz, ou seja ptrParent == nullptr;
    if (modifiedNode->ptrParent == nullptr) 
    {
        root = modifiedNodeRight;
    } else if (modifiedNode == modifiedNode->ptrParent->ptrLeft) //Vê se ele era o filho esquerdo do pai
    {
        modifiedNode->ptrParent->ptrLeft = modifiedNodeRight;
    } else 
    {
        modifiedNode->ptrParent->ptrRight = modifiedNodeRight;
    }

    modifiedNodeRight->ptrLeft = modifiedNode;
    modifiedNode->ptrParent = modifiedNodeRight;
}

void rotateRight(Node*& root, Node*& modifiedNode) 
{
    Node* modifiedNodeLeft = modifiedNode->ptrLeft; // Armazena o filho esquerdo de modifiedNode.
    modifiedNode->ptrLeft = modifiedNodeLeft->ptrRight;

    if (modifiedNodeLeft->ptrRight != nullptr) 
    {
        modifiedNodeLeft->ptrRight->ptrParent = modifiedNode;
    }

    modifiedNodeLeft->ptrParent = modifiedNode->ptrParent;
    
    //ve se o nó que estamos modificando era a raiz, ou seja ptrParent == nullptr;
    if (modifiedNode->ptrParent == nullptr) 
    {
        root = modifiedNodeLeft;
    } else if (modifiedNode == modifiedNode->ptrParent->ptrLeft) //se modifiedNode era o filho esquerdo atualiza o ponteiro esquerdo de seu pai.
    {
        modifiedNode->ptrParent->ptrLeft = modifiedNodeLeft;
    } else 
    {
        modifiedNode->ptrParent->ptrRight = modifiedNodeLeft;
    }

    modifiedNodeLeft->ptrRight = modifiedNode;
    modifiedNode->ptrParent = modifiedNodeLeft;
}

void corrigeInsert(Node*& root, Node*& modifiedNode) 
{
    //loop continua enquando o pai de modifiedNode não for preto.
    while (modifiedNode != root && modifiedNode->ptrParent->color == RED) 
    {
        Node* parentPtr = modifiedNode->ptrParent; //armazena o pai de modifiedNode.
        Node* grandParentPtr = parentPtr->ptrParent;//armazena o vô de modifiedNode.
        
        //verificar se o nó pai é filho esquerdo.
        if (parentPtr == grandParentPtr->ptrLeft) 
        {
            Node* unclePtr = grandParentPtr->ptrRight;

            if (unclePtr != nullptr && unclePtr->color == RED) 
            {
                grandParentPtr->color = RED;
                parentPtr->color = BLACK;
                unclePtr->color = BLACK;
                modifiedNode = grandParentPtr;
            } else {
                if (modifiedNode == parentPtr->ptrRight) 
                {
                    rotateLeft(root, parentPtr);
                    modifiedNode = parentPtr;
                }
                rotateRight(root, grandParentPtr);
                swap(parentPtr->color, grandParentPtr->color);
                modifiedNode = parentPtr;
            }
        } else {
            Node* unclePtr = grandParentPtr->ptrLeft; 

            if (unclePtr != nullptr && unclePtr->color == RED) 
            {
                grandParentPtr->color = RED;
                parentPtr->color = BLACK;
                unclePtr->color = BLACK;
                modifiedNode = grandParentPtr;
            } else {
                if (modifiedNode == parentPtr->ptrLeft) 
                {
                    rotateRight(root, parentPtr);
                    modifiedNode = parentPtr;
                }
                rotateLeft(root, grandParentPtr);
                swap(parentPtr->color, grandParentPtr->color);
                modifiedNode = parentPtr;
            }
        }
    }
    root->color = BLACK; //A raiz é sempre preta.
}


//função antiga que foi feita em sala pra inserir no em uma arvore.
Node* insertNodeDESBALANCEADO(Node* startingNode, int iData)
{
    if(startingNode == nullptr)
    {
        return createNode(iData);
    }
    
    if(iData < startingNode->iPayload)
    {
        startingNode->ptrLeft = insertNodeDESBALANCEADO(startingNode->ptrLeft, iData);
    }
    else
    {
        startingNode->ptrRight = insertNodeDESBALANCEADO(startingNode->ptrRight, iData);
    }
    
    return startingNode;
}

void removeNode(Node*& root, int iData)
{
    Node* nodeToRemove = searchNode(root, iData);
    if (nodeToRemove == nullptr)
        return;

    Node* Aux = nodeToRemove;
    Node* x;
    Color originalColor = Aux->color;

    //Garante que o nó nao tem os dos filhos.
    if (nodeToRemove->ptrLeft == nullptr) 
    {
        x = nodeToRemove->ptrRight;
        transplantaNode(root, nodeToRemove, nodeToRemove->ptrRight);
    } 
    else if (nodeToRemove->ptrRight == nullptr) 
    {
        x = nodeToRemove->ptrLeft;
        transplantaNode(root, nodeToRemove, nodeToRemove->ptrLeft);
    } 
    else 
    {
        //caso em que tem os 2 filhos.
        Aux = lesserLeaf(nodeToRemove->ptrRight);
        originalColor = Aux->color;
        x = Aux->ptrRight;

        if (Aux->ptrParent == nodeToRemove)
        {
            if (x != nullptr)
                x->ptrParent = Aux;
        } 
        else 
        {
            transplantaNode(root, Aux, Aux->ptrRight);
            Aux->ptrRight = nodeToRemove->ptrRight;
            Aux->ptrRight->ptrParent = Aux;
        }

        transplantaNode(root, nodeToRemove, Aux);
        Aux->ptrLeft = nodeToRemove->ptrLeft;
        Aux->ptrLeft->ptrParent = Aux;
        Aux->color = nodeToRemove->color;
    }
    //libera memória.
    free(nodeToRemove);

    if (originalColor == BLACK && x != nullptr)
        corrigeInsert(root, x);
}


void transplantaNode(Node*& root, Node* u, Node* v)
{
    //verifica se é a raiz
    if (u->ptrParent == nullptr)
    {
        root = v;
    }
    else if (u == u->ptrParent->ptrLeft)
    {
        u->ptrParent->ptrLeft = v;
    }
    else
    {
        u->ptrParent->ptrRight = v;
    }
    if (v != nullptr)
    {
        v->ptrParent = u->ptrParent;
    }
}

















