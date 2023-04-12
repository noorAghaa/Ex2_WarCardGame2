#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "card.hpp"
using namespace std;
namespace ariel
{
    class Player
    {
        private:
            string name;
            vector<Card> stack;
            size_t cardsTakenCount;
            bool inGame;
        public:
            Player(string name);
            void RemoveCard();
            void addCard(Card&);
            bool operator==(const Player&);
            const Card& getCard();
            void addCardTaken();
            void setInGame(bool);
            size_t stacksize();
            size_t cardesTaken();
            bool isInGame();
            string getName();
            bool hasCard(Card);
            string toString();
    };
}