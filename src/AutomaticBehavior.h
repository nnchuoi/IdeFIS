#ifndef AutomaticBehavior_h
#define AutomaticBehavior_h

#include "MeMegaPi.h"
#include "Controlrobot.h"
#include "TrueLineFollower.h"
#include "UltraSonicSensor.h"
#include "ControlFork.h"
#include "DetectColorPieceSensor.h"
#include "LineFollower.h"
#include "DetectColorSensor.h"
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
    LineFollower *lineFolowerWorshop;
    DetectColorSensor *sensorColorWorkshop;

    uint8_t piecesInFork;
  public :



    AutomaticBehavior(MeGyro *gyro, Controlrobot *r, TrueLineFollower *lf, UltraSonicSensor *us, ControlFork * f, DetectColorPieceSensor *scp, LineFollower *lfw, DetectColorSensor *scw ){
      gyroscope=gyro;
      robot=r;
      lineFollower=lf;
      ultraSonicSensor=us;
      fork=f;
      sensorColorPiece=scp;
      lineFolowerWorshop=lfw;
      sensorColorWorkshop=scw;
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
      fork->upFork();
      robot->left(40);
      delay(300);



      while(sensorColorWorkshop->detectWhiteBlack()!=true){
        lineFolowerWorshop->followLine(30);

      }

      while(sensorColorWorkshop->detectColor()!=true){
        lineFolowerWorshop->followLine(30);
      }

      robot->forward(0);


      /*
      delay(3500);
      robot->right(60);
      delay(280);
      robot->forward(0);
      delay(200);
      robot->forward(30);
      delay(300);
      robot->forward(0);
      */
    }




    void  takePiecesSameColor(int numberPieces)
      {

      uint8_t color=0;
      bool detectColor=false;
      uint8_t detectedColor;
      piecesInFork=0;
      bool pieceTaken=false;
      bool piece=false; // if piece or not
      fork->upFork();


      while(numberPieces>0){ //////////loop for all the piece
        pieceTaken=false;
        piece=false;
        //first alignment
         while(piece==false){
           lineFollower->followLine();
            piece=ultraSonicSensor->detectPiece(8);
         }

         //on fait reculer le robot pour mieux se stabiliser avec la ligne
         robot->forward(-30);
         delay(1500);
         robot->forward(0);

        //méthode pour prendre la pièce
        while(pieceTaken==false){

          lineFollower->followLine();
          piece=ultraSonicSensor->detectPiece(8); //on détecte une pièce
          // Serial.println(piece);
          if (piece==true){
            Serial.println("piece");
            /*on met le capteur couleur à l'avant en position*/
            delay(100);
            //fork->middleFork();
            fork->colorPosition();
            color=sensorColorPiece->detectColor();//on défini la couleur couleur principale avant le première prise

            Serial.println(color);
            while(color!=detectedColor && detectColor==true){
              color=sensorColorPiece->detectColor();
              //if the color of the piece is different, we stop the fonction : the number of remaining pieces=0
              if (detectedColor==true && ((detectedColor==GREEN && color==RED) || (detectedColor==RED && color==GREEN))) {
                numberPieces=0;
              }
            }

            detectedColor=color;
            detectColor=true;//la couleur a été définie
            Serial.println(detectedColor);
            robot->forward(-35);
            delay(2000);
            fork->downFork();
            robot->forward(35);
            delay(520);
            fork->upFork();
            robot->forward(-35);
            delay(400);
            robot->forward(0);

            pieceTaken=true;
            numberPieces-=1;
            piecesInFork+=1;
        }
      }

      robot->forward(-SPEED_FORWARD_MAX);
      delay(1000);
      robot->forward(0);
      //send to IHM
      Serial3.println("A_"+String(piecesInFork)+"_"+String(detectedColor));
    }
    /* take the piece in with the same colors*/
  }
  //--------------------------------------------------------------------//




  //------take pieces without checking color----------------//
    void  takePieces(int numberPieces){

      uint8_t color=0;
      piecesInFork=0;
      bool pieceTaken=false;
      bool piece=false; // if piece or not
      fork->upFork();


      while(numberPieces>0){ //////////loop for all the piece
        pieceTaken=false;

        //first alignment
         while(piece==false){
           lineFollower->followLine();
            piece=ultraSonicSensor->detectPiece(8);
         }

         //on fait reculer le robot pour mieux se stabiliser avec la ligne
         robot->forward(-30);
         delay(1500);
         robot->forward(0);

        //méthode pour prendre la pièce
        while(pieceTaken==false){

          lineFollower->followLine();
          piece=ultraSonicSensor->detectPiece(8); //on détecte une pièce
          // Serial.println(piece);
          if (piece==true){
            Serial.println("piece");
            /*on met le capteur couleur à l'avant en position*/
            delay(100);
            fork->middleFork();
            fork->colorPosition();
            color=sensorColorPiece->detectColor();//on défini la couleur couleur principale avant le première prise
            robot->forward(-35);
            delay(2000);
            fork->downFork();
            robot->forward(35);
            delay(520);
            fork->upFork();
            robot->forward(-35);
            delay(2000);
            robot->forward(0);
            pieceTaken=true;
            numberPieces-=1;
            piecesInFork+=1;
        }
      }

      robot->forward(-SPEED_FORWARD_MAX);
      delay(1000);
      robot->forward(0);
      //send to IHM
      Serial3.println("A_"+String(piecesInFork));
    }

  }


  ////////////////A CORRIGER AUJOURD'HUI
    void putPieces(int numberPiecesInZone){

      robot->forward(SPEED_FORWARD_PUT_PIECE);

      //position of robot to in the zone
      switch(numberPiecesInZone){
        case 0:
          delay(3300);
          fork->downFork();
          robot->forward(-30);
          delay(3300);
          fork->upFork();
          break;

        case 1:
          delay(2300);
          fork->downFork();
          robot->forward(-30);
          delay(2300);
          fork->upFork();
          break;

        case 2:
          delay(1300);
          fork->downFork();
          robot->forward(-30);
          delay(1300);
          fork->upFork();
          break;

        default:
          delay(1300);
          fork->downFork();
          robot->forward(-30);
          delay(1300);
          fork->upFork();
          break;

      }

      fork->downFork();
      robot->forward(-30);
      delay(1400);
      fork->upFork();

      Serial3.println("A_"+String());
    }








};

#endif
