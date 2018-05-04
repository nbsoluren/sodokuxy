//Author: Francis T. Saylon
//Section: CMSC 123 CD-4L
//Date Created: January 19, 2017
//Program Descrption: Diagnostic Exercise

#include <stdio.h>
#include <stdlib.h>

typedef struct nodetag{
	int x;
	struct nodetag *next;
}NODE;

//Creates a function that inserts a node in the linked list
void insert(NODE **head, NODE **newnode){
	//Variable Declaration
	NODE *viewer = *head;

	if(*head == NULL){ //Checks if the list is empty
		*head = (NODE*) malloc(sizeof(NODE));
		//Asks the user for the first integer of the list
		printf("Enter number: ");
		scanf("%d", &((*head)->x));
		
		//Points the pointer to NULL to avoid dangling
		(*head)->next = NULL;
	}else{
		//Traverses the linked list to find the tail
		while(viewer->next!=NULL) viewer=viewer->next;
		
		*newnode = (NODE*) malloc(sizeof(NODE));
		//Asks the user for an integer
		printf("Enter number: ");
		scanf("%d", &((*newnode)->x));
		
		//Connects the new node to the tail of the linked list
		viewer->next = *newnode;

		//Points the pointer to NULL to avoid dangling
		(*newnode)->next = NULL;
	}
}


//Creates a function that views the contents of the linked list
void view(NODE **head){
	//Variable Declaration
	NODE *viewer = *head;

	if(*head==NULL) printf("\nThe list is empty\n");
	//Traverses the linked list until the tail is found
	printf("\n");
	while(viewer!=NULL){
		printf("%d\n", viewer->x);
		viewer=viewer->next;
	}
}

//Creates a function that deletes a node from the head of the list
void delete(NODE **head){

	if(*head!=NULL){//Checks if the list is not empty
		NODE *toDelete = *head; //Declares a pointer that points to the head
		*head = (*head)->next; //Points the head to the next node
		free(toDelete); //Deletes the node
	}else printf("\nThe list is empty\n");
}

//Creates a function that frees the linked list when the program terminates
void freeAll(NODE **head){
	if(*head==NULL){
		free(*head);
	}else{
		while(*head!=NULL){
			delete(head);
		}
	}
}

int main(){
	//Variable Declaration
	NODE *head = NULL;
	NODE *newnode = NULL; 
	int choice = 0;

	//Creates a menu
	while(choice!=4){
		printf("\n[1] Insert\n");
		printf("[2] Delete\n");
		printf("[3] View\n");
		printf("[4] Exit\n");
		printf(">>>");
		scanf("%d", &choice);

		switch(choice){
			case 1: insert(&head, &newnode); break;
			case 2: delete(&head); break;
			case 3: view(&head); break;
			case 4: freeAll(&head); break;
		}
	}

	return 0;
}


