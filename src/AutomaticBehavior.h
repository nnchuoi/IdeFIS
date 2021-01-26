#ifndef AutomaticBehavior_h
#define AutomaticBehavior_h

#include "MeMegaPi.h"
#include "Controlrobot.h"
#include "TrueLineFollower.h"
#include "UltraSonicSensor.h"
#include "ControlFork.h"
#include "DetectColorPieceSensor.h"
#include <math.h>




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
      delay(100);
      double initialPosition;
      double gz; //actual z value
      double goalgz; //final z value after rotation
      double gzero;

      robot->forward(0);
      gyroscope->update();
      //Serial.read();

      initialPosition = gyroscope->getAngleZ()+180.0;

      gz=0;
      goalgz=90;
      gzero = fmod((initialPosition+goalgz),360.0);

      Serial.println("initial");
      Serial.println(initialPosition);
      Serial.println("gzero");
      Serial.println(gzero);
      robot->rotate(-ROTATION_SPEED);
      while(gz<goalgz){
        delay(100);
        gyroscope->update();
        gz = gyroscope->getAngleZ();
        Serial.println(gz);
        gz = ((fmod((gz + 180.0 + goalgz),360.0)) - gzero);
        if(gz<0){
          gz=360.0+gz;
        }
        Serial.println(gz);

      }
      robot->forward(0);
    }


    void turnRight90(){

      fork->middleFork();
      delay(100);
      double initialPosition;
      double gz; //actual z value
      double goalgz; //final z value after rotation
      double gzero;

      robot->forward(0);
      gyroscope->update();
      //Serial.read();

      initialPosition = (gyroscope->getAngleZ())*(-1.0)+180.0;

      gz=0;
      goalgz=90;
      gzero = fmod((initialPosition+goalgz),360.0);

      Serial.println("initial");
      Serial.println(initialPosition);
      Serial.println("gzero");
      Serial.println(gzero);
      robot->rotate(ROTATION_SPEED);
      while(gz<goalgz){
        delay(100);
        gyroscope->update();
        gz = (gyroscope->getAngleZ())*(-1.0);
        Serial.println(gz);
        gz = ((fmod((gz + 180.0 + goalgz),360.0)) - gzero);
        if(gz<0){
          gz=360.0+gz;
        }
        Serial.println(gz);

      }
      robot->forward(0);
    }



    void enterResteZone(){
      robot->left(60);
      delay(600);
      robot->forward(40);
      delay(2500);
      robot->right(60);
      delay(600);
      robot->forward(40);
      delay(600);

      turnLeft90();
      Serial.println("tourne left");
      delay(1000);
      turnLeft90();
      robot->forward(-40);
      delay(1100);
      robot->forward(0);
    }

    void exitRestZone(){

      robot->left(60);
      delay(250);
      robot->forward(40);
      delay(3500);
      robot->right(60);
      delay(250);
      robot->forward(0);
    }





    /* take the piece in with the same colors*/
    void  takePiecesSameColor()
      {

      uint8_t color=0;
      bool detectColor=false;
      uint8_t detectedColor;
      uint8_t piecesTaken=0;
      fork->upFork();

      while(1){

        lineFollower->followLine();

        bool piece=ultraSonicSensor->DetectPiece(7); //on détecte une pièce
        // Serial.println(piece);
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
