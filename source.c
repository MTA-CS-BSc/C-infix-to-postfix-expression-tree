#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 100

typedef struct treeNode {
    char data;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode;

typedef struct tree {
    TreeNode* root;
} Tree;

typedef struct listNode {
    char data;
    struct listNode* next;
} ListNode;

typedef struct list {
    ListNode* head;
    ListNode* tail;
} List;

typedef struct treeElementNode {
    TreeNode* node;
    struct treeElementNode* next;
} TreeElementNode;

typedef struct treeNodesList {
    TreeElementNode* head;
    TreeElementNode* tail;
} TreeNodesList;

#pragma region Functions declerations
// Receives a tree root reference and frees it's nodes
void freeTreeHelper(TreeNode* root);

// Receives a tree and frees it's nodes
void freeTree(Tree tree);

// Receives a list reference and frees it's nodes
void freeList(List* list);

// Receives a tree nodes' list reference and frees it's nodes
void freeTreeNodesList(TreeNodesList* list);

// Receives a list reference and initiatlizes it's head and tail references to NULL
void makeEmptyList(List* list);

// Receives a tree nodes list reference and initiatlizes it's head and tail references to NULL
void makeEmptyTreeNodesList(TreeNodesList* list);

// Receives a tree reference, returns true if the tree is empty, and false otherwise
bool isEmptyTree(Tree* tree);

// Receives a list reference, returns true if the list is empty, and false otherwise
bool isEmptyList(List* list);

// Receives a tree nodes list reference, returns true if the list is empty, and false otherwise
bool isEmptyTreeNodesList(TreeNodesList* list);

// Receives a char, returns true if it's one of the operators described in Q4, and false otherwise.
bool isOperator(char ch);

// Receives a char, returns true if it's a digit, and false otherwise.
bool isDigit(char ch);

// Receives a char, returns true if it's a digit, operator or brackets, and false otherwise.
bool isValidCharacter(char ch);

// Receives a char, and references of left and right tree nodes.
// Creates and returns a new tree node with the given values
TreeNode* createTreeNode(char data, TreeNode* left, TreeNode* right);

// Receives a char and a list node reference.
// Creates and returns a new list node with the given values
ListNode* createListNode(char data, ListNode* next);

// Receives a tree node reference and a tree element node reference.
// Creates and returns a new TreeElementsNode node with the given values
TreeElementNode* createTreeElementNode(TreeNode* node, TreeElementNode* next);

// Receives a list reference and a reference of a node to insert.
// Inserts the node to the beginning of the list
void insertNodeToStartList(List* list, ListNode* node);

// Receives a list reference and data to insert.
// Creates and inserts the node with the given values to the beginning of the list
void insertDataToStartList(List* list, char data);

// Receives a tree nodes list reference and a reference of a node to insert.
// Inserts the node to the beginning of the list
void insertNodeToStartTreeNodesList(TreeNodesList* list, TreeElementNode* node);

// Receives a tree nodes list reference and data to insert.
// Creates and inserts the node with the given values to the beginning of the list
void insertDataToStartTreeNodesList(TreeNodesList* list, TreeNode* data);

// Receives a list reference and a reference of a node to insert.
// Inserts the node to the end of the list
void insertNodeToEndList(List* list, ListNode* node);

// Receives a list reference and data to insert.
// Creates and inserts the node with the given values to the end of the list
void insertDataToEndList(List* list, char ch);

// Receives a list reference, removes the head of the list if it exists.
void removeNodeFromStartList(List* list);

// Receives a tree nodes list reference, removes the head of the list if it exists.
void removeNodeFromStartTreeNodesList(TreeNodesList* list);

// Receives two numbers and an operator (char represented).
// Calculates the result according to the operator.
double calculate(int val1, int val2, char op);

// Receives a root of an expression tree reference.
// Calculates and returns the expression result represented by the tree.
double calculateExpressionTreeHelper(TreeNode* root);

// Receives an expression tree. Calculates and returns the expression result represented by the tree.
double calcExpression(Tree expression_tree);

// Receives a post order list reference representing a tree
// (in other words, if we had a tree and printed it post-order, it would be the same as printing the list).
// Creates and returns the root of the tree represented by the list.
TreeNode* createExpressionTreeFromPostOrderList(List* postorder_list);

// Receives an expression to calculate.
// Creates and returns a list representing the tree of the string (without brackets).
// (in other words, if we had the tree and printed it post-order, it would be the same as printing the list).
List createPostOrderList(char* str);

// Receives an expression to calculate.
// Creates and returns the matching expression tree of the given string.
Tree createExpressionTreeFromString(char* str);

// Receives an expression to calculate and a tree reference.
// Attempts to create the matching expression tree.
// Returns true if the creation succeeded with the relevant tree as output parameter,
// and false otherwise with an empty tree as output parameter.
bool buildExpressionTree(char* expression, Tree* tree);
#pragma endregion

#pragma region Functions implementations
void freeTreeHelper(TreeNode* root) {
    if (root == NULL)
        return;

    freeTreeHelper(root->left);
    freeTreeHelper(root->right);
    free(root);
}

void freeTree(Tree tree) {
    freeTreeHelper(tree.root);
}

void freeList(List* list) {
    ListNode* current = list->head;
    ListNode* saver = NULL;

    while (current != NULL) {
        saver = current->next;
        free(current);
        current = saver;
    }
}

void freeTreeNodesList(TreeNodesList* list) {
    // The function frees only the TreeElementNodes since we're going to 
    // use the TreeNode data of each element

    TreeElementNode* current = list->head;
    TreeElementNode* saver;

    while (current != NULL) {
        saver = current->next;
        free(current);
        current = saver;
    }
}

void makeEmptyList(List* list) {
    list->head = NULL;
    list->tail = NULL;
}

void makeEmptyTreeNodesList(TreeNodesList* list) {
    list->head = list->tail = NULL;
}

bool isEmptyTree(Tree* tree) {
    return tree->root == NULL;
}

bool isEmptyList(List* list) {
    return list->head == NULL;
}

bool isEmptyTreeNodesList(TreeNodesList* list) {
    return list->head == NULL;
}

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%');
}

bool isDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

bool isValidCharacter(char ch) {
    return isOperator(ch) || isDigit(ch) || ch == '(' || ch == ')';
}

TreeNode* createTreeNode(char data, TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));

    if (!node)
        exit(1);

    node->data = data;
    node->left = left;
    node->right = right;

    return node;
}

ListNode* createListNode(char data, ListNode* next) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));

    if (!node)
        exit(1);

    node->data = data;
    node->next = next;

    return node;
}

TreeElementNode* createTreeElementNode(TreeNode* node, TreeElementNode* next) {
    TreeElementNode* tree_node_element = (TreeElementNode*)malloc(sizeof(TreeElementNode));

    if (!tree_node_element)
        exit(1);

    tree_node_element->node = node;
    tree_node_element->next = next;

    return tree_node_element;
}

void insertNodeToStartList(List* list, ListNode* node) {
    if (isEmptyList(list))
        list->head = list->tail = node;

    else {
        node->next = list->head;
        list->head = node;
    }
}

void insertDataToStartList(List* list, char data) {
    ListNode* node = createListNode(data, NULL);
    insertNodeToStartList(list, node);
}

void insertNodeToStartTreeNodesList(TreeNodesList* list, TreeElementNode* node) {
    if (isEmptyTreeNodesList(list))
        list->head = list->tail = node;

    else {
        node->next = list->head;
        list->head = node;
    }
}

void insertDataToStartTreeNodesList(TreeNodesList* list, TreeNode* data) {
    TreeElementNode* to_insert = createTreeElementNode(data, NULL);
    insertNodeToStartTreeNodesList(list, to_insert);
}

void insertNodeToEndList(List* list, ListNode* node) {
    if (isEmptyList(list))
        list->head = list->tail = node;

    else {
        list->tail->next = node;
        list->tail = node;
    }
}

void insertDataToEndList(List* list, char ch) {
    ListNode* node = createListNode(ch, NULL);
    insertNodeToEndList(list, node);
}

void removeNodeFromStartList(List* list) {
    ListNode* node_to_remove = list->head;

    if (list->head == list->tail)
        list->head = list->tail = NULL;

    else
        list->head = node_to_remove->next;

	if (!node_to_remove)
		free(node_to_remove);
}

void removeNodeFromStartTreeNodesList(TreeNodesList* list) {
    TreeElementNode* node_to_remove = list->head;

    if (list->head == list->tail)
        list->head = list->tail = NULL;

    else
        list->head = node_to_remove->next;

	if (!node_to_remove)
		free(node_to_remove);
}

double calculate(int val1, int val2, char op) {
    double result = 0.0;

    switch (op) {
    case '+':
        result = (double)val1 + val2;
        break;
    case '-':
        result = (double)val1 - val2;
        break;
    case '/':
        result = (double)val1 / val2;
        break;
    case '*':
        result = (double)val1 * val2;
        break;
    case '%':
        result = (double)(val1 % val2);
        break;
    }

    return result;
}

double calculateExpressionTreeHelper(TreeNode* root) {
    if (root == NULL)
        return 0;

    else if (isDigit(root->data))
        return (int)(root->data - '0');

    int right_value = calculateExpressionTreeHelper(root->right);
    int left_value = calculateExpressionTreeHelper(root->left);
    return calculate(right_value, left_value, root->data);
    
}

double calcExpression(Tree expression_tree) {
    return calculateExpressionTreeHelper(expression_tree.root);
}

TreeNode* createExpressionTreeFromPostOrderList(List* postorder_list) {
    int insert_index = 0;
    ListNode* current = postorder_list->head;
    TreeNodesList tree_nodes_list;

    makeEmptyTreeNodesList(&tree_nodes_list);

    while (current != NULL) {
        if (!isOperator(current->data))
            insertDataToStartTreeNodesList(&tree_nodes_list, createTreeNode(current->data, NULL, NULL));

        else {
            TreeNode* left = tree_nodes_list.head->node;
            removeNodeFromStartTreeNodesList(&tree_nodes_list);

            TreeNode* right = tree_nodes_list.head->node;
            removeNodeFromStartTreeNodesList(&tree_nodes_list);

            TreeNode* current_root = createTreeNode(current->data, left, right);
            insertDataToStartTreeNodesList(&tree_nodes_list, current_root);
        }

        current = current->next;
    }

    TreeNode* root = tree_nodes_list.head->node;

    freeTreeNodesList(&tree_nodes_list);

    return root; // The root of the expression tree
}

List createPostOrderList(char* str) {
    List operators;
    List postorder_list;
    int string_length = strlen(str), insert_index = 0;
    bool is_valid_expression = true;
    char prev_char = 'a';

    makeEmptyList(&postorder_list);
    makeEmptyList(&operators);

    for (int i = 0; i < string_length && is_valid_expression; i++) {
        if (!isValidCharacter(str[i]))
            is_valid_expression = false;
        
        else if (isDigit(str[i])) {
            if (isDigit(prev_char))
                is_valid_expression = false;

            else
                insertDataToEndList(&postorder_list, str[i]);
        }

        else if (str[i] == '(' || isOperator(str[i]))
            insertDataToStartList(&operators, str[i]);

        else if (str[i] == ')') {
            while (!isEmptyList(&operators) && operators.head->data != '(') {
                insertDataToEndList(&postorder_list, operators.head->data);
                removeNodeFromStartList(&operators);
            }

            if (!isEmptyList(&operators))
                removeNodeFromStartList(&operators);

            else
                is_valid_expression = false;
        }

        prev_char = str[i];
    }

    while (!isEmptyList(&operators) && is_valid_expression) {
        if (operators.head->data == '(')
            is_valid_expression = false;

        else {
            insertDataToEndList(&postorder_list, operators.head->data);
            removeNodeFromStartList(&operators);
        }
    }

    if (!is_valid_expression) {
        freeList(&postorder_list);
        makeEmptyList(&postorder_list);
    }

    return postorder_list;
}

Tree createExpressionTreeFromString(char* str) {
    List postorder_list;
    TreeNode* root = NULL;
    Tree returned_tree = { root };

    postorder_list = createPostOrderList(str);

    if (!isEmptyList(&postorder_list)) {
        returned_tree.root = createExpressionTreeFromPostOrderList(&postorder_list);
        freeList(&postorder_list);
    }

    return returned_tree;
}

bool buildExpressionTree(char* expression, Tree* tree) {
    *tree = createExpressionTreeFromString(expression);

    if (isEmptyTree(tree))
        return false;

    return true;
}
#pragma endregion

void main()
{
    char str[SIZE];
    Tree tr;
    double result;
    bool is_valid;

    printf("Please enter the expression: ");
    gets(str);

    is_valid = buildExpressionTree(str, &tr);

    if (is_valid) {
        result = calcExpression(tr);
        printf("%s = %.2f", str, res);
    }

    else
        printf("The input expression is not valid\n");

    freeTree(tr);
	exit(0);
}
