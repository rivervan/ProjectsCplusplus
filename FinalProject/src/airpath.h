#include<memory>
#include "SDL.h"
#include "sut.h"

enum TypePath{
    LineArriving,
    CycleVeer,
    CycleWait,
    OnTrackLeft,
    OnTrackCenter,
    OnTrackRight,
    LineRail
};




class AirPath{
  
 

  public:
      typedef int _IndexPointOnPath;

      //Constructors
      AirPath()=default;

      AirPath(int b, int x0);
      AirPath(const PointCartesian& center, int Ax, int By, int x0, bool isWhole = false);
      AirPath(const PointCartesian& center,  int P, int length);

      //Getters
      int getLenPath()const{return  _lenPath;};
      TypePath getTypePath()const{return _typePath;};
      std::shared_ptr<SDL_Point> getPoints()const{return _points;};

      _IndexPointOnPath getIndexStartPoint()const{return _startPoint;};
      _IndexPointOnPath getIndexEndPoint()const{return _endPoint;};

    


   
  private:
     TypePath _typePath; 
     int      _lenPath{0};
     std::shared_ptr<SDL_Point> _points; 

     _IndexPointOnPath _startPoint;
     _IndexPointOnPath _endPoint;

     std::shared_ptr<SDL_Point> getPointsLineArrivePath(int lenPath, int b, int x0);    
     std::shared_ptr<SDL_Point> getPointsCycleVeerPath(int lenPath, PointCartesian center, int Ax, int By, int x0);
     std::shared_ptr<SDL_Point> getPointsCycleWaitPath(int lenPath, PointCartesian center, int Ax, int By, int x0);
     std::shared_ptr<SDL_Point> getPointsLateralTrack(int lenPath, PointCartesian center, int P);
    

};