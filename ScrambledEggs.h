#ifndef SCRAMBLEDEGGS_H
#define SCRAMBLEDEGGS_H

#include <string>

/* Do NOT modify this file! */

class ScrambledEggs {
public:
    ScrambledEggs();
    void printGame();
    char getCurrentPlayer();
    void swapPlayer();
    bool move(std::string from, std::string to);
    bool hasConnected(char p);
    char gameOver();
private:
    char board[8][8];
    char currentPlayer, nextPlayer;
    int blacks, whites;

};

#endif // SCRAMBLEDEGGS_H
