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
        char menu[][50] = {"Dashboard", "Manage Donation Supplies", "Manage Distributed Donation", "Exit"};
        Print_Title(TITLELENGTH, strlen(title), title);
        Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
        Printf("Choice: ");
        scanf("%s", choice_buffer);
        fflush(stdin);
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
        Dashboard();
        break;

    case 2:
        DonationSupplies();
        break;

    case 3:
        DistributedDonation();
        break;

    case 4:
        Printf("Program Successfully Exited......\n");
        exit(0);

    default:
        break;
    }
}

void Dashboard()
{
    int choice;
    char choice_buffer[1000];
    clrscr();
    while (1)
    {
        while (1)
        {
            clrscr();
            char title[100] = "Dashboard";
            char menu[][50] = {"Accumulated donation received for each supply", "Accumulated distributed donation for each supply", "Return"};
            Print_Title(TITLELENGTH, strlen(title), title);
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            Printf("Choice: ");
            scanf("%s", choice_buffer);
            fflush(stdin);
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
            SupplyAccuDonation();
            break;

        case 2:
            DistAccuDonation();
            break;

        case 3:
            return;

        default:
            break;
        }
    }
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
            char menu[][50] = {"Add donation supply", "Edit donation supply", "View records", "Search donation supply", "Return"};
            Print_Title(TITLELENGTH, strlen(title), title);
            PrintTable(1, SUPPLYCOLUMN, Space_Supply, SupplyColumnName, SupplyLength);
            putchar('\n');
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            Printf("Choice: ");
            scanf("%s", choice_buffer);
            fflush(stdin);
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
    int choice;
    char choice_buffer[1000];
    clrscr();
    while (1)
    {
        while (1)
        {
            clrscr();
            char title[100] = "Manage Distributed Donation";
            char menu[][50] = {"Add distributed donation", "Edit distributed donation", "View records", "Search distributed donation", "Return"};
            Print_Title(TITLELENGTH, strlen(title), title);
            PrintTable(4, DISTCOLUMN, Space_Dist, DistColumnName, DistLength);
            putchar('\n');
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            Printf("Choice: ");
            scanf("%s", choice_buffer);
            fflush(stdin);
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
            AddDistDonation();
            break;

        case 2:
            EditDistDonation();
            break;

        case 3:
            ViewHistoryRecord_Dist();
            break;

        case 4:
            SearchDistDonation();
            break;

        case 5:
            return;

        default:
            break;
        }
    }
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
    Printf("Currently there are only %d types of supplies that you can donate.\n", SupplyTypeLength);
    Printf("Supply Code - Supply Name\n");
    //Print all the available supplies out
    for (int i = 0; i < SupplyTypeLength; i++)
    {
        Printf("%s - %s\n", Supply_Type[i][0], Supply_Type[i][1]);
    }

    //Prints stuffs and ask customer to enter
    Printf("\nPlease fill up the details of the donation: \n");

    //Supply Code validation
    do
    {
        Printf("Supply Code: ");
        scanf("%s", supply_code);
        fflush(stdin);
        supply_code_index = validation_supply_code(supply_code);
    } while (supply_code_index < 0);

    //Donator length validation(cannot exceed 20)
    do
    {
        Printf("Donator: ");
        scanf("%s", donator);
        fflush(stdin);
    } while (!Validation_CharLength(20, strlen(donator)));

    //Donation date validation(Format )
    do
    {
        Printf("Enter Date in format: dd/mm/yyyy\n");
        Printf("Date: ");
        //Get the string
        scanf("%s", date_buffer);
        fflush(stdin);
        //Write inside donation_date according to the format
        sscanf(date_buffer, "%d/%d/%d", &donation_date.day, &donation_date.month, &donation_date.year);
    } while (!Validation_Date(donation_date));

    //Shipment no.
    do
    {
        Printf("Shipment No.: ");
        scanf("%s", shipment_buffer);
        fflush(stdin);
    } while (!validation_isdigit(7, shipment_buffer, strlen(shipment_buffer)));

    //Quantity Donated
    do
    {
        Printf("Quantity(millions): ");
        scanf("%s", quantity_buffer);
        fflush(stdin);

    } while (!validation_isfloat(quantity_buffer, strlen(quantity_buffer)));

    //Must add to ensure donationID is corect
    SupplyLength++;
    //Store everything inside a variable of type supply
    snPrintf(buffer, 10, SUPPLYIDFORMAT, SupplyLength);
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
            Printf("\nEnter Donation ID: ");
            scanf("%s", donation_ID);
            fflush(stdin);
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
                Printf("Donation ID doesnt exist. Please enter again.\n");
            Exit_Phrase();
        }

        //Choosing which attribute to edit part
        while (1)
        {
            clrscr();

            char menu[][50] = {"Supply code", "Donator", "Donation date", "Shipment no", "Quantity received(millions)", "Current Quantity(millions)", "Return"};
            Print_Title(TITLELENGTH, strlen(title), title);
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            Printf("Choice: ");
            scanf("%s", choice_buffer);
            fflush(stdin);
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
                Printf("\nSupply name will be changed automatically");
                Printf("\nSupply Code: ");
                scanf("%s", buffer);
                fflush(stdin);
                supply_code_index = validation_supply_code(buffer);
            } while (supply_code_index < 0);
            break;
        //Donator
        case 2:
            do
            {
                Printf("Donator: ");
                scanf("%[^\n]", buffer);
                fflush(stdin);
            } while (!Validation_CharLength(20, strlen(buffer)));
            break;
        //Donation date
        case 3:
            do
            {
                Printf("Enter Date in format: dd/mm/yyyy\n");
                Printf("Date: ");
                //Get the string
                scanf("%s", buffer);
                fflush(stdin);
                //Write inside donation_date according to the format
                sscanf(buffer, "%d/%d/%d", &donation_date.day, &donation_date.month, &donation_date.year);
            } while (!Validation_Date(donation_date));
            break;
        //shipment no
        case 4:
            do
            {
                Printf("Shipment No.: ");
                scanf("%s", buffer);
                fflush(stdin);
            } while (!validation_isdigit(7, buffer, strlen(buffer)));
            break;
        //Quantity Received
        case 5:
            do
            {
                Printf("Quantity Received(millions): ");
                scanf("%s", buffer);
                fflush(stdin);

            } while (!validation_isfloat(buffer, strlen(buffer)));
            break;
        //Current Quantity
        case 6:
            do
            {
                Printf("Current Quantity(millions): ");
                scanf("%s", buffer);
                fflush(stdin);

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
            char title[50] = "Confirm Your Record";
            char menu[][50] = {"Confirm", "Cancel"};
            clrscr();
            Print_Title(TITLELENGTH, strlen(title), title);
            Print_SupplyList(&SupplyHead[search_index], choice, buffer);
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            Printf("Choice: ");
            scanf("%s", selection_buffer);
            fflush(stdin);
            if (validation_isdigit(1000, selection_buffer, strlen(selection_buffer)))
                selection = atoi(selection_buffer);
            else
                continue;

            if ((selection >= 1) && (selection <= sizeof(menu) / sizeof(menu[0])))
                break;
        }

        if (selection == 2)
        {
            Printf("You have cancelled this record.\n");
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
    int choice;
    char choice_buffer[1000];
    while (1)
    {
        while (1)
        {
            clrscr();
            char title[100] = "View Records";
            char menu[][50] = {"View current stocks", "View history records", "Return"};
            Print_Title(TITLELENGTH, strlen(title), title);
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            Printf("Choice: ");
            scanf("%s", choice_buffer);
            fflush(stdin);
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
            viewCurrentStocks();
            break;
        case 2:
            viewSupplyHistoryRecord();
        case 3:
            return;
        default:
            break;
        }
    }
}

static void viewCurrentStocks()
{
    int choice;
    char choice_buffer[1000];
    while (1)
    {
        while (1)
        {
            clrscr();
            char title[100] = "View Current Stocks";
            char menu[][50] = {"Stock ID - Ascending", "Quantity Received(millions) - Descending", "Current Quantity(millions) - Descending", "Return"};
            Print_Title(TITLELENGTH, strlen(title), title);
            Printf("Sort according to:\n");
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            Printf("Choice: ");
            scanf("%s", choice_buffer);
            fflush(stdin);
            if (validation_isdigit(1000, choice_buffer, strlen(choice_buffer)))
                choice = atoi(choice_buffer);
            else
                continue;
            if (CHOICE_CONDITION)
                break;
        }
        clrscr();
        switch (choice)
        {
        case 1:
            PrintTable(3, STOCKCOLUMN, Space_Stock, StockColumnName, StockLength);
            Exit_Phrase();
            break;
        case 2:
            PrintTable(9, STOCKCOLUMN, Space_Stock, StockColumnName, StockLength);
            Exit_Phrase();
            break;
        case 3:
            PrintTable(10, STOCKCOLUMN, Space_Stock, StockColumnName, StockLength);
            Exit_Phrase();
            break;
        case 4:
            return;
        default:
            break;
        }
    }
}

static void viewSupplyHistoryRecord()
{
    int choice;
    char choice_buffer[1000];
    while (1)
    {
        while (1)
        {
            clrscr();
            char title[100] = "View History Records";
            char menu[][50] = {"Donation ID - Ascending", "Quantity Received(millions) - Descending", "Current Quantity(millions) - Descending", "Return"};
            Print_Title(TITLELENGTH, strlen(title), title);
            Printf("Sort according to:\n");
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            Printf("Choice: ");
            scanf("%s", choice_buffer);
            fflush(stdin);
            if (validation_isdigit(1000, choice_buffer, strlen(choice_buffer)))
                choice = atoi(choice_buffer);
            else
                continue;
            if (CHOICE_CONDITION)
                break;
        }
        clrscr();
        switch (choice)
        {
        case 1:
            PrintTable(1, SUPPLYCOLUMN, Space_Supply, SupplyColumnName, SupplyLength);
            Exit_Phrase();
            break;
        case 2:
            PrintTable(5, SUPPLYCOLUMN, Space_Supply, SupplyColumnName, SupplyLength);
            Exit_Phrase();
            break;
        case 3:
            PrintTable(6, SUPPLYCOLUMN, Space_Supply, SupplyColumnName, SupplyLength);
            Exit_Phrase();
            break;
        case 4:
            return;
        default:
            break;
        }
    }
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
            char menu[][50] = {"Search in current stocks", "Search in history records", "Return"};
            Print_Title(TITLELENGTH, strlen(title), title);
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            Printf("Choice: ");
            scanf("%s", choice_buffer);
            fflush(stdin);
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
    while (1)
    {
        clrscr();
        Print_Title(TITLELENGTH, strlen(title), title);
        Printf("**Format of stocks ID is TXXXXXX, where X are numbers");
        Printf("\nEnter Stocks ID: ");
        scanf("%s", search_target);
        fflush(stdin);
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

            Printf("Stocks ID doesnt exist. Please enter again.\n");
        freeList_Stock(StockHead);
        Exit_Phrase();
        return;
    }
    clrscr();
    //Printing the table
    sum = PrintTableHeader(STOCKCOLUMN, Space_Stock, StockColumnName);
    PrintTableStockRow(Space_Stock, search_index);
    putchar('\n');
    for (i = 0; i < sum; i++)
        Printf("-");
    putchar('\n');
    Exit_Phrase();
    freeList_Stock(StockHead);
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
        Printf("**Format of Donation ID is SXXXXXX, where X are numbers");
        Printf("\nEnter Donation ID: ");
        scanf("%s", search_target);
        fflush(stdin);
        for (i = 0; i < SupplyLength; i++)
        {
            if (strcmp(SupplyHead[i].donation_ID, search_target) == 0)
            {
                search_index = i;
                break;
            }
        }
        if (search_index >= 0)
            break;
        else
            Printf("Donation ID doesnt exist. Please enter again.\n");

        Exit_Phrase();
        return;
    }
    clrscr();
    //Printing the table
    sum = PrintTableHeader(SUPPLYCOLUMN, Space_Supply, SupplyColumnName);
    PrintTableSupplyRow(Space_Supply, SupplyHead[i]);
    putchar('\n');
    for (i = 0; i < sum; i++)
        Printf("-");
    putchar('\n');
    Exit_Phrase();
    return;
}

void AddDistDonation()
{
    //If the character length user enter is not larger than 1000 should not have a problem
    char donee_name[1000];
    int supply_code_index;
    char donee_location[1000];
    struct date donation_date;
    char stocks_ID[1000];
    char quantity[1000];
    char accu_quantity[1000];
    char buffer[100];
    char date_buffer[1000];
    char supply_index;
    int validation_result;
    int ID_length;
    int ID_array[1000];
    float quan_remainder;
    dist temp;
    int k;

    clrscr();
    char title[100] = "Add Distributed Donation";
    Print_Title(TITLELENGTH, strlen(title), title);
    //Print all the stocks table out
    PrintTable(3, STOCKCOLUMN, Space_Stock, StockColumnName, StockLength);

    //Prints stuffs and ask customer to enter
    Printf("\nPlease fill up the details of the donation: \n");

    //Donee name validation(cannot exceed 30)
    do
    {
        Printf("Donee's name: ");
        scanf("%[^\n]", donee_name);
        fflush(stdin);
    } while (!Validation_CharLength(30, strlen(donee_name)));

    //Donee location length validation(cannot exceed 20)
    do
    {
        Printf("Donee's location: ");
        scanf("%[^\n]", donee_location);
        fflush(stdin);
    } while (!Validation_CharLength(20, strlen(donee_location)));

    //Donation date validation(Format )
    do
    {
        Printf("Enter Date in format: dd/mm/yyyy\n");
        Printf("Date: ");
        //Get the string
        scanf("%s", date_buffer);
        fflush(stdin);
        //Write inside donation_date according to the format
        sscanf(date_buffer, "%d/%d/%d", &donation_date.day, &donation_date.month, &donation_date.year);
    } while (!Validation_Date(donation_date));

    //stocks ID
    do
    {
        Printf("Stock ID: ");
        scanf("%s", stocks_ID);
        fflush(stdin);
        //The function will return supply index if stock ID exists, else it would return -1
        supply_index = validation_stockID(stocks_ID);
    } while (supply_index == -1);
    freeList_Stock(StockHead);

    //Quantity Donated
    do
    {
        ID_length = 0;
        Printf("Quantity(millions): ");
        scanf("%s", quantity);
        fflush(stdin);
        validation_result = validation_isfloat(quantity, strlen(quantity));
        if (validation_result)
            ID_length = EnsureQuantity(ID_array, atof(quantity), supply_index);

    } while (validation_result && (ID_length == -1));

    //Saving the variables temporarily for confirmation
    snPrintf(buffer, 10, DISTIDFORMAT, DistLength);
    strcpy(temp.distributed_ID, buffer);
    strcpy(temp.donee_name, donee_name);
    strcpy(temp.donee_location, donee_location);
    temp.donation_date = donation_date;
    strcpy(temp.stocks_ID, stocks_ID);
    temp.quantity = atof(quantity);

    //Mode 1 for adding; mode 2 for editing
    int result = ConfirmDistSection(&temp, -1, NULL, NULL);

    //Exit the add distributed donation
    if (result == 0)
        return;

    quan_remainder = atof(quantity);
    int transaction_no = DistLength + 1;
    for (int i = 0; i < ID_length; i++)
    {
        //Must add to ensure distributedID is corect
        DistLength++;
        //Store everything inside a variable of type supply
        snPrintf(buffer, 10, DISTIDFORMAT, DistLength);
        strcpy(DistHead[DistLength - 1].distributed_ID, buffer);
        strcpy(DistHead[DistLength - 1].donee_name, donee_name);
        strcpy(DistHead[DistLength - 1].donee_location, donee_location);
        DistHead[DistLength - 1].donation_date = donation_date;
        strcpy(DistHead[DistLength - 1].donation_ID, SupplyHead[ID_array[i]].donation_ID);
        strcpy(DistHead[DistLength - 1].stocks_ID, stocks_ID);
        //Calculate quantitty(ID length is the number of element in the array ID_array which store the index of donation ID of the same stock ID)
        if (ID_length > 1 && i != ID_length - 1)
        {
            quan_remainder -= SupplyHead[ID_array[i]].curr_quantity;
            DistHead[DistLength - 1].quantity = SupplyHead[ID_array[i]].curr_quantity;
            SupplyHead[ID_array[i]].curr_quantity = 0;
        }
        else
        {
            SupplyHead[ID_array[i]].curr_quantity -= quan_remainder;
            DistHead[DistLength - 1].quantity = quan_remainder;
        }

        //Calculate accumulative quantity
        //Distlength - 2 because need to skip the current one which is index DistLength - 1
        for (k = DistLength - 2; k >= 0; k--)
            //Same stock ID means come from the supply of same donator and supply type
            //Accumulative quantity must be the same stock ID, donee name and donee location
            if (!strcmp(DistHead[DistLength - 1].stocks_ID, DistHead[k].stocks_ID) && !strcmp(DistHead[DistLength - 1].donee_name, DistHead[k].donee_name) && !strcmp(DistHead[DistLength - 1].donee_location, DistHead[k].donee_location))
            {
                DistHead[DistLength - 1].accu_quantity = DistHead[k].accu_quantity + DistHead[DistLength - 1].quantity;
                break;
            }
        //Did not find records with the same stock ID, donee name and donee location
        //accu quantity equals quantity
        if (k < 0)
            DistHead[DistLength - 1].accu_quantity = DistHead[DistLength - 1].quantity;

        //Add transaction no
        DistHead[DistLength - 1].transaction_no = transaction_no;
    }
    SupplyToFile();
    DistToFile();
}

void EditDistDonation()
{
    int supply_code_index;
    struct date donation_date;
    char date_buffer[1000];
    char buffer[1000];
    char distributed_ID[1000];
    int search_index = -1;
    char title[100] = "Edit Donation Supply";
    int selection;
    int edit_index = -1;

    while (1)
    {
        int choice;
        char choice_buffer[1000];

        //User enter donation ID part
        while (1)
        {
            clrscr();

            Print_Title(TITLELENGTH, strlen(title), title);
            PrintTable(4, DISTCOLUMN, Space_Dist, DistColumnName, DistLength);
            Printf("\nEnter Distributed ID: ");
            scanf("%s", distributed_ID);
            fflush(stdin);
            //Locate the index of the distributed ID
            DistTotal_Generator();
            for (struct dist_total *ptr = DistTotalHead; ptr != NULL; ptr = ptr->link)
            {
                if (strcmp(ptr->disttotal_ID, distributed_ID) == 0)
                {
                    search_index = ptr->dist_index;
                    break;
                }
            }
            freeList_DistTotal(DistTotalHead);
            if (search_index >= 0)
                break;
            else
                Printf("Distributed ID doesnt exist. Please enter again.\n");

            Exit_Phrase();
        }

        //Choosing which attribute to edit part
        while (1)
        {
            clrscr();

            char menu[][50] = {"Donee name", "Donee location", "Donation date", "Return"};
            Print_Title(TITLELENGTH, strlen(title), title);
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            Printf("Choice: ");
            scanf("%s", choice_buffer);
            fflush(stdin);
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
                Printf("Donee name: ");
                scanf("%[^\n]", buffer);
                fflush(stdin);
                edit_index = 1;
            } while (!Validation_CharLength(20, strlen(buffer)));
            break;
        //Donator
        case 2:
            do
            {
                Printf("Donee location: ");
                scanf("%[^\n]", buffer);
                fflush(stdin);
                edit_index = 2;
            } while (!Validation_CharLength(20, strlen(buffer)));
            break;
        //Donation date
        case 3:
            do
            {
                Printf("Enter Date in format: dd/mm/yyyy\n");
                Printf("Date: ");
                //Get the string
                scanf("%s", buffer);
                fflush(stdin);
                //Write inside donation_date according to the format
                sscanf(buffer, "%d/%d/%d", &donation_date.day, &donation_date.month, &donation_date.year);
                edit_index = 3;
            } while (!Validation_Date(donation_date));
            break;

        case 4:
            edit_index = -1;
            return;

        default:
            break;
        }

        //Prints the confirm section
        clrscr();
        int result = ConfirmDistSection(&DistHead[search_index], edit_index, buffer, distributed_ID);

        //Exit the add distributed donation
        if (result == 0)
            return;
        else
        {
            //Need to replace every single record with the same transaction no.
            int k = search_index;
            while (DistHead[search_index].transaction_no == DistHead[k].transaction_no)
            {
                if (edit_index == 1)
                    strcpy(DistHead[k].donee_name, buffer);

                if (edit_index == 2)
                    strcpy(DistHead[k].donee_location, buffer);

                if (edit_index == 3)
                    DistHead[k].donation_date = donation_date;

                k++;
            }

            DistToFile();
        }
    }
}

void ViewHistoryRecord_Dist()
{
    int choice;
    char choice_buffer[1000];
    while (1)
    {
        while (1)
        {
            clrscr();
            char title[100] = "View Records";
            char menu[][50] = {"View current distributed donation", "View detailed distributed donation", "Return"};
            Print_Title(TITLELENGTH, strlen(title), title);
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            Printf("Choice: ");
            scanf("%s", choice_buffer);
            fflush(stdin);
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
            viewCurrentDistTotal();
            break;
        case 2:
            viewDistDetailedRecord();
            break;
        case 3:
            return;
        default:
            break;
        }
    }
}

static void viewCurrentDistTotal()
{
    int choice;
    char choice_buffer[1000];
    while (1)
    {
        while (1)
        {
            clrscr();
            char title[100] = "View Current Distributed Donation";
            char menu[][50] = {"Distributed ID - Ascending", "Quantity(millions) - Descending", "Accumulative Quantity(millions) - Descending", "Return"};
            Print_Title(TITLELENGTH, strlen(title), title);
            Printf("Sort according to:\n");
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            Printf("Choice: ");
            scanf("%s", choice_buffer);
            fflush(stdin);
            if (validation_isdigit(1000, choice_buffer, strlen(choice_buffer)))
                choice = atoi(choice_buffer);
            else
                continue;
            if (CHOICE_CONDITION)
                break;
        }
        clrscr();
        switch (choice)
        {
        case 1:
            PrintTable(4, DISTCOLUMN, Space_DistTotal, DistTotalColumnName, DistTotalLength);
            Exit_Phrase();
            break;
        case 2:
            PrintTable(11, DISTCOLUMN, Space_DistTotal, DistTotalColumnName, DistTotalLength);
            Exit_Phrase();
            break;
        case 3:
            PrintTable(12, DISTCOLUMN, Space_DistTotal, DistTotalColumnName, DistTotalLength);
            Exit_Phrase();
            break;
        case 4:
            return;

        default:
            break;
        }
    }
}

static void viewDistDetailedRecord()
{
    int choice;
    char choice_buffer[1000];
    while (1)
    {
        while (1)
        {
            clrscr();
            char title[100] = "View Detailed Distributed Donation";
            char menu[][50] = {"Distributed ID - Ascending", "Quantity(millions) - Descending", "Accumulative Quantity(millions) - Descending", "Return"};
            Print_Title(TITLELENGTH, strlen(title), title);
            Printf("Sort according to:\n");
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            Printf("Choice: ");
            scanf("%s", choice_buffer);
            fflush(stdin);
            if (validation_isdigit(1000, choice_buffer, strlen(choice_buffer)))
                choice = atoi(choice_buffer);
            else
                continue;
            if (CHOICE_CONDITION)
                break;
        }
        clrscr();
        switch (choice)
        {
        case 1:
            PrintTable(2, DISTCOLUMN, Space_Dist, DistColumnName, DistLength);
            Exit_Phrase();
            break;
        case 2:
            PrintTable(7, DISTCOLUMN, Space_Dist, DistColumnName, DistLength);
            Exit_Phrase();
            break;
        case 3:
            PrintTable(8, DISTCOLUMN, Space_Dist, DistColumnName, DistLength);
            Exit_Phrase();
            break;
        case 4:
            return;
        default:
            break;
        }
    }
}

void SearchDistDonation()
{
    while (1)
    {
        int choice;
        char choice_buffer[1000];
        while (1)
        {
            clrscr();
            char title[100] = "Search Distributed Donation";
            char menu[][50] = {"Search in current distributed donation", "Search in detailed distirbuted donation", "Return"};
            Print_Title(TITLELENGTH, strlen(title), title);
            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            Printf("Choice: ");
            scanf("%s", choice_buffer);
            fflush(stdin);
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
            SearchDistTotal();
            break;

        case 2:
            SearchDistHistory();
            break;

        case 3:
            return;

        default:
            break;
        }
    }
}

void SearchDistHistory()
{
    int i, k;
    int sum = 0;
    char search_target[1000];
    int search_index = -1;
    char title[100] = "Search in Detailed Distirbuted Donation";
    struct stocks *ptr;
    while (1)
    {
        clrscr();
        Print_Title(TITLELENGTH, strlen(title), title);
        Printf("**Format of Donation ID is DXXXXXX, where X are numbers");
        Printf("\nEnter Distributed ID: ");
        scanf("%s", search_target);
        fflush(stdin);
        for (i = 0; i < DistLength; i++)
        {
            if (strcmp(DistHead[i].distributed_ID, search_target) == 0)
            {
                search_index = i;
                break;
            }
        }
        if (search_index >= 0)
            break;
        else
            Printf("Distributed ID doesnt exist. Please enter again.\n");

        Exit_Phrase();
        return;
    }
    clrscr();
    //Printing the table
    sum = PrintTableHeader(DISTCOLUMN, Space_Dist, DistColumnName);
    PrintTableDistRow(Space_Dist, DistHead[i]);
    putchar('\n');
    for (i = 0; i < sum; i++)
        Printf("-");
    putchar('\n');
    Exit_Phrase();
    return;
}

void SearchDistTotal()
{
    int i, k;
    int sum = 0;
    char search_target[1000];
    struct dist_total *search_index = NULL;
    char title[100] = "Search in Current Distributed Donation";
    while (1)
    {
        clrscr();
        Print_Title(TITLELENGTH, strlen(title), title);
        Printf("**Format of stocks ID is IXXXXXX, where X are numbers");
        Printf("\nEnter Distributed ID: ");
        scanf("%s", search_target);
        fflush(stdin);
        DistTotal_Generator();
        search_index = NULL;
        for (struct dist_total *ptr = DistTotalHead; ptr != NULL; ptr = ptr->link)
            if (strcmp(ptr->disttotal_ID, search_target) == 0)
            {
                search_index = ptr;
                break;
            }
        if (search_index != NULL)
            break;
        else

            Printf("Distributed ID doesnt exist. Please enter again.\n");
        freeList_DistTotal(DistTotalHead);
        Exit_Phrase();
        return;
    }
    clrscr();
    //Printing the table
    sum = PrintTableHeader(DISTCOLUMN, Space_DistTotal, DistTotalColumnName);
    PrintTableDistTotalRow(Space_DistTotal, search_index);
    putchar('\n');
    for (i = 0; i < sum; i++)
        Printf("-");
    putchar('\n');
    Exit_Phrase();
    freeList_DistTotal(DistTotalHead);
    return;
}

void SupplyAccuDonation()
{
    double count[MAXSUPPLYTYPES] = {0};

    clrscr();
    char title[100] = "Accumulated Donation Received For Each Supply";
    Print_Title(TITLELENGTH, strlen(title), title);
    //Calculate quantity for each supply
    for (int i = 0; i < SupplyLength; i++)
    {
        for (int k = 0; k < SupplyTypeLength; k++)
        {
            if (strcmp(SupplyHead[i].supply_code, Supply_Type[k][0]) == 0)
            {
                count[k] += SupplyHead[i].init_quantity;
                break;
            }
        }
    }

    for (int i = 0; i < SupplyTypeLength; i++)
    {
        Printf("%s|%s - %f\n", Supply_Type[i][0], Supply_Type[i][1], count[i]);
    }
    putchar('\n');
    Exit_Phrase();
}

void DistAccuDonation()
{
    double count[MAXSUPPLYTYPES] = {0};

    clrscr();
    char title[100] = "Accumulated Distributed Donation for Each Supply";
    Print_Title(TITLELENGTH, strlen(title), title);
    //Calculate quantity for each supply
    for (int i = 0; i < DistLength; i++)
    {
        for (int k = 0; k < SupplyLength; k++)
        {
            if (strcmp(DistHead[i].donation_ID, SupplyHead[k].donation_ID) == 0)
            {
                for (int j = 0; j < SupplyTypeLength; j++)
                {
                    if (strcmp(SupplyHead[k].supply_code, Supply_Type[j][0]) == 0)
                    {
                        count[j] += DistHead[i].quantity;
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < SupplyTypeLength; i++)
    {
        Printf("%s|%s - %f\n", Supply_Type[i][0], Supply_Type[i][1], count[i]);
    }
    putchar('\n');
    Exit_Phrase();
}





