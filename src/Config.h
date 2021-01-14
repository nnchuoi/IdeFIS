#ifndef CONFIG_H
#define CONFIG_H

/*-----Colors------*/

#define GREEN 5
#define BLUE 7
#define RED 2




/*----Position gyroscope------*/
#define FORK_UP -33.0
#define FORK_DOWN 14.0
#define FORK_COLOR_SENSOR -32.5





/*----Speed motors-------------*/

 #define SPEED_FORK_UP 100
 #define SPEED_FORK_DOWN -100

 #define SPEED_FORWARD_MAX 40

 #define SPEED_LINEF_MAX 40

 #define ROTATION_SPEED 40


#define LEFT automaticBehavior.turnLeft();
#define RIGHT90 automaticBehavior.turnRight90();
#define STOP robot.forward(0);


#endif
