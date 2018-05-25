// Ishani Amin

#ifndef STOCKTRANSACTION_H
#define STOCKTRANSACTION_H

#include <iostream>
#include <string>

using namespace std;

#include "Stock.h"
#include "Account.h"

class StockTransaction {

public:
	StockTransaction(); //constructor

	void setHead(Stock*);
	Stock* getHead();

	void setTail(Stock*);
	Stock* getTail();

	//void setNext(Stock*);
	//Stock* getNext();

	//void setPrevious(Stock*);
	//Stock* getPrevious();

	//void setData(Stock*);
	//Stock* getData();

	void setCurrent(Stock*);
	Stock* getCurrent();


private:

	Stock * head;
	Stock *tail;
	Stock *current;


};



#endif