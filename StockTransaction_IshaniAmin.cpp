// Ishani Amin


#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <ctime>
//#include <windows.h>

#include "StockAccount.h"
#include "Stock.h"
#include "StockTransaction.h"

using namespace std;

// constructor
StockTransaction::StockTransaction() {

}





void StockTransaction::setHead(Stock* theHead) {
	head = theHead;
}

Stock* StockTransaction::getHead() {
	return head;
}






void StockTransaction::setTail(Stock* theTail) {
	tail = theTail;
}

Stock* StockTransaction::getTail() {
	return tail;
}

/*


void StockTransaction::setNext(Stock* nxtPtr) {
next = nxtPtr;
}

Stock* StockTransaction::getNext() {
return next;
}





void StockTransaction::setPrevious(Stock* prePtr) {
previous = prePtr;
}

Stock* StockTransaction::getPrevious() {
return previous;
}





void StockTransaction::setData(Stock* upData) {
data = upData;
}

Stock* StockTransaction::getData() {
return data;
}


*/

void StockTransaction::setCurrent(Stock* cur) {
	current = cur;
}

Stock* StockTransaction::getCurrent() {
	return current;
}