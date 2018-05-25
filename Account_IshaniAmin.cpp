// Ishani Amin

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Account.h"

/* BASE CLASS */

//constructor
Account::Account() {

}

// set cash balance
void Account::setCashBalance(float cashBal) {
	cashBalance = cashBal;
}

//get cash balance
float Account::getCashBalance() {
	return cashBalance;
}