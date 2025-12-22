#include "DELAY.h"



      /*-------------------definitions-----------------------*/
void delay_seconds(int sec)
{
T0PR=60000000-1;
T0TCR=1;
while(T0TC<sec);
T0TCR=3;
T0TCR=0;
}

void delay_milliseconds(int sec)
{
T0PR=60000-1;
T0TCR=1;
while(T0TC<sec);
T0TCR=3;
T0TCR=0;
}
void delay_microseconds(int sec)
{
T0PR=60-1;
T0TCR=1;
while(T0TC<sec);
T0TCR=3;
T0TCR=0;

}
