#include "player.hpp"
namespace ariel {
    Player::Player(string name){
        this->name=name;
        this->cardsTakenCount=0;
        inGame= false;
    }
    bool Player::hasCard(Card card){
        size_t i;
        for (i = 0; i < stack.size(); i++)
        {
            if (this->stack.at(i).getSuit() == card.getSuit() && this->stack.at(i).getValue() == card.getValue()){
                return true;
            }
        }
        return false;
    }

    size_t Player::stacksize() {
        return this->stack.size();
    }

    void Player::addCardTaken() {
        this->cardsTakenCount++;
    }

    const Card &Player::getCard() {
        return this->stack.back();
    }
    void Player::addCard(Card& newCard) {
        if (this->hasCard(newCard)){
            throw invalid_argument("player have card in hand");
        }
        this->stack.push_back(newCard);
    }

    void Player::setInGame(bool value) {
        this->inGame = value;
    }

    size_t Player::cardesTaken() {
        return this->cardsTakenCount;
    }

    string Player::getName() {
        return this->name;
    }

    bool Player::isInGame() {
        return this->inGame;
    }

    void Player::RemoveCard() {
        this->stack.pop_back();
    }

    bool Player::operator==(const Player &other) {
        if(this->name == other.name)
            return true;
        return false;
    }
    string Player::toString() {
        return "Player name:" + this->name + " stack size: " + to_string(stack.size()) + " cardsVector in his hand" + to_string(cardsTakenCount) + " cardsVector taken";
    }
}