#ifndef COM_VINCY_APPS_FILE_UTIL_H
#define COM_VINCY_APPS_FILE_UTIL_H
#include <clib/base_hdr.h>
#include <clib/string.h>
int makeDirectory(string *path);
int isDirectory(string *path);
int isFile(string *path);
string *currentDirectory(void);

struct fileDoc *initFileDoc();
int addLine(struct fileDoc *doc, char *line);
void printLines(struct fileDoc *doc);
int flushLines(struct fileDoc *doc, char *path, char *mode);
struct fileDoc *destructFileDoc(struct fileDoc *doc);
#endif /*UTIL_FILE_H*/
