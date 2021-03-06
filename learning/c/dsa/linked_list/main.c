#include "stdio.h"
#include "stdlib.h"

struct node {
    int data;
    struct node* next;
};

struct node *createNode() {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if(newNode==NULL){
        printf("Not Enough Memory!");
        exit(1);
    }
    return newNode;
}
int countList(struct node* head) {
    int i = 0;
    while (head != NULL) {
        i++;
        head = head->next;
    }
    return i;
}

void display(struct node *head) {
    if (head == NULL) {
        printf("Empty List!\n");
        return;
    }
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

void insertBeginning(int data, struct node** headRef) {
    struct node* newNode = createNode();
    newNode->data = data;
    newNode->next = *headRef;
    *headRef = newNode;
}

void insertEnd(int data, struct node** headRef) {
    struct node *newNode, *last;
    newNode = createNode();
    last = *headRef;

    newNode->data = data;
    newNode->next = NULL;

    if (*headRef == NULL) {
        *headRef = newNode;
        return;
    }

    while (last->next != NULL) last = last->next;
    last->next = newNode;
}

void insertAtIndex(int data, int index, struct node** headRef) {
    // index starts at 1
    struct node *temp, *newNode;
    int i = 1, count = countList(*headRef);

    if (index == count+1) {
        insertEnd(data, &*headRef);
        return;
    }

    if (index == 1) {
        insertBeginning(data, *&headRef);
        return;
    }

    if (count < index || index < 2) {
        printf("Invalid Index!\n");
        return;
    }

    temp = *headRef;
    while (i < index - 1) {
        temp = temp->next;
        i++;
    }
    newNode = createNode();
    newNode->data = data;
    newNode->next = temp->next;
    temp->next = newNode;
}

void deleteFromBeginning(struct node** headRef) {
    struct node* tmp;
    if (*headRef == NULL) {
        printf("Cannot Delete, Empty List!\n");
        return;
    }
    tmp = *headRef;
    *headRef = tmp->next;
    free(tmp);
}

void deleteFromEnd(struct node** headRef) {
    struct node *tmp, *prevNode;
    if (*headRef == NULL) {
        printf("Cannot Delete, Empty List!\n");
        return;
    }
    tmp = *headRef;
    while (tmp->next != NULL) {
        prevNode = tmp;
        tmp = tmp->next;
    }
    if (tmp == *headRef)
        *headRef = NULL;
    else
        prevNode->next = NULL;
    free(tmp);
}

void deleteIndex(int index, struct node** headRef) {
    struct node *tmp, *nextNode;
    int i = 1, count = countList(*headRef);
    if (*headRef == NULL) {
        printf("Cannot Delete, Empty List!\n");
        return;
    }

    if (index == 1) {
        deleteFromBeginning(*&headRef);
        return;
    }

    if (count < index || index < 2) {
        printf("Invalid Index.\n");
        return;
    }
    tmp = *headRef;

    while (i < index - 1) {
        tmp = tmp->next;
        i++;
    }

    nextNode = tmp->next;
    tmp->next = nextNode->next;
    free(nextNode);
}

struct node* reverse(struct node* head) {
    struct node *prevNode, *currentNode, *nextNode;
    prevNode = NULL;
    currentNode = nextNode = head;
    while (nextNode != NULL) {
        nextNode = nextNode->next;
        currentNode->next = prevNode;
        prevNode = currentNode;
        currentNode = nextNode;
    }
    return prevNode;
}

int main() {
    struct node *head, *temp, *lastN;
    head = temp = NULL;

    insertBeginning(10,&head);
    insertBeginning(15,&head);
    insertBeginning(20,&head);
    display(head);

    insertEnd(55,&head);
    insertEnd(58,&head);
    display(head);

    insertAtIndex(24,2,&head)    ;
    display(head);

    deleteFromBeginning(&head);
    deleteFromEnd(&head);
    deleteIndex(3,&head);
    display(head);


    head = reverse(head);
    display(head);
    
    printf("Total Items : %d\n",countList(head));

    return 0;
}
