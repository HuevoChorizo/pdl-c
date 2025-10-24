#include <fcntl.h>
#include <stdio.h>
#include <string.h>
int writer() { return open("Salida_tokens.txt", 0777); }
