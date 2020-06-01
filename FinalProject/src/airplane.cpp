#include<iostream>
#include "airplane.h"
#include "SDL.h"


Position::Position(std::shared_ptr<AirPath> newPath, SDL_Point newPoint){
     _currentPath  = newPath; 
     _currentPoint = newPoint;
    
}


 void Position::MoveCurrentPointToNewPointOnPath(SDL_Point newPoint){
     _currentPoint = newPoint;
 }

  
  Position& Position::operator=(Position &&src){ //Move operator
        
        
         if(this == &src)
            return *this;
                       
            _currentPath  = src._currentPath;
            _currentPoint = src._currentPoint; 
            src._currentPath = nullptr;
                     
         return *this;
  }   




       
        

AirPlane::AirPlane(Position &&position){
    _position = std::move(position);
    _cabCtr.w = 24;
    _cabCtr.h = 24;


    if(_position._currentPath->getTypePath() ==  TypePath::LineArriving){                 
         _distance = _position._currentPath->getLenPath() * Sut::sScale  - 1;
         _cabCtr.x = _position._currentPoint.x - 12; 
         _cabCtr.y = _position._currentPoint.y - 12;
    }

}


void AirPlane::simulate(){

}


void AirPlane::fly(SDL_Renderer *sdl_renderer){

      _cabCtr.x = _position._currentPoint.x - 12; 
      _cabCtr.y = _position._currentPoint.y - 12;
      
      _wingBottom[0].x = _cabCtr.x + 6;
      _wingBottom[0].y = _cabCtr.y;
      
      _wingBottom[1].x = _cabCtr.x + 12;
      _wingBottom[1].y = _cabCtr.y - 16;
      
      _wingBottom[2].x = _cabCtr.x + 18;
      _wingBottom[2].y = _cabCtr.y;
      
      
      _wingTop[0].x = _cabCtr.x + 6;
      _wingTop[0].y = _cabCtr.y + _cabCtr.h;
      
      _wingTop[1].x = _cabCtr.x + 12;
      _wingTop[1].y = _cabCtr.y + _cabCtr.h + 16;
      
      _wingTop[2].x = _cabCtr.x + 18;
      _wingTop[2].y = _cabCtr.y + _cabCtr.h;



      

      SDL_RenderDrawLine(sdl_renderer, _cabCtr.x, _cabCtr.y ,  _cabCtr.x + 12, _cabCtr.y + 12);
      SDL_RenderFillRect(sdl_renderer, &_cabCtr);
      SDL_RenderDrawLines(sdl_renderer, _wingTop, 3);
      SDL_RenderDrawLines(sdl_renderer, _wingBottom, 3);

      

      _position._currenIndexPoint += 1;

      if(_position._currenIndexPoint <= _position._currentPath->getLenPath() * Sut::sScale - 1 )
          _position._currentPoint = _position._currentPath->getPoints().get()[_position._currenIndexPoint];  

          
      _distance -= 1;

}