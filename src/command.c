#include <clib/base_hdr.h>
#include <clib/command.h>
#include <clib/stringlist.h>
#include <clib/error.h>
int run (int argc, char *argv[], char output[],int outputsize, int *read);
int clean ( int argc, char *argv[], int ret);
int runCommand (string *c,char output[], int outputsize, int *read)
{
  if( !isValidString ( c ))
  {
    return 0;
  }
  string_t len = getStringLength ( c );
  char *ptr = &c->value[0];
  int skips = 0;
  int noskips = 0;
  int idx = 0;
  int curr_range = 0;
  int start = 0;
  int end = 0;
  int datalen = 0;
  while( *ptr != '\0')
  {
    while( *ptr == ' ')
    {
      skips++;
      ptr++;
    }
    while( *ptr != '\0')
    {
      if( *ptr == ' ')
      {
	break;
      }
      noskips++;
      ptr++;
    }
    idx = ( skips + noskips );
  }
  datalen = noskips;
  char *args[datalen];
  int addIdx = 0;
  for( int i = 0; i < datalen; i++)
  {
    args[i] = NULL;
  }
  ptr = &c->value[0];
  idx = 0;
  skips = 0;
  noskips = 0;
  int insertIdx = 0;
  while( *ptr != '\0' )
  {
    while( *ptr == ' ' )
    {
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
      curr_range = ( ( skips + noskips) - idx );
    }
    start = ( ( idx == 0 ) ? idx : ( idx + 1) );
    end = ( idx + curr_range );
    args[addIdx] = ( char * ) malloc ( ( curr_range + 1) * sizeof( char ));
    if( args[addIdx] == NULL )
    {
      fprintf(stderr, "Out of memory\n");
      exit ( EXIT_FAILURE );
    }
    args[addIdx][curr_range] = '\0';
    insertIdx = 0;
    for( int i = start; i < end; i++)
    {
      args[addIdx][insertIdx++] = c->value[i];
    }
    addIdx++;
    idx = ( skips + noskips );
  }

  return run ( datalen, args, output, outputsize, read);
}

int run (int argc, char *argv[], char output[], int outputsize, int *readBytes)
{
  pid_t pid;
  int status;
  int pipes[2];
  if( pipe ( pipes ) == -1)
  {
   die ( makeString ( "could not create pipes"),1); 
  }

  if( ( pid = fork() ) < 0 )
  {
    return clean ( argc, argv, 0);
  }else if( pid == 0 )
  {
    dup2 ( pipes[1],STDOUT_FILENO);
    close ( pipes[0]);
    close ( pipes[1]);
    if( execvp ( *argv, argv ) < 0 )
    {
      return clean ( argc, argv, 0);
    }
  }else
  {
    close ( pipes[1]);
    *readBytes = read ( pipes[0],output, outputsize );
    while( wait (&status) != pid );
  }
  return clean ( argc, argv, 1);
}

int clean ( int argc, char *argv[], int ret)
{
  for( int i = 0; i < argc; i++ )
  {
    if( argv[i] != NULL )
    {
      free ( argv[i]);
    }
  }
  return ret; 
}
