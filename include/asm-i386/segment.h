#ifndef _ASM_SEGMENT_H
#define _ASM_SEGMENT_H

#define __KERNEL_CS	0x10
#define __KERNEL_DS	0x18

#define __USER_CS	0x23
#define __USER_DS	0x2B

#endif
//linux内核中只使用4种不同的段寄存器数值，两种是用户态(所有的进程)的，两种是内核态的
//
//
//
//intel的i386段寄存器格式定义
//			15									3|2	  1		0
//			-------------------------------------------------
//			|		Index						 | TI | RPL |								
//			-------------------------------------------------
//													|	 |->Request Privilege Level
//													|
//													|->Table Indicator, 0 = GDT, 1 = LDT
//		
//		Intel的设计意图是内核使用GDT而各个进程都使用自己的LDT
//
//		将define的四种linux段寄存器格式和Intel的对照
//
//													Index			TI	RPL
//	----------------------------------------------------------------------------------------------
//		__KERNEL_CS		0X10			0000	0000	0001	0 | 0 | 0 0
//		__KERNEL_DS		0X18			0000	0000	0001	1 | 0 | 0 0
//		__USER_CS		0X23			0000	0000	0010	0 | 0 |	1 1
//		__USER_DS		0X2B			0000	0000	0010	1 | 0 | 1 1
//	--------------------------------------------------------------------------------------------
//	
//
//		__KERNEL_CS:							Index = 2,		TI = 0,		RPL = 0
//		__KERNEL_DS:							Index = 3,		TI = 0,		RPL = 0
//		__USER_CS:								Index = 4,		TI = 0,		RPL = 3
//		__USER_DS:								Index = 5,		TI = 0,		RPL = 3
//
//	一对照就清晰了，首先TI全为0，那么linux的不管是内核还是用户进程全部都是使用GDT，(so fuck intel! hhhhhhhhhh)
//	实际上，在linux内核中基本上不使用LDT,它只会在一些特定的模式中才会使用LDT,
//
//	RPL:内核为0级而用户进程为3级
//
