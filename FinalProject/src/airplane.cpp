#include<iostream>
#include "airplane.h"
#include "SDL.h"



////////////POSITION DEFINITION//////////////////

Position::Position( std::map<TypePath, std::shared_ptr<AirPath>>  &paths, TypePath typePath, AirPath::_IndexPointOnPath indexPointOnPath){
                _paths   = paths;  //spetial review learning           
          _currentPath   = _paths[typePath];                            
     _currentIndexPoint  = indexPointOnPath;                     
}


  //Move operator
Position& Position::operator=(Position &&src){      

    if(this == &src)
       return *this;
                  
    _currentPath       = src._currentPath;
    _currentIndexPoint = src._currentIndexPoint;    
                _paths = src._paths; 
    src._currentPath   = nullptr;    
    

    return *this;

  }   


/*_______________________________________________*/

////////////AIRPLANE DEFINITION//////////////////

AirPlane::AirPlane(Position &&position, _SizeAirPlane sizeAirPlane, int speedFactor){
    _position = std::move(position);     
    _cabCtr.w = sizeAirPlane;
    _cabCtr.h = sizeAirPlane;

    _speedFactor = speedFactor;

     _isEndTrip = false;

    //Place to airplain on start point of path
    SDL_Point currentPoint = _position._currentPath->getPoints().get()[_position._currentIndexPoint];

     

    if (_position._currentIndexPoint >= _position._currentPath->getIndexStartPoint() && _position._currentIndexPoint < _position._currentPath->getIndexEndPoint())
        _isPathFinish = false;
    else
        _isPathFinish = true;
        

    drawAirPlane(currentPoint);
    
}





void AirPlane::simulate(){
    
     
    

    //1. Verify if the airplane arrived to end 
        if( (_position._currentIndexPoint + _speedFactor) >= _position._currentPath->getIndexEndPoint() )
        {            
            _position._currentIndexPoint = _position._currentPath->getIndexEndPoint();            
            _isPathFinish = true;    

        }
        else{
            //Move 
             
             switch (_position._currentPath->getTypePath())
             {
             case TypePath::OnTrackLeft:
             case TypePath::OnTrackCenter :
             case TypePath::OnTrackRight :

                  if(_position._currentIndexPoint > 2*(_position._currentPath->getIndexEndPoint()) / 3)
                     
                 _speedFactor = 1; 
                 break;             
             default:                
                 break;
             }
             
            _position._currentIndexPoint+=_speedFactor; 
                           
            //Get current point on current path
            SDL_Point pointOfFly = _position._currentPath->getPoints().get()[_position._currentIndexPoint];            
            //Draw airplane on path 
            drawAirPlane(pointOfFly);            

        }
        
       

       if (_isEndTrip == true){                               
           return; 
       }

        
       
     // std::cout<<"endPOINT: " << _position._currentPath->getIndexEndPoint() << "," << _position._currentIndexPoint;            
    //2. Change path      
    if(_isPathFinish == true){
         
        auto opt = _position._currentPath->getTypePath();
       
        switch(opt){
          
            case TypePath::LineArriving:                                             
               _position._currentPath =  _position._paths[TypePath::CycleVeer] ;               
               _position._currentIndexPoint = _position._currentPath->getIndexStartPoint();
               _isPathFinish = false;
               _isEndTrip = false;                 
               break;
            case TypePath::CycleVeer:
            case TypePath::CycleWait:                          
                switch (Sut::getFollowWay())                
                {
                    case Sut::TypeDecision::Wait:                    
                        _position._currentPath = _position._paths[TypePath::CycleWait];                        
                        _isEndTrip = false;                        
                        break;                
                    case Sut::TypeDecision::Rail1:                    
                        _position._currentPath =  _position._paths[TypePath::OnTrackLeft];                                                
                        _isEndTrip = false;                        
                        break;                
                    case Sut::TypeDecision::Rail2:                    
                        _position._currentPath =  _position._paths[TypePath::OnTrackCenter];                        
                        _isEndTrip = false;                        
                        break;                
                    case Sut::TypeDecision::Rail3:                    
                        _position._currentPath =  _position._paths[TypePath::OnTrackRight];                        
                        _isEndTrip = false;                        
                        break;                
                }
                _isPathFinish = false;
                _position._currentIndexPoint = 0;
                break;         

            case TypePath::OnTrackLeft:                     
            case TypePath::OnTrackCenter:              
            case TypePath::OnTrackRight:                                  
                _position._currentPath =  nullptr;                         
                _isPathFinish = true;
                _isEndTrip = true;
                                
            //case TypePath::LineRail:
            break;         
        }   

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