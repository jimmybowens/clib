#include "base_hdr.h"
#include "memory_util.h"
void * memAlloc(unsigned int size, void ( *handler)( int code ))
{
  void *ret = NULL;
  ret = malloc(size);
  if (ret == NULL)
  {
    if( handler == NULL )
    {
      handler(MEMORY_ERROR);
    }
    else{ 
      fprintf(stderr, "Out of memory\n");
      exit(MEMORY_ERROR);
    }
  }
  return ret;
}

void * memDeAlloc(void *el)
{
  if(el != NULL)
  {
    free(el);
    return NULL;
  }else
  {
    return NULL;
  }
}


















char *memAllocString(int size, void ( *handler)( int code ))
{
  char *string = NULL;
  string = (char *) memAlloc((size + 2) * sizeof(char), handler);
  string[size] = '\0';
  string[size+1] = '\x24';
  return string;
}

int isMemAllocString(char *input)
{
  if( input == NULL || input == '\0')
  {
    return 0;
  }
  char *ptr = &input[0];
  while( *ptr++ != '\0')
  {

  }
  if( *ptr == '\x24')
  {
    return 1;
  }
  return 0;
}

int * memAllocInt(int size, void ( *handler )( int code))
{
  int * i = NULL;
  i = (int *) memAlloc ( size * sizeof( int), handler);
  return i;
}

char ** memAllocStringArray(int size, void ( *handler )( int code ))
{
  char **array = NULL;
  array = (char **) memAlloc( (size + 1) * sizeof ( char ), handler );
  for( int i = 0; i < size; i++)
  {
    array[i] = NULL;
  }
  return array;
}

int ** memAllocIntArray( int size, void ( *handler )( int code ))
{
  int **array = NULL;
  array = (int **) memAlloc(size * sizeof( int ), handler);
  for( int i = 0; i < size; i++)
  {
    array[i] = NULL;
  }
  return array;
}
char * destroyString(char *s)
{
  if( s == NULL )
  {
    return NULL;
  }
  else
  {
    free(s);
    return NULL;
  }
}

int * destroyInt( int *i)
{
  if( i == NULL )
  {
    return NULL;
  }else
  {
    free(i);
    return NULL;
  }
}

char ** destroyStringArray(char **a, int size)
{
  if( a == NULL)
  {
    return NULL; 
  }
  else
  {
    for( int i = 0; i < size; i++)
    {
      destroyString(a[i]);
    }
    free(a);
    return NULL;
  }
}

int ** destroyIntArray(int **a, int size)
{
  if( a == NULL)
  {
    return NULL;
  }else
  {
    for( int i = 0; i < size; i++)
    {
      destroyInt(a[i]);
    }
    free(a);
    return NULL;
  }
}
