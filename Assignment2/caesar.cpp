//
// Tim Carpenter
//
// CST126 - Assignment 2
//
// caesar.cpp implementation

#include <string.h>
#include <math.h>
//#include <iostream> 
#include "algorithms.h"

//using namespace std; 

static int conversionKey(int originalKey)
{
   // take absolute value of original key to remove negative numbers
   int convertedKey = abs(originalKey);

   // calculate key for ints bigger than NUM_CHAR range; set key to modulus of key and NUM_CHAR
   convertedKey = convertedKey % NUM_CHARACTERS;

   //cout << "convertedKey after: " << convertedKey << endl; //testing of key output

   //if key is negative, subtract absolute value from character
   if (originalKey < 0)
   {
	  convertedKey = NUM_CHARACTERS - convertedKey;
   }

   return convertedKey;
}


// Encryption function
void  caesarEncrypt(const char plaintext[], char ciphertext[], int key)
{
   // process encrypt key for ciphertext usage
   int encryptKey = conversionKey(key);

   // define string length of plaintext for use in for loop processing
   size_t length = strlen(plaintext);

   // counter
   size_t count;

   // size_t note: use for variables that model size or index in array. 
   // usage conveys semantics: the variable represents size in bytes or idx
   // also helps makes code portable
   
   // 
   for (count = 0; count < length; ++count)
   {
	  // use char_out_of_range macro from header
	  // carry over non character symbols (char_out_of_range) from plaintext to ciphertext
	  if (CHAR_OUT_OF_RANGE(plaintext[count]))
	  {
		 ciphertext[count] = plaintext[count];
		 continue;
	  }


	  //
	  char character = plaintext[count] - MIN_ASCII_VALUE;

	  character += encryptKey % NUM_CHARACTERS;
	  character %= NUM_CHARACTERS;

	  ciphertext[count] = character + MIN_ASCII_VALUE;

   }

   ciphertext[count] = 0;

}


void caesarDecrypt(const char ciphertext[], char plaintext[], int key)
{
   //stupid simple way to decrypt. 
   caesarEncrypt(ciphertext, plaintext, -key);


}