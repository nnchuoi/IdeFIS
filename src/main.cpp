#include "MeMegaPi.h"

#include "Controlrobot.h"
#include "LineFollower.h"
#include "UltraSonicSensor.h"
#include "AutomaticBehavior.h"
#include "DetectColorSensor.h"
#include "ControlFork.h"
#include "TrueLineFollower.h"
#include "DetectColorPieceSensor.h"


#include <Wire.h>

#include "Config.h"






MeMegaPiDCMotor motor_left (PORT2B) ;
MeMegaPiDCMotor motor_right (PORT1B);
MeMegaPiDCMotor motorFork (PORT3B);
MeLineFollower lineFinder(PORT_5);
MeColorSensor colorsensor1(PORT_7);

MeColorSensor colorsensor0(PORT_8);
MeGyro gyro(PORT_6, 0x68);



Controlrobot robot(motor_left, motor_right);
LineFollower lf(lineFinder);
UltraSonicSensor ultraSonicSensor(&robot);

DetectColorSensor sensorColor(colorsensor0, &robot);
DetectColorPieceSensor sensorColorPiece(colorsensor1, &robot);
ControlFork fork(motorFork, &gyro, &robot);
TrueLineFollower trueLineFollower(lineFinder, &robot);
AutomaticBehavior automaticBehavior(&gyro,&robot, &trueLineFollower, &ultraSonicSensor, &fork, &sensorColorPiece);

unsigned long time1=0;
unsigned long time2=0;






int tourne=0;

bool state=false;

void setup(){
  Serial.begin(9600);
  gyro.begin();
  colorsensor0.SensorInit();

  delay(2000);
  //robot.forward(80);
  time1=millis();
  fork.downFork();
  //delay(1000);
  fork.upFork();





}

void loop(){

  //automaticBehavior.takePiecesSameColor(&robot, &trueLineFollower, &ultraSonicSensor, &sensorColorPiece, &fork);



/*
  while(state==false){
    trueLineFollower.followLine();
    state=sensorColor.detectColor(GREEN);
  }
  STOP
  RIGHT90
  */

  automaticBehavior.takePiecesSameColor();

/*

  trueLineFollower.followLine(&robot);

  time2=millis();
  if ((time2-time1)>=100){

    bool piece=UltraSonicSensor.DetectPiece(6, &robot);
    if (piece){
      fork.takePiece();
      delay(10000);
    }

    time1=millis();
    time2=0;
  }else{
    time2=0;
  }

  */



    //lf.followLine(&robot);

/*

    time2=millis();
    if ((time2-time1)>=100){
      UltraSonicSensor.DetectObject(5, &robot);
      time1=millis();
      time2=0;
    }else{
      time2=0;
    }
    */







/*
    time2=millis();
    if ((time2-time1)>=75){
      state=sensorColor.detectColor(GREEN);

      Serial.println(time2-time1);
      if (state && tourne==0){
        delay(550);
        fork.middleFork();
        LEFT;
        tourne=1;



      }else{
        STOP;
        state=false;

      }
      time1=millis();
      time2=0;
    }else{
      time2=0;
    }
    */














}
