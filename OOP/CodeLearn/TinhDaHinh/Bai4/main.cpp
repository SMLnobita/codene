#include <iostream>
#include "Employee.cpp"
#include "FullTimeEmployee.cpp"
#include "PartTimeEmployee.cpp"

int main() {
	Employee* nhanvien[2];
	nhanvien[0] = new PartTimeEmployee("Trung", 45000, 7);
	nhanvien[1] = new FullTimeEmployee("Linh", 65000);

	for (int i = 0; i < 2; i++)
	{
		cout << "==============================" << endl;
		cout << "Name: " << nhanvien[i]->getName() << endl;
		cout << "Salary per day: " << nhanvien[i]->calculateSalary() << endl;
	}
	return 0;
}