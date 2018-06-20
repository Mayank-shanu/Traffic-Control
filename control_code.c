#include<reg52.h>
#define RD1 1
#define RD2 2
#define R 1
#define Y 2
#define G 3
#define r1_red "Road 1 : STOP!"
#define r1_yellow "Road 1 : SLOW!"
#define r1_green "Road 1 : GO!"
#define r2_red "Road 1 : STOP!"
#define r2_yellow "Road 1 : SLOW!"
#define r2_green "Road 1 : GO!"
#define init_count 9
#define buz_delay 80


 //def p0 as counter or seven segment
//def P2 as led
//def p2.7 as buzzer
//def P2.3 as  seven_segment
//def P3 as rs,rd/wr,en
//P1 as lcd

sbit led_red_rd1 = P2^0;
sbit led_yellow_rd1 = P2^1;
sbit led_green_rd1 = P2^2;

sbit led_red_rd2 = P2^4;
sbit led_yellow_rd2 = P2^5;
sbit led_green_rd2 = P2^6;

sbit buz = P2^7;
sbit seven_segment = P2^3;

sbit RS = P3^0;
sbit RD_WR = P3^1;
sbit EN = P3^2;

void assign_led(int rd1_lgt[3],int rd2_lgt[3]);
void delay(int k);
void command_lcd(char ch);
void data_lcd(char ch[16]);
void lcd_control(char rd1_mess[16],char re2_mess[16]);
void initialize_lcd();
void buzzer_blink_seven_seg();
void counter(int);
void control(int);

void main(){
	   P1=P2=P3=P0=0x00;
	   initialize_lcd();

	   while(1){
	   		control(R);
			delay(100);
			control(G);
			delay(100);
	   }

}

void control(int status){//,int road=RD1){
	//only rd1 is checked
	int red[3]={1,0,0};
	int green[3]={0,0,1};
	int on[3] = {1,1,1};
	int off[3]={0,0,0};
	switch(status){
		case R:	assign_led(red,green);
				lcd_control(r1_red,r2_green);
				counter(R);
				break;
		case G:	assign_led(green,red);
				lcd_control(r1_green,r2_red);
				counter(G);
				break;
		default:	while(1){
						assign_led(on,on);
						delay(250);
						assign_led(off,off);
						delay(250);	
					}
				break;
	}
}

void assign_led(int rd1_lgt[3],int rd2_lgt[3]){

		   led_red_rd1 = rd1_lgt[0];
		   led_yellow_rd1 = rd1_lgt[1];
		   led_green_rd1 = rd1_lgt[2];

		   led_red_rd2 = rd2_lgt[0];
		   led_yellow_rd2 = rd2_lgt[1];
		   led_green_rd2 = rd2_lgt[2];

}
void delay(int k){
	int i,j;
	for(i=0;i<k;++i){
		for(j=0;j<k;++j);
	}
}

void lcd_control(char rd1_mess[16],char rd2_mess[16]){

	command_lcd(0x80);
	delay(10);
	data_lcd(rd1_mess);

	command_lcd(0x0c0);
	delay(10);
	data_lcd(rd2_mess);
}

void command_lcd(char ch){
	P1 = ch;
	RS = 0;
	RD_WR = 0;
	EN = 1;
	delay(5);
	EN=0;
	delay(2);
}
void data_lcd(char ch[16]){
	int i=0;
	while(i<=15){
		
		P1 = ch[i];
		RS = 1;
		RD_WR = 0;
		EN = 1;
		delay(5);
		EN=0;
		delay(10);
		++i;
	}  
}
void initialize_lcd(){
	command_lcd(0x38);
	delay(10);

	command_lcd(0x01);
	delay(10);

	command_lcd(0x0f);
	delay(10);

	command_lcd(0x0e);
	delay(10);

	command_lcd(0x3c);
	delay(10);

	command_lcd(0x80);
	delay(10);
}
void counter(int stat){
	int i=10;
	int red[3]={1,0,0};
	int yellow[3]={0,1,0};
	char equivalent_no[10]={0xC0,0xf9,0xA4,0xB0,0x99,0x92,0x82,0xf8,0x80,0x98};
	seven_segment = 1;

	for(i = 9;i>=0;--i){
		 P0 = equivalent_no[i];
		 delay(150);
		 if(i==5){
		 	if(stat == R){
				assign_led(red,yellow);	
			}
			else if(stat == G){
				assign_led(yellow,red);	
			}
		 }
		 if(i<=5){
		 	buzzer_blink_seven_seg();
		 }
	}
}

void buzzer_blink_seven_seg(){
	  buz= 1;
	  seven_segment = 0;
	  delay(buz_delay);
	  seven_segment = 1;
	  buz=0;
}







