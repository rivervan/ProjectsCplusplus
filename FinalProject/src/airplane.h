

#include <vector>
#include <memory>

#include "airpath.h"

#include "SDL.h"

//#include "sut.h"





class Position
{

    public:        
        
         Position()=default;
         Position(std::shared_ptr<AirPath> newPath, SDL_Point newPoint);
         Position &operator=( Position &&src);

        
         
         void MoveCurrentPointToNewPointOnPath(SDL_Point newPoint);

         std::shared_ptr<AirPath> _currentPath;
         SDL_Point _currentPoint;    
         int _currenIndexPoint{0};
         

};
 




class AirPlane{

  public:

        AirPlane()=default;
        AirPlane(Position &&position);
       
        void fly(SDL_Renderer *sdl_renderer);
        void simulate();
        int getDistance()const{return _distance;};
        
         
    
  
   private:

      Position _position;

      SDL_Rect _cabCtr;
      SDL_Point _wingBottom[3];
      SDL_Point _wingTop[3];
      int _distance{0};
      




};





