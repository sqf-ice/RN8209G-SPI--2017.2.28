#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "RN8209G_SPI.h"	
#include "usmart.h"

 
/************************************************

************************************************/

 				 	
//Ҫд�뵽W25Q64���ַ�������
const u8 TEXT_Buffer[]={"WarShipSTM32 SPI TEST"};
//extern u8 address;
//u8 BUF_len[8];
//u32 BUF_ReceiveData[32];//�����Ĵ�����ֵ����0��31��ʼ���棬
//u32 *data=BUF_ReceiveData;
//u8*len=BUF_len;
extern  float  RMSIAreg ;
extern  float  PowerPAreg ;
extern  float  RMSUreg  ;
extern float KiA;
extern  float  KiB  ;
extern  float  Ku		;
extern  float  Kp   ;
extern  float TempU      ;
extern  float TempIA     ;
extern  float TempPowerPA;


u32  data_r[4];
u32  *p= &data_r[0];
u8 mode_key=0;

__align(4) u8 dtbuf[50]; 



//u8*len;
 int main(void)
 {	  
  	delay_init();	    	 //��ʱ������ʼ��	  
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
  	uart_init(9600);	 	//���ڳ�ʼ��Ϊ115200
	  usmart_dev.init(SystemCoreClock/1000000);	//��ʼ��USMART		
	 
//	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
  	LCD_Init();			   	//��ʼ��LCD 	
	 
	KEY_Init();				//������ʼ��
	POINT_COLOR=RED;	
	LCD_ShowString(5,40,130,24,24,"Urms(24H) :"); 
	LCD_ShowString(5,70,130,24,24,"Iarms(22H):"); 
	LCD_ShowString(5,100,130,24,24,"PowA(26H) :"); 
	
	LCD_ShowString(20,150,60,24,24,"U :"); 
	LCD_ShowString(20,180,60,24,24,"IA:"); 
	LCD_ShowString(20,210,60,24,24,"PA:"); 
	
	LCD_ShowString(220,150,20,24,24,"V"); 
	LCD_ShowString(220,180,20,24,24,"A"); 
	LCD_ShowString(220,210,20,24,24,"W");
	 
	LCD_ShowString(20,240,60,24,24,"Ku:"); 
	LCD_ShowString(20,265,60,24,24,"Ki:"); 
	LCD_ShowString(20,295,60,24,24,"Kp:"); 
	 
	 
	RN8209G_SPI_config( );
	RN8209_WriteData(0xEA,0XFA);//�����λ
	delay_ms(50);
	RN8209_WriteData(0xEA,0XE5);//дʹ��
	delay_ms(50);
	RN8209_Parameter_Adjust();//У���һ������������
//		delay_ms(10);
//		
//		RN8209_ActivePower_Adjust();//У���2.1���������������й�У��
//		delay_ms(10);
//    
//		RN8209_ReactivePower_Adjust();//У���2.2���������������޹�У��
//		delay_ms(10);
//		
//		RN8209_Rms_Adjust();//У���3����������������ЧֵУ��
//		delay_ms(50);
//	 
	while(1)
	{
		KEY_Scan(0);
		if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0)&&(mode_key==0))//����֮�󣬼���Kֵ
		{ 
			POINT_COLOR=BLUE;
			LCD_ShowString(50,10,130,24,24,"  Count_Kx         "); 		
			delay_ms(50);			
			RN8209_Count_Kx();                                                 		                                                        
			sprintf((char *)dtbuf,"%f       ",Ku);                             
		  LCD_ShowString(100,240,120,24,24,dtbuf);                            
			                                                                   
			sprintf((char *)dtbuf,"%f       ",KiA);
			LCD_ShowString(60,265,200,24,24,dtbuf);
			
			
			sprintf((char *)dtbuf,"%f       ",Kp);
			LCD_ShowString(100,295,120,24,24,dtbuf); 
			delay_ms(1000);	
			mode_key=1;
		}
		
		if((GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)==0)&&(mode_key==1))//�ٴΰ���֮����K�����ѹ��������
		{
			POINT_COLOR=BLUE;
			LCD_ShowString(50,10,130,24,24,"  PowerEnergyCount         "); 
			mode_key=0;
			RN8209_PowerEnergyCount();

			sprintf((char *)dtbuf,"%f       ",TempU); 
			LCD_ShowString(100,150,120,24,24,dtbuf); 
			
			sprintf((char *)dtbuf,"%f      ",TempIA); 
			LCD_ShowString(100,180,120,24,24,dtbuf); 
			
			sprintf((char *)dtbuf,"%f       ",TempPowerPA); 
			LCD_ShowString(100,210,120,24,24,dtbuf); 
			delay_ms(1000);		
		}
		POINT_COLOR=BLUE;
		LCD_ShowString(50,10,130,24,24,"present value"); //һ�տ�ʼ����ȡ�Ĵ�����ֵ
		
		RN8209_KZ( ); //�����ǲ�������
//		RMSIAreg=RN8209_ReadData(IARMS);//����Aͨ����Чֵ
//	  PowerPAreg=RN8209_ReadData(PowerPA);//�й�����Aͨ��
//	  RMSUreg=RN8209_ReadData(URMS);//��ѹͨ����Чֵ
		
		RMSIAreg=RN8209_ReadData(0x30);//����Aͨ����Чֵ
//	  PowerPAreg=RN8209_ReadData(31H);//�й�����Aͨ��
	  RMSUreg=RN8209_ReadData(0x32);//��ѹͨ����Чֵ
				
		sprintf((char *)dtbuf,"%f       ",RMSUreg);
		LCD_ShowString(140,40,130,24,24,dtbuf); 
		
		sprintf((char *)dtbuf,"%f       ",RMSIAreg);
		LCD_ShowString(140,70,130,24,24,dtbuf); 
		
		sprintf((char *)dtbuf,"%f       ",PowerPAreg);
		LCD_ShowString(140,100,130,24,24,dtbuf); 
		
		
		RN8209_PowerEnergyCount();
		sprintf((char *)dtbuf,"%f      ",TempIA); 
		LCD_ShowString(100,180,120,24,24,dtbuf); 		
		
		
		
		
//		RN8209_ReadData(0x00,&data);//��ϵͳ�Ĵ���
//		delay_ms(10);
//		RN8209_ReadData(0x02,&data);//����Ƶ��
//		delay_ms(10);
//		RN8209_ReadData(0x0E,&data);//������ͨ��A����ЧֵУ������
//		delay_ms(10);
//		RN8209_ReadData(0x20,&data);//�й��������
//      delay_ms(10);
//		RN8209_ReadData(0x22,&data);//����Aͨ����Чֵ
//		delay_ms(10);        ����������
//		RN8209_ReadData(0x24);//��ѹͨ����Чֵ
//		delay_ms(5);
//		delay_ms(10);
//		RN8209_ReadData(0x25,&data);//����ѹƵ�ʼĴ���
//		delay_ms(10);
//		RN8209_ReadData(0x26,&data);//�й�����Aͨ��
//		delay_ms(10);
//		RN8209_ReadData(0x29,&data);//���й�����
//		delay_ms(10);
//		RN8209_ReadData(0x30,&data);//������ͨ��A��ADC
//		delay_ms(10);
//		RN8209_ReadData(0x32,&data);//����ѹͨ����ADC
//		delay_ms(10);
//		RN8209_ReadData(0x2b,&data);
//		 delay_ms(10);
//		RN8209_ReadData(0x2c,&data);
//		delay_ms(10);
//		RN8209_ReadData(0x35,&data);//����ѹƵ�ʼĴ���2

		
//		RN8209_readIA_RMS( ); 


	


//	  data_r[0]=0;//�´�������ʱ�򣬾�������
//		data_r[1]=0;
//		data_r[2]=0;
//		data_r[3]=0;
////		RN8209_ReadData(0x7F,data_r);//ID
////		RN8209_ReadData(0x22,data_r);//����Aͨ����Чֵ
////		delay_ms(200);
////		printf("   %x \r\n",*data_r); //��ʾID		
//		data_r[0]=0;//�´�������ʱ�򣬾�������
//		data_r[1]=0;
//		data_r[2]=0;
//		data_r[3]=0;
		
		
		
		
		
		
		
//		USART_SendData(USART1,data_r );
//		
		

//			RN8209_ReadData(0x00,&data);
//			delay_ms(10);
//	  	RN8209_ReadData(0x01,&data);//���������������ϰ汾
//			delay_ms(10); 
//			RN8209_ReadData(0x02,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x03,&data);
//			delay_ms(10);      
//			RN8209_ReadData(0x04,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x05,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x06,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x07,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x08,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x09,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x0a,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x0b,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x0c,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x0d,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x0e,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x0f,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x10,&data);
//			delay_ms(10); 
//			RN8209_ReadData(0x11,&data);
//			delay_ms(10); 
//	  	RN8209_ReadData(0x12,&data);
//			delay_ms(10); 
//	  	RN8209_ReadData(0x13,&data);
//			delay_ms(10); 
//	  	RN8209_ReadData(0x14,&data);
//			delay_ms(10); 
//			RN8209_ReadData(0x15,&data);//���������������ϰ汾
//			delay_ms(10); 
//			RN8209_ReadData(0x16,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x17,&data);
//			delay_ms(10);      
//			RN8209_ReadData(0x20,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x21,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x22,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x23,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x24,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x25,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x26,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x27,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x28,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x29,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x2A,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x2B,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x2C,&data);
//			delay_ms(10); 
//			RN8209_ReadData(0x2D,&data);
//			delay_ms(10); 
//	  	RN8209_ReadData(0x30,&data);
//			delay_ms(10); 
//	  	RN8209_ReadData(0x31,&data);
//			delay_ms(10); 
//	  	RN8209_ReadData(0x32,&data);
//			delay_ms(10);
//			RN8209_ReadData(0x35,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x40,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x41,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x42,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x43,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x44,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x45,&data);
//			delay_ms(10);        
//			RN8209_ReadData(0x7f,&data);
//			delay_ms(500); 
//			
//			delay_ms(1000);
			
////		 PBout(13)=1;
//		SDI_H;
//		
	}
}
 








