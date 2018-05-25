
#ifndef BANKTRANSACTION_H
#define BANKTRANSACTION_H


#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* DERIVED CLASS */

class BankTransaction {

public:

	BankTransaction(); //constructor

	void setType(char);
	char getType();

	void setDate(string);
	string getDate();

	void setAmount(float);
	float getAmount();




private:

	char transType;
	string date;
	float amount;

};


#endif