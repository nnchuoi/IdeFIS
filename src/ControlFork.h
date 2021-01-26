#ifndef ControlFork_h
#define ControlFork_h

#include "MeMegaPi.h"
#include "Controlrobot.h"
#include "automaticBehavior.h"


#include "Config.h"





class ControlFork
{
  public :
      Controlrobot *robot;
      MeMegaPiDCMotor motorFork;
      MeGyro *gyroscope;
      double gy;


    ControlFork(MeMegaPiDCMotor motor, MeGyro *gyro, Controlrobot *_robot){
      motorFork=motor;
      gyroscope=gyro;
      robot=_robot;
    };


    /* position up*/
    void upFork(){
      robot->forward(0);
      gyroscope->update();
      Serial.read();
      gy=gyroscope->getAngleY();
      Serial.println("okok");
      while(gy>FORK_UP){
        motorFork.run(SPEED_FORK_UP);
        delay(100);
        gyroscope->update();
        Serial.read();
        gy=gyroscope->getAngleY();
      }
      motorFork.run(0);
    }


    /* position to take the piece*/
    void downFork(){
      robot->forward(0);
      gyroscope->update();
      Serial.read();
      gy=gyroscope->getAngleY();
      while(gy<FORK_DOWN){
        motorFork.run(SPEED_FORK_DOWN);
        delay(100);
        gyroscope->update();
        Serial.read();
        gy=gyroscope->getAngleY();
      }
      motorFork.run(0);
    }

    /* gyroscope horizontal*/
    void middleFork(){
      robot->forward(0);
      gyroscope->update();
      gy=gyroscope->getAngleY();
      Serial.println(gy);


      while(gy<-1){
        motorFork.run(SPEED_FORK_DOWN);
        delay(10);
        gyroscope->update();
        gy=gyroscope->getAngleY();
      }
      while(gy>1){
        motorFork.run(SPEED_FORK_UP);
        delay(10);
        gyroscope->update();
        gy=gyroscope->getAngleY();
      }

      motorFork.run(0);
    }



    void colorPosition(){
      robot->forward(0);
      gyroscope->update();
      gy=gyroscope->getAngleY();
      Serial.println(gy);


      while(gy<(FORK_COLOR_SENSOR)){
        motorFork.run(-50);
        delay(10);
        gyroscope->update();
        gy=gyroscope->getAngleY();
      }
      while(gy>(FORK_COLOR_SENSOR)){
        motorFork.run(50);
        delay(10);
        gyroscope->update();
        gy=gyroscope->getAngleY();
      }

      motorFork.run(0);
    }



    void takePiece(){
      robot->forward(-45);
      delay(1500);
      downFork();
      robot->forward(35);
      delay(650);
      upFork();

    }
};



#endif
