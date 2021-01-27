#ifndef LineFollower_h
#define LineFollower_h

#include "MeMegaPi.h"
#include "Controlrobot.h"
#include "Config.h"



class LineFollower
{

private:

    int sensorState;
    int rSpeed;
    MeLineFollower lineFinder;
    Controlrobot *robot;

public:

    LineFollower(MeLineFollower port, Controlrobot *r):
    lineFinder{port}, robot{r}{}

    void followLine(){
      sensorState = lineFinder.readSensors();
      switch (sensorState){
         //two sensors inside
        case S1_IN_S2_IN:
            robot->forward(SPEED_LINEF_WORKSHOP);
            break;

        //right sensor outside
        case S1_IN_S2_OUT:
            robot->_motorLeft.run(-SPEED_LINEF_WORKSHOP);
            robot->_motorRight.run(-SPEED_LINEF_WORKSHOP);
            break;


        case S1_OUT_S2_IN:
            robot->_motorRight.run(SPEED_LINEF_WORKSHOP);
            robot->_motorLeft.run(SPEED_LINEF_WORKSHOP);
            break;


        case S1_OUT_S2_OUT:
          robot->forward(SPEED_LINEF_MAX);
          break;

      }
    }




};


#endif
