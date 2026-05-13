#include "game.h"
#include<vector>
void GameBoard:: placeWall(Position pos, bool isHorizontal){
    if(current_turn==1&&p1.walls_left<=0||current_turn==2&&p2.walls_left<=0)return;
    if(!is_valid_wall_placement())return;
wall wall;
wall.pos=pos;
wall.isHorizontal=isHorizontal;
walls.push_back(wall);
}