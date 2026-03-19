#include "Author.cpp"
#include <iostream>
#include <vector>

using namespace std;

class Book {
private:
	string name;
	vector<Author> authors;
	double price;
public:
	Book(string name, vector<Author> authors, double price) {
		this->name = name;
		this->authors = authors;
		this->price = price;
	}
	void setName(string name) { this->name = name; }
	string getName() { return name; }
	void setPrice(double price) { this->price = price; }
	double getPrice() { return price; }
	string getAuthorNames() {
		string authorNames = "";
		for (int i = 0; i < authors.size()-1; i++)
		{
			authorNames += authors[i].getName() + ", ";
		}
		authorNames += authors[authors.size() - 1].getName();
		return authorNames;
	}
};