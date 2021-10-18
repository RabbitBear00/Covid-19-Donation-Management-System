#include "basic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*void readFile_Donation()
{
    SupplyHead = NULL;
    DistHead = NULL;
    supply temp;
    supply *node, *curr;
    FILE *fp = fopen("donation.txt", "r");
    while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%d/%d/%d,%d,%d,%d\n", 
            temp.donation_ID, temp.supply_code, temp.supply_name, temp.donator, &temp.donation_date.day, 
            &temp.donation_date.month,&temp.donation_date.year,&temp.shipment_no, &temp.init_quantity, &temp.curr_quantity) != EOF)
    //while (fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%d/%d/%d,%d,%d\n", temp.donation_ID, temp.supply_code, temp.supply_name) != EOF)
      
    {
        node  = (supply*)malloc(sizeof(supply));
        strcpy(node->donation_ID, temp.donation_ID);
        strcpy(node->supply_code, temp.supply_code);
        strcpy(node->supply_name, temp.supply_name);
        strcpy(node->donator, temp.donator);
        node->donation_date = temp.donation_date;
        node->shipment_no = temp.shipment_no;
        node->init_quantity = temp.init_quantity;
        node->curr_quantity = temp.curr_quantity;
        node->link = NULL;
        
        if(SupplyHead == NULL)
        {
            SupplyHead = node;
            curr = node;
        }
        else
        {
            curr->link = node;
            curr = node;
        }
    }
    fclose(fp);
     
}*/
void ReadFile_Donation()
{
    int i = 0;
    supply temp;
    FILE *fp = fopen("./data/donation.txt", "r");

    //Retrieve data from donation.txt according to the format
    while (fscanf(fp, "%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%d/%d/%d\t%d\t%f\t%f\n",
                  temp.donation_ID, temp.supply_code, temp.supply_name, temp.donator, &temp.donation_date.day,
                  &temp.donation_date.month, &temp.donation_date.year, &temp.shipment_no, &temp.init_quantity, &temp.curr_quantity) != EOF)
    {
        //Copy all values from temp to array - SupplyHead
        strcpy(SupplyHead[i].donation_ID, temp.donation_ID);
        strcpy(SupplyHead[i].supply_code, temp.supply_code);
        strcpy(SupplyHead[i].supply_name, temp.supply_name);
        strcpy(SupplyHead[i].donator, temp.donator);
        SupplyHead[i].donation_date = temp.donation_date;
        SupplyHead[i].shipment_no = temp.shipment_no;
        SupplyHead[i].init_quantity = temp.init_quantity;
        SupplyHead[i].curr_quantity = temp.curr_quantity;

        //calculate length
        i++;
    }
    SupplyLength = i;
    fclose(fp);

    return;
}

/*void readFile_Dist()
{
    int i = 0;
    DistHead = NULL;
    dist temp;
    dist *node, *curr;
    FILE *fp = fopen("./data/dist.txt", "r");

    //Retrieve data from dist.txt according to the format
    while (fscanf(fp, "%[^\t]\t%[^\t]\t%[^\t]\t%d/%d/%d\t%[^\t]\t%f\n",
                  temp.distributed_ID, temp.donee_name, temp.donee_location, &temp.donation_date.day,
                  &temp.donation_date.month, &temp.donation_date.year, temp.donation_ID, &temp.quantity) != EOF)
    {
        //Copy all values from temp to node
        node = (dist *)calloc(1, sizeof(dist));
        strcpy(node->distributed_ID, temp.distributed_ID);
        strcpy(node->donee_name, temp.donee_name);
        strcpy(node->donee_location, temp.donee_location);
        node->donation_date = temp.donation_date;
        strcpy(node->donation_ID, temp.donation_ID);
        node->quantity = temp.quantity;

        //Linking the nodes to the list: DistHead
        if (DistHead == NULL)
        {
            DistHead = node;
            curr = node;
        }
        else
        {
            curr->link = node;
            curr = node;
        }
        //calculate length
        i++;
    }
    DistLength = i;
    fclose(fp);
}*/

void ReadFile_Dist()
{
    int i = 0;
    dist temp;
    FILE *fp = fopen("./data/dist.txt", "r");

    //Retrieve data from dist.txt according to the format
    while (fscanf(fp, "%[^\t]\t%[^\t]\t%[^\t]\t%d/%d/%d\t%[^\t]\t%[^\t]\t%f\t%f\t%d\n",
                  temp.distributed_ID, temp.donee_name, temp.donee_location, &temp.donation_date.day,
                  &temp.donation_date.month, &temp.donation_date.year, temp.donation_ID, &temp.stocks_ID, &temp.quantity, &temp.accu_quantity, &temp.transaction_no) != EOF)
    {
        //Copy all values from temp to array - DistHead
        strcpy(DistHead[i].distributed_ID, temp.distributed_ID);
        strcpy(DistHead[i].donee_name, temp.donee_name);
        strcpy(DistHead[i].donee_location, temp.donee_location);
        DistHead[i].donation_date = temp.donation_date;
        strcpy(DistHead[i].donation_ID, temp.donation_ID);
        strcpy(DistHead[i].stocks_ID, temp.stocks_ID);
        DistHead[i].quantity = temp.quantity;
        DistHead[i].accu_quantity = temp.accu_quantity;
        DistHead[i].transaction_no = temp.transaction_no;

        //calculate length
        i++;
    }
    DistLength = i;
    fclose(fp);

    return;
}

/*void print_dist()
{
    dist *ptr;
    for (ptr = DistHead; ptr != NULL; ptr = ptr->link)
    {
        printf("%s:%s:%s\n", ptr->distributed_ID, ptr->donee_name, ptr->donee_location);
    }
}

void print_donation()
{
    for (int i = 0; i < SupplyLength; i++)
    {
        printf("%s:%s:%s:%f\n", SupplyHead[i].donation_ID, SupplyHead[i].donator, SupplyHead[i].supply_name, SupplyHead[i].init_quantity);
    }
}*/
int PrintTableHeader(int col_count, int *space, char col_name[][30])
{
    int i, k, sum = 0;
    //Iterate the whole list and calculate the sum of spaces of the whole table
    for (i = 0; i < col_count; i++)
        sum += space[i];

    //Need to calculate spaces for '|'
    sum += i;

    //Printing Table header
    for (i = 0; i < sum; i++)
        printf("-");
    putchar('\n');

    printTableTitle(space, col_count, col_name);

    for (i = 0; i < sum; i++)
        printf("-");
    putchar('\n');

    return sum;
}
void PrintTable(int mode, int col_count, int *space, char col_name[][30], int row_count)
{
    int i, k, sum = 0;
    int sequence[MAXDIST];
    sum = PrintTableHeader(col_count, space, col_name);
    //Printing Table Rows(Mode 1: Supply, Mode 2: Dist, Mode 3: Stocks)
    switch (mode)
    {
    case 1:
        //Mode 1: Supply sort according to Supply ID(ascending)
        for (i = 0; i < row_count; i++)
        {
            printTableSupplyRow(space, SupplyHead[i]);
            putchar('\n');
        }
        break;

    case 2:
        //Mode 2: Dist sort according to Distributed ID(ascending)
        for (i = 0; i < row_count; i++)
        {
            printTableDistRow(space, DistHead[i]);
            putchar('\n');
        }
        break;

    case 3:
        //Mode 3: Stocks sort according to Stock ID(ascending)
        //Autogenerate table every time(Because Supply Will be updated if changes are made)
        Stock_Generator();
        for (struct stocks *ptr = StockHead; ptr != NULL; ptr = ptr->link)
        {
            printTableStockRow(Space_Stock, ptr);
            putchar('\n');
        }
        //Free the memory
        freeList(StockHead);
        break;

    case 4:
        //Mode 4: DistTotal sort according to DistTotal ID(ascending)
        //Autogenerate table every time(Because Dist Will be updated if changes are made)
        DistTotal_Generator();
        for (struct dist_total *ptr = DistTotalHead; ptr != NULL; ptr = ptr->link)
        {
            printTableDistTotalRow(Space_DistTotal, ptr);
            putchar('\n');
        }
        //Free the memory
        freeList_disttotal(DistTotalHead);

    case 5:
        //Mode 5: Supply Sort according to Initial Quantity(Descending)
        sequence_generator(sequence, SupplyLength);
        Sort_SupplyQuan(sequence, 1);
        //Go through sequence
        for (i = 0; i < SupplyLength; i++)
        {
            //Go through DistHead
            for (k = 0; k < SupplyLength; k++)
            {
                if (sequence[i] == k)
                {
                    printTableSupplyRow(Space_Supply, SupplyHead[k]);
                    putchar('\n');
                    break;
                }
            }
        }
        break;

    case 6:
        //Mode 6: Supply Sort according to Current Quantity(Descending)
        sequence_generator(sequence, SupplyLength);
        Sort_SupplyQuan(sequence, 2);
        //Go through sequence
        for (i = 0; i < SupplyLength; i++)
        {
            //Go through DistHead
            for (k = 0; k < SupplyLength; k++)
            {
                if (sequence[i] == k)
                {
                    printTableSupplyRow(Space_Supply, SupplyHead[k]);
                    putchar('\n');
                    break;
                }
            }
        }
        break;

    case 7:
        //Mode 7: Dist Sort according to Quantity(Descending)
        sequence_generator(sequence, DistLength);
        Sort_DistQuan(sequence, 1);
        //Go through sequence
        for (i = 0; i < DistLength; i++)
        {
            //Go through DistHead
            for (k = 0; k < DistLength; k++)
            {
                if (sequence[i] == k)
                {
                    printTableDistRow(Space_Dist, DistHead[k]);
                    putchar('\n');
                    break;
                }
            }
        }
        break;

    case 8:
        //Mode 8: Dist Sort according to Accumulative Quantity(Descending)
        sequence_generator(sequence, DistLength);
        Sort_DistQuan(sequence, 2);
        //Go through sequence
        for (i = 0; i < DistLength; i++)
        {
            //Go through DistHead
            for (k = 0; k < DistLength; k++)
            {
                if (sequence[i] == k)
                {
                    printTableDistRow(Space_Dist, DistHead[k]);
                    putchar('\n');
                    break;
                }
            }
        }
        break;

    case 9:
        //Mode 9: Stock Sort according to Initial Quantity(Descending)
        //Autogenerate table every time(Because Supply Will be updated if changes are made)
        Stock_Generator();
        Sort_StockQuan(&StockHead, StockLength, "init_quantity");
        for (struct stocks *ptr = StockHead; ptr != NULL; ptr = ptr->link)
        {
            printTableStockRow(Space_Stock, ptr);
            putchar('\n');
        }
        //Free the memory
        freeList(StockHead);
        break;

    case 10:
        //Mode 10: Stock Sort according to Current Quantity(Descending)
        //Autogenerate table every time(Because Supply Will be updated if changes are made)
        Stock_Generator();
        Sort_StockQuan(&StockHead, StockLength, "curr_quantity");
        for (struct stocks *ptr = StockHead; ptr != NULL; ptr = ptr->link)
        {
            printTableStockRow(Space_Stock, ptr);
            putchar('\n');
        }
        //Free the memory
        freeList(StockHead);
        break;

    case 11:
        //Mode 11: dist_total Sort according to Quantity(Descending)
        //Autogenerate table every time(Because dist Will be updated if changes are made)
        DistTotal_Generator();
        Sort_DistTotalQuan(&DistTotalHead, DistTotalLength, "quantity");
        for (struct dist_total *ptr = DistTotalHead; ptr != NULL; ptr = ptr->link)
        {
            printTableDistTotalRow(Space_DistTotal, ptr);
            putchar('\n');
        }
        //Free the memory
        freeList_disttotal(DistTotalHead);
        break;

    case 12:
        //Mode 12: dist_total Sort according to Accumulative Quantity(Descending)
        //Autogenerate table every time(Because dist Will be updated if changes are made)
        DistTotal_Generator();
        Sort_DistTotalQuan(&DistTotalHead, DistTotalLength, "accu_quantity");
        for (struct dist_total *ptr = DistTotalHead; ptr != NULL; ptr = ptr->link)
        {
            printTableDistTotalRow(Space_DistTotal, ptr);
            putchar('\n');
        }
        //Free the memory
        freeList_disttotal(DistTotalHead);
        break;

    default:
        break;
    }

    //Printing Table finish line
    for (i = 0; i < sum; i++)
        printf("-");
    putchar('\n');

    return;
}

static void printTableSupplyRow(int space[], supply input)
{
    int i = 1;
    int daterow = 5;
    int space_index = 0;
    char buffer[100];

    printf("|");
    //Iterate over supply
    while (i < SUPPLYCOLUMN + 1)
    {

        switch (i++)
        {
        //Could consider adding protection(check input length) to prevent buffer overflow
        //Iterate over every attribute in supply, storing values into buffer as string
        case 1:
            strcpy(buffer, input.donation_ID);
            break;

        case 2:
            strcpy(buffer, input.supply_code);
            break;

        case 3:
            strcpy(buffer, input.supply_name);
            break;

        case 4:
            strcpy(buffer, input.donator);
            break;

        case 5:
            snprintf(buffer, 99, DATEFORMAT, input.donation_date.day, input.donation_date.month, input.donation_date.year);
            break;

        case 6:
            snprintf(buffer, 99, INTFORMAT, input.shipment_no);
            break;

        case 7:
            snprintf(buffer, 99, FLOATFORMAT, input.init_quantity);
            break;

        case 8:
            snprintf(buffer, 99, FLOATFORMAT, input.curr_quantity);

        default:
            break;
        }

        //Printing all the values(attributes)
        printf("%s", buffer);
        for (int k = 0; k < space[space_index] - strlen(buffer); k++)
            printf(" ");

        space_index++;
        printf("|");
    }

    return;
}

static void printTableDistRow(int space[], dist input)
{
    int i = 1;
    int daterow = 5;
    int space_index = 0;
    char buffer[100];

    printf("|");
    //Iterate over supply
    while (i < DISTCOLUMN + 1)
    {
        switch (i++)
        {
        //Could consider adding protection(check input length) to prevent buffer overflow
        //Iterate over every attribute in supply, storing values into buffer as string
        case 1:
            strcpy(buffer, input.distributed_ID);
            break;

        case 2:
            strcpy(buffer, input.donee_name);
            break;

        case 3:
            strcpy(buffer, input.donee_location);
            break;

        case 4:
            snprintf(buffer, 99, DATEFORMAT, input.donation_date.day, input.donation_date.month, input.donation_date.year);
            break;

        case 5:
            strcpy(buffer, input.donation_ID);
            break;

        case 6:
            snprintf(buffer, 99, FLOATFORMAT, input.quantity);
            break;

        case 7:
            snprintf(buffer, 99, FLOATFORMAT, input.accu_quantity);
            break;

        default:
            break;
        }

        //Printing all the values(attributes)
        printf("%s", buffer);
        for (int k = 0; k < space[space_index] - strlen(buffer); k++)
            printf(" ");

        space_index++;
        printf("|");
    }

    return;
}

static void printTableStockRow(int space[], struct stocks *input)
{
    int i = 1;
    int index = input->supply_index;
    int space_index = 0;
    char buffer[100];

    printf("|");
    //Iterate over supply to find the index of the node's donation_ID

    while (i < STOCKCOLUMN + 1)
    {

        switch (i++)
        {
        //Could consider adding protection(check input length) to prevent buffer overflow
        //Iterate over every attribute in supply, storing values into buffer as string
        case 1:
            strcpy(buffer, input->stock_ID);
            break;

        case 2:
            strcpy(buffer, SupplyHead[index].supply_code);
            break;

        case 3:
            strcpy(buffer, SupplyHead[index].supply_name);
            break;

        case 4:
            strcpy(buffer, SupplyHead[index].donator);
            break;

        case 5:
            snprintf(buffer, 99, INTFORMAT, SupplyHead[index].shipment_no);
            break;

        case 6:
            snprintf(buffer, 99, FLOATFORMAT, input->init_quantity);
            break;

        case 7:
            snprintf(buffer, 99, FLOATFORMAT, input->curr_quantity);
            break;

        default:
            break;
        }

        //Printing all the values(attributes)
        printf("%s", buffer);
        for (int k = 0; k < space[space_index] - strlen(buffer); k++)
            printf(" ");

        space_index++;
        printf("|");
    }

    return;
}

static void printTableDistTotalRow(int space[], struct dist_total *input)
{
    int i = 1;
    int index = input->dist_index;
    int space_index = 0;
    char buffer[100];

    printf("|");
    //Iterate over supply to find the index of the node's donation_ID
    //+1 because i starts with 1
    while (i < DISTCOLUMN + 1)
    {

        switch (i++)
        {
        //Could consider adding protection(check input length) to prevent buffer overflow
        //Iterate over every attribute in supply, storing values into buffer as string
        case 1:
            strcpy(buffer, input->disttotal_ID);
            break;

        case 2:
            strcpy(buffer, DistHead[index].donee_name);
            break;

        case 3:
            strcpy(buffer, DistHead[index].donee_location);
            break;

        case 4:
            snprintf(buffer, 99, DATEFORMAT, DistHead[index].donation_date.day, DistHead[index].donation_date.month, DistHead[index].donation_date.year);
            break;

        case 5:
            strcpy(buffer, DistHead[index].stocks_ID);
            break;

        case 6:
            snprintf(buffer, 99, FLOATFORMAT, input->quantity);
            break;

        case 7:
            snprintf(buffer, 99, FLOATFORMAT, input->accu_quantity);
            break;

        default:
            break;
        }

        //Printing all the values(attributes)
        printf("%s", buffer);
        for (int k = 0; k < space[space_index] - strlen(buffer); k++)
            printf(" ");

        space_index++;
        printf("|");
    }

    return;
}

static void printTableTitle(int space[], int argc, char argv[MAXCOLUMN][30])
{
    int space_index = 0;
    int daterow = 5;
    printf("|");

    //Printing all the values
    for (int i = 0; i < argc; i++)
    {
        //Print column names
        printf("%s", argv[i]);
        for (int k = 0; k < space[space_index] - strlen(argv[i]); k++)
            printf(" ");

        space_index++;
        printf("|");
    }
    putchar('\n');

    return;
}

void Stock_Generator()
{
    StockHead = NULL;
    float total_curr_quan = 0;
    float total_init_quan = 0;
    int same_stock_count = 0;
    int finish[MAXSUPPLY];
    int finish_count = 0;
    int list_count = 1;
    int i, k;

    for (i = 0; i < SupplyLength; i++)
    {
        same_stock_count = 0;
        //Skip already recorded values
        //Skip this round if the current index is ald recorded
        if (skip_key(i, finish, finish_count))
            continue;

        for (k = i + 1; k < SupplyLength; k++)
        {
            //Skip already recorded values
            if (skip_key(k, finish, finish_count))
                continue;

            //If supply code, donator and date are the same, record the row number inside same_stock and finish, also calculate the sum of quantity
            if (!strcmp(SupplyHead[i].supply_code, SupplyHead[k].supply_code) && !strcmp(SupplyHead[i].donator, SupplyHead[k].donator) && (SupplyHead[i].shipment_no == SupplyHead[k].shipment_no))
            {
                //Add value of i into quantity
                if (same_stock_count == 0)
                {
                    same_stock_count++;
                    finish[finish_count] = i;
                    finish_count++;
                    total_init_quan += SupplyHead[i].init_quantity;
                    total_curr_quan += SupplyHead[i].curr_quantity;
                }

                //Add value of k into quantity
                same_stock_count++;
                finish[finish_count] = k;
                finish_count++;
                total_init_quan += SupplyHead[k].init_quantity;
                total_curr_quan += SupplyHead[k].curr_quantity;
            }
        }

        //Creating a new node to store quantity of stocks
        if (same_stock_count)
        {
            StockLength += 1;
            insertNode(i, total_init_quan, total_curr_quan);
        }
        else
        {
            StockLength += 1;
            insertNode(i, SupplyHead[i].init_quantity, SupplyHead[i].curr_quantity);
        }
    }

    return;
}

static void insertNode(int i, float total_init_quan, float total_curr_quan)
{
    struct stocks *node, *curr;

    //Formatting of Stock ID
    char buffer[10];
    snprintf(buffer, 8, STOCKIDFORMAT, StockLength);

    //Create a node
    node = (struct stocks *)calloc(1, sizeof(struct stocks));
    node->supply_index = i;
    strcpy(node->stock_ID, buffer);
    node->init_quantity = total_init_quan;
    node->curr_quantity = total_curr_quan;
    node->link = NULL;

    //Linking the node to the list: StockHead
    if (StockHead == NULL)
    {
        StockHead = node;
        curr = node;
    }
    else
    {
        curr->link = node;
        curr = node;
    }

    return;
}

static struct dist_total *insertNode_dist(int i, float quan, float accu_quan)
{
    struct dist_total *node, *curr;

    //Formatting of Stock ID
    char buffer[10];
    snprintf(buffer, 8, DIST_2IDFORMAT, DistTotalLength);

    //Create a node
    node = (struct dist_total *)calloc(1, sizeof(struct dist_total));
    node->dist_index = i;
    strcpy(node->disttotal_ID, buffer);
    node->quantity = quan;
    node->accu_quantity = accu_quan;
    node->link = NULL;

    //Linking the node to the list: StockHead
    if (DistTotalHead == NULL)
    {
        DistTotalHead = node;
        curr = node;
    }
    else
    {
        curr->link = node;
        curr = node;
    }

    return node;
}

static int skip_key(int i, int *finish, int finish_count)
{
    for (int j = 0; j < finish_count; j++)
    {
        //if same value appears return 1 else return 0
        if (i == finish[j])
        {
            return 1;
        }
    }
    return 0;
}

static void freeList(struct stocks *head)
{
    struct stocks *curr = head, *link;
    while (curr != NULL)
    {
        link = curr->link;
        free(curr);
        curr = link;
    }
    StockLength = 0;

    return;
}

int compare_dates(struct date d1, struct date d2)
{
    if (d1.year < d2.year)
        return -1;

    else if (d1.year > d2.year)
        return 1;

    if (d1.year == d2.year)
    {
        if (d1.month < d2.month)
            return -1;
        else if (d1.month > d2.month)
            return 1;
        else if (d1.day < d2.day)
            return -1;
        else if (d1.day > d2.day)
            return 1;
        else
            return 0;
    }
}

void clrscr()
{
    printf("\033[1J\033[H");

    return;
}

void Print_Title(int title_length, int argv_length, char *argv)
{
    for (int i = 0; i < title_length; i++)
        printf("-");
    putchar('\n');

    int space = (title_length - argv_length) / 2;

    for (int i = 0; i < space; i++)
        printf(" ");

    printf("%s\n", argv);

    for (int i = 0; i < title_length; i++)
        printf("-");
    printf("\n\n");

    return;
}

void Print_Menu(int argc, char argv[][30])
{
    for (int i = 1; i <= argc; i++)
    {
        printf("%d - %s\n", i, argv[i - 1]);
    }
    putchar('\n');
    return;
}

static void Sort_StockQuan(struct stocks **head, int count, char *mode_name)
{
    struct stocks **h;
    int i, j, swapped;

    //Mode 1: Init_quantity
    //Mode 2: Curr_quantity
    int mode;

    //Conditions Define
    if (strcmp(mode_name, "init_quantity") == 0)
        mode = 1;

    if (strcmp(mode_name, "curr_quantity") == 0)
        mode = 2;

    for (i = 0; i <= count; i++)
    {

        h = head;
        swapped = 0;

        for (j = 0; j < count - i - 1; j++)
        {

            struct stocks *p1 = *h;
            struct stocks *p2 = p1->link;
            if (p2 == NULL)
                continue;

            if (mode == 1 && (p1->init_quantity < p2->init_quantity))
            {
                /* update the link after swapping */
                *h = swap(p1, p2);
                swapped = 1;
            }

            if (mode == 2 && (p1->curr_quantity < p2->curr_quantity))
            {
                /* update the link after swapping */
                *h = swap(p1, p2);
                swapped = 1;
            }

            h = &(*h)->link;
        }

        /* break if the loop ended without any swap */
        if (swapped == 0)
            break;
    }
}

static struct stocks *swap(struct stocks *ptr1, struct stocks *ptr2)
{
    struct stocks *tmp = ptr2->link;
    ptr2->link = ptr1;
    ptr1->link = tmp;
    return ptr2;
}

/*void swap_data(struct stocks* ptr1, struct stocks* ptr2)
{
    struct stocks temp;
    temp = *ptr1;

    strcpy(ptr1->stock_ID, ptr2->stock_ID);
    ptr1->supply_index = ptr2->supply_index;
    ptr1->init_quantity = ptr2->init_quantity;
    ptr1->curr_quantity = ptr2->curr_quantity;

    strcpy(ptr2->stock_ID, temp.stock_ID);
    strcpy(ptr2->)
    
}*/

static void Sort_DistQuan(int *sequence, int mode)

{
    //mode 1: Quantity(Desc)
    //mode 2: Accumulative quantity(Desc)
    for (int i = 0; i < DistLength - 1; i++)
    {
        //index positions
        for (int k = 0; k < DistLength - i - 1; k++)
        {
            if (mode == 1 && DistHead[sequence[k]].quantity < DistHead[sequence[k + 1]].quantity)
            {
                int temp = sequence[k];
                sequence[k] = sequence[k + 1];
                sequence[k + 1] = temp;
            }

            if (mode == 2 && DistHead[sequence[k]].accu_quantity < DistHead[sequence[k + 1]].accu_quantity)
            {
                int temp = sequence[k];
                sequence[k] = sequence[k + 1];
                sequence[k + 1] = temp;
            }
        }
    }
}

static void Sort_SupplyQuan(int *sequence, int mode)

{
    //mode 1: Init Quantity
    //mode 2: Curr Quantity
    for (int i = 0; i < SupplyLength - 1; i++)
    {
        //index positions
        for (int k = 0; k < SupplyLength - i - 1; k++)
        {
            if (mode == 1 && SupplyHead[sequence[k]].init_quantity < SupplyHead[sequence[k + 1]].init_quantity)
            {
                int temp = sequence[k];
                sequence[k] = sequence[k + 1];
                sequence[k + 1] = temp;
            }

            if (mode == 2 && SupplyHead[sequence[k]].curr_quantity < SupplyHead[sequence[k + 1]].curr_quantity)
            {
                int temp = sequence[k];
                sequence[k] = sequence[k + 1];
                sequence[k + 1] = temp;
            }
        }
    }
}

static void sequence_generator(int *sequence, int length)
{
    for (int i = 0; i < length; i++)
    {
        sequence[i] = i;
    }
}

void DistTotal_Generator()
{
    DistTotalHead = NULL;
    struct dist_total *ptr;
    float quan = 0;
    float accu_quan = 0;
    int i, k;

    //Let the list exist first
    //insertNode_dist(0, DistHead[0].quantity, DistHead[0].accu_quantity);
    //ptr = DistTotalHead;
    for (i = 0; i < DistLength; i++)
    {
        ptr = insertNode_dist(i, DistHead[i].quantity, DistHead[i].accu_quantity);
        DistTotalLength++;

        //When the list has only one data, need to skip this step
        if (ptr->link != NULL)
            ptr = ptr->link;

        //Add the quantity to the list if transaction no turns out to be the same
        while (DistHead[i].transaction_no == DistHead[i + 1].transaction_no)
        {
            ptr->quantity += DistHead[i + 1].quantity;
            ptr->accu_quantity += DistHead[i + 1].accu_quantity;
            i++;
        }
    }
    return;
}

static struct dist_total *swap_disttotal(struct dist_total *ptr1, struct dist_total *ptr2)
{
    struct dist_total *tmp = ptr2->link;
    ptr2->link = ptr1;
    ptr1->link = tmp;
    return ptr2;
}

static void Sort_DistTotalQuan(struct dist_total **head, int count, char *mode_name)
{
    struct dist_total **h;
    int i, j, swapped;

    //Mode 1: Init_quantity
    //Mode 2: Curr_quantity
    int mode;

    //Conditions Define
    if (strcmp(mode_name, "quantity") == 0)
        mode = 1;

    if (strcmp(mode_name, "accu_quantity") == 0)
        mode = 2;

    for (i = 0; i <= count; i++)
    {

        h = head;
        swapped = 0;

        for (j = 0; j < count - i - 1; j++)
        {

            struct dist_total *p1 = *h;
            struct dist_total *p2 = p1->link;
            if (p2 == NULL)
                continue;

            if (mode == 1 && (p1->quantity < p2->quantity))
            {
                //update the link after swapping
                *h = swap_disttotal(p1, p2);
                swapped = 1;
            }

            if (mode == 2 && (p1->accu_quantity < p2->accu_quantity))
            {
                //update the link after swapping
                *h = swap_disttotal(p1, p2);
                swapped = 1;
            }

            //Move to the next item in the list
            h = &(*h)->link;
        }

        /* break if the loop ended without any swap */
        if (swapped == 0)
            break;
    }
}

static void freeList_disttotal(struct dist_total *head)
{
    struct dist_total *curr = head, *link;
    while (curr != NULL)
    {
        link = curr->link;
        free(curr);
        curr = link;
    }
    DistTotalLength = 0;

    return;
}

int Validation_Date(struct date input)
{
    if (input.year >= 1000 && input.year <= 9999)
    {
        //check month
        if (input.month >= 1 && input.month <= 12)
        {
            //check days
            if ((input.day >= 1 && input.day <= 31) && (input.month == 1 || input.month == 3 || input.month == 5 || input.month == 7 || input.month == 8 || input.month == 10 || input.month == 12))
                return 1;
            else if ((input.day >= 1 && input.day <= 30) && (input.month == 4 || input.month == 6 || input.month == 9 || input.month == 11))
                return 1;
            else if ((input.day >= 1 && input.day <= 28) && (input.month == 2))
                return 1;
            else if (input.day == 29 && input.month == 2 && (input.year % 400 == 0 || (input.year % 4 == 0 && input.year % 100 != 0)))
                return 1;
            else
            {
                printf("Invalid Date Input/Format.\n");
                return 0;
            }
        }
        else
        {
            printf("Invalid Date Input/Format.\n");
            return 0;
        }
    }
    else
    {
        printf("Invalid Date Input/Format.\n");
        return 0;
    }

    printf("Invalid Date Input/Format.\n");
    return 0;
}

int Validation_CharLength(int limit, int input_length)
{
    if (input_length > limit)
    {
        printf("The length can only be within %d characters.\n", limit);
        return 0;
    }

    return 1;
}

int validation_isdigit(int limit, char *input, int input_length)
{
    if (input_length > limit)
    {
        printf("The length can only be within %d characters.\n", limit);
        return 0;
    }

    for (int i = 0; i < input_length; i++)
    {
        if (isdigit(input[i]) == 0)
        {
            printf("Only numbers can be accepted.\n");
            return 0;
        }
    }

    return 1;
}

int validation_isfloat(char *input, int input_length)
{
    //To check whether . appeared
    int dotted = 0;
    for (int i = 0; i < input_length; i++)
    {
        if (input[i] == '.' && !dotted)
        {
            dotted = 1;
            continue;
        }
        if (isdigit(input[i]) == 0)
        {
            printf("Only numbers can be accepted.\n");
            return 0;
        }
    }

    if (atof(input) < 10000000)
        return 1;
    else
    {
        printf("Cannot exceed 10000000.\n");
        return 0;
    }
}

int validation_supply_code(char *input)
{
    for (int i = 0; i < SUPPLYTYPES; i++)
    {
        if (strcmp(input, Supply_Type[i][0]) == 0)
            return i;
    }
    printf("Invalid Supply Code.\n");
    return -1;
}

void ConfirmSupplySection(supply *input)
{
    int choice;
    char choice_buffer[1000];
    char title[30] = "Confirm Your Record";
    char menu[][30] = {"Confirm", "Cancel"};
    char buffer[100];
    while (1)
    {
        while (1)
        {
            Print_Title(TITLELENGTH, strlen(title), title);
            Print_SupplyList(input, -1, NULL);

            Print_Menu(sizeof(menu) / sizeof(menu[0]), menu);
            printf("Choice: ");
            scanf("%s", choice_buffer);
            if (validation_isdigit(1000, choice_buffer, strlen(choice_buffer)))
                choice = atoi(choice_buffer);
            else
                continue;
            //printf("%d %d", sizeof(menu), sizeof(menu[0]));
            //printf("%d\n",CHOICE_CONDITION);
            if (CHOICE_CONDITION)
                break;
        }

        switch (choice)
        {
        case 1:
            //Write data into file
            SupplyToFile();
            return;

        case 2:
            SupplyLength--;
            printf("You have cancelled this record.\n");
            Exit_Phrase();
            return;

        default:
            break;
        }
    }
}

void Exit_Phrase()
{
    printf("Press any key to continue......");
    getchar();
    getchar();
}

void Print_SupplyList(supply *input, int choice, char *edited_data)
{
    char buffer[1000];
    for (int i = 0; i < SUPPLYCOLUMN; i++)
    {
        //Print the edited data
        if (i == choice)
        {
            printf("%s: %s\n", SupplyColumnName[i], edited_data);
            if (choice == 1)
            {
                //Need to find the string of certain supply code
                int k = 0;
                for (k = 0; i < SUPPLYTYPES; k++)
                    if (strcmp(edited_data, Supply_Type[k][0]) == 0)
                        break;
                printf("%s: %s\n", SupplyColumnName[i], Supply_Type[k][1]);
                i++;
            }
            i++;
        }
        switch (i)
        {
        case 0:
            strcpy(buffer, input->donation_ID);
            break;
        case 1:
            strcpy(buffer, input->supply_code);
            break;
        case 2:
            strcpy(buffer, input->supply_name);
            break;
        case 3:
            strcpy(buffer, input->donator);
            break;
        case 4:
            snprintf(buffer, 50, DATEFORMAT, input->donation_date.day, input->donation_date.month, input->donation_date.year);
            break;
        case 5:
            snprintf(buffer, 99, INTFORMAT, input->shipment_no);
            break;
        case 6:
            snprintf(buffer, 99, FLOATFORMAT, input->init_quantity);
            break;
        case 7:
            snprintf(buffer, 99, FLOATFORMAT, input->curr_quantity);
            break;
        default:
            break;
        }
        printf("%s: %s\n", SupplyColumnName[i], buffer);
    }
}

void SupplyToFile()
{
    FILE *fp;

    fp = fopen("./data/donation.txt", "w+");
    for (int i = 0; i < SupplyLength; i++)
    {
        fprintf(fp, "%s\t%s\t%s\t%s\t%d/%d/%d\t%d\t%f\t%f\n", SupplyHead[i].donation_ID, SupplyHead[i].supply_code, SupplyHead[i].supply_name, SupplyHead[i].donator, SupplyHead[i].donation_date.day,
                SupplyHead[i].donation_date.month, SupplyHead[i].donation_date.year, SupplyHead[i].shipment_no, SupplyHead[i].init_quantity, SupplyHead[i].curr_quantity);
    }
    fclose(fp);
}
/*int main()
{
    int choice;
    //Retrive Data
    ReadFile_Donation();
    ReadFile_Dist();
    DistTotal_Generator();

    //Test if data be retreieved from txt files
    //PrintTableSupply();
    //print_donation();
    //printf(DATEFORMAT"\n", SupplyHead->donation_date.day, SupplyHead->donation_date.month, SupplyHead->donation_date.year);
    printf("%d %d", SupplyLength, DistLength);

    PrintTable(1, SUPPLYCOLUMN, Space_Supply, SupplyColumnName, SupplyLength, 0);
    PrintTable(2, DISTCOLUMN, Space_Dist, DistColumnName, DistLength, 0);
    PrintTable(3, STOCKCOLUMN, Space_Stock, StockColumnName, StockLength, 0);
    PrintTable(4, STOCKCOLUMN, Space_Stock, StockColumnName, StockLength, 0);
    PrintTable(5, STOCKCOLUMN, Space_Stock, StockColumnName, StockLength, 0);
    PrintTable(6, DISTCOLUMN, Space_Dist, DistColumnName, DistLength, 0);
    PrintTable(7, DISTCOLUMN, Space_Dist, DistColumnName, DistLength, 0);
    PrintTable(8, DISTCOLUMN, Space_DistTotal, DistTotalColumnName, DistTotalLength, 0);
    PrintTable(9, DISTCOLUMN, Space_DistTotal, DistTotalColumnName, DistTotalLength, 0);



    return 0;
}*/