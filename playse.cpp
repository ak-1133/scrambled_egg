// Name: Kwok Ching Hin Alvin
// Student ID: 1155235807
// Email: 1155235807@link.cuhk.edu.hk

#include <iostream>
#include <string>
#include "ScrambledEggs.h"
using namespace std;

/* Implements the game flow. */
int main() {
    ScrambledEggs game;
    string src, dest;

    while (true) {
        game.printGame();
        cout << game.getCurrentPlayer() << "'s move: ";
        cin >> src >> dest;

        while (!game.move(src, dest)) {
            cout << "Invalid move. Try again!" << endl;
            cout << game.getCurrentPlayer() << "'s move: ";
            cin >> src >> dest;
        }

        char result = game.gameOver();
        if (result != '-') {
            game.printGame();

            if (result == 'B') {
                cout << "B wins!" << endl;
            }

            else if (result == 'W') {
                cout << "W wins!" << endl;
            }

            else if (result == 'D') {
                cout << "Draw game!" << endl;
            }

            break;
        }

        game.swapPlayer();
    }

   return 0;
}

/* You may write extra functions in this file if you find necessary. */
