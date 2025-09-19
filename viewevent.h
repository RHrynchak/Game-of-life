#pragma once

enum class ViewAction{
    CELL_SIZE_DECREASE,
    CELL_SIZE_INCREASE,
    CAMERA_MOVE,
    WINDOW_SIZE_CHANGE
};

struct ViewEvent{
    ViewAction action;
    int velX = 0, velY = 0; //for CAMERA_MOVE
    int mouseX = -1, mouseY = -1; //mouse position for zoom
};