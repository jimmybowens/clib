#ifndef com_vincyapps_list_h
#define com_vincyapps_list_h
#include <clib/base_hdr.h>
list *listAddFront( list *head, void *data, listDestructor destructor);
list *listAddBack( list *head, void *data, listDestructor destructor );
list *listInsertAfter ( list *head, void *data, listCompareDataCallback callback, listDestructor destructor);
list *listInsertBefore ( list *head, void *data, list *alist, listDestructor destructor);
list *listRemoveFront ( list *head );
list *listRemoveByList ( list *head, list *del);
list *listRemoveBack ( list *head );
list *listRemoveAll ( list *head );
list *listRemoveByIndex ( list *head, listInspectIndexCallback callback);
list *listRemoveByValue ( list *head, listInspectDataCallback callback);
list *listFindByIndex ( list *head, listInspectIndexCallback callback);
list *listFindByValue ( list *head, listInspectDataCallback callback );
void listTraverse ( list *head, listTraverseCallback callback );
list *listFind ( list *head, listFinder finder);
#endif
