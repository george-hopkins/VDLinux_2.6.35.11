################################################################################
#
# Copyright (c) 2006-2007 MStar Semiconductor, Inc.
# All rights reserved.
#
# Unless otherwise stipulated in writing, any and all information contained
# herein regardless in any format shall remain the sole proprietary of
# MStar Semiconductor Inc. and be kept in strict confidence
# (��MStar Confidential Information��) by the recipient.
# Any unauthorized act including without limitation unauthorized disclosure,
# copying, use, reproduction, sale, distribution, modification, disassembling,
# reverse engineering and compiling of the contents of MStar Confidential
# Information is unlawful and strictly prohibited. MStar hereby reserves the
# rights to any and all damages, losses, costs and expenses resulting therefrom.
#
################################################################################


    .include "boot1.inc"

#-------------------------------------------------------------------------------------------------
# Version
#-------------------------------------------------------------------------------------------------
BOOT_VERSION                = 0x20080312

#-------------------------------------------------------------------------------------------------
# Build Options
#-------------------------------------------------------------------------------------------------
BOOT_DEBUG_VERSION          = 1                  # Set for debugging boot code

BOOT_COPY_VIA_DMA           = 0                  # Set for copying zipped binary from Flash to DRAM via DMA; otherwise via CPU

BOOT_PARALLEL_FLASH         = 0                  # Set for booting from Parallel Flash; otherwise from Serial Flash

SUPPORT_POWER_SAVING        = 1
DYNAMIC_POWER_ON_OFF        = 0

SUPPORT_UNZIP               = 1                 # Set for supporting Unzip (also need to change boot.sh)

RAM_SIZE_128                = 0
EN_EMAC                     = 0


#
# MIU setting
#------------------------------------------------

.if (BD_FPGA)
# 667MHZ=0x14A9, 800MHZ = 0x1129, 900MHZ = (0x1F09,0xC000)
MIU_FREQ					 = 0x1129
ENABLE_ODT					 = 1

# MIU0 settings
MIU0_LEN					 = 0x0C45
MIU0_PHASE					 = 0x0034
MIU0_DO_BIST				 = 0
MIU0_DO_BIST_PATTERN		 = 0x5AA5
#   test length (dram len / 8, in word)
MIU0_DO_BIST_LEN_H			 = 0x00FF
MIU0_DO_BIST_LEN_L			 = 0xFFFF
MIU0_DRAM_PHASE				 = 0x0244

# MIU1 settings
MIU1_INIT					 = 1
MIU1_LEN					 = 0x0C45
MIU1_PHASE					 = 0x0044
MIU1_DO_BIST				 = 0
MIU1_DO_BIST_PATTERN		 = 0xA55A
#   test length (dram len / 8, in word)
MIU1_DO_BIST_LEN_H			 = 0x0080
MIU1_DO_BIST_LEN_L			 = 0x0000
MIU1_DRAM_PHASE				 = 0x0244
.endif

.if (BD_FPGA)
# 667MHZ=0x14A9, 800MHZ = 0x1129, 900MHZ = (0x1F09,0xC000)
MIU_FREQ					 = 0x1129
ENABLE_ODT					 = 1

# MIU0 settings
MIU0_LEN					 = 0x0C45
MIU0_PHASE					 = 0x0034
MIU0_DO_BIST				 = 0
MIU0_DO_BIST_PATTERN		 = 0x5AA5
#   test length (dram len / 8, in word)
MIU0_DO_BIST_LEN_H			 = 0x00FF
MIU0_DO_BIST_LEN_L			 = 0xFFFF
MIU0_DRAM_PHASE				 = 0x0244

# MIU1 settings
MIU1_INIT					 = 1
MIU1_LEN					 = 0x0C45
MIU1_PHASE					 = 0x0044
MIU1_DO_BIST				 = 0
MIU1_DO_BIST_PATTERN		 = 0xA55A
#   test length (dram len / 8, in word)
MIU1_DO_BIST_LEN_H			 = 0x0080
MIU1_DO_BIST_LEN_L			 = 0x0000
MIU1_DRAM_PHASE				 = 0x0244
.endif # .if (BD_FPGA)

# Set DRAM type (exclusive selection)
DRAM_TYPE_DDR16_ETRON       = 1                 # BD_MST041A / BD_MST041B
DRAM_TYPE_SDR16_ESMT        = 0                 # BD_MST041D / BD_MST041E
DRAM_TYPE_SDR16_ETRON       = 0

#-------------------------------------------------------------------------------------------------
# Addressed in ROM / RAM
#-------------------------------------------------------------------------------------------------
# Start address after boot-up
ADDR_BOOT_ROM_START         = 0xBFC00000 #0x81C00000

# Reserve Bytes for boot code (to avoid recursive defines SIZE_BOOT in boot1.inc)
SIZE_BOOT_RESERVED          = 3072
SIZE_BOOTROM_RESERVED       = 4096
SIZE_BOOTRAM_RESERVED       = 2048 #1024

SIZE_CHUNK_HEADER_RESERVED  = 128   # 16 chunks.

#### Copy Unzip subroutine from ROM to RAM ###
#SIZE_UNZIP                 in boot1.c
ADDR_UNZIP_ROM_START        = (ADDR_BOOT_ROM_START + SIZE_BOOT_RESERVED + SIZE_BOOTROM_RESERVED + SIZE_BOOTRAM_RESERVED + SIZE_CHUNK_HEADER_RESERVED)
ADDR_UNZIP_ROM_END          = (ADDR_UNZIP_ROM_START + SIZE_UNZIP) #actually end+1
ADDR_UNZIP_RAM_START        = 0xA0200000 #0xA0800000
ADDR_UNZIP_RAM_START_CACHE  = (ADDR_UNZIP_RAM_START & ~0x20000000 )
ADDR_UNZIP_RAM_END          = (ADDR_UNZIP_RAM_START + SIZE_UNZIP) #actually end+1

### Copy Zipped binary from ROM to RAM ###
#SIZE_ZIPBIN                in boot1.c
ADDR_ZIPBIN_ROM_START       = (ADDR_UNZIP_ROM_END)
ADDR_ZIPBIN_ROM_END         = (ADDR_ZIPBIN_ROM_START + SIZE_ZIPBIN) #actually end+1
.if DRAM_TYPE_DDR16_ETRON
ADDR_ZIPBIN_RAM_START       = 0xA1000000    # >8MB
.endif
.if DRAM_TYPE_SDR16_ESMT
ADDR_ZIPBIN_RAM_START       = 0xA0600000 #0xA0500000    # 8MB
.endif
.if DRAM_TYPE_SDR16_ETRON
ADDR_ZIPBIN_RAM_START       = 0xA0500000    # 8MB
.endif
ADDR_ZIPBIN_RAM_START_CACHE = (ADDR_ZIPBIN_RAM_START & ~0x20000000 )
ADDR_ZIPBIN_RAM_END         = (ADDR_ZIPBIN_RAM_START + SIZE_ZIPBIN) #actually end+1

### Unzip binary ###
#Initialize system stack pointer for unzip subroutine
ADDR_UNZIP_BUFFER           = 0x80300000 #0x80A00000    # Decompression memory when doing unzip
ADDR_UNZIP_STACK_POINTER    = 0x80380000 #0x80A80000    # Initial stack pointer (downwards)
ADDR_SYSTEM_RAM_START       = 0xA0400000 #0xA0100000    # Address of Venus binary in RAM. Note: must be the same as the RAM start in link descriptor
ADDR_SYSTEM_RAM_START_CACHE = KERNEL_ENTRY_ADDR    #ToDo: copy general exception handler at OS init instead of linking it to code


#-------------------------------------------------------------------------------------------------
# Initialize Regs & Initialize Cache
#-------------------------------------------------------------------------------------------------
M_DebugCOUNTDM      = (0x1  << 25)

M_StatusCU          = (0xf  << 28)
M_StatusRP          = (0x1  << 27)
M_StatusRE          = (0x1  << 25)
M_StatusBEV         = (0x1  << 22)
M_StatusTS          = (0x1  << 21)
M_StatusSR          = (0x1  << 20)
M_StatusNMI         = (0x1  << 19)
M_StatusIM7         = (0x1  << 15)
M_StatusIM2         = (0x1  << 10)
M_StatusIM          = (0xff << 8)
M_StatusUM          = (0x1  << 4)
M_StatusERL         = (0x1  << 2)
M_StatusEXL         = (0x1  << 1)
M_StatusIE          = (0x1  << 0)

M_CauseIV           = (0x1  << 23)
M_CauseWP           = (0x1  << 22)
M_CauseIP1          = (0x1  << 9)
M_CauseIP0          = (0x1  << 8)

M_ConfigK23         = (0x7  << 28)
M_ConfigKU          = (0x7  << 25)
M_ConfigMT          = (0x7  << 7)
M_ConfigK0          = (0x7  << 0)
K_CacheAttrCN       = (0x3  << 0) #Cacheable, noncoherent, write-back, write allocate.
S_Config1IS         = 22
M_Config1IS         = (0x7  << S_Config1IS)
S_Config1IL         = 19
M_Config1IL         = (0x7  << S_Config1IL)
S_Config1IA         = 16
M_Config1IA         = (0x7  << S_Config1IA)
S_Config1DS         = 13
M_Config1DS         = (0x7  << S_Config1DS)
S_Config1DL         = 10
M_Config1DL         = (0x7  << S_Config1DL)
S_Config1DA         = 7
M_Config1DA         = (0x7  << S_Config1DA)

INITIAL_STATUS      = 0x10400000
INITIAL_CONFIG0     = 0x00000002 #Uncached

Index_Store_Tag_I   = 0x8
Index_Store_Tag_D   = 0x9

A_DSPRAM            = 0x04000000        # 0x84000000
A_KSEG0BASE         = 0x80000000


#-------------------------------------------------------------------------------------------------
# Flash registers
#-------------------------------------------------------------------------------------------------
REG_ISP_CLK_SRC             =   (0xBF000000 + 0x1E26*4)
REG_SFSH_PIU_BASE           =   0xBF007800
REG_SFSH_DMA_STATE          =   (REG_SFSH_PIU_BASE + 0x10*4) #[1]done [2]busy [8:15]state
REG_SFSH_DMA_SPISTART_L     =   (REG_SFSH_PIU_BASE + 0x70*4) #[15:0]
REG_SFSH_DMA_SPISTART_H     =   (REG_SFSH_PIU_BASE + 0x71*4) #[23:16]
REG_SFSH_DMA_DRAMSTART_L    =   (REG_SFSH_PIU_BASE + 0x72*4) #[15:0]  in unit of B; must be 8B aligned
REG_SFSH_DMA_DRAMSTART_H    =   (REG_SFSH_PIU_BASE + 0x73*4) #[23:16]
REG_SFSH_DMA_SIZE_L         =   (REG_SFSH_PIU_BASE + 0x74*4) #[15:0]  in unit of B; must be 8B aligned
REG_SFSH_DMA_SIZE_H         =   (REG_SFSH_PIU_BASE + 0x75*4) #[23:16]
REG_SFSH_DMA_CMD            =   (REG_SFSH_PIU_BASE + 0x76*4)
SFSH_DMA_ALIGN              =   8

#-------------------------------------------------------------------------------------------------
# Other registers
#-------------------------------------------------------------------------------------------------
REG_TOP_POWER_STATUS        = 0xBF203CDC

#-------------------------------------------------------------------------------------------------
# UART registers
#-------------------------------------------------------------------------------------------------
UART_BASE               = 0xBF201300
UART_RX		            = (0*4 + UART_BASE)
UART_TX		            = (0*4 + UART_BASE)
UART_DLL	            = (0*4 + UART_BASE)
UART_DLM	            = (2*4 + UART_BASE)
UART_IER	            = (2*4 + UART_BASE)
UART_IIR	            = (4*4 + UART_BASE)
UART_FCR	            = (4*4 + UART_BASE)
# UART_EFR	            = (2*4 + UART_BASE)
UART_LCR	            = (6*4 + UART_BASE)
UART_MCR	            = (8*4 + UART_BASE)
UART_LSR	            = (10*4 + UART_BASE)
UART_MSR	            = (12*4 + UART_BASE)
# UART_SCR	            = (7*4 + UART_BASE)

#Baud rate
.if (BD_FPGA)
 UART_BAUD_RATE	        = 38400
.else
UART_BAUD_RATE	        = 115200
.endif

#CPU clock
.if (BD_FPGA)
CPU_CLOCK_FREQ          =  12000000
.else
CPU_CLOCK_FREQ          = 216000000
.endif

#Clock source
.if (BD_FPGA)
UART_CLK_FREQ           =  12000000
.else
UART_CLK_FREQ           = 123000000
#UART_CLK_FREQ           = 172800000
.endif



#Divisor
UART_DIVISOR            = (UART_CLK_FREQ/(16 * UART_BAUD_RATE))

#-------------------------------------------------------------------------------------------------
# Macros
#-------------------------------------------------------------------------------------------------
.macro  RBASE   reg
lui     $8,     (\reg >> 16)
.endm

.macro WREG reg, value
li      $9, \value
sw      $9, (\reg & 0xFFFF)($8)
.endm

.macro DBGREG value
#    WREG    0xBF203DDC, \value
    RBASE   0xBF206700
    WREG    0xBF206700, \value  #use mail box: bank 1033, 8bit offset 0x80
.endm

.macro DELAYUS us
        li      $10, \us * (CPU_CLOCK_FREQ/2/1000000) #ticks
        mfc0    $26, $9      #tick1
1:
        mfc0    $9, $9      #tick2
        subu    $11, $9, $26 #tick2-tick1
        blt     $11, $10, 1b
        nop
.endm

.macro DELAYMS ms
        li      $10, \ms * (CPU_CLOCK_FREQ/2/1000) #ticks
        mfc0    $26, $9      #tick1
1:
        mfc0    $9, $9      #tick2
        subu    $11, $9, $26 #tick2-tick1
        blt     $11, $10, 1b
        nop
.endm

.macro RREG reg_d, reg
lui     $8, \reg >> 16
lw      \reg_d, (\reg & 0xFFFF)($8)
.endm

.macro LRREG reg_d, reg
lw      \reg_d, (\reg & 0xFFFF)($8)
.endm

.macro SSSW reg, value
lui     $8, \reg >> 16
sw      \value, (\reg & 0xFFFF)($8)
.endm

.macro LSSSW reg, value
sw      \value, (\reg & 0xFFFF)($8)
.endm

.macro PUTC char
    RBASE   UART_TX
    WREG    UART_TX, \char
.endm

USE_CACHE_INIT_METHOD1 = 1

.if USE_CACHE_INIT_METHOD1
.macro	mfc0_delay
nop
nop
nop
nop
.endm

Address_Fill_I	    = 0x14
.endif

