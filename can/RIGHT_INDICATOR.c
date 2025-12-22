#include<lpc21xx.h>
#include "CAN.h"
#include"LCD_4.h"
#define R_INDICATOR 1<<17
#define ID M.id
#define MG M.byteA
#define RI_ID 0x1FE
#define RI_ON 0xBBBBBBBB
#define RI_OFF 0x22222222

int main()
{
	CAN2_MSG M;

	lcd_in();
	IODIR0|=R_INDICATOR;
	IOSET0=R_INDICATOR;
	lcd_com(0x80);
	lcd_sprint("RIGHT INDICATOR");
		CAN2_INIT(1);
	while(1)
	{
		CAN2_RX(&M);
		if(ID==RI_ID)
		{
			if(MG==RI_ON)
			{
				lcd_com(0xc0);
			lcd_sprint("      ");
			lcd_com(0xc0);
			lcd_sprint("ON");
				IOCLR0=R_INDICATOR;	}
			else if(MG==RI_OFF)
			{
			lcd_com(0xc0);
			lcd_sprint("OFF");
				IOSET0=R_INDICATOR;	}
		}
	}
}
