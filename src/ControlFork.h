#ifndef ControlFork_h
#define ControlFork_h

#include "MeMegaPi.h"
#include "Controlrobot.h"
#include "AutomaticBehavior.h"

#include "Config.h"





class ControlFork
{
  private:
    double error, prev_error, sum_error, d_error;
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
      double KP=1,KI=0.1,KD=0.5;
      robot->forward(0);
      gyroscope->update();
      Serial.read();
      gy=gyroscope->getAngleY();
      Serial.println("okok");
      prev_error = 0.0;

      while(error !=0){
        error = gy - FORK_UP;
        sum_error += error;
        sum_error = min(sum_error, 50);
        sum_error = max(sum_error, -50);
        d_error = error - prev_error;
        prev_error = error;

        motorFork.run(KP*error + KI * sum_error + KD*d_error);
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
