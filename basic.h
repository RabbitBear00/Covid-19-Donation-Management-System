#ifndef basic_h
#define basic_h
//donation_ID,supply_code,supply_name,donator,donation_date,no. of shipment,Initial Quantity(millions),Current Quantity(millions)
//distributed_ID,donee_name,donee_location,donation_date,donation_ID,donated quantity(millions)

#define MAXSUPPLY 9999
#define SUPPLYCOLUMN 8
#define DISTCOLUMN 6
#define STOCKCOLUMN 7
#define MAXCOLUMN 10
#define FLOATFORMAT "%f"
#define INTFORMAT "%d"
#define DATEFORMAT "%02d/%02d/%04d"
//Data Structure for date
struct date
{
    int day;
    int month;
    int year;
};

//Data Structure for donation.txt
typedef struct supply
{
    char donation_ID[8];
    char supply_code[3];
    char supply_name[30];
    char donator[20];
    struct date donation_date;
    int shipment_no;
    float init_quantity;
    float curr_quantity;  
    struct supply *link;

}supply;

//Data Structure for dist.txt
typedef struct dist
{
    char distributed_ID[8];
    char donee_name[30];
    char donee_location[20];
    struct date donation_date;
    char donation_ID[8];
    float quantity;
    struct dist *link;

}dist;

//Data Structure for stocks
struct stocks
{
    char donation_ID[8];
};
//Variables to store data from txt files
supply SupplyHead[MAXSUPPLY];
dist *DistHead;

//Length of the array and list
int SupplyLength = 0;
int DistLength = 0;

//Space and length of the table
int Space_Supply[MAXCOLUMN] = {12, 12, 31, 21, 16, 14, 24, 24};
int Space_Dist[MAXCOLUMN] = {15, 31, 21, 13, 12, 16};
int Space_Stock[MAXCOLUMN] = {12, 12, 31, 21, 11, 24, 24};

//Column names
char SupplyColumnName[MAXCOLUMN][30] = {"Donation ID", "Supply Code", "Supply Name", "Donator", "Donation Date", "Shipment No.", "Quantity Received(mil.)", "Current Quantity(mil.)"};
char DistColumnName[MAXCOLUMN][30] = {"Distributed ID", "Donee Name", "Donee Location", "Donation Date", "Donation ID", "Quantity(mil.)"};
char StockColumnName[MAXCOLUMN][30] = {"Donation ID", "Supply Code", "Supply Name", "Donator", "Shipment No.", "Initial Quantity(mil.)", "Current Quantity(mil.)"};

//Function Declaration
//Get data from donation.txt, save in array: SupplyHead
void ReadFile_Donation();

//Get data from dist.txt, save in list: DistHead
void ReadFile_dist();

//Get current stocks from donation.txt storage: SupplyHead
void Stock_Generator();

//Printing donation supply table
void PrintTableSupply();
static void printTableDonationRow(int space[], supply input, int skipdate);
static void printTableDonationTitle(int space[], int argc, char argv[MAXCOLUMN][30], int skipdate);

//Printing distributed donation table
void PrintTableDist();

//Printing stock supply table
void PrintTableStock();

//Printing menus tool
void Print_Title(int space, int length, char argv[][10]);
void Print_Menu(int argc, char argv[][10]);

//Clear console
void clrscr();

//Validation functions
void Validation_Date(struct date input);
void Validation_CharLength(int limit, int input_length, char* input);
void validation_intlength(int limit, int *input);

#endif