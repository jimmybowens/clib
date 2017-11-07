#include <clib/stringlist.h>
#include <clib/string.h>
#include <clib/command.h>
#include <clib/output.h>

int main(int argc, char *argv[]){
/*  stringlist *head = NULL;
  head = stringlistAddFront (head, makeString ( "hello" )); 
  stringlist *iterator = NULL;
  for( iterator = head; ! stringlistEnd(iterator); iterator = stringlistNext(iterator))
  {
   // stringlistPrint ( iterator, 1);    
  }
  //printf("%d\n",stringlistEnd (head));
  head = stringlistDestroy(head);


  string *test = makeString ( "the fox --directory --command-type" );
  string *term = makeString ( "fox" );
//  printf ( "%d\n", stringContains ( test, term ) );
  printf ( "%d\n", findIndexOfString ( test, term, ' ',-1 ));
  printf ( "%d\n", findIndexOfChar ( test,'f',1));

  int index = -1;
  if( ( index = findIndexOfChar ( test , 'f',1)) != -1)
  {
    printf ( "%c\n", test->value[index]);
  }
  test = deleteString ( test );
  term = deleteString ( term );*/
  char output[1024];
  int read = 0;
  //char *acommand = "--red red --green green --blue blue --cyan cyan --magenta magenta --white white\n";
  colorizeString ( "--red Hello\n\t --green How are you?" );
  colorizeString ( "Hello2");
  return 0;
}
