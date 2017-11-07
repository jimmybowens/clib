#ifndef COM_VINCY_APPS_MEMORY_UTIL_H
#define COM_VINCY_APPS_MEMORY_UTIL_H
#define MEMORY_ERROR 200
void * memAlloc(unsigned int size, void (*handler)( int code));
void * memDeAlloc(void * el);
#endif /*UTIL_MEMORY_H*/
