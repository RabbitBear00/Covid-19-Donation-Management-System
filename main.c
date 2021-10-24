#include "menu.h"
#include "menu.c"

#include <stdio.h>


void MainMenu();

int main()
{
    ReadFile_Donation();
    ReadFile_Dist();
    //Main Menu
    while (1)
        MainMenu();
}

