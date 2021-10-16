#ifndef MENU_H
#define MENU_H

//Function Declaration

//Menus
//The first menu of all
void MainMenu();

//Primary Menus
void Dashboard();
void DonationSupplies();
void DistributedDonation();

//Secondary Menus for DonationSupplies()
void AddDonationSupply();
void EditDonationSupply();
void ViewHistoryRecord_Supply();
void SearchDonationSupplies();
void SearchStocks();
void SearchSupplyHistory();

//Secondary Menus for DistributedDonation();
void AddDistDonation();
void EditDistDonation();
void ViewHistoryRecord_Dist();
void SearchDistDonation();
void SearchDistHistory();
void SearchDistTotal();

//Secondary Menus for Dashboard

#endif