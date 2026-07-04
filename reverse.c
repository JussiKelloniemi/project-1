#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if ((pNewNode->line = (char*)malloc(strlen(line) + 1)) == NULL) {
        printf("malloc failed");
        exit(1);
    }
    strcpy(pNewNode->line, line);
    pNewNode->next = NULL;
    pNewNode->prev = NULL;
    return(pNewNode);
}

Node* addNode(Node** pHead, char *line) {
    
    Node* newNode = createNode(line); 

    if (*pHead == NULL) {
        *pHead = newNode;
        return(newNode);
    }

    Node* pCurrent = *pHead;

    while(pCurrent->next != NULL) {
        pCurrent = pCurrent->next;
    }

    pCurrent->next = newNode;
    newNode->prev = pCurrent;
    
    return(newNode);
}

// Reads input file and stores the contets of that file
Node* readFile(const char *inputFile, Node** pHead) {
    char *line = NULL;
    Node *pTail = NULL;
    size_t len = 0;

    FILE *fp = fopen(inputFile, "r");
    if (fp == NULL) {
        fprintf(stderr, "reverse: cannot open file '%s'\n", inputFile);
        exit(1);
    }
    
    while (getline(&line, &len, fp) != -1) {
        line[strcspn(line, "\n")] = '\n';
        pTail = addNode(pHead, line);
    }
    free(line);
    fclose(fp);
    return(pTail);
}



// Writes output file whenever one is given
void writeFile(const char *outputFile, Node* pTail) {
    FILE *fp = fopen(outputFile, "w");
    if (fp == NULL) {
        fprintf(stderr, "error: cannot open file '%s'\n", outputFile);
        exit(1);
    }

    Node* pCurrent = pTail;

    while(pCurrent != NULL) {
        fprintf(fp, "%s", pCurrent->line);
        pCurrent = pCurrent->prev;
    }
    printf("\n");
    return;
    fclose(fp);
}

// Prints out input file reversed
void printList(Node* pTail) {
    
    Node* pCurrent = pTail;
    while(pCurrent != NULL) {
        printf("%s", pCurrent->line);
        pCurrent = pCurrent->prev;
    }
    printf("\n");
    return;
}

int main(int argc, char *argv[]) {
    
    Node *pHead = NULL;
    Node *pTail = NULL;

    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }

    

    if (argc == 2) {
        const char *inputName = argv[1];
        pTail = readFile(inputName, &pHead);
        //addNode(pHead);
        printList(pTail);

        //printf("test 1 argument");
    }

    if (argc == 3) {
        const char *inputName = argv[1];
        const char *outputName = argv[2];

        if(strcmp(inputName, outputName) == 0) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }
        pTail = readFile(inputName, &pHead);
        writeFile(outputName, pTail);
        
        //printf("test 2 argument");
    }
    


    return(0);
}