#include <Servo.h>

//VARIABLE DECLARATIONS

//Servo variables (Servos, incrementor values that dictate servo positions, Arduino pin numbers, and 30 degree boundaries)
Servo servo1;
Servo servo2;
int leftRightIncrementor = 90; //servos start at 90 degrees when code begins
int upDownIncrementor = 90;
int LEFT_RIGHT_SERVO_PIN = 6;
int UP_DOWN_SERVO_PIN = 11;
int LEFT_RIGHT_SERVO_UPPER_LIMIT = 150;
int LEFT_RIGHT_SERVO_LOWER_LIMIT = 30;
int UP_DOWN_SERVO_UPPER_LIMIT = 150;
int UP_DOWN_SERVO_LOWER_LIMIT = 30;

//LDR variables (recorded values and Arduino pin numbers)
int lightValue1 = 0;
int lightValue2 = 0;
int lightValue3 = 0;
int lightValue4 = 0;
int TOP_LEFT_LDR_PIN = A0;
int TOP_RIGHT_LDR_PIN = A1;
int BOTTOM_LEFT_LDR_PIN = A2;
int BOTTOM_RIGHT_LDR_PIN = A3;

//Loop variable
int LOOP_DELAY = 50;

/* This variable is twice the difference between LDR values needed for the servo position to be incremented. 
 * LDR variability is so high that only a "significant" difference will move a servo, and it's multiplied by 2
 * because it's only ever used when averaging two LDR values. 
 */
int LDR_DIFFERENCE = 100;

void setup() {

    //Servo pins are set
    servo1.attach(LEFT_RIGHT_SERVO_PIN);
    servo2.attach(UP_DOWN_SERVO_PIN);

    //LDRs are set to input
    pinMode(TOP_LEFT_LDR_PIN, INPUT);
    pinMode(TOP_RIGHT_LDR_PIN, INPUT);
    pinMode(BOTTOM_LEFT_LDR_PIN, INPUT);
    pinMode(BOTTOM_RIGHT_LDR_PIN, INPUT);

    //Sets up serial monitor (mostly for debugging)
    Serial.begin(9600);

}

void loop() {

    //reads each sensor value and prints it to the serial monitor (for debugging purposes)
    Serial.print(analogRead(TOP_LEFT_LDR_PIN));
    Serial.print(" ");
    Serial.print(analogRead(TOP_RIGHT_LDR_PIN));
    Serial.print(" ");
    Serial.print(analogRead(BOTTOM_LEFT_LDR_PIN));
    Serial.print(" ");
    Serial.print(analogRead(BOTTOM_RIGHT_LDR_PIN));
    Serial.print(" ");
    Serial.print(leftRightIncrementor);
    Serial.print(" ");
    Serial.print(upDownIncrementor);

    //Servo position is continuously set to the Incrementor value
    servo1.write(leftRightIncrementor);
    servo2.write(upDownIncrementor);

    //LDRs are continuously read and each lightValue is then set to the corresponding LDR value
    lightValue1 = analogRead(TOP_LEFT_LDR_PIN);
    lightValue2 = analogRead(TOP_RIGHT_LDR_PIN);
    lightValue3 = analogRead(BOTTOM_LEFT_LDR_PIN);
    lightValue4 = analogRead(BOTTOM_RIGHT_LDR_PIN);

    /* Avg of left sensors is compared to avg of right sensors and that incrementor is changed accordingly.
     * Servos only move when there's a difference of 50+ between the left and right side's averages  
     */
    if ((int)((lightValue1 + lightValue3)/LDR_DIFFERENCE) > (int)((lightValue2 + lightValue4)/LDR_DIFFERENCE)) {
        leftRightIncrementor++;
    }
    else if ((int)((lightValue1 + lightValue3)/LDR_DIFFERENCE) < (int)((lightValue2 + lightValue4)/LDR_DIFFERENCE)) {
        leftRightIncrementor--;
    }

    /* Avg of upper sensors is compared to avg of lower sensors and that incrementor is changed accordingly.
     * Servos only move when there's a difference of 50+ between the upper and lower side's averages  
     */
    if ((int)((lightValue1 + lightValue2)/LDR_DIFFERENCE) > (int)((lightValue3 + lightValue4)/LDR_DIFFERENCE)) {
        upDownIncrementor--;
    }
    else if ((int)((lightValue1 + lightValue2)/LDR_DIFFERENCE) < (int)((lightValue3 + lightValue4)/LDR_DIFFERENCE)) {
        upDownIncrementor++;
    }

    //Sets boundary for the up/down servo between 30 and 150 degrees
    if (upDownIncrementor > UP_DOWN_SERVO_UPPER_LIMIT) {
        upDownIncrementor = UP_DOWN_SERVO_UPPER_LIMIT;
    }
    if (upDownIncrementor < UP_DOWN_SERVO_LOWER_LIMIT) {
        upDownIncrementor = UP_DOWN_SERVO_LOWER_LIMIT;
    }

    //Sets boundary for the left/right servo between 30 and 150 degrees
    if (leftRightIncrementor > LEFT_RIGHT_SERVO_UPPER_LIMIT) {
        leftRightIncrementor = LEFT_RIGHT_SERVO_UPPER_LIMIT;
    }
    if (leftRightIncrementor < LEFT_RIGHT_SERVO_LOWER_LIMIT) {
        leftRightIncrementor = LEFT_RIGHT_SERVO_LOWER_LIMIT;
    }

    //Gives CPU a chance to breathe
    delay(LOOP_DELAY);

}