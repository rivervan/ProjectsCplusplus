#include "SDL.h"
#include "sut.h"






 SDL_Point Sut::getTraslatePointScreen(int x, int y, int xso, int yso){
     SDL_Point screenXY;     
     screenXY.x = xso + x;
     screenXY.y = yso + y*(-1);     
     return screenXY;
}


