/**
 * @Author: simepy
 * @Date:   November 8th 2018, 11:48:23 pm
 * @Last modified by:   sime
 * @Last modified time: November 27th 2018, 8:10:00 pm
 */



#ifndef DES_H_
# define DES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>

//Msg
char  *permutationIP(char *msg);
char  *permutationIP1(char *str);
char  *loop16InF(char **msgData, char **keyData, int mode);
char  *dividMsgIn64Block(char *str, int nbrBlock);

//Key
char  *permutationPC1(char *key);
void  permutationPC2(char **keyData);
char  **createSubkeysAndConcat(char **key);

//Utils
char  *paddingAutoComplete(char *str);
char  **splitBlock(char *key);
char  *blockPermutation(const int *permutationTable, int sizeTable, char *block);
char  *hexaAsBinary(char *block);
char  *shifLeft(char *str, int nbrLeftShift);
char  *strToBinary(char *str);
void  reverseStr(char *str);
char  *intToBinary(int n);
void  printBinaryAsHexa(char *block);
char  *strBinToString(char *strBin);

#endif
