#include <iostream>
using namespace std;
#include "card.hpp"
namespace ariel {
    Card::Card(int value, int suit){
        this->value=value;
        this->suit=suit;
    }
    int Card::getSuit() const {return suit;}
    int Card::getValue() const {return value;}
    bool Card::operator==(const Card &other) const {
        return value == other.value;
    }
    bool Card::operator<(const Card &other) const {
        return value>other.value;
    }
    string Card::toString() const {
        string stringValue, stringSuit;
        if(value == 1)
        {
            stringValue = "Ace";
        } else if(value == 10)
        {
            stringValue = "Jack";
        } else if(value == 11)
        {
            stringValue = "Queen";
        }
        else if(value == 12)
        {
            stringValue = "King";
        } else stringValue = to_string(value);

        if(suit == 1)
        {
            stringSuit = "Clubs";
        }
        else if(suit == 2)
        {
            stringSuit = "Diamonds";

        }
        else if(suit == 3)
        {
            stringSuit = "Hearts";

        }else if(suit == 4)
        {
            stringSuit = "Spades";

        }

        return "Card Value: " + stringValue+ " of: "+ stringSuit;
    }
}