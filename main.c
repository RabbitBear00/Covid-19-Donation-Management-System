#include "basic.h"
#include "basic.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void MainMenu();

int main()
{
    ReadFile_Donation();
    ReadFile_Dist();
    //Main Menu
    while (1)
        MainMenu();
}

