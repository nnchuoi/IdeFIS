#ifndef LineFollower_h
#define LineFollower_h

#include "MeMegaPi.h"
#include "Controlrobot.h"



class LineFollower
{

  public:
      MeLineFollower lineFinder;



      LineFollower(MeLineFollower port):
        lineFinder{port}{}


      void followLine(Controlrobot *robot){

        sensorState = lineFinder.readSensors();


        switch (sensorState){
           //two sensors inside
          case S1_IN_S2_IN:
              robot->forward(50);
              break;

          //right sensor outside

          case S1_IN_S2_OUT:

              robot->_motorLeft.run(-45);
              robot->_motorRight.run(-45);

              break;

          case S1_OUT_S2_IN:


              robot->_motorRight.run(45);
              robot->_motorLeft.run(45);
              break;


          case S1_OUT_S2_OUT:
            robot->forward(50);
            break;

        }
      }
  private:
      //Controlrobot robot;
      int sensorState;
      int rSpeed;




};


#endif
