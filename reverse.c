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
    if ((pNewNode->line = (Node*)malloc(strlen(line) + 1)) == NULL) {
        printf("malloc failed");
        exit(1);
    }
    strcpy(pNewNode->line, line);
    pNewNode->next = NULL;
    pNewNode->prev = NULL;
    return(pNewNode);
}

void addNode(Node** pHead, char *line) {
    
    Node* newNode = createNode(line); 

    if (*pHead == NULL) {
        *pHead = newNode;
        return;
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
void readFile(const char *inputFile, Node** pHead) {
    char *line = NULL;
    size_t len = 0;

    FILE *fp = fopen(inputFile, "r");
    if (fp == NULL) {
        printf("error: cannot open file '%s'", inputFile);
        exit(1);
    }
    
    while (getline(&line, &len, fp) != -1) {
        addNode(pHead, line);
    }
    free(line);
    fclose(fp);
}



// Writes output file whenever one is given
void writeFile() {

}

// Prints out input file reversed
void printList(Node* head) {
    
    Node* pCurrent = head;
    while(pCurrent != NULL) {
        printf("%s", pCurrent->line);
        pCurrent = pCurrent->next;
    }
    return;
}

int main(int argc, char *argv[]) {
    
    Node *pHead = NULL;
    if (argc > 3) {
        printf("usage: reverse <input> <output>\n");
        return(1);
    }

    

    if (argc == 2) {
        const char *inputName = argv[1];
        readFile(inputName, &pHead);
        //addNode(pHead);
        printList(pHead);

        //printf("test 1 argument");
    }

    if (argc == 3) {
        printf("test 2 argument");
    }
    


    return(0);
}