/**
 * @Author: sime
 * @Date:   November 14th 2018, 4:33:14 pm
 * @Last modified by:   sime
 * @Last modified time: November 28th 2018, 5:51:49 pm
 */



#include "des.h"

void errorSizeMsg() {
  printf("Error: your key must be measure 16 caracteres\n");
}

void  printHelpMsg() {
  printf("Version: 2.0\n\
  Argument:\n\
  --decrypt : add for decrypt the message\n\
  -h, --help : print this message\n\
  Example:\n\
  for encrypt message\n\
  \"des message key\"\n\
  for decrypt message: \n\
  \"des --decrypt key encrypted_message\"\n");
}

int   verifArg(int ac, char **av) {
  if (ac < 2 || ac > 4) {
    printHelpMsg();
    return 1;
  }
  if (ac < 2 && strcmp("-h", av[1]) == 0 &&
  strcmp("--help", av[1]) == 0) {
    printHelpMsg();
    return 1;
  }
  if (ac < 3) {
    printHelpMsg();
    return 1;
  }
  if (strlen(av[2]) != 16) {
    errorSizeMsg();
    return 1;
  }
  return 0;
}

char  **algoKey(char *key) {
  char  *binaryData;
  char  *permuteData;
  char  **keyData;

  // convert a hexa string to binary string
  binaryData = hexaAsBinary(key);

  // permute the key PC1 table
  permuteData = permutationPC1(binaryData);
  free(binaryData);

  // split permutekey in two string of 28bits
  keyData = splitBlock(permuteData);
  free(permuteData);

  // create 16 subkey and concatenate each subkey in big 56bits keys
  keyData = createSubkeysAndConcat(keyData);

  // permute each 56bits keys folowing the PC-2 table
  permutationPC2(keyData);
  return keyData;
}

void  freeKey(char **key) {
  int   i = 0;

  while (i < 16) {
    free(key[i]);
    i++;
  }
  free(key);
}

// main fonction used when mode decryption is activate
void  decryptMsg(char *key, char *encryptMsg) {
  char  **keyData;
  char  *binaryMsg;
  char  *block64Msg;
  char  *permuteData;
  char  **splitedMsg;
  char  *strBinStr;
  int   i = 0;
  int   len;
  char  *finalStr;

  // create key
  keyData = algoKey(key);
  // convert string in hexa in Binary
  binaryMsg = hexaAsBinary(encryptMsg);

  // for devide binary msg in block of 64bits
  len = strlen(binaryMsg) / 64;
  // loop in each devide block
  while (i < len) {
    block64Msg = dividMsgIn64Block(binaryMsg, i);
    permuteData = permutationIP(block64Msg);
    free(block64Msg);
    splitedMsg = splitBlock(permuteData);
    free(permuteData);

    /*
    * decryption is a same than encryption:
    * we just reapply all the step but apply subkey in the reverse order
    * this is why mode (third parameter) is equal to 1
    */
    block64Msg = loop16InF(splitedMsg, keyData, 1);

    permuteData = permutationIP1(block64Msg);
    free(block64Msg);
    strBinStr = strBinToString(permuteData);
    free(permuteData);

    // this part is for concatenate all final 64bits blocks together
    if (i <= 0) {
      finalStr = malloc(sizeof(char) * strlen(strBinStr) + 1);
      strcpy(&finalStr[0], strBinStr);
    } else {
      finalStr = realloc(finalStr, (strlen(finalStr) + strlen(strBinStr)) + 1);
      strcpy(&finalStr[strlen(finalStr)], strBinStr);
    }
    free(strBinStr);
    i++;
  }
  printf("%s\n", finalStr);
  freeKey(keyData);
  free(finalStr);
  free(binaryMsg);
}

int   main(int ac, char **av) {
  char  *binaryData;
  char  *permuteData;
  char  **keyData;
  char  **msgData;
  char  *blockMsg64;
  int   i = 0;
  int   len;

  if (verifArg(ac, av)) {
    return 1;
  }

  if (strcmp("--decrypt", av[1]) == 0) {
    decryptMsg(av[2], av[3]);
  } else {
    keyData = algoKey(av[2]);

    binaryData = strToBinary(av[1]);
    // add 0bits in the end of the string if the string is not a multiple of 64bits
    binaryData = paddingAutoComplete(binaryData);

    len = strlen(binaryData) / 64;
    while (i < len) {
      blockMsg64 = dividMsgIn64Block(binaryData, i);
      // permute key with the folowing IP table
      permuteData = permutationIP(blockMsg64);
      free(blockMsg64);

      // split the msg in two
      msgData = splitBlock(permuteData);
      free(permuteData);

      /*
      * make 16 operations using the function below for produce 16 a blocks of 32 bits
      * Left block produced: Ln = Rn-1
      * Right block produced: Rn = Ln-1 + f(Rn-1,Kn)
      */
      blockMsg64 = loop16InF(msgData, keyData, 0);

      permuteData = permutationIP1(blockMsg64);
      free(blockMsg64);
      // print and convert binary in hexadecimal string
      printBinaryAsHexa(permuteData);
      free(permuteData);
      i++;
    }
    printf("\n");
    freeKey(keyData);
    free(binaryData);
  }
  return 0;
}
