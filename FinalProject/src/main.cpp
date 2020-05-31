
#include <iostream>
#include <cmath>
#include <memory>

#include "SDL.h"
#include "sut.h"

#include "airpath.h"





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

    //SDL_Point *pathFly = getPointsPathFly();


     //Create Path arrive
     AirPath arrivePath(-4,12);


     //Create Path veer
     PointCartesian centerSemi(0,-2);
     AirPath veerPath(centerSemi, 4,2,0);

     //Create Path Wait
     PointCartesian centerWhole(0,2);
     AirPath waitPath(centerWhole, 4,2,0, true);


      //Create Path Track Rigth
     PointCartesian centerTR(0,0);
     AirPath TRPath(centerTR,-2, 12);


     //Create Path Track Left
     PointCartesian centerTL(0,0);
     AirPath TLPath(centerTL, 2, 12);


     //Create Path Track left
     //PointCartesian centerWhole(0,2);
     //AirPath waitPath(centerWhole, 4,2,0, true);


      
      
      std::cout<< "UseCount arrivePath: " << arrivePath.getPoints().use_count() << std::endl;       
      std::cout<< "UseCount veerPath  : " << veerPath.getPoints().use_count() << std::endl;       
      std::cout<< "UseCount waitPath  : " << waitPath.getPoints().use_count() << std::endl;       
      std::cout<< "UseCount TRPath    : " << TRPath.getPoints().use_count() << std::endl;       
      std::cout<< "UseCount TLPath    : " << TLPath.getPoints().use_count() << std::endl;       
      /*
      for(auto i = 0; i < (TRPath.getLenPath() * Sut::sScale); i++){
         std::cout << TRPath.getPoints().get()[i].x  <<", "<< TRPath.getPoints().get()[i].y<< std::endl;
      }
      */
     


    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);


    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xe6, 0xe6, SDL_ALPHA_OPAQUE); 
    SDL_RenderDrawLine(sdl_renderer,Sut::OriginAxisX,0, Sut::OriginAxisX, Sut::kScreenHeight);
    SDL_RenderDrawLine(sdl_renderer, 0,Sut::OriginAxisY,Sut::kScreenWidth,Sut::OriginAxisY);

    
    
    //std::cout<< arrivePath.getPoints().use_count()  << std::endl;
    
    

  
    SDL_RenderDrawPoints(sdl_renderer,arrivePath.getPoints().get(),arrivePath.getLenPath()*Sut::sScale );
    SDL_RenderDrawPoints(sdl_renderer,veerPath.getPoints().get(),veerPath.getLenPath()*Sut::sScale );
    SDL_RenderDrawPoints(sdl_renderer,waitPath.getPoints().get(),waitPath.getLenPath()*Sut::sScale );
    SDL_RenderDrawPoints(sdl_renderer,TRPath.getPoints().get(),TRPath.getLenPath()*Sut::sScale );
    SDL_RenderDrawPoints(sdl_renderer,TLPath.getPoints().get(),TLPath.getLenPath()*Sut::sScale );
    

  //*****************************FIN*************************************



  SDL_RenderPresent(sdl_renderer);
  SDL_SetWindowTitle(sdl_window, "Air Controller"); 
  frame_end = SDL_GetTicks();


   
    frame_count++;
    frame_duration = frame_end - frame_start;
    
   
    if (frame_duration < Sut::kMsPerFrame) {
      SDL_Delay(Sut::kMsPerFrame - frame_duration);
    }
    
   
   
    
    SDL_Delay(7000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(sdl_window);

    // Clean up
    SDL_Quit();

    std::cout<<"FIN DEL PROGRAMA" << std::endl;
     
     return 0;


 




}