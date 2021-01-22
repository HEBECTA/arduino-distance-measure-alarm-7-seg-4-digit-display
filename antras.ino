
#define BUZZ 2
#define TRIG 8
#define ECHO 9

#define CLOCK 11 // SHCP SHIFT REGISTER CLOCK INPUT
#define DATA 12 // 
#define LATCH 13 // STCP STORAGE REGISTER CLOCK INPUT

// 4 digit 8 sgements display module
// common anodes for 4 digits
#define DIG1 4
#define DIG2 5
#define DIG3 6
#define DIG4 7

bool metric_system = true;

#include "buzz.h"
#include "distance.h"
#include "Segment.h"

Buzz buzz = Buzz(BUZZ);
Distance distance = Distance(TRIG, ECHO);
Segment segment = Segment(CLOCK, DATA, LATCH, DIG1, DIG2, DIG3, DIG4);

void buttonPressed();

void setup() {                
 
  buzz.init();
  distance.init();
  segment.init();

  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), buttonPressed, CHANGE);

  Serial.begin(115200);
}

void loop() {

  long cm = distance.cm_dist();

  if (!metric_system)
    cm *= 2.54;

  // input, val low, val high, desired low, desired high
  int sound = map(cm, 0, 400, 200, 20000);

  buzz.play(sound);

  segment.display(cm);

  Serial.print("cm ");
  Serial.print(cm);
  Serial.println();
  Serial.print("hz ");
  Serial.println(sound);

}

void buttonPressed(){

  //distance.change_measure_system();
  metric_system != metric_system;

}
