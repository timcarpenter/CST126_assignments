//
// Tim Carpenter
//
// CST126 - Assignment 2
//
// caesar.cpp implementation

#include <string.h>
#include <math.h>
#include "algorithms.h"


static int conversionKey(int originalKey)
{
   // take absolute value of original key to remove negative numbers
   int convertedKey = abs(originalKey);

   // 
   convertedKey %= NUM_CHARACTERS;

   //convert negative value key to real number
   if (originalKey < 0)
   {
	  convertedKey = NUM_CHARACTERS - convertedKey;
   }

   return convertedKey;
}


// Encryption function
void  caesarEncrypt(const char plaintext[], char ciphertext[], int key)
{
   key = conversionKey(key);

   size_t length = strlen(plaintext);

   size_t count;

   //
   for (count = 0; count < length; ++count)
   {
	  //
	  if (CHAR_OUT_OF_RANGE(plaintext[count]))
	  {
		 ciphertext[count] = plaintext[count];
		 continue;
	  }


	  //
	  char character = plaintext[count] - MIN_ASCII_VALUE;

	  character += key % NUM_CHARACTERS;
	  character %= NUM_CHARACTERS;

	  ciphertext[count] = character + MIN_ASCII_VALUE;

   }

   ciphertext[count] = 0;

}


void caesarDecrypt(const char ciphertext[], char plaintext[], int key)
{

   caesarEncrypt(ciphertext, plaintext, -key);


}