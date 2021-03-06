/* Test file for 5-4 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#define ElementType BTree
#define MAX_STACK_SIZE 100
#define MAXSIZE 100
#define LEFT 0
#define RIGHT 1
#define IS_FULL(x) ((x)==NULL)?1: 0
#define N 10
#define ElementType thrBiTree
#define dataType char // the type of data of thrtreeNode
// NOV16: It's better to unify two kinds of binary tree definitions 
/* binary tree ADT struct definition
typedef struct treeNode *BTree;
struct treeNode {
    int data;
    BTree left;
    BTree right;
};
*/

/* threaded binary tree ADT struct definition */
typedef struct thrtreeNode *thrBiTree;
struct thrtreeNode {
    dataType data;
    thrBiTree left;
    thrBiTree right;
    bool left_thr;    // true if no left child: left is a thread
    bool right_thr;   // false if has right child: right links a child
};

/* stack ADT struct definition */
typedef struct {
    ElementType *array;
    int top;
    int maxsize;
} Snode;
typedef Snode *Stack;

/* queue ADT struct definition */
struct Node{
    ElementType data;
    struct Node *next;
};

typedef struct {
    struct Node *front;
    struct Node *rear;
    int cursize;
    int maxsize;
} Qnode;
typedef Qnode *Queue;

/* stack ADT methods */
Stack CreateStack(int size);
bool IsFull(Stack S);
bool IsEmpty(Stack S);
void push(Stack S, ElementType item);
ElementType pop(Stack S);
void display(Stack S);

/* queue ADT methods */
Queue CreateQueue(int maxsize);
bool QIsFull(Queue Q);
bool QIsEmpty(Queue Q);
void enqueue(Queue Q, ElementType item);
ElementType dequeue(Queue Q);


/* binary tree traversal
void iter_preorder(BTree root);
void iter_inorder(BTree root);
void iter_postorder(BTree root);
void iter_postorder2(BTree root);

void inorder(BTree ptr);
void preorder(BTree ptr);
void postorder(BTree ptr);

BTree copy(BTree origin);
bool isEqual(BTree t1, BTree t2);
void countleaf(BTree root, int *count);
int iter_countleaf(BTree root);
void swaptree(BTree root);

binary tree creation and helper function
BTree createBTree(char *array, int len);
BTree makenode(char data);
*/
thrBiTree create_sentinel(thrBiTree root);
thrBiTree makethrnode(dataType data);
thrBiTree createthrBiTree(dataType *array, int len);
thrBiTree linkthr_preorder(thrBiTree root, int len);

int main(void)
{
	/*BTree root = (BTree)malloc(sizeof(struct treeNode));
	root->data = 100;

	BTree node1 = (BTree)malloc(sizeof(struct treeNode)); node1->data = 1;
	BTree node2 = (BTree)malloc(sizeof(struct treeNode)); node2->data = 2;
	BTree node3 = (BTree)malloc(sizeof(struct treeNode)); node3->data = 3;
	BTree node4 = (BTree)malloc(sizeof(struct treeNode)); node4->data = 4;
	BTree node5 = (BTree)malloc(sizeof(struct treeNode)); node5->data = 5;
	BTree node6 = (BTree)malloc(sizeof(struct treeNode)); node6->data = 6;
	BTree node7 = (BTree)malloc(sizeof(struct treeNode)); node7->data = 7;
	root->left = node1; root->right = node2;
	node1->left = node3; node1->right = node4;
	node2->left = node5; node2->right = node6;
	node3->left = NULL; node3->right = NULL; node4->left = node7; node4->right = NULL;
	node5->left = NULL; node5->right = NULL; node6->left = NULL; node6->right = NULL;
	node7->left = NULL; node7->right = NULL;

	iter_postorder2(root);
	swaptree(root);
	puts("\n");
	iter_postorder2(root);*/
    char info2[N+1] = "0abcd##e#f";
	thrBiTree testree = createthrBiTree(info2, N+1);
	testree = linkthr_preorder(testree, N+1);
    
	return 0;
}

/* stack ADT methods */
Stack CreateStack(int size)
{
    Stack newS = (Stack)malloc(sizeof(Stack));
    newS->array = (ElementType *)calloc(size, sizeof(ElementType));
    newS->top = -1;
    newS->maxsize = size;
    return newS;
}

bool IsFull(Stack S)
{
    return S->top - 1 == S->maxsize;
}

bool IsEmpty(Stack S)
{
    return S->top == -1;
}

void push(Stack S, ElementType item)
{
    if (IsFull(S))
    {
        fprintf(stderr, "The stack is full.\n");
        exit(EXIT_FAILURE);
    }
    else
        S->array[++(S->top)] = item;
}

ElementType pop(Stack S)
{
    if (IsEmpty(S))
    {
        fprintf(stderr, "The stack is empty.\n");
        exit(EXIT_FAILURE);
    }
    else
        return S->array[(S->top)--];
}

void display(Stack S)
{
    for (int i = 0; i < S->top + 1; i++)
        printf("%d ", S->array[i]);
    putchar('\n');
}

/* queue ADT methods */
Queue CreateQueue(int maxsize)
{
    Queue temp = (Queue)malloc(sizeof(Qnode));
    temp->front = temp->rear = NULL;
    temp->maxsize = maxsize;
    temp->cursize = 0;
    return temp;
}

bool QIsFull(Queue Q)
{
    return Q->cursize == Q->maxsize;
}

bool QIsEmpty(Queue Q)
{
    return Q->front == NULL;
}

void enqueue(Queue Q, ElementType item)
{
    struct Node *rearcell;
    ElementType rearelem = item;
    if (QIsFull(Q))
    {
        printf("The queue is Full.\n");
        exit(1);
    }
        
    else
    {
        rearcell = (struct Node *)malloc(sizeof(struct Node));
        rearcell->data = rearelem;
        if (Q->cursize == 0)
            Q->front = Q->rear = rearcell;
        else
        {
            Q->rear->next = rearcell;
            Q->rear = Q->rear->next;
        }    
        ++Q->cursize;
    }
}

ElementType dequeue(Queue Q)
{
    struct Node *frontcell;
    ElementType frontelem;
    if (QIsEmpty(Q))
    {
        printf("The queue is empty.\n");
        return NULL; 
    }
    else
    {
        frontcell = Q->front;
        frontelem = frontcell->data;
        if (Q->front == Q->rear)
            Q->front = Q->rear = NULL;
        else
            Q->front = Q->front->next;
        free(frontcell);
        --Q->cursize;
        return frontelem;
    }
}

/* binary tree traversal methods
void iter_preorder(BTree root)
{
    Stack S = CreateStack(MAXSIZE);    // create and initialize stack
    BTree tree = root;
    while (tree || !IsEmpty(S))        // using 'while' is more readable than 'for'
    {
        while (tree)
        {
            printf("%c ", tree->data);
            push(S, tree);             // push visited node into stack
            tree = tree->left;         // move all the way to left
        }
        if (!IsEmpty(S))
        {
            tree = pop(S);             // when there's no more left subtree,
            tree = tree->right;        // to the right
        }
    }
}

void iter_inorder(BTree root)
{
    Stack S = CreateStack(MAXSIZE);
    BTree tree = root;
    while (tree || !IsEmpty(S))
    {
        while (tree)
        {
            push(S, tree);             // push tree node into stack when still have left child
            tree = tree->left;
        }
        if (!IsEmpty(S))
        {
            tree = pop(S);                 // pop out tree node when no more left child
            printf("%d ", tree->data);     // which means move back upper level and print
            tree = tree->right;            // then, to the right sub tree and repeat
        }
    }
}

#define LEFT 0
#define RIGHT 1
void iter_postorder(BTree root)
{
    Stack S = CreateStack(MAXSIZE);
    BTree lastvisited = NULL;
    BTree peeknode = NULL;
    while (!IsEmpty(S) || root)
    {
        if (root)
        {
            push(S, root);
            root = root->left;
        }
        else
        {
            peeknode = pop(S);
            push(S, peeknode); // not now to pop out so push back
            if (peeknode->right && lastvisited != peeknode->right)
                root = peeknode->right;
            else
            {
                printf("%d ", peeknode->data);
                lastvisited = pop(S);
            }
        }
    }
}

no visited flag solution
void iter_postorder2(BTree root)
{
    Stack S = CreateStack(MAXSIZE);
    BTree prev = NULL; // previously traversed(not necessarily printed) node
    push(S, root);
    BTree curr = NULL;
    while (!IsEmpty(S))
    {
        curr = pop(S);
        push(S, curr);
        if (!prev || prev->left == curr || prev->right == curr)
        {
            // traversing down the tree
            if (curr->left)
                push(S, curr->left);
            else if (curr->right)
                push(S, curr->right);
            else
            {
                printf("%d ", curr->data);
                pop(S);
            }
        }
        else if (curr->left == prev)
        {
            // traversing up the tree from left sub tree
            if (curr->right)
                push(S, curr->right);
            else
            {
                printf("%d ", curr->data);
                pop(S);
            }
        }
        else if (curr->right == prev)
        {
            // traversing up the tree from right sub tree
            printf("%d ", curr->data);
            pop(S);
        }
        prev = curr;
    }
}

void inorder(BTree ptr)
{
    if (ptr)
    {
        inorder(ptr->left);
        printf("%d ", ptr->data);
        inorder(ptr->right);
    }
}

void postorder(BTree ptr)
{
    if (ptr)
    {
        inorder(ptr->left);
        inorder(ptr->right);
        printf("%d ", ptr->data);
    }
}

void preorder(BTree ptr)
{
    if (ptr)
    {
        printf("%d ", ptr->data);
        inorder(ptr->left);
        inorder(ptr->right);
    }
}

BTree copy(BTree origin)
{
    if (origin)
    {
        BTree temp = (BTree)malloc(sizeof(struct treeNode));
        if (IS_FULL(temp))
        {
            fprintf(stderr, "The memory is full.\n");
            exit(1);
        }
        temp->left = copy(origin->left);
        temp->right = copy(origin->right);
        temp->data = origin->data;
        return temp;
    }
    return NULL;
}

bool isEqual(BTree t1, BTree t2)
{
    return (!t1 && !t2) || (t1 && t2 && (t1->data == t2->data) &&
    isEqual(t1->left, t2->left) && isEqual(t1->right, t2->right));
}

void countleaf(BTree root, int *count)
{
    if (root)
    {
        countleaf(root->left, count);
        countleaf(root->right, count);
        if (!root->left && !root->right)
            (*count)++;
    }
}

int iter_countleaf(BTree root)
{
    Stack S = CreateStack(MAXSIZE);
    BTree lastvisited = NULL;
    BTree peeknode = NULL;
    int leaves = 0;
    while (!IsEmpty(S) || root)
    {
        if (root)
        {
            push(S, root);
            root = root->left;
        }
        else
        {
            peeknode = pop(S);
            push(S, peeknode); // not now to pop out so push back
            if (peeknode->right && lastvisited != peeknode->right)
                root = peeknode->right;
            else
            {
                printf("%d ", peeknode->data);
                if (!peeknode->left && !peeknode->right)
                	leaves++;
                lastvisited = pop(S);
            }
        }
    }
    return leaves;
}

void swaptree(BTree root)
{
    if (!root)
        return;
    BTree temp;
    temp = root->left;
    root->left = root->right;
    root->right = temp;
    swaptree(root->left);
    swaptree(root->right);
}

BTree createBTree(char *array, int len)
{
    //generate a binary tree
    BTree parent;
    Queue Q = CreateQueue(len);
    int i = 1;
    BTree root = makenode(array[i]);
    //printf("[Line 456] root->data: %c\n", root->data);
    enqueue(Q, root);
    //printf("[Line 458] root->data: %c\n", root->data);

    while (Q && (i*2+1 < len))
    {
        parent = dequeue(Q);
        //printf("[Line 465] i: %d\n", i);        
        BTree leftchild = makenode(array[i*2]);
        BTree rightchild = makenode(array[i++*2+1]);
        if (leftchild)
        {
            parent->left = leftchild;
            //printf("[Line 471] leftchild->data: %c | i: %d\n", leftchild->data, i);
            enqueue(Q, leftchild);
            //printf("[Line 473] leftchild->data: %c | i: %d\n", leftchild->data, i);
        }
        if (rightchild)
        {
            parent->right = rightchild;
            //printf("[Line 478] rightchild->data: %c | i: %d\n", rightchild->data, i);
            enqueue(Q, rightchild);
            //printf("[Line 480] rightchild->data: %c | i: %d\n", rightchild->data, i);
        }
    }
return root;
}

BTree makenode(char data)
{
    //create a tree node and return its pointer if data is not '#'
    if (data != '#')
    {
        BTree node = (BTree)malloc(sizeof(struct treeNode));
        if (!node)
        {
            fprintf(stderr, "Memory full.\n");
            exit(EXIT_FAILURE);
        }
        node->data = data; node->left = NULL; node->right = NULL;
        return node;
    }
    else
        return NULL;
}
*/

thrBiTree makethrnode(dataType data)
{
    /* create a threaded tree node and return its pointer if data
     is not '#' */
    if (data != '#')
    {
        thrBiTree node = (thrBiTree)malloc(sizeof(struct thrtreeNode));
        if (!node)
        {
            fprintf(stderr, "Memory full.\n");
            exit(EXIT_FAILURE);
        }
        node->data = data; node->left = NULL; node->right = NULL;
        // newly created node has no children yet so threaded set to true
        node->left_thr = true; node->right_thr = true;
        return node;
    }
    else
        return NULL;
}

thrBiTree createthrBiTree(dataType *array, int len)
{
    /* generate a binary tree */
    if (len < 2)
        return NULL;
    thrBiTree parent;
    Queue Q = CreateQueue(len);
    Queue save = CreateQueue(len);
    int i = 1;
    thrBiTree root = makethrnode(array[i]);
    enqueue(Q, root);
    enqueue(save, root);

    while (Q && (i*2+1 < len))
    {
        parent = dequeue(Q);      
        thrBiTree leftchild = makethrnode(array[i*2]);
        thrBiTree rightchild = makethrnode(array[i++*2+1]);
        if (leftchild)
        {
            parent->left = leftchild;
            parent->left_thr = false;
            enqueue(Q, leftchild);
        }
        if (rightchild)
        {
            parent->right = rightchild;
            parent->right_thr = false;
            enqueue(Q, rightchild);
        }
    }
return root;
}

thrBiTree linkthr_preorder(thrBiTree root, int len)
{
    /* input: root is the root node of sent in binary tree
    len is the number of tree nodes excluding sentinel node of arg 'array'
    of function 'thrBiTree createthrBiTree(dataType *array, int len)' */
    Queue save = CreateQueue(len);
    Stack S = CreateStack(MAXSIZE);          // create and initialize stack
    thrBiTree tree = root;
    thrBiTree prev, curr;               // two pointer to be used to make thread
    thrBiTree sentinel = create_sentinel(root); // create a sentinel node
    while (tree || !IsEmpty(S))        // using 'while' is more readable than 'for'
    {
        while (tree)
        {
            printf("%c ", tree->data);
            enqueue(save, tree);       // save preorder traversed node in queue
            push(S, tree);             // push visited node into stack
            tree = tree->left;         // move all the way to left
        }
        if (!IsEmpty(S))
        {
            tree = pop(S);             // when there's no more left subtree,
            tree = tree->right;        // to the right
        }
    }
    prev = dequeue(save);
    prev->left_thr = true;
    prev->left = sentinel;
    while (!QIsEmpty(save))
    {
        curr = dequeue(save);
        if (!curr->left)
        {
            curr->left_thr = true;
            curr->left = prev;
        }
        if (!prev->right)
        {
            prev->right_thr = true;
            prev->right = curr;
        }
        prev = curr;
    }
    prev->right_thr = true;
    prev->right = sentinel;
    return sentinel;
}

thrBiTree create_sentinel(thrBiTree root)
{
    thrBiTree temp = (thrBiTree)malloc(sizeof(struct thrtreeNode));
    temp->left = root; temp->right = temp;
    temp->left_thr = false; temp->right_thr = false;
    return temp;
}

