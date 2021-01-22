#ifndef DISTANCE_H
#define DISTANCE_H
//bool metric_system = true;
class Distance{
  
private:

  int m_pinTrig, m_pinEcho;
  long dist;
  unsigned long m_new, m_current;

  //bool metric_system;

public:
  
  Distance(int trig, int echo)
  : m_pinTrig(trig), m_pinEcho(echo),
  m_new(0), m_current(0)
  //metric_system(true)
  { 
  }

  void change_measure_system(){
/*
    if (metric_system)
      metric_system = false;

    else
      metric_system = true;*/
  }

  void init(){

    pinMode(m_pinTrig, OUTPUT);
    pinMode(m_pinEcho, INPUT);

    digitalWrite(m_pinTrig, LOW);
   }

  long cm_dist(){

    m_current = millis();

    digitalWrite(m_pinTrig, HIGH);

    if (m_current - m_new >= 100 ){

      digitalWrite(m_pinTrig, LOW);

      m_new = m_current;

      long duration = pulseIn(m_pinEcho, HIGH);
 
      // Convert the time into a distance
      //if (metric_system) 
        dist = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

     // else
       // dist = (duration/2) / 74;
      
      return dist;
    }

    return dist;
  }
};

#endif
