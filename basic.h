#ifndef BASIC_H
#define BASIC_H
//donation_ID,supply_code,supply_name,donator,donation_date,no. of shipment,Initial Quantity(millions),Current Quantity(millions)
//distributed_ID,donee_name,donee_location,donation_date,donation_ID,donated quantity(millions)

#define MAXSUPPLY 9999
#define MAXDIST 9999
#define SUPPLYCOLUMN 8
#define DISTCOLUMN 7
#define STOCKCOLUMN 7
#define MAXCOLUMN 10
#define FLOATFORMAT "%.2f"
#define INTFORMAT "%d"
#define DATEFORMAT "%02d/%02d/%04d"
#define STOCKIDFORMAT "T%06d"
#define SUPPLYIDFORMAT "S%06d"
#define DISTIDFORMAT "D%06d"
#define DIST_2IDFORMAT "I%06d"
#define TITLELENGTH 50
#define SUPPLYTYPES 5
#define CHOICE_CONDITION (choice >= 1) && (choice <= sizeof(menu) / sizeof(menu[0]))

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

} supply;

//Data Structure for dist.txt
typedef struct dist
{
    char distributed_ID[8];
    char donee_name[30];
    char donee_location[20];
    struct date donation_date;
    char donation_ID[8];
    char stocks_ID[8];
    float quantity;
    float accu_quantity;
    int transaction_no;

} dist;

//Data Structure for stocks

struct stocks
{
    int supply_index;
    char stock_ID[8];
    float init_quantity;
    float curr_quantity;
    struct stocks *link;
};

struct dist_total
{
    int dist_index;
    char disttotal_ID[8];
    float quantity;
    float accu_quantity;
    struct dist_total *link;
};

//Variables to store data from txt files
supply SupplyHead[MAXSUPPLY];
dist DistHead[MAXDIST];
struct stocks *StockHead;
struct dist_total *DistTotalHead;

//Length of the array and list
int SupplyLength = 0;
int DistLength = 0;
int StockLength = 0;
int DistTotalLength = 0;

//Space and length of the table
int Space_Supply[MAXCOLUMN] = {12, 12, 31, 21, 16, 14, 24, 24};
int Space_Dist[MAXCOLUMN] = {15, 31, 21, 16, 12, 16, 32};
int Space_DistTotal[MAXCOLUMN] = {15, 31, 21, 16, 12, 16, 32};
int Space_Stock[MAXCOLUMN] = {12, 12, 31, 21, 14, 24, 24};

//Column names
char SupplyColumnName[MAXCOLUMN][30] = {"Donation ID", "Supply Code", "Supply Name", "Donator", "Donation Date", "Shipment No.", "Quantity Received(mil.)", "Current Quantity(mil.)"};
char DistColumnName[MAXCOLUMN][30] = {"Distributed ID", "Donee Name", "Donee Location", "Donation Date", "Donation ID", "Quantity(mil.)", "Accumulative Quantity(mil.)"};
char DistTotalColumnName[MAXCOLUMN][30] = {"Distributed ID", "Donee Name", "Donee Location", "Donation Date", "Stock ID", "Quantity(mil.)", "Accumulative Quantity(mil.)"};
char StockColumnName[MAXCOLUMN][30] = {"Stock ID", "Supply Code", "Supply Name", "Donator", "Shipment No.", "Initial Quantity(mil.)", "Current Quantity(mil.)"};

//Supply Types that can donate
char Supply_Type[][2][30] = {{"CT", "Contactless Thermometer"}, {"HS", "Hand Sanitizers"}, {"FM", "Face Mask"}, {"SM", "Surgical Mask"}, {"OM", "Oxygen Mask"}};

//Function Declaration
//Get data from donation.txt, save in array: SupplyHead
void ReadFile_Donation();

//Get data from dist.txt, save in list: DistHead
void ReadFile_Dist();

//Printing donation supply stocks table
void PrintTable(int mode, int col_count, int *space, char col_name[][30], int row_count, int skipdate);
static void printTableTitle(int space[], int argc, char argv[MAXCOLUMN][30], int skipdate);
static void printTableSupplyRow(int space[], supply input, int skipdate);
static void printTableDistRow(int space[], dist input, int skipdate);
static void printTableStockRow(int space[], struct stocks *input);
static void printTableDistTotalRow(int space[], struct dist_total *input);

//Printing menus tool
void Print_Title(int title_length, int argv_size, char argv[100]);
void Print_Menu(int argc, char argv[][30]);

//Comparing Dataes: d1 < d2: -1; d1 == d2: 0; d1 > d2: 1;
int compare_dates(struct date d1, struct date d2);

//Clear console
void clrscr();

//Validation functions
//Return 1 when date is valid else return 0
int Validation_Date(struct date input);
int Validation_CharLength(int limit, int input_length);
int validation_isdigit(int limit, char *input, int input_length);
int validation_isfloat(char *input, int input_length);
int validation_supply_code(char* input);

//Functions for stock list
//Generate list for struct stocks
void Stock_Generator();
//Insert node for struct stocks
static void insertNode(int i, float total_init_quan, float total_curr_quan);
//swap nodes for struct stocks
static struct stocks *swap(struct stocks *ptr1, struct stocks *ptr2);
//Sort nodes for struct stocks(initial quantity, current quantity)
static void Sort_StockQuan(struct stocks **head, int count, char *mode);
//free list for struct stocks
static void freeList(struct stocks *head);
//Check if the row is recorded in array finish, if it is recorded skip the current loop
static int skip_key(int i, int *finish, int finish_count);

//Dist type functions
//Sorting dist type's initial quantity and current quantity
static void Sort_DistQuan(int *sequence, int mode);
//Generate an array sequence pf [0, length-1] to be sorted in Sort_DistQuan
static void sequence_generator(int *sequence, int length);

//Functions for dist_total list
//Generate list for struct dist_total
void DistTotal_Generator();
//Insert node for struct dist_total
static struct dist_total *insertNode_dist(int i, float quan, float accu_quan);
//Sort nodes for struct dist_total(quantity, accumulative quantity)
static void Sort_DistTotalQuan(struct dist_total **head, int count, char *mode_name);
//Swap nodes for struct dist_total
static struct dist_total *swap_disttotal(struct dist_total *ptr1, struct dist_total *ptr2);
//Free list for struct dist_total
static void freeList_disttotal(struct dist_total *head);

//Press any key to continue
void Exit_Phrase();

//Write data into file
void SupplyToFile();

//Print List Out
void Print_SupplyList(supply *input, int choice, char* edited_data);


#endif