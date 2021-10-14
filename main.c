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

void MainMenu()
{
    int choice;

    while (1)
    {
        clrscr();
        char title[100] = "Covid-19 Inventory Management System";
        char menu[][30] = {"Dahsboard", "Manage Donation Supplies", "Manage Distributed Donation", "Exit"};
        Print_Title(TITLELENGTH, strlen(title), title);
        Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
        printf("Choice: ");

        scanf("%d", &choice);
        if (CHOICE_CONDITION)
            break;
    }

    switch (choice)
    {
    case 1:
        //Dashboard();
        break;

    case 2:
        //DonationSupplies();
        break;

    case 3:
        //DistributedDonation();
        break;

    case 4:
        printf("Program Successfully Exited......\n");
        exit(0);

    default:
        break;
    }
}

void Dashboard()
{
}

void DonationSupplies()
{
    int choice;

    while (1)
    {
        clrscr();
        char title[100] = "Manage Donation Supplies";
        char menu[][30] = {"Add donation supply", "Edit donation supply", "Search donation supply", "Return"};
        Print_Title(TITLELENGTH, strlen(title), title);
        PrintTable(1, SUPPLYCOLUMN, Space_Supply, SupplyColumnName, SupplyLength, 0);
        putchar('\n');
        Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);

        scanf("%d", &choice);
        if (CHOICE_CONDITION)
            break;
    }

    switch (choice)
    {
        case 1:
            //AddDonationSupply();
            break;
        
        case 2:
            //EditDonationSupply();
            break;
        
        case 3:
            //SearchDonationSupply();
            break;
        
        case 4:
            return;
    }
}

void DistributedDonation()
{
}
