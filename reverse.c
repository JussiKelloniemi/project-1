#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    char *line;
    struct node *next;
    struct node *prev;
} Node;

Node *createNode(char *line) {
    Node *pNewNode = NULL;

    if ((pNewNode = (Node*)malloc(sizeof(Node))) == NULL) {
        printf("malloc failed");
        exit(1);
    }

    pNewNode->line = line;
    pNewNode->next = NULL;
    pNewNode->prev = NULL;
    return(pNewNode);
}

void addNode(Node** pHead, char *line) {
    
    Node* newNode = createNode(line); 

    if (*pHead == NULL) {
        *pHead = newNode;
    }

    Node* pCurrent = *pHead;

    while(pCurrent->next != NULL) {
        pCurrent = pCurrent->next;
    }

    pCurrent->next = newNode;
    newNode->prev = pCurrent;
    
    return;
}

// Reads input file and stores the contets of that file
FILE *readFile(const char *inputFile) {
    FILE *fp = fopen(inputFile, "r");
    if (fp == NULL) {
        printf("error: cannot open file '%s'", inputFile);
        exit(1);
    }

    return(fp);
}



// Writes output file whenever one is given
void writeFile() {

}

// Prints out input file reversed
void printReverse(Node* head) {
    
    Node* pCurrent = head;
    while(pCurrent != NULL) {
        printf("%s\n", pCurrent->line);
        pCurrent = pCurrent->next;
    }
    return;
}

int main(int argc, char *argv[]) {
    
    Node *pHead = NULL;
    char *line = NULL;
    if (argc > 3) {
        printf("usage: reverse <input> <output>\n");
        return(1);
    }

    const char *inputName = argv[1];
    const char *outputName = argv[2];

    if (argc == 2) {
        FILE *inputFile = readFile(inputName);
        //addNode(pHead);
        printReverse(pHead);

        //printf("test 1 argument");
    }

    if (argc == 3) {
        printf("test 2 argument");
    }
    


    return(0);
}