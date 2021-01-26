#ifndef ControlFork_h
#define ControlFork_h

#include "MeMegaPi.h"
#include "Controlrobot.h"
#include "AutomaticBehavior.h"

#include "Config.h"





class ControlFork
{
  private:
    double error, prev_error, sum_error, d_error, res;
    double mu_error[10];
    int last = 0;
    double mm=0;
    void meanSmooth(double sample, boolean reset){
        if(reset){
            for (int i = 0; i < 8; ++i) {
                mu_error[i] = 0;
            }
            last = 7;
            mm = 0;
        }
        mm = mm + sample - mu_error[last];
        mu_error[last] = sample;
        last++;
        if(last == 8){
            last = 0;
        }


    }
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
      double KP=15,KI=3,KD=0;
      robot->forward(0);
      gyroscope->update();
      Serial.read();
      gy=gyroscope->getAngleY();
      Serial.println("okok");
      error = gy - FORK_UP;
      prev_error = 0.0;
      meanSmooth(error, true);

      while((mm>0.01 || mm<-0.01) || (error >0.02 || error < -0.02)){
        error = gy - FORK_UP;
        meanSmooth(error, false);
        Serial.println(error);
        Serial.println(mm);
        sum_error += error;
        sum_error = min(sum_error, 20);
        sum_error = max(sum_error, -20);
        d_error = error - prev_error;
        prev_error = error;
        res = KP*error + KI * sum_error + KD*d_error;
        res = min(res, 80);
        res = max(res, -80);
        motorFork.run(res);
        delay(10);
        gyroscope->update();
        Serial.read();
        gy=gyroscope->getAngleY();
      }
      motorFork.run(0);
    }


    /* position to take the piece*/
    void downFork(){
        double KP=15,KI=3,KD=0;
        robot->forward(0);
        gyroscope->update();
        Serial.read();
        gy=gyroscope->getAngleY();
        Serial.println("okok");
        error = gy - FORK_DOWN;
        prev_error = 0.0;
        meanSmooth(error, true);

        while((mm>0.01 || mm<-0.01) || (error >0.02 || error < -0.02)){
            error = gy - FORK_DOWN;
            meanSmooth(error, false);
            Serial.println(error);
            Serial.println(mm);
            sum_error += error;
            sum_error = min(sum_error, 20);
            sum_error = max(sum_error, -20);
            d_error = error - prev_error;
            prev_error = error;
            res = KP*error + KI * sum_error + KD*d_error;
            res = min(res, 80);
            res = max(res, -80);
            motorFork.run(res);
            delay(10);
            gyroscope->update();
            Serial.read();
            gy=gyroscope->getAngleY();
        }
      motorFork.run(0);
    }

    /* gyroscope horizontal*/
    void middleFork(){
        double KP=15,KI=3,KD=0;
        robot->forward(0);
        gyroscope->update();
        Serial.read();
        gy=gyroscope->getAngleY();
        Serial.println("okok");
        error = gy - 0;
        prev_error = 0.0;
        meanSmooth(error, true);

        while((mm>0.01 || mm<-0.01) || (error >0.02 || error < -0.02)){
            error = gy - 0;
            meanSmooth(error, false);
            Serial.println(error);
            Serial.println(mm);
            sum_error += error;
            sum_error = min(sum_error, 20);
            sum_error = max(sum_error, -20);
            d_error = error - prev_error;
            prev_error = error;
            res = KP*error + KI * sum_error + KD*d_error;
            res = min(res, 80);
            res = max(res, -80);
            motorFork.run(res);
            delay(10);
            gyroscope->update();
            Serial.read();
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
