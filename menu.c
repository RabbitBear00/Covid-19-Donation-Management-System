#include "basic.h"
#include "basic.c"
#include "menu.h"

void MainMenu()
{
    int choice;
    char choice_buffer[1000];
    while (1)
    {
        clrscr();
        char title[100] = "Covid-19 Inventory Management System";
        char menu[][30] = {"Dahsboard", "Manage Donation Supplies", "Manage Distributed Donation", "Exit"};
        Print_Title(TITLELENGTH, strlen(title), title);
        Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
        printf("Choice: ");
        scanf("%s", choice_buffer);
        if (validation_isdigit(1000, choice_buffer, strlen(choice_buffer)))
            choice = atoi(choice_buffer);
        else
            continue;
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
    char choice_buffer[1000];
    clrscr();
    while (1)
    {
        while (1)
        {
            clrscr();
            char title[100] = "Manage Donation Supplies";
            char menu[][30] = {"Add donation supply", "Edit donation supply", "View Current Stocks", "Search donation supply", "Return"};
            Print_Title(TITLELENGTH, strlen(title), title);
            PrintTable(1, SUPPLYCOLUMN, Space_Supply, SupplyColumnName, SupplyLength);
            putchar('\n');
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            printf("Choice: ");
            scanf("%s", choice_buffer);
            if (validation_isdigit(1000, choice_buffer, strlen(choice_buffer)))
                choice = atoi(choice_buffer);
            else
                continue;
            if (CHOICE_CONDITION)
                break;
        }

        switch (choice)
        {
        case 1:
            AddDonationSupply();
            break;

        case 2:
            EditDonationSupply();
            break;

        case 3:
            ViewCurrentStock_Supply();
            break;

        case 4:
            SearchDonationSupplies();
            break;

        case 5:
            return;

        default:
            break;
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
    int supply_code_index;
    struct date donation_date;
    char date_buffer[1000];
    char buffer[1000];
    char donation_ID[1000];
    int search_index = -1;
    char title[100] = "Edit Donation Supply";
    int selection;

    while (1)
    {
        int choice;
        char choice_buffer[1000];

        //User enter donation ID part
        while (1)
        {
            clrscr();

            Print_Title(TITLELENGTH, strlen(title), title);
            PrintTable(1, SUPPLYCOLUMN, Space_Supply, SupplyColumnName, SupplyLength);
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

            char menu[][30] = {"Supply code", "Donator", "Donation date", "Shipment no", "Quantity received(millions)", "Current Quantity(millions)", "Return"};
            Print_Title(TITLELENGTH, strlen(title), title);
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            printf("Choice: ");
            scanf("%s", choice_buffer);
            if (validation_isdigit(1000, choice_buffer, strlen(choice_buffer)))
                choice = atoi(choice_buffer);
            else
                continue;
            if (CHOICE_CONDITION)
                break;
        }

        switch (choice)
        {
        //Supply Code
        case 1:
            do
            {
                printf("\nSupply name will be changed automatically");
                printf("\nSupply Code: ");
                scanf("%s", buffer);
                supply_code_index = validation_supply_code(buffer);
            } while (supply_code_index < 0);
            break;
        //Donator
        case 2:
            do
            {
                printf("Donator: ");
                scanf("%s", buffer);
            } while (!Validation_CharLength(20, strlen(buffer)));
            break;
        //Donation date
        case 3:
            do
            {
                printf("Enter Date in format: dd/mm/yyyy\n");
                printf("Date: ");
                //Get the string
                scanf("%s", buffer);
                //Write inside donation_date according to the format
                sscanf(buffer, "%d/%d/%d", &donation_date.day, &donation_date.month, &donation_date.year);
            } while (!Validation_Date(donation_date));
            break;
        //shipment no
        case 4:
            do
            {
                printf("Shipment No.: ");
                scanf("%s", buffer);
            } while (!validation_isdigit(7, buffer, strlen(buffer)));
            break;
        //Quantity Received
        case 5:
            do
            {
                printf("Quantity Received(millions): ");
                scanf("%s", buffer);

            } while (!validation_isfloat(buffer, strlen(buffer)));
            break;
        //Current Quantity
        case 6:
            do
            {
                printf("Current Quantity(millions): ");
                scanf("%s", buffer);

            } while (!validation_isfloat(buffer, strlen(buffer)));
            break;

        case 7:
            return;

        default:
            break;
        }

        //Perform to locate exact location in the supply list(Need to skip row 3 which is supply_name)
        if (choice >= 2 && choice <= 6)
            choice++;
        while (1)
        {
            char selection_buffer[1000];
            char title[30] = "Confirm Your Record";
            char menu[][30] = {"Confirm", "Cancel"};
            clrscr();
            Print_Title(TITLELENGTH, strlen(title), title);
            Print_SupplyList(&SupplyHead[search_index], choice, buffer);
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            printf("Choice: ");
            scanf("%s", selection_buffer);
            if (validation_isdigit(1000, selection_buffer, strlen(selection_buffer)))
                selection = atoi(selection_buffer);
            else
                continue;

            if ((selection >= 1) && (selection <= sizeof(menu) / sizeof(menu[0])))
                break;
        }

        if (selection == 2)
        {
            printf("You have cancelled this record.\n");
            Exit_Phrase();
            return;
        }
        //Replace with the attribute in SuppleHead
        if (choice == 1)
        {
            strcpy(SupplyHead[search_index].supply_code, buffer);
            strcpy(SupplyHead[search_index].supply_name, Supply_Type[supply_code_index][1]);
        }

        else if (choice == 3)
            strcpy(SupplyHead[search_index].donator, buffer);

        else if (choice == 4)
            SupplyHead[search_index].donation_date = donation_date;

        else if (choice == 5)
            SupplyHead[search_index].shipment_no = atoi(buffer);

        else if (choice == 6)
            SupplyHead[search_index].init_quantity = atof(buffer);

        else if (choice == 7)
            SupplyHead[search_index].curr_quantity = atof(buffer);
        //Write into file
        SupplyToFile();

        return;
    }
}

void ViewCurrentStock_Supply()
{
    clrscr();
    char title[100] = "View Current Stocks";
    Print_Title(TITLELENGTH, strlen(title), title);
    PrintTable(3, STOCKCOLUMN, Space_Stock, StockColumnName, StockLength);
    Exit_Phrase();
    return;
}

void SearchDonationSupplies()
{
    while (1)
    {
        int choice;
        char choice_buffer[1000];
        while (1)
        {
            clrscr();
            char title[100] = "Search Donation Supply";
            char menu[][30] = {"Search in current stocks", "Search in history records", "Return"};
            Print_Title(TITLELENGTH, strlen(title), title);
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            printf("Choice: ");
            scanf("%s", choice_buffer);
            if (validation_isdigit(1000, choice_buffer, strlen(choice_buffer)))
                choice = atoi(choice_buffer);
            else
                continue;
            if (CHOICE_CONDITION)
                break;
        }

        switch (choice)
        {
        case 1:
            SearchStocks();
            break;

        case 2:
            SearchSupplyHistory();
            break;

        case 3:
            return;

        default:
            break;
        }
    }
}

void SearchStocks()
{
    int i, k;
    int sum = 0;
    char search_target[1000];
    struct stocks *search_index = NULL;
    char title[100] = "Search Current Stocks";
    struct stocks *ptr;
    while (1)
    {
        clrscr();
        Print_Title(TITLELENGTH, strlen(title), title);
        printf("**Format of stocks ID is TXXXXXX, where X are numbers");
        printf("\nEnter Stocks ID: ");
        scanf("%s", search_target);
        Stock_Generator();
        search_index = NULL;
        for (struct stocks *ptr = StockHead; ptr != NULL; ptr = ptr->link)
            if (strcmp(ptr->stock_ID, search_target) == 0)
            {
                search_index = ptr;
                break;
            }
        if (search_index != NULL)
            break;
        else
        
            printf("Stocks ID doesnt exist. Please enter again.\n");
        freeList(StockHead);
        Exit_Phrase();
        return;
    }
    clrscr();
    //Printing the table
    sum = PrintTableHeader(STOCKCOLUMN, Space_Stock, StockColumnName);
    printTableStockRow(Space_Stock, search_index);
    putchar('\n');
    for(i = 0; i < sum; i++)
        printf("-");
    putchar('\n');
    Exit_Phrase();
    freeList(StockHead);
    return;
}

void SearchSupplyHistory()
{
    int i, k;
    int sum = 0;
    char search_target[1000];
    int search_index = -1;
    char title[100] = "Search History Records";
    struct stocks *ptr;
    while (1)
    {
        clrscr();
        Print_Title(TITLELENGTH, strlen(title), title);
        printf("**Format of Donation ID is SXXXXXX, where X are numbers");
        printf("\nEnter Donation ID: ");
        scanf("%s", search_target);
        for(i = 0; i < SupplyLength; i++)
        {
            if(strcmp(SupplyHead[i].donation_ID, search_target) == 0)
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
        return;
    }
    clrscr();
    //Printing the table
    sum = PrintTableHeader(SUPPLYCOLUMN, Space_Supply, SupplyColumnName);
    printTableSupplyRow(Space_Supply, SupplyHead[i]);
    putchar('\n');
    for(i = 0; i < sum; i++)
        printf("-");
    putchar('\n');
    Exit_Phrase();
    return;
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