#ifndef SEGMENT_H
#define SEGMENT_H

// 0x 1 2 3 4 5 6 7 8
// 0x A B C D E F G .
#define ZERO 0b00000011
#define ONE 0b10011111
#define TWO 0b00100101
#define TRHEE 0b00001101
#define FOUR 0b10011001
#define FIVE 0b01001001
#define SIX 0b01000001
#define SEVEN 0b00011111
#define EIGHT 0b00000001
#define NINE 0b00001001

class Segment{
  
private:

  int m_pinClock, m_pinData, m_pinLatch;

  int m_pinSeg1, m_pinSeg2, m_pinSeg3, m_pinSeg4;

  int digit_size, i;

  bool printing;

  long temp;

  unsigned long m_new, m_current;

  int convert_digit(int d) const{

      switch (d){

        case 0:
          return ZERO;
        
        case 1:
          return ONE;
          
        case 2:
          return TWO;

        case 3:
          return TRHEE;

        case 4:
          return FOUR;

        case 5:
          return FIVE;

        case 6:
          return SIX;

        case 7:
          return SEVEN;

        case 8:
          return EIGHT;

        case 9:
          return NINE;

        default:

          return -1;
      }
  }


public:

  Segment(int clock, int data, int latch, int seg1, int seg2, int seg3, int seg4)
  : 
  m_pinClock(clock), m_pinData(data), m_pinLatch(latch), 
  m_pinSeg1(seg1), m_pinSeg2(seg2), m_pinSeg3(seg3), m_pinSeg4(seg4),
  m_current(0), m_new(0), i(0),
  printing(false)
  {
  }

  void init(){

    pinMode(m_pinClock, OUTPUT);
    pinMode(m_pinData, OUTPUT);
    pinMode(m_pinLatch, OUTPUT);
    pinMode(m_pinSeg1, OUTPUT);
    pinMode(m_pinSeg2, OUTPUT);
    pinMode(m_pinSeg3, OUTPUT);
    pinMode(m_pinSeg4, OUTPUT);

    digitalWrite(m_pinLatch, HIGH);

    digitalWrite(m_pinSeg1, LOW);
    digitalWrite(m_pinSeg2, LOW);
    digitalWrite(m_pinSeg3, LOW);
    digitalWrite(m_pinSeg4, LOW);
  }


  void display(long digit){

    if ( !printing ){

      temp = digit;
  
      digit_size = 0;
  
      while (temp > 0 ){
  
        temp /= 10;
  
        ++digit_size;
      }
      
      if (digit_size > 3)
        digit_size = 4;

      i = 0;

      temp = digit;

      printing = true;
    }

 
      m_current = millis();
  
      if (m_current - m_new >= 1){
  
        m_new = m_current;
        
        int d = temp % 10;
        temp /= 10;

        d = convert_digit(d);
    
        digitalWrite(m_pinSeg1, LOW);
        digitalWrite(m_pinSeg2, LOW);
        digitalWrite(m_pinSeg3, LOW);
        digitalWrite(m_pinSeg4, LOW);
    
        digitalWrite(m_pinLatch, LOW);
        shiftOut(m_pinData, m_pinClock, LSBFIRST, d);
        digitalWrite(m_pinLatch, HIGH);
    
        switch(i){
    
              case 0: 
                  digitalWrite(m_pinSeg4, HIGH);
                  break;
            
              case 1:
                  digitalWrite(m_pinSeg3, HIGH);
                   break;
                
              case 2:
                  digitalWrite(m_pinSeg2, HIGH);
                  break;
      
              case 3:
                  digitalWrite(m_pinSeg1, HIGH);
                  break;
    
              default:
                  break;
        }

         ++i;

         if (i >= digit_size )
            printing = false;
    }
  }
};


#endif
