// Ishani Amin

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Account {

public:

	Account(); //constructor

	// get and set cash balance
	void setCashBalance(float);
	float getCashBalance();

private:

	float cashBalance;

};


#endif