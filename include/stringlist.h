#ifndef COM_VINCY_APPS_STRINGLIST_H
#define COM_VINCY_APPS_STRINGLIST_H
#include <clib/base_hdr.h>
int stringlistEnd ( stringlist *iterator );
stringlist *stringlistNext ( stringlist *iterator );
stringlist *stringlistBreak ( stringlist *iterator );
stringlist *stringlistAddFront ( stringlist *head, string *data);
stringlist *stringlistAddBack ( stringlist *head, string *data);
stringlist *stringlistRemoveFront ( stringlist *head );
stringlist *stringlistRemoveBack ( stringlist *head );
stringlist *stringlistDestroy ( stringlist *head);
stringlist *stringlistSort ( stringlist *head );
stringlist *stringlistFindByIndex ( stringlist *head, unsigned long index);
void stringlistPrint ( stringlist *head, int count);
unsigned long stringlistLength ( stringlist *head );
void stringlistTraverse ( stringlist *head, stringlistTraverser traverser);
#endif
