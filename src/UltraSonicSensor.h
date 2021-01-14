#ifndef UltraSonicSensor_h
#define UltraSonicSensor_h

#include "MeMegaPi.h"
#include "Controlrobot.h"
MeUltrasonicSensor ultraSensor(PORT_4);




class UltraSonicSensor
{

  private :
    unsigned long detectPieceInitialTime=0;
    unsigned long detectPieceTime=0;
    Controlrobot *robot;

  public :


  UltraSonicSensor (Controlrobot *r):robot{r}{}

    void DetectObject(int distance, Controlrobot *robot){
      //Serial.println(ultraSensor.distanceCm());
      while(ultraSensor.distanceCm()<=distance){
        robot->forward(0);
      }


      }
    bool DetectPiece(int distance){

      /*timer of 100ms*/
      detectPieceTime=millis();
      if ((detectPieceTime-detectPieceInitialTime)>=100){

        detectPieceInitialTime=millis();
        detectPieceTime=0;

        if (ultraSensor.distanceCm()<=distance){
          robot->forward(0);
          Serial.println("capte");

          return true;
        }

        return false;

      }else{
        detectPieceTime=0;
      }
    }




};

#endif
