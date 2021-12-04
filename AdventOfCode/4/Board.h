//
//  Board.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 04.12.21.
//

#ifndef Board_h
#define Board_h

struct Entry {
    int number = 0;
    bool isSet = false;
};

template <int N>
class Board {
  public:
    Board(std::ifstream &file) {
        for(int i=0; i<N; ++i) {
            for(int j=0; j<N; ++j) {
                file >> board[i][j].number;
            }
        }

        file >> std::ws;
    }

    void select(int number) {
        for(int i=0; i<N; ++i) {
            for(int j=0; j<N; ++j) {
                if(board[i][j].number == number) {
                    board[i][j].isSet = true;
                }
            }
        }

        checkWon();
    }

    bool hasWon() {
        return hasLine;
    }

    int result(int number) {
        int sum = 0;
        for(int i=0; i<N; ++i) {
            for(int j=0; j<N; ++j) {
                if(!board[i][j].isSet) {
                    sum += board[i][j].number;
                }
            }
        }

        return sum * number;
    }

  private:
    void checkWon() {
        for(int i=0; i<N; ++i) {
            bool rowAllSet = true;
            bool colAllSet = true;
            for(int j=0; j<N; ++j) {
                rowAllSet &= board[i][j].isSet;
                colAllSet &= board[j][i].isSet;
            }

            if(rowAllSet || colAllSet) {
                hasLine = true;
                return;
            }
        }
    }

  private:
    Entry board[5][5];
    bool hasLine = false;
};


#endif /* Board_h */
