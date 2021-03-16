// bool esp32 = false;
#ifdef ESP32   
    #include <ESP32Encoder.h>
    #include <Arduino.h>
    #include <analogWrite.h>
#else
    #include<Encoder.h>
#endif
class motor
{
private:
public:
    int en1=0,en2=0,dir1=0,dir2=0,pwmPin = 0,curr_pwm = 0,cpr;
    
    int directional_offset = 1;
   
   
    #ifdef ESP32 
        ESP32Encoder *encoder = new ESP32Encoder();
    #else
        Encoder *encoder = new Encoder(0,0);
    #endif
    
    double getReadings()
    {
        #ifdef ESP32
           return (long)encoder->getCount()*directional_offset;
        #else
        
           return encoder->read()*directional_offset;
        #endif
    }
    double getAngle(){
        // return int(((((double)encoder->read()/cpr)*360)+360))%360;
        return int(((this->getReadings()/cpr)*360)+360)%360;
    }
    void setDirectional_offset(int n = 1)
    {
        directional_offset = n;
    }
    void reset()
    {
        
        #ifdef ESP32
            encoder->setCount(0);
        #else 
            encoder->write(0);
        #endif
    }
    void setup()
    {
        pinMode(dir1,OUTPUT);
        pinMode(dir2,OUTPUT);
        pinMode(pwmPin,OUTPUT);
        #ifdef ESP32
            encoder->attachHalfQuad(en1,en2);    
        	ESP32Encoder::useInternalWeakPullResistors=UP;
            analogWriteResolution(pwmPin, 13);//8,9,10,11,12,13,14,15,16 try 
        #endif
        this->reset();
    }
    void forward()
    {
        // Serial.print("Going forward");
        digitalWrite(dir1,HIGH);
        analogWrite(pwmPin,abs(curr_pwm));
        
        digitalWrite(dir2,LOW);
    }
    void backward()
    {
        
        // Serial.println("Going backward");
        digitalWrite(dir1,LOW);
        analogWrite(pwmPin,abs(curr_pwm));
        // Serial.println(curr_pwm);
        digitalWrite(dir2,HIGH);
    }

    void stop()
    {
        // Serial.println("Going stopping");
        digitalWrite(dir1,LOW);
        digitalWrite(dir2,LOW);
        setPWM(1);
    }
    void setPWM(int pwm)
    {
        curr_pwm = pwm;
        if(pwm<0){
            this->backward();
        }
        else if(pwm>0){
            this->forward();
        }
        else{
            stop();
        }
        Serial.print("Speed is ");
        Serial.println(curr_pwm);
        analogWrite(pwmPin,abs(curr_pwm));
    }
    motor()
    {

    }
    motor(int encoder1,int encoder2,int direction1,int direction2,int PwmPin,int cpr, int _directional_offset = 1 )
    {
        directional_offset = _directional_offset;
        en1 = encoder1;
        en2 = encoder2;
        dir1 = direction1;
        dir2 = direction2;
        pwmPin = PwmPin;
        #ifdef ESP32
           
        #else 
            encoder = new Encoder(en1,en2);
        #endif
        this->cpr = cpr;
        setup();
    }
};