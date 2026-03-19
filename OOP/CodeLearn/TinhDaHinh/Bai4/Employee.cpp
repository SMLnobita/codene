#pragma once
#include <iostream>
using namespace std;
class Employee {
	string name;
	int paymentPerHour;
public:
	Employee(string name, int paymentPerHour){
		this->name = name;
		this->paymentPerHour = paymentPerHour;
	}
	void setName(string name) { this->name = name; }
	string getName() { return name; }
	void setPaymentPerHour(int paymentPerHour){
		this->paymentPerHour = paymentPerHour;
	}
	int getPaymentPerHour() { return paymentPerHour; }
	virtual int calculateSalary() = 0;
};