int MaxVol = 252; //voltage for bit 1
int LowTime = 550;  //Time for one bit
int MaxBits = 20; //No more than MaxBits in a row

bool jump = true;
int biti = 1;
unsigned long t0,t1,tTotal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(230400);

  ADCSRA = 0;             // clear ADCSRA register
  ADCSRB = 0;             // clear ADCSRB register
  ADMUX |= (0 & 0x07);    // set A0 analog input pin
  ADMUX |= (1 << REFS0);  // set reference voltage
  ADMUX |= (1 << ADLAR);  // left align ADC value to 8 bits from ADCH register

  // sampling rate is [ADC clock] / [prescaler] / [conversion clock cycles]
  // for Arduino Uno ADC clock is 16 MHz and a conversion takes 13 clock cycles
  //ADCSRA |= (1 << ADPS2) | (1 << ADPS0);    // 32 prescaler for 38.5 KHz
  //ADCSRA |= (1 << ADPS2);                     // 16 prescaler for 76.9 KHz
  ADCSRA |= (1 << ADPS1) | (1 << ADPS0);    // 8 prescaler for 153.8 KHz

  ADCSRA |= (1 << ADATE); // enable auto trigger
  ADCSRA |= (1 << ADIE);  // enable interrupts when measurement complete
  ADCSRA |= (1 << ADEN);  // enable ADC
  ADCSRA |= (1 << ADSC);  // start ADC measurements
}

ISR(ADC_vect){
  byte x = ADCH;  // read 8 bit value from ADC
  
  if(x > MaxVol/2 && biti == 0){  //If was 0 and now is 1
    t1 = micros();  //How much time was 0?
    tTotal = t1-t0;
    tTotal = tTotal / LowTime;  //How many bits are this time?
    for(int i = 0; i < tTotal; i++){
      Serial.print("0");
      jump = false;
    }
    t0 = t1;
    biti = 1; //Set actual bit as 1
  }else{
    if(x < MaxVol/2 && biti == 1){  //If was 1 and now is 0
      t1 = micros();  //How much time was 1?
      tTotal = t1-t0;
      tTotal = tTotal / LowTime;  //How many bits are this time?
      for(int i = 0; i < tTotal; i++){
        Serial.print("1");
        jump = false;
      }
      t0 = t1;
      biti = 0; //Set actual bit as 0
    }else{
      t1 = micros();  //How much time without changing bit?
      tTotal = t1-t0;
      if(tTotal > LowTime * MaxBits && jump == false){
        Serial.println(); //Jump to next row
        jump = true;
      }
    }
  }
}
  
void loop() {
  // put your main code here, to run repeatedly:
}
