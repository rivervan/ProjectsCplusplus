#include<iostream>
#include "airplane.h"
#include "SDL.h"



////////////POSITION DEFINITION//////////////////

Position::Position(std::shared_ptr<AirPath> newPath, AirPath::_IndexPointOnPath indexPointOnPath){
          _currentPath   = newPath;       
     _currentIndexPoint  = indexPointOnPath;
        
}


  //Move operator
Position& Position::operator=(Position &&src){      

    if(this == &src)
       return *this;
                  
    _currentPath       = src._currentPath;
    _currentIndexPoint = src._currentIndexPoint; 
    src._currentPath   = nullptr;                     
    return *this;

  }   


/*_______________________________________________*/

////////////AIRPLANE DEFINITION//////////////////

AirPlane::AirPlane(Position &&position, _SizeAirPlane sizeAirPlane){
    _position = std::move(position);
    _cabCtr.w = sizeAirPlane;
    _cabCtr.h = sizeAirPlane;


    //Place to airplain on start point of path
    SDL_Point currentPoint = _position._currentPath->getPoints().get()[_position._currentIndexPoint];

     

    if (_position._currentIndexPoint >= _position._currentPath->getIndexStartPoint() && _position._currentIndexPoint < _position._currentPath->getIndexEndPoint())
        _isPathFinish = false;
    else
        _isPathFinish = true;
        

    drawAirPlane(currentPoint);
    
}





void AirPlane::simulate(){



       _position._currentIndexPoint++;
       SDL_Point pointOfFly = _position._currentPath->getPoints().get()[_position._currentIndexPoint];           



       drawAirPlane(pointOfFly);


       if( _position._currentIndexPoint >= _position._currentPath->getIndexEndPoint() ){
            _isPathFinish = true;            
       }
         

   }
    





void AirPlane::drawAirPlane(const SDL_Point &currentPoint){

      _cabCtr.x = currentPoint.x - _cabCtr.w/2; 
      _cabCtr.y = currentPoint.y - _cabCtr.h/2;
      

      _wingTop[0].x = _cabCtr.x + _cabCtr.w/4;
      _wingTop[0].y = _cabCtr.y;
      
      _wingTop[1].x = _cabCtr.x + _cabCtr.w/2;
      _wingTop[1].y = _cabCtr.y - 3*_cabCtr.w/4 ;
      
      _wingTop[2].x = _cabCtr.x + 3*_cabCtr.w/4;
      _wingTop[2].y = _cabCtr.y;
      

      _wingBottom[0].x = _cabCtr.x + _cabCtr.w/4;
      _wingBottom[0].y = _cabCtr.y + _cabCtr.h;
      
      _wingBottom[1].x = _cabCtr.x + _cabCtr.w/2;
      _wingBottom[1].y = _cabCtr.y + _cabCtr.h +  3*_cabCtr.h/4;
      
      _wingBottom[2].x = _cabCtr.x + 3*_cabCtr.w/4;
      _wingBottom[2].y = _cabCtr.y + _cabCtr.h;


}


void AirPlane::RenderAirplane(SDL_Renderer *sdl_renderer){  
     
      
      SDL_RenderDrawLine(sdl_renderer, _cabCtr.x, _cabCtr.y ,  _cabCtr.x +  _cabCtr.w/2, _cabCtr.y +  _cabCtr.h/2);
      SDL_RenderFillRect(sdl_renderer, &_cabCtr);
      SDL_RenderDrawLines(sdl_renderer, _wingTop, 3);
      SDL_RenderDrawLines(sdl_renderer, _wingBottom, 3);    
}


/*_______________________________________________*/