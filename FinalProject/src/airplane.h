

#include <vector>
#include <memory>

#include "airpath.h"

#include "SDL.h"

//#include "sut.h"





class Position
{

 

    public:        
        
         Position()=default;
         Position(std::shared_ptr<AirPath> newPath, AirPath::_IndexPointOnPath indexPointOnPath);
         Position &operator=( Position &&src);         
        
         
         friend class AirPlane;

                  
     private: 

         std::shared_ptr<AirPath> _currentPath;                       
         AirPath::_IndexPointOnPath _currentIndexPoint{0};
                    
};
 




class AirPlane{



  public:
        typedef int _SizeAirPlane;

        AirPlane()=default;
        AirPlane(Position &&position, _SizeAirPlane sizeAirPlane = 24, int speedFactor=1);
               

        bool getIsPathFinish()const{return _isPathFinish;};


        void RenderAirplane(SDL_Renderer *sdl_renderer);
        void simulate();
                        
  
   private:
  
      Position _position;
    
      //Shape of plane
      SDL_Rect _cabCtr;
      SDL_Point _wingBottom[3];
      SDL_Point _wingTop[3];


      //Members of control
      bool _isPathFinish{false};
      int _speedFactor;



      //Help functions
      void drawAirPlane(const SDL_Point &currentPoint);



};





