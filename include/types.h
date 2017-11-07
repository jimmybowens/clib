#ifndef COM_VINCY_APPS_TYPES_H
#define COM_VINCY_APPS_TYPES_H

#define COLOR_DEFAULT "\x1B[0m"
#define COLOR_RED "\x1B[31m"
#define COLOR_GREEN "\x1B[32m"
#define COLOR_YELLOW "\x1B[33m"
#define COLOR_BLUE "\x1B[34m"
#define COLOR_MAGENTA "\x1B[35m"
#define COLOR_CYAN "\x1B[36m"
#define COLOR_WHITE "\x1B[37m"

//string
struct xstring
{
  char * value;
};
struct xstring_array
{
  struct xstring **value;
  unsigned int len;
};
typedef struct xstring string;
typedef struct xstring_array string_array;
typedef unsigned int string_t;
//stringlist
struct cs_stringlist
{
  int index;
  string * data;
  struct cs_stringlist *next
};
typedef struct cs_stringlist stringlist;
typedef void ( *stringlistTraverser )( stringlist *item );
//generic list
typedef void (*listDestructor)(void *data);
typedef void (*listDisplay)(void *data);
struct xlist
{
  listDestructor destructor;
  listDisplay display;
  int index;
  void *data;
  struct xlist *next;
};
typedef struct xlist list;
typedef int( *listCompareDataCallback)( void *data1, void *data2 );
typedef int( *listInspectDataCallback)( void *data );
typedef int( *listInspectIndexCallback)( int index );
typedef void( *listTraverseCallback)( void *data);
typedef void *( *listMakeDataCallback)(void *data);
typedef int ( *listFinder )(list *current);
//filedoc
struct fileDoc{
  char ** lines;
  unsigned int size;
  unsigned int len;
};
#endif
