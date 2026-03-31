#include <REGX52.H>
#include "Buzzer.h"
#include "Timer0.h"
#define SPEED 700
#define P	37
#define L1	1
#define L1_	2
#define L2	3
#define L2_	4
#define L3	5
#define L4	6
#define L4_	7
#define L5	8
#define L5_	9
#define L6	10
#define L6_	11
#define L7	12
#define M1	13
#define M1_	14
#define M2	15
#define M2_	16
#define M3	17
#define M4	18
#define M4_	19
#define M5	20
#define M5_	21
#define M6	22
#define M6_	23
#define M7	24
#define H1	25
#define H1_	26
#define H2	27
#define H2_	28
#define H3	29
#define H4	30
#define H4_	31
#define H5	32
#define H5_	33
#define H6	34
#define H6_	35
#define H7	36
void Delay(unsigned int xms);
sbit Buzzer=P2^5;
unsigned int FreqTable[]={
63777,63872, 63969, 64054, 64140, 64216, 64291, 64360, 64426, 64489, 64547,
64607, 64655, 64704, 64751, 64795, 64837, 64876, 64913, 64947, 64981, 65012, 
65042, 65070, 65095, 65120, 65144, 65166, 65186, 65206, 65225, 65242, 65259,
65274, 65289, 65303,0/*休止符0第37位*/};
unsigned char FreqSelect,MusicSelect;
unsigned char code Music[]={
	//第一小节
	M3,16,M2,16,M1,16,L7,16,L6,16,L5,16,L6,16,L7,16,
	//第二小节
	M3,16,M2,16,M1,16,L7,16,L6,16,L5,16,L6,16,L7,16,
	//第三小节
	H1, 4, M7, 4, H1, 4, M3, 4, M5, 8, M6, 4, M7, 4,
	H1, 8, H3, 8, H5, 4, H3, 4, H5, 4, H6, 4,
	H4, 4, H3, 4, H2, 4, H4, 4, H3, 4, H2, 4, H1, 4, M7, 4,
	M6, 4, M5, 4, M4, 4, H1, 4, M7, 8, H1, 4, H2, 4,
	//第四小节
	H5, 4, H3, 2, H4, 2, H5, 4, H3, 2, H4, 2, H5, 2, M5, 2, M6, 2, M7, 2, H1, 2, H2, 2, H3, 2, H4, 2,
	H3, 4, H1, 2, H2, 2, H3, 4, H3, 2, H4, 2, H5, 2, H6, 2, H5, 2, H4, 2, H5, 2, H1, 2, M7, 2, H1, 2,
	M6, 4, H1, 2, M7, 2, M6, 4, M5, 2, M4, 2, M5, 2, M4, 2, M3, 2, M4, 2, M5, 2, M6, 2, M7, 2, H1, 2,
	M6, 4, H1, 2, M7, 2, H1, 4, M7, 2, M6, 2, M7, 2, M6, 2, M7, 2, H1, 2, H2, 2, H3, 2, H4, 2, H5, 2,
	//第五小节
	H5, 4, H3, 2, H4, 2, H5, 4, H3, 2, H4, 2, H5, 2, M5, 2, M6, 2, M7, 2, H1, 2, H2, 2, H3, 2, H4, 2,
	H3, 4, H1, 2, H2, 2, H3, 4, M3, 2, M4, 2, M5, 2, M6, 2, M5, 2, M4, 2, M5, 2, H1, 2, M7, 2, H1, 2,
	M6, 4, H1, 2, M7, 2, M6, 4, M5, 2, M4, 2, M5, 2, M4, 2, M3, 2, M4, 2, M5, 2, M6, 2, M7, 2, H1, 2,
	M6, 4, H1, 2, M7, 2, H1, 4, M7, 2, M6, 2, M7, 2, M6, 2, M7, 2, H1, 2, H2, 2, H1, 2, M7, 4,
	0xFF	//终止标志
};

void main()
{Timer0_Init();
while(1){
	if(Music[MusicSelect]!=0xFF)	//如果不是停止标志位
		{FreqSelect=Music[MusicSelect];
		MusicSelect++ ;	
		Delay(SPEED/8*Music[MusicSelect]);//
		MusicSelect++;	
		TR0=0;
		Delay(5);
		TR0=1;
	
		
	}
		}
	}
void Tmier0_Rountine() interrupt 1
{	static unsigned int T0Count;
	if (FreqTable[FreqSelect]!=0){
	TL0 = FreqTable[FreqSelect]%256;				//设置定时初始值
	TH0 = FreqTable[FreqSelect]/256;				//设置定时初始值
	Buzzer=!Buzzer;}
	}



