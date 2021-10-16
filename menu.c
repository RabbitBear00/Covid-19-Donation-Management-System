#include "basic.h"
#include "basic.c"
#include "menu.h"

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
        while (1)
        {
            clrscr();
            char title[100] = "Manage Donation Supplies";
            char menu[][30] = {"Add donation supply", "Edit donation supply", "Search donation supply", "Return"};
            Print_Title(TITLELENGTH, strlen(title), title);
            PrintTable(1, SUPPLYCOLUMN, Space_Supply, SupplyColumnName, SupplyLength, 0);
            putchar('\n');
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            printf("Choice: ");
            scanf("%d", &choice);
            if (CHOICE_CONDITION)
                break;
        }

        switch (choice)
        {
        case 1:
            AddDonationSupply();
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
}

void DistributedDonation()
{
}

void AddDonationSupply()
{
    //If the character length user enter is not larger than 1000 should not have a problem
    char supply_code[1000];
    int supply_code_index;
    char donator[1000];
    struct date donation_date;
    char date_buffer[1000];
    char shipment_buffer[1000];
    char quantity_buffer[1000];
    char buffer[100];

    clrscr();
    char title[100] = "Add Donation Supply";
    Print_Title(TITLELENGTH, strlen(title), title);
    printf("Currently there are only %d types of supplies that you can donate.\n", SUPPLYTYPES);
    printf("Supply Code - Supply Name\n");
    //Print all the available supplies out
    for (int i = 0; i < SUPPLYTYPES; i++)
    {
        printf("%s - %s\n", Supply_Type[i][0], Supply_Type[i][1]);
    }

    //Prints stuffs and ask customer to enter
    printf("\nPlease fill up the details of the donation: \n");

    //Supply Code validation
    do
    {
        printf("Supply Code: ");
        scanf("%s", supply_code);
        supply_code_index = validation_supply_code(supply_code);
    } while (supply_code_index < 0);

    //Donator length validation(cannot exceed 20)
    do
    {
        printf("Donator: ");
        scanf("%s", donator);
    } while (!Validation_CharLength(20, strlen(donator)));

    //Donation date validation(Format )
    do
    {
        printf("Enter Date in format: dd/mm/yyyy\n");
        printf("Date: ");
        //Get the string
        scanf("%s", date_buffer);
        //Write inside donation_date according to the format
        sscanf(date_buffer, "%d/%d/%d", &donation_date.day, &donation_date.month, &donation_date.year);
    } while (!Validation_Date(donation_date));

    //Shipment no.
    do
    {
        printf("Shipment No.: ");
        scanf("%s", shipment_buffer);
    } while (!validation_isdigit(7, shipment_buffer, strlen(shipment_buffer)));

    //Quantity Donated
    do
    {
        printf("Quantity(millions): ");
        scanf("%s", quantity_buffer);

    } while (!validation_isfloat(quantity_buffer, strlen(quantity_buffer)));

    //Must add to ensure donationID is corect
    SupplyLength++;
    //Store everything inside a variable of type supply
    snprintf(buffer, 10, SUPPLYIDFORMAT, SupplyLength);
    strcpy(SupplyHead[SupplyLength - 1].donation_ID, buffer);
    strcpy(SupplyHead[SupplyLength - 1].supply_code, supply_code);
    strcpy(SupplyHead[SupplyLength - 1].supply_name, Supply_Type[supply_code_index][1]);
    strcpy(SupplyHead[SupplyLength - 1].donator, donator);
    SupplyHead[SupplyLength - 1].donation_date = donation_date;
    SupplyHead[SupplyLength - 1].shipment_no = atoi(shipment_buffer);
    SupplyHead[SupplyLength - 1].init_quantity = atof(quantity_buffer);
    SupplyHead[SupplyLength - 1].curr_quantity = atof(quantity_buffer);

    ConfirmSupplySection(&SupplyHead[SupplyLength - 1]);
}

void EditDonationSupply()
{
    char supply_code[1000];
    int supply_code_index;
    char donator[1000];
    struct date donation_date;
    char date_buffer[1000];
    char shipment_buffer[1000];
    char quantity_buffer[1000];
    char buffer[100];
    char donation_ID[1000];
    int search_index = -1;
    char title[100] = "Edit Donation Supply";

    while (1)
    {
        int choice;
        //User enter donation ID part
        while (1)
        {
            clrscr();

            Print_Title(TITLELENGTH, strlen(title), title);
            PrintTable(1, SUPPLYCOLUMN, Space_Supply, SupplyColumnName, SupplyLength, 0);
            printf("\nEnter Donation ID: ");
            scanf("%s", donation_ID);
            for (int i = 0; i < SupplyLength; i++)
            {
                if (strcmp(SupplyHead[i].donation_ID, donation_ID) == 0)
                {
                    search_index = i;
                    break;
                }
            }

            if (search_index >= 0)
                break;
            else
                printf("Donation ID doesnt exist. Please enter again.\n");
            Exit_Phrase();
        }

        //Choosing which attribute to edit part
        while (1)
        {
            clrscr();

            char menu[][30] = {"Supply code", "Donator", "Donation date", "Shipment no", "Quantity received(millions)", "Return"};
            Print_Title(TITLELENGTH, strlen(title), title);
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            printf("Choice: ");

            scanf("%d", &choice);
            if (CHOICE_CONDITION)
                break;
        }

        switch (choice)
        {
        //Supply Code
        case 1:
            do
            {
                printf("\nSupply Code: ");
                scanf("%s", supply_code);
                supply_code_index = validation_supply_code(supply_code);
            } while (supply_code_index < 0);
            break;
        //Donator
        case 2:
            do
            {
                printf("Donator: ");
                scanf("%s", donator);
            } while (!Validation_CharLength(20, strlen(donator)));
            break;
        //Donation date
        case 3:
            do
            {
                printf("Enter Date in format: dd/mm/yyyy\n");
                printf("Date: ");
                //Get the string
                scanf("%s", date_buffer);
                //Write inside donation_date according to the format
                sscanf(date_buffer, "%d/%d/%d", &donation_date.day, &donation_date.month, &donation_date.year);
            } while (!Validation_Date(donation_date));
            break;
        //shipment no
        case 4:
            do
            {
                printf("Shipment No.: ");
                scanf("%s", shipment_buffer);
            } while (!validation_isdigit(7, shipment_buffer, strlen(shipment_buffer)));
            break;
        //Quantity Received
        case 5:
            do
            {
                printf("Quantity(millions): ");
                scanf("%s", quantity_buffer);

            } while (!validation_isfloat(quantity_buffer, strlen(quantity_buffer)));
        case 6:
            Exit_Phrase();
            return;
        default:
            break;
        }
    }
}

void ViewHistoryRecord_Supply()
{
}

void SearchDonationSupplies()
{
}
void SearchStocks()
{
}

void SearchSupplyHistory()
{
}

void AddDistDonation()
{
}

void EditDistDonation()
{
}

void ViewHistoryRecord_Dist()
{
}

void SearchDistDonation()
{
}

void SearchDistHistory()
{
}

void SearchDistTotal()
{
}

int main()
{
    ReadFile_Donation();
    DonationSupplies();
}