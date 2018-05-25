// Ishani Amin

#ifndef STOCK_H
#define STOCK_H


#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* DERIVED CLASS */

class Stock {

public:

	Stock(); //constructor

	void setEvent(char);
	char getEvent();

	void setStockSymbol(string);
	string getStockSymbol();

	void setSharesNum(int);
	int getSharesNum();

	void setPricePerStock(float);
	float getPricePerStock();

	void setTotalSharePrice(float);
	float getTotalSharePrice();

	void setTime(string);
	string getTime();

	Stock *next;
	Stock *previous;
	//Stock *current;
	//Stock *head;


private:

	char eventType;
	string stockSymbol;
	int sharesNum;
	float pricePerShare;
	float totalSharePrice;
	string timeOf;



};


#endif