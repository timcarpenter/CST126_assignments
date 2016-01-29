
//
// CST 126 - Assignment #2
//
// Author: Michael Hoffman
//
// File: algorithms.h
//
// Constants/macros and prototypes for the encryption/decryption
// functionality.
//


#ifndef  algorithms_H
#define  algorithms_H


//
// Constants/macros
//

#define  MAX_MSG_SIZE      256
#define  MIN_ASCII_VALUE  ('a')
#define  MAX_ASCII_VALUE  ('z')
#define  NUM_CHARACTERS  (MAX_ASCII_VALUE - MIN_ASCII_VALUE + 1)

#define  CHAR_OUT_OF_RANGE(c)  ( (c) < MIN_ASCII_VALUE || (c) > MAX_ASCII_VALUE )


//
// Prototypes
//

extern void  caesarEncrypt( const char  plaintext[],
                            char        ciphertext[],
                            int         key );
extern void  caesarDecrypt( const char  ciphertext[],
                            char        plaintext[],
                            int         key );

extern void  substitutionEncrypt( const char  plaintext[],
                                  char        ciphertext[],
                                  const char  key[] );
extern void  substitutionDecrypt( const char  ciphertext[],
                                  char        plaintext[],
                                  const char  key[] );

extern void  vigenereEncrypt( const char  plaintext[],
                              char        ciphertext[],
                              const char  key[] );
extern void  vigenereDecrypt( const char  ciphertext[],
                              char        plaintext[],
                              const char  key[] );

extern void  transpositionEncrypt( const char  plaintext[],
                                   char        ciphertext[],
                                   unsigned    key );
extern void  transpositionDecrypt( const char  ciphertext[],
                                   char        plaintext[],
                                   unsigned    key );

#endif
