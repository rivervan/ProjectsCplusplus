#include <iostream>


#include "SDL.h"

int main() {
   
   
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};

  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};

  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
   


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
                                  SDL_WINDOWPOS_CENTERED, kScreenWidth, kScreenHeight, SDL_WINDOW_SHOWN);

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
  bool running = true;

  int Xini = -40;
  int Yini = 320;
 

  while (running) {
    frame_start = SDL_GetTicks();

    
     
  SDL_Rect alaArr;
  SDL_Rect alaAbj;
  SDL_Rect cabDel;
  SDL_Rect cabCtr;
  SDL_Rect cabAtr;
  SDL_Rect cabCola;

  cabCtr.w = kScreenWidth / kGridWidth;
  cabCtr.h = kScreenWidth / kGridWidth;

  alaArr.w = cabCtr.w;
  alaArr.h = cabCtr.h;

  cabCola.w = cabCtr.w;
  cabCola.h = cabCtr.h;
  
  cabDel.w = cabCtr.w;
  cabDel.h = cabCtr.h;
   
  cabAtr.w = cabCtr.w;
  cabAtr.h = cabCtr.h;

  alaAbj.w = cabCtr.w;
  alaAbj.h = cabCtr.h;


  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
   
   
  SDL_SetRenderDrawColor(sdl_renderer, 0x77, 0xCC, 0x00, 0xFF);
  cabCtr.x = Xini++;
  cabCtr.y = Yini;

  cabAtr.x = cabCtr.x-20;
  cabAtr.y = cabCtr.y;

  cabCola.x = cabAtr.x - 20;
  cabCola.y = cabAtr.y;


  cabDel.x = cabCtr.x + 20;
  cabDel.y = cabCtr.y;
  
  SDL_RenderDrawLine(sdl_renderer, cabCtr.x , cabCtr.y,  cabCtr.x + 10, cabCtr.y - 40);
  SDL_RenderDrawLine(sdl_renderer, cabCtr.x + 20, cabCtr.y,  cabCtr.x + 10 , cabCtr.y - 40);


  SDL_RenderDrawLine(sdl_renderer, cabCtr.x , cabCtr.y + 20,  cabCtr.x + 10, cabCtr.y + 60);
  SDL_RenderDrawLine(sdl_renderer, cabCtr.x + 20, cabCtr.y + 20,  cabCtr.x + 10 , cabCtr.y + 60);

  SDL_RenderDrawLine(sdl_renderer, cabCola.x , cabCola.y,  cabCola.x, cabCola.y - 20);
  SDL_RenderDrawLine(sdl_renderer, cabCola.x + 20 , cabCola.y,  cabCola.x , cabCola.y - 20);

  SDL_RenderDrawLine(sdl_renderer, cabDel.x + 20 , cabDel.y,  cabDel.x + 30, cabDel.y +  10);
  SDL_RenderDrawLine(sdl_renderer, cabDel.x + 20 , cabDel.y + 20,  cabDel.x + 30 , cabDel.y + 10);


  SDL_RenderFillRect(sdl_renderer, &cabCtr);
  SDL_RenderFillRect(sdl_renderer, &cabAtr);
  SDL_RenderFillRect(sdl_renderer, &cabDel);
  SDL_RenderFillRect(sdl_renderer, &cabCola);

  SDL_RenderPresent(sdl_renderer);

  SDL_SetWindowTitle(sdl_window, "Mi juego"); 


    frame_end = SDL_GetTicks();



    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    /*
    if (frame_end - title_timestamp >= 1000) {      
      frame_count = 0;
      title_timestamp = frame_end;
    }*/
    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < kMsPerFrame) {
      SDL_Delay(kMsPerFrame - frame_duration);
    }

    if(Xini == (kScreenWidth + 40))
      break;


  }











   
    // SDL_Delay(7000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(sdl_window);

    // Clean up
    SDL_Quit();

    std::cout<<"FIN DEL PROGRAMA" << std::endl;
     
     return 0;

}