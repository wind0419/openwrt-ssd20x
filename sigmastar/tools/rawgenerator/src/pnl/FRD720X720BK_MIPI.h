#ifndef PNL_TABLE_FRD720X720BK
#define PNL_TABLE_FRD720X720BK
#define FLAG_DELAY            0xFE
#define FLAG_END_OF_TABLE     0xFF   // END OF REGISTERS MARKER

MhalPnlParamConfig_t stPanel_FRD720X720BK =
{
    "FRD720X720BK_60", // const char *m_pPanelName;                ///<  PanelName
#if !defined (__aarch64__)
    0,
#endif
    0, //MS_U8 m_bPanelDither :1;                 ///<  PANEL_DITHER, keep the setting
    E_MHAL_PNL_LINK_MIPI_DSI, //MHAL_DISP_ApiPnlLinkType_e m_ePanelLinkType   :4;  ///<  PANEL_LINK

    ///////////////////////////////////////////////
    // Board related setting
    ///////////////////////////////////////////////
    1,  //MS_U8 m_bPanelDualPort  :1;              ///<  VOP_21[8], MOD_4A[1],    PANEL_DUAL_PORT, refer to m_bPanelDoubleClk
    0,  //MS_U8 m_bPanelSwapPort  :1;              ///<  MOD_4A[0],               PANEL_SWAP_PORT, refer to "LVDS output app note" A/B channel swap
    0,  //MS_U8 m_bPanelSwapOdd_ML    :1;          ///<  PANEL_SWAP_ODD_ML
    0,  //MS_U8 m_bPanelSwapEven_ML   :1;          ///<  PANEL_SWAP_EVEN_ML
    0,  //MS_U8 m_bPanelSwapOdd_RB    :1;          ///<  PANEL_SWAP_ODD_RB
    0,  //MS_U8 m_bPanelSwapEven_RB   :1;          ///<  PANEL_SWAP_EVEN_RB

    0,  //MS_U8 m_bPanelSwapLVDS_POL  :1;          ///<  MOD_40[5], PANEL_SWAP_LVDS_POL, for differential P/N swap
    0,  //MS_U8 m_bPanelSwapLVDS_CH   :1;          ///<  MOD_40[6], PANEL_SWAP_LVDS_CH, for pair swap
    0,  //MS_U8 m_bPanelPDP10BIT      :1;          ///<  MOD_40[3], PANEL_PDP_10BIT ,for pair swap
    1,  //MS_U8 m_bPanelLVDS_TI_MODE  :1;          ///<  MOD_40[2], PANEL_LVDS_TI_MODE, refer to "LVDS output app note"

    ///////////////////////////////////////////////
    // For TTL Only
    ///////////////////////////////////////////////
    0,  //MS_U8 m_ucPanelDCLKDelay;                ///<  PANEL_DCLK_DELAY
    0,  //MS_U8 m_bPanelInvDCLK   :1;              ///<  MOD_4A[4],                   PANEL_INV_DCLK
    0,  //MS_U8 m_bPanelInvDE     :1;              ///<  MOD_4A[2],                   PANEL_INV_DE
    0,  //MS_U8 m_bPanelInvHSync  :1;              ///<  MOD_4A[12],                  PANEL_INV_HSYNC
    0,  //MS_U8 m_bPanelInvVSync  :1;              ///<  MOD_4A[3],                   PANEL_INV_VSYNC

    ///////////////////////////////////////////////
    // Output driving current setting
    ///////////////////////////////////////////////
    // driving current setting (0x00=4mA, 0x01=6mA, 0x02=8mA, 0x03=12mA)
    1,  //MS_U8 m_ucPanelDCKLCurrent;              ///<  define PANEL_DCLK_CURRENT
    1,  //MS_U8 m_ucPanelDECurrent;                ///<  define PANEL_DE_CURRENT
    1,  //MS_U8 m_ucPanelODDDataCurrent;           ///<  define PANEL_ODD_DATA_CURRENT
    1,  //MS_U8 m_ucPanelEvenDataCurrent;          ///<  define PANEL_EVEN_DATA_CURRENT

    ///////////////////////////////////////////////
    // panel on/off timing
    ///////////////////////////////////////////////
    30,  //MS_U16 m_wPanelOnTiming1;                ///<  time between panel & data while turn on power
    400,  //MS_U16 m_wPanelOnTiming2;                ///<  time between data & back light while turn on power
    80,  //MS_U16 m_wPanelOffTiming1;               ///<  time between back light & data while turn off power
    30,  //MS_U16 m_wPanelOffTiming2;               ///<  time between data & panel while turn off power

    ///////////////////////////////////////////////
    // panel timing spec.
    ///////////////////////////////////////////////
    // sync related
    20,  //MS_U8 m_ucPanelHSyncWidth;               ///<  VOP_01[7:0], PANEL_HSYNC_WIDTH
    20,  //MS_U8 m_ucPanelHSyncBackPorch;           ///<  PANEL_HSYNC_BACK_PORCH, no register setting, provide value for query only

                                             ///<  not support Manuel VSync Start/End now
                                             ///<  VOP_02[10:0] VSync start = Vtt - VBackPorch - VSyncWidth
                                             ///<  VOP_03[10:0] VSync end = Vtt - VBackPorch
    10,  //MS_U8 m_ucPanelVSyncWidth;               ///<  define PANEL_VSYNC_WIDTH
    10,  //MS_U8 m_ucPanelVBackPorch;               ///<  define PANEL_VSYNC_BACK_PORCH

    // DE related
    40,  //MS_U16 m_wPanelHStart;                   ///<  VOP_04[11:0], PANEL_HSTART, DE H Start (PANEL_HSYNC_WIDTH + PANEL_HSYNC_BACK_PORCH)
    20,  //MS_U16 m_wPanelVStart;                   ///<  VOP_06[11:0], PANEL_VSTART, DE V Start
    720,  //MS_U16 m_wPanelWidth;                    ///< PANEL_WIDTH, DE width (VOP_05[11:0] = HEnd = HStart + Width - 1)
    720,  //MS_U16 m_wPanelHeight;                   ///< PANEL_HEIGHT, DE height (VOP_07[11:0], = Vend = VStart + Height - 1)

    // DClk related
    0,  //MS_U16 m_wPanelMaxHTotal;                ///<  PANEL_MAX_HTOTAL. Reserved for future using.
    790,  //MS_U16 m_wPanelHTotal;                   ///<  VOP_0C[11:0], PANEL_HTOTAL
    0,  //MS_U16 m_wPanelMinHTotal;                ///<  PANEL_MIN_HTOTAL. Reserved for future using.

    0,  //MS_U16 m_wPanelMaxVTotal;                ///<  PANEL_MAX_VTOTAL. Reserved for future using.
    755,  //MS_U16 m_wPanelVTotal;                   ///<  VOP_0D[11:0], PANEL_VTOTAL
    0,  //MS_U16 m_wPanelMinVTotal;                ///<  PANEL_MIN_VTOTAL. Reserved for future using.

    0,  //MS_U8 m_dwPanelMaxDCLK;                  ///<  PANEL_MAX_DCLK. Reserved for future using.
    33,  //MS_U8 m_dwPanelDCLK;                     ///<  LPLL_0F[23:0], PANEL_DCLK          ,{0x3100_10[7:0], 0x3100_0F[15:0]}
    0,  //MS_U8 m_dwPanelMinDCLK;                  ///<  PANEL_MIN_DCLK. Reserved for future using.
                                             ///<  spread spectrum
    0,  //MS_U16 m_wSpreadSpectrumStep;            ///<  move to board define, no use now.
    0,  //MS_U16 m_wSpreadSpectrumSpan;            ///<  move to board define, no use now.

    160,  //MS_U8 m_ucDimmingCtl;                    ///<  Initial Dimming Value
    255,  //MS_U8 m_ucMaxPWMVal;                     ///<  Max Dimming Value
    80,  //MS_U8 m_ucMinPWMVal;                     ///<  Min Dimming Value

    0,  //MS_U8 m_bPanelDeinterMode   :1;          ///<  define PANEL_DEINTER_MODE,  no use now
    E_MHAL_PNL_ASPECT_RATIO_WIDE,  //MHAL_DISP_PnlAspectRatio_e m_ucPanelAspectRatio; ///<  Panel Aspect Ratio, provide information to upper layer application for aspect ratio setting.
  /*
    *
    * Board related params
    *
    *  If a board ( like BD_MST064C_D01A_S ) swap LVDS TX polarity
    *    : This polarity swap value =
    *      (LVDS_PN_SWAP_H<<8) | LVDS_PN_SWAP_L from board define,
    *  Otherwise
    *    : The value shall set to 0.
    */
    0,  //MS_U16 m_u16LVDSTxSwapValue;
    E_MHAL_PNL_TI_8BIT_MODE,  //MHAL_DISP_ApiPnlTiBitMode_e m_ucTiBitMode;                         ///< MOD_4B[1:0], refer to "LVDS output app note"
    E_MHAL_PNL_OUTPUT_8BIT_MODE,  //MHAL_DISP_ApiPnlOutPutFormatBitMode_e m_ucOutputFormatBitMode;

    0,  //MS_U8 m_bPanelSwapOdd_RG    :1;          ///<  define PANEL_SWAP_ODD_RG
    0,  //MS_U8 m_bPanelSwapEven_RG   :1;          ///<  define PANEL_SWAP_EVEN_RG
    0,  //MS_U8 m_bPanelSwapOdd_GB    :1;          ///<  define PANEL_SWAP_ODD_GB
    0,  //MS_U8 m_bPanelSwapEven_GB   :1;          ///<  define PANEL_SWAP_EVEN_GB

    /**
    *  Others
    */
    1,  //MS_U8 m_bPanelDoubleClk     :1;             ///<  LPLL_03[7], define Double Clock ,LVDS dual mode
    0x001c848e,  //MS_U32 m_dwPanelMaxSET;                     ///<  define PANEL_MAX_SET
    0x0018eb59,  //MS_U32 m_dwPanelMinSET;                     ///<  define PANEL_MIN_SET
    E_MHAL_PNL_CHG_VTOTAL,  //MHAL_DISP_ApiPnlOutTimingMode_e m_ucOutTimingMode;   ///<Define which panel output timing change mode is used to change VFreq for same panel
    0,  //MS_U8 m_bPanelNoiseDith     :1;             ///<  PAFRC mixed with noise dither disable
    E_MHAL_PNL_CH_SWAP_2,
    E_MHAL_PNL_CH_SWAP_4,
    E_MHAL_PNL_CH_SWAP_3,
    E_MHAL_PNL_CH_SWAP_1,
    E_MHAL_PNL_CH_SWAP_0,
};

u8 ST720BK_INIT_CMD[] =
{
    0xB9,3,0xFF,
    0x83,0x94,
    0xBA,15,
    0x33,0x03,
    0x68,0x6B,
    0xB2,0xC0,
    0x00,0x01,
    0x00,0x00,0x00,0x80,0x08,0x3D,0x7A,
    0xB1,10,0x50,0x12,0x12,0x89,0x33,0x54,0x71,0x31,0x55,0x2F,
    0xB2,6,0x00,0x00,0x1E,0x0E,0x0D,0x2F,
    0xB4,21,0x04,0x65,0x04,0x65,0x04,0x65,0x01,0x05,0x7E,0x35,0x00,0x3F,0x04,
    0x65,0x04,0x65,0x04,0x65,0x05,0x04,0x7E,
    0xD3,33,0x00,0x00,0x07,0x07,0x00,0x00,0x10,0x00,0x32,0x10,0x05,0x00,0x00,
    0x32,0x10,0x00,0x00,0x00,0x32,0x10,0x00,0x00,0x00,0x36,0x03,0x09,0x09,0x37,0x00,0x00,0x37,0x0E,0x40,
    0xD5,44,0x25,0x24,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x19,0x19,0x21,
    0x20,0x23,0x22,0x02,0x03,0x00,0x01,0x06,0x07,0x04,0x05,0x18,0x18,0x18,0x18,
    0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,0x18,
    0xE0,58,0x00,0x26,0x31,0x37,0x3B,0x40,0x42,0x40,0x81,0x92,0xA0,0x9C,0xA3,
    0xB3,0xB6,0xB8,0xC5,0xC6,0xC1,0xCC,0xD8,0x6C,0x72,0x75,0x78,0x7B,0x7D,0x7E,0x7F,0x00,0x26,0x31,0x37,0x3B,0x40,0x42,0x40,0x81,0x92,0xA0,0x9C,0xA3,0xB3,0xB6,
    0xB8,0xC5,0xC6,0xC1,0xCC,0xD8,0x6C,0x72,0x75,0x78,0x7B,0x7D,0x7E,0x7F,
    0xCC,1,0x0B,
    0xC0,2,0x1F,0x73,
    0xC7,4,0x00,0x00,0x00,0x00,
    0xD4,1,0x02,
    0xB6,2,0x64,0x64,
    0x11,0,0,
    FLAG_DELAY,FLAG_DELAY,200,
    0x29,0,0,
    FLAG_DELAY, FLAG_DELAY,20,
    FLAG_END_OF_TABLE, FLAG_END_OF_TABLE,
};

MhalPnlMipiDsiConfig_t stMipiDsiConfig_FRD720X720BK =
{
    //HsTrail HsPrpr HsZero ClkHsPrpr ClkHsExit ClkTrail ClkZero ClkHsPost DaHsExit ContDet
    5,      3,     5,     10,       14,       3,       12,     10,       5,       0,
    //Lpx   TaGet  TaSure  TaGo
    16,   26,    24,     50,

    //Hac,  Hpw,  Hbp, Hfp, Vac,  Vpw,  Vbp, Vfp,  Bllp, Fps
    720,    20,   20,  30,  720,  10,    10,  20,   0,    60,

    E_MHAL_PNL_MIPI_DSI_LANE_4,      // MhalPnlMipiDsiLaneMode_e enLaneNum;
    E_MHAL_PNL_MIPI_DSI_RGB888,      // MhalPnlMipiDsiFormat_e enFormat;
    E_MHAL_PNL_MIPI_DSI_SYNC_PULSE,  // MhalPnlMipiDsiCtrlMode_e enCtrl;

    ST720BK_INIT_CMD,
    sizeof(ST720BK_INIT_CMD),
    1, 0x01AF, 0x01B9, 0x80D2, 7,
};
#endif //PNL_TABLE_FRD720X720BK