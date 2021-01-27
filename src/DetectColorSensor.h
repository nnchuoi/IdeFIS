#ifndef DetectColorSensor_h
#define DetectColorSensor_h

#include "MeMegaPi.h"
#include "Controlrobot.h"
#include "AutomaticBehavior.h"





class DetectColorSensor
{
  private :
    uint8_t colorResult;
    Controlrobot *robot;
    unsigned long detectColorInitialTime=0;
    unsigned long detectColorTime=0;
  public :


    MeColorSensor colorsensor0;
    DetectColorSensor(MeColorSensor colorsensor, Controlrobot *robot){
      colorsensor0=colorsensor;
    };

    bool detectColor(){


      detectColorTime=millis();
      if ((detectColorTime-detectColorInitialTime)>=0){

        detectColorInitialTime=millis();
        detectColorTime=0;
        colorResult=colorsensor0.IdeFISColor();
        if (colorResult==12){
          return true;
        }
        return false;
      }else{
        detectColorTime=0;
      }
    }

    bool detectWhiteBlack(){
      detectColorTime=millis();
      if ((detectColorTime-detectColorInitialTime)>=0){

        detectColorInitialTime=millis();
        detectColorTime=0;
        colorResult=colorsensor0.IdeFISColor();
        if (colorResult!=12){
          return true;
        }
        return false;
      }else{
        detectColorTime=0;
      }
    }

};


#endif
