#include <iostream>
#include <cmath>


#include "SDL.h"

#define PI 3.141592653589793238462



struct PointCartesian
{
  int x;
  int y;
};



SDL_Point  getTraslatePointScreen(int x, int y, int xso, int yso){
     SDL_Point screenXY;     
     screenXY.x = xso + x;
     screenXY.y = yso + y*(-1);     
     return screenXY;
} 


PointCartesian getTraslatePointCartesian (int xs, int ys, int xso, int yso){
   PointCartesian pc; 
   pc.x = xs-xso;
   pc.y = (-1) * (ys - yso) ;

   return pc;
}



SDL_Point *getPointsSin(){        
  static SDL_Point arr[2048];
  
   
   int xt = 0;
   int yt = 0;
   
   for(auto x = 0; x < 2048; x++){       
      int y = sin(x*PI/180) * 128;       
        arr[x] = getTraslatePointScreen(x,y,0,1364); 
    
   }    
    return arr;
}




SDL_Point *getPointsPathA(){        
  static SDL_Point arrElipse[1024];
  


  
   
   int cx = 0;
   int cy = 2;
   int Ax = 4;
   int By = 2;
   
  float x = 0; 
  float y = 0;

   
    for(auto i = 0; i < 256 ; i++){
       
       float  yPartial = sqrt((By*By) - ( (By*By) * pow((x - cx),2)/(Ax*Ax)) );    

       arrElipse[i] = getTraslatePointScreen(x *64,yPartial * 64 + cy*64,512,1152);
       arrElipse[256+i] = getTraslatePointScreen(x*64, (-1)*yPartial * 64 + cy*64,512,1152);
        x -= 1.0/64.0;
    }
    
    x=0;
    for(auto i = 0; i < 256 ; i++){       
       float  yPartial = sqrt((By*By) - ( (By*By) * pow((x - cx),2)/(Ax*Ax)) );    

       arrElipse[512+i] = getTraslatePointScreen(x *64,yPartial * 64 + cy*64,512,1152);
       arrElipse[768+i] = getTraslatePointScreen(x*64, (-1)*yPartial * 64 + cy*64,512,1152);
        x += 1.0/64.0;
    }
   
  


    
    return arrElipse;
}


SDL_Point *getPointsPathB(){        
  static SDL_Point arrElipse2[512];
  
   
   int cx = 0;
   int cy = -2;
   int Ax = 4;
   int By = 2;
   
  float x = 0; 
  float y = 0;

   
    for(auto i = 0; i < 256 ; i++){
       
       float  yPartial = sqrt((By*By) - ( (By*By) * pow((x - cx),2)/(Ax*Ax)) );    

       arrElipse2[i] = getTraslatePointScreen(x *64,yPartial * 64 + cy*64,512,1152);
       arrElipse2[256+i] = getTraslatePointScreen(x*64, (-1)*yPartial * 64 + cy*64,512,1152);
        x -= 1.0/64.0;
    }


    
    return arrElipse2;
}



SDL_Point *getPointsPathX(){        
  static SDL_Point arrPista1[1536];

   float x = 0.0f;
   float y = 0.0f; 
   int P  = 2;
      
   for(auto i = 0; i < 1536; i++){       
        
      
    float y = ( -P / (1 + exp(x-2*PI)))  + P ;
    int ys = (int) (y * 64);
    int xs = (int) (x * 64);
       
    arrPista1[i] = getTraslatePointScreen(xs,ys,512,1152);      
     x += (1.0/64.0) ;


   }

    
    return arrPista1;
}


SDL_Point *getPointsPathY(){        
  static SDL_Point arrPista2[1536];

   float x = 0.0f;
   float y = 0.0f; 
   int P  = -2;
      
   for(auto i = 0; i < 1536; i++){       
        
      
    float y = ( -P / (1 + exp(x-2*PI)))  + P ;
    int ys = (int) (y * 64);
    int xs = (int) (x * 64);
    
    arrPista2[i] = getTraslatePointScreen(xs,ys,512,1152);      
     x += (1.0/64.0) ;

   }    
    return arrPista2;
}



SDL_Point *getPointsPathFly(){        
  static SDL_Point arrFly[1024];

   float x = 1023.0f;
   float y = -4.0f * 64; 

      
   for(auto i = 1023; i >= 0; i--){                               
    arrFly[i] = getTraslatePointScreen(x,y,512,1152);      
     x--;

   }    
    return arrFly;
}

SDL_Point *getPointsPathZ(){        
  static SDL_Point arrPista3[1536];

   float x = 0.0f;
   float y = 0; 

      
   for(auto i = 0; i < 1536; i++){                               
    arrPista3[i] = getTraslatePointScreen(x,y,512,1152);      
     x++;

   }    
    return arrPista3;
}







int main() {
   
   
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};

  constexpr std::size_t kScreenWidth{2048};
  constexpr std::size_t kScreenHeight{2048};

  constexpr std::size_t kGridWidth{64};
  constexpr std::size_t kGridHeight{64};
   


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

  //int Xini = 0;
  //int Yini = 1364;
  int Xini = 0;



   
 
 // SDL_Point *points = getPointsSin();
  SDL_Point *pathWait = getPointsPathA();
  SDL_Point *pathArrive = getPointsPathB();
  SDL_Point *pathPista1 = getPointsPathX();
  SDL_Point *pathPista2 =  getPointsPathY();
  SDL_Point *pathPista3 = getPointsPathZ();
  SDL_Point *pathFly = getPointsPathFly();
  

  /*
  std::cout<<  "***************************" <<std::endl;
   for(auto i = 0; i<200; i++){
      std::cout<< pathWait[i].x << ", "<< pathWait[i].y<< std::endl;
   }
*/

SDL_Rect cabCtr;
cabCtr.w = 32;
cabCtr.h = 32;

 
/*     
  SDL_Rect alaArr;
  SDL_Rect alaAbj;
  SDL_Rect cabDel;
  SDL_Rect cabCtr;
  SDL_Rect cabAtr;
  SDL_Rect cabCola;

  cabCtr.w = kScreenWidth / kGridWidth; //32 grid X 64 Tamaño
  cabCtr.h = kScreenWidth / kGridWidth;

  alaArr.w = cabCtr.w;
  alaArr.h = cabCtr.h;

  cabCola.w = cabCtr.w - 2;
  cabCola.h = cabCtr.h;
  
  cabDel.w = cabCtr.w - 2 ;
  cabDel.h = cabCtr.h;
   
  cabAtr.w = cabCtr.w - 2;
  cabAtr.h = cabCtr.h;

  alaAbj.w = cabCtr.w;
  alaAbj.h = cabCtr.h;

*/


  PointCartesian pxyBefore;
  PointCartesian pxyCurrent;
  int deltaX = 0;
  int deltaY = 0;


  SDL_Point OScreen;
  OScreen.x = 512;
  OScreen.y = 1152;
  
  PointCartesian OCartesian; 
  OCartesian.x = 0; 
  OCartesian.y = 0; 





 // while (running) {
    frame_start = SDL_GetTicks();

    
  

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
   

  //EJES CARTESIANOS

 SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xe6, 0xe6, SDL_ALPHA_OPAQUE); 
 SDL_RenderDrawLine(sdl_renderer, OScreen.x,0, OScreen.x, 2048);
 SDL_RenderDrawLine(sdl_renderer, 0,OScreen.y,2048,OScreen.y);

   

  //GRAFICA SIN() 
 // SDL_SetRenderDrawColor(sdl_renderer, 0x77, 0xCC, 0x00, 0xFF);
 // SDL_RenderDrawPoints(sdl_renderer,points,2048);


  SDL_SetRenderDrawColor(sdl_renderer, 0x69, 0x69, 0x69, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawPoints(sdl_renderer,pathWait,1024);  
  SDL_RenderDrawPoints(sdl_renderer,pathArrive,512);
  SDL_RenderDrawPoints(sdl_renderer,pathFly,1024);
   

  SDL_SetRenderDrawColor(sdl_renderer, 0xff, 0xbf, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawPoints(sdl_renderer,pathPista1,1536);  
  SDL_RenderDrawPoints(sdl_renderer,pathPista2,1536);
  SDL_RenderDrawPoints(sdl_renderer,pathPista3,1536);  

/*
SDL_Point puntos[] = {
    {320, 200},
    {300, 240},
    {340, 240},
    {320, 200} 
};
*/


 


 SDL_SetRenderDrawColor(sdl_renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);
 cabCtr.x = pathFly[1024 - 1].x - 16; 
 cabCtr.y = pathFly[1024 - 1].y - 16;
 
 SDL_RenderDrawLine(sdl_renderer, cabCtr.x, cabCtr.y ,  cabCtr.x + 16, cabCtr.y + 16);
 SDL_RenderFillRect(sdl_renderer, &cabCtr);

/**
 SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
 SDL_RenderDrawLines(sdl_renderer, puntos, 4);

 SDL_RenderDrawLine(sdl_renderer, cabCtr.x , cabCtr.y,  cabCtr.x + 8, cabCtr.y - 32);

 */


 
 
    //speed factor
  
  
  /*   
  cabCtr.x = points[Xini].x;
  cabCtr.y = points[Xini].y;
 */
 

  

  /*
  cabCtr.x = Xini;
  cabCtr.y = Yini;
  */

 /*
  Xini += 2;

  cabAtr.x = cabCtr.x-16;
  cabAtr.y = cabCtr.y;

  cabCola.x = cabAtr.x - 16;
  cabCola.y = cabAtr.y;

  cabDel.x = cabCtr.x + 16;
  cabDel.y = cabCtr.y;

  SDL_RenderDrawLine(sdl_renderer, cabCtr.x , cabCtr.y,  cabCtr.x + 8, cabCtr.y - 32);
  SDL_RenderDrawLine(sdl_renderer, cabCtr.x + 16, cabCtr.y,  cabCtr.x + 8 , cabCtr.y - 32);
  SDL_RenderDrawLine(sdl_renderer, cabCtr.x , cabCtr.y + 16,  cabCtr.x + 8, cabCtr.y + 48);
  SDL_RenderDrawLine(sdl_renderer, cabCtr.x + 16, cabCtr.y + 16,  cabCtr.x + 8 , cabCtr.y + 48);

  SDL_RenderDrawLine(sdl_renderer, cabCola.x , cabCola.y,  cabCola.x, cabCola.y - 16);
  SDL_RenderDrawLine(sdl_renderer, cabCola.x + 16 , cabCola.y,  cabCola.x , cabCola.y - 16);

  SDL_RenderDrawLine(sdl_renderer, cabDel.x + 16 , cabDel.y,  cabDel.x + 24, cabDel.y +  8);
  SDL_RenderDrawLine(sdl_renderer, cabDel.x + 16 , cabDel.y + 16,  cabDel.x + 24 , cabDel.y + 8);


  SDL_RenderFillRect(sdl_renderer, &cabCtr);
  SDL_RenderFillRect(sdl_renderer, &cabAtr);
  SDL_RenderFillRect(sdl_renderer, &cabDel);
  SDL_RenderFillRect(sdl_renderer, &cabCola);

 */



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


    /*
    if(Xini > 2047)
      break;
    */

//  }












   
    
     SDL_Delay(7000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(sdl_window);

    // Clean up
    SDL_Quit();

    std::cout<<"FIN DEL PROGRAMA" << std::endl;
     
     return 0;

}