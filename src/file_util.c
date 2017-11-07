#include "base_hdr.h"
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <clib/memory_util.h>
#include <clib/file_util.h>
#include <clib/string.h>
string *currentDirectory(void)
{
  char *cwd = NULL;
  cwd = getcwd(0,0);
  if( cwd == NULL )
  {
    return NULL;
  }
  string *result = makeString ( cwd );
  free ( cwd );
  return result;
}
int makeDirectory(string *path)
{
  int status = 0;
  if( ! isValidString ( path ))
  {
    return 0;
  }
  status  = mkdir(path->value, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  if (status == 0)
  {
    return 1;
  }else if(status == -1)
  {
    return 1;
  }else
  {
    return 0;
  }
}

int isDirectory(string *path)
{
  if( ! isValidString ( path ))
  {
    return 0;
  }
  DIR *dir = NULL;
  dir = opendir(path->value);
  if(dir != NULL)
  {
    closedir(dir);
    return 1;
  }else if(ENOENT == errno)
  {
    return 0;
  }
  else
  {
    return 0;
  }
}

int isFile(string *path)
{
  if( ! isValidString ( path ))
  {
    return 0;
  }

  if(isDirectory(path))
  {
    return 0;
  }

  FILE *fptr = NULL;

  fptr = fopen(path->value,"r");

  if (fptr != NULL)
  {
    fclose(fptr);
    return 1;
  }else
  {
    return 0;
  }
}

struct fileDoc *initFileDoc()
{

  struct fileDoc *doc = (struct fileDoc *) memAlloc(sizeof(struct fileDoc),NULL);
  doc->size = 100;
  doc->len = 0;
  doc->lines = NULL;
  doc->lines = (char **) memAlloc(100 * sizeof(char *),NULL);
  for (int i = 0; i < 100; i++)
  {
    doc->lines[i] = NULL;
  }
  return doc;
}

struct fileDoc *destructFileDoc(struct fileDoc *doc)
{
  if(doc == NULL)
  {
    return NULL;
  }

  if(doc->lines != NULL)
  {
    for(int i = 0; i < doc->size; i++)
    {
      memDeAlloc(doc->lines[i]);
    }
    memDeAlloc(doc->lines);
  }
 memDeAlloc(doc);
 return NULL;
}

int addLine(struct fileDoc *doc, char *line)
{
  if(doc == NULL)
  {
    return 0;
  }

  if(line == NULL || line == '\0')
  {
    return 0;
  }

  if(doc->len >= doc->size)
  {
    return 0;
  }

  int lineLen=0;
  char *linePtr = &line[0];
  while(*linePtr++ != '\0')
  {
    lineLen++; 
  }
  lineLen++;//for new line char
  char * newLine = (char *) memAlloc(lineLen * sizeof(char),NULL);
  newLine[lineLen] = '\0';
  newLine[(lineLen - 1)] = '\n';
  linePtr = &line[0];
  int dx = 0;
  while(*linePtr != '\0')
  {
    newLine[dx++] = *linePtr++;
  }
  doc->lines[doc->len] = newLine;
  doc->len++;
  return 0;
};

void printLines(struct fileDoc *doc)
{
  if(doc != NULL)
  {
    if(doc->lines != NULL)
    {
      for (int i = 0; i < doc->len; i++)
      {
	printf("%s\n", doc->lines[i]);
      }
    }
  }
}

int removeAllLines(struct fileDoc *doc)
{
  if(doc == NULL)
  {
    return 0;
  }

  if(doc->lines != NULL)
  {
    for(int i = 0; i < doc->size;i++)
    {
      memDeAlloc(doc->lines[i]);
      doc->lines[i] = NULL;
    }
  }
  return 1;
}

int flushLines(struct fileDoc *doc, char *path, char *mode)
{
  if(doc == NULL)
  {
    return 0;
  }
  if(path == NULL || path == '\0')
  {
    return 0;
  }

  if(mode == NULL || mode == '\0')
  {
    return 0;
  }

  FILE *fptr = NULL;
  fptr = fopen(path, mode);
  if(fptr == NULL)
  {
    return 0;
  }

  for(int i = 0; i < doc->len; i++)
  {
    fprintf(fptr, "%s", doc->lines[i]);
  }
  fclose(fptr);
  if(removeAllLines(doc))
  {
    doc->len = 0;
  }
  return 1;
}

