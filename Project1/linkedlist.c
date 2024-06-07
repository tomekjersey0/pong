#include <stdio.h>
#include "linkedlist.h"

struct Node* createList() {
	struct Node head = { {0, 0}, NULL};
	return &head;
}

void addItem(struct Node* head, struct Node item) {
	head->next = &item;
}

void printList(struct Node* head) {
	struct Node* current_node = head;

	int index = 0;
	while (current_node != NULL) {
		printf("index: %d, data: %d", index, current_node->data);
		index++;
		current_node = current_node->next;
	}
}