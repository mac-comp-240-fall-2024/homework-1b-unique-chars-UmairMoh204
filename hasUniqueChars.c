/*
 * hasUniqueChars.c
 * 
 * Umair Mohammed
 * 
 * bool hasUniqueChars(char * inputStr) is a method that checks to see if an input string has an duplicate of letters, numbers, or symbols. If there is a duplicate the method would return a
 * 0 indicating that there is an duplicate and 1 indicating that there are no duplicates. 
 * 
 * Author: 
 */

#include <stdio.h>  // fprintf, printf
#include <stdlib.h> // exit() defined here
#include <string.h> // useful string operations
#include <ctype.h>  //useful character operations
#include <stdbool.h>  // to define a boolean type and true, false
                      // see https://en.wikibooks.org/wiki/C_Programming/stdbool.h

#include "binary_convert.h"


/*
 * This function is for debugging by printing out the value
 * of an input insigned long as a binary string.
 */
void seeBits(unsigned long value, char *debug_text) {
  
  // string to represent binary value of variable value
  char *bin_str;

  bin_str = ulong_to_bin_str(value);
  printf("%s%s\n", debug_text, bin_str);
  free(bin_str);
  
}


// TODO: Read this carefully to see how to loop over characters of a string
// TODO: (Remove TODOs once you have completed the task they describe)
/*
 * Given an input string of chars, check for any non-printing
 * characters and print an error and exit if the string has any.
 */
void checkInvalid(char * inputStr) {
  char nextChar;
  int i;
  
  for(i = 0; i < strlen(inputStr); i++) {
    nextChar = inputStr[i];

    // if nextChar is invalid (31 or less or 127 as an ascii char code), then bail out
    if ((nextChar <= 31 ) || (nextChar == 127)) {
      fprintf(stderr, "invalid character in string\n");
      exit(EXIT_FAILURE);
    }
  }
}


/*
 * TODO: Replace this code by a good description this function takes in, does and returns.
 * Include the error conditions that cause it to exit with failure.
 */
bool hasUniqueChars(char * inputStr) {
  // bail out quickly if any invalid characters
  checkInvalid(inputStr);
  
  int i;   // loop counter
  
  // unsigned long can handle 64 different chars in a string
  // if a bit at a position is 1, then we have seen that character
  unsigned long checkBitsA_z = 0;   // for checking A through z and {|}~
  unsigned long checkBitsexcl_amp = 0;  // for checking ! though @ 

  char nextChar;         // next character in string to check

  // -------------------------------------------------------------
  // This section contains code to display the initial values of checkBitsA_z
  // and checkBitsexcl_amp, for debugging purposes. 
  // It also illustrates how to use the seeBits function for debugging.
  // Printed values should initially be all zeros
  // TODO: remove or comment out this code when satisfied of function correctness

  for (int i = 0; i < strlen(inputStr); i++) {
    nextChar = inputStr[i];
    unsigned long index = nextChar-65;
    unsigned long mask = 1l << index;
    /// This is saying that if there is a space to continue
    if (nextChar == 32) {
      continue;
    }
    /// This is checking if nextChar is between A-Z and if so then to get an index and mask to determine whether the nextChar is repeated in the input string
    else if ((nextChar >= 65) && nextChar <=90) {
      unsigned long index = nextChar - 65;
      unsigned long mask = 1l << index;
      /// Checking to see if there is a match
      if (mask & checkBitsA_z) {
        return false;
      }
      /// Tracks to see if it has been seen and if not to save it as seen return false if there is a duplicate
      else {
        checkBitsA_z |= mask;
      }
    }
    /// This is checking if nextChar is between a-z and if so to get an index and mask to determine whether the nextChar is repeated in the input string
    else if ((nextChar >= 97) && nextChar <=122) {
      unsigned long index = nextChar - 97 + 26;
      unsigned long mask = 1l << index;
      /// Tracks to see if it has been seen and if not to save it as seen return false if there is a duplicate
      if (mask & checkBitsA_z) {
        return false;
      }
      else {
        checkBitsA_z |= mask;
      }
    }
    /// This is checking if nextChar is a special character and if so to get an index and mast to determine if there is a repeated special charcter
    else if (nextChar >= 33 && nextChar <= 64) {
      unsigned long index = nextChar - 33;
      unsigned long mask = 1l << index;
      /// Tracks to see if it has been seen and if not to save it as seen return false if there is a duplicate
      if (checkBitsexcl_amp & mask) {
          return false;
      }

      else {
        checkBitsexcl_amp |= mask;
      }
    }
  }
  return true;
  
  char debug_str_A_z[128];
  strcpy(debug_str_A_z, "checkBitsA_z before: \n");
  seeBits(checkBitsA_z, debug_str_A_z);
  
  char debug_str_excl_amp[128];
  strcpy(debug_str_excl_amp, "checkBitsexcl_amp before: \n");
  seeBits(checkBitsexcl_amp, debug_str_excl_amp);
  // -------------------------------------------------------------

  // TODO: Declare additional variables you need here


  printf("nextchar int value: %d\n", nextChar);
  char char_str[2] = "\0";
  char_str[0] = nextChar;
  strcpy(debug_str_A_z, "nextchar: ");
  strcat(debug_str_A_z, char_str);
  strcat(debug_str_A_z,", checkBitsA_z: \n");
  seeBits(checkBitsA_z, debug_str_A_z);
    // ------------------------------------------------------------- 
}
