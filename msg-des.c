/**
 * @Author: sime
 * @Date:   November 14th 2018, 4:33:41 pm
 * @Last modified by:   sime
 * @Last modified time: November 28th 2018, 7:13:47 pm
 */



#include "des.h"

/*
* apply xor fonction to a str and str1
*/
char  *msgXor(char *str, char *str1) {
  int tmp, tmp1, xor;
  char *strXor;
  char tol[2];
  char tol1[2];
  char c[2];
  int i = 0;
  int len = strlen(str);

  strXor = malloc(sizeof(char) * len + 1);
  while (i < len) {
    tol[0] = str[i];
    tol1[0] = str1[i];
    tol[1] = '\0';
    tol1[1] = '\0';
    tmp = strtol(tol, 0, 10);
    tmp1 = strtol(tol1, 0, 10);
    xor = tmp ^ tmp1;
    sprintf(c, "%d", xor);
    strXor[i] = c[0];
    i++;
  }
  strXor[i] = '\0';
  return strXor;
}

/*
* convert the binary number str[0] and str[5] in decimal
*/
int   binFistLastToInt(char *str) {
  char tmp[3];

  tmp[0] = str[0];
  tmp[1] = str[5];
  tmp[2] = '\0';
  return strtol(tmp, 0, 2);
}

/*
* convert the binary number str[1], str[2], str[3] and str[4] in decimal
*/
int   binMiddleToInt(char *str) {
  char tmp[5];

  strncpy(tmp, &str[1], 4);
  tmp[4] = '\0';
  return strtol(tmp, 0, 2);
}

/*
* compare each block of 6bits converted with 2 below fonction in 2 decimal number
ù with the S Table
*/
char  *makeSTable(int *row, int *column) {
  const int s[8][64][16] = {
    {
      {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,},
      {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,},
      {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,},
      {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13,},
    }, {
      {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,},
      {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,},
      {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,},
      {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9,},
    }, {
      {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,},
      {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,},
      {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,},
      {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,},
    }, {
      {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,},
      {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,},
      {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,},
      {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14,},
    }, {
      {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,},
      {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,},
      {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,},
      {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3,},
    }, {
      {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,},
      {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,},
      {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,},
      {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13,},
    }, {
      {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,},
      {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,},
      {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,},
      {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12,},
    }, {
      {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,},
      {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,},
      {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,},
      {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11,},
    }
  };
  int   i = 0;
  int   l = 0;
  char  *strS;
  char  *tmpStr;

  strS = malloc(sizeof(char) * 33);
  while (i < 8) {
    tmpStr = intToBinary(s[i][row[i]][column[i]]);
    strncpy(&strS[l], tmpStr, 4);
    free(tmpStr);
    i++;
    l += 4;
  }
  strS[l] = '\0';
  return strS;
}

// see the fonction description below
char  *doSTable(char *xorMsg) {
  int   i = 0;
  int   y = 0;
  int   len;
  int   nbrLastEnd[8];
  int   nbrMiddle[8];
  char  tmp[6];

  // devide 48bits msg in 8 groups of 6bits
  // and convert each in decimal following the algorithm
  len = strlen(xorMsg);
  while (i < len) {
    strncpy(tmp, &xorMsg[i], 6);
    nbrLastEnd[y] = binFistLastToInt(tmp);
    nbrMiddle[y] = binMiddleToInt(tmp);
    i += 6;
    y++;
  }
  free(xorMsg);
  return makeSTable(nbrLastEnd, nbrMiddle);
}

/*
* main fonction of the loop16InF
*/
char  *functionF(char *strRight, char *key) {
  const int eBitSelect[] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1,
  };
  const int p[] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25,
  };
  char  *rightExtended = blockPermutation(eBitSelect,
    sizeof(eBitSelect) / sizeof(int), strRight);
  char  *tmpMsgData;
  char  *strFoncF;

  tmpMsgData = msgXor(rightExtended, key);
  free(rightExtended);
  strFoncF = doSTable(tmpMsgData);
  tmpMsgData = blockPermutation(p, sizeof(p) / sizeof(int), strFoncF);
  free(strFoncF);
  return tmpMsgData;
}

char  *dividMsgIn64Block(char *str, int nbrBlock) {
  char  *part64block = malloc(sizeof(char) * 65);

  strncpy(part64block, &str[nbrBlock * 64], 64);
  part64block[64] = '\0';
  return part64block;
}

char  *loop16InF(char **msgData, char **keyData, int mode) {
  char  **left;
  char  **right;
  int   i = 1;
  char  *finalStr;
  int   lenMsgData = strlen(msgData[0]) + 1;
  char  *strFoncF;
  char  *strMsgXor;

  // mode 0 = encryption, 1 = decryption
  finalStr = malloc(sizeof(char) * 65);
  left = malloc(sizeof(char *) * 16);
  right = malloc(sizeof(char *) * 16);
  left[0] = malloc(sizeof(char) * lenMsgData);
  right[0] = malloc(sizeof(char) * lenMsgData);
  strcpy(left[0], msgData[1]);
  if (mode == 1) {
    strFoncF = functionF(msgData[1], keyData[15]);
    strMsgXor = msgXor(msgData[0], strFoncF);
    free(strFoncF);
    strcpy(right[0], strMsgXor);
    free(strMsgXor);
  } else {
    strFoncF = functionF(msgData[1], keyData[0]);
    strMsgXor = msgXor(msgData[0], strFoncF);
    free(strFoncF);
    strcpy(right[0], strMsgXor);
    free(strMsgXor);
  }
  free(msgData[0]);
  free(msgData[1]);
  free(msgData);
  /*
  * buld following this:
  *   Ln = Rn-1
  *   Rn = Ln-1 + f(Rn-1,Kn)
  */
  while (i < 16) {
    left[i] = malloc(sizeof(char) * lenMsgData);
    right[i] = malloc(sizeof(char) * lenMsgData);
    strcpy(left[i], right[i - 1]);
    if (mode == 1) {
      strFoncF = functionF(right[i - 1], keyData[15 - i]);
      strMsgXor = msgXor(left[i - 1], strFoncF);
      free(strFoncF);
      strcpy(right[i], strMsgXor);
      free(strMsgXor);
    } else {
      strFoncF = functionF(right[i - 1], keyData[i]);
      strMsgXor = msgXor(left[i - 1], strFoncF);
      free(strFoncF);
      strcpy(right[i], strMsgXor);
      free(strMsgXor);
    }
    i++;
  }

  // reverse order of the end string and concat together
  strncpy(finalStr, right[15], 32);
  strncpy(&finalStr[32], left[15], 33);
  i--;
  while (i >= 0) {
    free(left[i]);
    free(right[i]);
    i--;
  }
  free(left);
  free(right);
  return finalStr;
}

char  *permutationIP1(char *str) {
  const int   ip1[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41,  9, 49, 17, 57, 25,
  };

  return blockPermutation(ip1, (sizeof(ip1) / sizeof(int)), str);
}

char  *permutationIP(char *msg) {
  const int   ip[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17,  9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7,
  };

  return blockPermutation(ip, (sizeof(ip) / sizeof(int)), msg);
}
