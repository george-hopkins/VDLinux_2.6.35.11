/*
 *  arch/arm/mach-ccep/include/mach/firenze.h
 *
 *  Copyright (C) 2010 Samsung Electronics
 *  Author: tukho.kim@samsung.com 
 *
 */

#ifndef __FIRENZE_H
#define __FIRENZE_H

#include <mach/irqs-sdp1004.h>
#include <mach/sdp1004.h>

/* clock parameters, see clocks.h */
#define INPUT_FREQ		24000000
#define FIN			INPUT_FREQ

/* Only using initialize kernel */
#define PCLK			(667000000 >> 2)	

/* system timer tick or high-resolution timer*/
#define SYS_TICK		HZ

/* timer definition  */
#define SYS_TIMER		0
#define SYS_TIMER_PRESCALER 	10 	// PCLK = 647 * 625 * 4 * 100 

#define TIMER_CLOCK		(REQ_PCLK)
#define SDP_GET_TIMERCLK(x)	sdp1004_get_clock(x)


// 20080523 HRTimer (clock source) define
#if defined(CONFIG_GENERIC_TIME) || defined(CONFIG_GERNERIC_COCKEVENTS)
#define CLKSRC_TIMER		1
#endif /* defined(CONFIG_GENERIC_TIME) || defined(CONFIG_GERNERIC_COCKEVENTS) */
// 20080523 HRTimer (clock source) define end
/* system timer tick or high-resolution timer end */ 


/* Memory Define */
/* Move to arch/arm/mach-ccep/include/mach/memory.h */
#include <mach/memory.h>

/* System Kernel memory size */
#define KERNEL_MEM_SIZE			(SYS_MEM0_SIZE + SYS_MEM1_SIZE)	// 100MByte

/* flash chip locations(SMC banks) */
#define PA_FLASH_BANK0			(0x0)
#define PA_FLASH_BANK1			(0x04000000)
#define FLASH_MAXSIZE			(32 << 20)		

// UART definition 
#define SDP_UART_NR			(3)

#define SER_BAUD_9600			(9600)
#define SER_BAUD_19200			(19200)
#define SER_BAUD_38400			(38400)
#define SER_BAUD_57600			(57600)
#define SER_BAUD_115200			(115200)
#define CURRENT_BAUD_RATE		(SER_BAUD_115200)

#define UART_CLOCK			(REQ_PCLK)
#define SDP_GET_UARTCLK(x)		sdp1004_get_clock(x)


// define interrupt resource definition 

#if (NR_IRQS==32)
#define SDP_INTERRUPT_RESOURCE \
/*irtSrc, qSrc,           level,       polarity,    priority,   sub priority        */ \
{{0,    IRQ_TSD,      	LEVEL_LEVEL, POLARITY_HIGH, 0xFFFFFFFF, 0xFFFFFFFF}, \
 {1,    IRQ_AIO,      	LEVEL_LEVEL, POLARITY_HIGH, 0xFFFFFFFE, 0xFFFFFFFF}, \
 {2,    IRQ_BDGA,     	LEVEL_LEVEL, POLARITY_HIGH, 0xFFFFFFFC, 0xFFFFFFFF}, \
 {3,    IRQ_TIMER,    	LEVEL_EDGE,  POLARITY_HIGH, 0xFFFFFFF8, 0xFFFFFFFF}, \
 {4,    IRQ_PSD,      	LEVEL_LEVEL, POLARITY_HIGH, 0xFFFFFFF0, 0xFFFFFFFF}, \
 {5,    IRQ_SE,       	LEVEL_LEVEL, POLARITY_HIGH, 0xFFFFFFE0, 0xFFFFFFFF}, \
 {6,    IRQ_AE,       	LEVEL_LEVEL, POLARITY_HIGH, 0xFFFFFFC0, 0xFFFFFFFF}, \
 {7,    IRQ_HDMI,     	LEVEL_LEVEL, POLARITY_HIGH, 0xFFFFFF80, 0xFFFFFFFF}, \
 {8,    IRQ_SATA0, 	LEVEL_LEVEL, POLARITY_HIGH, 0xFFFFFF00, 0xFFFFFFFF}, \
 {9,    IRQ_SATA1_PCIE, LEVEL_LEVEL, POLARITY_HIGH, 0xFFFFFE00, 0xFFFFFFFF}, \
 {10,   IRQ_RMI,	LEVEL_LEVEL, POLARITY_HIGH, 0xFFFFFC00, 0xFFFFFFFF}, \
 {11,   IRQ_RESERVED,	LEVEL_LEVEL, POLARITY_HIGH, 0xFFFFF800, 0xFFFFFFFF}, \
 {12,   IRQ_BDDP,     	LEVEL_LEVEL, POLARITY_HIGH,  0xFFFFF000, 0xFFFFFFFF}, \
 {13,   IRQ_USB_EHCI0,  LEVEL_LEVEL, POLARITY_HIGH, 0xFFFFE000, 0xFFFFFFFF}, \
 {14,   IRQ_USB_EHCI1,	LEVEL_LEVEL, POLARITY_HIGH, 0xFFFFC000, 0xFFFFFFFF}, \
 {15,   IRQ_MFD,	LEVEL_LEVEL, POLARITY_HIGH, 0xFFFF8000, 0xFFFFFFFF}, \
 {16,   IRQ_EMAC,	LEVEL_LEVEL, POLARITY_HIGH, 0xFFFF0000, 0xFFFFFFFF}, \
 {17,   IRQ_SDMMC,	LEVEL_LEVEL, POLARITY_HIGH, 0xFFFE0000, 0xFFFFFFFF}, \
 {18,   IRQ_GDMA,	LEVEL_LEVEL, POLARITY_HIGH, 0xFFFC0000, 0xFFFFFFFF}, \
 {19,   IRQ_PL310,	LEVEL_LEVEL, POLARITY_HIGH, 0xFFF80000, 0xFFFFFFFF}, \
 {20,   IRQ_NFCON, 	LEVEL_LEVEL, POLARITY_HIGH, 0xFFF00000, 0xFFFFFFFF}, \
 {21,   IRQ_SMC, 	LEVEL_LEVEL, POLARITY_HIGH, 0xFFE00000, 0xFFFFFFFF}, \
 {22,   IRQ_USB_OHCI0, 	LEVEL_LEVEL, POLARITY_HIGH, 0xFFC00000, 0xFFFFFFFF}, \
 {23,   IRQ_USB_OHCI1, 	LEVEL_LEVEL, POLARITY_HIGH, 0xFF800000, 0xFFFFFFFF}, \
 {24, IRQ_USB0_OVERCUR, LEVEL_LEVEL, POLARITY_HIGH, 0xFF000000, 0xFFFFFFFF}, \
 {25, IRQ_USB1_OVERCUR, LEVEL_LEVEL, POLARITY_HIGH, 0xFE000000, 0xFFFFFFFF}, \
 {26,   IRQ_UART,	LEVEL_LEVEL, POLARITY_HIGH, 0xFC000000, 0xFFFFFFFF}, \
 {27,   IRQ_SPI,     	LEVEL_LEVEL, POLARITY_HIGH, 0xF8000000, 0xFFFFFFFF}, \
 {28,   IRQ_I2C,	LEVEL_LEVEL, POLARITY_HIGH, 0xF0000000, 0xFFFFFFFF}, \
 {29,   IRQ_CSSYS,	LEVEL_LEVEL, POLARITY_HIGH, 0xE0000000, 0xFFFFFFFF}, \
 {30,   IRQ_BUS,      	LEVEL_LEVEL, POLARITY_HIGH, 0xC0000000, 0xFFFFFFFF}, \
 {31,   IRQ_EXT,   	LEVEL_LEVEL_EXT, POLARITY_HIGH, 0x80000000, 0xFFFFFFFF} }
#else
#define SDP_INTERRUPT_RESOURCE \
/*irtSrc, qSrc,           level,       polarity,    priority,   sub priority        */ \
{{0,    IRQ_TSD,      	LEVEL_LEVEL,	POLARITY_HIGH, 0xFFFFFFFF, 0xFFFFFFFF}, \
 {1,    IRQ_AIO,      	LEVEL_LEVEL,	POLARITY_HIGH, 0xFFFFFFFE, 0xFFFFFFFF}, \
 {2,    IRQ_BDGA,     	LEVEL_LEVEL,	POLARITY_HIGH, 0xFFFFFFFC, 0xFFFFFFFF}, \
 {3,    IRQ_TIMER,    	LEVEL_EDGE,	POLARITY_HIGH, 0xFFFFFFF8, 0xFFFFFFFF}, \
 {4,    IRQ_PSD,      	LEVEL_LEVEL,	POLARITY_HIGH, 0xFFFFFFF0, 0xFFFFFFFF}, \
 {5,    IRQ_SE,       	LEVEL_LEVEL,	POLARITY_HIGH, 0xFFFFFFE0, 0xFFFFFFFF}, \
 {6,    IRQ_AE,       	LEVEL_LEVEL,	POLARITY_HIGH, 0xFFFFFFC0, 0xFFFFFFFF}, \
 {7,    IRQ_HDMI,     	LEVEL_LEVEL,	POLARITY_HIGH, 0xFFFFFF80, 0xFFFFFFFF}, \
 {8,    IRQ_SATA0, 	LEVEL_LEVEL,	POLARITY_HIGH, 0xFFFFFF00, 0xFFFFFFFF}, \
 {9,    IRQ_SATA1_PCIE, LEVEL_LEVEL,	POLARITY_HIGH, 0xFFFFFE00, 0xFFFFFFFF}, \
 {10,   IRQ_GP,     	LEVEL_LEVEL,	POLARITY_HIGH, 0xFFFFFC00, 0xFFFFFFFF}, \
 {11,   IRQ_COP0,	LEVEL_LEVEL,	POLARITY_HIGH, 0xFFFFF800, 0xFFFFFFFF}, \
 {12,   IRQ_BDDP, 	LEVEL_LEVEL,	POLARITY_HIGH, 0xFFFFF000, 0xFFFFFFFF}, \
 {13,   IRQ_USB_EHCI0, 	LEVEL_LEVEL,	POLARITY_HIGH, 0xFFFFE000, 0xFFFFFFFF}, \
 {14,   IRQ_USB_EHCI1,	LEVEL_LEVEL,	POLARITY_HIGH, 0xFFFFC000, 0xFFFFFFFF}, \
 {15,   IRQ_MFD,	LEVEL_LEVEL,	POLARITY_HIGH, 0xFFFF8000, 0xFFFFFFFF}, \
 {16,   IRQ_EMAC,       LEVEL_LEVEL,	POLARITY_HIGH, 0xFFFF0000, 0xFFFFFFFF}, \
 {17,   IRQ_SDMMC,      LEVEL_LEVEL,	POLARITY_HIGH, 0xFFFE0000, 0xFFFFFFFF}, \
 {18,   IRQ_GDMA,       LEVEL_LEVEL,	POLARITY_HIGH, 0xFFFC0000, 0xFFFFFFFF}, \
 {19,   IRQ_HDMI_DDC,   LEVEL_LEVEL,	POLARITY_HIGH, 0xFFF80000, 0xFFFFFFFF}, \
 {20,   IRQ_NFCON,      LEVEL_LEVEL,	POLARITY_HIGH, 0xFFF00000, 0xFFFFFFFF}, \
 {21,   IRQ_COP1,       LEVEL_LEVEL,	POLARITY_HIGH, 0xFFE00000, 0xFFFFFFFF}, \
 {22,   IRQ_USB_OHCI0, 	LEVEL_LEVEL,	POLARITY_HIGH, 0xFFC00000, 0xFFFFFFFF}, \
 {23,   IRQ_USB_OHCI1, 	LEVEL_LEVEL,	POLARITY_HIGH, 0xFF800000, 0xFFFFFFFF}, \
 {24,   IRQ_GA2D, 	LEVEL_LEVEL,	POLARITY_HIGH, 0xFF000000, 0xFFFFFFFF}, \
 {25,   IRQ_GA3D, 	LEVEL_LEVEL,	POLARITY_HIGH, 0xFE000000, 0xFFFFFFFF}, \
 {26,   IRQ_GSCL, 	LEVEL_LEVEL,	POLARITY_HIGH, 0xFC000000, 0xFFFFFFFF}, \
 {27,   IRQ_RLD,  	LEVEL_LEVEL,	POLARITY_HIGH, 0xF8000000, 0xFFFFFFFF}, \
 {28,   IRQ_PNG,	LEVEL_LEVEL,	POLARITY_HIGH, 0xF0000000, 0xFFFFFFFF}, \
 {29,   IRQ_JPEG, 	LEVEL_LEVEL,	POLARITY_HIGH, 0xE0000000, 0xFFFFFFFF}, \
 {30,   IRQ_CSC, 	LEVEL_LEVEL,	POLARITY_HIGH, 0xC0000000, 0xFFFFFFFF}, \
 {31,   IRQ_SDP,  	LEVEL_LEVEL,	POLARITY_HIGH, 0x80000000, 0xFFFFFFFF}, \
 {32,   IRQ_UART0,    	LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFFFFFFF}, \
 {33,   IRQ_UART1,    	LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFFFFFFE}, \
 {34,   IRQ_UART2,    	LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFFFFFFC}, \
 {35,   IRQ_UART3,    	LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFFFFFF8}, \
 {36,   IRQ_UDMA0,    	LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFFFFFF0}, \
 {37,   IRQ_UDMA1,    	LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFFFFFE0}, \
 {38,   IRQ_I2C1_4,    	LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFFFFFC0}, \
 {39,   IRQ_SPI,	LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFFFFF80}, \
 {40,   IRQ_SATA0_REDEF,LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFFFFF00}, \
 {41,   IRQ_SATA1_PCIE_REDEF,LEVEL_LEVEL,POLARITY_HIGH,0x00000000, 0xFFFFFE00}, \
 {42,   IRQ_RMI,	LEVEL_LEVEL,	POLARITY_LOW,  0x00000000, 0xFFFFFC00}, \
 {43,   IRQ_RESERVED,	LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFFFF800}, \
 {44,   IRQ_BUS,	LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFFFF000}, \
 {45,   IRQ_CSSYS,	LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFFFE000}, \
 {46, IRQ_USB0_OVERCUR, LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFFFC000}, \
 {47, IRQ_USB1_OVERCUR, LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFFF8000}, \
 {48,   IRQ_EMAC_REDEF,	LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFFF0000}, \
 {49,   IRQ_SDMMC_REDEF,LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFFE0000}, \
 {50,   IRQ_GDMA_REDEF,	LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFFC0000}, \
 {51,   IRQ_PL310,	LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFF80000}, \
 {52,   IRQ_NFCON_REDEF,LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFF00000}, \
 {53,   IRQ_SMC,    	LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFE00000}, \
 {54, IRQ_USB_OHCI0_REDEF, LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFFC00000}, \
 {55, IRQ_USB_OHCI1_REDEF, LEVEL_LEVEL,	POLARITY_HIGH, 0x00000000, 0xFF800000}, \
 {56,   IRQ_EXTINT0,    LEVEL_LEVEL_EXT,POLARITY_HIGH, 0x00000000, 0xFF000000}, \
 {57,   IRQ_EXTINT1,   	LEVEL_LEVEL_EXT,POLARITY_HIGH, 0x00000000, 0xFE000000}, \
 {58,   IRQ_EXTINT2,    LEVEL_LEVEL_EXT,POLARITY_HIGH, 0x00000000, 0xFC000000}, \
 {59,   IRQ_EXTINT3,	LEVEL_LEVEL_EXT,POLARITY_HIGH, 0x00000000, 0xF8000000}, \
 {60,   IRQ_EXTINT4,    LEVEL_LEVEL_EXT,POLARITY_HIGH, 0x00000000, 0xF0000000}, \
 {61,   IRQ_EXTINT5,	LEVEL_LEVEL_EXT,POLARITY_HIGH, 0x00000000, 0xE0000000}, \
 {62,   IRQ_EXTINT6,    LEVEL_LEVEL_EXT,POLARITY_HIGH, 0x00000000, 0xC0000000}, \
 {63,   IRQ_EXTINT7, 	LEVEL_LEVEL_EXT,POLARITY_HIGH, 0x00000000, 0x80000000} }
#endif /* (NR_IRQ != 64) */

#endif

