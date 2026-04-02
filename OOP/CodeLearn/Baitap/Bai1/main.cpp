#include "Card.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<Card> cards;
  cards.push_back(Card("Lap Trinh C++", "Bjarne", 5));
  cards.push_back(Card("Giai Tich", "Nguyen Van A", 1));
  cards.push_back(Card("Vat Ly Dai Cuong", "Tran Van B", 3));
  cards.push_back(Card("Co So Du Lieu", "Le Van C", 2));

  cout << "=== TRUOC KHI SAP XEP ===" << endl;
  for (int i = 0; i < cards.size(); i++) {
    cards[i].display();
    cout << endl;
  }

  Card::sortCard(cards);

  cout << "=== SAU KHI SAP XEP (tang dan theo so sach) ===" << endl;
  for (int i = 0; i < cards.size(); i++) {
    cards[i].display();
    cout << endl;
  }

  return 0;
}