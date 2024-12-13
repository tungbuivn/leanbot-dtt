// Example sketch to control a stepper motor with A4988 stepper motor driver
// and Arduino without a library, now with acceleration support
// More info: https://www.makerguides.com
#ifdef ARDUINO
#include <Arduino.h>
#include <protothreads.h>
#include "speed.h"
#endif
// Define stepper motor connections and steps per revolution:
#define LEFT_DIR_PIN PIND7
#define LEFT_STEP_PIN PIND6
#define RIGHT_DIR_PIN PIND4
#define RIGHT_STEP_PIN PIND5

const float num_stp = 98;

struct StepperMotor : pt
{
    unsigned long tm;
    unsigned long tmend;
    unsigned long steps;
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
float constant_speed_time = 0;
float remaining_time = 0;
float accelleration_time = 0;
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

    Serial.println("Step delay: " + String(DELAY_TARGET) + "us");

    Serial.println("Steps per revolution: " + String(STEPS_PER_REVOLUTION));
    Serial.println("RPM: " + String(RPMS));
    Serial.println("Steps per second: " + String(MAX_STEPS_PER_SECOND));
}

float delta = 5;
float last_delay = 0;
int runMotor(StepperMotor *motor)
{
    static int currentDelay = 0;
    static unsigned long accelerationSteps = 0;
    static unsigned long constantSpeedSteps = 0;
    static int last_time = 0;
    static long long sum_time = 0;
    static unsigned long steps = 0;
    static unsigned long i = 0;
    static unsigned long j = 0;
    PT_BEGIN(motor);

    while (true)
    {

        steps = motor->steps;
        if (steps == 0)
        {
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

        sum_time=0;
        j = -1;
        for (i = 0; i < steps; i++)
        {
            if (i < accelerationSteps)
            {
                currentDelay = MAX_STEP_DELAY_MICROSECONDS - pgm_read_word(&speed_table[i]);
                last_time = currentDelay;
            }
            else if (i < accelerationSteps + constantSpeedSteps)
            {
                currentDelay = DELAY_TARGET;
                // Serial.println("total_time: "+String(currentDelay));
            }
            else
            {
                j++;

                currentDelay = last_time + pgm_read_word(&speed_table[j]);
            }
            // Serial.println("Current delay: "+String(currentDelay));

            digitalWrite(LEFT_STEP_PIN, LOW);
            digitalWrite(RIGHT_STEP_PIN, LOW);
            delayMicroseconds(currentDelay - 2);
            digitalWrite(LEFT_STEP_PIN, HIGH);
            digitalWrite(RIGHT_STEP_PIN, HIGH);
            delayMicroseconds(2);
            sum_time += currentDelay;
            //    total_time+=currentDelay;
            PT_YIELD(motor);
        }

       
        Serial.println("time: " + String((float)(sum_time) / 1000) + "ms " + "check time: " + String(steps * DELAY_TARGET / 1000) + "ms");

        motor->steps = 0;
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
          
            if (data == ' ')
            {
                PT_WAIT_UNTIL(pt, stepperMotor.steps == 0);
                stepperMotor.steps = 2*2048;
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