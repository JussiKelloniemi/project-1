<ins>**Project 1**</ins><br/>
Jussi Kelloniemi

Program reverses order of the lines given in either input file or as in standard input.
Lines can be read from standard input or from input file. Lines can be printed into standard output
or into output file.
The program can be compiled with simple ```make``` command. Using ```make``` command runs:

```gcc -o reverse reverse.c -Wall```

User can give the program 0, 1 or 2 arguments depending on what user wants to do.<br/><br/>
```./reverse```
Reads from standard input and prints to standard output.

```./reverse input.txt```
Reads from input file and prints to standard output

```./reverse input.txt output.txt```
Reads from input file and writes into output file.

Program checks for multiple errors such as:
* Input and output files are not the same or hardlinked
* No more than 2 arguments are given
* Failure to open input or output files

The program uses doubly linked list as its data structure:
```
typedef struct node { 
    char *line; 
    struct node *next;
    struct node *prev;
} Node;
```

Each line is stored in a node where memory is dynamically allocated for each line.
Nodes contain pointers for the previous and the next node so that list can be traversed in both directions.

**Functions**:

```Node *createNode(char *line)```:<br/>
Creates new node for linked list and allocates memory for new line.

```Node* addNode(Node** pHead, char *line)```:<br/>
Adds node to the end of the data structure. If the list is empty the node becomes the head of the list.
Else traverses to the end of the list and node is added as tail.

```Node* readFile(const char *inputFile, Node** pHead)```:<br/>
Opens and reads through input file line by line and adds each line into the data structure as their own node.
If file cannot be opened, error message is printed.

```Node* readStdIn(FILE *fp, Node **pHead)```:<br/>
Reads each line given in standard input and adds each line into the data structure as a node.
If standard input cannot be read, error message is printed and program exits.

```void freeList(Node* pHead)```:<br/>
Traverses through the data structure freeing memory from each node.

```void writeFile(const char *outputFile, Node* pTail)```:<br/>
Traverses through the linked list in reversed order and writes 
each line from node into the output file user has given. If file cannot be opened, error message is printed and
program exits.

```void printList(Node* pTail)```:<br/>
Travers through the linked list in reversed order and prints
each line from nodes into standrad output.
