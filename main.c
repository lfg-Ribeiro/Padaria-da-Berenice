#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"

int main() {
    
    setlocale(LC_ALL, "Portuguese");

    puxaMenu();
    
    return 0;
}