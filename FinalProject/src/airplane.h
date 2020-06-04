

#include <vector>
#include <memory>

#include "airpath.h"
#include <map>

#include "SDL.h"

//#include "sut.h"





class Position
{

 

    public:        
        
         Position()=default;
         Position(std::map<TypePath, std::shared_ptr<AirPath>> &paths, TypePath typePath, AirPath::_IndexPointOnPath indexPointOnPath);
         Position &operator=( Position &&src);         
        
         

         friend class AirPlane;

                  
     private: 
         
        //std::map<TypePath, std::shared_ptr<AirPath>>  _paths; 
        std::map<TypePath, std::shared_ptr<AirPath>>  _paths; 

         std::shared_ptr<AirPath> _currentPath;                       
         AirPath::_IndexPointOnPath _currentIndexPoint{0};
         
         
                    
};
 




class AirPlane{



  public:
        typedef int _SizeAirPlane;

        AirPlane()=default;
        AirPlane(Position &&position, _SizeAirPlane sizeAirPlane = 24, int speedFactor=1);
               

        bool getIsPathFinish()const{return _isPathFinish;};
        bool getIsEndTrip()const{return _isEndTrip;};


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
      bool _isEndTrip;



      //Help functions
      void drawAirPlane(const SDL_Point &currentPoint);



};





