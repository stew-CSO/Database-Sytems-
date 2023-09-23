// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

// Allocate memory for a new list and initialize it.
list_t *list_alloc() {
  list_t *new_list = (list_t *)malloc(sizeof(list_t));
  if (new_list) {
    new_list->head = NULL; // Initialize the head to NULL
  }
  return new_list;
}

// Free the memory associated with the list and its nodes.
void list_free(list_t *l) {
  if (l) {
    node_t *current = l->head;
    while (current) {
      node_t *next = current->next;
      free(current);
      current = next;
    }
    free(l);
  }
}

// Print the elements of the list.
void list_print(list_t *l) {
  if (!l || !l->head) {
    printf("List is empty.\n");
    return;
  }

  node_t *current = l->head;
  int index = 1; // Start with 1-based index
  while (current) {
    printf("%d -> ", current->value);
    current = current->next;
    index++;
  }
  printf("NULL\n");
}

// Convert the list to a string representation.
char *listToString(list_t *l) {
  if (!l || !l->head) {
    char *buf = (char *)malloc(sizeof(char) * 5); // "NULL\0"
    strcpy(buf, "NULL");
    return buf;
  }

  char *buf = (char *)malloc(sizeof(char) * 1024);
  char tbuf[20];
  buf[0] = '\0'; // Initialize the buffer as an empty string

  node_t *curr = l->head;
  while (curr != NULL) {
    sprintf(tbuf, "%d->", curr->value);
    strcat(buf, tbuf);
    curr = curr->next;
  }
  strcat(buf, "NULL");
  return buf;
}

// Get the length of the list.
int list_length(list_t *l) {
  int length = 0;
  if (!l) {
    return length;
  }

  node_t *current = l->head;
  while (current) {
    length++;
    current = current->next;
  }
  return length;
}

// Add an element to the back of the list.
void list_add_to_back(list_t *l, elem value) {
  if (!l) {
    return;
  }

  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  if (new_node) {
    new_node->value = value;
    new_node->next = NULL;

    if (!l->head) {
      l->head = new_node; // If the list is empty, set the new node as the head.
    } else {
        node_t *current = l->head;
        while (current->next) {
          current = current->next;
      }
      current->next = new_node; // Add the new node to the end of the list.
    }
  }
}

// Add an element to the front of the list.
void list_add_to_front(list_t *l, elem value) {
  if (!l) {
    return;
  }

  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  if (new_node) {
    new_node->value = value;
    new_node->next = l->head; // Set the next of the new node to the current head.
    l->head = new_node; // Set the new node as the new head.
  }
}

// Add an element at a specific index in the list.
void list_add_at_index(list_t *l, elem value, int index) {
  if (!l || index < 1) { // 1-based indexing
    return;
  }

  if (index == 1) {
        // Adding at the front is the same as adding to the front.
    list_add_to_front(l, value);
    return;
  }

  int current_index = 1; // 1-based index
  node_t *current = l->head;
  node_t *prev = NULL;

    // Traverse to the node just before the specified index.
  while (current && current_index < index) {
    prev = current;
    current = current->next;
    current_index++;
  }

  if (current) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node) {
      new_node->value = value;
      new_node->next = current;
      prev->next = new_node;
    }
  }
}

// Remove and return the element from the back of the list.
elem list_remove_from_back(list_t *l) {
  if (!l || !l->head) {
    return -1; // Return a sentinel value for an empty list.
  }

  if (!l->head->next) {
  // If there is only one element in the list, remove it.
    elem removed_value = l->head->value;
    free(l->head);
    l->head = NULL; // The list is now empty.
    return removed_value;
  }

  // Find the second-to-last node.
  node_t *current = l->head;
  while (current->next->next) {
    current = current->next;
  }

    // Remove the last node.
  elem removed_value = current->next->value;
  free(current->next);
  current->next = NULL;
  return removed_value;
}

// Remove and return the element from the front of the list.
elem list_remove_from_front(list_t *l) {
  if (!l || !l->head) {
    return -1; // Return a sentinel value for an empty list.
  }

  elem removed_value = l->head->value;
  node_t *temp = l->head;
  l->head = l->head->next;
  free(temp);
  return removed_value;
}

// Remove and return the element at a specific index in the list.
elem list_remove_at_index(list_t *l, int index) {
  if (!l || !l->head || index < 1) { // 1-based indexing
    return -1; // Return a sentinel value for invalid input or an empty list.
  }

  if (index == 1) {
  // Removing the element at the front is the same as removing from the front.
     return list_remove_from_front(l);
  }

  int current_index = 1; // 1-based index
  node_t *current = l->head;
  node_t *prev = NULL;

  // Traverse to the node at the specified index.
  while (current && current_index < index) {
    prev = current;
    current = current->next;
    current_index++;
  }

  if (current) {
  // Remove the node at the specified index.
    elem removed_value = current->value;
    prev->next = current->next;
    free(current);
    return removed_value;
  }

  return -1; // Return a sentinel value for an invalid index.
}
