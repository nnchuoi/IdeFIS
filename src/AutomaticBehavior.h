#ifndef AutomaticBehavior_h
#define AutomaticBehavior_h

#include "MeMegaPi.h"
#include "Controlrobot.h"
#include "TrueLineFollower.h"
#include "UltraSonicSensor.h"
#include "ControlFork.h"
#include "DetectColorPieceSensor.h"




int speed=80;
double gz;
class AutomaticBehavior
{


  private:
    MeGyro *gyroscope;
    Controlrobot *robot;
    TrueLineFollower *lineFollower;
    UltraSonicSensor *ultraSonicSensor;
    ControlFork *fork;
    DetectColorPieceSensor *sensorColorPiece;
  public :



    AutomaticBehavior(MeGyro *gyro, Controlrobot *r, TrueLineFollower *lf, UltraSonicSensor *us, ControlFork * f, DetectColorPieceSensor *scp){
      gyroscope=gyro;
      robot=r;
      lineFollower=lf;
      ultraSonicSensor=us;
      fork=f;
      sensorColorPiece=scp;
    };

    void turnLeft90(){
      fork->middleFork();
      delay(10);
      double initialPosition;
      double gz; //actual z value
      double goalgz; //final z value after rotation

      robot->forward(0);
      gyroscope->update();
      Serial.read();

      initialPosition = gyroscope->getAngleZ();
      gz=0.0;
      goalgz=90.0;

      Serial.println(initialPosition);
      Serial.println(goalgz);
      robot->rotate(-ROTATION_SPEED);
      while(gz<goalgz){
        delay(100);
        gyroscope->update();
        //Serial.read();
        gz = gyroscope->getAngleZ();
        /*correction when z>180, z=0...*/
        if(initialPosition>90){
          gz-=90.0;
          if(gz<0.0){gz=180.0-initialPosition-gz;
          }else{
            gz=gz-initialPosition;
          }
        }else{
          gz=gz-initialPosition;
        }

        Serial.println(gz);
      }
    }


    void turnRight90(){
      fork->middleFork();
      delay(10);
      double initialPosition;
      double gz; //actual z value
      double goalgz; //final z value after rotation

      robot->forward(0);
      gyroscope->update();
      Serial.read();

      initialPosition = -(gyroscope->getAngleZ());
      gz=0.0;
      goalgz=90.0;

      Serial.println(initialPosition);
      Serial.println(goalgz);
      robot->rotate(ROTATION_SPEED);
      while(gz<goalgz){
        delay(100);
        gyroscope->update();
        //Serial.read();
        gz = -(gyroscope->getAngleZ());
        /*correction when z>180, z=0...*/
        if(initialPosition>90){
          gz-=90.0;
          if(gz<0.0){gz=180.0-initialPosition-gz;
          }else{
            gz=gz-initialPosition;
          }
        }else{
          gz=gz-initialPosition;
        }

        Serial.println(gz);
      }
    }


    /* take the piece in with the same colors*/
    void  takePiecesSameColor()
      {

      uint8_t color=0;
      bool detectColor=false;
      uint8_t detectedColor;
      uint8_t piecesTaken=0;

      while(1){
        lineFollower->followLine();
        bool piece=ultraSonicSensor->DetectPiece(5); //on détecte une pièce
        Serial.println(piece);
        if (piece==true){
          Serial.println("piece");
          /*on met le capteur couleur à l'avant en position*/
          fork->colorPosition();
          color=sensorColorPiece->detectColor();//on défini la couleur couleur principale avant le première prise

          Serial.println(color);
          while(color!=detectedColor && detectColor==true){
            color=sensorColorPiece->detectColor();
          }

          detectedColor=color;
          detectColor=true;//la couleur a été définie
          Serial.println(detectedColor);
          robot->forward(-35);
          delay(2000);
          fork->downFork();
          robot->forward(35);
          delay(650);
          fork->upFork();

        }
      }


      //Serial3.println(couleur+nb)
      robot->forward(-SPEED_FORWARD_MAX);
      delay(1000);
      robot->forward(0);
    }






};

#endif
