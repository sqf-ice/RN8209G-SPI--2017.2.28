#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
////����Ƭѡ�ź�Ϊ��
//);//����Ƭѡ�ź�Ϊ��	
//
////����ʱ���ź�Ϊ��
//);//����ʱ���ź�Ϊ��	
//
///���ô�����ź�Ϊ��
//;//���ô�����ź�Ϊ��	
//
///���ô������ź�Ϊ��	
//���ô������ź�Ϊ��	
////////////////////////////////////////////////////////////////////////////////

 
 				  	    													  

void RN8209G_SPI_config(void);

//u32 RN8209_ReadData(u8 address,u32 *data_r);
u32 RN8209_ReadData(u8 address);
void RN8209_WriteData(u8 address,u32 order);    
void RN8209_Parameter_Adjust(void);
void RN8209_ActivePower_Adjust(void);
void RN8209_ReactivePower_Adjust(void);
void RN8209_Rms_Adjust(void);
void RN8209_Count_Kx(void );
void RN8209_DC_Config(void );
void RN8209_DC_Adjust(void );
u32 RN8209_readIA_RMS(void );
void RN8209_KZ(void);


#define SCSN_H GPIO_SetBits(GPIOB, GPIO_Pin_12);//����Ƭѡ�ź�Ϊ��
#define SCSN_L GPIO_ResetBits(GPIOB, GPIO_Pin_12);//����Ƭѡ�ź�Ϊ��	

#define SCLK_H GPIO_SetBits(GPIOB, GPIO_Pin_13);//����ʱ���ź�Ϊ��
#define SCLK_L GPIO_ResetBits(GPIOB, GPIO_Pin_13);//����ʱ���ź�Ϊ��	

#define SDO  GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14);//���ô�����ź�Ϊ��
	

#define SDI_H GPIO_SetBits(GPIOB, GPIO_Pin_15);//���ô������ź�Ϊ��
#define SDI_L GPIO_ResetBits(GPIOB, GPIO_Pin_15);//���ô������ź�Ϊ��	

//----------------------start RN8209  ��ַ����---------------------------------------------------//
//----------------------�Ѿ���ˣ�������������2016.10.12-----------------------------------------//
#define					SYSCON        0x00 
#define        	EMUCON 				0x01
#define        	HFConst     	0x02 
#define        	PStart      	0x03 
#define        	DStart      	0x04 
#define					GPQA        	0x05 
#define        	GPQB        	0x06 
#define        	PhsA        	0x07 
#define        	PhsB        	0x08
#define					QPhsCal				0x09    
#define					APOSA 				0x0a
#define        	APOSB 				0x0b
#define        	RPOSA 				0x0c
#define        	RPOSB 				0x0d
#define        	IARMSOS     	0x0e
#define        	IBRMSOS     	0x0f
#define        	IBGain      	0x10
#define					D2FPL       	0x11
#define        	D2FPH       	0x12
#define        	DCIAH       	0x13
#define        	DCIBH       	0x14
#define         DCUH					0x15   
#define         DCL   				0x16 
#define         EMUCON2				0x17

#define					PFCnt    			0x20
#define        	DFcnt    			0x21
#define        	IARMS       	0x22
#define        	IBRMS       	0x23
#define        	URMS        	0x24
#define					UFreq       	0x25
#define        	PowerPA     	0x26
#define        	PowerPB     	0x27
#define        	PowerQ     	  0x28
#define         EnergyP  			0x29
#define         EnergyP2 			0x2a
#define         EnergyD  			0x2b
#define         EnergyD2    	0x2c
#define         EMUStatus   	0x2d
#define         SPL_IA      	0x30
#define         SPL_IB      	0x31
#define         SPL_U       	0x32

#define         IE  					0x40
#define         IF  					0x41
#define         RIF  			 		0x42

#define         SysStatus  		0x43
#define         RData      		0x44
#define         WData      		0x45
#define         DeviceID   		0x7f

#define         WriteEnAdd   	0xea
#define         WriteEnData   0xe5//дʹ��

#define         WriteDisAdd   0xea
#define         WriteDisData  0xdc

#define         SelectIaAdd   0xea
#define         SelectIaData  0x5a//ѡ�����ͨ��A

#define         SelectIbAdd   0xea
#define         SelectIbData  0xa5

#define         SoftRestAdd   0xea
#define         SoftRestData  0xfa//�����λ����ͬӲ��
//----------------------end RN8209  ��ַ����----------------------------------------------//

//-------------------------start У������ļ�---------------------------------------------//
typedef struct 
{		
	u16     AdjustSYSCON;
	u16			AdjustEMUCON;
	u16			AdjustHFConst;
	u16			AdjustPStart;	
	u16			AdjustQStart;  			//10
	u16			AdjustGPQA;    	
	u16			AdjustGPQB;    	
	u16			AdjustIAGain;  	
	u16			AdjustUGain;   	
	u16			AdjustIBGain;  	
	u16			AdjustPhsA;	   	
	u16			AdjustPhsB;    	
	u16			AdjustQPhsCal; 			//22
	u16			AdjustAPOSA;   	
	u16			AdjustAPOSB;	 	
	u16			AdjustRPOSA;   	
	u16			AdjustRPOSB;   	
	u16			AdjustIARMSOS; 			//32
	u16			AdjustIBRMSOS;			//34
	u16			AdjustDCIAH;
	u16			AdjustDCIBH;
	u16			AdjustDCUH;
	u16			AdjustDCL;
	u16			AdjustEMUCON2; 	
	float		AdjustKUrms;								//��ѹϵ��
	float		AdjustKIArms;								// Aͨ������ϵ��
	float		AdjustKIBrms;								// Bͨ������ϵ��
	float		AdjustKPrms;								// ����ϵ��
//	u16		Adjust	RealUI[2];						// 
//	u32		Adjust	RealPw;								// ?????,????????? 0.2%
	u32			AdjustChkSum;             	
	u16			AdjustRTCDota0;							// RTCУ���Ĵ���
	u8			AdjustTemperAdj[2];					// �ߵ��²���ֵ
//	u8		Adjust	RTCAdj[4];						// RTC
//	u8		Adjust	CurAdj;								// ???????
	u8 			AdjustOfsetAdjAcVolt[2]; 		//���ݵ�ѹ����offset��ֵ
//	u16			CorrectionTemper;  		//
}Adjust_Parameter_TypeDef;		//58 Byte
//-------------------------end У������ļ�---------------------------------------------//




#endif

