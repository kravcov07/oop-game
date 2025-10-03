#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include <vector>

#include "Cell.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

class GameField{
public:
    GameField(int width, int height);
    

private:
    int width_;
    int height_;
    Cell** cells_;
    Player* player_;
    std::vector<Enemy*> enemies_;
};

#endif