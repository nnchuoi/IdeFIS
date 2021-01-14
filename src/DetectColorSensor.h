#ifndef DetectColorSensor_h
#define DetectColorSensor_h

#include "MeMegaPi.h"
#include "Controlrobot.h"
#include "automaticBehavior.h"





class DetectColorSensor
{
  private :
    uint8_t colorResult;
    Controlrobot *robot;
  public :


    MeColorSensor colorsensor0;
    DetectColorSensor(MeColorSensor colorsensor, Controlrobot *robot){
      colorsensor0=colorsensor;
    };

    bool detectColor(int color){

      colorResult=colorsensor0.ColorIdentify();
      Serial.println("couleur:");
      Serial.println(colorResult);

      if (colorResult==color){
        return true;

      }
      return false;
    }

};


#endif
