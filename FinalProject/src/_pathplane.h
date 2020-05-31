
/*



#include <iostream>
#include <cmath>
#include <memory>

#include "sut.h"





enum TypePath{

    LineArrive,
    CycleVeer,
    CycleWait,
    OnTrackLeft,
    OnTrackCenter,
    OnTrackRight,
    LineRail
};



class PathPlane{

    public:
         PathPlane(int lenPath, int b, int x0);
       



     int getLenPath()const{return  _lenPath;};

     TypePath getTypePath(int index)const{return _typePath;}

     std::shared_ptr<SDL_Point> getPoints()const{return _points;};
    


     


    private:

     TypePath _typePath; 
     int      _lenPath{0};

     std::shared_ptr<SDL_Point> _points; 
     std::shared_ptr<SDL_Point> getPointsLineArrive(int lenPath, float b, float x0);    
     




};


*/