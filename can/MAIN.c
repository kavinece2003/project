#include<lpc21xx.h>
#include "CAN.h"
#include "LCD_4.h"
#include "DELAY.h"
#define SW1 14
#define SW2 15
#define SW3 16
#define FLAG1 v.flag1
#define FLAG2 v.flag2
#define FLAG3 v.flag3
#define LI_ID 0x1FF
#define RI_ID 0x1FE
#define WP_ID 0x1FD
#define LI_ON 0xAAAAAAAA
#define LI_OFF 0x11111111
#define RI_ON 0xBBBBBBBB
#define RI_OFF 0x22222222
#define WP_ON 0xCCCCCCCC
#define WP_OFF 0x33333333
struct flag
{
	int flag1:2;
	int flag2:2;
	int flag3:2;
};
								
int main()
{
	CAN2_MSG M;
	struct flag v;
	FLAG1=0;
	FLAG2=0;
	FLAG3=0;
	lcd_in();
	lcd_rot_str("BODY CONTROL MODULES IN AUTOMOTIVES...");
	delay_milliseconds(500);
	lcd_com(0x01);
		delay_milliseconds(500);
		lcd_com(0x80);
	lcd_sprint("INITIALIZING....");
	delay_milliseconds(500);
	lcd_com(0x01);

	lcd_com(0x80);
	lcd_sprint("LI");
	lcd_com(0x84);
	lcd_sprint("RI");
	lcd_com(0x88);
	lcd_sprint("WP");
	lcd_com(0xc0);
	lcd_sprint("OFF");
	lcd_com(0xc4);
	lcd_sprint("OFF");
	lcd_com(0xc8);
	lcd_sprint("OFF");
   	CAN2_INIT(1);
	while(1)
	{
	if(((IOPIN0>>SW1)&1)==0)
	{
		delay_milliseconds(200);
	
		if(FLAG1==0)
		{
			M.id=LI_ID;
			M.rtr=0;
			M.dlc=4;
			M.byteA=LI_ON;
			CAN2_TX(M);
			lcd_com(0xc0);
	lcd_sprint("ON ");
			FLAG1=1;
		}
		else
		{
			M.id=LI_ID;
			M.rtr=0;
			M.dlc=4;
			M.byteA=LI_OFF;
			CAN2_TX(M);
			lcd_com(0xc0);
	lcd_sprint("OFF");
			FLAG1=0;
		}
		
		while(((IOPIN0>>SW1)&1)==0);
	}
	if(((IOPIN0>>SW2)&1)==0)
	{	
		delay_milliseconds(200);
		if(FLAG2==0)
		{
			M.id=RI_ID;
			M.rtr=0;
			M.dlc=4;
			M.byteA=RI_ON;
			CAN2_TX(M);
				lcd_com(0xc4);
	lcd_sprint("ON ");
			FLAG2=1;
		}
		else
		{
			M.id=RI_ID;
			M.rtr=0;
			M.dlc=4;
			M.byteA=RI_OFF;
			CAN2_TX(M);
				lcd_com(0xc4);
	lcd_sprint("OFF");
			FLAG2=0;
		}
		
		while(((IOPIN0>>SW2)&1)==0);
	}
	if(((IOPIN0>>SW3)&1)==0)
	{	
		delay_milliseconds(200);
		if(FLAG3==0)
		{
			M.id=WP_ID;
			M.rtr=0;
			M.dlc=4;
			M.byteA=WP_ON;
			CAN2_TX(M);
			lcd_com(0xc8);
	lcd_sprint("ON ");
			FLAG3=1;
		}
		else
		{
			M.id=WP_ID;
			M.rtr=0;
			M.dlc=4;
			M.byteA=WP_OFF;
			CAN2_TX(M);
			lcd_com(0xc8);
	lcd_sprint("OFF");
			FLAG3=0;
		}
	
		while(((IOPIN0>>SW3)&1)==0);
	}
}
	}
