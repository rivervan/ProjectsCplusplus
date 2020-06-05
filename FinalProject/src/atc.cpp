#include<vector>
#include<iostream>

#include "atc.h"



void Atc::recivePlaneAirApaceIN(bool &running,  std::map<TypePath, std::shared_ptr<AirPath>>  &paths, std::vector< std::shared_ptr<AirPlane>> &planes )const
{

  SDL_Event e;
  while (SDL_PollEvent(&e)) 
  {
    if (e.type == SDL_KEYDOWN && e.key.keysym.sym== SDLK_RIGHT) {
      running = false;
      

    } 
    else {
       if (e.type == SDL_KEYDOWN && e.key.keysym.sym== SDLK_LEFT) {
            //Creadte && Add new airPath 
 
            Position position (paths, TypePath::LineArriving, 0);            
            planes.emplace_back(std::make_shared<AirPlane>(std::move(position),24,3) );
             
          
      }
    }
  }






}