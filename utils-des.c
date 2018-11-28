/**
 * @Author: sime
 * @Date:   November 14th 2018, 4:35:18 pm
 * @Last modified by:   sime
 * @Last modified time: November 28th 2018, 7:35:17 pm
 */



#include "des.h"

// Add some 0 bits for make a str a multiple of 64
// because DES algorithm need 64 bits block for work
char  *paddingAutoComplete(char *str) {
  int   i;
  int   sizeStr = strlen(str);

  if (sizeStr % 64 != 0) {
    i = sizeStr;
    while ((strlen(str) % 64) != 0) {
      str = realloc(str, strlen(str) + 9);
      strncpy(&str[i], "00000000\0", 9);
      i += 8;
    }
  }
  return str;
}

// permute a block with a folowing permutationTable
char  *blockPermutation(const int *permutationTable, int sizeTable, char *block) {
  int i = 0;
  char *permutedKey = malloc(sizeof(char) * sizeTable + 1);

  while (i < sizeTable) {
    permutedKey[i] = block[permutationTable[i] - 1];
    i++;
  }
  permutedKey[sizeTable] = '\0';
  return permutedKey;
}

char  **splitBlock(char *key) {
  char  **keySplited;
  int   sizeKeyDivid = (strlen(key) / 2);
  int   sizeCount = 0;
  int   i = 0;

  keySplited = malloc(sizeof(char *) * 2);
  while (i < 2) {
    keySplited[i] = malloc(sizeof(char) * sizeKeyDivid + 1);
    strncpy(keySplited[i], &key[sizeCount], sizeKeyDivid);
    keySplited[i][sizeKeyDivid] = '\0';
    i++;
    sizeCount += sizeKeyDivid;
  }
  return keySplited;
}

char  *intToBinary(int n) {
    int   binaryNum[4];
    int   i = 0;
    int   y, l;
    char  tmp[2];
    char  *str;

    str = malloc(sizeof(char) * 5);
    while (n > 0) {
      binaryNum[i] = n % 2;
      n = n / 2;
      i++;
    }
    while (i < 4) {
      binaryNum[i] = 0;
      i++;
    }
    y = i - 1;
    l = 0;
    while (y >= 0) {
      sprintf(tmp, "%d", binaryNum[y]);
      str[l] = tmp[0];
      y--;
      l++;
    }
    return str;
}

char  *strToBinary(char *str)
{
    int   lenStr = strlen(str);
    char  *bin = malloc(sizeof(char) * (lenStr * 8) + 1);
    char  tmp[8];
    int   val, len;
    int   i = 0;

    while (i < lenStr)
    {
      val = (int)str[i];
      len = 0;
      while (val > 0)
      {
        if (val % 2) {
          tmp[len] = '1';
          len++;
        } else {
          tmp[len] = '0';
          len++;
        }
        val /= 2;
      }
      while (len < 8) {
        tmp[len] = '0';
        len++;
      }
      reverseStr(tmp);
      strncpy(&bin[i * 8], tmp, 8);
      i++;
    }
    bin[lenStr * 8] = '\0';
    return bin;
}

// convert a binary string to a string
char  *strBinToString(char *strBin) {
  int   num;
  int   i = 0;
  char  tmp[8];
  char  *strChar;
  int   lenstr = strlen(strBin);

  strChar = malloc(sizeof(char) * (lenstr / 8) + 1);
  while (i < lenstr) {
    strncpy(tmp, &strBin[i], 8);
    if (strcmp(tmp, "00000000") == 0) {
      break;
    }
    num = (int)strtol(tmp, NULL, 2);
    strChar[i / 8] = (char)num;
    i += 8;
  }
  strChar[(i / 8)] = '\0';
  return strChar;
}

void  reverseStr(char *str) {
  int   len, i = 0;
  char  c;

  len = strlen(str) - 1;
  while (i < (len - i)) {
    c = str[i];
    str[i] = str[len - i];
    str[len - i] = c;
    i++;
  }
}

void  printBinaryAsHexa(char *block) {
  int   i = 0;
  char  tmp[5];
  int   len = strlen(block) - 1;

  while (i < len) {
    strncpy(tmp, &block[i], 4);
    tmp[4] = '\0';
    printf("%lX", strtol(tmp, 0, 2));
    i += 4;
  }
}

char  *hexaAsBinary(char *block) {
  int   i = 0;
  int   y = 0;
  char  *c;
  char  *blockBin;
  int   lenBlock = strlen(block);
  const char  hexaDigits[17] = "0123456789abcdef\0";
  const char  hexBinary[16][5] = {
    "0000", "0001", "0010",
    "0011", "0100", "0101",
    "0110", "0111", "1000",
    "1001", "1010", "1011",
    "1100", "1101", "1110",
    "1111",
  };

  blockBin = malloc(sizeof(char) * (lenBlock * 4) + 1);
  while (i < lenBlock) {
    if ((c = strchr(hexaDigits, tolower(block[i]))) != NULL) {
      strncpy(&blockBin[y], hexBinary[c - hexaDigits], 4);
      y += 4;
    } else {
      printf("Your key need to be in hexadecimal digits, like: 0123456789abcdef\n");
      free(blockBin);
      exit(1);
    }
    i++;
  }
  blockBin[lenBlock * 4] = '\0';
  return blockBin;
}

// shift the bits in the Left to nbrLeftShift
char  *shifLeft(char *str, int nbrLeftShift) {
  int   i, y;
  int   sizeStr = strlen(str);
  char  *shiftedKey;

  shiftedKey = malloc(sizeof(char) * 29);
  i = 0;
  y = sizeStr - nbrLeftShift;
  while (i < nbrLeftShift) {
    shiftedKey[y] = str[i];
    i++;
    y++;
  }
  y = 0;
  i = nbrLeftShift;
  while (i < sizeStr) {
    shiftedKey[y] = str[i];
    y++;
    i++;
  }
  shiftedKey[28] = '\0';
  return shiftedKey;
}
