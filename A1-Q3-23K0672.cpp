#include <iostream>
#include <math.h> // for calculating changes in new and old co-ords
using namespace std;

class ChessPiece {
    private:
        string name;
        string color;
        char symbol;

    public:
        ChessPiece() {
            name = "Pawn";
            color = "White";
            symbol = 'P';
        }

        ChessPiece(string pieceName, string pieceColor, char pieceSymbol) {
            name = pieceName;
            color = pieceColor;
            symbol = pieceSymbol;
        }

        string getName() {
            return this -> name;
        }

        string getColor() {
            return this -> color;
        }

        char getSymbol() {
            return this -> symbol;
        }

        void setName(string newName) {
            this -> name = newName;
        }

        void setColor(string newColor) {
            if (newColor == "Black" || newColor == "White") { 
                this -> color = newColor;
            }
            else {
                cout << "Invalid color entered.";
            }
        }

        void setSymbol(char newSymbol) {
            if ((color == "White") && (newSymbol >= 97 && newSymbol <= 122)) {
                this -> symbol = newSymbol;
            }
            else if ((color == "Black") && (newSymbol >= 65 && newSymbol <= 90)) {
                this -> symbol = newSymbol;
            }
        }
};

const int size = 8;

class ChessBoard {
    private:
        ChessPiece *ChessGrid[size][size];

    public:
        ChessBoard() { // intialization
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    ChessGrid[i][j] = nullptr;
                }
            }

            for (int j = 0; j < size; ++j) {
                ChessGrid[0][j] = new ChessPiece("b", "Black", 'B');
                ChessGrid[1][j] = new ChessPiece("Pawn", "Black", 'P');
                ChessGrid[7][j] = new ChessPiece("w", "White", 'W');
                ChessGrid[6][j] = new ChessPiece("Pawn", "White", 'p');
            }

            ChessGrid[0][0] = ChessGrid[0][7] = new ChessPiece("Rook", "Black", 'R');
            ChessGrid[0][1] = ChessGrid[0][6] = new ChessPiece("Knight", "Black", 'N');
            ChessGrid[0][2] = ChessGrid[0][5] = new ChessPiece("Bishop", "Black", 'B');
            ChessGrid[0][3] = new ChessPiece("Queen", "Black", 'Q');
            ChessGrid[0][4] = new ChessPiece("King", "Black", 'K');
            
            ChessGrid[7][0] = ChessGrid[7][7] = new ChessPiece("Rook", "White", 'r');
            ChessGrid[7][1] = ChessGrid[7][6] = new ChessPiece("Knight", "White", 'n');
            ChessGrid[7][2] = ChessGrid[7][5] = new ChessPiece("Bishop", "White", 'b');
            ChessGrid[7][3] = new ChessPiece("Queen", "White", 'q');
            ChessGrid[7][4] = new ChessPiece("King", "White", 'k');
        }

        ~ChessBoard() {
            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < size; ++j) {
                    delete ChessGrid[i][j];
                }
            }
        }

        void display() {
            cout << "\n\nCurrent state of the board:\n";

            cout << "\ta\tb\tc\td\te\tf\tg\th\n";
            for (int i = 0; i < size; i++) {
                cout << 8 - i << "\t";
                for (int j = 0; j < size; j++) {
                    if (ChessGrid[i][j] == nullptr) {
                        cout << "." << "\t";
                    }
                    else {
                        cout << ChessGrid[i][j]->getSymbol() << "\t";
                    }
                }
                cout << 8 - i << "\n";
            }
            cout << "\ta\tb\tc\td\te\tf\tg\th\n";
        }

        // implementation for the first moves only

        bool movePiece(string source, string destination) {
            // finding indices for movement
            int row = '8' - source[1];
            int col = source[0] - 'a';
            int newRow = '8' - destination[1];
            int newCol = destination[0] - 'a';

            // for black pawns
            if (ChessGrid[row][col]->getSymbol() == 'P') {
                if (row == 1 && ((newRow == row + 1) || (newRow == row + 2))) {
                    if (ChessGrid[newRow][newCol] == nullptr) { 
                        ChessGrid[newRow][newCol] = new ChessPiece("Pawn", "Black", 'P');
                        return true;
                    }
                }
            }
            // for white pawns
            if (ChessGrid[row][col]->getSymbol() == 'p') {
                if (row == 6 && ((newRow == row - 1) || (newRow == row - 2))) {
                    if (ChessGrid[newRow][newCol] == nullptr) { 
                        ChessGrid[newRow][newCol] = new ChessPiece("Pawn", "White", 'p');
                        return true;
                    }
                }
            }
            // for both black and white knights
            if ((ChessGrid[row][col]->getColor() == "Black" && ChessGrid[row][col]->getSymbol() == 'N') ||
                (ChessGrid[row][col]->getColor() == "White" && ChessGrid[row][col]->getSymbol() == 'n')) {
                int moveRows = newRow - row;
                int moveCols = newCol - col;
                if ((abs(moveRows) == 2 && abs(moveCols) == 1) || (abs(moveCols) == 2 && abs(moveRows) == 1)) {
                    ChessGrid[newRow][newCol] = ChessGrid[row][col];
                    ChessGrid[row][col] = nullptr;
                    return true;
                }
            }
            return false;
        }
};

int main () {
    cout << "23K-0672\t\tSyeda Batool Kazmi";

    ChessBoard cb1;
    cb1.display();

    if (cb1.movePiece("b8", "a6")) {
        cout << "\nPiece moved.";
        cb1.display();
    }
    else {
        cout << "\nInvalid move.";
    }

    if (cb1.movePiece("b8", "d7")) {
        cout << "\nPiece moved.";
        cb1.display();
    }
    else {
        cout << "\nInvalid move.";
    }
}