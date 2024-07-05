enum Color {RED, BLACK};

//Criando a estrutura para a árvore
typedef struct Node
{
    int iPayload;
    Node* ptrLeft;
    Node* ptrRight;
    Node* ptrParent;
    
    Color color;
} Node;

Node* insertNodeDESBALANCEADO(Node*, int);
Node* createNode(int);
Node* insertNode(Node*, int);
void traverseInOrder(Node*);

void rotateRight(Node*&, Node*&);
void rotateLeft(Node*&, Node*&);
void corrigeInsert(Node*&, Node*&);

Node* lesserLeaf(Node*);
Node* biggerLeaf(Node*);
Node* searchNode(Node*, int);
int treeHeight(Node*);

void removeNode(Node*&, int);
Node* substituiNode(Node*, Node*);
void transplantaNode(Node*&, Node*, Node*);

