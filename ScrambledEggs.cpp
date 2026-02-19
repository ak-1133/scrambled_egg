// Name: Kwok Ching Hin Alvin
// Student ID: 1155235807
// Email: 1155235807@link.cuhk.edu.hk

#include <iostream>
#include <string>
#include "ScrambledEggs.h"
using namespace std;

/* Only implements the ScrambledEggs class in this file.
   Do NOT write any main() function in this file! But you may write other extra
   functions (but not member functions) if you find necessary. */

ScrambledEggs::ScrambledEggs() {
    char init[8][8] = {
        {'.', 'W', 'B', 'W', 'B', 'W', 'B', '.'},
        {'B', '.', '.', '.', '.', '.', '.', 'W'},
        {'W', '.', '.', '.', '.', '.', '.', 'B'},
        {'B', '.', '.', '.', '.', '.', '.', 'W'},
        {'W', '.', '.', '.', '.', '.', '.', 'B'},
        {'B', '.', '.', '.', '.', '.', '.', 'W'},
        {'W', '.', '.', '.', '.', '.', '.', 'B'},
        {'.', 'B', 'W', 'B', 'W', 'B', 'W', '.'}
    };
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = init[i][j];
        }
    }

    currentPlayer = 'B';
    nextPlayer = 'W';
    blacks = 12;
    whites = 12;
}

void ScrambledEggs::printGame() {
    cout << "  a b c d e f g h " << endl;
    for (int i = 0; i < 8; ++i) {
        cout << i << " ";
        for (int j = 0; j < 8; ++j) {
            cout << board[i][j];
            if (j < 7) {
                cout << " ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

char ScrambledEggs::getCurrentPlayer() {
    return currentPlayer;
}

void ScrambledEggs::swapPlayer() {
    char temp = currentPlayer;
    currentPlayer = nextPlayer;
    nextPlayer = temp;
}

bool ScrambledEggs::move(string src, string land) {
    // Check for valid string length (length = 2)
    if ((src.length() != 2) || (land.length() != 2)) {
        return false;
    }

    // Check 1: Valid board positions
    if ((src[0] < 'a') || (src[0] > 'h') || (land[0] < 'a') || (land[0] > 'h')) {
        return false;
    }
    if ((src[1] < '0') || (src[1] > '7') || (land[1] < '0') || (land[1] > '7')) {
        return false;
    }

    int r1 = src[1] - '0';
    int c1 = src[0] - 'a';
    int r2 = land[1] - '0';
    int c2 = land[0] - 'a';

    // Check 2: Source position board[r1][c1] must contain the current player's piece
    if (board[r1][c1] != currentPlayer) {
        return false;
    }

    // Check 6: Landing position board[r2][c2] must NOT be a piece of the same player
    if ((r1 == r2) && (c1 == c2)) {
        return false;
    } 
    
    // Check 3: Move must be horizontal, vertical, or diagonal
    int dc = 0, dr = 0;
    bool isHorizointal = false;
    bool isVertical = false;
    bool isDiagonal = false;

    // Vertical
    if (c1 == c2) {
        isVertical = true;
        if (r2 > r1) {
            dr = 1;
        }
        else {
            dr = -1;
        }
    }

    // Horizontal
    else if (r1 == r2) {
        isHorizointal = true;
        if (c2 > c1) {
            dc = 1;
        }
        else {
            dc = -1;
        }
    }

    // Diagonal
    else if (abs(r2 - r1) == abs(c2 - c1)) {
        isDiagonal = true;
        if (c2 > c1) {
            dc = 1;
        }
        else {
            dc = -1;
        }
        if (r2 > r1) {
            dr = 1;
        }
        else {
            dr = -1;
        }
    }

    else {
        return false;
    }

    // Check 4: Move distance must exactly equal the number of pieces on that line
    int steps = 0;
    int piecesOnLine = 0;
    int c = c1 + dc;
    int r = r1 + dr;
    while ((c >= 0) && (c < 8) && (r >= 0) && (r < 8)) {
        if (board[r][c] != '.') {
            piecesOnLine++;
        }
        c += dc;
        r += dr;
        steps++;
    }

    c = c1 - dc;
    r = r1 - dr;
    while ((c >= 0) && (c < 8) && (r >= 0) && (r < 8)) {
        if (board[r][c] != '.') {
            piecesOnLine++;
        }
        c -= dc;
        r -= dr;
        steps++;
    }

    int dist;
    if ((dc == 0) || (dr == 0)) {
        dist = abs(c2 - c1) + abs(r2 - r1);
    }
    else {
        dist = abs(c2 - c1);
    }
    if (dist != (piecesOnLine + 1)) {
        return false;
    }

    // Check 5: Move must not jump over opponent's pieces
    c = c1 + dc;
    r = r1 + dr;
    while ((c != c2) || (r != r2)) {
        if ((board[r][c] != '.') && (board[r][c] != currentPlayer)) {
            return false;
        }
        c += dc;
        r += dr;
    }

    // Check landing square
    char target = board[r2][c2];
    if (target == currentPlayer) {
        return false;
    }
    if (target != '.') {
        char opponent;
        if (currentPlayer == 'B') {
            opponent = 'W';
        }
        else {
            opponent = 'B';
        }
        if (target != opponent) {
            return false;
        }
    }
    
    // Perform the move
    board[r1][c1] = '.';
    board[r2][c2] = currentPlayer;

    // Update piece counts if it was a capture
    if (target != '.') {
        if (currentPlayer == 'B') {
            whites--;
        }
        else {
            blacks--;
        }
    }

    // Move was valid and successful
    return true;
}

bool ScrambledEggs::hasConnected(char p) {
    if ((p == 'B' && blacks <= 1) || (p == 'W' && whites <= 1)) {
        return true;
    }

    bool reachability[8][8] = { false };
    int count = 0;
    int startR = -1, startC = -1;

    // Find the first piece of player p, set the square to true
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == p) {
                startR = i;
                startC = j;
                break;
            }
        }
    }

    if (startR == -1) {
        return true;
    }

    // Flood fill
    int stack[64][2];
    int top = 0;
    stack[top][0] = startR;
    stack[top][1] = startC;
    top++;
    reachability[startR][startC] = true;
    count = 1;

    int dr[] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dc[] = { -1, 0, 1, -1, 1, -1, 0, 1 };

    while (top > 0) {
        top--;
        int r = stack[top][0];
        int c = stack[top][1];

        for (int d = 0; d < 8; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];
            if ((nr >= 0) && (nr < 8) && (nc >= 0) && (nc < 8) && (!reachability[nr][nc]) && (board[nr][nc] == p)) {
                reachability[nr][nc] = true;
                count++;
                stack[top][0] = nr;
                stack[top][1] = nc;
                top++;
            }
        }
    }

    if (p == 'B') {
        return (count == blacks);
    }
    else {
        return (count == whites);
    }
}

char ScrambledEggs::gameOver() {
    bool bConnected = hasConnected('B');
    bool wConnected = hasConnected('W');

    if (bConnected && wConnected) {
        return 'D';
    }

    if (bConnected) {
        return 'B';
    }

    if (wConnected) {
        return 'W';
    }

    return '-';
}


