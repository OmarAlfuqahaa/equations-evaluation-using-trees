//Omar Alfoqahaa 1200207
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 100 // max size
// *********************************************************************************************************************

// stack (array of character)
typedef struct {
    char stack[MAX_SIZE];
    int top;
} Stack;
// initialize stack
void initialize(Stack *s) {
    s->top = -1;
}
// is full function
bool is_full(Stack *s) {
    return s->top == MAX_SIZE - 1;
}
// is empty function
bool is_empty(Stack *s) {
    return s->top == -1;
}
// push (add to stack)
void push(Stack *s, char c) {
    if (!is_full(s)) {
        s->stack[++s->top] = c;
    }
}
// return from stack(with remove)
char pop(Stack *s) {
    if (!is_empty(s)) {
        return s->stack[s->top--];
    }
    return '\0';
}
// return from stack (without remove)
char peek(Stack *s) {
    if (!is_empty(s)) {
        return s->stack[s->top];
    }
    return '\0';
}

// *********************************************************************************************************************
// struct node (Doubly linked list)
typedef struct Node {
    char data[MAX_SIZE];
    struct Node *prev;
    struct Node *next;
} Node;

// doubly linked list structure
typedef struct {
    Node *head;
    Node *tail;
} DoublyLinkedList;

// function to initialize an empty doubly linked list
void initializeList(DoublyLinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
}

// function to create a new node
Node *createNode(const char data[]) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("memory allocation error!!!\n");
        exit(0);
    }

    // Ensure the data fits within the specified size
    strcpy(newNode->data, data);
    newNode->data[100 - 1] = '\0'; // null-terminate the string

    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}


// function to insert a node at the end of the list
void insertLast(DoublyLinkedList *list, const char data[]) {

    Node *newNode = createNode(data);

    if (list->tail == NULL) {
        // if the list is empty, set both head and tail to the new node
        list->head = newNode;
        list->tail = newNode;
    } else {
        // otherwise, update the links and move the tail to the new node
        newNode->prev = list->tail;
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

// function to print the non-sorted elements of the list
void printList(DoublyLinkedList *list) {
    Node *current = list->head;

    while (current != NULL) {
        printf("%s\n", current->data);
        current = current->next;
    }
}
// isAccepted function ( used to read numbers ,opp(s), and parentheses only)
int isAccepted(char ch) {
    return ch >= '0' && ch <= '9' || ch == '*' || ch == '/' || ch == '+' || ch == '-' || ch == '(' || ch == ')'|| ch == '%';
}
// read file from input file
void readFile(DoublyLinkedList *list, const char *filename) {
    FILE *file = fopen(filename, "r");
    char line[100], ch;
    int index = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (isAccepted(ch))
            line[index++] = ch;
        else if (ch == '\n' && index != 0) {
            line[index] = '\0';
            insertLast(list, line);
            index = 0;
        }


    }
    if (index != 0) { // to read the last line
        line[index] = '\0';
        insertLast(list, line);
    }
    printf("File Loaded successfully!\n");

}

//**********************************************************************************************************************
// tree node struct
typedef struct TreeNode {
    char data[MAX_SIZE];
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// function to create a new tree node
TreeNode *createTreeNode(const char *data) {
    TreeNode *newNode = (TreeNode *) malloc(sizeof(TreeNode));
    strcpy(newNode->data, data);
    newNode->left = newNode->right = NULL;
    return newNode;
}

//**********************************************************************************************************************
// tree stack struct
typedef struct TreeStack {
    int top;
    TreeNode *trees[MAX_SIZE];
} TreeStack;

// initialize tree stack
void initializeTreeStack(TreeStack *s) {
    s->top = -1;
}

// is full function
bool isTreeStackFull(TreeStack *s) {
    return s->top == MAX_SIZE - 1;
}

// push function
void pushTreeStack(TreeStack *s, TreeNode *treeNode) {
    if (!isTreeStackFull(s)) {
        s->trees[++s->top] = treeNode;
    }
}

// pop function
TreeNode *popTreeStack(TreeStack *s) {
    return s->trees[s->top--];
}
//**********************************************************************************************************************

// op1 is always % * / and op2 is that in stack
// it return if the op1 has precedence more than op2
//hasPrecedence function
bool hasPrecedence(char op1, char op2)
{
    if (op1 == '+' || op1 == '-')
        return false;
    else if (op2 == '+' || op2 == '-')
        return true;
    return false;
}

//infix to postfix function
char *infixToPostfix(char s[])
{
    Stack stack;
    initialize(&stack);
    char *postfix = (char *) malloc(MAX_SIZE + 1);
    unsigned long l = strlen(s);
    int currPostfixIndex = 0;
    for (int i = 0; i < l; i++) {
        switch (s[i]) {
            case '+':
            case '-':
                if (postfix[currPostfixIndex - 1] != ' ')
                    postfix[currPostfixIndex++] = ' ';
                while (!is_empty(&stack) && peek(&stack) != '(') {   // to pop all elements in stack
                    postfix[currPostfixIndex++] = pop(&stack);
                    postfix[currPostfixIndex++] = ' ';
                }
                push(&stack, s[i]);
                break;
            case '/':
            case '%':
            case '*':
                if (postfix[currPostfixIndex - 1] != ' ')
                    postfix[currPostfixIndex++] = ' ';
                while (!is_empty(&stack) && !hasPrecedence(s[i], peek(&stack)) && peek(&stack) != '(') {
                    postfix[currPostfixIndex++] = pop(&stack);
                    postfix[currPostfixIndex++] = ' ';
                }

                push(&stack, s[i]);
                break;
            case '(':
                push(&stack, s[i]);
                break;
            case ')':
                if (postfix[currPostfixIndex - 1] != ' ')
                    postfix[currPostfixIndex++] = ' ';
                while (!is_empty(&stack) && peek(&stack) != '(') {
                    postfix[currPostfixIndex++] = pop(&stack);
                    postfix[currPostfixIndex++] = ' ';
                }

                pop(&stack);
                break;
            default:
                if (postfix[currPostfixIndex - 1] != ' ' && postfix[currPostfixIndex - 1] < '0' ||
                    postfix[currPostfixIndex - 1] > '9')
                    postfix[currPostfixIndex++] = ' ';

                postfix[currPostfixIndex++] = s[i];


        }
    }

    while (!is_empty(&stack)) {
        postfix[currPostfixIndex++] = ' ';
        postfix[currPostfixIndex++] = pop(&stack);
    }
    postfix[currPostfixIndex++] = '\0';

    return postfix;
}
// fill equation to linked list
DoublyLinkedList toPostfix(DoublyLinkedList *list) {

    DoublyLinkedList postList;
    initializeList(&postList);

    // char equation [100];
    Node *current = list->head;
    while (current != NULL) {
        char *postFix = infixToPostfix(current->data);

        insertLast(&postList, postFix);

        current = current->next;
    }

    return postList;
}
// is operator function
bool isOperator(const char *token) {
    return token[0] == '+' || token[0] == '-' ||
           token[0] == '*' || token[0] == '/' || token[0] == '%';
}
// build evaluation tree function
TreeNode *buildEvaluationTree(char postfix[]) {
    TreeStack stack;
    initializeTreeStack(&stack);

    char postfixCopy[MAX_SIZE];
    strcpy(postfixCopy, postfix);

    char *token = strtok(postfixCopy, " ");
    while (token != NULL) {
        if (strlen(token) != 0) {
            if (!isOperator(token)) {
                TreeNode *treeNode = createTreeNode(token);
                pushTreeStack(&stack, treeNode);
            } else {
                TreeNode *right = popTreeStack(&stack);
                TreeNode *left = popTreeStack(&stack);

                TreeNode *treeNode = createTreeNode(token);
                treeNode->right = right;
                treeNode->left = left;

                pushTreeStack(&stack, treeNode);
            }
        }

        token = strtok(NULL, " ");
    }

    return popTreeStack(&stack);
}
// evaluate tree function
int evaluateTree(TreeNode *root) {
    if (root->left == NULL && root->right == NULL)
        return atoi(root->data);

    int left = evaluateTree(root->left);
    int right = evaluateTree(root->right);
    switch (root->data[0]) {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            if (right!=0){
            return left / right;}
            else
                printf("division on zero !!!");
            exit(0);
        case '%':
            if (right!=0){
                return left % right;}
            else
                printf("% on zero !!!");
            exit(0);
    }
    return 0;
}
// build and evaluation tree function
DoublyLinkedList buildAndEvaluateTree(DoublyLinkedList *postfixList) {
    DoublyLinkedList results;
    initializeList(&results);
    Node *current = postfixList->head;
    while (current != NULL) {
        TreeNode *evaluationTree = buildEvaluationTree(current->data);
        int result = evaluateTree(evaluationTree);
        char *stringResult = malloc(sizeof(char) * MAX_SIZE);
        itoa(result, stringResult, 10);
        insertLast(&results, stringResult);
        current = current->next;
    }

    return results;
}
// save to file function
void saveToFile(const char *filename, DoublyLinkedList *equation, DoublyLinkedList *results) {
    FILE *out = fopen(filename, "w");

    Node *equationCurr = equation->head;
    Node *resultCurr = results->head;
    while (equationCurr != NULL) {
        fprintf(out, "%s = %s\n", equationCurr->data, resultCurr->data);

        equationCurr = equationCurr->next;
        resultCurr = resultCurr->next;
    }

    fclose(out);
    printf("saved\n");
}
// print results function
void printResults(DoublyLinkedList *equations, DoublyLinkedList *results) {
    Node *equationCurrent = equations->head;
    Node *resultsCurrent = results->head;


    while (equationCurrent != NULL) {
        printf("%s = %s\n", equationCurrent->data,resultsCurrent->data);
        equationCurrent = equationCurrent->next;
        resultsCurrent = resultsCurrent->next;
    }
}

//**********************************************************************************************************************
int main() {
    DoublyLinkedList infixEquation;
    DoublyLinkedList postfixEquation;
    DoublyLinkedList results;
    initializeList(&infixEquation);

    char choice;
    do {
        printf("\nMenu:\n");
        printf("1. Read equations\n");
        printf("2. Print equations\n");
        printf("3. Evaluate using Expression tree\n");
        printf("4. Print postfix expressions\n");
        printf("5. Save to output file (postfix and results)\n");
        printf("6. Exit\n");

        printf("Enter your choice:");
        scanf(" %c", &choice);

        switch (choice) {
            case '1': //Read equations
                readFile(&infixEquation, "input.txt");
                postfixEquation = toPostfix(&infixEquation);
                break;
            case '2': // Print equations
                if (infixEquation.head == NULL) {
                    printf("You must read file first");
                    break;
                }
                printf("Equations: \n");
                printList(&infixEquation);
                break;
            case '3': // Evaluate using Expression tree
                if (infixEquation.head == NULL) {
                    printf("You must read file first");
                    break;
                }

                results = buildAndEvaluateTree(&postfixEquation);
                printf("Results: \n");
                printResults(&infixEquation, &results);
                break;
            case '4': // Print postfix expressions
                if (infixEquation.head == NULL) {
                    printf("You must read file first");
                    break;
                }

                printf("Postfix: \n");
                printList(&postfixEquation);
                break;
            case '5': // Save to output file (postfix and results)
                if (infixEquation.head == NULL) {
                    printf("You must read file first");
                    break;
                }

                saveToFile("output.txt", &postfixEquation, &results);
                break;
            case '6': // Exit
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 6);

    return 0;
}
