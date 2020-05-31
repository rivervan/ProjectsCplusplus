
/*
 #include<iostream>

 #include "SDL.h"
 #include "sut.h"
 #include "pathplane.h"



  
  PathPlane::PathPlane(int lenPath, int b, int x0){
       _typePath = TypePath::LineArrive;
        _lenPath  = lenPath;
        _points   = getPointsLineArrive(lenPath,b,x0);


         std::cout<< "CONSTRUCTOR..."<< std::endl;
  }


  std::shared_ptr<SDL_Point> PathPlane::getPointsLineArrive(int lenPath, float b, float x0){

   std::shared_ptr<SDL_Point> points(new SDL_Point[lenPath], std::default_delete<SDL_Point[]>() )    //= std::make_shared<SDL_Point[lenPath]>();


   float xScreen =  x0 * Sut::sScale;
   float yScreen =  b  * Sut::sScale; 

      
   for(auto i = xScreen; i >= 0; i--){                               
     points[i] = getTraslatePointScreen(xScreen,yScreen,Sut.OriginAxisX,Sut.OriginAxisY);      
     xScreen--;
   }    

    
    for(auto i = 0; i<lenPath; i++){
        std::cout<< points.get()[i].x << ", " << points.get()[i].y << std::endl;
    }


    return std::move(points);

     


  }



*/






