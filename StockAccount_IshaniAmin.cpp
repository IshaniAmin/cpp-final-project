// Ishani Amin
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <ctime>
#include <vector>
//#include <windows.h>
using namespace std;


#include "StockAccount.h"
#include "Stock.h"
#include "StockTransaction.h"

// constructor
StockAccount::StockAccount() {

}

float StockAccount::readStockPrice(string stockInput) {

	int random = rand() % 2;

	ifstream inFile;

	if (random == 0) {
		inFile.open("Result_1.txt");
	}

	if (random == 1) {
		inFile.open("Result_2.txt");
	}

	if (inFile.fail()) {
		cout << "Error opening file" << endl;
	}

	string stockSymbol;
	float stockPrice;
	string date;

	while (!inFile.eof()) {

		inFile >> stockSymbol >> stockPrice >> date;

		if (stockSymbol == stockInput) {
			return stockPrice;
		}

	}

	inFile.close();
}

StockTransaction StockAccount::currentPortfolio() {

	Stock *ST;
	StockTransaction port;
	ST = transaction.getHead();

	// Go through the transaction history of all the transaction and consolidate them
	// Once we consolidaet each stock we putinto portfolio object
	deletePortfolio();
	while (ST != NULL)
	{
		string ss = ST->getStockSymbol();
		//cout << "SSSS=" << ss << endl;
		int stock = 0;
		// Check if we alrady consolidated this symbole from the porfolio object
		bool alreadyConsolidated = false;
		Stock *porth = port.getHead();
		while (porth != NULL) {
			if (porth->getStockSymbol() == ss) {
				alreadyConsolidated = true;
				break;
			}
			porth = porth->next;
		}
		if (!alreadyConsolidated) {
			Stock *ST1 = transaction.getHead();
			while (ST1 != NULL) {
				if (ST1->getStockSymbol() == ss) {
					//cout << "FOUND " << ss << endl;
					if (ST1->getEvent() == 'B')
						stock = stock + ST1->getSharesNum();
					else if (ST1->getEvent() == 'S')
						stock = stock - ST1->getSharesNum();
				}
				ST1 = ST1->next;
			}

			if (stock != 0) {
				Stock *addToPortfolio = new Stock();
				addToPortfolio->setStockSymbol(ss);
				addToPortfolio->setSharesNum(stock);
				addToPortfolio->setPricePerStock(readStockPrice(ss));
				addToPortfolio->setTotalSharePrice(addToPortfolio->getPricePerStock() * stock);
				//cout << "PRICE="<< addToPortfolio->getPricePerStock() << " STOCK=" << addToPortfolio->getStockSymbol() << " TOTAL=" << addToPortfolio->getTotalSharePrice() << endl;
				if (port.getHead() == NULL) {
					port.setHead(addToPortfolio);
					port.setTail(addToPortfolio);
					port.setCurrent(addToPortfolio);
					//stockTrans.setData(ST);
					//stockTrans.setCurrent(ST);
					//cout << "ADDED FIRST" << endl;
				}
				else {
					port.getCurrent()->next = addToPortfolio;
					addToPortfolio->previous = port.getCurrent();
					port.setCurrent(addToPortfolio);
					port.setTail(addToPortfolio);
					//cout << "ADDED SECOND" << endl;
				}
			}
		}
		ST = ST->next;

	}

	portfolio = port;
	sortPortfolio();
	ST = port.getHead();
	while (ST != NULL) {
		portfolioValue = portfolioValue + ST->getTotalSharePrice();
		ST = ST->next;
	}

	return port;
}



void StockAccount::writeStock() {

	ofstream outFile;

	outFile.open("stock_transaction_history.txt");

	if (outFile.fail()) {
		cout << "Error opening file write" << endl;
	}

	Stock *ST;
	ST = transaction.getHead();

	while (ST != NULL) {
		if (ST->next == NULL)
			outFile << ST->getEvent() << " " << ST->getStockSymbol() << " " << ST->getSharesNum() << " " << ST->getPricePerStock() << " " << ST->getTotalSharePrice() << " " << ST->getTime();
		else
			outFile << ST->getEvent() << " " << ST->getStockSymbol() << " " << ST->getSharesNum() << " " << ST->getPricePerStock() << " " << ST->getTotalSharePrice() << " " << ST->getTime() << endl;
		ST = ST->next;

	}


	outFile.close();
}


void StockAccount::buyShares(string compSym, int numShares, BankAccount &ba) {

	time_t now = time(0);
	tm *ltm = localtime(&now);
	// Check the bank balance from the Bank Account using friend function
	// to see it there is enough money to buy the stock


	string time = to_string(1 + ltm->tm_hour) + ":" + to_string(1 + ltm->tm_min) + ":" + to_string(1 + ltm->tm_sec);

	Stock *ST;

	ST = new Stock();

	ST->setEvent('B');
	ST->setStockSymbol(compSym);
	ST->setSharesNum(numShares);
	ST->setPricePerStock(readStockPrice(compSym));
	ST->setTotalSharePrice(numShares * ST->getPricePerStock());
	ST->setTime(time);
	ST->next = NULL;

	transaction.getCurrent()->next = ST;
	ST->previous = transaction.getCurrent();
	transaction.setCurrent(ST);
	transaction.setTail(ST);
	transaction.setCurrent(ST);
	transaction.setTail(ST);
	currentPortfolio();
	writeStock();

	ba.withdrawMoney(ST->getTotalSharePrice());


}


void StockAccount::sellShares(string compSym, int numShares, BankAccount &ba) {

	time_t now = time(0);
	tm *ltm = localtime(&now);

	string time = to_string(1 + ltm->tm_hour) + ":" + to_string(1 + ltm->tm_min) + ":" + to_string(1 + ltm->tm_sec);

	Stock *ST;

	ST = new Stock();

	ST->setEvent('S');
	ST->setStockSymbol(compSym);
	ST->setSharesNum(numShares);
	ST->setPricePerStock(readStockPrice(compSym));
	ST->setTotalSharePrice(numShares * ST->getPricePerStock());
	ST->setTime(time);
	ST->next = NULL;

	transaction.getCurrent()->next = ST;
	ST->previous = transaction.getCurrent();
	transaction.setCurrent(ST);
	transaction.setTail(ST);
	currentPortfolio();
	writeStock();

	ba.depositMoney(ST->getTotalSharePrice());

}


bool StockAccount::checkPortSymbol(string sym) {

	bool check = false;

	Stock *ST;

	ST = transaction.getHead();

	while (ST != NULL) {
		if (ST->getStockSymbol() == sym) {
			check = true;
			break;
		}
		ST = ST->next;
	}

	return check;
}


StockTransaction StockAccount::readStock() {

	ifstream inFile;
	inFile.open("stock_transaction_history.txt");

	if (inFile.fail()) {
		cout << "Error opening file read" << endl;
	}

	StockTransaction stockTrans;

	char eventType;
	string stockSymbol;
	int sharesNum;
	float pricePerShare;
	float totalSharePrice;
	string timeOf;
	Stock *ST;


	while (!inFile.eof()) {

		inFile >> eventType >> stockSymbol >> sharesNum >> pricePerShare >> totalSharePrice >> timeOf;

		ST = new Stock();

		ST->setEvent(eventType);
		ST->setStockSymbol(stockSymbol);
		ST->setSharesNum(sharesNum);
		ST->setPricePerStock(pricePerShare);
		ST->setTotalSharePrice(totalSharePrice);
		ST->setTime(timeOf);
		ST->next = NULL;


		if (stockTrans.getHead() == NULL) {
			stockTrans.setHead(ST);
			stockTrans.setTail(ST);
			stockTrans.setCurrent(ST);
		}
		else {
			stockTrans.getCurrent()->next = ST;
			ST->previous = stockTrans.getCurrent();
			stockTrans.setCurrent(ST);
			stockTrans.setTail(ST);
		}

	}

	inFile.close();

	return stockTrans;
}

void StockAccount::setStock(StockTransaction t) {
	transaction = t;
}

StockTransaction StockAccount::getStock() {
	return transaction;
}

void StockAccount::setPortfolio(StockTransaction portfolioValue) {
	portfolio = portfolioValue;
}

StockTransaction StockAccount::getPortfolio() {
	return portfolio;
}


void StockAccount::printPortfolio() {

	Stock *ST;
	ST = portfolio.getHead();


	cout << "Company-Symbol\tNumber\tPricePerShare\tTotalValue" << endl;


	while (ST != NULL) {

		cout << ST->getStockSymbol() << "\t\t";
		cout << ST->getSharesNum() << "\t";
		cout << "$" << ST->getPricePerStock() << "\t\t";
		cout << "$" << ST->getTotalSharePrice() << "\t\t" << endl;

		ST = ST->next;


	}

}



void StockAccount::printHistory() {

	Stock *ST;
	ST = transaction.getHead();


	cout << "Event\tCompSymbol\tNumber\tPricePerShare\tTotalValue\tTime" << endl;


	while (ST != NULL) {

		if (ST->getEvent() == 'B') {
			cout << "Buy\t";
		}
		else if (ST->getEvent() == 'S') {
			cout << "Sell\t";
		}

		cout << ST->getStockSymbol() << "\t\t";
		cout << ST->getSharesNum() << "\t";
		cout << "$" << ST->getPricePerStock() << "\t\t";
		cout << "$" << ST->getTotalSharePrice() << "\t\t";
		cout << ST->getTime() << endl;

		ST = ST->next;


	}

}
float StockAccount::getBankBalance(BankAccount &ba) {
	return ba.getCashBalance();
}


void StockAccount::deletePortfolio() {
	Stock *poh = portfolio.getHead();
	while (poh != NULL) {
		Stock *freeNode = poh;
		poh = poh->next;
		delete freeNode;
	}
}

void StockAccount::sortPortfolio() {

	Stock *head, *i, *j, *temp;

	head = portfolio.getHead();

	for (i = head; i->next != NULL; i = i->next) {
		for (j = i->next; j != NULL; j = j->next) {
			if (i->getTotalSharePrice() < j->getTotalSharePrice()) {
				temp = new Stock();
				temp->setPricePerStock(i->getPricePerStock());
				temp->setSharesNum(i->getSharesNum());
				temp->setStockSymbol(i->getStockSymbol());
				temp->setTime(i->getTime());
				temp->setTotalSharePrice(i->getTotalSharePrice());

				i->setPricePerStock(j->getPricePerStock());
				i->setSharesNum(j->getSharesNum());
				i->setStockSymbol(j->getStockSymbol());
				i->setTime(j->getTime());
				i->setTotalSharePrice(j->getTotalSharePrice());

				j->setPricePerStock(temp->getPricePerStock());
				j->setSharesNum(temp->getSharesNum());
				j->setStockSymbol(temp->getStockSymbol());
				j->setTime(temp->getTime());
				j->setTotalSharePrice(temp->getTotalSharePrice());
			}

		}
	}
}

void StockAccount::withdrawMoney(BankAccount &ba, float amount)
{
	ba.withdrawMoney(amount);
}
void StockAccount::setPortfolioValue(float v) {
	portfolioValue = v;
}
float StockAccount::getPortfolioValue() {
	return portfolioValue;
}