// Ishani Amin

#ifndef STOCKACCOUNT_H
#define STOCKACCOUNT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Account.h"
#include "Stock.h"
#include "StockTransaction.h"
#include "BankAccount.h"

/* DERIVED CLASS */

class StockAccount : public Account {

public:

	//constructor
	StockAccount();

	float readStockPrice(string);

	StockTransaction currentPortfolio();

	StockTransaction readStock();

	void writeStock();

	void buyShares(string, int, BankAccount&);
	void sellShares(string, int, BankAccount&);

	bool checkPortSymbol(string);

	void setStock(StockTransaction);
	StockTransaction getStock();

	void setPortfolio(StockTransaction);
	StockTransaction getPortfolio();

	void sortPortfolio();


	void printPortfolio();

	void printHistory();



	float getBankBalance(BankAccount&);

	void withdrawMoney(BankAccount&, float);

	void deletePortfolio();

	void setPortfolioValue(float);
	float getPortfolioValue();


private:

	StockTransaction transaction;
	StockTransaction portfolio;
	float portfolioValue;
};


#endif