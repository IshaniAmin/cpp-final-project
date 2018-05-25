// Ishani Amin
#include <iostream>
#include <string>
#include <vector>

using namespace std;

//include header files
#include "Account.h"
#include "StockAccount.h"
#include "BankAccount.h"
#include "BankTransaction.h"
#include "Stock.h"
#include "StockTransaction.h"


int main() {

	// variable to save user choice
	int choice1 = 0;

	// when user enters 3, it will exit out of the program
	while (choice1 != 3) {
		
		// first menu options listed and then asks for user input saving it into variable "choice1"
		cout << "Welcome to the Account Management System. Please select an account to access:" << endl;
		cout << "1. Stock Portfolio Account" << endl;
		cout << "2. Bank Account" << endl;
		cout << "3. Exit" << endl;
		cout << "Your choice: ";
		cin >> choice1;
		cout << endl;

		// declaring classes as variables
		Account A;
		StockAccount SA;
		BankAccount BA;

		cout << " 1 " << endl;

		// setting up BankAccount
		vector<BankTransaction> bt;
		bt = BA.readTransaction();
		BA.setTransaction(bt); // setting bank account transaction
		BA.setCashBalance(BA.updateBalance()); //updating cash balance

		cout << " 2 " << endl;

		StockTransaction s; // declaring StockTransaction class as s
		s = SA.readStock(); // creating linked list of history
		SA.setStock(s); // setting stock to transaction
		SA.currentPortfolio(); // creating linked list of portfolio

		cout << " 3 " << endl;

		int choiceBank = 0; // variable for user input in bank menu
		int choiceStock = 0; // variable for user input in stock menu

		// Tried using matlab syntax but didn't work
		// --------------------------------------
		/*
		Engine *ep;
		mxArray *mp, *ans;
		double *ar, *detreal;int i, j;

		ep = engOpen(NULL);

		if (ep == NULL)
		{
		cout << "Error: Not Found”
		<< endl;
		exit(1);
		}

		mp = mxCreateDoubleMatrix(3, 3, 0);

		mxSetName(mp, "A");
		ar = mxGetPr(mp);
		for (i = 1;i<4:i++) {
		for (j = 1;j<4;:j++) {
		ar[i - 1 + 3 * (j - 1)] = j * j*i*i;
		}
		}
		ep = engOpen("");
		engPutArray(ep, mp);
		engEvalString(ep, "d = det(A);");
		engClose(ep);
		*/
		// --------------------------------------

		//StockAccount or choice 1
		if (choice1 == 1) {

			// when user enters 7, it will exit out of stock menu and back to previous menu
			while (choiceStock != 7) {

				// stock menu options listed and then asks for user input saving it into variable "choiceStock"
				cout << endl;
				cout << "Stock Portfolio Account" << endl;
				cout << "1. Display the price for a stock symbol" << endl;
				cout << "2. Display current portfolio" << endl;
				cout << "3. Buy shares" << endl;
				cout << "4. Sell shares " << endl;
				cout << "5. View a graph for the portfolio value " << endl;
				cout << "6. View transaction history" << endl;
				cout << "7. Return to previous menu" << endl;
				cout << "Please select an option: ";
				cin >> choiceStock;
				cout << endl;

				// creating variables that will be entered by user when buying or selling shared
				string stockSymbol;
				int sharesNum;
				float amt;

				switch (choiceStock) {
				
				// Display the price for a stock symbol
				case 1:
					cout << "Please enter the stock symbol: "; // asks user for stock symbol to check price for
					cin >> stockSymbol;
					cout << endl;

					// readStockPrice returns the price of the stock
					// if it returns a number that is greater then 0, price will be displayed
					if (SA.readStockPrice(stockSymbol) > 0) {
						cout << "Company symbol \t" << "Price per Share" << endl;
						cout << stockSymbol << "\t\t $" << SA.readStockPrice(stockSymbol) << endl;
					}
					// else user is told that the stock cannot be found
					else {
						cout << "Stock symbol cannot be found." << endl;
					}
					cout << endl;
					break;

				
				// Display current portfolio
				case 2:
					// setting cash balance to account
					A.setCashBalance(BA.getCashBalance());
					cout << "Cash balance= $" << A.getCashBalance() << endl;
					SA.printPortfolio(); // prints current portfolio
					cout << "Total portfolio value: " << SA.getPortfolioValue() << endl;
					cout << endl;
					break;

				// Buy shares
				case 3:
					cout << "Please enter the stock symbol you wish to purchase: ";
					cin >> stockSymbol;
					cout << "Please enter the number of shares you want to buy: ";
					cin >> sharesNum;
					cout << "Please enter the maximum amount you are willing to pay for each share: ";
					cin >> amt;
					cout << endl;

					// checking if there are enough funds in the bank to buy shares
					if ((SA.readStockPrice(stockSymbol) * sharesNum) >= SA.getBankBalance(BA)) {
						cout << "Not enough Fund to buy the stock" << endl;
						break;
					}

					// Checking if stock symbol can be found
					if (SA.readStockPrice(stockSymbol) > 0) {

						// Checking is price of stock is less then max amount user is willing to pay
						if (amt >= SA.readStockPrice(stockSymbol)) {
							SA.buyShares(stockSymbol, sharesNum, BA);
							SA.writeStock();
						}
						else {
							cout << "The price of the stock is more than what you are willing to pay for it." << endl;
						}

					}
					else {
						cout << "Stock symbol cannot be found." << endl;
					}

					cout << endl;
					break;

				// Sell shares
				case 4:
					cout << "Please enter the stock symbol of the shares you want to sell: ";
					cin >> stockSymbol;
					cout << "Please enter the number of shares you want to sell: ";
					cin >> sharesNum;
					cout << "Please enter the minimun amount you are willing to sell each share for: ";
					cin >> amt;
					cout << endl;

					// Checking if stock is in portfolio to sell
					if (SA.checkPortSymbol(stockSymbol)) {

						// Checking is price of stock is more then minumun amount user is willing to pay
						if (SA.readStockPrice(stockSymbol) > amt) {
							SA.sellShares(stockSymbol, sharesNum, BA);
							SA.writeStock();
						}
						else {
							cout << "The price of the stock is lower than the amount you are willing to sell it for." << endl;
						}
					}
					else {
						cout << "This stock is not in the portfolio." << endl;
					}

					cout << endl;
					break;

				// View a graph for the portfolio value
				// Matlab was not compatiable with my computer
				case 5:
					cout << endl;
					break;

					// View transaction history
				case 6:
					// prints stock transaction history using printHistory() function from Stock Account class
					SA.printHistory();
					cout << endl;
					break;
				default:
					cout << endl;
					cout << "Please enter one of the options" << endl;
				} // end switch
			} // end stock account while 
		} // end stock account if statement


		  //BankAccount or choice 2
		if (choice1 == 2) {

			// when user enters 5, it will exit out of bank menu and back to previous menu
			while (choiceBank != 5) {

				cout << "Bank Account: " << endl;
				cout << "Please select an option: " << endl;
				cout << "1. View account balance  " << endl;
				cout << "2. Deposit money " << endl;
				cout << "3. Withdraw money " << endl;
				cout << "4. Print out history " << endl;
				cout << "5. Return to previous menu " << endl;
				cout << "Your option: ";
				cin >> choiceBank;
				cout << endl;

				// creating deposit and withdraw variables
				int deposit;
				int withdraw;

				switch (choiceBank) {

				// View account balance
				case 1:
					// getting cash balance
					cout << "Account balance is: $" << BA.getCashBalance() << endl;
					cout << endl;
					break;

				// Deposit money
				case 2:
					// Asks user how much to deposit
					cout << "Please select the amount you wish to deposit: ";
					cin >> deposit;
					// passes user inut into depositMoney()
					BA.depositMoney(deposit);
					cout << endl;
					break;

				// Withdraw money
				case 3:
					// Asks user how much to withdraw
					cout << "Please select the amount you wish to withdraw: ";
					cin >> withdraw;

					// checking if there is enough money in the back to withdraw
					if (BA.getCashBalance() < withdraw) {
						cout << "Insufficient funds" << endl;
					}
					else {
						BA.withdrawMoney(withdraw);
					}
					cout << endl;
					break;

				// Print out history
				case 4:
					cout << "Bank History" << endl;
					BA.printHistory();
					cout << endl;
					break;
				} // end switch
			} // end for bank account while
		} // end bank account if statement

	} // end while for first menu

	return 0;

}