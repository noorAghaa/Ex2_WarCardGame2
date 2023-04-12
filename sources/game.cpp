
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib>
#include "game.hpp"

namespace ariel
{
    Game::Game(Player &plr1, Player &plr2) : playerOne(plr1), playerTwo(plr2), Winner(nullptr), lastturnStats(" "), log(" "), TurnsCount(0), DrawsCount(0), PlayerOneWinsCount(0), PlayerTwoWinsCount(0) {
        for(int t=1;t<5;t++)
        {
            for (int i = 1; i < 14; ++i)
                cardsVector.push_back(Card(i, t));
        }
        // Shuffle the cardsVector from https://stackoverflow.com/questions/6926433/how-to-shuffle-a-stdvector
        unsigned seed = (unsigned) time(NULL);
        auto rng = default_random_engine(seed);
        shuffle(cardsVector.begin(), cardsVector.end(), rng);
        dealCards();

        this->playerOne.setInGame(true);
        this->playerTwo.setInGame(true);
    }

    void Game::dealCards() {
        int k=0;
        while(!cardsVector.empty())
        {
            if (k == 0){
                playerOne.addCard(cardsVector.back());
                k=1;
            }
            else
            {
                playerTwo.addCard(cardsVector.back());
                k=0;
            }
            cardsVector.pop_back();
        }
    }


    void Game::playTurn()
    {
        if (playerOne.isInGame() && playerTwo.isInGame())
        {
            this->TurnsCount++;
            if (this->TurnsCount > 26){
                throw invalid_argument("cannot go over 26 turns");
            }
            int DrawThisTurn = 0;
            this->lastturnStats = "null";

            Card playerOneCard = playerOne.getCard();
            Card playerTwoCard = playerTwo.getCard();

            playerOne.RemoveCard();
            playerTwo.RemoveCard();
            cout << playerOne.getName() << "   " << playerOneCard.toString() << "  " << playerTwo.getName() << " playedd with" << playerTwoCard.toString();
            this->lastturnStats = "turn  " + to_string(this->TurnsCount) + ":\n" + playerOne.getName() + " playedd " + playerOneCard.toString() + "  " + playerTwo.getName() + " played with" + playerTwoCard.toString() ;


            while (playerOneCard == playerTwoCard)
            {
                CardsEqual(DrawThisTurn, playerOneCard, playerTwoCard);
            }

            if (playerOneCard < playerTwoCard)
            {
                playerTwoDominates(DrawThisTurn);
            }
            else
            {
                playerOneDominates(DrawThisTurn);
            }
            if (!playerOne.stacksize() || !playerTwo.stacksize())
            {
                noMorePlays();
            }
            this->log += this->lastturnStats;

        }
        else
        {
            throw invalid_argument("gameover");
        }
    }

    void Game::noMorePlays() {
        playerOne.setInGame(false);
        playerTwo.setInGame(false);
        if(playerOne.cardesTaken() > playerTwo.cardesTaken())
        {
            Winner =&playerOne;
        }

        else
        {
            Winner =&playerTwo;
        }
    }

    void Game::playerOneDominates(int DrawThisTurn) {
        cout << playerOne.getName() << " win" << endl;
        lastturnStats += (playerTwo.getName() + "win the round" + "\n" + "draws: " + to_string(DrawThisTurn)) + "\n";
        PlayerOneWinsCount++;
        playerOne.addCardTaken();
        playerOne.addCardTaken();


        while(!player1CardsVector.empty())
        {
            playerOne.addCardTaken();

            player1CardsVector.pop_back();
        }

        while(!player2CardsVector.empty())
        {
            playerOne.addCardTaken();
            player2CardsVector.pop_back();
        }
    }


    void Game::playerTwoDominates(int DrawThisTurn) {
        cout << playerTwo.getName() << " win" << endl;
        lastturnStats += (playerOne.getName() + " win the round" + "\n" + "Draws" + to_string(DrawThisTurn)) + "\n";
        PlayerTwoWinsCount++;

        playerTwo.addCardTaken();
        playerTwo.addCardTaken();

        while(!player1CardsVector.empty())
        {

            playerTwo.addCardTaken();
            player1CardsVector.pop_back();

        }

        while(!player2CardsVector.empty())
        {

            playerTwo.addCardTaken();

            player2CardsVector.pop_back();
        }
    }

    void Game::CardsEqual(int &DrawThisTurn, Card &playerOneCard, Card &playerTwoCard) {

        DrawsCount++;

        DrawThisTurn++;

        cout << "draw." << endl;

        lastturnStats += "Draw!\n";

        if (playerOne.stacksize() < 2 || playerTwo.stacksize() < 2)
        {
            unsigned seed2 = (unsigned) time(NULL);
            auto rng2 = default_random_engine(seed2);
            shuffle(player1CardsVector.begin(), player1CardsVector.end(), rng2);

            seed2 = (unsigned) time(NULL);
            rng2 = default_random_engine(seed2);
            shuffle(player2CardsVector.begin(), player2CardsVector.end(), rng2);

            while(!player1CardsVector.empty())
            {

                playerOne.addCard(player1CardsVector.back());
                player1CardsVector.pop_back();

            }


            while(!player2CardsVector.empty())
            {
                playerTwo.addCard(player2CardsVector.back());
                player2CardsVector.pop_back();
            }
        }

        player1CardsVector.push_back(playerOne.getCard());
        player2CardsVector.push_back(playerTwo.getCard());

        playerOne.RemoveCard();
        playerTwo.RemoveCard();


        playerOneCard = playerOne.getCard();

        playerTwoCard = playerTwo.getCard();


        cout << playerOne.getName() << " played  " << playerOneCard.toString() << " " << playerTwo.getName() << "  pglayed " << playerTwoCard.toString() << ". ";
        lastturnStats += playerOne.getName() + " played  " + playerOneCard.toString() + " " + playerTwo.getName() + " played  k" + playerTwoCard.toString() + ". ";
    }

    void Game::playAll()
    {
        while (playerOne.isInGame() && playerTwo.isInGame() && this->TurnsCount < 26)
        {
            playTurn();
        }
    }

    void Game::printWiner() const {
        if (playerOne.cardesTaken() > playerTwo.cardesTaken()) {
            cout << this->playerOne.getName() << " wins " << this->playerOne.cardesTaken() << "cardsVector" << endl;
        } else if (playerOne.cardesTaken() < playerTwo.cardesTaken()) {
            cout << this->playerTwo.getName() << " wins << this->playerTwo.cardesTaken()" << "cardsVector" << endl;
        } else {
            cout << "draw" << this->playerOne.cardesTaken() << "cardsVecto" << endl;
        }
    }

    void Game::printLastTurn() const {

        cout << lastturnStats << endl;
    }

    void Game::printStats()
    {

    }

    void Game::printLog() const {
        cout << log << endl;
    }

}