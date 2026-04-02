#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Card {
  string nameBook;
  string nameAuthor;
  int numberBook;

public:
  Card() {}
  Card(string nameBook, string nameAuthor, int numberBook) {
    this->nameBook = nameBook;
    this->nameAuthor = nameAuthor;
    this->numberBook = numberBook;
  }
  void display() {
    cout << "Name Book: " << nameBook << endl;
    cout << "Name Author: " << nameAuthor << endl;
    cout << "Number Book: " << numberBook << endl;
  }
  int getNumBook() { return numberBook; }
  void static sortCard(vector<Card> &card) {
    for (int i = 0; i < card.size() - 1; i++) {
      for (int j = i + 1; j < card.size(); j++) {
        if (card[i].numberBook > card[j].numberBook) {
          Card temp = card[i];
          card[i] = card[j];
          card[j] = temp;
        }
      }
    }
  }
};