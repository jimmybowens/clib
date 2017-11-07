#include <clib/base_hdr.h>
#include <clib/string.h>

void die (string *message, int code)
{
  do
  {
    if( isValidString ( message ))
    {
      fprintf ( stderr, "%s%s\n", COLOR_RED, message->value );
      deleteString ( message );
    }else
    {
       fprintf ( stderr, "an error has occured...aborting!\n" );
    }
    exit ( ( code > 0 ) ? code : EXIT_FAILURE );
  }while( 0 );
}
