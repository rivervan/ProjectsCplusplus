#include<iostream>
#include<memory>

#include "SDL.h"
#include "airpath.h"
#include "sut.h"




AirPath::AirPath(int b, int x0){
      _typePath = TypePath::LineArriving;
      _lenPath  = x0;
      _points   = getPointsLineArrivePath(_lenPath,b,x0);

     _startPoint = 0; //Ready to  paths with variable direction
     _endPoint   = _lenPath * Sut::sScale - 1;


}


AirPath::AirPath(const PointCartesian& center, int Ax, int By, int x0, bool isWhole ){
    
    if (isWhole == false){
        _typePath = TypePath::CycleVeer;
        _lenPath  = 2*Ax;
        _points   = getPointsCycleVeerPath(_lenPath, center, Ax, By, x0);  
    }else
    {
        _typePath = TypePath::CycleWait;
        _lenPath  = 4*Ax;
        _points   = getPointsCycleWaitPath(_lenPath, center, Ax, By, x0);  

    }
   
    _startPoint = 0; //Ready to  paths with variable direction
     _endPoint   = _lenPath  * Sut::sScale - 1;
    

}


AirPath::AirPath(const PointCartesian& center,  int P, int length){
    
    if ( P < 0)
        _typePath = TypePath::OnTrackRight;           
    else
        _typePath = TypePath::OnTrackLeft;



     _lenPath  = length;
     _points   = getPointsLateralTrack(_lenPath, center, P);
    

    _startPoint = 0; //Ready to  paths with variable direction
    _endPoint   = _lenPath  * Sut::sScale - 1;
}





//Get points on screen for Arriving
std::shared_ptr<SDL_Point> AirPath::getPointsLineArrivePath(int lenPath, int b, int x0){

   std::shared_ptr<SDL_Point> points (new SDL_Point[lenPath * Sut::sScale]);

   int xScreen =  x0 * Sut::sScale;
   int yScreen =  b  * Sut::sScale;     
   int xScreenMax = xScreen;
      
   for(auto i = 0; i < xScreenMax; i++){                               
     points.get()[i] = Sut::getTraslatePointScreen(xScreen,yScreen,Sut::OriginAxisX,Sut::OriginAxisY);      
     xScreen--;
   }    
    return std::move(points);    
  }


std::shared_ptr<SDL_Point> AirPath::getPointsCycleVeerPath(int lenPath, PointCartesian center, int Ax, int By, int x0){
      int pointsOnX = lenPath * Sut::sScale;
      std::shared_ptr<SDL_Point> points (new SDL_Point[lenPath * Sut::sScale]);
     
   float x = 0; 
   float y = 0;


   int xScreen =  x * Sut::sScale;
   int yScreen =  y * Sut::sScale;

   float  yPartial = 0;
   
    for(auto i = 0; i < (pointsOnX/2)  ; i++){
       
              yPartial = sqrt((By*By) - ( (By*By) * pow((x - center.x),2)/(Ax*Ax)) );        
              yScreen  = (-1)*yPartial * Sut::sScale + center.y * Sut::sScale;
              xScreen =  x * Sut::sScale;

       points.get()[i] = Sut::getTraslatePointScreen(xScreen,yScreen,Sut::OriginAxisX,Sut::OriginAxisY);      
        x -= 1.0/Sut::sScale;
    }


    for(auto i = 0; i < (pointsOnX/2)  ; i++){
       
              yPartial = sqrt((By*By) - ( (By*By) * pow((x - center.x),2)/(Ax*Ax)) );        
              yScreen  = yPartial * Sut::sScale + center.y * Sut::sScale;
              xScreen  = x * Sut::sScale;

       points.get()[(pointsOnX/2) +i] = Sut::getTraslatePointScreen(xScreen,yScreen,Sut::OriginAxisX,Sut::OriginAxisY);      
        x += 1.0/Sut::sScale;
    }




      return std::move(points);

    
  }

          
std::shared_ptr<SDL_Point> AirPath::getPointsCycleWaitPath(int lenPath, PointCartesian center, int Ax, int By, int x0){

      int pointsOnX = lenPath * Sut::sScale;
      std::shared_ptr<SDL_Point> points (new SDL_Point[lenPath * Sut::sScale]);
     
      float x = 0; 
      float y = 0;


      int xScreen =  x * Sut::sScale;
      int yScreen =  y * Sut::sScale;

      float  yPartial = 0;
   

    for(auto i = 0; i < (pointsOnX/4)  ; i++){
       
        yPartial = sqrt((By*By) - ( (By*By) * pow((x - center.x),2)/(Ax*Ax)) );        
        yScreen  = (-1)*yPartial * Sut::sScale + center.y * Sut::sScale;
        xScreen  =  x * Sut::sScale;

       points.get()[i] = Sut::getTraslatePointScreen(xScreen,yScreen,Sut::OriginAxisX,Sut::OriginAxisY);      
       x += 1.0/Sut::sScale;
    }


    for(auto i = 0; i < (pointsOnX/4)  ; i++){
       
              yPartial = sqrt((By*By) - ( (By*By) * pow((x - center.x),2)/(Ax*Ax)) );        
              yScreen  = yPartial * Sut::sScale + center.y * Sut::sScale;
              xScreen  = x * Sut::sScale;

       points.get()[(pointsOnX/4) +i] = Sut::getTraslatePointScreen(xScreen,yScreen,Sut::OriginAxisX,Sut::OriginAxisY);      
        x -= 1.0/Sut::sScale;
    }



     for(auto i = 0; i < (pointsOnX/4)  ; i++){
       
              yPartial = sqrt((By*By) - ( (By*By) * pow((x - center.x),2)/(Ax*Ax)) );        
              yScreen  = yPartial * Sut::sScale + center.y * Sut::sScale;
              xScreen  = x * Sut::sScale;

       points.get()[(2*pointsOnX/4) +i] = Sut::getTraslatePointScreen(xScreen,yScreen,Sut::OriginAxisX,Sut::OriginAxisY);      
        x -= 1.0/Sut::sScale;
    }



    for(auto i = 0; i < (pointsOnX/4)  ; i++){
       
              yPartial = sqrt((By*By) - ( (By*By) * pow((x - center.x),2)/(Ax*Ax)) );        
              yScreen  = (-1)*yPartial * Sut::sScale + center.y * Sut::sScale;
              xScreen =  x * Sut::sScale;

       points.get()[(3*pointsOnX/4) + i] = Sut::getTraslatePointScreen(xScreen,yScreen,Sut::OriginAxisX,Sut::OriginAxisY);      
        x += 1.0/Sut::sScale;
    }


      return std::move(points);





   }


std::shared_ptr<SDL_Point> AirPath::getPointsLateralTrack(int lenPath, PointCartesian center, int P){
      
      std::shared_ptr<SDL_Point> points (new SDL_Point[lenPath * Sut::sScale]);
      

      float x =  (float) center.x;
      float y =  (float) center.y; 

      for(auto i = 0; i < (lenPath*Sut::sScale); i++){

         float y = ( -P / (1 + exp(x-2*Sut::PI)))  + P ;
         int yScreen = (int) (y * Sut::sScale);
         int xScreen = (int) (x * Sut::sScale);

         points.get()[i] = Sut::getTraslatePointScreen(xScreen,yScreen,Sut::OriginAxisX,Sut::OriginAxisY);

         x += (1.0/Sut::sScale) ;
      }


      return std::move(points);

}


