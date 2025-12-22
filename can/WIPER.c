#include<lpc21xx.h>
#include "CAN.h"
#include "DELAY.h"
#include "LCD_4.h"
//#define  1<<17
#define ID M.id
#define WP 1<<8
#define MG M.byteA
#define WP_ID 0x1FD
#define WP_ON 0xCCCCCCCC
#define WP_OFF 0x33333333
void pwm_config(void);
void var_pwm(void);
volatile int pulse=60000,flag;
void timer1_config(void);
void TIMER1_INTERRUPT(void)__irq
{
T1IR=0x0f;
PWMMR4=pulse;
PWMLER=1<<4;
if(pulse<=60000)
{
flag=1;
}
if(pulse>=300000)
	flag=0;
	if(flag)
	pulse=pulse+60000;
	else
	pulse=pulse-300000;
 VICVectAddr=0;
}
int main()
{

	CAN2_MSG M;
	lcd_in();
	lcd_sprint("WIPER..");
	CAN2_INIT(1);
	
	pwm_config();
	timer1_config();
	while(1)
	{
		CAN2_RX(&M);
		if(ID==WP_ID)
		{ 
			if(MG==WP_ON)
			{
			lcd_com(0xc0);
			lcd_sprint("ON ");
			PINSEL0|=1<<17;
		
			}
			else if(MG==WP_OFF)
			{
			   	lcd_com(0xc0);
			lcd_sprint("OFF");
			PINSEL0 &=~(1<<17);
	
			}
		}
	}
}
   void pwm_config(void)
{
PWMMR0=20*15000-1;
PWMMR4=7500;
PWMPCR=1<<12;
PWMMCR=0X02;
PWMTCR=0X09;
}
void var_pwm(void)
{
float pulse_time;
for(pulse_time=0.5;pulse_time<2.6;pulse_time+=0.5)
{
PWMMR4=pulse_time*15000;
PWMLER=1<<4;
//delay_milliseconds(100);
}
for(pulse_time=2.5;pulse_time>0.4;pulse_time-=0.5)
{
PWMMR4=pulse_time*15000;
PWMLER=1<<4;
//delay_milliseconds(100);
}
}
void timer1_config(void)
{
VICIntSelect=0;
VICVectCntl0=(1<<5)|5;
VICVectAddr0=(int)TIMER1_INTERRUPT;
T1MR0=6000000-1;
T1MCR=0x03;
T1TCR=1;
VICIntEnable=1<<5;
}
