#ifndef __CHIP_INT_H__
#define __CHIP_INT_H__

#define MSTAR_CHIP_INT_END 128//64

#define REG_INT_BASE                0xbf203200

#if 1 // for MIPS VPE 0
//IRQ registers
#define REG_IRQ_MASK_L              (REG_INT_BASE+ (0x0034<< 2))
#define REG_IRQ_MASK_H              (REG_INT_BASE+ (0x0035<< 2))
#define REG_IRQ_PENDING_L           (REG_INT_BASE+ (0x003c<< 2))
#define REG_IRQ_PENDING_H           (REG_INT_BASE+ (0x003d<< 2))

//IRQ EXP registers
#define REG_IRQ_EXP_MASK_L          (REG_INT_BASE+ (0x0036<< 2))
#define REG_IRQ_EXP_MASK_H          (REG_INT_BASE+ (0x0037<< 2))
#define REG_IRQ_EXP_PENDING_L       (REG_INT_BASE+ (0x003e<< 2))
#define REG_IRQ_EXP_PENDING_H       (REG_INT_BASE+ (0x003f<< 2))

//FIQ registers
#define REG_FIQ_MASK_L              (REG_INT_BASE+ (0x0024<< 2))
#define REG_FIQ_MASK_H              (REG_INT_BASE+ (0x0025<< 2))
#define REG_FIQ_CLEAR_L             (REG_INT_BASE+ (0x002c<< 2))
#define REG_FIQ_CLEAR_H             (REG_INT_BASE+ (0x002d<< 2))
#define REG_FIQ_PENDING_L           (REG_INT_BASE+ (0x002c<< 2))
#define REG_FIQ_PENDING_H           (REG_INT_BASE+ (0x002d<< 2))

//FIQ EXP registers
#define REG_FIQ_EXP_MASK_L          (REG_INT_BASE+ (0x0026<< 2))
#define REG_FIQ_EXP_MASK_H          (REG_INT_BASE+ (0x0027<< 2))
#define REG_FIQ_EXP_CLEAR_L         (REG_INT_BASE+ (0x002e<< 2))
#define REG_FIQ_EXP_CLEAR_H         (REG_INT_BASE+ (0x002f<< 2))
#define REG_FIQ_EXP_PENDING_L       (REG_INT_BASE+ (0x002e<< 2))
#define REG_FIQ_EXP_PENDING_H       (REG_INT_BASE+ (0x002f<< 2))
#else // for MIPS VPE 1
//IRQ registers
#define REG_IRQ_MASK_L              (REG_INT_BASE+ (0x0054<< 2))
#define REG_IRQ_MASK_H              (REG_INT_BASE+ (0x0055<< 2))
#define REG_IRQ_PENDING_L           (REG_INT_BASE+ (0x005c<< 2))
#define REG_IRQ_PENDING_H           (REG_INT_BASE+ (0x005d<< 2))

//IRQ EXP registers
#define REG_IRQ_EXP_MASK_L          (REG_INT_BASE+ (0x0056<< 2))
#define REG_IRQ_EXP_MASK_H          (REG_INT_BASE+ (0x0057<< 2))
#define REG_IRQ_EXP_PENDING_L       (REG_INT_BASE+ (0x005e<< 2))
#define REG_IRQ_EXP_PENDING_H       (REG_INT_BASE+ (0x005f<< 2))

//FIQ registers
#define REG_FIQ_MASK_L              (REG_INT_BASE+ (0x0044<< 2))
#define REG_FIQ_MASK_H              (REG_INT_BASE+ (0x0045<< 2))
#define REG_FIQ_CLEAR_L             (REG_INT_BASE+ (0x004c<< 2))
#define REG_FIQ_CLEAR_H             (REG_INT_BASE+ (0x004d<< 2))
#define REG_FIQ_PENDING_L           (REG_INT_BASE+ (0x004c<< 2))
#define REG_FIQ_PENDING_H           (REG_INT_BASE+ (0x004d<< 2))

//FIQ EXP registers
#define REG_FIQ_EXP_MASK_L          (REG_INT_BASE+ (0x0046<< 2))
#define REG_FIQ_EXP_MASK_H          (REG_INT_BASE+ (0x0047<< 2))
#define REG_FIQ_EXP_CLEAR_L         (REG_INT_BASE+ (0x004e<< 2))
#define REG_FIQ_EXP_CLEAR_H         (REG_INT_BASE+ (0x004f<< 2))
#define REG_FIQ_EXP_PENDING_L       (REG_INT_BASE+ (0x004e<< 2))
#define REG_FIQ_EXP_PENDING_H       (REG_INT_BASE+ (0x004f<< 2))
#endif

#define MSTAR_INT_BASE  8
/*******************************************************/
/*   THE IRQ AND FIQ ARE NOT COMPLETED.                */
/*   FOR EACH IP OWNER, PLEASE REVIEW IT BY YOURSELF   */
/*******************************************************/
typedef enum
{
    // IRQ
    E_IRQL_START                = 0 + MSTAR_INT_BASE,
    E_IRQ_UART0                 = E_IRQL_START  + 0,
    E_IRQ_MVD                   = E_IRQL_START  + 3,
    E_IRQ_PS                    = E_IRQL_START  + 4,
    E_IRQ_NFIE                  = E_IRQL_START  + 5,
    E_IRQ_USB                   = E_IRQL_START  + 6,
    E_IRQ_UHC                   = E_IRQL_START  + 7,
    E_IRQ_EC_BRIDGE             = E_IRQL_START  + 8,
    E_IRQ_EMAC                  = E_IRQL_START  + 9,
    E_IRQ_DISP                  = E_IRQL_START  + 10,
    E_IRQ_FRC_SC                = E_IRQL_START  + 11,
    E_IRQ_MIIC_DMA3             = E_IRQL_START  + 12,
    E_IRQ_MASTER_IIC3           = E_IRQL_START  + 13,
    E_IRQ_COMB                  = E_IRQL_START  + 14,
    E_IRQ_FRC_FIQ_TO_8051       = E_IRQL_START  + 15,
    E_IRQL_END                  = 15 + MSTAR_INT_BASE,

    E_IRQH_START                = 16 + MSTAR_INT_BASE,
    E_IRQ_TSP2HK                = E_IRQH_START  + 0,
    E_IRQ_VE                    = E_IRQH_START  + 1,
    E_IRQ_CIMAX2MCU             = E_IRQH_START  + 2,
    E_IRQ_DC                    = E_IRQH_START  + 3,
    E_IRQ_GOP                   = E_IRQH_START  + 4,
    E_IRQ_PCM                   = E_IRQH_START  + 5,
    E_IRQ_IIC0                  = E_IRQH_START  + 6,
    E_IRQ_SMART                 = E_IRQH_START  + 7,
    E_IRQ_DDC2BI                = E_IRQH_START  + 10,
    E_IRQ_SCM                   = E_IRQH_START  + 11,
    E_IRQ_VBI                   = E_IRQH_START  + 12,
    E_IRQ_MVD2MIPS              = E_IRQH_START  + 13,
    E_IRQ_GPD                   = E_IRQH_START  + 14,
    E_IRQ_ADCDVI2RIU            = E_IRQH_START  + 15,
    E_IRQH_END                  = 31 + MSTAR_INT_BASE,

    // FIQ
    E_FIQL_START                = 32 + MSTAR_INT_BASE,
    E_FIQ_EXTIMER0              = E_FIQL_START +  0,
    E_FIQ_EXTIMER1              = E_FIQL_START +  1,
    E_FIQ_WDT                   = E_FIQL_START +  2,
    E_FIQ_STRETCH               = E_FIQL_START +  3,
    E_FIQ_MB_AUR2TOMCU0         = E_FIQL_START +  4,
    E_FIQ_MB_AUR2TOMCU1         = E_FIQL_START +  5,
    E_FIQ_MB_DSP2TOMCU0         = E_FIQL_START +  6,
    E_FIQ_MB_DSP2TOMCU1         = E_FIQL_START +  7,
    E_FIQ_USB                   = E_FIQL_START +  8,
    E_FIQ_UHC                   = E_FIQL_START +  9,
    E_FIQ_HDMI_NON_PCM          = E_FIQL_START + 11,
    E_FIQ_SPDIF_IN_NON_PCM      = E_FIQL_START + 12,
    E_FIQ_EMAC                  = E_FIQL_START + 13,
    E_FIQ_SE_DSP2UP             = E_FIQL_START + 14,
    E_FIQ_TSP2AEON              = E_FIQL_START + 15,
    E_FIQL_END                  = 47 + MSTAR_INT_BASE,

    E_FIQH_START                = 48 + MSTAR_INT_BASE,
    E_FIQ_VIVALDI_STR           = E_FIQH_START +  0,
    E_FIQ_VIVALDI_PTS           = E_FIQH_START +  1,
    E_FIQ_DSP_MIU_PROT          = E_FIQH_START +  2,
    E_FIQ_XIU_TIMEOUT           = E_FIQH_START +  3,
    E_FIQ_DMDMCU2HK_INT         = E_FIQH_START +  4,
    E_FIQ_VSYNC_VE4VBI          = E_FIQH_START +  5,
    E_FIQ_FIELD_VE4VBI          = E_FIQH_START +  6,
    E_FIQ_VDMCU2HK              = E_FIQH_START +  7,
    E_FIQ_VE_DONE_TT            = E_FIQH_START +  8,
    E_FIQ_IR                    = E_FIQH_START + 11,
    E_FIQ_AFEC_VSYNC            = E_FIQH_START + 12,
    E_FIQ_DEC_DSP2UP            = E_FIQH_START + 13,
    E_FIQ_FRCR2MIPS             = E_FIQH_START + 14,
    E_FIQ_DSP2MIPS              = E_FIQH_START + 15,
    E_FIQH_END                  = 63 + MSTAR_INT_BASE,

    //IRQEXP
    E_IRQEXPL_START             = 64 + MSTAR_INT_BASE,
    E_IRQEXPL_HVD               = E_IRQEXPL_START+0,
    E_IRQEXPL_USB1              = E_IRQEXPL_START+1,
    E_IRQEXPL_UHC1              = E_IRQEXPL_START+2,
    E_IRQEXPL_MIU               = E_IRQEXPL_START+3,
    E_IRQEXPL_USB2              = E_IRQEXPL_START+4,
    E_IRQEXPL_UHC2              = E_IRQEXPL_START+5,
    E_IRQEXPL_AEON2HI           = E_IRQEXPL_START+6,
    E_IRQEXPL_UART1             = E_IRQEXPL_START+7,
    E_IRQEXPL_UART2             = E_IRQEXPL_START+8,
    E_IRQEXPL_FRC_IRQ2HST0      = E_IRQEXPL_START+9,
    E_IRQEXPL_MPIF              = E_IRQEXPL_START+10,
    E_IRQEXPL_MIIC_DMA2         = E_IRQEXPL_START+11,
    E_IRQEXPL_MASTER_IIC2       = E_IRQEXPL_START+12,
    E_IRQEXPL_JPD               = E_IRQEXPL_START+13,
    E_IRQEXPL_DISP_IPATH        = E_IRQEXPL_START+14,
    E_IRQEXPL_MFE               = E_IRQEXPL_START+15,
    E_IRQEXPL_END               = 79 + MSTAR_INT_BASE,

    E_IRQEXPH_START             = 80 + MSTAR_INT_BASE,
    E_IRQEXPH_BDMA0             = E_IRQEXPH_START+0,
    E_IRQEXPH_BDMA1             = E_IRQEXPH_START+1,
    E_IRQEXPH_UART2MCU          = E_IRQEXPH_START+2,
    E_IRQEXPH_URDMA2MCU         = E_IRQEXPH_START+3,
    E_IRQEXPH_DVI_HDMI_HDCP     = E_IRQEXPH_START+4,
    E_IRQEXPH_G3D2MCU           = E_IRQEXPH_START+5,
    E_IRQEXPH_CEC               = E_IRQEXPH_START+6,
    E_IRQEXPH_HDCP_IIC          = E_IRQEXPH_START+7,
    E_IRQEXPH_HDCP_X74          = E_IRQEXPH_START+8,
    E_IRQEXPH_WADR_ERR_INT      = E_IRQEXPH_START+9,
    E_IRQEXPH_DCSUB             = E_IRQEXPH_START+10,
    E_IRQEXPH_GE                = E_IRQEXPH_START+11,
    E_IRQEXPH_MIIC_DMA1         = E_IRQEXPH_START+12,
    E_IRQEXPH_MASTER_IIC1       = E_IRQEXPH_START+13,
    E_IRQEXPH_MIIC_DMA0         = E_IRQEXPH_START+14,
    E_IRQEXPH_MASTER_IIC0       = E_IRQEXPH_START+15,
    E_IRQEXPH_END               = 95 + MSTAR_INT_BASE,

    // FIQEXP
    E_FIQEXPL_START                     = 96 + MSTAR_INT_BASE,
    E_FIQEXPL_IR_INT_RC                 = E_FIQEXPL_START+0,
    E_FIQEXPL_AU_DMA_BUF_INT            = E_FIQEXPL_START+1,
    E_FIQEXPL_IR_IN                     = E_FIQEXPL_START+2,
    E_FIQEXPL_8051_TO_MIPS              = E_FIQEXPL_START+6,
    E_FIQEXPL_GPIO0                     = E_FIQEXPL_START+7,
    E_FIQEXPL_MIPS_TO_8051              = E_FIQEXPL_START+10,
    E_FIQEXPL_GPIO1                     = E_FIQEXPL_START+11,
    E_FIQEXPL_GPIO2                     = E_FIQEXPL_START+15,
    E_FIQEXPL_END                       = 111 + MSTAR_INT_BASE,

    E_FIQEXPH_START                     = 112 + MSTAR_INT_BASE,
    E_FIQEXPH_USB1                      = E_FIQEXPH_START+3,
    E_FIQEXPH_UHC1                      = E_FIQEXPH_START+4,
    E_FIQEXPH_USB2                      = E_FIQEXPH_START+5,
    E_FIQEXPH_UHC2                      = E_FIQEXPH_START+6,
    E_FIQEXPH_GPIO3                     = E_FIQEXPH_START+7,
    E_FIQEXPH_GPIO4                     = E_FIQEXPH_START+8,
    E_FIQEXPH_GPIO5                     = E_FIQEXPH_START+9,
    E_FIQEXPH_GPIO6                     = E_FIQEXPH_START+10,
    E_FIQEXPH_PWM_RP_I                  = E_FIQEXPH_START+11,
    E_FIQEXPH_PWM_FP_I                  = E_FIQEXPH_START+12,
    E_FIQEXPH_PWM_RP_R                  = E_FIQEXPH_START+13,
    E_FIQEXPH_PWM_FP_R                  = E_FIQEXPH_START+14,
    E_FIQEXPH_GPIO7                     = E_FIQEXPH_START+15,
    E_FIQEXPH_END                       = 127 + MSTAR_INT_BASE,

    // IRQ Virtual Low
    E_IRQVIRL_START                     = 128 + MSTAR_INT_BASE,
    E_IRQVIRL_END                       = 143 + MSTAR_INT_BASE,

    // FIQ Virtual Low
    E_FIQVIRL_START                     = 144 + MSTAR_INT_BASE,
    E_FIQVIRL_8051_TO_AEON              = E_FIQVIRL_START+0,
    E_FIQVIRL_AEON_TO_8051              = E_FIQVIRL_START+1,
    E_FIQVIRL_MIPS_TO_FRCR2             = E_FIQVIRL_START+2,
    E_FIQVIRL_END                       = 159 + MSTAR_INT_BASE,

    E_IRQ_FIQ_ALL               = 0xFF //all IRQs & FIQs
} InterruptNum;

    // REG_FIQ_MASK_L
    //FIQ Low 16 bits
    #define FIQL_MASK                           0xFFFF
    #define FIQ_EXTIMER0                        (0x1 << (E_FIQ_EXTIMER0         - E_FIQL_START) )
    #define FIQ_EXTIMER1                        (0x1 << (E_FIQ_EXTIMER1         - E_FIQL_START) )
    #define FIQ_WDT                             (0x1 << (E_FIQ_WDT              - E_FIQL_START) )
    #define FIQ_STRETCH                         (0x1 << (E_FIQ_STRETCH          - E_FIQL_START) )
    #define FIQ_MB_AUR2TOMCU0                   (0x1 << (E_FIQ_MB_AUR2TOMCU0    - E_FIQL_START) )
    #define FIQ_MB_AUR2TOMCU1                   (0x1 << (E_FIQ_MB_AUR2TOMCU1    - E_FIQL_START) )
    #define FIQ_MB_DSP2TOMCU0                   (0x1 << (E_FIQ_MB_DSP2TOMCU0    - E_FIQL_START) )
    #define FIQ_MB_DSP2TOMCU1                   (0x1 << (E_FIQ_MB_DSP2TOMCU1    - E_FIQL_START) )
    #define FIQ_USB                             (0x1 << (E_FIQ_USB              - E_FIQL_START) )
    #define FIQ_UHC                             (0x1 << (E_FIQ_UHC              - E_FIQL_START) )
    #define FIQ_HDMI_NON_PCM                    (0x1 << (E_FIQ_HDMI_NON_PCM     - E_FIQL_START) )
    #define FIQ_SPDIF_IN_NON_PCM                (0x1 << (E_FIQ_SPDIF_IN_NON_PCM - E_FIQL_START) )
    #define FIQ_EMAC                            (0x1 << (E_FIQ_EMAC             - E_FIQL_START) )
    #define FIQ_SE_DSP2UP                       (0x1 << (E_FIQ_SE_DSP2UP        - E_FIQL_START) )
    #define FIQ_TSP2AEON                        (0x1 << (E_FIQ_TSP2AEON         - E_FIQL_START) )


    // REG_FIQ_MASK_H
    //FIQ High 16 bits
    #define FIQH_MASK                           0xFFFF
    #define FIQ_VIVALDI_STR                     (0x1 << (E_FIQ_VIVALDI_STR      - E_FIQH_START) )
    #define FIQ_VIVALDI_PTS                     (0x1 << (E_FIQ_VIVALDI_PTS      - E_FIQH_START) )
    #define FIQ_DSP_MIU_PROT                    (0x1 << (E_FIQ_DSP_MIU_PROT     - E_FIQH_START) )
    #define FIQ_XIU_TIMEOUT                     (0x1 << (E_FIQ_XIU_TIMEOUT      - E_FIQH_START) )
    #define FIQ_DMDMCU2HK_INT                   (0x1 << (E_FIQ_DMDMCU2HK_INT    - E_FIQH_START) )
    #define FIQ_VSYNC_VE4VBI                    (0x1 << (E_FIQ_VSYNC_VE4VBI     - E_FIQH_START) )
    #define FIQ_FIELD_VE4VBI                    (0x1 << (E_FIQ_FIELD_VE4VBI     - E_FIQH_START) )
    #define FIQ_VDMCU2HK                        (0x1 << (E_FIQ_VDMCU2HK         - E_FIQH_START) )
    #define FIQ_VE_DONE_TT                      (0x1 << (E_FIQ_VE_DONE_TT       - E_FIQH_START) )
    #define FIQ_IR                              (0x1 << (E_FIQ_IR               - E_FIQH_START) )
    #define FIQ_AFEC_VSYNC                      (0x1 << (E_FIQ_AFEC_VSYNC       - E_FIQH_START) )
    #define FIQ_DEC_DSP2UP                      (0x1 << (E_FIQ_DEC_DSP2UP       - E_FIQH_START) )
    #define FIQ_FRCR2MIPS                       (0x1 << (E_FIQ_FRCR2MIPS        - E_FIQH_START) )
    #define FIQ_DSP2MIPS                        (0x1 << (E_FIQ_DSP2MIPS         - E_FIQH_START) )



    // #define REG_IRQ_PENDING_L
    #define IRQL_MASK                           0xFFFF
    #define IRQ_UART0                           (0x1 << (E_IRQ_UART0            - E_IRQL_START) )
    #define IRQ_MVD                             (0x1 << (E_IRQ_MVD              - E_IRQL_START) )
    #define IRQ_PS                              (0x1 << (E_IRQ_PS               - E_IRQL_START) )
    #define IRQ_NFIE                            (0x1 << (E_IRQ_NFIE             - E_IRQL_START) )
    #define IRQ_USB                             (0x1 << (E_IRQ_USB              - E_IRQL_START) )
    #define IRQ_UHC                             (0x1 << (E_IRQ_UHC              - E_IRQL_START) )
    #define IRQ_EC_BRIDGE                       (0x1 << (E_IRQ_EC_BRIDGE        - E_IRQL_START) )
    #define IRQ_EMAC                            (0x1 << (E_IRQ_EMAC             - E_IRQL_START) )
    #define IRQ_DISP                            (0x1 << (E_IRQ_DISP             - E_IRQL_START) )
    #define IRQ_FRC_SC                          (0x1 << (E_IRQ_FRC_SC           - E_IRQL_START) )
    #define IRQ_MIIC_DMA3                       (0x1 << (E_IRQ_MIIC_DMA3        - E_IRQL_START) )
    #define IRQ_MASTER_IIC3                     (0x1 << (E_IRQ_MASTER_IIC3      - E_IRQL_START) )
    #define IRQ_COMB                            (0x1 << (E_IRQ_COMB             - E_IRQL_START) )
    #define IRQ_FRC_FIQ_TO_8051                 (0x1 << (E_IRQ_FRC_FIQ_TO_8051  - E_IRQL_START) )


    // #define REG_IRQ_PENDING_H
    #define IRQH_MASK                           0xFFFF
    #define IRQ_TSP2HK                          (0x1 << (E_IRQ_TSP2HK           - E_IRQH_START) )
    #define IRQ_VE                              (0x1 << (E_IRQ_VE               - E_IRQH_START) )
    #define IRQ_CIMAX2MCU                       (0x1 << (E_IRQ_CIMAX2MCU        - E_IRQH_START) )
    #define IRQ_DC                              (0x1 << (E_IRQ_DC               - E_IRQH_START) )
    #define IRQ_GOP                             (0x1 << (E_IRQ_GOP              - E_IRQH_START) )
    #define IRQ_PCM                             (0x1 << (E_IRQ_PCM              - E_IRQH_START) )
    #define IRQ_IIC0                            (0x1 << (E_IRQ_IIC0             - E_IRQH_START) )
    #define IRQ_SMART                           (0x1 << (E_IRQ_SMART            - E_IRQH_START) )
    #define IRQ_DDC2BI                          (0x1 << (E_IRQ_DDC2BI           - E_IRQH_START) )
    #define IRQ_SCM                             (0x1 << (E_IRQ_SCM              - E_IRQH_START) )
    #define IRQ_VBI                             (0x1 << (E_IRQ_VBI              - E_IRQH_START) )
    #define IRQ_MVD2MIPS                        (0x1 << (E_IRQ_MVD2MIPS         - E_IRQH_START) )
    #define IRQ_GPD                             (0x1 << (E_IRQ_GPD              - E_IRQH_START) )
    #define IRQ_ADCDVI2RIU                      (0x1 << (E_IRQ_ADCDVI2RIU       - E_IRQH_START) )

    // #define REG_IRQEXP_PENDING_L
    #define IRQEXPL_MASK                        0xFFFF
    #define IRQEXPL_HVD                         (0x1 << (E_IRQEXPL_HVD          - E_IRQEXPL_START) )
    #define IRQEXPL_USB1                        (0x1 << (E_IRQEXPL_USB1         - E_IRQEXPL_START) )
    #define IRQEXPL_UHC1                        (0x1 << (E_IRQEXPL_UHC1         - E_IRQEXPL_START) )
    #define IRQEXPL_MIU                         (0x1 << (E_IRQEXPL_MIU          - E_IRQEXPL_START) )
    #define IRQEXPL_USB2                        (0x1 << (E_IRQEXPL_USB2         - E_IRQEXPL_START) )
    #define IRQEXPL_UHC2                        (0x1 << (E_IRQEXPL_UHC2         - E_IRQEXPL_START) )
    #define IRQEXPL_AEON2HI                     (0x1 << (E_IRQEXPL_AEON2HI      - E_IRQEXPL_START) )
    #define IRQEXPL_UART1                       (0x1 << (E_IRQEXPL_UART1        - E_IRQEXPL_START) )
    #define IRQEXPL_UART2                       (0x1 << (E_IRQEXPL_UART2        - E_IRQEXPL_START) )
    #define IRQEXPL_FRC_IRQ2HST0                (0x1 << (E_IRQEXPL_FRC_IRQ2HST0 - E_IRQEXPL_START) )
    #define IRQEXPL_MPIF                        (0x1 << (E_IRQEXPL_MPIF         - E_IRQEXPL_START) )
    #define IRQEXPL_MIIC_DMA2                   (0x1 << (E_IRQEXPL_MIIC_DMA2    - E_IRQEXPL_START) )
    #define IRQEXPL_MASTER_IIC2                 (0x1 << (E_IRQEXPL_MASTER_IIC2  - E_IRQEXPL_START) )
    #define IRQEXPL_JPD                         (0x1 << (E_IRQEXPL_JPD          - E_IRQEXPL_START) )
    #define IRQEXPL_DISP_IPATH                  (0x1 << (E_IRQEXPL_DISP_IPATH   - E_IRQEXPL_START) )
    #define IRQEXPL_MFE                         (0x1 << (E_IRQEXPL_MFE          - E_IRQEXPL_START) )

    // #define REG_IRQEXP_PENDING_H
    #define IRQEXPH_MASK                        0xFFFF
    #define IRQEXPH_BDMA0                       (0x1 << (E_IRQEXPH_BDMA0        - E_IRQEXPH_START) )
    #define IRQEXPH_BDMA1                       (0x1 << (E_IRQEXPH_BDMA1        - E_IRQEXPH_START) )
    #define IRQEXPH_UART2MCU                    (0x1 << (E_IRQEXPH_UART2MCU     - E_IRQEXPH_START) )
    #define IRQEXPH_URDMA2MCU                   (0x1 << (E_IRQEXPH_URDMA2MCU    - E_IRQEXPH_START) )
    #define IRQEXPH_DVI_HDMI_HDCP               (0x1 << (E_IRQEXPH_DVI_HDMI_HDCP- E_IRQEXPH_START) )
    #define IRQEXPH_G3D2MCU                     (0x1 << (E_IRQEXPH_G3D2MCU      - E_IRQEXPH_START) )
    #define IRQEXPH_CEC                         (0x1 << (E_IRQEXPH_CEC          - E_IRQEXPH_START) )
    #define IRQEXPH_HDCP_IIC                    (0x1 << (E_IRQEXPH_HDCP_IIC     - E_IRQEXPH_START) )
    #define IRQEXPH_HDCP_X74                    (0x1 << (E_IRQEXPH_HDCP_X74     - E_IRQEXPH_START) )
    #define IRQEXPH_WADR_ERR_INT                (0x1 << (E_IRQEXPH_WADR_ERR_INT - E_IRQEXPH_START) )
    #define IRQEXPH_DCSUB                       (0x1 << (E_IRQEXPH_DCSUB        - E_IRQEXPH_START) )
    #define IRQEXPH_GE                          (0x1 << (E_IRQEXPH_GE           - E_IRQEXPH_START) )
    #define IRQEXPH_MIIC_DMA1                   (0x1 << (E_IRQEXPH_MIIC_DMA1    - E_IRQEXPH_START) )
    #define IRQEXPH_MASTER_IIC1                 (0x1 << (E_IRQEXPH_MASTER_IIC1  - E_IRQEXPH_START) )
    #define IRQEXPH_MIIC_DMA0                   (0x1 << (E_IRQEXPH_MIIC_DMA0    - E_IRQEXPH_START) )
    #define IRQEXPH_MASTER_IIC0                 (0x1 << (E_IRQEXPH_MASTER_IIC0  - E_IRQEXPH_START) )

    // #define REG_FIQEXP_PENDING_L
    #define FIQEXPL_MASK                        0xFFFF
    #define FIQEXPL_IR_INT_RC                   (0x1 << (E_FIQEXPL_IR_INT_RC     - E_FIQEXPL_START) )
    #define FIQEXPL_AU_DMA_BUF_INT              (0x1 << (E_FIQEXPL_AU_DMA_BUF_INT- E_FIQEXPL_START) )
    #define FIQEXPL_IR_IN                       (0x1 << (E_FIQEXPL_IR_IN         - E_FIQEXPL_START) )
    #define FIQEXPL_8051_TO_MIPS                (0x1 << (E_FIQEXPL_8051_TO_MIPS  - E_FIQEXPL_START) )
    #define FIQEXPL_GPIO0                       (0x1 << (E_FIQEXPL_GPIO0         - E_FIQEXPL_START) )
    #define FIQEXPL_MIPS_TO_8051                (0x1 << (E_FIQEXPL_MIPS_TO_8051  - E_FIQEXPL_START) )
    #define FIQEXPL_GPIO1                       (0x1 << (E_FIQEXPL_GPIO1         - E_FIQEXPL_START) )
    #define FIQEXPL_GPIO2                       (0x1 << (E_FIQEXPL_GPIO2         - E_FIQEXPL_START) )

    // #define REG_FIQEXP_PENDING_H
    #define FIQEXPH_MASK                        0xFFFF
    #define FIQEXPH_USB1                        (0x1 << (E_FIQEXPH_USB1          - E_FIQEXPH_START) )
    #define FIQEXPH_UHC1                        (0x1 << (E_FIQEXPH_UHC1          - E_FIQEXPH_START) )
    #define FIQEXPH_USB2                        (0x1 << (E_FIQEXPH_USB2          - E_FIQEXPH_START) )
    #define FIQEXPH_UHC2                        (0x1 << (E_FIQEXPH_UHC2          - E_FIQEXPH_START) )
    #define FIQEXPH_GPIO3                       (0x1 << (E_FIQEXPH_GPIO3         - E_FIQEXPH_START) )
    #define FIQEXPH_GPIO4                       (0x1 << (E_FIQEXPH_GPIO4         - E_FIQEXPH_START) )
    #define FIQEXPH_GPIO5                       (0x1 << (E_FIQEXPH_GPIO5         - E_FIQEXPH_START) )
    #define FIQEXPH_GPIO6                       (0x1 << (E_FIQEXPH_GPIO6         - E_FIQEXPH_START) )
    #define FIQEXPH_PWM_RP_I                    (0x1 << (E_FIQEXPH_PWM_RP_I      - E_FIQEXPH_START) )
    #define FIQEXPH_PWM_FP_I                    (0x1 << (E_FIQEXPH_PWM_FP_I      - E_FIQEXPH_START) )
    #define FIQEXPH_PWM_RP_R                    (0x1 << (E_FIQEXPH_PWM_RP_R      - E_FIQEXPH_START) )
    #define FIQEXPH_PWM_FP_R                    (0x1 << (E_FIQEXPH_PWM_FP_R      - E_FIQEXPH_START) )
    #define FIQEXPH_GPIO7                       (0x1 << (E_FIQEXPH_GPIO7         - E_FIQEXPH_START) )

#define IRQL_EXP_ALL                    0xFFFF
#define IRQH_EXP_ALL                    0xFFFF
#define FIQL_EXP_ALL                    0xFFFF
#define FIQH_EXP_ALL                    0xFFFF

#endif // #ifndef __CHIP_INT_H__