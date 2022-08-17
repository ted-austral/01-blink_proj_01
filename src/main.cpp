#include <Arduino.h>

/*
 *  Project 01-blink_proj_01
 *      IntroCom - Austral - 2022 - EAM
 * 
 *      Each "sample' time, reads both pushbuttons as an integer number named "num"
 *      After reading, prints num in serial monitor and blinks LED num+1 number of periods of "pulse" time on and off
 *      Tact switch connected to +VDD so must engage pulldown resistor, subsequents reads gives a HIGH for a push botton closed
 *      Austral 2022 - IntroCom - EAM
 */

// Array of switches that compose the number

static const unsigned char bnum[NUM_BIT] =
{
    PUSH_01, PUSH_00
};

void
setup(void)
{
    int i;

    pinMode(INTLED,OUTPUT);
    digitalWrite(INTLED,LOW);

    for( i = 0; i < NUM_BIT; ++i )
        pinMode( bnum[i], INPUT_PULLDOWN );
    Serial.begin(BAUD);

}

void
loop(void)
{
    int count,num;

    num = 0;
    for( count = 0; count < NUM_BIT; ++count )
        bitWrite(num, count, digitalRead( bnum[count] ));
    Serial.println(num);

    num = 2*(num+1);
    for( count = 0; count < sample/pulse; ++count )
    {
        if( num > 0 )
        {
            if( num%2 != 0 )
            {
                digitalWrite(INTLED,HIGH);
            }
            else
            {
                digitalWrite(INTLED,LOW);
            }
            --num;
        }
        delay(pulse);
    }
}
