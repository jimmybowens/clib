#include <clib/base_hdr.h>
#include <clib/stringlist.h>
#include <clib/string.h>
stringlist *stringlistCreate(stringlist *head, string *data, unsigned long index);
int stringlistEnd ( stringlist *current )
{
  return ( current == NULL );
}
stringlist *stringlistNext ( stringlist *current )
{
   if( current == NULL )
   {
      return current;
   }
   return current->next;
}
stringlist *stringlistBreak ( stringlist *current )
{
  current = NULL;
  return current;
}
void stringlistTraverse ( stringlist *head, stringlistTraverser traverser)
{
  if( head != NULL )
  {
    if( traverser != NULL )
    {
      stringlist *cursor = head;
      while( cursor != NULL )
      {
	traverser ( cursor );
	cursor = cursor->next;
      }
    }
  }
}
unsigned long stringlistLength ( stringlist *head )
{
  unsigned long len = 0;
  if( head == NULL )
  {
    return len;
  }
  stringlist *cursor = head;
  while( cursor != NULL )
  {
    len++;
    cursor = cursor->next;
  }
  return len;
}
void stringlistPrint ( stringlist *head, int count)
{
  int idx = 0;
  if( head != NULL )
  {
    stringlist *cursor = head;
    while( cursor != NULL )
    {
      if( (count >= 0) && (idx == count) )
      {
	break;
      }
      if( cursor->data != NULL )
      {
	printf("%d ", cursor->index);
	printStringLn ( cursor->data );
      }
      cursor = cursor->next;
      idx++;
    }
  }else
  {
    printf ( "NULL\n" );
  }
}
stringlist *stringlistAddFront ( stringlist *head, string *data)
{
  stringlist *alist = stringlistCreate ( head, data, ( stringlistLength ( head ) + 1));
  head = alist;
  return head;
}
stringlist *stringlistAddBack ( stringlist *head, string *data)
{
  if( head == NULL )
  {
    return stringlistAddFront (head, data);
  }
  stringlist *cursor = head;
  while( cursor->next != NULL )
  {
    cursor = cursor->next;
  }
  stringlist *alist = stringlistCreate ( NULL, data, ( stringlistLength ( head ) + 1));
  cursor->next = alist;
  return head;
}
stringlist *stringlistRemoveFront ( stringlist *head )
{
 if( head == NULL )
 {
    return head;
 }
 stringlist * cursor = head;
 head = head->next;
 cursor->next = NULL;
 if( cursor == head )
 {
  head = NULL;
 }
 if( cursor->data != NULL )
 {
   cursor->data = deleteString(cursor->data);
 }
 free(cursor);
 return head;
}
stringlist *stringlistRemoveBack ( stringlist *head )
{
  if( head == NULL )
  {
    return head;
  }
  stringlist *cursor = head;
  stringlist *back = NULL;
  while( cursor->next != NULL )
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
    cursor->data = deleteString(cursor->data);
  }
  free(cursor);
  return head;
}
stringlist *stringlistDestroy ( stringlist *head)
{
  if( head == NULL )
  {
    return head;
  }
  stringlist *cursor = head;
  head = NULL;
  while( cursor != NULL )
  {
    cursor = stringlistRemoveFront(cursor);
  }
  return stringlistDestroy(cursor);
}
stringlist *stringlistSort ( stringlist *head )
{
   if( head == NULL )
   {
      return head;
   }
   stringlist *x,*y,*e;
   x = head;
   head = NULL;
   while( x != NULL )
   {
      e = x;
      x = x->next;
      if( head != NULL )
      {
	if( e->index > head->index )
	{
	  y = head;
	  while( ( y->next != NULL ) && ( e->index > y->next->index ))
	  {
	    y = y->next;
	  }
	  e->next = y->next;
	  y->next = e;
	}else
	{
	  e->next = head;
	  head = e;
	}
      }else
      {
	e->next = NULL;
	head = e;
      }
   }
   return head;
}
stringlist * stringlistFindByIndex ( stringlist *head, unsigned long index)
{
  if( head == NULL )
  {
    return NULL;
  }
  stringlist *cursor = head;
  while( cursor != NULL )
  {
    if( cursor->index == index )
    {
      return cursor;
    }
    cursor = cursor->next;
  }
  return NULL;
}
stringlist *stringlistCreate(stringlist *head, string *data, unsigned long index)
{
  stringlist * alist = NULL;
  alist = (stringlist *) malloc(sizeof( stringlist ));
  if( alist == NULL )
  {
    fprintf(stderr, "Out of memory\n");
    exit(EXIT_FAILURE);
  }
  alist->index = index;
  alist->data = data;
  alist->next = head;
  return alist;
}
