#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


enum Player {
    X = 1,
    O = 2,
};

enum GameState {
    WIN,
    DRAW,
    RUN,
};


void showCurrentPlayer(enum Player* currentPlayer);
void showBoard(int* b, int size);
void getUserInput(int* b, enum Player* currentPlayer, int* movesCount);
void switchPlayer(enum Player* currentPlayer);
void setGameState(enum GameState* state, enum Player* currentPlayer, int* movesCount, int* b);
void showGameState(enum GameState* state, enum Player* currentPlayer);
void clearTerminal();
bool isPosAlreadyUse(int* pos, int* b);


int main() {
    int movesCount = 0;
    enum GameState currentState = RUN;
    enum Player currentPlayer = X;
    int board[] = {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
    };

    while (currentState == RUN) {
        showCurrentPlayer(&currentPlayer);
        showBoard(board, sizeof(board)/sizeof(board[0]));
        getUserInput(board, &currentPlayer, &movesCount);
        setGameState(&currentState, &currentPlayer, &movesCount, board);
        clearTerminal();
    }
    showGameState(&currentState, &currentPlayer);

    return 0;
}


void showBoard(int* b, int size) {
    for (int i = 0; i < size; i++) {
        char ch;
        switch (b[i]) {
            case 0:
                ch = '_';
                break;
            case 1:
                ch = 'X';
                break;
            case 2:
                ch = 'O';
                break;
        }

        printf("%c", ch);
        if (i == 2 || i == 5 || i == 8) {
            printf("\n");
        } else {
            printf("|");
        }
    }
}


void getUserInput(int* board, enum Player* currentPlayer, int* movesCount) {
    int pos;

    printf("Enter pos (1,9): ");
    scanf("%d", &pos);

    if (pos < 1 || pos > 9) {
        return;
    }

    if (isPosAlreadyUse(&pos, board)) {
        return;
    }

    board[pos-1] = *currentPlayer;
    switchPlayer(currentPlayer);
    (*movesCount)++;
}


void switchPlayer(enum Player* currentPlayer) {
    if (*currentPlayer == X) {
        *currentPlayer = O;
    } else {
        *currentPlayer = X;
    }
}


bool isPosAlreadyUse(int* pos, int* board) {
    if (board[(*pos)-1] != 0) {
        return true;
    }
    return false;
}


void showCurrentPlayer(enum Player* currentPlayer) {
    switch (*currentPlayer) {
        case X:
            printf("Turn: X\n");
            break;
        case O:
            printf("Turn: O\n");
            break;
    }
}


void setGameState(enum GameState* state, enum Player* currentPlayer, int* movesCount, int* board) {
    enum Player previousPlayer;

    if (*currentPlayer == X) {
        previousPlayer = O;
    } else {
        previousPlayer = X;
    }

    // COLUMNS
    if (
        previousPlayer == board[0] && board[0] == board[1] && board[1] == board[2]
        || previousPlayer == board[3] && board[3] == board[4] && board[4] == board[5]
        || previousPlayer == board[6] && board[6] == board[7] && board[7] == board[8]
    ){
        *state = WIN;
        return;
    }

    // ROWS
    if ( 
        previousPlayer == board[0] && board[0] == board[3] && board[3] == board[6]
        || previousPlayer == board[1] && board[1] == board[4] && board[4] == board[7]
        || previousPlayer == board[2] && board[2] == board[5] && board[5] == board[8]
    ){
        *state = WIN;
        return;
    }

    // DIAGONALS
    if (
        previousPlayer == board[0] && board[4] && board[8]
        || previousPlayer == board[2] && board[4] && board[6]
    ) {
        *state = WIN;
        return;
    }

    if (*movesCount > 8) {
        *state = DRAW;
        return;
    }
}


void showGameState(enum GameState* state, enum Player* currentPlayer) {
    char winner;

    if (*currentPlayer == X) {
        winner = 'O';
    } else {
        winner = 'X';
    }

    printf("### GAME IS OVER ###\n");

    switch (*state) {
        case DRAW:
            printf("State : DRAW\n");
            break;
        case WIN:
            printf("State : Win\n");
            printf("Winner: %c\n", winner);
            break;
        case RUN:
            break;
    }
}


void clearTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
