#pragma once
#include <vector>
#include "card.hpp"
#include "player.hpp"


namespace ariel
{
    class Game
    {
        private:
            Player& playerOne;
            Player& playerTwo;
            Player *Winner;
            int TurnsCount;
            int DrawsCount;
            int PlayerOneWinsCount;
            int PlayerTwoWinsCount;
            vector<Card> cardsVector;
            vector<Card> player1CardsVector;
            vector<Card> player2CardsVector;
            string lastturnStats;
            string log;

        public:
            Game(Player&, Player&);
            void playTurn();
            void printLog() const;
            void printStats();
            void dealCards();
            void printLastTurn() const;
            void playAll();
            void printWiner() const;
            void CardsEqual(int &DrawThisTurn, Card &playerOneCard, Card &playerTwoCard);
            void playerTwoDominates(int DrawThisTurn);
            void playerOneDominates(int DrawThisTurn);
            void noMorePlays();
    };
}