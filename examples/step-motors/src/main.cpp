// Example sketch to control a stepper motor with A4988 stepper motor driver
// and Arduino without a library, now with acceleration support
// More info: https://www.makerguides.com
#include <Arduino.h>
#include <protothreads.h>
// Define stepper motor connections and steps per revolution:
#define LEFT_DIR_PIN PIND7
#define LEFT_STEP_PIN PIND6
#define RIGHT_DIR_PIN PIND4
#define RIGHT_STEP_PIN PIND5
#define STEPS_PER_REVOLUTION 2048L
#define RPMS 30
#define MAX_STEPS_PER_SECOND (STEPS_PER_REVOLUTION * RPMS / 60L)
#define STEP_DELAY_MICROSECONDS  450  //(1e6/MAX_STEPS_PER_SECOND)
#define MAX_STEP_DELAY_MICROSECONDS 2000
#define MIN_STEP_DELAY_MICROSECONDS STEP_DELAY_MICROSECONDS
#define WHEEL_DIAMETER 30
#define WHEEL_CIRCUMFERENCE (WHEEL_DIAMETER * PI)
#define STEPS_PER_MM (STEPS_PER_REVOLUTION / WHEEL_CIRCUMFERENCE)
#define MAX_ACCELERATION_STEPS 300
#define DELAY_DELTA ((MAX_STEP_DELAY_MICROSECONDS - MIN_STEP_DELAY_MICROSECONDS)*1.0 / MAX_ACCELERATION_STEPS)

struct StepperMotor : pt
{
    unsigned long tm;
    unsigned long tmend;
    unsigned long  steps;
    int dir;
    void runStep(int steps, int dir);
};
struct SerialData : pt
{
    int steps;
};
void StepperMotor::runStep(int steps, int dir)
{
    this->steps = steps;
    this->dir = dir;
}
StepperMotor stepperMotor;
SerialData ptSerial;
int count = 0;
void setup()
{
    // Declare pins as output:
    Serial.begin(115200);
    pinMode(LEFT_STEP_PIN, OUTPUT);
    pinMode(LEFT_DIR_PIN, OUTPUT);
    pinMode(RIGHT_STEP_PIN, OUTPUT);
    pinMode(RIGHT_DIR_PIN, OUTPUT);
    // move forward
    digitalWrite(LEFT_DIR_PIN, LOW);
    digitalWrite(RIGHT_DIR_PIN, LOW);
    PT_INIT(&stepperMotor);
    PT_INIT(&ptSerial);
    stepperMotor.steps=0;
    Serial.println("Init ok");
   
    
}



int runMotor(StepperMotor *motor)
{
    static float currentDelay =0;
    static unsigned long tm=0;
    static unsigned long tmend=0;
    static unsigned long accelerationSteps = 0;
    static unsigned long constantSpeedSteps = 0;
    
    static unsigned long   steps=0;
    static unsigned long   i=0;
    PT_BEGIN(motor);
   
    

      while (true)
    {

        steps=motor->steps;
        if (steps==0) {
            PT_YIELD(motor);
            // motor->steps=0;
            continue;
        }


        if (motor->steps >= 2 * MAX_ACCELERATION_STEPS)
        {
            accelerationSteps = MAX_ACCELERATION_STEPS;
            constantSpeedSteps = motor->steps - (2 * MAX_ACCELERATION_STEPS);
        }
        else
        {
            accelerationSteps = motor->steps / 2;
            constantSpeedSteps = 0;
        }
        
         currentDelay = MAX_STEP_DELAY_MICROSECONDS;
         tm=micros();
         
         
         constantSpeedSteps=constantSpeedSteps;
         
        
        
        
        for (i = 0; i < steps; i++)
        {
            if (i<accelerationSteps) {
                currentDelay-=DELAY_DELTA;
            } else if (i<accelerationSteps+constantSpeedSteps) {
                currentDelay=MIN_STEP_DELAY_MICROSECONDS;
            } else {
                currentDelay+=DELAY_DELTA;
            }
            digitalWrite(LEFT_STEP_PIN, LOW);
            digitalWrite(RIGHT_STEP_PIN, LOW);
            delayMicroseconds(currentDelay);
            digitalWrite(LEFT_STEP_PIN, HIGH);
            digitalWrite(RIGHT_STEP_PIN, HIGH);
            delayMicroseconds(2);
            PT_YIELD(motor);
        }
        
           
        tmend=micros();
        Serial.println("time: "+String((tmend-tm)/1000)+"ms");
        motor->steps=0;
        // motor->i=0;
        
    }
    PT_END(motor);
    
}

int readSerialData(pt *pt)
{
    PT_BEGIN(pt);
    while (true)
    {
        if (Serial.available() > 0)
        {
            char data = (char)Serial.read();
            if (data=='a')
            {
                PT_WAIT_UNTIL(pt, stepperMotor.steps==0);
                stepperMotor.steps=2048+1024;
                
            }
            
        }
        PT_YIELD(pt);
    }
    PT_END(pt);
}
void loop()
{
   
    PT_SCHEDULE(runMotor(&stepperMotor));
    PT_SCHEDULE(readSerialData(&ptSerial));
    
}