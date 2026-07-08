/*
Sources:
https://www.geeksforgeeks.org/c/doubly-linked-list-in-c/
When creating data structure to store lines from files used this as guide to create doubly linked list.

https://stackoverflow.com/questions/28132673/list-hard-links-of-a-file-c
During testing had issues to pass test 5 because I did not have check for whether files were hardlinked or not. This led me to use sys/stat.h library to overcome this.

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

typedef struct node {
    char *line;
    struct node *next;
    struct node *prev;
} Node;

// Creates node to be added for linked list
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

// Adds node to linked list
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

// Reads standard input and stores lines to linked list
Node* readStdIn(FILE *fp, Node **pHead) {
    char *line = NULL;
    Node *pTail = NULL;
    size_t len = 0;

    if (fp == NULL) {
        fprintf(stderr, "reverse: cannot read from stdin");
        exit(1);
    }

    while (getline(&line, &len, fp) != -1) {
        line[strcspn(line, "\n")] = '\n';
        pTail = addNode(pHead, line);
    }
    free(line);
    return(pTail);
}

// Frees list after program is ran.
void freeList(Node* pHead) {
    Node *pCurrent = pHead;
    
    while(pCurrent != NULL) {
        Node *pNext = pCurrent->next;
        free(pCurrent->line);
        free(pCurrent);
        pCurrent = pNext;
    }

    return;
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
    fclose(fp);
    return;
}

// Prints out input file reversed
void printList(Node* pTail) {
    
    Node* pCurrent = pTail;
    while(pCurrent != NULL) {
        printf("%s", pCurrent->line);
        pCurrent = pCurrent->prev;
    }
    return;
}

int main(int argc, char *argv[]) {
    
    Node *pHead = NULL;
    Node *pTail = NULL;
    struct stat s1;
    struct stat s2;

    if (argc > 3) { // When user gives more than 3 arguments gives this error
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    } else if (argc == 1) {
        pTail = readStdIn(stdin, &pHead);
        printList(pTail);
    } else if (argc == 2) {
        const char *inputName = argv[1];
        pTail = readFile(inputName, &pHead);
        printList(pTail);
    } else if (argc == 3) {
        const char *inputName = argv[1];
        const char *outputName = argv[2];
        stat(inputName, &s1);
        stat(outputName, &s2);

        // Checks if given files are the same
        if(strcmp(inputName, outputName) == 0) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }
        
        // Checks if given files are hardlinked and gives eror if they are
        if(s1.st_ino == s2.st_ino && s1.st_dev == s2.st_dev) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            exit(1);
        }

        pTail = readFile(inputName, &pHead);
        writeFile(outputName, pTail);
    }
    

    freeList(pHead);
    return(0);
}