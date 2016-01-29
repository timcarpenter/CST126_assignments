//
// CST 126 - Assignment #2
//
// Author: Michael Hoffman
//
// File: crypto.cpp
//
// This file contains a menu-based test program
// for the encryption/decryption of messages.
//


#define _CRT_SECURE_NO_WARNINGS
  //
  // This is needed to supress Microsoft's compiler from generating
  // annoying C4996 warning messages for strcpy()


#include  <cstring>
#include  <cctype>
#include  <iostream>
#include  <cstdlib>
#include  "algorithms.h"

using  namespace  std;


//
// Constants/macros
//

#define  MENU_INPUT_SIZE   10
#define  ALPHABET          "abcdefghijklmnopqrstuvwxyz"

#define  NUM_ARRAY_ENTRIES(a)  ( sizeof(a)/sizeof(*a) )


//
// Enumerated types for the menu system
//

enum  Algorithm
{
  algorithmNone_  =  -1,
  algorithmCaesar_,
  algorithmSubstitution_,
  algorithmVigenere_,
  algorithmTransposition_
};

enum  Action
{
  actionNone_  =  -1,
  actionEncrypt_,
  actionDecrypt_
};

enum  Menu
{
  menuMain_  =  0,
  menuAlgorithms_,
};


//
// Menu table type definitions
//
typedef void  (*MenuHandler)( int );

struct  MenuChoice
{
  const char   *choices;
  const char   *text;
  MenuHandler   handler;
  int           parameter;
};
 

//
// menu handler prototypes
//
static void  mnuNewMessage( int );
static void  mnuAction( int  action );
static void  mnuAlgorithm( int  algorithm );
static bool  processMenu( Menu  menuIdx );


//
// Menu tables
//
static const MenuChoice  mainMenu[]  =
                       {
                         {  "1", "1. Set the message", mnuNewMessage, actionNone_    },
                         {  "2", "2. Encrypt",         mnuAction,     actionEncrypt_ },
                         {  "3", "3. Decrypt",         mnuAction,     actionDecrypt_ },
                         { "Qq", "Q. Quit",            0,             actionNone_    }
                       };

static const MenuChoice  algorithmMenu[]  =
                 {
                   {  "1", "1. Caesar",              mnuAlgorithm, algorithmCaesar_        },
                   {  "2", "2. Substitution",        mnuAlgorithm, algorithmSubstitution_  },
                   {  "3", "3. Vigenere",            mnuAlgorithm, algorithmVigenere_      },
                   {  "4", "4. Transposition",       mnuAlgorithm, algorithmTransposition_ },
                   { "Mm", "M. Return to main menu", 0,            algorithmNone_          }
                 };


//
// Convert a string to lowercase
//
void  strToLower( char  str[] )
{
  for( ; *str; ++str )
    *str  =  tolower(*str);
}


//
// Menu header type definitions
//
typedef void  (*MenuHeaderHandler)( void );

struct  MenuEntry
{
        MenuHeaderHandler   headerHandler;
  const MenuChoice         *choices;
  int                       numEntries;
};


//
// Menu header prototypes
//
static void  mainMenuHeader(void);
static void  algorithmMenuHeader(void);


//
// Menu header tables
//
static const MenuEntry  menus[]  =
    {
      { mainMenuHeader,      mainMenu,      NUM_ARRAY_ENTRIES(mainMenu)      },
      { algorithmMenuHeader, algorithmMenu, NUM_ARRAY_ENTRIES(algorithmMenu) }
    };



//
// Current message/action values
//
static char    message[MAX_MSG_SIZE];
static Action  currentAction;


//
// Key generation and validation type definitions
//
typedef void  (*GenerateFunc)( char  * );
typedef bool  (*ValidationFunc)( const char  * );


//
// Key generation and validation prototypes
//

static void  generateKeySubstitution( char  *str );

static bool  validKeySubstitution( const char  *keyStr );
static bool  validKeyVigenere( const char  *keyStr );
static bool  validKeyTransposition( const char  *keyStr );


//
// Algorithm type defintions
//
struct  AlgorithmKey
{
  const char      *name;
  const char      *instructions;
  GenerateFunc     generate;
  ValidationFunc   valid;
  char             keyStr[MAX_MSG_SIZE];
};


//
// Algorithm tables
//
static AlgorithmKey  keys[]  =
                         {
                           {
                             "Caesar",
                             "a whole number",
                             0,
                             0,
                             "0"
                           },
                           {
                             "Substitution",
                             "random generator numeric seed value",
                             generateKeySubstitution,
                             validKeySubstitution,
                             ALPHABET
                           },
                           {
                             "Vigenere",
                             "a single word of letters only",
                             0,
                             validKeyVigenere,
                             "z"
                           },
                           {
                             "Transposition",
                             "a row size greater than 1",
                             0,
                             validKeyTransposition,
                             ""
                           }
                         };


//
// Key generation routines
//

  //
  // Generate a substitution alphabet string based
  // on a random number seed.
  //
static void  generateKeySubstitution( char  *str )
{
  srand( atol(str) );

  memset( str, 0, MAX_MSG_SIZE );

  int  idx = 0;
  while( idx < NUM_CHARACTERS )
  {
    char  nextChar  =  rand() % NUM_CHARACTERS  +  MIN_ASCII_VALUE;

    if  ( strchr(str, nextChar) )
      continue;

    str[idx++]  =  nextChar;
  }

}


//
// Key validation routines
//

  //
  // All characters must be unique lowercase letters
  //
static bool  validKeySubstitution( const char  *keyStr )
{
  if  ( strlen(keyStr) != 'z'-'a'+1 )  return  false;

  for( char  c='a';  c <= 'z';  ++c )
  {
    if  (! strchr(keyStr, c) )  return  false;
  }

  return  true;
}


  //
  // Must be a single word made up of only
  // lowercase alphabetic characters
  //
static bool  validKeyVigenere( const char  *keyStr )
{
  for( size_t  i = 0;  i < strlen(keyStr);  ++i )
  {
    if  ( ! strchr(ALPHABET, keyStr[i] ) )  return  false;
  }

  return  true;
}


  //
  // Must be an integer >= 2
  //
static bool  validKeyTransposition( const char  *keyStr )
{
  return  atoi(keyStr)  >=  2;
}


//
// Menu routines
//

static void  mainMenuHeader(void)
{
  cout  <<  endl
        <<  "********************"  <<  endl
        <<  "*** Message Text ***"  <<  endl  <<  endl
        <<  message                 <<  endl  <<  endl
        <<  "********************"  <<  endl
        <<  "********************"  <<  endl
        <<  endl
        <<  "Main Menu:";
}


static void  algorithmMenuHeader(void)
{
  cout  <<  "Algorithm Menu:";
}


static void  mnuNewMessage( int )
{
  cout  <<  endl  <<  "Enter new message: ";

  cin.getline( message, MAX_MSG_SIZE );

  strToLower(message);
}


static void  mnuAction( int  action )
{
  currentAction  =  Action(action);

  processMenu( menuAlgorithms_ );
}


//
// If blank is entered, use the existing key value.
// Otherwise, generate/validate the key as defined
// in the algorithms table.
//
static void  optionallySetKey( AlgorithmKey  &key )
{
  char  userInput[MAX_MSG_SIZE];

  while(true)
  {
    cout  <<  endl  <<  "Key: ";


    cin.getline( userInput, MAX_MSG_SIZE );

    if  ( ! strlen(userInput) )  return;

    if  ( key.generate )  key.generate( userInput );

    if  ( ! key.valid )  break;

    if  ( key.valid( userInput ) )  break;

    cout  <<  "Invalid entry. Try again."  <<  endl;
  }

  strcpy( key.keyStr, userInput );

  strToLower(key.keyStr);
}


//
// Algorithm execution
//
static void  executeAlgorithm( Algorithm  algorithm )
{
  AlgorithmKey  &key  =  keys[algorithm];

  char  result[MAX_MSG_SIZE];

  if  ( currentAction == actionEncrypt_ )
  {
    switch( algorithm )
    {
      case  algorithmCaesar_         :  caesarEncrypt( message, result, atoi(key.keyStr) );         break;
      case  algorithmSubstitution_   :  substitutionEncrypt( message, result, key.keyStr );         break;
      case  algorithmVigenere_       :  vigenereEncrypt( message, result, key.keyStr );             break;
      case  algorithmTransposition_  :  transpositionEncrypt( message, result, atoi(key.keyStr) );  break;
    }
  }
  else
  {
    switch( algorithm )
    {
      case  algorithmCaesar_         :  caesarDecrypt( message, result, atoi(key.keyStr) );         break;
      case  algorithmSubstitution_   :  substitutionDecrypt( message, result, key.keyStr );         break;
      case  algorithmVigenere_       :  vigenereDecrypt( message, result, key.keyStr );             break;
      case  algorithmTransposition_  :  transpositionDecrypt( message, result, atoi(key.keyStr) );  break;
    }
  }

  strcpy( message, result );
}


//
// Algorithm processing routine
//
static void  mnuAlgorithm( int  algorithm )
{
  AlgorithmKey  &key  =  keys[algorithm];
  
  cout  <<  endl
        <<  "Algorithm   : "  <<  key.name                     <<  endl
        <<  "Current key : "  <<  key.keyStr                   <<  endl
        <<  endl
        <<  "For new key enter "  <<  key.instructions << '.'  <<  endl
        <<  "To keep current key press ENTER."                 <<  endl;

  optionallySetKey( key );

  executeAlgorithm( Algorithm(algorithm) );
}


//
// Menu display routine
//
static void  displayMenu( const MenuEntry  &menu )
{
  cout  <<  endl;

  menu.headerHandler();

  cout  <<  endl;

  for( int  i = 0;  i < menu.numEntries;  ++i )
  {
    cout  <<  "  "  <<  menu.choices[i].text  <<  endl;
  }
}


//
// Routine to get a menu choice from the user
//
static int  getChoice( const MenuEntry  &menu )
{
  char  choice[MENU_INPUT_SIZE];
  bool  done  =  false;
  int   index;

  while( true )
  {
    cout  <<  endl  <<  "Choice : ";

    cin.getline(choice, MENU_INPUT_SIZE);

    for( index=0;  index < menu.numEntries;  ++index )
    {
      if  ( strchr( menu.choices[index].choices, choice[0]) )
      {
        done = true;
        break;
      }
    }

    if  (done)  break;

    cout  <<  "Invalid entry. Try again."  <<  endl;
  }

  return  index;
}


//
// Returns true if a handler was called. Otherwise returns false.
//
static bool  processMenu( Menu  menuIdx )
{
  const MenuEntry  &menu  =  menus[menuIdx];

  displayMenu( menu );

  int  index  =  getChoice( menu );

  if  ( ! menu.choices[index].handler )
    return  false;

  menu.choices[index].handler( menu.choices[index].parameter );

  return  true;
}


//
// Main program
//
int  main()
{
  mnuNewMessage(0);

  while( processMenu( menuMain_ ) )
    ;

  return  0;
}
