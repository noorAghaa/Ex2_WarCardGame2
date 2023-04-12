#pragma once
#include <iostream>
#include <string>
using namespace std;
namespace ariel
{
    class Card
    {
        private:
            int value;
            int suit;
        public:
            Card(int value, int suit);
            int getValue() const;
            int getSuit() const;
            bool operator==(const Card &other) const;
            bool operator<(const Card &other) const;
            string toString() const;
    };
}
