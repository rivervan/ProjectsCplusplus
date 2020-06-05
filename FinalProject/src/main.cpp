
#include <iostream>
#include <cmath>
#include <memory>
#include <map>
#include <vector>

#include "SDL.h"
#include "sut.h"

#include "atc.h"
//#include "airplane.h"




int main() {


  

  SDL_Renderer *sdl_renderer;
  SDL_Window *sdl_window;


  //****************************************************
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      std::cerr << "SDL could not initialize.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create Window
    sdl_window = SDL_CreateWindow("Mi Game", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, Sut::kScreenWidth, Sut::kScreenHeight, SDL_WINDOW_SHOWN);

    if (nullptr == sdl_window) {
      std::cerr << "Window could not be created.\n";
      std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
    }

    // Create renderer
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if (nullptr == sdl_renderer) {
      std::cerr << "Renderer could not be created.\n";
      std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
    }

 //****************************************************




  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  


   //********************RENDERIZADO*************************************

    std::map<TypePath, std::shared_ptr<AirPath>> pathsAirs;   
    std::vector<std::shared_ptr<AirPlane>> planes;




    //Create PATHS
               
     //Create Path arrive
     pathsAirs[TypePath::LineArriving] = std::make_shared<AirPath>(12,-4,12,Sense::Left);
                   
     //Create Path veer
     PointCartesian centerSemi(0,-2);
     pathsAirs[TypePath::CycleVeer]    = std::make_shared<AirPath>(centerSemi, 4,2,0);
          
     //Create Path Wait
     PointCartesian centerWhole(0,2);
     pathsAirs[TypePath::CycleWait]    = std::make_shared<AirPath>(centerWhole, 4,2,0, true);
     
      //Create Path Track Rigth
     PointCartesian centerTR(0,0);
     pathsAirs[TypePath::OnTrackRight] = std::make_shared<AirPath>(centerTR,-2, 12);
          
     //Create Path Track Left
     PointCartesian centerTL(0,0);
     pathsAirs[TypePath::OnTrackLeft]  = std::make_shared<AirPath>(centerTL, 2, 12);
     
     //Create Path Track Center          
     pathsAirs[TypePath::OnTrackCenter] =  std::make_shared<AirPath>(12,0,0, Sense::Right);
     
     
     


Atc atc; 
bool running = true;


while (running) {
    frame_start = SDL_GetTicks();



     atc.recivePlaneAirApaceIN(running, pathsAirs,planes);
     
     
    

    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);


    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xe6, 0xe6, SDL_ALPHA_OPAQUE); 
    SDL_RenderDrawLine(sdl_renderer,Sut::OriginAxisX,0, Sut::OriginAxisX, Sut::kScreenHeight);
    SDL_RenderDrawLine(sdl_renderer, 0,Sut::OriginAxisY,Sut::kScreenWidth,Sut::OriginAxisY);

      
    

    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0xcc, 0xcc, SDL_ALPHA_OPAQUE);   


                                       
                                       
    SDL_RenderDrawPoints(sdl_renderer, pathsAirs[TypePath::LineArriving]->getPoints().get(),       pathsAirs[TypePath::LineArriving]->getLenPath()*Sut::sScale );
    SDL_RenderDrawPoints(sdl_renderer, pathsAirs[TypePath::CycleVeer]->getPoints().get(),          pathsAirs[TypePath::CycleVeer]->getLenPath()*Sut::sScale );
    SDL_RenderDrawPoints(sdl_renderer, pathsAirs[TypePath::CycleWait]->getPoints().get(),          pathsAirs[TypePath::CycleWait]->getLenPath()*Sut::sScale );
    SDL_RenderDrawPoints(sdl_renderer, pathsAirs[TypePath::OnTrackRight]->getPoints().get(),       pathsAirs[TypePath::OnTrackRight]->getLenPath()*Sut::sScale );
    SDL_RenderDrawPoints(sdl_renderer, pathsAirs[TypePath::OnTrackLeft]->getPoints().get(),        pathsAirs[TypePath::OnTrackLeft]->getLenPath()*Sut::sScale );        
    SDL_RenderDrawPoints(sdl_renderer, pathsAirs[TypePath::OnTrackCenter]->getPoints().get(),      pathsAirs[TypePath::OnTrackCenter]->getLenPath()*Sut::sScale);
    
     //FLYING AIRPLANE

     SDL_SetRenderDrawColor(sdl_renderer, 0xff, 0xff, 0x00, SDL_ALPHA_OPAQUE);


     auto it = planes.begin();
     while(it!=planes.end()){
        
         if( (*it)->getIsEndTrip()){
              planes.erase(it);
              if(planes.size() <= 0 ){
                running = false;
                break;
              }
              
         }else
         {
            (*it)->simulate();
            (*it)->RenderAirplane(sdl_renderer);
         }
         it++;
    
     }


  

     //myPlane.simulate();
   

     //myPlane.RenderAirplane(sdl_renderer);



  //*****************************FIN*************************************



  SDL_RenderPresent(sdl_renderer);
  SDL_SetWindowTitle(sdl_window, "Air Controller"); 
  frame_end = SDL_GetTicks();


   
    frame_count++;
    frame_duration = frame_end - frame_start;
    
   
    if (frame_duration < Sut::kMsPerFrame) {
      SDL_Delay(Sut::kMsPerFrame - frame_duration);
    }
    
   
     /*
    if (myPlane.getIsEndTrip())
         break;
    */

 }


    
    SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(sdl_window);

    // Clean up
    SDL_Quit();

    std::cout<<"FIN DEL PROGRAMA" << std::endl;
     
     return 0;


 




}