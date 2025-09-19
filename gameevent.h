#pragma once
#include "cell.h"

enum class GameAction{
    SPEED_UP,
    SPEED_DOWN,
    PAUSE,
    CLEAR,
    TOGGLE_CELL
};

struct GameEvent{
    GameAction action;
    Cell cell {-1, -1}; //for TOGGLE_CELL
};