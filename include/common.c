#include "stdio.h"
#include "stdlib.h"
#include "common.h"

List* CreateNode(void* value) {
    List* node = (List*)malloc(sizeof(List));
    node->data = value;
    node->next = NULL;
    return node;
}

void AddFirst(List **head, void *value) {
	List* node = CreateNode(value);
	node->next = *head;
	*head = node;
}

void AddLast(List** head, void* value) {
	List* node = CreateNode(value);
	List* current = *head;
	if (current == NULL) {
		*head = node;
		return;
	}
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = node;
}

void RemoveFirst(List** head){
	List* current = *head;
	if (current == NULL) {
		return;
	}
	*head = current->next;
	free(current);
}

void RemoveLast(List** head) {
	List* current = *head;
	if (current == NULL) {
		return;
	}
	if (current->next == NULL) {
		free(current);
		*head = NULL;
		return;
	}
	while (current->next->next != NULL) {
		current = current->next;
	}
	free(current->next);
	current->next = NULL;
}

void RemoveAll(List** head) {
	List* current = *head;
	while (current != NULL) {
		List* next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}