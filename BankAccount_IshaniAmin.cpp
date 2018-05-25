// Ishani Amin
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <ctime>
//#include <windows.h>
using namespace std;

#include "BankAccount.h"
#include "BankTransaction.h"

// constructor
BankAccount::BankAccount() {


}

vector<BankTransaction> BankAccount::readTransaction() {

	ifstream inFile;
	inFile.open("bank_transaction_history.txt");

	if (inFile.fail()) {
		cout << "Error opening file" << endl;
	}

	vector<BankTransaction> transactionHistory;

	char transactionType;
	string dateAdded;
	float newAmount;
	BankTransaction BT;

	while (!inFile.eof()) {

		inFile >> transactionType >> newAmount >> dateAdded;

		BT = *(new BankTransaction());
		BT.setType(transactionType);
		BT.setDate(dateAdded);
		BT.setAmount(newAmount);
		transactionHistory.push_back(BT);

	}

	inFile.close();

	return transactionHistory;

}



void BankAccount::writeTransaction() {

	ofstream outFile;

	outFile.open("bank_transaction_history.txt");

	if (outFile.fail()) {
		cout << "Error opening file" << endl;
	}

	for (int i = 0; i < transaction.size(); i++) {
		outFile << transaction[i].getType() << " " << transaction[i].getAmount() << " " << transaction[i].getDate() << endl;
	}

	outFile.close();
}


void BankAccount::depositMoney(float input) {


	time_t now = time(0);
	tm *ltm = localtime(&now);
	string date = to_string((1 + ltm->tm_mon)) + "/" + to_string((ltm->tm_mday)) + "/" + to_string((1900 + ltm->tm_year));

	BankTransaction BT;

	BT = *(new BankTransaction());
	BT.setType('D');
	BT.setDate(date);
	BT.setAmount(input);
	transaction.push_back(BT);

	setCashBalance(updateBalance());
	writeTransaction();

}

void BankAccount::withdrawMoney(float input) {


	time_t now = time(0);
	tm *ltm = localtime(&now);
	string date = to_string((1 + ltm->tm_mon)) + "/" + to_string((ltm->tm_mday)) + "/" + to_string((1900 + ltm->tm_year));

	BankTransaction BT;

	BT = *(new BankTransaction());
	BT.setType('W');
	BT.setDate(date);
	BT.setAmount(input);
	transaction.push_back(BT);

	setCashBalance(updateBalance());
	writeTransaction();


}




float BankAccount::updateBalance() {

	float balance = 0.00;

	for (int i = 0; i < transaction.size(); i++) {

		if (i == 0) {
			balance = transaction[i].getAmount();
		}
		else {
			if (transaction[i].getType() == 'D') {
				balance = balance + transaction[i].getAmount();
			}
			else if (transaction[i].getType() == 'W') {
				balance = balance - transaction[i].getAmount();
			}

		}
	}

	return balance;
}


void BankAccount::setTransaction(vector<BankTransaction> t) {
	transaction = t;
}
vector<BankTransaction> BankAccount::getTransaction() {
	return transaction;
}

void BankAccount::printHistory() {
	float balance;

	cout << "Event\t\tAmount\t\tDate\t\tBalance" << endl;

	for (int i = 0; i < transaction.size(); i++) {

		if (transaction[i].getType() == 'D') {
			cout << "Deposit\t\t";
		}
		else if (transaction[i].getType() == 'W') {
			cout << "Withdrawl\t";
		}

		cout << "$" << transaction[i].getAmount() << "\t\t";

		cout << transaction[i].getDate() << "\t";
		if (i == 0) {
			balance = transaction[i].getAmount();
		}
		else {
			if (transaction[i].getType() == 'D') {
				balance = balance + transaction[i].getAmount();
			}
			else {
				balance = balance - transaction[i].getAmount();
			}

		}
		cout << "$" << balance;
		cout << endl;

	}


}











