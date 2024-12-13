var fs=require("fs");
var rpms=30;
var acc_steps=30;
var steps_per_revolution=2048;
var max_step_delay_microseconds=2000;

    var delay_target=1e6/((rpms/60)*steps_per_revolution);
var acc=(2000-delay_target)*2/((acc_steps-1)*(acc_steps-1));
var arr=[];
for(var i=0;i<acc_steps;i++){
    var delay=i*i*acc/2;
    arr.push(Math.round(delay));
}
fs.writeFileSync("src/speed.h",
`
#pragma once
#include <Arduino.h>
#define RPMS ${rpms}
#define STEPS_PER_REVOLUTION ${steps_per_revolution}
#define MAX_STEP_DELAY_MICROSECONDS ${max_step_delay_microseconds}
#define MAX_ACCELERATION_STEPS ${acc_steps}


#define MAX_STEPS_PER_SECOND ((long)STEPS_PER_REVOLUTION * (long)RPMS / 60L) // Cast to long
#define DELAY_TARGET (1e6 / (long)MAX_STEPS_PER_SECOND) // Cast to long

const int speed_table[] PROGMEM = {${arr.join(",")}};
`);
console.log(arr);