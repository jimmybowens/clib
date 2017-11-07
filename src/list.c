#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list *listCreate(list *next, void *data, listDestructor destructor);
void defaultDestructor(void *data);
list *listAddFront( list *head, void *data, listDestructor destructor)
{
  list *alist = listCreate(head,data,destructor);
  head = alist;
  return head;
}
list *listAddBack( list *head, void *data, listDestructor destructor)
{
  if( head == NULL || destructor == NULL)
  {
    return head;
  }
  list *cursor = head;
  while( cursor->next != NULL)
  {
    cursor = cursor->next;
  }
  list *alist = listCreate(NULL,data,destructor);
  cursor->next = alist;
  return head;
}
list *listInsertAfter ( list *head, void *data, listCompareDataCallback callback, listDestructor destructor)
{
  if( head == NULL )
  {
    return listAddFront(head,data,destructor);
  }
  if( callback == NULL )
  {
    return listAddBack(head,data,destructor);
  }
  list *cursor = head;
  while( cursor != NULL )
  {
    if( callback (data, cursor->data) )
    {
      break;
    }
    cursor = cursor->next;
  }

  if( cursor != NULL )
  {
      list *newlist = listCreate(cursor->next,data,destructor);
      cursor->next = newlist;
      return head;
  }
  return listAddFront(head,data,destructor);
}
list *listInsertBefore ( list *head, void *data, list *alist, listDestructor destructor)
{
  if( head == NULL || alist == NULL )
  {
    return listAddFront(head,data,destructor); //alist cannot exist if head is null;
  }

  if( alist == head )
  {
    return listAddFront(head, data,destructor);
  }
  list *cursor = head;
  while( cursor != NULL )
  {
    if( cursor->next == alist )
    {
      break; 
    }
    cursor = cursor->next;
  }

  if( cursor != NULL )
  {
    list *newlist = listCreate(cursor->next, data, destructor);
    cursor->next = newlist;
    return head;
  }
  return listAddFront(head,data,destructor);
}

list *listRemoveFront ( list *head )
{
  if( head == NULL )
  {
    return NULL; //nothing to remove
  }
  list *cursor = head; //keep track of current head
  head = head->next; //move head forward by 1
  cursor->next = NULL;//unlink
  if( cursor == head )
  {
    head = NULL;
  }
  if( cursor->data != NULL)
  {
    cursor->destructor(cursor->data);
  }
  free(cursor);
  return head;
}
list *listRemoveByList ( list *head, list *del)
{
  if( del == NULL)
  {
    return head;
  }
  if( del == head )
  {
    head = listRemoveFront(head);
    return head;
  }
  if( del->next == NULL)
  {
    head = listRemoveBack(head);
    return head;
  }
  list *cursor = head;
  while( cursor != NULL )
  {
    if( cursor->next == del)
    {
      break;
    }
    cursor = cursor->next;
  }
  if( cursor != NULL )
  {
    list *tmp = cursor->next;
    cursor->next = tmp->next;
    tmp->next = NULL;
    if( tmp->data != NULL )
    {
      tmp->destructor(tmp->data);
    }
    free(tmp);
  }
  return head;
}
list *listRemoveBack ( list *head )
{
  if( head == NULL )
  {
    return NULL; //nothing to delete
  }
  list *cursor = head;//point to current head
  list *back = NULL;
  while( cursor->next != NULL )//look ahead
  {
    back = cursor;
    cursor = cursor->next;
  }
  if( back != NULL )
  {
    back->next = NULL;
  }
  if( cursor == head )
  {
    head = NULL;
  }
  if( cursor->data != NULL )
  {
    cursor->destructor(cursor->data);
  }
  free(cursor);
  return head;
}
/*list *listRemoveAll ( list *head )
{
  list *cursor, *tmp;
  if( head != NULL )
  {
    cursor = head;
    head = NULL;//free head from rest of list
    while( cursor != NULL )
    {
      tmp = cursor->next;
      if( cursor->data != NULL)
      {
	cursor->destructor(cursor->data);
      }
      free(cursor);
      cursor = tmp;
    }
  }
  return head;
}*/
list *listRemoveAll ( list *head )
{
  if( head == NULL )
  {
    return head;
  }
  list *cursor = head;
  head = NULL;
  while( cursor != NULL )
  {
    cursor=listRemoveFront(cursor);
  }
  return listRemoveAll(cursor);
}
void listTraverse ( list *head, listTraverseCallback callback )
{
  if( head != NULL && callback != NULL)
  {
    list *cursor = head;
    while( cursor != NULL )
    {
      callback(cursor->data);
      cursor = cursor->next;
    }
  }
}
list *listFindByIndex ( list *head, listInspectIndexCallback callback)
{
  return NULL;
}
list *listFindByValue ( list *head, listInspectDataCallback callback )
{
  if( head == NULL || callback == NULL )
  {
    return head;//empty list or no callback
  }
  list *cursor = head;
  while( cursor != NULL )
  {
    if( callback ( cursor->data))
    {
      return cursor;
    }
    cursor = cursor->next;
  }
  
  return head;//return head because value not found 
}

list *listCreate(list *next, void *data, listDestructor destructor)
{
  list *alist = (list *)malloc(sizeof( list ));
  if( alist == NULL )
  {
    fprintf(stderr, "Out of memory\n");
    exit(EXIT_FAILURE);
  }
  alist->data = data;
  alist->next = next;
  if( destructor == NULL )
  {
    alist->destructor = defaultDestructor;
  }else
  {
    alist->destructor = destructor;
  }
  alist->display = NULL;//TODO
  alist->index = 0;//TODO
  return alist;
}
void defaultDestructor(void *data)
{
  if( data != NULL)
  {
    free(data);
  }
}

list *listFind ( list *head, listFinder finder)
{
  if( head == NULL )
  {
    return head;
  }
  if( finder == NULL )
  {
    return NULL;
  }
  list *cursor = head;
  while( cursor != NULL )
  {
    if( finder(cursor))
    {
      return cursor;
    }
    cursor = cursor->next;
  }
  return NULL;
}
