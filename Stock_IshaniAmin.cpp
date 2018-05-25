// Ishani Amin

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Stock.h"


// constructor
Stock::Stock() {

}

void Stock::setEvent(char evenTy) {
	eventType = evenTy;
}

char Stock::getEvent() {
	return eventType;
}

void Stock::setStockSymbol(string sym) {
	stockSymbol = sym;
}

string Stock::getStockSymbol() {
	return stockSymbol;
}

void Stock::setSharesNum(int shares) {
	sharesNum = shares;
}

int Stock::getSharesNum() {
	return sharesNum;
}

void Stock::setPricePerStock(float pricePer) {
	pricePerShare = pricePer;
}

float Stock::getPricePerStock() {
	return pricePerShare;
}

void Stock::setTotalSharePrice(float totalPrice) {
	totalSharePrice = totalPrice;
}

float Stock::getTotalSharePrice() {
	return totalSharePrice;
}

void Stock::setTime(string upTime) {
	timeOf = upTime;
}

string Stock::getTime() {
	return timeOf;
}
