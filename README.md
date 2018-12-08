# Summarise 
  DES C is a Simple implementation of the DES algorithm in C

# Based in: 
  http://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm

# Compilation 
  In Linux;
    Compile the program with: "make"
    PS: you can also do: "make re" for recompile all,
        do "make clean" for remove all ".o",
        and do "make fclean" for remove all ".o" and executable

# Usage:

## Argument:

    my_des [OPTION] [msg] key [encrypted msg]

    Note: Key argument: must be a hexadecimal string and size must be equal to 16 characters
    --decrypt : add for decrypt the message
    -h, --help : print a help message


## Test:
    for encrypt a message:
      "./my_des message key"
    for decrypt a message: 
      "./my_des --decrypt key encrypted_message"

## Example:
### Encrypted a message:
      ./my_des fooBar 0123456789ABCDEF
      equal: A591268739E2E7B3
### Decryted a message:
      ./my_des --decrypt 0123456789ABCDEF A591268739E2E7B3
      equal: fooBar
