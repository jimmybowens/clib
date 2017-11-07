#include <clib/output.h>
#include <clib/string.h>
#include <clib/error.h>
#include <clib/stringlist.h>

string * PARAM_GREEN = NULL;
string * PARAM_RED = NULL;
string * PARAM_BLUE = NULL;
string * PARAM_CYAN = NULL;
string * PARAM_WHITE = NULL;
string * PARAM_MAGENTA = NULL;
string * PARAM_YELLOW = NULL;

void colorizeString ( char *value )
{
  if( !colorProgramRunning ())
  {
    startColorProgram();
  }
  string *input = makeString ( value );
  if( isValidString ( input ))
  {
    stringlist *formatted = NULL;
    char *ptr = &input->value[0];
    int idx = 0;
    int skips = 0;
    int noskips = 0;
    int curr_range = 0;
    int start = 0;
    int end = 0;
    int insertIdx = 0;
    int printNewLine = 0;
    string *param = NULL;
    while( *ptr != '\0' )
    {      
      while( *ptr == ' ')
      {
	//printNewLine = ( ( *ptr == '\n') ? ( printNewLine + 1) : printNewLine );
	skips++;
	ptr++;
      }
      while( *ptr != '\0' )
      {
	if( *ptr == ' ' )
	{
	  break; 
	}
	noskips++;
	ptr++;
	curr_range = ( ( skips + noskips ) - idx );
      }
      start = ( ( idx == 0 ) ? idx : ( idx + 1) );
      end = ( idx + curr_range );
      insertIdx = 0;
      param = makeEmptyString ( ( end - start ) );
      for( int i = start; i < end; i++ )
      {
	param->value[insertIdx++] = input->value[i];  
      }
      formatted = stringlistAddBack ( formatted, param );
      idx = ( skips + noskips );
    }
    stringlist *iterator = NULL;
    for( iterator = formatted; ! stringlistEnd ( iterator ); iterator = stringlistNext ( iterator ))
    {
     if(isValidString ( iterator->data ) )
     {
       if( stringEqual ( iterator->data, PARAM_GREEN ) && iterator->next != NULL && isValidString ( iterator->next->data ))
       {
	  printf ( "%s%s ",COLOR_GREEN, iterator->next->data->value );
	  iterator = stringlistNext ( iterator );
       }
       else if( stringEqual ( iterator->data, PARAM_RED) && iterator->next != NULL && isValidString ( iterator->next->data ))
       {
	 printf ( "%s%s ",COLOR_RED, iterator->next->data->value );
	 iterator = stringlistNext ( iterator ); 
       }
       else if( stringEqual ( iterator->data, PARAM_YELLOW) && iterator->next != NULL && isValidString ( iterator->next->data ))
       {
	 printf ( "%s%s ",COLOR_YELLOW, iterator->next->data->value );
	 iterator = stringlistNext ( iterator ); 
       }
       else if( stringEqual ( iterator->data, PARAM_WHITE) && iterator->next != NULL && isValidString ( iterator->next->data ))
       {
	 printf ( "%s%s ",COLOR_WHITE, iterator->next->data->value );
	 iterator = stringlistNext ( iterator ); 
       }
       else if( stringEqual ( iterator->data, PARAM_BLUE) && iterator->next != NULL && isValidString ( iterator->next->data ))
       {
	 printf ( "%s%s ",COLOR_BLUE, iterator->next->data->value );
	 iterator = stringlistNext ( iterator ); 
       }
       else if( stringEqual ( iterator->data, PARAM_MAGENTA) && iterator->next != NULL && isValidString ( iterator->next->data ))
       {
	 printf ( "%s%s ",COLOR_MAGENTA, iterator->next->data->value );
	 iterator = stringlistNext ( iterator ); 
       }
       else if( stringEqual ( iterator->data, PARAM_CYAN) && iterator->next != NULL && isValidString ( iterator->next->data ))
       {
	 printf ( "%s%s ",COLOR_CYAN, iterator->next->data->value );
	 iterator = stringlistNext ( iterator ); 
       }
       else
       {
	 if( findIndexOfChar ( iterator->data, '\n',100) != -1)
	 {
	    printf ( "%s%s",COLOR_DEFAULT,iterator->data->value);  
	  
	 }else
	 {
	    printf ( "%s%s ",COLOR_DEFAULT,iterator->data->value);
	 }
       }
     }
    }
    formatted = stringlistDestroy ( formatted );
    input = deleteString ( input );
  }
  stopColorProgram();
  //printf ( "Value: %s%s %sGOOD",COLOR_RED,input->value,COLOR_MAGENTA);
}

int colorProgramValidate ( string *param )
{
  if( ! colorProgramRunning () )
  {
    startColorProgram ();
  }
  if( !isValidString ( param ))
  {
    if( stringEqual ( param, PARAM_RED ))
    {
      stopColorProgram();
      return 31;;
    }else if( stringEqual ( param, PARAM_GREEN ))
    {
      stopColorProgram();
      return 32;
    }else if( stringEqual ( param, PARAM_YELLOW ))
    {
      stopColorProgram();
      return 33;
    }else if( stringEqual ( param, PARAM_BLUE ))
    {
      stopColorProgram();
      return 34;
    }else if( stringEqual ( param, PARAM_MAGENTA ))
    {
      stopColorProgram();
      return 35;
    }else if( stringEqual ( param, PARAM_CYAN ))
    {
      stopColorProgram();
      return 36;
    }else if( stringEqual ( param, PARAM_WHITE ))
    {
      stopColorProgram();
      return 37;
    }else
    {
      stopColorProgram();
      return -1;
    }
  }
  stopColorProgram();
  return -1;
}

int colorProgramRunning(void)
{
  return ( ( PARAM_GREEN != NULL ) || ( PARAM_RED != NULL ) || ( PARAM_BLUE != NULL ) || ( PARAM_CYAN != NULL ) || ( PARAM_WHITE != NULL ) || ( PARAM_MAGENTA != NULL ) || ( PARAM_YELLOW != NULL));
}

void startColorProgram(void)
{
  if( ! colorProgramRunning ())
  {
    PARAM_GREEN = makeString ( "--green" );
    PARAM_RED = makeString ( "--red" );
    PARAM_BLUE = makeString ( "--blue");
    PARAM_CYAN = makeString ( "--cyan" );
    PARAM_MAGENTA = makeString ( "--magenta" );
    PARAM_WHITE = makeString ( "--white" );
    PARAM_YELLOW = makeString ( "--yello" );
  }
}

void stopColorProgram(void)
{
  PARAM_GREEN = deleteString ( PARAM_GREEN );
  PARAM_RED = deleteString ( PARAM_RED );
  PARAM_BLUE = deleteString ( PARAM_BLUE );
  PARAM_CYAN = deleteString ( PARAM_CYAN );
  PARAM_WHITE = deleteString ( PARAM_WHITE );
  PARAM_YELLOW = deleteString ( PARAM_YELLOW );
  PARAM_MAGENTA = deleteString ( PARAM_MAGENTA );
}
