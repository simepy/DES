/**
 * @Author: simepy
 * @Date:   November 8th 2018, 11:51:18 pm
 * @Last modified by:   sime
 * @Last modified time: November 28th 2018, 7:20:50 pm
 */



#include "des.h"

char  *permutationPC1(char *key) {
  const int   PC1[] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4,
  };
  return blockPermutation(PC1, (sizeof(PC1) / sizeof(int)), key);

}

char  **createSubkeysAndConcat(char **key) {
  int   lenKeyBig = strlen(key[0]);
  char  leftShiftKey[34][lenKeyBig + 1];
  const int nbrLeftShift[16] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1,
  };
  char  *shiftedKeyLeft;
  char  *shiftedKeyRight;
  char  **concatSubKey;
  char  concatTmp[57];
  int   i = 0;
  int   y = 1;


  strncpy(leftShiftKey[y], key[0], 28);
  strncpy(leftShiftKey[y - 1], key[1], 28);
  leftShiftKey[y][28] = '\0';
  leftShiftKey[y - 1][28] = '\0';
  free(key[0]);
  free(key[1]);
  free(key);
  while (i < 16) {
    shiftedKeyRight = shifLeft(leftShiftKey[y], nbrLeftShift[i]);
    shiftedKeyLeft = shifLeft(leftShiftKey[y - 1], nbrLeftShift[i]);
    strcpy(leftShiftKey[y + 1], shiftedKeyLeft);
    strcpy(leftShiftKey[y + 2], shiftedKeyRight);
    free(shiftedKeyLeft);
    free(shiftedKeyRight);
    i++;
    y += 2;
  }

  // concatenate 2 28bit string in one
  i = 0;
  y = 2;
  concatSubKey = malloc(sizeof(char *) * 16);
  while (i < 16) {
    concatSubKey[i] = malloc(sizeof(char) * 57);
    strncpy(concatTmp, leftShiftKey[y + 1], 28); // LEFT
    strncpy(&concatTmp[28], leftShiftKey[y], 28); // RIGHT
    concatTmp[56] = '\0';
    strncpy(concatSubKey[i], concatTmp, 57);
    i++;
    y += 2;
  }
  return concatSubKey;
}

void  permutationPC2(char **keyData) {
  int i = 0;
  char *tmpData;
  const int   PC2[] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32,
  };

  while (i < 16) {
    tmpData = blockPermutation(PC2, (sizeof(PC2) / sizeof(int)), keyData[i]);
    strcpy(keyData[i], tmpData);
    free(tmpData);
    i++;
  }
}
