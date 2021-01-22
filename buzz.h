#ifndef BUZZ_H
#define BUZZ_H

class Buzz{

private:

  int m_pin;
  int m_volt;
  unsigned long m_new, m_current;

  public:

    Buzz(int pin)
    {
      m_volt = HIGH;
      m_new = 0;
      m_current = 0;
      m_pin = pin;
      
     }

   void init(){

    pinMode(m_pin, OUTPUT);
   }

    // 500 --> 9k   Hz
    void play(int hz){

        //digitalWrite(m_pin, m_volt);

        m_current = micros();

        if (m_current - m_new >= hz){

          if ( m_volt == HIGH )
            m_volt = LOW;

          else
            m_volt = HIGH;

            m_new = m_current;

           digitalWrite(m_pin, m_volt);
        }
    }

    void play2(int hz){

        digitalWrite(m_pin, HIGH);
        delayMicroseconds(hz);
        digitalWrite(m_pin, LOW);
        delayMicroseconds(hz);
    }
  };

  
#endif
