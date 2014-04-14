#include <stdlib.h>
#include "linked_list.h"

List *ll_create_list(void)
{
  List *list = malloc(sizeof(List));
  if (list == NULL) {
    return NULL;
  }

  list->size = 0;
  list->head = NULL;
  list->tail = NULL;
  return list;
}

void ll_append_list_node(List *list, ListNode *node)
{
  if (list == NULL) { return; }

  if(list->head == NULL)
  {
    list->head = node;
    list->tail = node;
  } else 
  {
    ListNode *tail = list->tail;
    tail->next = node;
    list->tail = node;
  }

  list->size += 1;
}

void ll_prepend_list_node(List *list, ListNode *node)
{
  if (list == NULL) { return; }

  if(list->head == NULL)
  {
    list->head = node;
    list->tail = node;
  } else 
  {
    node->next = list->head;
    list->head = node;
  }

  list->size += 1;
}

void ll_free_list(List *list)
{
  int size = list->size;
  ListNode *current, *next;

  current = list->head;

  while(size--)
  {
    next = current->next;
    free(current);

    current = next;
  }

  free(list);
}
