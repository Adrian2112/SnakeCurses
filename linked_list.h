#include <stdlib.h>

typedef struct ListNode 
{
  struct ListNode *next;
  void *value;
} ListNode;

typedef struct List
{
  size_t size;
  ListNode *head;
  ListNode *tail;
} List;

List *ll_create_list(void);
void ll_append_list_node(List *list, ListNode *node);
void ll_free_list(List *list);
