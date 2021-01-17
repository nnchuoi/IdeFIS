#ifndef DetectColorPieceSensor_h
#define DetectColorPieceSensor_h

#include "MeMegaPi.h"
#include "Controlrobot.h"
#include "automaticBehavior.h"
#include "Config.h"





class DetectColorPieceSensor {
  private:
    uint8_t colorResult;
    MeColorSensor colorsensor0;
    Controlrobot *robot;

  public :

    DetectColorPieceSensor(MeColorSensor colorsensor, Controlrobot *r){
      colorsensor0=colorsensor;
      robot=r;
    };

    int detectColor(){

      colorResult=colorsensor0.ColorIdentify();

      /* on avance pas à pas tant qu'on détecte pas une pièce */
      while(colorResult!=RED && colorResult!=GREEN){
        Serial.println(GREEN);
        Serial.println("ok");

        robot->forward(45);
        delay(40);
        robot->forward(0);
        colorResult=colorsensor0.ColorIdentify();

      }
      Serial.println("couleur:");
      Serial.println(colorResult);
      return colorResult;

    }

};


#endif
