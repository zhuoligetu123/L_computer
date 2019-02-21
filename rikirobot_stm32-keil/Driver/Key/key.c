#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f10x.h"
#include "key.h"
#include "millisecondtimer.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////  
								    
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 												//PD2�˿�����
 GPIO_Init(GPIOD, &GPIO_InitStructure);					 													//�����趨������ʼ��GPIOB.5

}
//������������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//0��û���κΰ�������
//1��KEY0����
//2��KEY1����
//3��KEY2���� 
//4��KEY3���� WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY2>KEY3!!
int KEY_Scan(int mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������	
  int i = 0; 	
	if(key_up&&(KEY1==0||KEY2==0||KEY3==0||KEY4==0))
	{
		delay(10);//ȥ���� 
		key_up=0;
		if(KEY1==0)
		{
		   return 1 ;
		}
		if(KEY2==0)
		{
			return 2;
		}
		if(KEY3==0)
		{
			return 3;
		}
		if(KEY4==0)
		{
			return 4;
		}
	}
	else if(KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)key_up=1; 	    
 	return 0;// �ް�������
}

#ifdef __cplusplus
}
#endif