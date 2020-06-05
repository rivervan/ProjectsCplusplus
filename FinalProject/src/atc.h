
#include <vector>
#include <memory>
#include <iostream>

#include "SDL.h"
#include "airplane.h"


class Atc
{
private:
    
public:
    Atc()=default;
    void recivePlaneAirApaceIN(bool &running,  std::map<TypePath, std::shared_ptr<AirPath>>  &paths, std::vector< std::shared_ptr<AirPlane>> &planes )const;
    

};



