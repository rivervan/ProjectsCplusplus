

#include<algorithm>
#include<numeric>

#include "atc.h"



 void Atc::recivePlaneAirSpaceIN(Position &&position){     
      std::lock_guard<std::mutex> uLock(_mutex);                             
      _planes.emplace_back(AirPlane(std::move(position), 24,3));              
 }

 

void Atc::workerDetectedCrash(int idx){
     
     for(auto i = idx+1; i < _planes.size(); i++){

        if(! _planes[idx].getIsEndTrip() && !_planes[i].getIsEndTrip() && !_planes[i].getIsCrashed() && !_planes[idx].getIsCrashed() ){


          float x = _planes[idx].getCurrentPointS().x - _planes[i].getCurrentPointS().x;
          float y = _planes[idx].getCurrentPointS().y - _planes[i].getCurrentPointS().y;                    
          float d = sqrt(x*x + y*y);
                   
           if( d <= _planes[idx].getSizePlane()){
            std::lock_guard<std::mutex> uLock(_mutex);
                   _planes[idx].setCrashed();
                   _planes[i].setCrashed();                                              
           }
        }

     }   

     
    
  }


  void Atc::doEnablePlains(){

    std::for_each(_planes.begin(), _planes.end(), [](AirPlane &plane){
             if(plane.getIsCrashed())
                plane.setIsEnable(false);
       });

  }





 void Atc::fly(SDL_Renderer *sdl_renderer){
      std::lock_guard<std::mutex> uLock(_mutex);                      
            
            std::for_each(_planes.begin(), _planes.end(), [sdl_renderer](AirPlane &plane){
                plane.simulate();                                                   
                plane.RenderAirplane(sdl_renderer);
            });


           
 }


 int Atc::takeoffPlaneOUT(){

       std::unique_lock<std::mutex> uLock(_mutex);      
        int countTakeOff = 0;          

         
        for (auto it = _planes.begin(); it != _planes.end(); ) {
             
            if ((*it).getIsEndTrip()  ) {                            
                it = _planes.erase(it);             
                countTakeOff++;
            } else {
                ++it;
            }

        }

        return countTakeOff; 

 }