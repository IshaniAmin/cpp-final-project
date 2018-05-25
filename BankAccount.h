// Ishani Amin


#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;


#include "Account.h"
#include "BankTransaction.h"


/* DERIVED CLASS */

class BankAccount : public Account {

public:

	BankAccount(); //constructor

	vector<BankTransaction> readTransaction();

	void writeTransaction();

	void depositMoney(float);
	void withdrawMoney(float);


	void setTransaction(vector<BankTransaction>);
	vector<BankTransaction> getTransaction();

	float updateBalance();

	void printHistory();
	friend class StockAccount;

private:

	vector<BankTransaction> transaction;


};


#endif
