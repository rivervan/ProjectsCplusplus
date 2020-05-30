#include <iostream>
#include <cmath>


#include "SDL.h"

#define PI 3.141592653589793238462


enum Trajectory{
    Fly,
    Arrive,
    Wait,
    TrackIzq,
    TrackCentral,
    TrackDer
};



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
        arrElipse[i] = getTraslatePointScreen(x*64, (-1)*yPartial * 64 + cy*64,512,1152);       

        x += 1.0/64.0;

    }

    for(auto i = 0; i < 256 ; i++){
       
       float  yPartial = sqrt((By*By) - ( (By*By) * pow((x - cx),2)/(Ax*Ax)) );           
       arrElipse[256+i] = getTraslatePointScreen(x *64,yPartial * 64 + cy*64,512,1152);
      
        x -= 1.0/64.0;

    }


    for(auto i = 0; i < 256 ; i++){
       
       float  yPartial = sqrt((By*By) - ( (By*By) * pow((x - cx),2)/(Ax*Ax)) );           
       arrElipse[512+i] = getTraslatePointScreen(x *64,yPartial * 64 + cy*64,512,1152);
      
        x -= 1.0/64.0;

    }

    for(auto i = 0; i < 256 ; i++){
       
       float  yPartial = sqrt((By*By) - ( (By*By) * pow((x - cx),2)/(Ax*Ax)) );          
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
       arrElipse2[i] = getTraslatePointScreen(x*64, (-1)*yPartial * 64 + cy*64,512,1152);

       

        x -= 1.0/64.0;

    }

     for(auto i = 0; i < 256 ; i++){
       
       float  yPartial = sqrt((By*By) - ( (By*By) * pow((x - cx),2)/(Ax*Ax)) );          
       arrElipse2[256+i] = getTraslatePointScreen(x *64,yPartial * 64 + cy*64,512,1152);

        x += 1.0/64.0;

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


  int cycle = 0;
  int distance = 0;
  int trajectoryPoint = 0; //Path fly



   
 
 // SDL_Point *points = getPointsSin();
  SDL_Point *pathWait = getPointsPathA();
  SDL_Point *pathArrive = getPointsPathB();
  SDL_Point *pathPista1 = getPointsPathX();
  SDL_Point *pathPista2 =  getPointsPathY();
  SDL_Point *pathPista3 = getPointsPathZ();
  SDL_Point *pathFly = getPointsPathFly();
  

  
  std::cout<<  "***************************" <<std::endl;
   for(auto i = 0; i<512; i++){
      std::cout<< pathArrive[i].x << ", "<< pathArrive[i].y<< std::endl;
   }


SDL_Rect cabCtr;
cabCtr.w = 24;
cabCtr.h = 24;

SDL_Point alaA[3];
SDL_Point alaB[3];




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



   Trajectory currentTrajectory = Trajectory::Fly;
   bool changeTrajectory = true;
   bool isEnableTrack = true;
  

  while (running) {
    frame_start = SDL_GetTicks();

    
  

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
   

  //EJES CARTESIANOS

 SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xe6, 0xe6, SDL_ALPHA_OPAQUE); 
 SDL_RenderDrawLine(sdl_renderer, OScreen.x,0, OScreen.x, 2048);
 SDL_RenderDrawLine(sdl_renderer, 0,OScreen.y,2048,OScreen.y);

   

  

  //SE TRAZAN LAS PATHS & TRAJECTORIES

  SDL_SetRenderDrawColor(sdl_renderer, 0x69, 0x69, 0x69, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawPoints(sdl_renderer,pathWait,1024);  
  SDL_RenderDrawPoints(sdl_renderer,pathArrive,512);
  SDL_RenderDrawPoints(sdl_renderer,pathFly,1024);
   

  SDL_SetRenderDrawColor(sdl_renderer, 0xff, 0xbf, 0x00, SDL_ALPHA_OPAQUE);
  SDL_RenderDrawPoints(sdl_renderer,pathPista1,1536);  
  SDL_RenderDrawPoints(sdl_renderer,pathPista2,1536);
  SDL_RenderDrawPoints(sdl_renderer,pathPista3,1536);  


 //DRAW AIRPLANE//////////////////////////////////////////////////////

  

  switch(currentTrajectory){

     case Trajectory::Fly:
          if(changeTrajectory){
              std::cout<<"Trajectory::Fly"<<std::endl;
              changeTrajectory = false;
              cycle = 1024;
              distance = 0;
              trajectoryPoint = 1024 - 1;            
          }

          cabCtr.x = pathFly[trajectoryPoint].x - 12; 
          cabCtr.y = pathFly[trajectoryPoint].y - 12;

          break;

     case Trajectory::Arrive:          
          if(changeTrajectory){
              std::cout<<"Trajectory::Arrive"<<std::endl;
              changeTrajectory = false;
              cycle = 512;
              distance = 0;
              trajectoryPoint = 0;             
          }                    
          cabCtr.x = pathArrive[trajectoryPoint].x - 12; 
          cabCtr.y = pathArrive[trajectoryPoint].y - 12;

          break;

     case Trajectory::Wait:
           if(changeTrajectory){
              std::cout<<"Trajectory::Wait"<<std::endl;
              changeTrajectory = false;
              cycle = 1024;
              distance = 0;
              trajectoryPoint = 0;  
              isEnableTrack = false; //QUITAR            
          }          
          
          cabCtr.x = pathWait[trajectoryPoint].x - 12; 
          cabCtr.y = pathWait[trajectoryPoint].y - 12;              
          break;

     case Trajectory::TrackIzq:
          if(changeTrajectory){
            std::cout<<"Trajectory::TrackIzq"<<std::endl;
              changeTrajectory = false;
              cycle = 1536;
              distance = 0;
              trajectoryPoint = 0;              
          }       
          cabCtr.x = pathPista1[trajectoryPoint].x - 12; 
          cabCtr.y = pathPista1[trajectoryPoint].y - 12;
          break;


     case Trajectory::TrackCentral:
          if(changeTrajectory){
            std::cout<<"Trajectory::TrackIzq"<<std::endl;
              changeTrajectory = false;
              cycle = 1536;
              distance = 0;
              trajectoryPoint = 0;              
          }       
          cabCtr.x = pathPista2[trajectoryPoint].x - 12; 
          cabCtr.y = pathPista2[trajectoryPoint].y - 12;
          
          break;
     case Trajectory::TrackDer:
         if(changeTrajectory){
            std::cout<<"Trajectory::TrackIzq"<<std::endl;
              changeTrajectory = false;
              cycle = 1536;
              distance = 0;
              trajectoryPoint = 0;              
          }       
          cabCtr.x = pathPista3[trajectoryPoint].x - 12; 
          cabCtr.y = pathPista3[trajectoryPoint].y - 12;
          
          break;
     

     

    
  }   




 SDL_SetRenderDrawColor(sdl_renderer, 0xff, 0xff, 0xff, SDL_ALPHA_OPAQUE);


  


 alaA[0].x = cabCtr.x + 6;
 alaA[0].y = cabCtr.y;

 alaA[1].x = cabCtr.x + 12;
 alaA[1].y = cabCtr.y - 16;

 alaA[2].x = cabCtr.x + 18;
 alaA[2].y = cabCtr.y;


 alaB[0].x = cabCtr.x + 6;
 alaB[0].y = cabCtr.y + cabCtr.h;

 alaB[1].x = cabCtr.x + 12;
 alaB[1].y = cabCtr.y + cabCtr.h + 16;

 alaB[2].x = cabCtr.x + 18;
 alaB[2].y = cabCtr.y + cabCtr.h;

 SDL_RenderDrawLine(sdl_renderer, cabCtr.x, cabCtr.y ,  cabCtr.x + 12, cabCtr.y + 12);
 SDL_RenderFillRect(sdl_renderer, &cabCtr);
 SDL_RenderDrawLines(sdl_renderer, alaA, 3);
 SDL_RenderDrawLines(sdl_renderer, alaB, 3);

//DRAW AIRPLANE//////////////////////////////////////////////////////

  


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
    
    bool endSimulation = false;

    if(currentTrajectory== Trajectory::Fly)
      trajectoryPoint -=2 ;     
    else
      trajectoryPoint +=2 ;     
    
    distance += 2;
    if( !(distance < cycle)){
        ;

         switch (currentTrajectory)
         {
         case Trajectory::Fly:
              currentTrajectory=Trajectory::Arrive;       
              break;

        case Trajectory::Arrive:
        case Trajectory::Wait:
              if(!isEnableTrack){ //Agregar funcionalidad Aleatoria
                  currentTrajectory=Trajectory::TrackCentral;     
                  /*
                  currentTrajectory=Trajectory::TrackCentral;
                  currentTrajectory=Trajectory::TrackCentral;
                  */
              }else
              {
                currentTrajectory=Trajectory::Wait;
              }
              break;
        case Trajectory::TrackIzq:
        case Trajectory::TrackCentral:
        case Trajectory::TrackDer:
              endSimulation = true;             
              break;

         default:
           break;
         }

       changeTrajectory = true;
        
        
    }
    
    if(endSimulation)
          break;

 }












   
    
     //SDL_Delay(7000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(sdl_window);

    // Clean up
    SDL_Quit();

    std::cout<<"FIN DEL PROGRAMA" << std::endl;
     
     return 0;

}