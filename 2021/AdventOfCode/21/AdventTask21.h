//
//  AdventTask21.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 21.12.21.
//

#ifndef AdventTask21_h
#define AdventTask21_h

struct Game {
    Game() {}
    Game(int start1, int start2, int score1, int score2, bool player1Turn) : start1(start1), start2(start2), player1Turn(player1Turn), diceRolls({}), score1(score1), score2(score2), number(1), finished(0) {}

    int start1;
    int start2;
    int score1;
    int score2;
    bool player1Turn;
    std::vector<int> diceRolls;
    int64_t number;

    int finished;

    std::string key() {
        std::stringstream ss;
        ss << start1 << "-" << start2 << "-" << score1 << "-" << score2 << "-" << player1Turn << "-" << diceRolls.size();

        int s = std::accumulate(diceRolls.begin(), diceRolls.end(), 0);

        ss << "-" << s;
        return ss.str();
    }
};

class AdventTask21 : public AdventTask<21> {
  protected:
    virtual void solveSilver(std::ifstream &file) {

        std::string input;
        file >> input; file >> input; file >> input; file >> input; file >> input;
        auto start1 = std::stoi(input);

        file >> input; file >> input; file >> input; file >> input; file >> input;
        auto start2 = std::stoi(input);

        bool player1Turn = true;
        int diceRolls = 3;
        int dice = 0;

        int score1 = 0;
        int score2 = 0;

        int rolls = 0;

        while(score1 < 1000 && score2 < 1000) {
            int sum = 0;
            for(int i=0; i<diceRolls; ++i) {
                dice = next(dice, 100);
                rolls++;
                sum += (dice % 10);
            }

            if (player1Turn) {
                start1 += sum;
                start1 = start1 % 10;
                score1 += (start1 == 0) ? 10 : start1;
            } else {
                start2 += sum;
                start2 = start2 % 10;
                score2 += (start2 == 0) ? 10 : start2;
            }

            player1Turn = !player1Turn;
            std::cout << score1 << " " << score2 << std::endl;
        }

        std::cout << score1 << " " << score2 << " => " << std::min(score1,score2)*rolls;
    }

    virtual void solveGold(std::ifstream &file) {
        std::string input;
        file >> input; file >> input; file >> input; file >> input; file >> input;
        auto start1 = std::stoi(input);

        file >> input; file >> input; file >> input; file >> input; file >> input;
        auto start2 = std::stoi(input);

        std::cout << start(start1, start2);
    }

    int64_t start(int start1, int start2) {
        std::map<std::string, Game> games;

        int64_t player1Wins = 0;
        int64_t player2Wins = 0;

        auto g = Game(start1, start2, 0, 0, true);
        games[g.key()] = g;

        while(true) {
            auto minScore = 22;
            std::string key = "";

            for(auto it=games.begin(); it!=games.end(); ++it) {
                auto &g = it->second;

                auto score = g.player1Turn ? g.score1 : g.score2;

                if(score < minScore) {
                    minScore = score;
                    key = g.key();
                }
            }

            if(key == "") {
                break;
            }

            auto it = games.find(key);
            Game g = it->second;
            games.erase(it);
            play(g, games, player1Wins, player2Wins);
        }

        return std::max(player1Wins, player2Wins);
    }

    void play(Game &game, std::map<std::string, Game> &games, int64_t &player1, int64_t& player2) {
        if(game.diceRolls.size() < 3) {
            for(int i=0; i<3; ++i) {
                Game g = game;
                g.diceRolls.push_back(i+1);

                if(games.count(g.key())) {
                    games[g.key()].number += g.number;
                } else {
                    games[g.key()] = g;
                }
            }

            return;
        }

        int sum = 0;
        for(int i=0; i<3; ++i) {
            sum += (game.diceRolls[i] % 10);
        }

        game.diceRolls.clear();

        if (game.player1Turn) {
            game.start1 += sum;
            game.start1 = game.start1 % 10;
            game.score1 += (game.start1 == 0) ? 10 : game.start1;
        } else {
            game.start2 += sum;
            game.start2 = game.start2 % 10;
            game.score2 += (game.start2 == 0) ? 10 : game.start2;
        }

        game.player1Turn = !game.player1Turn;

        if(game.score1 >= 21) {
            player1 += game.number;
        } else if(game.score2 >= 21) {
            player2 += game.number;
        } else {
            if(games.count(game.key())) {
                games[game.key()].number += game.number;
            } else {
                games[game.key()] = game;
            }
        }
    }

    int next(int i, int max) {
        return i == max ? 1 : (i+1);
    }
};

#endif /* AdventTask21_h */
