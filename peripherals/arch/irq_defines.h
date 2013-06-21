/*===========================================================================
        Copyright (C) 2009-2011, iSOFT INFRASTRUCTURE SOFTWARE CO.,LTD.

        All rights reserved. This software is iSOFT property. Duplication 
        or disclosure without iSOFT written authorization is prohibited.

 ===========================================================================*/

#ifndef IRQ_TYPES_H
#define IRQ_TYPES_H

  /* Software interrupts. */
#define INTC_SSCIR0_3_CLR0  0
#define INTC_SSCIR0_3_CLR1  1
#define INTC_SSCIR0_3_CLR2  2
#define INTC_SSCIR0_3_CLR3  3
#define INTC_SSCIR0_7_CLR4  4
#define INTC_SSCIR0_7_CLR5  5
#define INTC_SSCIR0_7_CLR6  6
#define INTC_SSCIR0_7_CLR7  7 
#define MCM_MSWTIR_SWTIC    8
#define MCM_ESR_COMB        9
  /* eDMA */
#define EDMA_ERRL_ERR31_0   10
#define EDMA_INTL_INT0      11
#define EDMA_INTL_INT1      12
#define EDMA_INTL_INT2      13
#define EDMA_INTL_INT3      14
#define EDMA_INTL_INT4      15
#define EDMA_INTL_INT5      16
#define EDMA_INTL_INT6      17
#define EDMA_INTL_INT7      18
#define EDMA_INTL_INT8      19
#define EDMA_INTL_INT9      20
#define EDMA_INTL_INT10     21
#define EDMA_INTL_INT11     22
#define EDMA_INTL_INT12     23
#define EDMA_INTL_INT13     24
#define EDMA_INTL_INT14     25
#define EDMA_INTL_INT15     26
#define EDMA_INTL_INT16     27
#define EDMA_INTL_INT17     28
#define EDMA_INTL_INT18     29
#define EDMA_INTL_INT19     30
#define EDMA_INTL_INT20     31
#define EDMA_INTL_INT21     32
#define EDMA_INTL_INT22     33
#define EDMA_INTL_INT23     34
#define EDMA_INTL_INT24     35
#define EDMA_INTL_INT25     36
#define EDMA_INTL_INT26     37
#define EDMA_INTL_INT27     38
#define EDMA_INTL_INT28     39
#define EDMA_INTL_INT29     40
#define EDMA_INTL_INT30     41
#define EDMA_INTL_INT31     42

#define FMPLL_SYNSR_LOCF    43
#define FMPLL_SYNSR_LOLF    44
#define SIU_OSR_OVER        45
  /* External interrupts */
#define SIU_EISR_EIF0       46
#define SIU_EISR_EIF1       47
#define SIU_EISR_EIF2       48
#define SIU_EISR_EIF3       49
#define SIU_EISR_EIF15_4    50

  /* eMIOS */
#define EMIOS_FLAG_F0       51
#define EMIOS_FLAG_F1       52
#define EMIOS_FLAG_F2       53
#define EMIOS_FLAG_F3       54
#define EMIOS_FLAG_F4       55
#define EMIOS_FLAG_F5       56
#define EMIOS_FLAG_F6       57
#define EMIOS_FLAG_F7       58
#define EMIOS_FLAG_F8       59
#define EMIOS_FLAG_F9       60
#define EMIOS_FLAG_F10      61
#define EMIOS_FLAG_F11      62
#define EMIOS_FLAG_F12      63
#define EMIOS_FLAG_F13      64
#define EMIOS_FLAG_F14      65
#define EMIOS_FLAG_F15      66
  /* eTPU */
#define ETPU_MCR_GE         67
#define ETPU_CISR_1_CIS0    68
#define ETPU_CISR_1_CIS1    69
#define ETPU_CISR_1_CIS2    70
#define ETPU_CISR_1_CIS3    71
#define ETPU_CISR_1_CIS4    72
#define ETPU_CISR_1_CIS5    73
#define ETPU_CISR_1_CIS6    74
#define ETPU_CISR_1_CIS7    75
#define ETPU_CISR_1_CIS8    76
#define ETPU_CISR_1_CIS9    77
#define ETPU_CISR_1_CIS10   78
#define ETPU_CISR_1_CIS11   79
#define ETPU_CISR_1_CIS12   80
#define ETPU_CISR_1_CIS13   81
#define ETPU_CISR_1_CIS14   82
#define ETPU_CISR_1_CIS15   83
#define ETPU_CISR_1_CIS16   84
#define ETPU_CISR_1_CIS17   85
#define ETPU_CISR_1_CIS18   86
#define ETPU_CISR_1_CIS19   87
#define ETPU_CISR_1_CIS20   88
#define ETPU_CISR_1_CIS21   89
#define ETPU_CISR_1_CIS22   90
#define ETPU_CISR_1_CIS23   91
#define ETPU_CISR_1_CIS24   92
#define ETPU_CISR_1_CIS25   93
#define ETPU_CISR_1_CIS26   94
#define ETPU_CISR_1_CIS27   95
#define ETPU_CISR_1_CIS28   96
#define ETPU_CISR_1_CIS29   97
#define ETPU_CISR_1_CIS30   98
#define ETPU_CISR_1_CIS31   99

  /* eQADC */
#define EQADC_FISR_OVER     100
#define EQADC_FISR0_NCF0    101
#define EQADC_FISR0_PF0     102
#define EQADC_FISR0_EOQF0   103
#define EQADC_FISR0_CFFF0   104
#define EQADC_FISR0_RFDF0   105
#define EQADC_FISR1_NCF1    106
#define EQADC_FISR1_PF1     107
#define EQADC_FISR1_EOQF1   108
#define EQADC_FISR1_CFFF1   109
#define EQADC_FISR1_RFDF1   110
#define EQADC_FISR2_NCF2    111
#define EQADC_FISR2_PF2     112
#define EQADC_FISR2_EOQF2   113
#define EQADC_FISR2_CFFF2   114
#define EQADC_FISR2_RFDF2   115
#define EQADC_FISR3_NCF3    116
#define EQADC_FISR3_PF3     117
#define EQADC_FISR3_EOQF3   118
#define EQADC_FISR3_CFFF3   119
#define EQADC_FISR3_RFDF3   120
#define EQADC_FISR4_NCF4    121
#define EQADC_FISR4_PF4     122
#define EQADC_FISR4_EOQF4   123
#define EQADC_FISR4_CFFF4   124
#define EQADC_FISR4_RFDF4   125
#define EQADC_FISR5_NCF5    126
#define EQADC_FISR5_PF5     127
#define EQADC_FISR5_EOQF5   128
#define EQADC_FISR5_CFFF5   129
#define EQADC_FISR5_RFDF5   130

  /* DSPI */
#define DSPI_B_ISR_OVER     131
#define DSPI_B_ISR_EOQF     132
#define DSPI_B_ISR_TFFF     133
#define DSPI_B_ISR_TCF      134
#define DSPI_B_ISR_RFDF     135
#define DSPI_C_ISR_OVER     136
#define DSPI_C_ISR_EOQF     137
#define DSPI_C_ISR_TFFF     138
#define DSPI_C_ISR_TCF      139
#define DSPI_C_ISR_RFDF     140

  /* eSCI */
#define ESCI_A_COMB         146
#define ESCI_B_COMB         149
  /* FlexCAN A */
#define FLEXCAN_A_ESR_BOFF_INT  152
#define FLEXCAN_A_ESR_ERR_INT   153
#define FLEXCAN_A_WAKEUP_INT    154
#define FLEXCAN_A_IFLAG1_BUF0I  155
#define FLEXCAN_A_IFLAG1_BUF1I  156
#define FLEXCAN_A_IFLAG1_BUF2I  157
#define FLEXCAN_A_IFLAG1_BUF3I  158
#define FLEXCAN_A_IFLAG1_BUF4I  159
#define FLEXCAN_A_IFLAG1_BUF5I  160
#define FLEXCAN_A_IFLAG1_BUF6I  161
#define FLEXCAN_A_IFLAG1_BUF7I  162
#define FLEXCAN_A_IFLAG1_BUF8I  163
#define FLEXCAN_A_IFLAG1_BUF9I  164
#define FLEXCAN_A_IFLAG1_BUF10I 165
#define FLEXCAN_A_IFLAG1_BUF11I 166
#define FLEXCAN_A_IFLAG1_BUF12I 167
#define FLEXCAN_A_IFLAG1_BUF13I 168
#define FLEXCAN_A_IFLAG1_BUF14I 169
#define FLEXCAN_A_IFLAG1_BUF15I 170
#define FLEXCAN_A_IFLAG1_BUF31_16I  171
#define FLEXCAN_A_IFLAG1_BUF63_32I  172
  
  /* FlexCAN C */
#define FLEXCAN_C_ESR_BOFF_INT  173
#define FLEXCAN_C_ESR_ERR_INT   174
#define FLEXCAN_C_WAKEUP_INT    175
#define FLEXCAN_C_IFLAG1_BUF0I  176
#define FLEXCAN_C_IFLAG1_BUF1I  177
#define FLEXCAN_C_IFLAG1_BUF2I  178
#define FLEXCAN_C_IFLAG1_BUF3I  179
#define FLEXCAN_C_IFLAG1_BUF4I  180
#define FLEXCAN_C_IFLAG1_BUF5I  181
#define FLEXCAN_C_IFLAG1_BUF6I  182
#define FLEXCAN_C_IFLAG1_BUF7I  183
#define FLEXCAN_C_IFLAG1_BUF8I  184
#define FLEXCAN_C_IFLAG1_BUF9I  185
#define FLEXCAN_C_IFLAG1_BUF10I 186
#define FLEXCAN_C_IFLAG1_BUF11I 187
#define FLEXCAN_C_IFLAG1_BUF12I 188
#define FLEXCAN_C_IFLAG1_BUF13I 189
#define FLEXCAN_C_IFLAG1_BUF14I 190
#define FLEXCAN_C_IFLAG1_BUF15I 191
#define FLEXCAN_C_IFLAG1_BUF31_16I  192
  
#define DECFIL_A_IN     197
#define DECFIL_A_OUT    198
#define DECFIL_A_ERR    199
#define STM0            200
#define STM1_3          201
  
  /* EMIOS */
#define EMIOS_FLAG_F23  209
  
  /* PIT */
#define PIT0    301
#define PIT1    302
#define PIT2    303
#define PIT3    304
#define RTI_INT 305
#define PMC_INT 306
#define FLASH_ECC_INT   307
  
  /* STM */
#define STM1    358
#define STM2    359
#define STM3    360

#endif
