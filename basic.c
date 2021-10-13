#include "basic.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
void readFile_Donation()
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
}

void readFile_Dist()
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
}

void print_dist()
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
}

void PrintTableSupply()
{
    int i, sum = 0;
    //Iterate the whole list and calculate the sum of spaces of the whole table
    for (i = 0; i < SUPPLYCOLUMN; i++)
        sum += Space_Supply[i];

    //Need to calculate spaces for '|'
    sum += i;

    //Printing Table header
    for (i = 0; i < sum; i++)
        printf("-");
    putchar('\n');

    printTableDonationTitle(Space_Supply, SUPPLYCOLUMN, SupplyColumnName, 0);

    for (i = 0; i < sum; i++)
        printf("-");
    putchar('\n');

    //Printing Table Rows
    for(i = 0; i < SupplyLength; i++)
    {
        printTableDonationRow(Space_Supply, SupplyHead[i], 0);
        putchar('\n');
    }

    //Printing Table finish line
    for (i = 0; i < sum; i++)
        printf("-");
    putchar('\n');
       
}

static void printTableDonationRow(int space[], supply input, int skipdate)
{
    int i = 1;
    int daterow = 5;
    int space_index = 0;
    char buffer[100];
    
    printf("|");
    //Iterate over supply
    while(i < 9)
    {
        //Skip date column if skipdate == true
        if(skipdate == 1&& i == daterow)
        {
            i++;
            space_index++;
        }
        
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
}

static void printTableDonationTitle(int space[], int argc, char argv[MAXCOLUMN][30], int skipdate)
{
    int space_index = 0;
    int daterow = 5;
    printf("|");

    //Printing all the values
    for (int i = 0; i < argc; i++)
    {
        //Skip date column if skipdate == true
        if(skipdate && (i == daterow))
            i++;

        //Print column names
        printf("%s", argv[i]);
        for(int k = 0; k < space[space_index] - strlen(argv[i]); k++)
            printf(" ");

        space_index++;
        printf("|");
    }
    putchar('\n');
    
}

void clrscr()
{
   printf("\033[1J\033[H");
}

int main()
{
    //Retrive Data
    readFile_Donation();
    readFile_Dist();
    //Test if data be retreieved from txt files
    //PrintTableSupply();
    //print_donation();
    //printf(DATEFORMAT"\n", SupplyHead->donation_date.day, SupplyHead->donation_date.month, SupplyHead->donation_date.year);

    clrscr();
    
    PrintTableSupply();
    return 0;
}