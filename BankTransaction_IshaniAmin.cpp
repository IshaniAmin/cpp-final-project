// Ishani Amin

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "BankTransaction.h"


// constructor
BankTransaction::BankTransaction() {


}


void BankTransaction::setType(char type) {
	transType = type;
}

char BankTransaction::getType() {
	return transType;
}


void BankTransaction::setDate(string newdate) {
	date = newdate;
}

string BankTransaction::getDate() {
	return date;
}


void BankTransaction::setAmount(float newamount) {
	amount = newamount;
}

float BankTransaction::getAmount() {
	return amount;
}

