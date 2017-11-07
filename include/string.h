#ifndef com_vincyapps_string_h
#define com_vincyapps_string_h
#include <clib/base_hdr.h>
int isValidString(string *input);
string * makeString(char *input);
string * makeEmptyString(string_t size);
string * copyString(string *input);
string * concatString(string *s1, string *s2);
string * cutString(string *strInput, int from, int to);
string * resizeString(string *input, int size);
string * replaceChars(string *strInput, string *strDelim, char replValue);
string * delinString(string *input,char delim);
string * delinString2 (string *input, string *delimeters);
string * stripString(string *input, char delim, int count);
string * stripString2(string *input, string *delimeters, int count);
string * stripString3(string *input, string * delimeters, int count, int from, int to);
string * stripStringFront(string *input, string *delimeters);
string * stripStringBack(string *input, string *delimiters);
int stringEqual(string *one, string *two);
stringlist * splitString(string *strInput, char delim);
stringlist * splitString2(string *strInput, string *strDelim);
int findIndexOfChar(string *input, char c, int count);
int findIndexOfChar2(string *strInput, string *strDelim, int count);
int findIndexOfString(string *input, string *term, char delim, int count );
//int stringContains ( string *input, string *term);
string_t getStringLength(string *input);
string_t getWordCount(string *input, char delim);
void printStringLn(string *input);
string * deleteString(string *input);
#endif

