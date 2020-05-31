#ifndef SUT_H_
#define SUT_H_

#include <iostream>
#include <cmath>
#include "SDL.h"






struct PointCartesian
{
  PointCartesian(int px, int py): x(px),y(py){}

  int x;
  int y;
};


class Sut{


   public: 
      
     static float constexpr  PI = 3.1415926;
     static int constexpr  sScale = 48;  //32
     
    static constexpr std::size_t kFramesPerSecond{60};
    static constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
   
    static constexpr std::size_t kScreenWidth{1152};     //768
    static constexpr std::size_t kScreenHeight{1024};    //768
   
    static constexpr std::size_t OriginAxisX{384};       //256
    static constexpr std::size_t OriginAxisY{512};       //512
  
     static SDL_Point  getTraslatePointScreen(int x, int y, int xso, int yso);
     

  private:

      
    
};




#endif 