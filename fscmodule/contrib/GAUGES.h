#ifndef	__GAUGES_H__
#define __GAUGES_H__

#pragma pack(4)

// Bit Flag Constants
#define BIT0    0x00000001
#define BIT1    0x00000002
#define BIT2    0x00000004
#define BIT3    0x00000008
#define BIT4    0x00000010
#define BIT5    0x00000020
#define BIT6    0x00000040
#define BIT7    0x00000080
#define BIT8    0x00000100
#define BIT9    0x00000200
#define BIT10   0x00000400
#define BIT11   0x00000800
#define BIT12   0x00001000
#define BIT13   0x00002000
#define BIT14   0x00004000
#define BIT15   0x00008000
#define BIT16   0x00010000
#define BIT17   0x00020000
#define BIT18   0x00040000
#define BIT19   0x00080000
#define BIT20   0x00100000
#define BIT21   0x00200000
#define BIT22   0x00400000
#define BIT23   0x00800000
#define BIT24   0x01000000
#define BIT25   0x02000000
#define BIT26   0x04000000
#define BIT27   0x08000000
#define BIT28   0x10000000
#define BIT29   0x20000000
#define BIT30   0x40000000
#define BIT31   0x80000000

#define	DLLEXPORT __declspec(dllexport)
#define	FSAPI __stdcall

typedef CHAR    STRING, *PSTRING, **PPSTRING;       // generic string of unknown length
typedef CHAR    STRINGZ, *PSTRINGZ, **PPSTRINGZ;    // generic string of unknown length, zero term
typedef const CHAR  *PCSTRINGZ, **PPCSTRINGZ;   // generic string of unknown length, zero term
typedef void            *PVOID;
typedef PVOID           *PPVOID;
typedef unsigned    char    UINT8, *PUINT8, **PPUINT8;
typedef signed      char    SINT8, *PSINT8, **PPSINT8;
typedef unsigned    short   UINT16, *PUINT16, **PPUINT16;
typedef signed      short   SINT16, *PSINT16, **PPSINT16;
typedef signed      int     SINT32, *PSINT32, **PPSINT32;
typedef unsigned    char    VAR8, *PVAR8, **PPVAR8;
typedef unsigned    short   VAR16, *PVAR16, **PPVAR16;
typedef unsigned    int     VAR32, *PVAR32, **PPVAR32;
typedef int     FLAGS, *PFLAGS, **PPFLAGS;
typedef VAR8    FLAGS8, *PFLAGS8, **PPFLAGS8;
typedef VAR16   FLAGS16, *PFLAGS16, **PPFLAGS16;
typedef VAR32   FLAGS32, *PFLAGS32, **PPFLAGS32;
typedef int     ENUM, *PENUM, **PPENUM;
typedef VAR8    ENUM8, *PENUM8, **PPENUM8;
typedef VAR16   ENUM16, *PENUM16, **PPENUM16;
typedef VAR32   ENUM32, *PENUM32, **PPENUM32;
typedef int     INDX, *PINDX, **PPINDX;
typedef VAR8    INDX8, *PINDX8, **PPINDX8;
typedef VAR16   INDX16, *PINDX16, **PPINDX16;
typedef VAR32   INDX32, *PINDX32, **PPINDX32;
typedef int     ID, *PID, **PPID;
typedef VAR8    ID8, *PID8, **PPID8;
typedef VAR16   ID16, *PID16, **PPID16;
typedef VAR32   ID32, *PID32, **PPID32;
typedef double  FLOAT64, *PFLOAT64, **PPFLOAT64;
typedef float   FLOAT32, *PFLOAT32, **PPFLOAT32;
typedef VAR32   ERR, *PERR, **PPERR;

//
// Key Accelerator Event Handling
//
typedef void (FSAPI *GAUGE_KEY_EVENT_HANDLER) (ID32 event, UINT32 evdata, PVOID userdata);

//
// Key Accelerator Event IDs
//
#define KEY_ID_MIN                      0x00010000

#define KEY_NULL                        (KEY_ID_MIN + 0)
#define KEY_DEMO_STOP                   (KEY_ID_MIN + 1)
#define KEY_REPLAY_STOP                 (KEY_ID_MIN + 1)
#define KEY_SELECT_1                    (KEY_ID_MIN + 2)
#define KEY_SELECT_2                    (KEY_ID_MIN + 3)
#define KEY_SELECT_3                    (KEY_ID_MIN + 4)
#define KEY_SELECT_4                    (KEY_ID_MIN + 5)
#define KEY_DEMO_RECORD_1_SEC           (KEY_ID_MIN + 7)
#define KEY_DEMO_RECORD_5_SEC           (KEY_ID_MIN + 8)
#define KEY_MINUS                       (KEY_ID_MIN + 12)
#define KEY_PLUS                        (KEY_ID_MIN + 13)
#define KEY_ZOOM_1X                     (KEY_ID_MIN + 14)
#define KEY_PANEL_SELECT_1              (KEY_ID_MIN + 15)
#define KEY_SOUND_TOGGLE                (KEY_ID_MIN + 16)
#define KEY_FULL_WINDOW_TOGGLE          (KEY_ID_MIN + 17)
#define KEY_ENGINE                      (KEY_ID_MIN + 18)
#define KEY_SIM_RATE                    (KEY_ID_MIN + 19)
#define KEY_XPNDR                       (KEY_ID_MIN + 20)
#define KEY_SLEW_TOGGLE                 (KEY_ID_MIN + 21)
#define KEY_EGT                         (KEY_ID_MIN + 22)
#define KEY_SMOKE_TOGGLE                (KEY_ID_MIN + 23)
#define KEY_STROBES_TOGGLE              (KEY_ID_MIN + 24)
#define KEY_PAUSE_TOGGLE                (KEY_ID_MIN + 25)
#define KEY_REFRESH_SCENERY             (KEY_ID_MIN + 26)
#define KEY_ATC                         (KEY_ID_MIN + 28)
#define KEY_ADF                         (KEY_ID_MIN + 30)
#define KEY_VIEW_MODE                   (KEY_ID_MIN + 31)
#define KEY_HEADING_GYRO_SET            (KEY_ID_MIN + 32)
#define KEY_DME                         (KEY_ID_MIN + 33)
#define KEY_GEAR_TOGGLE                 (KEY_ID_MIN + 34)
#define KEY_ANTI_ICE_TOGGLE             (KEY_ID_MIN + 35)
#define KEY_JET_STARTER                 (KEY_ID_MIN + 36)
#define KEY_JOYSTICK_CALIBRATE          (KEY_ID_MIN + 37)
#define KEY_ALL_LIGHTS_TOGGLE           (KEY_ID_MIN + 38)
#define KEY_SITUATION_SAVE              (KEY_ID_MIN + 39)
#define KEY_VIEW_WINDOW_TO_FRONT        (KEY_ID_MIN + 40)
#define KEY_DEMO_RECORD_STOP            (KEY_ID_MIN + 43)
#define KEY_ANALYSIS_MANEUVER_STOP      (KEY_ID_MIN + 43)
#define KEY_AP_MASTER                   (KEY_ID_MIN + 44)
#define KEY_FREQUENCY_SWAP              (KEY_ID_MIN + 45)
#define KEY_COM_RADIO                   (KEY_ID_MIN + 46)
#define KEY_VOR_OBS                     (KEY_ID_MIN + 47)
#define KEY_BAROMETRIC                  (KEY_ID_MIN + 48)
#define KEY_NAV_RADIO                   (KEY_ID_MIN + 49)
#define KEY_MAGNETO                     (KEY_ID_MIN + 50)
#define KEY_DEMO_RECORD_MESSAGE         (KEY_ID_MIN + 51)
#define KEY_BRAKES                      (KEY_ID_MIN + 52)
#define KEY_SPOILERS_TOGGLE             (KEY_ID_MIN + 53)
#define KEY_SITUATION_RESET             (KEY_ID_MIN + 55)
#define KEY_FLAPS_UP                    (KEY_ID_MIN + 59)
#define KEY_THROTTLE_FULL               (KEY_ID_MIN + 60)
#define KEY_FLAPS_1                     (KEY_ID_MIN + 61)
#define KEY_THROTTLE_INCR               (KEY_ID_MIN + 62)
#define KEY_FLAPS_2                     (KEY_ID_MIN + 63)
#define KEY_THROTTLE_INCR_SMALL         (KEY_ID_MIN + 64)
#define KEY_FLAPS_3                     (KEY_ID_MIN + 65)
#define KEY_THROTTLE_DECR               (KEY_ID_MIN + 66)
#define KEY_FLAPS_4                     (KEY_ID_MIN + 67)
#define KEY_FLAPS_DOWN                  (KEY_ID_MIN + 67)
#define KEY_THROTTLE_CUT                (KEY_ID_MIN + 68)
#define KEY_VIEW                        (KEY_ID_MIN + 70)
#define KEY_ELEV_TRIM_DN                (KEY_ID_MIN + 71)
#define KEY_ELEV_DOWN                   (KEY_ID_MIN + 72)
#define KEY_INCREASE_THROTTLE           (KEY_ID_MIN + 73)
#define KEY_AILERONS_LEFT               (KEY_ID_MIN + 75)
#define KEY_CENTER_AILER_RUDDER         (KEY_ID_MIN + 76)
#define KEY_AILERONS_RIGHT              (KEY_ID_MIN + 77)
#define KEY_ELEV_TRIM_UP                (KEY_ID_MIN + 79)
#define KEY_ELEV_UP                     (KEY_ID_MIN + 80)
#define KEY_DECREASE_THROTTLE           (KEY_ID_MIN + 81)
#define KEY_MOUSE_AS_YOKE_TOGGLE        (KEY_ID_MIN + 83)
#define KEY_SLEW_ALTIT_UP_FAST          (KEY_ID_MIN + 84)
#define KEY_SLEW_ALTIT_UP_SLOW          (KEY_ID_MIN + 85)
#define KEY_SLEW_ALTIT_FREEZE           (KEY_ID_MIN + 86)
#define KEY_SLEW_ALTIT_DN_SLOW          (KEY_ID_MIN + 87)
#define KEY_SLEW_ALTIT_DN_FAST          (KEY_ID_MIN + 88)
#define KEY_SLEW_ALTIT_PLUS             (KEY_ID_MIN + 89)
#define KEY_SLEW_ALTIT_MINUS            (KEY_ID_MIN + 90)
#define KEY_SLEW_PITCH_DN_FAST          (KEY_ID_MIN + 91)
#define KEY_SLEW_PITCH_DN_SLOW          (KEY_ID_MIN + 92)
#define KEY_SLEW_PITCH_FREEZE           (KEY_ID_MIN + 93)
#define KEY_SLEW_PITCH_UP_SLOW          (KEY_ID_MIN + 94)
#define KEY_SLEW_PITCH_UP_FAST          (KEY_ID_MIN + 95)
#define KEY_SLEW_PITCH_PLUS             (KEY_ID_MIN + 96)
#define KEY_SLEW_PITCH_MINUS            (KEY_ID_MIN + 97)
#define KEY_MAGNETO_DECR                (KEY_ID_MIN + 98)
#define KEY_MAGNETO_INCR                (KEY_ID_MIN + 99)
#define KEY_COM_RADIO_WHOLE_DEC         (KEY_ID_MIN + 100)
#define KEY_COM_RADIO_WHOLE_INC         (KEY_ID_MIN + 101)
#define KEY_COM_RADIO_FRACT_DEC         (KEY_ID_MIN + 102)
#define KEY_COM_RADIO_FRACT_INC         (KEY_ID_MIN + 103)
#define KEY_NAV1_RADIO_WHOLE_DEC        (KEY_ID_MIN + 104)
#define KEY_NAV1_RADIO_WHOLE_INC        (KEY_ID_MIN + 105)
#define KEY_NAV1_RADIO_FRACT_DEC        (KEY_ID_MIN + 106)
#define KEY_NAV1_RADIO_FRACT_INC        (KEY_ID_MIN + 107)
#define KEY_NAV2_RADIO_WHOLE_DEC        (KEY_ID_MIN + 108)
#define KEY_NAV2_RADIO_WHOLE_INC        (KEY_ID_MIN + 109)
#define KEY_NAV2_RADIO_FRACT_DEC        (KEY_ID_MIN + 110)
#define KEY_NAV2_RADIO_FRACT_INC        (KEY_ID_MIN + 111)
#define KEY_ADF_100_INC                 (KEY_ID_MIN + 112)
#define KEY_ADF_10_INC                  (KEY_ID_MIN + 113)
#define KEY_ADF_1_INC                   (KEY_ID_MIN + 114)
#define KEY_XPNDR_1000_INC              (KEY_ID_MIN + 115)
#define KEY_XPNDR_100_INC               (KEY_ID_MIN + 116)
#define KEY_XPNDR_10_INC                (KEY_ID_MIN + 117)
#define KEY_XPNDR_1_INC                 (KEY_ID_MIN + 118)
#define KEY_ZOOM_IN                     (KEY_ID_MIN + 119)
#define KEY_ZOOM_OUT                    (KEY_ID_MIN + 120)
#define KEY_CLOCK_HOURS_DEC             (KEY_ID_MIN + 121)
#define KEY_CLOCK_HOURS_INC             (KEY_ID_MIN + 122)
#define KEY_CLOCK_MINUTES_DEC           (KEY_ID_MIN + 123)
#define KEY_CLOCK_MINUTES_INC           (KEY_ID_MIN + 124)
#define KEY_CLOCK_SECONDS_ZERO          (KEY_ID_MIN + 125)
#define KEY_VOR1_OBI_DEC                (KEY_ID_MIN + 126)
#define KEY_VOR1_OBI_INC                (KEY_ID_MIN + 127)
#define KEY_VOR2_OBI_DEC                (KEY_ID_MIN + 128)
#define KEY_VOR2_OBI_INC                (KEY_ID_MIN + 129)
#define KEY_ADF_100_DEC                 (KEY_ID_MIN + 130)
#define KEY_ADF_10_DEC                  (KEY_ID_MIN + 131)
#define KEY_ADF_1_DEC                   (KEY_ID_MIN + 132)
#define KEY_AP_MASTER_ALT               (KEY_ID_MIN + 133)
#define KEY_MAP_ZOOM_FINE_IN            (KEY_ID_MIN + 134)
#define KEY_PAN_LEFT                    (KEY_ID_MIN + 135)
#define KEY_PAN_RIGHT                   (KEY_ID_MIN + 136)
#define KEY_MAP_ZOOM_FINE_OUT           (KEY_ID_MIN + 137)
#define KEY_VIEW_FORWARD                (KEY_ID_MIN + 138)
#define KEY_VIEW_FORWARD_RIGHT          (KEY_ID_MIN + 139)
#define KEY_VIEW_RIGHT                  (KEY_ID_MIN + 140)
#define KEY_VIEW_REAR_RIGHT             (KEY_ID_MIN + 141)
#define KEY_VIEW_REAR                   (KEY_ID_MIN + 142)
#define KEY_VIEW_REAR_LEFT              (KEY_ID_MIN + 143)
#define KEY_VIEW_LEFT                   (KEY_ID_MIN + 144)
#define KEY_VIEW_FORWARD_LEFT           (KEY_ID_MIN + 145)
#define KEY_VIEW_DOWN                   (KEY_ID_MIN + 146)
#define KEY_ELEVATOR_DOWN               (KEY_ID_MIN + 147)
#define KEY_ELEVATOR_UP                 (KEY_ID_MIN + 148)
#define KEY_AILERON_LEFT                (KEY_ID_MIN + 149)
#define KEY_AILERON_CENTER              (KEY_ID_MIN + 150)
#define KEY_AILERON_RIGHT               (KEY_ID_MIN + 151)
#define KEY_RUDDER_LEFT                 (KEY_ID_MIN + 152)
#define KEY_RUDDER_CENTER               (KEY_ID_MIN + 153)
#define KEY_RUDDER_RIGHT                (KEY_ID_MIN + 154)
#define KEY_VIEW1_MODE_SET              (KEY_ID_MIN + 155)
#define KEY_SOUND_SET                   (KEY_ID_MIN + 156)
#define KEY_VIEW1_DIRECTION_SET         (KEY_ID_MIN + 157)
#define KEY_ELEVATOR_SET                (KEY_ID_MIN + 158)
#define KEY_AILERON_SET                 (KEY_ID_MIN + 159)
#define KEY_RUDDER_SET                  (KEY_ID_MIN + 160)
#define KEY_THROTTLE_SET                (KEY_ID_MIN + 161)
#define KEY_FLAPS_SET                   (KEY_ID_MIN + 162)
#define KEY_GEAR_SET                    (KEY_ID_MIN + 164)
#define KEY_VIEW1_ZOOM_SET              (KEY_ID_MIN + 165)
#define KEY_AXIS_IND_SET                (KEY_ID_MIN + 166)
#define KEY_ELEVATOR_TRIM_SET           (KEY_ID_MIN + 170)
#define KEY_COM_RADIO_SET               (KEY_ID_MIN + 171)
#define KEY_NAV1_RADIO_SET              (KEY_ID_MIN + 172)
#define KEY_NAV2_RADIO_SET              (KEY_ID_MIN + 173)
#define KEY_VIEW2_MODE_SET              (KEY_ID_MIN + 174)
#define KEY_VIEW2_DIRECTION_SET         (KEY_ID_MIN + 175)
#define KEY_VIEW2_ZOOM_SET              (KEY_ID_MIN + 176)
#define KEY_MAP_ZOOM_SET                (KEY_ID_MIN + 177)
#define KEY_ADF_SET                     (KEY_ID_MIN + 178)
#define KEY_XPNDR_SET                   (KEY_ID_MIN + 179)
#define KEY_VOR1_SET                    (KEY_ID_MIN + 180)
#define KEY_VOR2_SET                    (KEY_ID_MIN + 181)
#define KEY_ZOOM_MINUS                  (KEY_ID_MIN + 182)
#define KEY_ZOOM_PLUS                   (KEY_ID_MIN + 183)
#define KEY_BRAKES_LEFT                 (KEY_ID_MIN + 184)
#define KEY_BRAKES_RIGHT                (KEY_ID_MIN + 185)
#define KEY_AP_ATT_HOLD                 (KEY_ID_MIN + 186)
#define KEY_AP_LOC_HOLD                 (KEY_ID_MIN + 187)
#define KEY_AP_APR_HOLD                 (KEY_ID_MIN + 188)
#define KEY_AP_HDG_HOLD                 (KEY_ID_MIN + 189)
#define KEY_AP_ALT_HOLD                 (KEY_ID_MIN + 190)
#define KEY_AP_WING_LEVELER             (KEY_ID_MIN + 191)
#define KEY_AP_BC_HOLD                  (KEY_ID_MIN + 192)
#define KEY_AP_NAV1_HOLD                (KEY_ID_MIN + 193)
#define KEY_SLEW_OFF                    (KEY_ID_MIN + 194)
#define KEY_SLEW_ON                     (KEY_ID_MIN + 195)
#define KEY_EXIT                        (KEY_ID_MIN + 196)
#define KEY_ABORT                       (KEY_ID_MIN + 197)
#define KEY_PAN_UP                      (KEY_ID_MIN + 198)
#define KEY_PAN_DOWN                    (KEY_ID_MIN + 199)
#define KEY_READOUTS_SLEW               (KEY_ID_MIN + 200)
#define KEY_READOUTS_FLIGHT             (KEY_ID_MIN + 201)
#define KEY_SLEW_BANK_MINUS             (KEY_ID_MIN + 202)
#define KEY_SLEW_AHEAD_PLUS             (KEY_ID_MIN + 203)
#define KEY_SLEW_BANK_PLUS              (KEY_ID_MIN + 204)
#define KEY_SLEW_LEFT                   (KEY_ID_MIN + 205)
#define KEY_SLEW_FREEZE                 (KEY_ID_MIN + 206)
#define KEY_SLEW_RIGHT                  (KEY_ID_MIN + 207)
#define KEY_SLEW_HEADING_MINUS          (KEY_ID_MIN + 208)
#define KEY_SLEW_AHEAD_MINUS            (KEY_ID_MIN + 209)
#define KEY_SLEW_HEADING_PLUS           (KEY_ID_MIN + 210)
#define KEY_PANEL_SELECT_2              (KEY_ID_MIN + 211)
#define KEY_PANEL_TOGGLE                (KEY_ID_MIN + 212)
#define KEY_VIEW_MODE_REV               (KEY_ID_MIN + 213)
#define KEY_PANEL_LIGHTS_TOGGLE         (KEY_ID_MIN + 214)
#define KEY_LANDING_LIGHTS_TOGGLE       (KEY_ID_MIN + 215)
#define KEY_PARKING_BRAKES              (KEY_ID_MIN + 216)
#define KEY_ZOOM_IN_FINE                (KEY_ID_MIN + 218)
#define KEY_ZOOM_OUT_FINE               (KEY_ID_MIN + 219)
#define KEY_MINUS_SHIFT                 (KEY_ID_MIN + 220)
#define KEY_PLUS_SHIFT                  (KEY_ID_MIN + 221)
#define KEY_FLAPS_INCR                  (KEY_ID_MIN + 222)
#define KEY_FLAPS_DECR                  (KEY_ID_MIN + 223)
#define KEY_FLAPS_DETENTS_SET           (KEY_ID_MIN + 224)
#define KEY_AXIS_ELEVATOR_SET           (KEY_ID_MIN + 226)
#define KEY_AXIS_AILERONS_SET           (KEY_ID_MIN + 227)
#define KEY_AXIS_RUDDER_SET             (KEY_ID_MIN + 228)
#define KEY_AXIS_THROTTLE_SET           (KEY_ID_MIN + 229)
#define KEY_AXIS_ELEV_TRIM_SET          (KEY_ID_MIN + 230)
#define KEY_PROP_PITCH_SET              (KEY_ID_MIN + 231)
#define KEY_PROP_PITCH_LO               (KEY_ID_MIN + 232)
#define KEY_PROP_PITCH_INCR             (KEY_ID_MIN + 233)
#define KEY_PROP_PITCH_INCR_SMALL       (KEY_ID_MIN + 234)
#define KEY_PROP_PITCH_DECR             (KEY_ID_MIN + 235)
#define KEY_PROP_PITCH_HI               (KEY_ID_MIN + 236)
#define KEY_MIXTURE_SET                 (KEY_ID_MIN + 237)
#define KEY_MIXTURE_RICH                (KEY_ID_MIN + 238)
#define KEY_MIXTURE_INCR                (KEY_ID_MIN + 239)
#define KEY_MIXTURE_INCR_SMALL          (KEY_ID_MIN + 240)
#define KEY_MIXTURE_DECR                (KEY_ID_MIN + 241)
#define KEY_MIXTURE_LEAN                (KEY_ID_MIN + 242)
#define KEY_SCRIPT_EVENT_1              (KEY_ID_MIN + 246)
#define KEY_SCRIPT_EVENT_2              (KEY_ID_MIN + 247)
#define KEY_SPOILERS_SET                (KEY_ID_MIN + 250)
#define KEY_DME1_TOGGLE                 (KEY_ID_MIN + 251)
#define KEY_DME2_TOGGLE                 (KEY_ID_MIN + 252)
#define KEY_SIM_RATE_INCR               (KEY_ID_MIN + 253)
#define KEY_SIM_RATE_DECR               (KEY_ID_MIN + 254)
#define KEY_AUTOPILOT_OFF               (KEY_ID_MIN + 255)
#define KEY_AUTOPILOT_ON                (KEY_ID_MIN + 256)
#define KEY_YAW_DAMPER_TOGGLE           (KEY_ID_MIN + 257)
#define KEY_PAUSE_ON                    (KEY_ID_MIN + 258)
#define KEY_PAUSE_OFF                   (KEY_ID_MIN + 259)
#define KEY_SLEW_RESET                  (KEY_ID_MIN + 260)
#define KEY_AP_PANEL_HEADING_HOLD       (KEY_ID_MIN + 262)
#define KEY_AP_PANEL_ALTITUDE_HOLD      (KEY_ID_MIN + 263)
#define KEY_CHVPP_LEFT_HAT_UP           (KEY_ID_MIN + 264)
#define KEY_CHVPP_LEFT_HAT_DOWN         (KEY_ID_MIN + 265)
#define KEY_CHVPP_AP_ALT_WING           (KEY_ID_MIN + 266)
#define KEY_CENTER_NT361_CHECK          (KEY_ID_MIN + 267)
#define KEY_AP_ATT_HOLD_ON              (KEY_ID_MIN + 268)
#define KEY_AP_LOC_HOLD_ON              (KEY_ID_MIN + 269)
#define KEY_AP_APR_HOLD_ON              (KEY_ID_MIN + 270)
#define KEY_AP_HDG_HOLD_ON              (KEY_ID_MIN + 271)
#define KEY_AP_ALT_HOLD_ON              (KEY_ID_MIN + 272)
#define KEY_AP_WING_LEVELER_ON          (KEY_ID_MIN + 273)
#define KEY_AP_BC_HOLD_ON               (KEY_ID_MIN + 274)
#define KEY_AP_NAV1_HOLD_ON             (KEY_ID_MIN + 275)
#define KEY_AP_ATT_HOLD_OFF             (KEY_ID_MIN + 276)
#define KEY_AP_LOC_HOLD_OFF             (KEY_ID_MIN + 277)
#define KEY_AP_APR_HOLD_OFF             (KEY_ID_MIN + 278)
#define KEY_AP_HDG_HOLD_OFF             (KEY_ID_MIN + 279)
#define KEY_AP_ALT_HOLD_OFF             (KEY_ID_MIN + 280)
#define KEY_AP_WING_LEVELER_OFF         (KEY_ID_MIN + 281)
#define KEY_AP_BC_HOLD_OFF              (KEY_ID_MIN + 282)
#define KEY_AP_NAV1_HOLD_OFF            (KEY_ID_MIN + 283)
#define KEY_THROTTLE1_SET               (KEY_ID_MIN + 284)
#define KEY_THROTTLE2_SET               (KEY_ID_MIN + 285)
#define KEY_THROTTLE3_SET               (KEY_ID_MIN + 286)
#define KEY_THROTTLE4_SET               (KEY_ID_MIN + 287)
#define KEY_CLOSE_VIEW                  (KEY_ID_MIN + 288)
#define KEY_NEW_VIEW                    (KEY_ID_MIN + 289)
#define KEY_NEW_MAP                     (KEY_ID_MIN + 290)
#define KEY_NEXT_VIEW                   (KEY_ID_MIN + 291)
#define KEY_PREV_VIEW                   (KEY_ID_MIN + 292)
#define KEY_VIEW_TYPE                   (KEY_ID_MIN + 293)
#define KEY_VIEW_TYPE_REV               (KEY_ID_MIN + 294)
#define KEY_VIEW_TYPE_SET               (KEY_ID_MIN + 295)
#define KEY_RADIO_VOR1_IDENT_DISABLE    (KEY_ID_MIN + 296)
#define KEY_RADIO_VOR2_IDENT_DISABLE    (KEY_ID_MIN + 297)
#define KEY_RADIO_DME1_IDENT_DISABLE    (KEY_ID_MIN + 298)
#define KEY_RADIO_DME2_IDENT_DISABLE    (KEY_ID_MIN + 299)
#define KEY_RADIO_ADF_IDENT_DISABLE     (KEY_ID_MIN + 300)
#define KEY_RADIO_VOR1_IDENT_ENABLE     (KEY_ID_MIN + 301)
#define KEY_RADIO_VOR2_IDENT_ENABLE     (KEY_ID_MIN + 302)
#define KEY_RADIO_DME1_IDENT_ENABLE     (KEY_ID_MIN + 303)
#define KEY_RADIO_DME2_IDENT_ENABLE     (KEY_ID_MIN + 304)
#define KEY_RADIO_ADF_IDENT_ENABLE      (KEY_ID_MIN + 305)
#define KEY_RADIO_VOR1_IDENT_TOGGLE     (KEY_ID_MIN + 306)
#define KEY_RADIO_VOR2_IDENT_TOGGLE     (KEY_ID_MIN + 307)
#define KEY_RADIO_DME1_IDENT_TOGGLE     (KEY_ID_MIN + 308)
#define KEY_RADIO_DME2_IDENT_TOGGLE     (KEY_ID_MIN + 309)
#define KEY_RADIO_ADF_IDENT_TOGGLE      (KEY_ID_MIN + 310)
#define KEY_RADIO_VOR1_IDENT_SET        (KEY_ID_MIN + 311)
#define KEY_RADIO_VOR2_IDENT_SET        (KEY_ID_MIN + 312)
#define KEY_RADIO_DME1_IDENT_SET        (KEY_ID_MIN + 313)
#define KEY_RADIO_DME2_IDENT_SET        (KEY_ID_MIN + 314)
#define KEY_RADIO_ADF_IDENT_SET         (KEY_ID_MIN + 315)
#define KEY_GEAR_PUMP                   (KEY_ID_MIN + 316)
#define KEY_SPOILERS_ARM_TOGGLE         (KEY_ID_MIN + 317)
#define KEY_PAN_LEFT_UP                 (KEY_ID_MIN + 318)
#define KEY_PAN_LEFT_DOWN               (KEY_ID_MIN + 319)
#define KEY_PAN_RIGHT_UP                (KEY_ID_MIN + 320)
#define KEY_PAN_RIGHT_DOWN              (KEY_ID_MIN + 321)
#define KEY_PITOT_HEAT_TOGGLE           (KEY_ID_MIN + 322)
#define KEY_AP_AIRSPEED_HOLD            (KEY_ID_MIN + 323)
#define KEY_AUTO_THROTTLE_ARM           (KEY_ID_MIN + 324)
#define KEY_AUTO_THROTTLE_TO_GA         (KEY_ID_MIN + 325)
#define KEY_LANDING_LIGHT_UP            (KEY_ID_MIN + 326)
#define KEY_LANDING_LIGHT_DOWN          (KEY_ID_MIN + 327)
#define KEY_LANDING_LIGHT_LEFT          (KEY_ID_MIN + 328)
#define KEY_LANDING_LIGHT_RIGHT         (KEY_ID_MIN + 329)
#define KEY_LANDING_LIGHT_HOME          (KEY_ID_MIN + 330)
#define KEY_AXIS_SLEW_AHEAD_SET         (KEY_ID_MIN + 331)
#define KEY_AXIS_SLEW_SIDEWAYS_SET      (KEY_ID_MIN + 332)
#define KEY_AXIS_SLEW_HEADING_SET       (KEY_ID_MIN + 333)
#define KEY_AXIS_SLEW_ALT_SET           (KEY_ID_MIN + 334)
#define KEY_AXIS_SLEW_BANK_SET          (KEY_ID_MIN + 335)
#define KEY_AXIS_SLEW_PITCH_SET         (KEY_ID_MIN + 336)
#define KEY_PAN_TILT_LEFT               (KEY_ID_MIN + 337)
#define KEY_PAN_TILT_RIGHT              (KEY_ID_MIN + 338)
#define KEY_PAN_RESET                   (KEY_ID_MIN + 339)
#define KEY_KNEEBOARD                   (KEY_ID_MIN + 340)
#define KEY_GYRO_DRIFT_INC              (KEY_ID_MIN + 341)
#define KEY_GYRO_DRIFT_DEC              (KEY_ID_MIN + 342)
#define KEY_HEADING_BUG_INC             (KEY_ID_MIN + 343)
#define KEY_HEADING_BUG_DEC             (KEY_ID_MIN + 344)
#define KEY_ADF_CARD_INC                (KEY_ID_MIN + 345)
#define KEY_ADF_CARD_DEC                (KEY_ID_MIN + 346)
#define KEY_KOHLSMAN_INC                (KEY_ID_MIN + 347)
#define KEY_KOHLSMAN_DEC                (KEY_ID_MIN + 348)
#define KEY_TRUE_AIRSPEED_CALIBRATE_INC (KEY_ID_MIN + 349)
#define KEY_TRUE_AIRSPEED_CALIBRATE_DEC (KEY_ID_MIN + 350)
#define KEY_CROSS_FEED_OFF              (KEY_ID_MIN + 351)
#define KEY_CROSS_FEED_LEFT_TO_RIGHT    (KEY_ID_MIN + 352)
#define KEY_CROSS_FEED_RIGHT_TO_LEFT    (KEY_ID_MIN + 353)
#define KEY_AP_PANEL_VS_HOLD            (KEY_ID_MIN + 354)
#define KEY_AP_PANEL_SPEED_HOLD         (KEY_ID_MIN + 355)
#define KEY_AP_ALT_VAR_INC              (KEY_ID_MIN + 356)
#define KEY_AP_ALT_VAR_DEC              (KEY_ID_MIN + 357)
#define KEY_AP_VS_VAR_INC               (KEY_ID_MIN + 358)
#define KEY_AP_VS_VAR_DEC               (KEY_ID_MIN + 359)
#define KEY_AP_SPD_VAR_INC              (KEY_ID_MIN + 360)
#define KEY_AP_SPD_VAR_DEC              (KEY_ID_MIN + 361)
#define KEY_AP_N1_REF_INC               (KEY_ID_MIN + 362)
#define KEY_AP_N1_REF_DEC               (KEY_ID_MIN + 363)
#define KEY_MULTIPLAYER_TRACK_TOGGLE    (KEY_ID_MIN + 364)
#define KEY_MULTIPLAYER_PLAYER_TOGGLE   (KEY_ID_MIN + 365)
#define KEY_MULTIPLAYER_PLAYER_SNAP     (KEY_ID_MIN + 366)
#define KEY_MULTIPLAYER_GO_OBSERVER     (KEY_ID_MIN + 367)
#define KEY_MULTIPLAYER_CHAT            (KEY_ID_MIN + 368)
#define KEY_MULTIPLAYER_ACTIVATE_CHAT   (KEY_ID_MIN + 369)
#define KEY_PANEL_1                     (KEY_ID_MIN + 370)
#define KEY_PANEL_2                     (KEY_ID_MIN + 371)
#define KEY_PANEL_3                     (KEY_ID_MIN + 372)
#define KEY_PANEL_4                     (KEY_ID_MIN + 373)
#define KEY_PANEL_5                     (KEY_ID_MIN + 374)
#define KEY_PANEL_6                     (KEY_ID_MIN + 375)
#define KEY_PANEL_7                     (KEY_ID_MIN + 376)
#define KEY_PANEL_8                     (KEY_ID_MIN + 377)
#define KEY_PANEL_9                     (KEY_ID_MIN + 378)
#define KEY_AP_PANEL_MACH_HOLD          (KEY_ID_MIN + 379)
#define KEY_AP_MACH_VAR_INC             (KEY_ID_MIN + 380)
#define KEY_AP_MACH_VAR_DEC             (KEY_ID_MIN + 381)
#define KEY_AP_MACH_HOLD                (KEY_ID_MIN + 382)
#define KEY_MIXTURE1_SET                (KEY_ID_MIN + 383)
#define KEY_MIXTURE2_SET                (KEY_ID_MIN + 384)
#define KEY_MIXTURE3_SET                (KEY_ID_MIN + 385)
#define KEY_MIXTURE4_SET                (KEY_ID_MIN + 386)
#define KEY_PROP_PITCH1_SET             (KEY_ID_MIN + 387)
#define KEY_PROP_PITCH2_SET             (KEY_ID_MIN + 388)
#define KEY_PROP_PITCH3_SET             (KEY_ID_MIN + 389)
#define KEY_PROP_PITCH4_SET             (KEY_ID_MIN + 390)
#define KEY_MAGNETO1_OFF                (KEY_ID_MIN + 391)
#define KEY_STARTER1_OFF                (KEY_ID_MIN + 391)
#define KEY_MAGNETO1_RIGHT              (KEY_ID_MIN + 392)
#define KEY_STARTER1_START              (KEY_ID_MIN + 392)
#define KEY_MAGNETO1_LEFT               (KEY_ID_MIN + 393)
#define KEY_STARTER1_GEN                (KEY_ID_MIN + 393)
#define KEY_MAGNETO1_BOTH               (KEY_ID_MIN + 394)
#define KEY_MAGNETO1_START              (KEY_ID_MIN + 395)
#define KEY_STARTER1_SET                (KEY_ID_MIN + 396)
#define KEY_MAGNETO2_OFF                (KEY_ID_MIN + 397)
#define KEY_STARTER2_OFF                (KEY_ID_MIN + 397)
#define KEY_MAGNETO2_RIGHT              (KEY_ID_MIN + 398)
#define KEY_STARTER2_START              (KEY_ID_MIN + 398)
#define KEY_MAGNETO2_LEFT               (KEY_ID_MIN + 399)
#define KEY_STARTER2_GEN                (KEY_ID_MIN + 399)
#define KEY_MAGNETO2_BOTH               (KEY_ID_MIN + 400)
#define KEY_MAGNETO2_START              (KEY_ID_MIN + 401)
#define KEY_STARTER2_SET                (KEY_ID_MIN + 402)
#define KEY_MAGNETO3_OFF                (KEY_ID_MIN + 403)
#define KEY_STARTER3_OFF                (KEY_ID_MIN + 403)
#define KEY_MAGNETO3_RIGHT              (KEY_ID_MIN + 404)
#define KEY_STARTER3_START              (KEY_ID_MIN + 404)
#define KEY_MAGNETO3_LEFT               (KEY_ID_MIN + 405)
#define KEY_STARTER3_GEN                (KEY_ID_MIN + 405)
#define KEY_MAGNETO3_BOTH               (KEY_ID_MIN + 406)
#define KEY_MAGNETO3_START              (KEY_ID_MIN + 407)
#define KEY_STARTER3_SET                (KEY_ID_MIN + 408)
#define KEY_MAGNETO4_OFF                (KEY_ID_MIN + 409)
#define KEY_STARTER4_OFF                (KEY_ID_MIN + 409)
#define KEY_MAGNETO4_RIGHT              (KEY_ID_MIN + 410)
#define KEY_STARTER4_START              (KEY_ID_MIN + 410)
#define KEY_MAGNETO4_LEFT               (KEY_ID_MIN + 411)
#define KEY_STARTER4_GEN                (KEY_ID_MIN + 411)
#define KEY_MAGNETO4_BOTH               (KEY_ID_MIN + 412)
#define KEY_MAGNETO4_START              (KEY_ID_MIN + 413)
#define KEY_STARTER4_SET                (KEY_ID_MIN + 414)
#define KEY_AUTOCOORD_TOGGLE            (KEY_ID_MIN + 415)
#define KEY_AUTOCOORD_OFF               (KEY_ID_MIN + 416)
#define KEY_AUTOCOORD_ON                (KEY_ID_MIN + 417)
#define KEY_AUTOCOORD_SET               (KEY_ID_MIN + 418)
#define KEY_FUEL_SELECTOR_OFF           (KEY_ID_MIN + 419)
#define KEY_FUEL_SELECTOR_ALL           (KEY_ID_MIN + 420)
#define KEY_FUEL_SELECTOR_LEFT          (KEY_ID_MIN + 421)
#define KEY_FUEL_SELECTOR_RIGHT         (KEY_ID_MIN + 422)
#define KEY_FUEL_SELECTOR_LEFT_AUX      (KEY_ID_MIN + 423)
#define KEY_FUEL_SELECTOR_RIGHT_AUX     (KEY_ID_MIN + 424)
#define KEY_FUEL_SELECTOR_CENTER        (KEY_ID_MIN + 425)
#define KEY_FUEL_SELECTOR_SET           (KEY_ID_MIN + 426)
#define KEY_THROTTLE1_FULL              (KEY_ID_MIN + 427)
#define KEY_THROTTLE1_INCR              (KEY_ID_MIN + 428)
#define KEY_THROTTLE1_INCR_SMALL        (KEY_ID_MIN + 429)
#define KEY_THROTTLE1_DECR              (KEY_ID_MIN + 430)
#define KEY_THROTTLE1_CUT               (KEY_ID_MIN + 431)
#define KEY_THROTTLE2_FULL              (KEY_ID_MIN + 432)
#define KEY_THROTTLE2_INCR              (KEY_ID_MIN + 433)
#define KEY_THROTTLE2_INCR_SMALL        (KEY_ID_MIN + 434)
#define KEY_THROTTLE2_DECR              (KEY_ID_MIN + 435)
#define KEY_THROTTLE2_CUT               (KEY_ID_MIN + 436)
#define KEY_THROTTLE3_FULL              (KEY_ID_MIN + 437)
#define KEY_THROTTLE3_INCR              (KEY_ID_MIN + 438)
#define KEY_THROTTLE3_INCR_SMALL        (KEY_ID_MIN + 439)
#define KEY_THROTTLE3_DECR              (KEY_ID_MIN + 440)
#define KEY_THROTTLE3_CUT               (KEY_ID_MIN + 441)
#define KEY_THROTTLE4_FULL              (KEY_ID_MIN + 442)
#define KEY_THROTTLE4_INCR              (KEY_ID_MIN + 443)
#define KEY_THROTTLE4_INCR_SMALL        (KEY_ID_MIN + 444)
#define KEY_THROTTLE4_DECR              (KEY_ID_MIN + 445)
#define KEY_THROTTLE4_CUT               (KEY_ID_MIN + 446)
#define KEY_MIXTURE1_RICH               (KEY_ID_MIN + 447)
#define KEY_MIXTURE1_INCR               (KEY_ID_MIN + 448)
#define KEY_MIXTURE1_INCR_SMALL         (KEY_ID_MIN + 449)
#define KEY_MIXTURE1_DECR               (KEY_ID_MIN + 450)
#define KEY_MIXTURE1_LEAN               (KEY_ID_MIN + 451)
#define KEY_MIXTURE2_RICH               (KEY_ID_MIN + 452)
#define KEY_MIXTURE2_INCR               (KEY_ID_MIN + 453)
#define KEY_MIXTURE2_INCR_SMALL         (KEY_ID_MIN + 454)
#define KEY_MIXTURE2_DECR               (KEY_ID_MIN + 455)
#define KEY_MIXTURE2_LEAN               (KEY_ID_MIN + 456)
#define KEY_MIXTURE3_RICH               (KEY_ID_MIN + 457)
#define KEY_MIXTURE3_INCR               (KEY_ID_MIN + 458)
#define KEY_MIXTURE3_INCR_SMALL         (KEY_ID_MIN + 459)
#define KEY_MIXTURE3_DECR               (KEY_ID_MIN + 460)
#define KEY_MIXTURE3_LEAN               (KEY_ID_MIN + 461)
#define KEY_MIXTURE4_RICH               (KEY_ID_MIN + 462)
#define KEY_MIXTURE4_INCR               (KEY_ID_MIN + 463)
#define KEY_MIXTURE4_INCR_SMALL         (KEY_ID_MIN + 464)
#define KEY_MIXTURE4_DECR               (KEY_ID_MIN + 465)
#define KEY_MIXTURE4_LEAN               (KEY_ID_MIN + 466)
#define KEY_PROP_PITCH1_LO              (KEY_ID_MIN + 467)
#define KEY_PROP_PITCH1_INCR            (KEY_ID_MIN + 468)
#define KEY_PROP_PITCH1_INCR_SMALL      (KEY_ID_MIN + 469)
#define KEY_PROP_PITCH1_DECR            (KEY_ID_MIN + 470)
#define KEY_PROP_PITCH1_HI              (KEY_ID_MIN + 471)
#define KEY_PROP_PITCH2_LO              (KEY_ID_MIN + 472)
#define KEY_PROP_PITCH2_INCR            (KEY_ID_MIN + 473)
#define KEY_PROP_PITCH2_INCR_SMALL      (KEY_ID_MIN + 474)
#define KEY_PROP_PITCH2_DECR            (KEY_ID_MIN + 475)
#define KEY_PROP_PITCH2_HI              (KEY_ID_MIN + 476)
#define KEY_PROP_PITCH3_LO              (KEY_ID_MIN + 477)
#define KEY_PROP_PITCH3_INCR            (KEY_ID_MIN + 478)
#define KEY_PROP_PITCH3_INCR_SMALL      (KEY_ID_MIN + 479)
#define KEY_PROP_PITCH3_DECR            (KEY_ID_MIN + 480)
#define KEY_PROP_PITCH3_HI              (KEY_ID_MIN + 481)
#define KEY_PROP_PITCH4_LO              (KEY_ID_MIN + 482)
#define KEY_PROP_PITCH4_INCR            (KEY_ID_MIN + 483)
#define KEY_PROP_PITCH4_INCR_SMALL      (KEY_ID_MIN + 484)
#define KEY_PROP_PITCH4_DECR            (KEY_ID_MIN + 485)
#define KEY_PROP_PITCH4_HI              (KEY_ID_MIN + 486)
#define KEY_MAGNETO_OFF                 (KEY_ID_MIN + 487)
#define KEY_STARTER_OFF                 (KEY_ID_MIN + 487)
#define KEY_MAGNETO_RIGHT               (KEY_ID_MIN + 488)
#define KEY_STARTER_START               (KEY_ID_MIN + 488)
#define KEY_MAGNETO_LEFT                (KEY_ID_MIN + 489)
#define KEY_STARTER_GEN                 (KEY_ID_MIN + 489)
#define KEY_MAGNETO_BOTH                (KEY_ID_MIN + 490)
#define KEY_MAGNETO_START               (KEY_ID_MIN + 491)
#define KEY_STARTER_SET                 (KEY_ID_MIN + 492)
#define KEY_ANTI_ICE_ON                 (KEY_ID_MIN + 493)
#define KEY_ANTI_ICE_OFF                (KEY_ID_MIN + 494)
#define KEY_ANTI_ICE_SET                (KEY_ID_MIN + 495)
#define KEY_EGT_INC                     (KEY_ID_MIN + 496)
#define KEY_EGT_DEC                     (KEY_ID_MIN + 497)
#define KEY_EGT_SET                     (KEY_ID_MIN + 498)
#define KEY_AP_ALT_VAR_SET_METRIC       (KEY_ID_MIN + 499)
#define KEY_AP_VS_VAR_SET_ENGLISH       (KEY_ID_MIN + 500)
#define KEY_AP_SPD_VAR_SET              (KEY_ID_MIN + 501)
#define KEY_AP_MACH_VAR_SET             (KEY_ID_MIN + 502)
#define KEY_ADF_CARD_SET                (KEY_ID_MIN + 503)
#define KEY_KOHLSMAN_SET                (KEY_ID_MIN + 504)
#define KEY_SIM_RATE_SET                (KEY_ID_MIN + 505)
#define KEY_HEADING_BUG_SET             (KEY_ID_MIN + 506)
#define KEY_TRUE_AIRSPEED_CAL_SET       (KEY_ID_MIN + 507)
#define KEY_CLOCK_HOURS_SET             (KEY_ID_MIN + 508)
#define KEY_CLOCK_MINUTES_SET           (KEY_ID_MIN + 509)
#define KEY_GYRO_DRIFT_SET              (KEY_ID_MIN + 510)
#define KEY_ADF_EXTENDED_SET            (KEY_ID_MIN + 511)
#define KEY_SLEW_SET                    (KEY_ID_MIN + 512)
#define KEY_SMOKE_ON                    (KEY_ID_MIN + 513)
#define KEY_SMOKE_OFF                   (KEY_ID_MIN + 514)
#define KEY_SMOKE_SET                   (KEY_ID_MIN + 515)
#define KEY_STROBES_ON                  (KEY_ID_MIN + 516)
#define KEY_STROBES_OFF                 (KEY_ID_MIN + 517)
#define KEY_STROBES_SET                 (KEY_ID_MIN + 518)
#define KEY_PAUSE_SET                   (KEY_ID_MIN + 519)
#define KEY_PANEL_LIGHTS_ON             (KEY_ID_MIN + 520)
#define KEY_PANEL_LIGHTS_OFF            (KEY_ID_MIN + 521)
#define KEY_PANEL_LIGHTS_SET            (KEY_ID_MIN + 522)
#define KEY_LANDING_LIGHTS_ON           (KEY_ID_MIN + 523)
#define KEY_LANDING_LIGHTS_OFF          (KEY_ID_MIN + 524)
#define KEY_LANDING_LIGHTS_SET          (KEY_ID_MIN + 525)
#define KEY_SOUND_ON                    (KEY_ID_MIN + 526)
#define KEY_SOUND_OFF                   (KEY_ID_MIN + 527)
#define KEY_SPOILERS_ON                 (KEY_ID_MIN + 528)
#define KEY_SPOILERS_OFF                (KEY_ID_MIN + 529)
#define KEY_SPOILERS_ARM_ON             (KEY_ID_MIN + 530)
#define KEY_SPOILERS_ARM_OFF            (KEY_ID_MIN + 531)
#define KEY_SPOILERS_ARM_SET            (KEY_ID_MIN + 532)
#define KEY_YAW_DAMPER_ON               (KEY_ID_MIN + 533)
#define KEY_YAW_DAMPER_OFF              (KEY_ID_MIN + 534)
#define KEY_YAW_DAMPER_SET              (KEY_ID_MIN + 535)
#define KEY_PITOT_HEAT_ON               (KEY_ID_MIN + 536)
#define KEY_PITOT_HEAT_OFF              (KEY_ID_MIN + 537)
#define KEY_PITOT_HEAT_SET              (KEY_ID_MIN + 538)
#define KEY_ZULU_HOURS_SET              (KEY_ID_MIN + 539)
#define KEY_ZULU_MINUTES_SET            (KEY_ID_MIN + 540)
#define KEY_ZULU_DAY_SET                (KEY_ID_MIN + 541)
#define KEY_ZULU_YEAR_SET               (KEY_ID_MIN + 542)
#define KEY_GEAR_UP                     (KEY_ID_MIN + 543)
#define KEY_GEAR_DOWN                   (KEY_ID_MIN + 544)
#define KEY_EGT1_INC                    (KEY_ID_MIN + 545)
#define KEY_EGT1_DEC                    (KEY_ID_MIN + 546)
#define KEY_EGT1_SET                    (KEY_ID_MIN + 547)
#define KEY_EGT2_INC                    (KEY_ID_MIN + 548)
#define KEY_EGT2_DEC                    (KEY_ID_MIN + 549)
#define KEY_EGT2_SET                    (KEY_ID_MIN + 550)
#define KEY_EGT3_INC                    (KEY_ID_MIN + 551)
#define KEY_EGT3_DEC                    (KEY_ID_MIN + 552)
#define KEY_EGT3_SET                    (KEY_ID_MIN + 553)
#define KEY_EGT4_INC                    (KEY_ID_MIN + 554)
#define KEY_EGT4_DEC                    (KEY_ID_MIN + 555)
#define KEY_EGT4_SET                    (KEY_ID_MIN + 556)
#define KEY_AP_AIRSPEED_ON              (KEY_ID_MIN + 557)
#define KEY_AP_AIRSPEED_OFF             (KEY_ID_MIN + 558)
#define KEY_AP_AIRSPEED_SET             (KEY_ID_MIN + 559)
#define KEY_AP_MACH_ON                  (KEY_ID_MIN + 560)
#define KEY_AP_MACH_OFF                 (KEY_ID_MIN + 561)
#define KEY_AP_MACH_SET                 (KEY_ID_MIN + 562)
#define KEY_AP_VS_HOLD                  (KEY_ID_MIN + 563)
#define KEY_AP_VS_ON                    (KEY_ID_MIN + 564)
#define KEY_AP_VS_OFF                   (KEY_ID_MIN + 565)
#define KEY_AP_VS_SET                   (KEY_ID_MIN + 566)
#define KEY_AP_PANEL_ALTITUDE_ON        (KEY_ID_MIN + 567)
#define KEY_AP_PANEL_ALTITUDE_OFF       (KEY_ID_MIN + 568)
#define KEY_AP_PANEL_ALTITUDE_SET       (KEY_ID_MIN + 569)
#define KEY_AP_PANEL_HEADING_ON         (KEY_ID_MIN + 570)
#define KEY_AP_PANEL_HEADING_OFF        (KEY_ID_MIN + 571)
#define KEY_AP_PANEL_HEADING_SET        (KEY_ID_MIN + 572)
#define KEY_AP_PANEL_MACH_ON            (KEY_ID_MIN + 573)
#define KEY_AP_PANEL_MACH_OFF           (KEY_ID_MIN + 574)
#define KEY_AP_PANEL_MACH_SET           (KEY_ID_MIN + 575)
#define KEY_AP_PANEL_SPEED_ON           (KEY_ID_MIN + 576)
#define KEY_AP_PANEL_SPEED_OFF          (KEY_ID_MIN + 577)
#define KEY_AP_PANEL_SPEED_SET          (KEY_ID_MIN + 578)
#define KEY_AP_PANEL_VS_ON              (KEY_ID_MIN + 579)
#define KEY_AP_PANEL_VS_OFF             (KEY_ID_MIN + 580)
#define KEY_AP_PANEL_VS_SET             (KEY_ID_MIN + 581)
#define KEY_SEE_OWN_AC_TOGGLE           (KEY_ID_MIN + 582)
#define KEY_SEE_OWN_AC_ON               (KEY_ID_MIN + 583)
#define KEY_SEE_OWN_AC_OFF              (KEY_ID_MIN + 584)
#define KEY_SEE_OWN_AC_SET              (KEY_ID_MIN + 585)
#define KEY_ADF_LOWRANGE_SET            (KEY_ID_MIN + 586)
#define KEY_ADF_HIGHRANGE_SET           (KEY_ID_MIN + 587)
#define KEY_AP_ALT_VAR_SET_ENGLISH      (KEY_ID_MIN + 588)
#define KEY_AP_VS_VAR_SET_METRIC        (KEY_ID_MIN + 589)
#define KEY_MAGNETO1_DECR               (KEY_ID_MIN + 590)
#define KEY_MAGNETO1_INCR               (KEY_ID_MIN + 591)
#define KEY_MAGNETO2_DECR               (KEY_ID_MIN + 592)
#define KEY_MAGNETO2_INCR               (KEY_ID_MIN + 593)
#define KEY_MAGNETO3_DECR               (KEY_ID_MIN + 594)
#define KEY_MAGNETO3_INCR               (KEY_ID_MIN + 595)
#define KEY_MAGNETO4_DECR               (KEY_ID_MIN + 596)
#define KEY_MAGNETO4_INCR               (KEY_ID_MIN + 597)
#define KEY_GUNSIGHT_SEL                (KEY_ID_MIN + 599)
#define KEY_GUNSIGHT_TOGGLE             (KEY_ID_MIN + 600)
#define KEY_VIEW_FORWARD_UP             (KEY_ID_MIN + 601)
#define KEY_VIEW_FORWARD_RIGHT_UP       (KEY_ID_MIN + 602)
#define KEY_VIEW_RIGHT_UP               (KEY_ID_MIN + 603)
#define KEY_VIEW_REAR_RIGHT_UP          (KEY_ID_MIN + 604)
#define KEY_VIEW_REAR_UP                (KEY_ID_MIN + 605)
#define KEY_VIEW_REAR_LEFT_UP           (KEY_ID_MIN + 606)
#define KEY_VIEW_LEFT_UP                (KEY_ID_MIN + 607)
#define KEY_VIEW_FORWARD_LEFT_UP        (KEY_ID_MIN + 608)
#define KEY_VIEW_UP                     (KEY_ID_MIN + 609)
#define KEY_SKIP_ACTION                 (KEY_ID_MIN + 610)
#define KEY_VIEW_RESET                  (KEY_ID_MIN + 611)
#define KEY_FIRE_ALL_GUNS               (KEY_ID_MIN + 620)
#define KEY_FIRE_PRIMARY_GUNS           (KEY_ID_MIN + 621)
#define KEY_FIRE_SECONDARY_GUNS         (KEY_ID_MIN + 622)
#define KEY_COWLFLAP1_SET               (KEY_ID_MIN + 626)
#define KEY_COWLFLAP2_SET               (KEY_ID_MIN + 627)
#define KEY_COWLFLAP3_SET               (KEY_ID_MIN + 628)
#define KEY_COWLFLAP4_SET               (KEY_ID_MIN + 629)
#define KEY_TOGGLE_RADAR                (KEY_ID_MIN + 634)
#define KEY_ATC_MENU_1                  (KEY_ID_MIN + 636)
#define KEY_ATC_MENU_2                  (KEY_ID_MIN + 637)
#define KEY_ATC_MENU_3                  (KEY_ID_MIN + 638)
#define KEY_ATC_MENU_4                  (KEY_ID_MIN + 639)
#define KEY_ATC_MENU_5                  (KEY_ID_MIN + 640)
#define KEY_ATC_MENU_6                  (KEY_ID_MIN + 641)
#define KEY_ATC_MENU_7                  (KEY_ID_MIN + 642)
#define KEY_ATC_MENU_8                  (KEY_ID_MIN + 643)
#define KEY_ATC_MENU_9                  (KEY_ID_MIN + 644)
#define KEY_ATC_MENU_0                  (KEY_ID_MIN + 645)
#define KEY_VIEW_AUX_00                 (KEY_ID_MIN + 646)
#define KEY_VIEW_AUX_01                 (KEY_ID_MIN + 647)
#define KEY_VIEW_AUX_02                 (KEY_ID_MIN + 648)
#define KEY_VIEW_AUX_03                 (KEY_ID_MIN + 649)
#define KEY_VIEW_AUX_04                 (KEY_ID_MIN + 650)
#define KEY_VIEW_AUX_05                 (KEY_ID_MIN + 651)
#define KEY_INVOKE_HELP                 (KEY_ID_MIN + 659)
#define KEY_SELECT_NEXT_TARGET          (KEY_ID_MIN + 660)
#define KEY_TOGGLE_PADLOCK              (KEY_ID_MIN + 661)
#define KEY_UNLOCK_TARGET               (KEY_ID_MIN + 662)
#define KEY_TOGGLE_AIRCRAFT_LABELS      (KEY_ID_MIN + 663)
#define KEY_TOGGLE_DAMAGE_TEXT          (KEY_ID_MIN + 664)
#define KEY_TOGGLE_ENEMY_INDICATOR      (KEY_ID_MIN + 665)
#define KEY_WAR_EMERGENCY_POWER         (KEY_ID_MIN + 666)
#define KEY_BAIL_OUT                    (KEY_ID_MIN + 667)
#define KEY_TOGGLE_RADIO                (KEY_ID_MIN + 668)
#define KEY_KEYBOARD_OVERLAY            (KEY_ID_MIN + 669)
#define KEY_CHASE_VIEW                  (KEY_ID_MIN + 670)
#define KEY_OTHER_AIRCRAFT_VIEW         (KEY_ID_MIN + 671)
#define KEY_BOMB_VIEW                   (KEY_ID_MIN + 672)
#define KEY_HUD_UNITS                   (KEY_ID_MIN + 673)
#define KEY_HUD_COLOR                   (KEY_ID_MIN + 674)
#define KEY_LETTERBOX                   (KEY_ID_MIN + 687)
#define KEY_ENGINE_AUTO_START           (KEY_ID_MIN + 688)
#define KEY_THROTTLE_10                 (KEY_ID_MIN + 689)
#define KEY_THROTTLE_20                 (KEY_ID_MIN + 690)
#define KEY_THROTTLE_30                 (KEY_ID_MIN + 691)
#define KEY_THROTTLE_40                 (KEY_ID_MIN + 692)
#define KEY_THROTTLE_50                 (KEY_ID_MIN + 693)
#define KEY_THROTTLE_60                 (KEY_ID_MIN + 694)
#define KEY_THROTTLE_70                 (KEY_ID_MIN + 695)
#define KEY_THROTTLE_80                 (KEY_ID_MIN + 696)
#define KEY_THROTTLE_90                 (KEY_ID_MIN + 697)
#define KEY_FORCE_END                   (KEY_ID_MIN + 698)
#define KEY_FUEL_PUMP                   (KEY_ID_MIN + 701)
#define KEY_ENGINE_PRIMER               (KEY_ID_MIN + 702)
#define KEY_TOGGLE_BEACON_LIGHTS        (KEY_ID_MIN + 703)
#define KEY_TOGGLE_TAXI_LIGHTS          (KEY_ID_MIN + 704)
#define KEY_TOGGLE_MASTER_BATTERY       (KEY_ID_MIN + 705)
#define KEY_TOGGLE_MASTER_ALTERNATOR    (KEY_ID_MIN + 706)
#define KEY_INC_COWL_FLAPS              (KEY_ID_MIN + 707)
#define KEY_DEC_COWL_FLAPS              (KEY_ID_MIN + 708)
#define KEY_OVERLAYMENU                 (KEY_ID_MIN + 731)
#define KEY_USERINTERRUPT               (KEY_ID_MIN + 732)
#define KEY_SELECT_PREV_TARGET          (KEY_ID_MIN + 733)
#define KEY_STOP_PRIMARY_GUNS           (KEY_ID_MIN + 734)
#define KEY_STOP_SECONDARY_GUNS         (KEY_ID_MIN + 735)
#define KEY_STOP_ALL_GUNS               (KEY_ID_MIN + 736)
#define KEY_SP_MULTIPLAYER_SCORE_DISPLAY (KEY_ID_MIN + 737)
#define KEY_VIEW_SNAP_FORWARD           (KEY_ID_MIN + 738)
#define KEY_VIEW_SNAP_REAR              (KEY_ID_MIN + 739)
#define KEY_AILERON_TRIM_LEFT           (KEY_ID_MIN + 740)
#define KEY_AILERON_TRIM_RIGHT          (KEY_ID_MIN + 741)
#define KEY_RUDDER_TRIM_LEFT            (KEY_ID_MIN + 742)
#define KEY_RUDDER_TRIM_RIGHT           (KEY_ID_MIN + 743)
#define KEY_RADIO_COMMNAV1_TEST_TOGGLE  (KEY_ID_MIN + 744)
#define KEY_RADIO_COMMNAV2_TEST_TOGGLE  (KEY_ID_MIN + 745)
#define KEY_RADIO_COMM1_AUTOSWITCH_TOGGLE (KEY_ID_MIN + 746)
#define KEY_RADIO_NAV1_AUTOSWITCH_TOGGLE (KEY_ID_MIN + 747)
#define KEY_RADIO_COMM2_AUTOSWITCH_TOGGLE (KEY_ID_MIN + 748)
#define KEY_RADIO_NAV2_AUTOSWITCH_TOGGLE (KEY_ID_MIN + 749)
#define KEY_DME_TOGGLE                  (KEY_ID_MIN + 750)
#define KEY_TOGGLE_PROP_SYNC            (KEY_ID_MIN + 751)
#define KEY_TOGGLE_FLIGHT_DIRECTOR      (KEY_ID_MIN + 752)
#define KEY_SYNC_FLIGHT_DIRECTOR_PITCH  (KEY_ID_MIN + 753)
#define KEY_TOGGLE_ELECTRIC_VACUUM_PUMP (KEY_ID_MIN + 754)
#define KEY_AXIS_PROPELLER_SET          (KEY_ID_MIN + 755)
#define KEY_AXIS_MIXTURE_SET            (KEY_ID_MIN + 756)
#define KEY_TOGGLE_AVIONICS_MASTER      (KEY_ID_MIN + 757)
#define KEY_INC_CONCORDE_NOSE_VISOR     (KEY_ID_MIN + 758)
#define KEY_DEC_CONCORDE_NOSE_VISOR     (KEY_ID_MIN + 759)
#define KEY_TOGGLE_AFTERBURNER          (KEY_ID_MIN + 760)
#define KEY_TOGGLE_ARM_AUTOFEATHER      (KEY_ID_MIN + 761)
#define KEY_INC_AUTOBRAKE_CONTROL       (KEY_ID_MIN + 762)
#define KEY_DEC_AUTOBRAKE_CONTROL       (KEY_ID_MIN + 763)
#define KEY_TOGGLE_STARTER1             (KEY_ID_MIN + 764)
#define KEY_TOGGLE_STARTER2             (KEY_ID_MIN + 765)
#define KEY_TOGGLE_STARTER3             (KEY_ID_MIN + 766)
#define KEY_TOGGLE_STARTER4             (KEY_ID_MIN + 767)
#define KEY_TOGGLE_ALL_STARTERS         (KEY_ID_MIN + 768)
#define KEY_TOGGLE_VACUUM_FAILURE       (KEY_ID_MIN + 769)
#define KEY_TOGGLE_ELECTRICAL_FAILURE   (KEY_ID_MIN + 770)
#define KEY_TOGGLE_PITOT_BLOCKAGE       (KEY_ID_MIN + 771)
#define KEY_TOGGLE_STATIC_PORT_BLOCKAGE (KEY_ID_MIN + 772)
#define KEY_TOGGLE_HYDRAULIC_FAILURE    (KEY_ID_MIN + 773)
#define KEY_TOGGLE_TOTAL_BRAKE_FAILURE  (KEY_ID_MIN + 774)
#define KEY_TOGGLE_LEFT_BRAKE_FAILURE   (KEY_ID_MIN + 775)
#define KEY_TOGGLE_RIGHT_BRAKE_FAILURE  (KEY_ID_MIN + 776)
#define KEY_TOGGLE_ENGINE1_FAILURE      (KEY_ID_MIN + 777)
#define KEY_TOGGLE_ENGINE2_FAILURE      (KEY_ID_MIN + 778)
#define KEY_TOGGLE_ENGINE3_FAILURE      (KEY_ID_MIN + 779)
#define KEY_TOGGLE_ENGINE4_FAILURE      (KEY_ID_MIN + 780)
#define KEY_TOGGLE_ALTERNATE_STATIC     (KEY_ID_MIN + 781)
#define KEY_ATTITUDE_BARS_POSITION_INC  (KEY_ID_MIN + 782)
#define KEY_ATTITUDE_BARS_POSITION_DEC  (KEY_ID_MIN + 783)
#define KEY_TOGGLE_RAD_INS_SWITCH       (KEY_ID_MIN + 784)
#define KEY_DECISION_HEIGHT_INC         (KEY_ID_MIN + 785)
#define KEY_DECISION_HEIGHT_DEC         (KEY_ID_MIN + 786)
#define KEY_LOW_HIGHT_WARNING_SET       (KEY_ID_MIN + 787)
#define KEY_LOW_HIGHT_WARNING_GAUGE_WILL_SET (KEY_ID_MIN + 788)
#define KEY_SET_FUEL_TRANSFER_FORWARD   (KEY_ID_MIN + 789)
#define KEY_SET_FUEL_TRANSFER_AFT       (KEY_ID_MIN + 790)
#define KEY_SET_FUEL_TRANSFER_AUTO      (KEY_ID_MIN + 791)
#define KEY_SET_FUEL_TRANSFER_OFF       (KEY_ID_MIN + 792)
#define KEY_INC_COWL_FLAPS1             (KEY_ID_MIN + 793)
#define KEY_DEC_COWL_FLAPS1             (KEY_ID_MIN + 794)
#define KEY_INC_COWL_FLAPS2             (KEY_ID_MIN + 795)
#define KEY_DEC_COWL_FLAPS2             (KEY_ID_MIN + 796)
#define KEY_INC_COWL_FLAPS3             (KEY_ID_MIN + 797)
#define KEY_DEC_COWL_FLAPS3             (KEY_ID_MIN + 798)
#define KEY_INC_COWL_FLAPS4             (KEY_ID_MIN + 799)
#define KEY_DEC_COWL_FLAPS4             (KEY_ID_MIN + 800)
#define KEY_TOGGLE_STRUCTURAL_DEICE     (KEY_ID_MIN + 801)
#define KEY_TOGGLE_PROPELLER_DEICE      (KEY_ID_MIN + 802)
#define KEY_TOGGLE_ELECT_FUEL_PUMP      (KEY_ID_MIN + 803)
#define KEY_TOGGLE_ELECT_FUEL_PUMP1     (KEY_ID_MIN + 804)
#define KEY_TOGGLE_ELECT_FUEL_PUMP2     (KEY_ID_MIN + 805)
#define KEY_TOGGLE_ELECT_FUEL_PUMP3     (KEY_ID_MIN + 806)
#define KEY_TOGGLE_ELECT_FUEL_PUMP4     (KEY_ID_MIN + 807)
#define KEY_TOGGLE_PRIMER               (KEY_ID_MIN + 808)
#define KEY_TOGGLE_PRIMER1              (KEY_ID_MIN + 809)
#define KEY_TOGGLE_PRIMER2              (KEY_ID_MIN + 810)
#define KEY_TOGGLE_PRIMER3              (KEY_ID_MIN + 811)
#define KEY_TOGGLE_PRIMER4              (KEY_ID_MIN + 812)
#define KEY_ENGINE_FUELFLOW_BUG_POSITION1 (KEY_ID_MIN + 813)
#define KEY_ENGINE_FUELFLOW_BUG_POSITION2 (KEY_ID_MIN + 814)
#define KEY_ENGINE_FUELFLOW_BUG_POSITION3 (KEY_ID_MIN + 815)
#define KEY_ENGINE_FUELFLOW_BUG_POSITION4 (KEY_ID_MIN + 816)
#define KEY_AUTOPILOT_AIRSPEED_HOLD_CURRENT (KEY_ID_MIN + 817)
#define KEY_AUTOPILOT_AIRSPEED_ACQUIRE  (KEY_ID_MIN + 818)
#define KEY_AUTOPILOT_PANEL_AIRSPEED_SET (KEY_ID_MIN + 819)
#define KEY_AUTOPILOT_MACH_HOLD_CURRENT (KEY_ID_MIN + 820)
#define KEY_AUTOPILOT_PANEL_MAX_SPEED   (KEY_ID_MIN + 821)
#define KEY_AUTOPILOT_PANEL_CRUISE_SPEED (KEY_ID_MIN + 822)
#define KEY_TOGGLE_AFTERBURNER1         (KEY_ID_MIN + 823)
#define KEY_TOGGLE_AFTERBURNER2         (KEY_ID_MIN + 824)
#define KEY_TOGGLE_AFTERBURNER3         (KEY_ID_MIN + 825)
#define KEY_TOGGLE_AFTERBURNER4         (KEY_ID_MIN + 826)
#define KEY_TOGGLE_ALTERNATOR1          (KEY_ID_MIN + 827)
#define KEY_TOGGLE_ALTERNATOR2          (KEY_ID_MIN + 828)
#define KEY_TOGGLE_ALTERNATOR3          (KEY_ID_MIN + 829)
#define KEY_TOGGLE_ALTERNATOR4          (KEY_ID_MIN + 830)
#define KEY_VOR1_OBI_FAST_DEC           (KEY_ID_MIN + 831)
#define KEY_VOR1_OBI_FAST_INC           (KEY_ID_MIN + 832)
#define KEY_VOR2_OBI_FAST_DEC           (KEY_ID_MIN + 833)
#define KEY_VOR2_OBI_FAST_INC           (KEY_ID_MIN + 834)
#define KEY_COM_STBY_RADIO_SET          (KEY_ID_MIN + 835)
#define KEY_COM_STBY_RADIO_SWITCH_TO    (KEY_ID_MIN + 836)
#define KEY_COM_RADIO_SWAP              KEY_COM_STBY_RADIO_SWITCH_TO
#define KEY_TOGGLE_ATTITUDE_CAGE        (KEY_ID_MIN + 837)
#define KEY_TOGGLE_MASTER_BATTERY_ALTERNATOR (KEY_ID_MIN + 838)
#define KEY_TOGGLE_GPS_DRIVES_NAV1      (KEY_ID_MIN + 839)
#define KEY_TOGGLE_LOGO_LIGHTS          (KEY_ID_MIN + 840)
#define KEY_TOGGLE_RECOGNITION_LIGHTS   (KEY_ID_MIN + 841)
#define KEY_TOGGLE_WING_LIGHTS          (KEY_ID_MIN + 842)
#define KEY_TOGGLE_NAV_LIGHTS           (KEY_ID_MIN + 843)
#define KEY_HELI_BEEP_INCREASE          (KEY_ID_MIN + 844)
#define KEY_HELI_BEEP_DECREASE          (KEY_ID_MIN + 845)
#define KEY_AXIS_SPOILER_SET            (KEY_ID_MIN + 846)
#define KEY_CONCORDE_NOSE_VISOR_FULL_EXT (KEY_ID_MIN + 847)
#define KEY_CONCORDE_NOSE_VISOR_FULL_RET (KEY_ID_MIN + 848)
#define KEY_LOD_ZOOM_IN                 (KEY_ID_MIN + 849)
#define KEY_LOD_ZOOM_OUT                (KEY_ID_MIN + 850)
#define KEY_AXIS_LEFT_BRAKE_SET         (KEY_ID_MIN + 851)
#define KEY_AXIS_RIGHT_BRAKE_SET        (KEY_ID_MIN + 852)
#define KEY_TOGGLE_AIRCRAFT_EXIT        (KEY_ID_MIN + 853)
#define KEY_TOGGLE_WING_FOLD            (KEY_ID_MIN + 854)
#define KEY_TOGGLE_TAIL_HOOK_HANDLE     (KEY_ID_MIN + 855)
#define KEY_RELEASE_DROP_TANK_ALL       (KEY_ID_MIN + 856)
#define KEY_RELEASE_DROP_TANK_1         (KEY_ID_MIN + 857)
#define KEY_RELEASE_DROP_TANK_2         (KEY_ID_MIN + 858)
#define KEY_MAGNETO_SET                 (KEY_ID_MIN + 863)
#define KEY_MAGNETO1_SET                (KEY_ID_MIN + 864)
#define KEY_MAGNETO2_SET                (KEY_ID_MIN + 865)
#define KEY_MAGNETO3_SET                (KEY_ID_MIN + 866)
#define KEY_MAGNETO4_SET                (KEY_ID_MIN + 867)
#define KEY_PANEL_HUD_TOGGLE            (KEY_ID_MIN + 868)
#define KEY_TOOLTIP_UNITS_SET           (KEY_ID_MIN + 869)
#define KEY_TOOLTIP_UNITS_TOGGLE        (KEY_ID_MIN + 870)
#define KEY_VIEW_SNAP_PANEL             (KEY_ID_MIN + 877)
#define KEY_VIEW_SNAP_PANEL_RESET       (KEY_ID_MIN + 878)
#define KEY_PAN_RESET_COCKPIT           (KEY_ID_MIN + 879)
#define KEY_PAN_VIEW                    (KEY_ID_MIN + 880)
#define KEY_SNAP_VIEW                   (KEY_ID_MIN + 881)
#define KEY_AXIS_THROTTLE1_SET          (KEY_ID_MIN + 884)
#define KEY_AXIS_PROPELLER1_SET         (KEY_ID_MIN + 885)
#define KEY_AXIS_MIXTURE1_SET           (KEY_ID_MIN + 886)
#define KEY_AXIS_THROTTLE2_SET          (KEY_ID_MIN + 887)
#define KEY_AXIS_PROPELLER2_SET         (KEY_ID_MIN + 888)
#define KEY_AXIS_MIXTURE2_SET           (KEY_ID_MIN + 889)
#define KEY_AXIS_THROTTLE3_SET          (KEY_ID_MIN + 890)
#define KEY_AXIS_PROPELLER3_SET         (KEY_ID_MIN + 891)
#define KEY_AXIS_MIXTURE3_SET           (KEY_ID_MIN + 892)
#define KEY_AXIS_THROTTLE4_SET          (KEY_ID_MIN + 893)
#define KEY_AXIS_PROPELLER4_SET         (KEY_ID_MIN + 894)
#define KEY_AXIS_MIXTURE4_SET           (KEY_ID_MIN + 895)
#define KEY_FLIGHT_MAP                  (KEY_ID_MIN + 896)
#define KEY_LABEL_COLOR_CYCLE           (KEY_ID_MIN + 897)
#define KEY_COM_RADIO_FRACT_DEC_CARRY   (KEY_ID_MIN + 898)
#define KEY_COM_RADIO_FRACT_INC_CARRY   (KEY_ID_MIN + 899)
#define KEY_COM2_RADIO_WHOLE_DEC        (KEY_ID_MIN + 900)
#define KEY_COM2_RADIO_WHOLE_INC        (KEY_ID_MIN + 901)
#define KEY_COM2_RADIO_FRACT_DEC        (KEY_ID_MIN + 902)
#define KEY_COM2_RADIO_FRACT_DEC_CARRY  (KEY_ID_MIN + 903)
#define KEY_COM2_RADIO_FRACT_INC        (KEY_ID_MIN + 904)
#define KEY_COM2_RADIO_FRACT_INC_CARRY  (KEY_ID_MIN + 905)
#define KEY_COM2_RADIO_SET              (KEY_ID_MIN + 906)
#define KEY_COM2_STBY_RADIO_SET         (KEY_ID_MIN + 907)
#define KEY_COM2_RADIO_SWAP             (KEY_ID_MIN + 908)
#define KEY_NAV1_RADIO_FRACT_DEC_CARRY  (KEY_ID_MIN + 909)
#define KEY_NAV1_RADIO_FRACT_INC_CARRY  (KEY_ID_MIN + 910)
#define KEY_NAV1_STBY_SET               (KEY_ID_MIN + 911)
#define KEY_NAV1_RADIO_SWAP             (KEY_ID_MIN + 912)
#define KEY_NAV2_RADIO_FRACT_DEC_CARRY  (KEY_ID_MIN + 913)
#define KEY_NAV2_RADIO_FRACT_INC_CARRY  (KEY_ID_MIN + 914)
#define KEY_NAV2_STBY_SET               (KEY_ID_MIN + 915)
#define KEY_NAV2_RADIO_SWAP             (KEY_ID_MIN + 916)
#define KEY_ADF1_RADIO_TENTHS_DEC       (KEY_ID_MIN + 917)
#define KEY_ADF1_RADIO_TENTHS_INC       (KEY_ID_MIN + 918)
#define KEY_XPNDR_1000_DEC              (KEY_ID_MIN + 919)
#define KEY_XPNDR_100_DEC               (KEY_ID_MIN + 920)
#define KEY_XPNDR_10_DEC                (KEY_ID_MIN + 921)
#define KEY_XPNDR_1_DEC                 (KEY_ID_MIN + 922)
#define KEY_XPNDR_DEC_CARRY             (KEY_ID_MIN + 923)
#define KEY_XPNDR_INC_CARRY             (KEY_ID_MIN + 924)
#define KEY_ADF_FRACT_DEC_CARRY         (KEY_ID_MIN + 925)
#define KEY_ADF_FRACT_INC_CARRY         (KEY_ID_MIN + 926)
#define KEY_COM1_TRANSMIT_SELECT        (KEY_ID_MIN + 927)
#define KEY_COM2_TRANSMIT_SELECT        (KEY_ID_MIN + 928)
#define KEY_COM_RECEIVE_ALL_TOGGLE      (KEY_ID_MIN + 929)
#define KEY_COM_RECEIVE_ALL_SET         (KEY_ID_MIN + 930)
#define KEY_MARKER_SOUND_TOGGLE         (KEY_ID_MIN + 941)
#define KEY_MARKER_SOUND_SET            (KEY_ID_MIN + 942)
#define KEY_ADF_COMPLETE_SET            (KEY_ID_MIN + 943)
#define KEY_ADF_OUTSIDE_SOURCE          (KEY_ID_MIN + 944)
#define KEY_ADF_NEEDLE_SET              (KEY_ID_MIN + 945)
#define KEY_TOGGLE_WATER_RUDDER         (KEY_ID_MIN + 946)
#define KEY_PUSHBACK_SET                (KEY_ID_MIN + 947)
#define KEY_ANTI_ICE_TOGGLE_ENG1        (KEY_ID_MIN + 948)
#define KEY_ANTI_ICE_TOGGLE_ENG2        (KEY_ID_MIN + 949)
#define KEY_ANTI_ICE_TOGGLE_ENG3        (KEY_ID_MIN + 950)
#define KEY_ANTI_ICE_TOGGLE_ENG4        (KEY_ID_MIN + 951)
#define KEY_ANTI_ICE_SET_ENG1           (KEY_ID_MIN + 952)
#define KEY_ANTI_ICE_SET_ENG2           (KEY_ID_MIN + 953)
#define KEY_ANTI_ICE_SET_ENG3           (KEY_ID_MIN + 954)
#define KEY_ANTI_ICE_SET_ENG4           (KEY_ID_MIN + 955)
#define KEY_RELOAD_PANELS               (KEY_ID_MIN + 956)
#define KEY_TOGGLE_FUEL_VALVE_ALL       (KEY_ID_MIN + 957)
#define KEY_TOGGLE_FUEL_VALVE_ENG1      (KEY_ID_MIN + 958)
#define KEY_TOGGLE_FUEL_VALVE_ENG2      (KEY_ID_MIN + 959)
#define KEY_TOGGLE_FUEL_VALVE_ENG3      (KEY_ID_MIN + 960)
#define KEY_TOGGLE_FUEL_VALVE_ENG4      (KEY_ID_MIN + 961)
#define KEY_TUG_HEADING                 (KEY_ID_MIN + 962)
#define KEY_TUG_SPEED                   (KEY_ID_MIN + 963)
#define KEY_CHASE_VIEW_NEXT             (KEY_ID_MIN + 964)
#define KEY_CHASE_VIEW_PREV             (KEY_ID_MIN + 965)
#define KEY_AP_NAV_SELECT_SET           (KEY_ID_MIN + 966)
#define KEY_AXIS_PAN_PITCH              (KEY_ID_MIN + 967)
#define KEY_AXIS_PAN_HEADING            (KEY_ID_MIN + 968)
#define KEY_AXIS_PAN_TILT               (KEY_ID_MIN + 969)
#define KEY_PANEL_ID_TOGGLE             (KEY_ID_MIN + 970)
#define KEY_PANEL_ID_OPEN               (KEY_ID_MIN + 971)
#define KEY_PANEL_ID_CLOSE              (KEY_ID_MIN + 972)
#define KEY_HEADING_BUG_SELECT          (KEY_ID_MIN + 973)
#define KEY_ALTITUDE_BUG_SELECT         (KEY_ID_MIN + 974)
#define KEY_VSI_BUG_SELECT              (KEY_ID_MIN + 975)
#define KEY_CONTROL_RELOAD_USER_AIRCRAFT (KEY_ID_MIN + 976)
#define KEY_ATC_MENU_OPEN               (KEY_ID_MIN + 977)
#define KEY_ATC_MENU_CLOSE              (KEY_ID_MIN + 978)
#define KEY_CHASE_VIEW_TOGGLE           (KEY_ID_MIN + 979)
#define KEY_FUEL_SELECTOR_2_OFF         (KEY_ID_MIN + 980)
#define KEY_FUEL_SELECTOR_2_ALL         (KEY_ID_MIN + 981)
#define KEY_FUEL_SELECTOR_2_LEFT        (KEY_ID_MIN + 982)
#define KEY_FUEL_SELECTOR_2_RIGHT       (KEY_ID_MIN + 983)
#define KEY_FUEL_SELECTOR_2_LEFT_AUX    (KEY_ID_MIN + 984)
#define KEY_FUEL_SELECTOR_2_RIGHT_AUX   (KEY_ID_MIN + 985)
#define KEY_FUEL_SELECTOR_2_CENTER      (KEY_ID_MIN + 986)
#define KEY_FUEL_SELECTOR_2_SET         (KEY_ID_MIN + 987)
#define KEY_EYEPOINT_UP                 (KEY_ID_MIN + 988)
#define KEY_EYEPOINT_DOWN               (KEY_ID_MIN + 989)
#define KEY_EYEPOINT_RIGHT              (KEY_ID_MIN + 990)
#define KEY_EYEPOINT_LEFT               (KEY_ID_MIN + 991)
#define KEY_EYEPOINT_FORWARD            (KEY_ID_MIN + 992)
#define KEY_EYEPOINT_BACK               (KEY_ID_MIN + 993)
#define KEY_EYEPOINT_RESET              (KEY_ID_MIN + 994)
#define KEY_ENGINE_AUTO_SHUTDOWN        (KEY_ID_MIN + 995)
#define KEY_AIRSPEED_BUG_SELECT         (KEY_ID_MIN + 996)
#define KEY_TUG_DISABLE                 (KEY_ID_MIN + 997)
#define KEY_AXIS_FLAPS_SET              (KEY_ID_MIN + 998)
#define KEY_TOGGLE_MASTER_IGNITION_SWITCH (KEY_ID_MIN + 999)
#define KEY_TOGGLE_FEATHER_SWITCHES     (KEY_ID_MIN + 1000)
#define KEY_TOGGLE_FEATHER_SWITCH_1		(KEY_ID_MIN + 1001)
#define KEY_TOGGLE_FEATHER_SWITCH_2		(KEY_ID_MIN + 1002)
#define KEY_TOGGLE_FEATHER_SWITCH_3		(KEY_ID_MIN + 1003)
#define KEY_TOGGLE_FEATHER_SWITCH_4		(KEY_ID_MIN + 1004)
#define KEY_TOGGLE_TAILWHEEL_LOCK		(KEY_ID_MIN + 1005)
#define	KEY_ADF_WHOLE_INC				(KEY_ID_MIN + 1006)
#define	KEY_ADF_WHOLE_DEC				(KEY_ID_MIN + 1007)
#define	KEY_ADF2_100_INC				(KEY_ID_MIN + 1008)
#define	KEY_ADF2_10_INC					(KEY_ID_MIN + 1009)
#define	KEY_ADF2_1_INC					(KEY_ID_MIN + 1010)
#define	KEY_ADF2_RADIO_TENTHS_INC		(KEY_ID_MIN + 1011)
#define	KEY_ADF2_100_DEC				(KEY_ID_MIN + 1012)
#define	KEY_ADF2_10_DEC					(KEY_ID_MIN + 1013)
#define	KEY_ADF2_1_DEC					(KEY_ID_MIN + 1014)
#define	KEY_ADF2_RADIO_TENTHS_DEC		(KEY_ID_MIN + 1015)
#define	KEY_ADF2_WHOLE_INC				(KEY_ID_MIN + 1016)
#define	KEY_ADF2_WHOLE_DEC				(KEY_ID_MIN + 1017)
#define	KEY_ADF2_FRACT_INC_CARRY		(KEY_ID_MIN + 1018)
#define	KEY_ADF2_FRACT_DEC_CARRY		(KEY_ID_MIN + 1019)
#define	KEY_ADF2_COMPLETE_SET			(KEY_ID_MIN + 1020)
#define	KEY_RADIO_ADF2_IDENT_DISABLE	(KEY_ID_MIN + 1021)
#define	KEY_RADIO_ADF2_IDENT_ENABLE		(KEY_ID_MIN + 1022)
#define	KEY_RADIO_ADF2_IDENT_TOGGLE		(KEY_ID_MIN + 1023)
#define	KEY_RADIO_ADF2_IDENT_SET		(KEY_ID_MIN + 1024)
#define KEY_FUEL_SELECTOR_3_OFF         (KEY_ID_MIN + 1025)
#define KEY_FUEL_SELECTOR_3_ALL         (KEY_ID_MIN + 1026)
#define KEY_FUEL_SELECTOR_3_LEFT        (KEY_ID_MIN + 1027)
#define KEY_FUEL_SELECTOR_3_RIGHT       (KEY_ID_MIN + 1028)
#define KEY_FUEL_SELECTOR_3_LEFT_AUX    (KEY_ID_MIN + 1029)
#define KEY_FUEL_SELECTOR_3_RIGHT_AUX   (KEY_ID_MIN + 1030)
#define KEY_FUEL_SELECTOR_3_CENTER      (KEY_ID_MIN + 1031)
#define KEY_FUEL_SELECTOR_3_SET         (KEY_ID_MIN + 1032)
#define KEY_FUEL_SELECTOR_4_OFF         (KEY_ID_MIN + 1033)
#define KEY_FUEL_SELECTOR_4_ALL         (KEY_ID_MIN + 1034)
#define KEY_FUEL_SELECTOR_4_LEFT        (KEY_ID_MIN + 1035)
#define KEY_FUEL_SELECTOR_4_RIGHT       (KEY_ID_MIN + 1036)
#define KEY_FUEL_SELECTOR_4_LEFT_AUX    (KEY_ID_MIN + 1037)
#define KEY_FUEL_SELECTOR_4_RIGHT_AUX   (KEY_ID_MIN + 1038)
#define KEY_FUEL_SELECTOR_4_CENTER      (KEY_ID_MIN + 1039)
#define KEY_FUEL_SELECTOR_4_SET         (KEY_ID_MIN + 1040)
#define KEY_INDUCTOR_COMPASS_REF_INC    (KEY_ID_MIN + 1041)
#define KEY_INDUCTOR_COMPASS_REF_DEC    (KEY_ID_MIN + 1042)
#define KEY_TOGGLE_CABIN_LIGHTS         (KEY_ID_MIN + 1043)
#define KEY_RESET_G_FORCE_INDICATOR     (KEY_ID_MIN + 1044)
#define KEY_RESET_MAX_RPM_INDICATOR		(KEY_ID_MIN + 1045)
#define KEY_MANUAL_FUEL_TRANSFER		(KEY_ID_MIN + 1046)
#define KEY_AP_PITCH_REF_INC_UP			(KEY_ID_MIN + 1047)
#define KEY_AP_PITCH_REF_INC_DN			(KEY_ID_MIN + 1048)
#define KEY_AP_PITCH_REF_SELECT			(KEY_ID_MIN + 1049)
#define KEY_SIM_RESET					(KEY_ID_MIN + 1050)
#define KEY_ROTOR_BRAKE          		(KEY_ID_MIN + 1051)
#define KEY_ROTOR_CLUTCH_SWITCH_TOGGLE	(KEY_ID_MIN + 1052)
#define KEY_ROTOR_CLUTCH_SWITCH_SET 	(KEY_ID_MIN + 1053)
#define KEY_ROTOR_GOV_SWITCH_TOGGLE		(KEY_ID_MIN + 1054)
#define KEY_ROTOR_GOV_SWITCH_SET   		(KEY_ID_MIN + 1055)
#define KEY_ROTOR_LATERAL_TRIM_INC 		(KEY_ID_MIN + 1056)
#define KEY_ROTOR_LATERAL_TRIM_DEC 		(KEY_ID_MIN + 1057)
#define KEY_ROTOR_LATERAL_TRIM_SET 		(KEY_ID_MIN + 1058)
#define KEY_CROSS_FEED_OPEN             (KEY_ID_MIN + 1059)
#define KEY_CROSS_FEED_TOGGLE           (KEY_ID_MIN + 1060)
#define KEY_VIRTUAL_COPILOT_TOGGLE		(KEY_ID_MIN + 1061)
#define KEY_VIRTUAL_COPILOT_SET 		(KEY_ID_MIN + 1062)
#define KEY_VIRTUAL_COPILOT_ACTION		(KEY_ID_MIN + 1063)
#define KEY_MIXTURE_SET_BEST    		(KEY_ID_MIN + 1064)
#define KEY_ADD_FUEL_QUANTITY      		(KEY_ID_MIN + 1065)
#define KEY_GPS_POWER_BUTTON      		(KEY_ID_MIN + 1066)
#define KEY_GPS_NEAREST_BUTTON      	(KEY_ID_MIN + 1068)
#define KEY_GPS_OBS_BUTTON      		(KEY_ID_MIN + 1069)
#define KEY_GPS_MSG_BUTTON      		(KEY_ID_MIN + 1070)
#define KEY_GPS_MSG_BUTTON_DOWN  		(KEY_ID_MIN + 1071)
#define KEY_GPS_MSG_BUTTON_UP    		(KEY_ID_MIN + 1072)
#define KEY_GPS_FLIGHTPLAN_BUTTON      	(KEY_ID_MIN + 1073)
#define KEY_GPS_VNAV_BUTTON      		(KEY_ID_MIN + 1074)
#define KEY_GPS_TERRAIN_BUTTON      	(KEY_ID_MIN + 1075)
#define KEY_GPS_PROCEDURE_BUTTON    	(KEY_ID_MIN + 1076)
#define KEY_GPS_SETUP_BUTTON      		(KEY_ID_MIN + 1077)
#define KEY_GPS_ACTIVATE_BUTTON      	(KEY_ID_MIN + 1078)
#define KEY_GPS_ZOOMIN_BUTTON      		(KEY_ID_MIN + 1079)
#define KEY_GPS_ZOOMOUT_BUTTON      	(KEY_ID_MIN + 1080)
#define KEY_GPS_DIRECTTO_BUTTON      	(KEY_ID_MIN + 1081)
#define KEY_GPS_MENU_BUTTON      		(KEY_ID_MIN + 1082)
#define KEY_GPS_CLEAR_BUTTON      		(KEY_ID_MIN + 1083)
#define KEY_GPS_CLEAR_ALL_BUTTON   		(KEY_ID_MIN + 1084)
#define KEY_GPS_CLEAR_BUTTON_DOWN  		(KEY_ID_MIN + 1085)
#define KEY_GPS_CLEAR_BUTTON_UP    		(KEY_ID_MIN + 1086)
#define KEY_GPS_ENTER_BUTTON      		(KEY_ID_MIN + 1087)
#define KEY_GPS_CURSOR_BUTTON      		(KEY_ID_MIN + 1088)
#define KEY_GPS_GROUP_KNOB_INC 			(KEY_ID_MIN + 1089)
#define KEY_GPS_GROUP_KNOB_DEC 			(KEY_ID_MIN + 1090)
#define KEY_GPS_PAGE_KNOB_INC  			(KEY_ID_MIN + 1091)
#define KEY_GPS_PAGE_KNOB_DEC 			(KEY_ID_MIN + 1092)
#define KEY_GPS_BUTTON1     			(KEY_ID_MIN + 1093)
#define KEY_GPS_BUTTON2     			(KEY_ID_MIN + 1094)
#define KEY_GPS_BUTTON3     			(KEY_ID_MIN + 1095)
#define KEY_GPS_BUTTON4     			(KEY_ID_MIN + 1096)
#define KEY_GPS_BUTTON5     			(KEY_ID_MIN + 1097)
#define KEY_THROTTLE_DECR_SMALL         (KEY_ID_MIN + 1098)
#define KEY_THROTTLE1_DECR_SMALL        (KEY_ID_MIN + 1099)
#define KEY_THROTTLE2_DECR_SMALL        (KEY_ID_MIN + 1100)
#define KEY_THROTTLE3_DECR_SMALL        (KEY_ID_MIN + 1101)
#define KEY_THROTTLE4_DECR_SMALL        (KEY_ID_MIN + 1102)
#define KEY_PROP_PITCH_DECR_SMALL       (KEY_ID_MIN + 1103)
#define KEY_PROP_PITCH1_DECR_SMALL      (KEY_ID_MIN + 1104)
#define KEY_PROP_PITCH2_DECR_SMALL      (KEY_ID_MIN + 1105)
#define KEY_PROP_PITCH3_DECR_SMALL      (KEY_ID_MIN + 1106)
#define KEY_PROP_PITCH4_DECR_SMALL      (KEY_ID_MIN + 1107)
#define KEY_MIXTURE_DECR_SMALL          (KEY_ID_MIN + 1108)
#define KEY_MIXTURE1_DECR_SMALL         (KEY_ID_MIN + 1109)
#define KEY_MIXTURE2_DECR_SMALL         (KEY_ID_MIN + 1110)
#define KEY_MIXTURE3_DECR_SMALL         (KEY_ID_MIN + 1111)
#define KEY_MIXTURE4_DECR_SMALL         (KEY_ID_MIN + 1112)

// XML tokens aircraft_varget
typedef enum XML_TOKEN
{
	XML_NONE,
	XML_ANGLE_OF_ATTACK_INDICATOR,
	XML_GUN_AMMO,
	XML_CANNON_AMMO,
	XML_ROCKET_AMMO,
	XML_BOMB_AMMO,
	XML_LIGHT_STATES,
	XML_LIGHT_PANEL,
	XML_LIGHT_STROBE,
	XML_LIGHT_LANDING,
	XML_STROBE_FLASH,
	XML_LIGHT_TAXI,
	XML_LIGHT_BEACON,
	XML_LIGHT_NAV,
	XML_LIGHT_LOGO,
	XML_LIGHT_WING,
	XML_LIGHT_RECOGNITION,
	XML_LIGHT_CABIN,
	XML_LANDING_LIGHT_PBH,
	XML_CENTER_WHEEL_RPM,
	XML_LEFT_WHEEL_RPM,
	XML_RIGHT_WHEEL_RPM,
	XML_TOTAL_WORLD_VELOCITY,
	XML_GROUND_VELOCITY,
	XML_AIRSPEED_TRUE,
	XML_AIRSPEED_INDICATED,
	XML_AIRSPEED_SELECT_INDICATED_OR_TRUE,
	XML_AIRSPEED_TRUE_CALIBRATE,
	XML_AIRSPEED_BARBER_POLE,
	XML_AIRSPEED_MACH,
	XML_VERTICAL_SPEED,
	XML_MACH_MAX_OPERATE,
	XML_STALL_WARNING,
	XML_OVERSPEED_WARNING,
	XML_BARBER_POLE_MACH,
	XML_VELOCITY_BODY_X,
	XML_VELOCITY_BODY_Y,
	XML_VELOCITY_BODY_Z,
	XML_VELOCITY_WORLD_X,
	XML_VELOCITY_WORLD_Y,
	XML_VELOCITY_WORLD_Z,
	XML_RELATIVE_WIND_VELOCITY_BODY_X,
	XML_RELATIVE_WIND_VELOCITY_BODY_Y,
	XML_RELATIVE_WIND_VELOCITY_BODY_Z,
	XML_DESIGN_SPEED_VS0,
	XML_DESIGN_SPEED_VS1,
	XML_DESIGN_SPEED_VC,
	XML_MIN_DRAG_VELOCITY,
	XML_PLANE_LATITUDE,
	XML_PLANE_LONGITUDE,
	XML_PLANE_ALTITUDE,
	XML_PLANE_ALT_ABOVE_GROUND,
	XML_PLANE_PITCH_DEGREES,
	XML_PLANE_BANK_DEGREES,
	XML_PLANE_HEADING_DEGREES_MAGNETIC,
	XML_PLANE_HEADING_DEGREES_TRUE,
	XML_INDICATED_ALTITUDE,
	XML_PRESSURE_ALTITUDE,
	XML_KOHLSMAN_SETTING_MB,
	XML_KOHLSMAN_SETTING_HG,
	XML_ATTITUDE_INDICATOR_PITCH_DEGREES,
	XML_ATTITUDE_INDICATOR_BANK_DEGREES,
	XML_ATTITUDE_BARS_POSITION,
	XML_ATTITUDE_CAGE,
	XML_MAGVAR,
	XML_WISKEY_COMPASS_INDICATION_DEGREES,
	XML_PLANE_HEADING_DEGREES_GYRO,
	XML_GYRO_DRIFT_ERROR,
	XML_DELTA_HEADING_RATE,
	XML_GROUND_ALTITUDE,
	XML_SIM_ON_GROUND,
	XML_TURN_COORDINATOR_BALL,
	XML_YOKE_Y_POSITION,
	XML_YOKE_Y_INDICATOR,
	XML_YOKE_X_POSITION,
	XML_YOKE_X_INIDICATOR,
	XML_AILERON_POSITION,
	XML_RUDDER_PEDAL_POSITION,
	XML_RUDDER_PEDAL_INDICATOR,
	XML_RUDDER_POSITION,
	XML_ELEVATOR_POSITION,
	XML_ELEVATOR_TRIM_POSITION,
	XML_ELEVATOR_TRIM_INDICATOR,
	XML_ELEVATOR_TRIM_PCT,
	XML_BRAKE_LEFT_POSITION,
	XML_BRAKE_RIGHT_POSITION,
	XML_BRAKE_INDICATOR,
	XML_BRAKE_PARKING_POSITION,
	XML_BRAKE_PARKING_INDICATOR,
	XML_SPOILERS_ARMED,
	XML_SPOILERS_HANDLE_POSITION,
	XML_SPOILERS_LEFT_POSITION,
	XML_SPOILERS_RIGHT_POSITION,
	XML_FLAPS_NUM_HANDLE_POSITIONS,
	XML_FLAPS_HANDLE_PERCENT,
	XML_FLAPS_HANDLE_INDEX,
	XML_TRAILING_EDGE_FLAPS_LEFT_PERCENT,
	XML_TRAILING_EDGE_FLAPS_RIGHT_PERCENT,
	XML_LEADING_EDGE_FLAPS_LEFT_PERCENT,
	XML_LEADING_EDGE_FLAPS_RIGHT_PERCENT,
	XML_TRAILING_EDGE_FLAPS_LEFT_ANGLE,
	XML_TRAILING_EDGE_FLAPS_RIGHT_ANGLE,
	XML_LEADING_EDGE_FLAPS_LEFT_ANGLE,
	XML_LEADING_EDGE_FLAPS_RIGHT_ANGLE,
	XML_FLAP_POSITION_SET,
	XML_IS_GEAR_RETRACTABLE,
	XML_IS_GEAR_WHEELS,
	XML_IS_GEAR_SKIS,
	XML_IS_GEAR_FLOATS,
	XML_IS_GEAR_SKIDS,
	XML_GEAR_HANDLE_POSITION,
	XML_GEAR_CENTER_POSITION,
	XML_GEAR_LEFT_POSITION,
	XML_GEAR_RIGHT_POSITION,
	XML_GEAR_TAIL_POSITION,
	XML_GEAR_AUX_POSITION,
	XML_GEAR_POSITION,
	XML_GEAR_ANIMATION_POSITION,
	XML_GEAR_TOTAL_PCT_EXTENDED,
	XML_TAILWHEEL_LOCK_ON,
	XML_COWL_FLAPS,
	XML_AVIONICS_MASTER_SWITCH,
	XML_PANEL_AUTO_FEATHER_SWITCH,
	XML_PANEL_ANTI_ICE_SWITCH,
	XML_AUTO_BRAKE_SWITCH_CB,
	XML_WATER_RUDDER_HANDLE_POSITION,
	XML_WATER_LEFT_RUDDER_EXTENDED,
	XML_WATER_RIGHT_RUDDER_EXTENDED,
	XML_GEAR_CENTER_STEER_ANGLE,
	XML_GEAR_LEFT_STEER_ANGLE,
	XML_GEAR_RIGHT_STEER_ANGLE,
	XML_GEAR_AUX_STEER_ANGLE,
	XML_GEAR_STEER_ANGLE,
	XML_WATER_LEFT_RUDDER_STEER_ANGLE,
	XML_WATER_RIGHT_RUDDER_STEER_ANGLE,
	XML_GEAR_CENTER_STEER_ANGLE_PCT,
	XML_GEAR_LEFT_STEER_ANGLE_PCT,
	XML_GEAR_RIGHT_STEER_ANGLE_PCT,
	XML_GEAR_AUX_STEER_ANGLE_PCT,
	XML_GEAR_STEER_ANGLE_PCT,
	XML_WATER_LEFT_RUDDER_STEER_ANGLE_PCT,
	XML_WATER_RIGHT_RUDDER_STEER_ANGLE_PCT,
	XML_ELEVATOR_DEFLECTION,
	XML_ELEVATOR_DEFLECTION_PCT,
	XML_AILERON_LEFT_DEFLECTION,
	XML_AILERON_LEFT_DEFLECTION_PCT,
	XML_AILERON_RIGHT_DEFLECTION,
	XML_AILERON_RIGHT_DEFLECTION_PCT,
	XML_AILERON_AVERAGE_DEFLECTION,
	XML_AILERON_TRIM,
	XML_AILERON_TRIM_PCT,
	XML_RUDDER_DEFLECTION,
	XML_RUDDER_DEFLECTION_PCT,
	XML_RUDDER_TRIM,
	XML_RUDDER_TRIM_PCT,
	XML_PROP_SYNC_ACTIVE,
	XML_INCIDENCE_ALPHA,
	XML_INCIDENCE_BETA,
	XML_CG_PERCENT,
	XML_CG_PERCENT_LATERAL,
	XML_CG_AFT_LIMIT,
	XML_CG_FWD_LIMIT,
	XML_CG_MAX_MACH,
	XML_CG_MIN_MACH,
	XML_PAYLOAD_STATION_WEIGHT,
	XML_PAYLOAD_STATION_NAME,
	XML_PAYLOAD_STATION_COUNT,
	XML_ELEVON_DEFLECTION,
	XML_FOLDING_WING_LEFT_PERCENT,
	XML_FOLDING_WING_RIGHT_PERCENT,
	XML_CANOPY_OPEN,
	XML_TAILHOOK_POSITION,
	XML_EXIT_OPEN,
	XML_RADIO_HEIGHT,
	XML_DECISION_HEIGHT,
	XML_TOTAL_WEIGHT,
	XML_MAX_GROSS_WEIGHT,
	XML_EMPTY_WEIGHT,
	XML_AUTOPILOT_MASTER,
	XML_AUTOPILOT_WING_LEVELER,
	XML_AUTOPILOT_NAV1_LOCK,
	XML_AUTOPILOT_HEADING_LOCK,
	XML_AUTOPILOT_HEADING_LOCK_DIR,
	XML_AUTOPILOT_ALTITUDE_LOCK,
	XML_AUTOPILOT_ALTITUDE_LOCK_VAR,
	XML_AUTOPILOT_ATTITUDE_HOLD,
	XML_AUTOPILOT_GLIDESLOPE_HOLD,
	XML_AUTOPILOT_APPROACH_HOLD,
	XML_AUTOPILOT_BACKCOURSE_HOLD,
	XML_AUTOPILOT_YAW_DAMPER,
	XML_AUTOPILOT_AIRSPEED_HOLD,
	XML_AUTOPILOT_AIRSPEED_HOLD_VAR,
	XML_AUTOPILOT_MACH_HOLD,
	XML_AUTOPILOT_MACH_HOLD_VAR,
	XML_AUTOPILOT_VERTICAL_HOLD,
	XML_AUTOPILOT_VERTICAL_HOLD_VAR,
	XML_AUTOPILOT_ALTITUDE_MANUALLY_TUNABLE,
	XML_AUTOPILOT_HEADING_MANUALLY_TUNABLE,
	XML_AUTOPILOT_THROTTLE_ARM,
	XML_AUTOPILOT_TAKEOFF_POWER_ACTIVE,
	XML_AUTOPILOT_RPM_HOLD_VAR,
	XML_AUTOPILOT_SPEED_SETTING,
	XML_AUTOPILOT_AIRSPEED_ACQUISITION,
	XML_AUTOPILOT_AIRSPEED_HOLD_CURRENT,
	XML_AUTOPILOT_MAX_SPEED_HOLD,
	XML_AUTOPILOT_CRUISE_SPEED_HOLD,
	XML_AUTOPILOT_FLIGHT_DIRECTOR_ACTIVE,
	XML_AUTOPILOT_FLIGHT_DIRECTOR_PITCH,
	XML_AUTOPILOT_FLIGHT_DIRECTOR_BANK,
	XML_AUTOPILOT_PITCH_HOLD_REF,
	XML_AUTOPILOT_NAV_SELECTED,
	XML_GPS_DRIVES_NAV1,
	XML_AUTOTHROTTLE_ACTIVE,
	XML_ENGINE_CONTROL_SELECT,
	XML_NUMBER_OF_ENGINES,
	XML_PROPELLER_ADVANCED_SELECTION,
	XML_THROTTLE_LOWER_LIMIT,
	XML_OIL_AMOUNT,
	XML_ENGINE_PRIMER,
	XML_ENGINE_TYPE,
	XML_ENG_RPM_ANIMATION_PERCENT,
	XML_PROP_RPM,
	XML_PROP_MAX_RPM_PERCENT,
	XML_PROP_THRUST,
	XML_PROP_BETA,
	XML_PROP_FEATHERING_INHIBIT,
	XML_PROP_FEATHERED,
	XML_PROP_SYNC_DELTA_LEVER,
	XML_PROP_AUTO_FEATHER_ARMED,
	XML_PROP_FEATHER_SWITCH,
	XML_PROP_AUTO_CRUISE_ACTIVE,
	XML_MASTER_IGNITION_SWITCH,
	XML_ENG_COMBUSTION,
	XML_OLD_ENG_STARTER,
	XML_ENG_N1_RPM,
	XML_ENG_N2_RPM,
	XML_ENG_FUEL_FLOW_GPH,
	XML_ENG_FUEL_FLOW_PPH,
	XML_ENG_FUEL_FLOW_PPH_SSL,
	XML_ENG_TORQUE,
	XML_ENG_ANTI_ICE,
	XML_ENG_PRESSURE_RATIO,
	XML_ENG_PRESSURE_RATIO_GES,
	XML_ENG_EXHAUST_GAS_TEMPERATURE,
	XML_ENG_EXHAUST_GAS_TEMPERATURE_GES,
	XML_ENG_CYLINDER_HEAD_TEMPERATURE,
	XML_ENG_OIL_TEMPERATURE,
	XML_ENG_OIL_PRESSURE,
	XML_ENG_OIL_QUANTITY,
	XML_ENG_HYDRAULIC_PRESSURE,
	XML_ENG_HYDRAULIC_QUANTITY,
	XML_ENG_MANIFOLD_PRESSURE,
	XML_ENG_VIBRATION,
	XML_ENG_RPM_SCALER,
	XML_ENG_TURBINE_TEMPERATURE,
	XML_ENG_TORQUE_PERCENT,
	XML_ENG_FUEL_PRESSURE,
	XML_ENG_ELECTRICAL_LOAD,
	XML_ENG_TRANSMISSION_PRESSURE,
	XML_ENG_TRANSMISSION_TEMPERATURE,
	XML_ENG_ROTOR_RPM,
	XML_ENG_FUEL_FLOW_BUG_POSITION,
	XML_ENG_MAX_RPM,
	XML_ENG_ON_FIRE,
	XML_GENERAL_ENG_COMBUSTION,
	XML_GENERAL_ENG_MASTER_ALTERNATOR,
	XML_GENERAL_ENG_FUEL_PUMP_SWITCH,
	XML_GENERAL_ENG_FUEL_PUMP_ON,
	XML_GENERAL_ENG_RPM,
	XML_GENERAL_ENG_PCT_MAX_RPM,
	XML_GENERAL_ENG_MAX_REACHED_RPM,
	XML_GENERAL_ENG_THROTTLE_LEVER_POSITION,
	XML_GENERAL_ENG_MIXTURE_LEVER_POSITION,
	XML_GENERAL_ENG_PROPELLER_LEVER_POSITION,
	XML_GENERAL_ENG_STARTER,
	XML_GENERAL_ENG_EXHAUST_GAS_TEMPERATURE,
	XML_GENERAL_ENG_OIL_PRESSURE,
	XML_GENERAL_ENG_OIL_LEAKED_PERCENT,
	XML_GENERAL_ENG_COMBUSTION_SOUND_PERCENT,
	XML_GENERAL_ENG_DAMAGE_PERCENT,
	XML_GENERAL_ENG_OIL_TEMPERATURE,
	XML_GENERAL_ENG_FAILED,
	XML_GENERAL_ENG_GENERATOR_SWITCH,
	XML_GENERAL_ENG_GENERATOR_ACTIVE,
	XML_GENERAL_ENG_ANTI_ICE_POSITION,
	XML_GENERAL_ENG_FUEL_VALVE,
	XML_GENERAL_ENG_FUEL_PRESSURE,
	XML_GENERAL_ENG_ELAPSED_TIME,
	XML_RECIP_ENG_COWL_FLAP_POSITION,
	XML_RECIP_ENG_PRIMER,
	XML_RECIP_ENG_MANIFOLD_PRESSURE,
	XML_RECIP_ENG_ALTERNATE_AIR_POSITION,
	XML_RECIP_ENG_COOLANT_RESERVOIR_PERCENT,
	XML_RECIP_ENG_LEFT_MAGNETO,
	XML_RECIP_ENG_RIGHT_MAGNETO,
	XML_RECIP_ENG_BRAKE_POWER,
	XML_RECIP_ENG_STARTER_TORQUE,
	XML_RECIP_ENG_TURBOCHARGER_FAILED,
	XML_RECIP_ENG_EMERGENCY_BOOST_ACTIVE,
	XML_RECIP_ENG_EMERGENCY_BOOST_ELAPSED_TIME,
	XML_RECIP_ENG_WASTEGATE_POSITION,
	XML_RECIP_ENG_TURBINE_INLET_TEMPERATURE,
	XML_RECIP_ENG_CYLINDER_HEAD_TEMPERATURE,
	XML_RECIP_ENG_RADIATOR_TEMPERATURE,
	XML_RECIP_ENG_FUEL_AVAILABLE,
	XML_RECIP_ENG_FUEL_FLOW,
	XML_RECIP_ENG_FUEL_TANK_SELECTOR,
	XML_RECIP_ENG_FUEL_TANKS_USED,
	XML_RECIP_ENG_FUEL_NUMBER_TANKS_USED,
	XML_RECIP_CARBURETOR_TEMPERATURE,
	XML_RECIP_MIXTURE_RATIO,
	XML_TURB_ENG_N1,
	XML_TURB_ENG_N2,
	XML_TURB_ENG_CORRECTED_N1,
	XML_TURB_ENG_CORRECTED_N2,
	XML_TURB_ENG_CORRECTED_FF,
	XML_TURB_ENG_MAX_TORQUE_PERCENT,
	XML_TURB_ENG_PRESSURE_RATIO,
	XML_TURB_ENG_ITT,
	XML_TURB_ENG_AFTERBURNER,
	XML_TURB_ENG_JET_THRUST,
	XML_TURB_ENG_BLEED_AIR,
	XML_TURB_ENG_TANK_SELECTOR,
	XML_TURB_ENG_TANKS_USED,
	XML_TURB_ENG_NUM_TANKS_USED,
	XML_TURB_ENG_FUEL_FLOW_PPH,
	XML_TURB_ENG_FUEL_AVAILABLE,
	XML_TURB_ENG_PRIMARY_NOZZLE_PERCENT,
	XML_TURB_ENG_REVERSE_NOZZLE_PERCENT,
	XML_TURB_ENG_VIBRATION,
	XML_ENG_FAILED,
	XML_PARTIAL_PANEL_ADF,
	XML_PARTIAL_PANEL_AIRSPEED,
	XML_PARTIAL_PANEL_ALTIMETER,
	XML_PARTIAL_PANEL_ATTITUDE,
	XML_PARTIAL_PANEL_COMM,
	XML_PARTIAL_PANEL_COMPASS,
	XML_PARTIAL_PANEL_ELECTRICAL,
	XML_PARTIAL_PANEL_AVIONICS,
	XML_PARTIAL_PANEL_ENGINE,
	XML_PARTIAL_PANEL_FUEL_INDICATOR,
	XML_PARTIAL_PANEL_HEADING,
	XML_PARTIAL_PANEL_VERTICAL_VELOCITY,
	XML_PARTIAL_PANEL_TRANSPONDER,
	XML_PARTIAL_PANEL_NAV,
	XML_PARTIAL_PANEL_PITOT,
	XML_PARTIAL_PANEL_TURN_COORDINATOR,
	XML_PARTIAL_PANEL_VACUUM,
	XML_FUEL_TANK_CENTER_LEVEL,
	XML_FUEL_TANK_CENTER_CAPACITY,
	XML_FUEL_TANK_CENTER_QUANTITY,
	XML_FUEL_TANK_CENTER2_LEVEL,
	XML_FUEL_TANK_CENTER2_CAPACITY,
	XML_FUEL_TANK_CENTER2_QUANTITY,
	XML_FUEL_TANK_CENTER3_LEVEL,
	XML_FUEL_TANK_CENTER3_CAPACITY,
	XML_FUEL_TANK_CENTER3_QUANTITY,
	XML_FUEL_TANK_LEFT_MAIN_LEVEL,
	XML_FUEL_TANK_LEFT_MAIN_CAPACITY,
	XML_FUEL_TANK_LEFT_MAIN_QUANTITY,
	XML_FUEL_TANK_LEFT_AUX_LEVEL,
	XML_FUEL_TANK_LEFT_AUX_CAPACITY,
	XML_FUEL_TANK_LEFT_AUX_QUANTITY,
	XML_FUEL_TANK_LEFT_TIP_LEVEL,
	XML_FUEL_TANK_LEFT_TIP_CAPACITY,
	XML_FUEL_TANK_LEFT_TIP_QUANTITY,
	XML_FUEL_LEFT_QUANTITY,
	XML_FUEL_TANK_RIGHT_MAIN_LEVEL,
	XML_FUEL_TANK_RIGHT_MAIN_CAPACITY,
	XML_FUEL_TANK_RIGHT_MAIN_QUANTITY,
	XML_FUEL_TANK_RIGHT_AUX_LEVEL,
	XML_FUEL_TANK_RIGHT_AUX_CAPACITY,
	XML_FUEL_TANK_RIGHT_AUX_QUANTITY,
	XML_FUEL_TANK_RIGHT_TIP_LEVEL,
	XML_FUEL_TANK_RIGHT_TIP_CAPACITY,
	XML_FUEL_TANK_RIGHT_TIP_QUANTITY,
	XML_FUEL_RIGHT_QUANTITY,
	XML_FUEL_TANK_EXTERNAL1_LEVEL,
	XML_FUEL_TANK_EXTERNAL1_CAPACITY,
	XML_FUEL_TANK_EXTERNAL1_QUANTITY,
	XML_FUEL_TANK_EXTERNAL2_LEVEL,
	XML_FUEL_TANK_EXTERNAL2_CAPACITY,
	XML_FUEL_TANK_EXTERNAL2_QUANTITY,
	XML_FUEL_TOTAL_QUANTITY,
	XML_FUEL_TOTAL_CAPACITY,
	XML_FUEL_LEFT_CAPACITY,
	XML_FUEL_RIGHT_CAPACITY,
	XML_FUEL_WEIGHT_PER_GALLON,
	XML_FUEL_TANK_SELECTOR,
	XML_FUEL_CROSS_FEED,
	XML_NUM_FUEL_SELECTORS,
	XML_FUEL_SELECTED_QUANTITY_PERCENT,
	XML_FUEL_SELECTED_QUANTITY,
	XML_FUEL_TOTAL_QUANTITY_WEIGHT,
	XML_FUEL_SELECTED_TRANSFER_MODE,
	XML_WARNING_FUEL,
	XML_WARNING_FUEL_LEFT,
	XML_WARNING_FUEL_RIGHT,
	XML_WARNING_VACUUM,
	XML_WARNING_VACUUM_LEFT,
	XML_WARNING_VACUUM_RIGHT,
	XML_WARNING_OIL_PRESSURE,
	XML_WARNING_VOLTAGE,
	XML_WARNING_LOW_HEIGHT,
	XML_AUTOPILOT_AVAILABLE,
	XML_FLAPS_AVAILABLE,
	XML_STALL_HORN_AVAILABLE,
	XML_ENGINE_MIXURE_AVAILABLE,
	XML_CARB_HEAT_AVAILABLE,
	XML_SPOILER_AVAILABLE,
	XML_STROBES_AVAILABLE,
	XML_PROP_TYPE_AVAILABLE,
	XML_TOE_BRAKES_AVAILABLE,
	XML_IS_TAIL_DRAGGER,
	XML_SYSTEMS_AVAILABLE,
	XML_INSTRUMENTS_AVAILABLE,
	XML_FUEL_PUMP,
	XML_NAV_AVAILABLE,
	XML_ELECTRICAL_MASTER_BATTERY,
	XML_ELECTRICAL_OLD_CHARGING_AMPS,
	XML_ELECTRICAL_TOTAL_LOAD_AMPS,
	XML_ELECTRICAL_BATTERY_LOAD,
	XML_ELECTRICAL_BATTERY_VOLTAGE,
	XML_ELECTRICAL_MAIN_BUS_VOLTAGE,
	XML_ELECTRICAL_MAIN_BUS_AMPS,
	XML_ELECTRICAL_AVIONICS_BUS_VOLTAGE,
	XML_ELECTRICAL_AVIONICS_BUS_AMPS,
	XML_ELECTRICAL_HOT_BATTERY_BUS_VOLTAGE,
	XML_ELECTRICAL_HOT_BATTERY_BUS_AMPS,
	XML_ELECTRICAL_BATTERY_BUS_VOLTAGE,
	XML_ELECTRICAL_BATTERY_BUS_AMPS,
	XML_ELECTRICAL_GENALT_BUS_VOLTAGE,
	XML_ELECTRICAL_GENALT_BUS_AMPS,
	XML_CIRCUIT_GENERAL_PANEL_ON,
	XML_CIRCUIT_FLAP_MOTOR_ON,
	XML_CIRCUIT_GEAR_MOTOR_ON,
	XML_CIRCUIT_AUTOPILOT_ON,
	XML_CIRCUIT_AVIONICS_ON,
	XML_CIRCUIT_PITOT_HEAT_ON,
	XML_CIRCUIT_PROP_SYNC_ON,
	XML_CIRCUIT_AUTO_FEATHER_ON,
	XML_CIRCUIT_AUTO_BRAKES_ON,
	XML_CIRCUIT_STANDY_VACUUM_ON,
	XML_CIRCUIT_MARKER_BEACON_ON,
	XML_CIRCUIT_GEAR_WARNING_ON,
	XML_CIRCUIT_HYDRAULIC_PUMP_ON,
	XML_AMBIENT_DENSITY,
	XML_AMBIENT_TEMPERATURE,
	XML_AMBIENT_PRESSURE,
	XML_AMBIENT_WIND_VELOCITY,
	XML_AMBIENT_WIND_DIRECTION,
	XML_AMBIENT_WIND_X,
	XML_AMBIENT_WIND_Y,
	XML_AMBIENT_WIND_Z,
	XML_AMBIENT_PRECIP_STATE,
	XML_BAROMETER_PRESSURE,
	XML_SEA_LEVEL_PRESSURE,
	XML_TOTAL_AIR_TEMPERATURE,
	XML_STANDARD_ATM_TEMPERATURE,
	XML_AIRCRAFT_WIND_X,
	XML_AIRCRAFT_WIND_Y,
	XML_AIRCRAFT_WIND_Z,
	XML_HYDRAULIC_PRESSURE,
	XML_HYDRAULIC_RESERVOIR_PERCENT,
	XML_HYDRAULIC_SYSTEM_INTEGRITY,
	XML_GEAR_HYDRAULIC_PRESSURE,
	XML_CONCORDE_VISOR_NOSE_HANDLE,
	XML_CONCORDE_VISOR_POSITION_PERCENT,
	XML_CONCORDE_NOSE_ANGLE,
	XML_COM_TRANSMIT,
	XML_COM_RECIEVE_ALL,
	XML_NAV_SOUND,
	XML_DME_SOUND,
	XML_ADF_SOUND,
	XML_ADF_CARD,
	XML_MARKER_SOUND,
	XML_COM_ACTIVE_FREQUENCY,
	XML_COM_STANDBY_FREQUENCY,
	XML_COM_STATUS,
	XML_TRANSPONDER_CODE,
	XML_ADF_FREQUENCY,
	XML_ADF_EXT_FREQUENCY,
	XML_ADF_ACTIVE_FREQUENCY,
	XML_ADF_STANDBY_FREQUENCY,
	XML_ADF_LATLONALT,
	XML_ADF_SIGNAL,
	XML_ADF_RADIAL,
	XML_ADF_IDENT,
	XML_ADF_NAME,
	XML_NAV_ACTIVE_FREQUENCY,
	XML_NAV_STANDBY_FREQUENCY,
	XML_NAV_SIGNAL,
	XML_NAV_IDENT,
	XML_NAV_NAME,
	XML_NAV_CODES,
	XML_NAV_HAS_NAV,
	XML_NAV_HAS_LOCALIZER,
	XML_NAV_HAS_DME,
	XML_NAV_HAS_GLIDE_SLOPE,
	XML_NAV_BACK_COURSE_FLAGS,
	XML_NAV_MAGVAR,
	XML_NAV_RADIAL,
	XML_NAV_RADIAL_ERROR,
	XML_NAV_LOCALIZER,
	XML_NAV_GLIDE_SLOPE,
	XML_NAV_GLIDE_SLOPE_ERROR,
	XML_NAV_CDI,
	XML_NAV_GSI,
	XML_NAV_TOFROM,
	XML_NAV_GS_FLAG,
	XML_NAV_OBS,
	XML_NAV_DME,
	XML_NAV_DMESPEED,
	XML_NAV_VOR_LATLONALT,
	XML_NAV_GS_LATLONALT,
	XML_NAV_DME_LATLONALT,
	XML_MARKER_BEACON_STATE,
	XML_INNER_MARKER,
	XML_MIDDLE_MARKER,
	XML_OUTER_MARKER,
	XML_INNER_MARKER_LATLONALT,
	XML_MIDDLE_MARKER_LATLONALT,
	XML_OUTER_MARKER_LATLONALT,
	XML_REALISM,
	XML_AUTO_COORDINATION,
	XML_UNLIMITED_FUEL,
	XML_ATC_TYPE,
	XML_ATC_MODEL,
	XML_ATC_HEAVY,
	XML_ATC_ID,
	XML_ATC_AIRLINE,
	XML_ATC_FLIGHT_NUMBER,
	XML_STRUCT_LATLONALT,
	XML_STRUCT_LATLONALTPBH,
	XML_STRUCT_PBH32,
	XML_STRUCT_DAMAGEVISIBLE,
	XML_STRUCT_WORLDVELOCITY,
	XML_STRUCT_WORLD_ROTATION_VELOCITY,
	XML_STRUCT_ENGINE_POSITION,
	XML_PITOT_HEAT,
	XML_SMOKE_ENABLE,
	XML_SMOKESYSTEM_AVAILABLE,
	XML_G_FORCE,
	XML_MAX_G_FORCE,
	XML_MIN_G_FORCE,
	XML_SUCTION_PRESSURE,
	XML_RAD_INS_SWITCH,
	XML_TYPICAL_DESCENT_RATE,
	XML_VISUAL_MODEL_RADIUS,
	XML_IS_USER_SIM,
	XML_CONTROLLABLE,
	XML_HEADING_INDICATOR,
	XML_TITLE,
	XML_CATEGORY,
	XML_SIM_DISABLED,
	XML_PROP_DEICE_SWITCH,
	XML_STRUCTURAL_DEICE_SWITCH,
	XML_ARTIFICIAL_GROUND_ELEVATION,
	XML_SURFACE_TYPE,
	XML_SURFACE_CONDITION,
	XML_PUSHBACK_STATE,
	XML_HSI_CDI_NEEDLE,
	XML_HSI_GSI_NEEDLE,
	XML_HSI_CDI_NEEDLE_VALID,
	XML_HSI_GSI_NEEDLE_VALID,
	XML_HSI_TF_FLAGS,
	XML_HSI_BEARING,
	XML_HSI_BEARING_VALID,
	XML_HSI_HAS_LOCALIZER,
	XML_HSI_SPEED,
	XML_HSI_DISTANCE,
	XML_HSI_STATION_IDENT,
	XML_IS_SLEW_ACTIVE,
	XML_IS_SLEW_ALLOWED,
	XML_ATC_SUGGESTED_MIN_RWY_TAKEOFF,
	XML_ATC_SUGGESTED_MIN_RWY_LANDING,
	XML_YAW_STRING_ANGLE,
	XML_YAW_STRING_PCT_EXTENDED,
	XML_INDUCTOR_COMPASS_PERCENT_DEVIATION,
	XML_INDUCTOR_COMPASS_HEADING_REF,
	XML_ANEMOMETER_PCT_RPM,
	XML_GPS_POSITION_LAT,
	XML_GPS_POSITION_LON,
	XML_GPS_POSITION_ALT,
	XML_GPS_MAGVAR,
	XML_GPS_IS_ACTIVE_FLIGHT_PLAN,
	XML_GPS_IS_ACTIVE_WAY_POINT,
	XML_GPS_IS_ARRIVED,
	XML_GPS_IS_DIRECTTO_FLIGHTPLAN,
	XML_GPS_GROUND_SPEED,
	XML_GPS_GROUND_TRUE_HEADING,
	XML_GPS_GROUND_MAGNETIC_TRACK,
	XML_GPS_GROUND_TRUE_TRACK,
	XML_GPS_ETE,
	XML_GPS_ETA,
	XML_GPS_WP_DISTANCE,
	XML_GPS_WP_BEARING,
	XML_GPS_WP_TRUE_BEARING,
	XML_GPS_WP_CROSS_TRK,
	XML_GPS_WP_DESIRED_TRACK,
	XML_GPS_WP_TRUE_REQ_HDG,
	XML_GPS_WP_VERTICAL_SPEED,
	XML_GPS_WP_TRACK_ANGLE_ERROR,
	XML_GPS_WP_NEXT_ID,
	XML_GPS_WP_NEXT_LAT,
	XML_GPS_WP_NEXT_LON,
	XML_GPS_WP_NEXT_ALT,
	XML_GPS_WP_PREV_VALID,
	XML_GPS_WP_PREV_ID,
	XML_GPS_WP_PREV_LAT,
	XML_GPS_WP_PREV_LON,
	XML_GPS_WP_PREV_ALT,
	XML_GPS_WP_ETE,
	XML_GPS_WP_ETA,
	XML_GPS_COURSE_TO_STEER,
	XML_GPS_FLIGHT_PLAN_WP_INDEX,
	XML_GPS_FLIGHT_PLAN_WP_COUNT,
	XML_GPS_IS_ACTIVE_WP_LOCKED,
	XML_GPS_IS_APPROACH_LOADED,
	XML_GPS_IS_APPROACH_ACTIVE,
	XML_GPS_APPROACH_MODE,
	XML_GPS_APPROACH_WP_TYPE,
	XML_GPS_APPROACH_IS_WP_RUNWAY,
	XML_GPS_APPROACH_SEGMENT_TYPE,
	XML_GPS_APPROACH_AIRPORT_ID,
	XML_GPS_APPROACH_APPROACH_INDEX,
	XML_GPS_APPROACH_APPROACH_ID,
	XML_GPS_APPROACH_APPROACH_TYPE,
	XML_GPS_APPROACH_TRANSITION_INDEX,
	XML_GPS_APPROACH_TRANSITION_ID,
	XML_GPS_APPROACH_IS_FINAL,
	XML_GPS_APPROACH_IS_MISSED,
	XML_GPS_APPROACH_TIMEZONE_DEVIATION,
	XML_GPS_APPROACH_WP_INDEX,
	XML_GPS_APPROACH_WP_COUNT,
	XML_GPS_TARGET_DISTANCE,
	XML_GPS_TARGET_ALTITUDE,
	XML_USER_INPUT_ENABLED,
	XML_ROTOR_BRAKE_HANDLE_POS,
	XML_ROTOR_BRAKE_ACTIVE,
	XML_ROTOR_CLUTCH_SWITCH_POS,
	XML_ROTOR_CLUTCH_ACTIVE,
	XML_ROTOR_TEMPERATURE,
	XML_ROTOR_CHIP_DETECTED,
	XML_ROTOR_GOV_SWITCH_POS,
	XML_ROTOR_GOV_ACTIVE,
	XML_ROTOR_LATERAL_TRIM_PCT,
	XML_ROTOR_RPM_PCT,
	XML_GEAR_DAMAGE_BY_SPEED,
	XML_GEAR_SPEED_EXCEEDED,
	XML_FLAP_DAMAGE_BY_SPEED,
	XML_FLAP_SPEED_EXCEEDED,
	XML_ESTIMATED_CRUISE_SPEED,
	XML_ESTIMATED_FUEL_FLOW,
	XML_EYEPOINT_POSITION,
	XML_DEFAULT_2D_COCKPIT_VIEW_ANGLE,
	XML_DEFAULT_VC_COCKPIT_VIEW_ANGLE,
	XML_NAV_VOR_LLAF64,
	XML_NAV_GS_LLAF64,
	XML_NAV_RAW_GLIDE_SLOPE,
	XML_WINDSHIELD_RAIN_EFFECT_AVAILABLE,
	XML_TRAILING_EDGE_FLAPS0_LEFT_PERCENT,
	XML_TRAILING_EDGE_FLAPS1_LEFT_PERCENT,
	XML_TRAILING_EDGE_FLAPS0_RIGHT_PERCENT,
	XML_TRAILING_EDGE_FLAPS1_RIGHT_PERCENT,
	XML_LEADING_EDGE_FLAPS0_LEFT_PERCENT,
	XML_LEADING_EDGE_FLAPS1_LEFT_PERCENT,
	XML_LEADING_EDGE_FLAPS0_RIGHT_PERCENT,
	XML_LEADING_EDGE_FLAPS1_RIGHT_PERCENT,
	XML_TRAILING_EDGE_FLAPS0_LEFT_ANGLE,
	XML_TRAILING_EDGE_FLAPS1_LEFT_ANGLE,
	XML_TRAILING_EDGE_FLAPS0_RIGHT_ANGLE,
	XML_TRAILING_EDGE_FLAPS1_RIGHT_ANGLE,
	XML_LEADING_EDGE_FLAPS0_LEFT_ANGLE,
	XML_LEADING_EDGE_FLAPS1_LEFT_ANGLE,
	XML_LEADING_EDGE_FLAPS0_RIGHT_ANGLE,
	XML_LEADING_EDGE_FLAPS1_RIGHT_ANGLE,
	XML_ELEVON1_DEFLECTION,
	XML_ELEVON2_DEFLECTION,
	XML_ELEVON3_DEFLECTION,
	XML_ELEVON4_DEFLECTION,
	XML_ELEVON5_DEFLECTION,
	XML_ELEVON6_DEFLECTION,
	XML_ELEVON7_DEFLECTION,
	XML_ELEVON8_DEFLECTION,
	XML_PROP1_RPM,
	XML_PROP2_RPM,
	XML_PROP3_RPM,
	XML_PROP4_RPM,
	XML_PROP1_MAX_RPM_PERCENT,
	XML_PROP2_MAX_RPM_PERCENT,
	XML_PROP3_MAX_RPM_PERCENT,
	XML_PROP4_MAX_RPM_PERCENT,
	XML_PROP1_THRUST,
	XML_PROP2_THRUST,
	XML_PROP3_THRUST,
	XML_PROP4_THRUST,
	XML_PROP1_BETA,
	XML_PROP2_BETA,
	XML_PROP3_BETA,
	XML_PROP4_BETA,
	XML_PROP1_FEATHERING_INHIBIT,
	XML_PROP2_FEATHERING_INHIBIT,
	XML_PROP3_FEATHERING_INHIBIT,
	XML_PROP4_FEATHERING_INHIBIT,
	XML_PROP1_FEATHERED,
	XML_PROP2_FEATHERED,
	XML_PROP3_FEATHERED,
	XML_PROP4_FEATHERED,
	XML_PROP1_SYNC_DELTA_LEVER,
	XML_PROP2_SYNC_DELTA_LEVER,
	XML_PROP3_SYNC_DELTA_LEVER,
	XML_PROP4_SYNC_DELTA_LEVER,
	XML_PROP1_AUTO_FEATHER_ARMED,
	XML_PROP2_AUTO_FEATHER_ARMED,
	XML_PROP3_AUTO_FEATHER_ARMED,
	XML_PROP4_AUTO_FEATHER_ARMED,
	XML_ENG1_COMBUSTION,
	XML_ENG2_COMBUSTION,
	XML_ENG3_COMBUSTION,
	XML_ENG4_COMBUSTION,
	XML_OLD_ENG1_STARTER,
	XML_OLD_ENG2_STARTER,
	XML_OLD_ENG3_STARTER,
	XML_OLD_ENG4_STARTER,
	XML_ENG1_N1_RPM,
	XML_ENG2_N1_RPM,
	XML_ENG3_N1_RPM,
	XML_ENG4_N1_RPM,
	XML_ENG1_N2_RPM,
	XML_ENG2_N2_RPM,
	XML_ENG3_N2_RPM,
	XML_ENG4_N2_RPM,
	XML_ENG1_FUEL_FLOW_GPH,
	XML_ENG2_FUEL_FLOW_GPH,
	XML_ENG3_FUEL_FLOW_GPH,
	XML_ENG4_FUEL_FLOW_GPH,
	XML_ENG1_FUEL_FLOW_PPH,
	XML_ENG2_FUEL_FLOW_PPH,
	XML_ENG3_FUEL_FLOW_PPH,
	XML_ENG4_FUEL_FLOW_PPH,
	XML_ENG1_FUEL_FLOW_PPH_SSL,
	XML_ENG2_FUEL_FLOW_PPH_SSL,
	XML_ENG3_FUEL_FLOW_PPH_SSL,
	XML_ENG4_FUEL_FLOW_PPH_SSL,
	XML_ENG1_TORQUE,
	XML_ENG2_TORQUE,
	XML_ENG3_TORQUE,
	XML_ENG4_TORQUE,
	XML_ENG1_ANTI_ICE,
	XML_ENG2_ANTI_ICE,
	XML_ENG3_ANTI_ICE,
	XML_ENG4_ANTI_ICE,
	XML_ENG1_PRESSURE_RATIO,
	XML_ENG2_PRESSURE_RATIO,
	XML_ENG3_PRESSURE_RATIO,
	XML_ENG4_PRESSURE_RATIO,
	XML_ENG1_PRESSURE_RATIO_GES,
	XML_ENG2_PRESSURE_RATIO_GES,
	XML_ENG3_PRESSURE_RATIO_GES,
	XML_ENG4_PRESSURE_RATIO_GES,
	XML_ENG1_EXHAUST_GAS_TEMPERATURE,
	XML_ENG2_EXHAUST_GAS_TEMPERATURE,
	XML_ENG3_EXHAUST_GAS_TEMPERATURE,
	XML_ENG4_EXHAUST_GAS_TEMPERATURE,
	XML_ENG1_EXHAUST_GAS_TEMPERATURE_GES,
	XML_ENG2_EXHAUST_GAS_TEMPERATURE_GES,
	XML_ENG3_EXHAUST_GAS_TEMPERATURE_GES,
	XML_ENG4_EXHAUST_GAS_TEMPERATURE_GES,
	XML_ENG1_CYLINDER_HEAD_TEMPERATURE,
	XML_ENG2_CYLINDER_HEAD_TEMPERATURE,
	XML_ENG3_CYLINDER_HEAD_TEMPERATURE,
	XML_ENG4_CYLINDER_HEAD_TEMPERATURE,
	XML_ENG1_OIL_TEMPERATURE,
	XML_ENG2_OIL_TEMPERATURE,
	XML_ENG3_OIL_TEMPERATURE,
	XML_ENG4_OIL_TEMPERATURE,
	XML_ENG1_OIL_PRESSURE,
	XML_ENG2_OIL_PRESSURE,
	XML_ENG3_OIL_PRESSURE,
	XML_ENG4_OIL_PRESSURE,
	XML_ENG1_OIL_QUANTITY,
	XML_ENG2_OIL_QUANTITY,
	XML_ENG3_OIL_QUANTITY,
	XML_ENG4_OIL_QUANTITY,
	XML_ENG1_HYDRAULIC_PRESSURE,
	XML_ENG2_HYDRAULIC_PRESSURE,
	XML_ENG3_HYDRAULIC_PRESSURE,
	XML_ENG4_HYDRAULIC_PRESSURE,
	XML_ENG1_HYDRAULIC_QUANTITY,
	XML_ENG2_HYDRAULIC_QUANTITY,
	XML_ENG3_HYDRAULIC_QUANTITY,
	XML_ENG4_HYDRAULIC_QUANTITY,
	XML_ENG1_MANIFOLD_PRESSURE,
	XML_ENG2_MANIFOLD_PRESSURE,
	XML_ENG3_MANIFOLD_PRESSURE,
	XML_ENG4_MANIFOLD_PRESSURE,
	XML_ENG1_VIBRATION,
	XML_ENG2_VIBRATION,
	XML_ENG3_VIBRATION,
	XML_ENG4_VIBRATION,
	XML_ENG1_RPM_SCALER,
	XML_ENG2_RPM_SCALER,
	XML_ENG3_RPM_SCALER,
	XML_ENG4_RPM_SCALER,
	XML_ENG1_TURBINE_TEMPERATURE,
	XML_ENG2_TURBINE_TEMPERATURE,
	XML_ENG3_TURBINE_TEMPERATURE,
	XML_ENG4_TURBINE_TEMPERATURE,
	XML_ENG1_TORQUE_PERCENT,
	XML_ENG2_TORQUE_PERCENT,
	XML_ENG3_TORQUE_PERCENT,
	XML_ENG4_TORQUE_PERCENT,
	XML_ENG1_FUEL_PRESSURE,
	XML_ENG2_FUEL_PRESSURE,
	XML_ENG3_FUEL_PRESSURE,
	XML_ENG4_FUEL_PRESSURE,
	XML_ENG1_ELECTRICAL_LOAD,
	XML_ENG2_ELECTRICAL_LOAD,
	XML_ENG3_ELECTRICAL_LOAD,
	XML_ENG4_ELECTRICAL_LOAD,
	XML_ENG1_TRANSMISSION_PRESSURE,
	XML_ENG2_TRANSMISSION_PRESSURE,
	XML_ENG3_TRANSMISSION_PRESSURE,
	XML_ENG4_TRANSMISSION_PRESSURE,
	XML_ENG1_TRANSMISSION_TEMPERATURE,
	XML_ENG2_TRANSMISSION_TEMPERATURE,
	XML_ENG3_TRANSMISSION_TEMPERATURE,
	XML_ENG4_TRANSMISSION_TEMPERATURE,
	XML_ENG1_ROTOR_RPM,
	XML_ENG2_ROTOR_RPM,
	XML_ENG3_ROTOR_RPM,
	XML_ENG4_ROTOR_RPM,
	XML_ENG1_FUEL_FLOW_BUG_POSITION,
	XML_ENG2_FUEL_FLOW_BUG_POSITION,
	XML_ENG3_FUEL_FLOW_BUG_POSITION,
	XML_ENG4_FUEL_FLOW_BUG_POSITION,
	XML_ENG1_MAX_RPM,
	XML_ENG2_MAX_RPM,
	XML_ENG3_MAX_RPM,
	XML_ENG4_MAX_RPM,
	XML_ENG1_ON_FIRE,
	XML_ENG2_ON_FIRE,
	XML_ENG3_ON_FIRE,
	XML_ENG4_ON_FIRE,
	XML_GENERAL_ENG1_COMBUSTION,
	XML_GENERAL_ENG2_COMBUSTION,
	XML_GENERAL_ENG3_COMBUSTION,
	XML_GENERAL_ENG4_COMBUSTION,
	XML_GENERAL_ENG1_MASTER_ALTERNATOR,
	XML_GENERAL_ENG2_MASTER_ALTERNATOR,
	XML_GENERAL_ENG3_MASTER_ALTERNATOR,
	XML_GENERAL_ENG4_MASTER_ALTERNATOR,
	XML_GENERAL_ENG1_FUEL_PUMP_SWITCH,
	XML_GENERAL_ENG2_FUEL_PUMP_SWITCH,
	XML_GENERAL_ENG3_FUEL_PUMP_SWITCH,
	XML_GENERAL_ENG4_FUEL_PUMP_SWITCH,
	XML_GENERAL_ENG1_FUEL_PUMP_ON,
	XML_GENERAL_ENG2_FUEL_PUMP_ON,
	XML_GENERAL_ENG3_FUEL_PUMP_ON,
	XML_GENERAL_ENG4_FUEL_PUMP_ON,
	XML_GENERAL_ENG1_RPM,
	XML_GENERAL_ENG2_RPM,
	XML_GENERAL_ENG3_RPM,
	XML_GENERAL_ENG4_RPM,
	XML_GENERAL_ENG1_THROTTLE_LEVER_POSITION,
	XML_GENERAL_ENG2_THROTTLE_LEVER_POSITION,
	XML_GENERAL_ENG3_THROTTLE_LEVER_POSITION,
	XML_GENERAL_ENG4_THROTTLE_LEVER_POSITION,
	XML_GENERAL_ENG1_MIXTURE_LEVER_POSITION,
	XML_GENERAL_ENG2_MIXTURE_LEVER_POSITION,
	XML_GENERAL_ENG3_MIXTURE_LEVER_POSITION,
	XML_GENERAL_ENG4_MIXTURE_LEVER_POSITION,
	XML_GENERAL_ENG1_PROPELLER_LEVER_POSITION,
	XML_GENERAL_ENG2_PROPELLER_LEVER_POSITION,
	XML_GENERAL_ENG3_PROPELLER_LEVER_POSITION,
	XML_GENERAL_ENG4_PROPELLER_LEVER_POSITION,
	XML_GENERAL_ENG1_STARTER,
	XML_GENERAL_ENG2_STARTER,
	XML_GENERAL_ENG3_STARTER,
	XML_GENERAL_ENG4_STARTER,
	XML_GENERAL_ENG1_EXHAUST_GAS_TEMPERATURE,
	XML_GENERAL_ENG2_EXHAUST_GAS_TEMPERATURE,
	XML_GENERAL_ENG3_EXHAUST_GAS_TEMPERATURE,
	XML_GENERAL_ENG4_EXHAUST_GAS_TEMPERATURE,
	XML_GENERAL_ENG1_OIL_PRESSURE,
	XML_GENERAL_ENG2_OIL_PRESSURE,
	XML_GENERAL_ENG3_OIL_PRESSURE,
	XML_GENERAL_ENG4_OIL_PRESSURE,
	XML_GENERAL_ENG1_OIL_LEAKED_PERCENT,
	XML_GENERAL_ENG2_OIL_LEAKED_PERCENT,
	XML_GENERAL_ENG3_OIL_LEAKED_PERCENT,
	XML_GENERAL_ENG4_OIL_LEAKED_PERCENT,
	XML_GENERAL_ENG1_COMBUSTION_SOUND_PERCENT,
	XML_GENERAL_ENG2_COMBUSTION_SOUND_PERCENT,
	XML_GENERAL_ENG3_COMBUSTION_SOUND_PERCENT,
	XML_GENERAL_ENG4_COMBUSTION_SOUND_PERCENT,
	XML_GENERAL_ENG1_DAMAGE_PERCENT,
	XML_GENERAL_ENG2_DAMAGE_PERCENT,
	XML_GENERAL_ENG3_DAMAGE_PERCENT,
	XML_GENERAL_ENG4_DAMAGE_PERCENT,
	XML_GENERAL_ENG1_OIL_TEMPERATURE,
	XML_GENERAL_ENG2_OIL_TEMPERATURE,
	XML_GENERAL_ENG3_OIL_TEMPERATURE,
	XML_GENERAL_ENG4_OIL_TEMPERATURE,
	XML_GENERAL_ENG1_FAILED,
	XML_GENERAL_ENG2_FAILED,
	XML_GENERAL_ENG3_FAILED,
	XML_GENERAL_ENG4_FAILED,
	XML_GENERAL_ENG1_GENERATOR_SWITCH,
	XML_GENERAL_ENG2_GENERATOR_SWITCH,
	XML_GENERAL_ENG3_GENERATOR_SWITCH,
	XML_GENERAL_ENG4_GENERATOR_SWITCH,
	XML_GENERAL_ENG1_GENERATOR_ACTIVE,
	XML_GENERAL_ENG2_GENERATOR_ACTIVE,
	XML_GENERAL_ENG3_GENERATOR_ACTIVE,
	XML_GENERAL_ENG4_GENERATOR_ACTIVE,
	XML_GENERAL_ENG1_ANTI_ICE_POSITION,
	XML_GENERAL_ENG2_ANTI_ICE_POSITION,
	XML_GENERAL_ENG3_ANTI_ICE_POSITION,
	XML_GENERAL_ENG4_ANTI_ICE_POSITION,
	XML_GENERAL_ENG1_FUEL_VALVE,
	XML_GENERAL_ENG2_FUEL_VALVE,
	XML_GENERAL_ENG3_FUEL_VALVE,
	XML_GENERAL_ENG4_FUEL_VALVE,
	XML_GENERAL_ENG1_FUEL_PRESSURE,
	XML_GENERAL_ENG2_FUEL_PRESSURE,
	XML_GENERAL_ENG3_FUEL_PRESSURE,
	XML_GENERAL_ENG4_FUEL_PRESSURE,
	XML_RECIP_ENG1_COWL_FLAP_POSITION,
	XML_RECIP_ENG2_COWL_FLAP_POSITION,
	XML_RECIP_ENG3_COWL_FLAP_POSITION,
	XML_RECIP_ENG4_COWL_FLAP_POSITION,
	XML_RECIP_ENG1_PRIMER,
	XML_RECIP_ENG2_PRIMER,
	XML_RECIP_ENG3_PRIMER,
	XML_RECIP_ENG4_PRIMER,
	XML_RECIP_ENG1_MANIFOLD_PRESSURE,
	XML_RECIP_ENG2_MANIFOLD_PRESSURE,
	XML_RECIP_ENG3_MANIFOLD_PRESSURE,
	XML_RECIP_ENG4_MANIFOLD_PRESSURE,
	XML_RECIP_ENG1_ALTERNATE_AIR_POSITION,
	XML_RECIP_ENG2_ALTERNATE_AIR_POSITION,
	XML_RECIP_ENG3_ALTERNATE_AIR_POSITION,
	XML_RECIP_ENG4_ALTERNATE_AIR_POSITION,
	XML_RECIP_ENG1_COOLANT_RESERVOIR_PERCENT,
	XML_RECIP_ENG2_COOLANT_RESERVOIR_PERCENT,
	XML_RECIP_ENG3_COOLANT_RESERVOIR_PERCENT,
	XML_RECIP_ENG4_COOLANT_RESERVOIR_PERCENT,
	XML_RECIP_ENG1_LEFT_MAGNETO,
	XML_RECIP_ENG2_LEFT_MAGNETO,
	XML_RECIP_ENG3_LEFT_MAGNETO,
	XML_RECIP_ENG4_LEFT_MAGNETO,
	XML_RECIP_ENG1_RIGHT_MAGNETO,
	XML_RECIP_ENG2_RIGHT_MAGNETO,
	XML_RECIP_ENG3_RIGHT_MAGNETO,
	XML_RECIP_ENG4_RIGHT_MAGNETO,
	XML_RECIP_ENG1_BRAKE_POWER,
	XML_RECIP_ENG2_BRAKE_POWER,
	XML_RECIP_ENG3_BRAKE_POWER,
	XML_RECIP_ENG4_BRAKE_POWER,
	XML_RECIP_ENG1_STARTER_TORQUE,
	XML_RECIP_ENG2_STARTER_TORQUE,
	XML_RECIP_ENG3_STARTER_TORQUE,
	XML_RECIP_ENG4_STARTER_TORQUE,
	XML_RECIP_ENG1_TURBOCHARGER_FAILED,
	XML_RECIP_ENG2_TURBOCHARGER_FAILED,
	XML_RECIP_ENG3_TURBOCHARGER_FAILED,
	XML_RECIP_ENG4_TURBOCHARGER_FAILED,
	XML_RECIP_ENG1_EMERGENCY_BOOST_ACTIVE,
	XML_RECIP_ENG2_EMERGENCY_BOOST_ACTIVE,
	XML_RECIP_ENG3_EMERGENCY_BOOST_ACTIVE,
	XML_RECIP_ENG4_EMERGENCY_BOOST_ACTIVE,
	XML_RECIP_ENG1_EMERGENCY_BOOST_ELAPSED_TIME,
	XML_RECIP_ENG2_EMERGENCY_BOOST_ELAPSED_TIME,
	XML_RECIP_ENG3_EMERGENCY_BOOST_ELAPSED_TIME,
	XML_RECIP_ENG4_EMERGENCY_BOOST_ELAPSED_TIME,
	XML_RECIP_ENG1_WASTEGATE_POSITION,
	XML_RECIP_ENG2_WASTEGATE_POSITION,
	XML_RECIP_ENG3_WASTEGATE_POSITION,
	XML_RECIP_ENG4_WASTEGATE_POSITION,
	XML_RECIP_ENG1_TURBINE_INLET_TEMPERATURE,
	XML_RECIP_ENG2_TURBINE_INLET_TEMPERATURE,
	XML_RECIP_ENG3_TURBINE_INLET_TEMPERATURE,
	XML_RECIP_ENG4_TURBINE_INLET_TEMPERATURE,
	XML_RECIP_ENG1_CYLINDER_HEAD_TEMPERATURE,
	XML_RECIP_ENG2_CYLINDER_HEAD_TEMPERATURE,
	XML_RECIP_ENG3_CYLINDER_HEAD_TEMPERATURE,
	XML_RECIP_ENG4_CYLINDER_HEAD_TEMPERATURE,
	XML_RECIP_ENG1_RADIATOR_TEMPERATURE,
	XML_RECIP_ENG2_RADIATOR_TEMPERATURE,
	XML_RECIP_ENG3_RADIATOR_TEMPERATURE,
	XML_RECIP_ENG4_RADIATOR_TEMPERATURE,
	XML_RECIP_ENG1_FUEL_AVAILABLE,
	XML_RECIP_ENG2_FUEL_AVAILABLE,
	XML_RECIP_ENG3_FUEL_AVAILABLE,
	XML_RECIP_ENG4_FUEL_AVAILABLE,
	XML_RECIP_ENG1_FUEL_FLOW,
	XML_RECIP_ENG2_FUEL_FLOW,
	XML_RECIP_ENG3_FUEL_FLOW,
	XML_RECIP_ENG4_FUEL_FLOW,
	XML_RECIP_ENG1_FUEL_TANK_SELECTOR,
	XML_RECIP_ENG2_FUEL_TANK_SELECTOR,
	XML_RECIP_ENG3_FUEL_TANK_SELECTOR,
	XML_RECIP_ENG4_FUEL_TANK_SELECTOR,
	XML_RECIP_ENG1_FUEL_TANKS_USED,
	XML_RECIP_ENG2_FUEL_TANKS_USED,
	XML_RECIP_ENG3_FUEL_TANKS_USED,
	XML_RECIP_ENG4_FUEL_TANKS_USED,
	XML_RECIP_ENG1_FUEL_NUMBER_TANKS_USED,
	XML_RECIP_ENG2_FUEL_NUMBER_TANKS_USED,
	XML_RECIP_ENG3_FUEL_NUMBER_TANKS_USED,
	XML_RECIP_ENG4_FUEL_NUMBER_TANKS_USED,
	XML_TURB_ENG1_N1,
	XML_TURB_ENG2_N1,
	XML_TURB_ENG3_N1,
	XML_TURB_ENG4_N1,
	XML_TURB_ENG1_N2,
	XML_TURB_ENG2_N2,
	XML_TURB_ENG3_N2,
	XML_TURB_ENG4_N2,
	XML_TURB_ENG1_CORRECTED_N1,
	XML_TURB_ENG2_CORRECTED_N1,
	XML_TURB_ENG3_CORRECTED_N1,
	XML_TURB_ENG4_CORRECTED_N1,
	XML_TURB_ENG1_CORRECTED_N2,
	XML_TURB_ENG2_CORRECTED_N2,
	XML_TURB_ENG3_CORRECTED_N2,
	XML_TURB_ENG4_CORRECTED_N2,
	XML_TURB_ENG1_CORRECTED_FF,
	XML_TURB_ENG2_CORRECTED_FF,
	XML_TURB_ENG3_CORRECTED_FF,
	XML_TURB_ENG4_CORRECTED_FF,
	XML_TURB_ENG1_MAX_TORQUE_PERCENT,
	XML_TURB_ENG2_MAX_TORQUE_PERCENT,
	XML_TURB_ENG3_MAX_TORQUE_PERCENT,
	XML_TURB_ENG4_MAX_TORQUE_PERCENT,
	XML_TURB_ENG1_PRESSURE_RATIO,
	XML_TURB_ENG2_PRESSURE_RATIO,
	XML_TURB_ENG3_PRESSURE_RATIO,
	XML_TURB_ENG4_PRESSURE_RATIO,
	XML_TURB_ENG1_ITT,
	XML_TURB_ENG2_ITT,
	XML_TURB_ENG3_ITT,
	XML_TURB_ENG4_ITT,
	XML_TURB_ENG1_AFTERBURNER,
	XML_TURB_ENG2_AFTERBURNER,
	XML_TURB_ENG3_AFTERBURNER,
	XML_TURB_ENG4_AFTERBURNER,
	XML_TURB_ENG1_JET_THRUST,
	XML_TURB_ENG2_JET_THRUST,
	XML_TURB_ENG3_JET_THRUST,
	XML_TURB_ENG4_JET_THRUST,
	XML_TURB_ENG1_BLEED_AIR,
	XML_TURB_ENG2_BLEED_AIR,
	XML_TURB_ENG3_BLEED_AIR,
	XML_TURB_ENG4_BLEED_AIR,
	XML_TURB_ENG1_TANK_SELECTOR,
	XML_TURB_ENG2_TANK_SELECTOR,
	XML_TURB_ENG3_TANK_SELECTOR,
	XML_TURB_ENG4_TANK_SELECTOR,
	XML_TURB_ENG1_TANKS_USED,
	XML_TURB_ENG2_TANKS_USED,
	XML_TURB_ENG3_TANKS_USED,
	XML_TURB_ENG4_TANKS_USED,
	XML_TURB_ENG1_NUM_TANKS_USED,
	XML_TURB_ENG2_NUM_TANKS_USED,
	XML_TURB_ENG3_NUM_TANKS_USED,
	XML_TURB_ENG4_NUM_TANKS_USED,
	XML_TURB_ENG1_FUEL_FLOW_PPH,
	XML_TURB_ENG2_FUEL_FLOW_PPH,
	XML_TURB_ENG3_FUEL_FLOW_PPH,
	XML_TURB_ENG4_FUEL_FLOW_PPH,
	XML_TURB_ENG1_FUEL_AVAILABLE,
	XML_TURB_ENG2_FUEL_AVAILABLE,
	XML_TURB_ENG3_FUEL_AVAILABLE,
	XML_TURB_ENG4_FUEL_AVAILABLE,
	XML_TURB_ENG1_PRIMARY_NOZZLE_PERCENT,
	XML_TURB_ENG2_PRIMARY_NOZZLE_PERCENT,
	XML_TURB_ENG3_PRIMARY_NOZZLE_PERCENT,
	XML_TURB_ENG4_PRIMARY_NOZZLE_PERCENT,
	XML_TURB_ENG1_REVERSE_NOZZLE_PERCENT,
	XML_TURB_ENG2_REVERSE_NOZZLE_PERCENT,
	XML_TURB_ENG3_REVERSE_NOZZLE_PERCENT,
	XML_TURB_ENG4_REVERSE_NOZZLE_PERCENT,
	XML_TURB_ENG1_VIBRATION,
	XML_TURB_ENG2_VIBRATION,
	XML_TURB_ENG3_VIBRATION,
	XML_TURB_ENG4_VIBRATION,
	XML_ENG1_FAILED,
	XML_ENG2_FAILED,
	XML_ENG3_FAILED,
	XML_ENG4_FAILED,
	XML_PARTIAL_PANEL_ADF1,
	XML_PARTIAL_PANEL_COMM1,
	XML_PARTIAL_PANEL_COMM2,
	XML_PARTIAL_PANEL_TRANSPONDER1,
	XML_PARTIAL_PANEL_NAV1,
	XML_PARTIAL_PANEL_NAV2,
	XML_FUEL_TANK_SELECTOR_1,
	XML_FUEL_TANK_SELECTOR_2,
	XML_FUEL_TANK_SELECTOR_3,
	XML_FUEL_TANK_SELECTOR_4,
	XML_NAV1_AVAILABLE,
	XML_NAV2_AVAILABLE,
	XML_ELECTRICAL_GENALT1_BUS_VOLTAGE,
	XML_ELECTRICAL_GENALT2_BUS_VOLTAGE,
	XML_ELECTRICAL_GENALT3_BUS_VOLTAGE,
	XML_ELECTRICAL_GENALT4_BUS_VOLTAGE,
	XML_ELECTRICAL_GENALT1_BUS_AMPS,
	XML_ELECTRICAL_GENALT2_BUS_AMPS,
	XML_ELECTRICAL_GENALT3_BUS_AMPS,
	XML_ELECTRICAL_GENALT4_BUS_AMPS,
	XML_HYDRAULIC1_PRESSURE,
	XML_HYDRAULIC2_PRESSURE,
	XML_HYDRAULIC3_PRESSURE,
	XML_HYDRAULIC4_PRESSURE,
	XML_HYDRAULIC1_RESERVOIR_PERCENT,
	XML_HYDRAULIC2_RESERVOIR_PERCENT,
	XML_HYDRAULIC3_RESERVOIR_PERCENT,
	XML_HYDRAULIC4_RESERVOIR_PERCENT,
	XML_COM1_TRANSMIT,
	XML_COM2_TRANSMIT,
	XML_NAV1_SOUND,
	XML_NAV2_SOUND,
	XML_COM1_ACTIVE_FREQUENCY,
	XML_COM2_ACTIVE_FREQUENCY,
	XML_COM1_STANDBY_FREQUENCY,
	XML_COM2_STANDBY_FREQUENCY,
	XML_COM1_STATUS,
	XML_COM2_STATUS,
	XML_TRANSPONDER1_CODE,
	XML_ADF1_FREQUENCY,
	XML_ADF1_EXT_FREQUENCY,
	XML_ADF1_ACTIVE_FREQUENCY,
	XML_ADF1_STANDBY_FREQUENCY,
	XML_ADF1_LATLONALT,
	XML_ADF1_SIGNAL,
	XML_ADF1_RADIAL,
	XML_ADF1_IDENT,
	XML_ADF1_NAME,
	XML_NAV1_ACTIVE_FREQUENCY,
	XML_NAV2_ACTIVE_FREQUENCY,
	XML_NAV1_STANDBY_FREQUENCY,
	XML_NAV2_STANDBY_FREQUENCY,
	XML_NAV1_SIGNAL,
	XML_NAV2_SIGNAL,
	XML_NAV1_IDENT,
	XML_NAV2_IDENT,
	XML_NAV1_NAME,
	XML_NAV2_NAME,
	XML_NAV1_CODES,
	XML_NAV2_CODES,
	XML_NAV1_HAS_NAV,
	XML_NAV2_HAS_NAV,
	XML_NAV1_HAS_LOCALIZER,
	XML_NAV2_HAS_LOCALIZER,
	XML_NAV1_HAS_DME,
	XML_NAV2_HAS_DME,
	XML_NAV1_HAS_GLIDE_SLOPE,
	XML_NAV2_HAS_GLIDE_SLOPE,
	XML_NAV1_BACK_COURSE_FLAGS,
	XML_NAV2_BACK_COURSE_FLAGS,
	XML_NAV1_MAGVAR,
	XML_NAV2_MAGVAR,
	XML_NAV1_RADIAL,
	XML_NAV2_RADIAL,
	XML_NAV1_RADIAL_ERROR,
	XML_NAV2_RADIAL_ERROR,
	XML_NAV1_LOCALIZER,
	XML_NAV2_LOCALIZER,
	XML_NAV1_GLIDE_SLOPE,
	XML_NAV2_GLIDE_SLOPE,
	XML_NAV1_GLIDE_SLOPE_ERROR,
	XML_NAV2_GLIDE_SLOPE_ERROR,
	XML_NAV1_CDI,
	XML_NAV2_CDI,
	XML_NAV1_GSI,
	XML_NAV2_GSI,
	XML_NAV1_TOFROM,
	XML_NAV2_TOFROM,
	XML_NAV1_GS_FLAG,
	XML_NAV2_GS_FLAG,
	XML_NAV1_OBS,
	XML_NAV2_OBS,
	XML_NAV1_DME,
	XML_NAV2_DME,
	XML_NAV1_DMESPEED,
	XML_NAV2_DMESPEED,
	XML_NAV1_VOR_LATLONALT,
	XML_NAV2_VOR_LATLONALT,
	XML_NAV1_GS_LATLONALT,
	XML_NAV2_GS_LATLONALT,
	XML_NAV1_DME_LATLONALT,
	XML_NAV2_DME_LATLONALT,
	XML_HEADING_INDICATOR_0,
	XML_HEADING_INDICATOR_1,
	XML_HEADING_INDICATOR_2,
	XML_HEADING_INDICATOR_3,
	XML_HEADING_INDICATOR_4,
	GAUGE_XML_TOKEN
} XML_TOKEN;

// Gauge tokens for lookup_var
typedef	enum	GAUGE_TOKEN
{
	MODULE_VAR_NONE = 0,
	TICK18,						//  inc'd at 18hz. used for general purpose timing
	GROUND_ALTITUDE,			//  ground level altitude (1/256 meter/unit)
	CLOCK_HOUR,					//  local clock time, hours {0..23}
	CLOCK_MINUTE,				//  local clock time, minutes {0..59}
	CLOCK_SECOND,				//  local clock time, seconds {0..59}
	ZULU_HOUR,					//  delta time from GMT
	ZULU_MINUTE,				//  delta time from GMT
	ZULU_DAY,					//  GMT day of year (1 - 365/366)
	ZULU_YEAR,					//  GMT year
	PANEL_LIGHTS,				//  TRUE=panel lighting on
	STROBE_LIGHTS,				//  TRUE=strobe lights on
	STROBE_FLASH,				//  TRUE=strobe flash on model & screen
	PITOT_HEAT,					//	TRUE=pitot heat on
	LANDING_LIGHTS,				//  TRUE=landing lights on
	SMOKE_ENABLE,				//  TRUE=smoke system active
	ADF_FREQUENCY,				//  |
	ADF_500_HZ_TUNABLE,			//	|	ADF frequency
	ADF_EXTENDED_FREQUENCY,		//	|
	ADF_IDENTITY,
	ADF_SIGNAL_STRENGTH,
	ADF_MORSE_IDENT,
	ADF_CARD_RADIAL,			//	integer degrees 0-360
	COM_FREQUENCY,				//  BCD COM radio freq
	NAV1_FREQUENCY,				//  BCD NAV1 radio freq
	NAV1_VOR_RADIAL,
	NAV1_MORSE_IDENT,
	NAV2_FREQUENCY,				//  BCD NAV2 radio freq
	NAV2_VOR_RADIAL,
	NAV2_MORSE_IDENT,
	DME1_DISPLAY_TYPE,			//  FALSE=distance readout,  TRUE=speed in kts readout
	DME1_DISTANCE,				//  DME1 distance readout
	DME1_SPEED,					//  DME1 speed readout
	DME1_MORSE_IDENT,
	DME2_DISPLAY_TYPE,			//  FALSE=distance readout,  TRUE=speed in kts readout
	DME2_DISTANCE,				//  DME2 distance readout
	DME2_SPEED,					//  DME2 speed readout
	DME2_MORSE_IDENT,
	TRANSPONDER_CODE,			//  Octal Transponder code {0000 - 7777}
	ADF_NEEDLE,					//	16 bit pseudodegrees
	VOR1_NEEDLE,				// +-127 correspond to +-10 if VOR or to +-2.5 if localiser.
	VOR1_GS_NEEDLE,				// +-120 correspond to +-0.7
	VOR1_BACK_COURSE_FLAGS,		//  Status of VOR1 (see BC_FLAG_ in FS6DEF.H)
	VOR1_TF_FLAG,
	VOR1_GS_FLAG,
	VOR1_OBI,
	VOR1_CODE,
	VOR1_IDENTITY,
	VOR1_MAG_VAR,
	VOR1_SIGNAL_STRENGTH,
	VOR2_NEEDLE,
	VOR2_BACK_COURSE_FLAGS,		//  Status of VOR2 (see BC_FLAG_ in FS6DEF.H)
	VOR2_TF_FLAG,
	VOR2_GS_FLAG,
	VOR2_OBI,
	VOR2_CODE,
	VOR2_IDENTITY,
	VOR2_MAG_VAR,
	VOR2_SIGNAL_STRENGTH,
	VOR2_BEARING_DEGREES,
	AIRCRAFT_ON_GROUND,			//  TRUE=aircraft is on the ground
	AIRSPEED,					//	Airspeed - Indicated or True based on GLOBALP->indicated_aspd
	AIRSPEED_TRUE_CALIBRATE,	//	Degrees rotation of the tas calibration card
	BARBER_POLE_ASPD,			//  Movable Red-line airspeed  {1/128th knot/unit}
	MACH,						//  mach, 64k=3.2 mach (would be better as UIF32)
	VERTICAL_SPEED,				//  Velocity Up, vertical speed {1/256th m/sec}
	MACH_MAX_OPERATE,
	STALL_WARNING,				//  TRUE=5 knots before stall
	OVERSPEED_WARNING,			//  TRUE=overspeed warning
	TURN_COORDINATOR_BALL_POS,	//  turn coordinator ball position {-127..0..127}
	DELTA_HEADING_RATE,
	PLANE_LATITUDE,				//  current position of our aircraft
	PLANE_LONGITUDE,			//  current position of our aircraft
	PLANE_ALTITUDE,				//  current position of our aircraft
	ALT_FROM_BAROMETRIC_PRESSURE,
	KOHLSMAN_SETTING_MB,		//  knob position millibars
	KOHLSMAN_SETTING_HG,		//  knob position inches of hg
	PLANE_PITCH_DEGREES,
	ATTITUDE_INDICATOR_PITCH_DEGREES,
	PLANE_BANK_DEGREES,
	ATTITUDE_INDICATOR_BANK_DEGREES,
	PLANE_HEADING_DEGREES_MAGNETIC,
	MAGNETIC_VAR,				//  magnetic north vs. true north angular error
	WHISKEY_COMPASS_DEGREES,	//	True degrees
	PLANE_HEADING_DEGREES_GYRO,
	GYRO_DRIFT_ERROR,
	PLANE_HEADING_DEGREES_TRUE,
	AIRCRAFT_AUTOPILOT_AVAILABLE,
	AIRCRAFT_FLAPS_AVAILABLE,
	AIRCRAFT_STALL_HORN_AVAILABLE,
	AIRCRAFT_ENGINE_MIXTURE_AVAILABLE,
	AIRCRAFT_CARB_HEAT_AVAILABLE,
	AIRCRAFT_SPOILER_AVAILABLE,
	AIRCRAFT_IS_TAIL_DRAGGER,
	AIRCRAFT_STROBES_AVAILABLE,
	AIRCRAFT_PROP_TYPE_AVAILABLE,	//  PROP_TYPE_FIXED, PROP_TYPE_MANUAL, PROP_TYPE_AUTOMATIC
	AIRCRAFT_TOE_BRAKES_AVAILABLE,
	AIRCRAFT_NAV1_AVAILABLE,
	AIRCRAFT_NAV2_AVAILABLE,
	AIRCRAFT_NAV1_OBS_AVAILABLE,
	AIRCRAFT_NAV2_OBS_AVAILABLE,
	AIRCRAFT_VOR2_GAUGE_AVAILABLE,
	AIRCRAFT_GYRO_DRIFT_AVAILABLE,	// fek: may not be used for bug #2131 but making other changes...build build build
	AUTOPILOT_ACTIVE,			//  autopilot master on/off
	AUTOPILOT_WING_LEVELER,		//  wing leveler on/off
	AUTOPILOT_NAV1_LOCK,		//  nav 1 lock on/off
	AUTOPILOT_HEADING_LOCK,		//  heading lock on/off
	AUTOPILOT_HEADING_LOCK_DIR,	//  heading lock direction
	AUTOPILOT_ALTITUDE_LOCK,	//  altitude lock on/off
	AUTOPILOT_ALTITUDE_LOCK_VAR,//  altitude lock altitude in appropriate units
	AUTOPILOT_ATTITUDE_HOLD,	//  attitude hold
	AUTOPILOT_GLIDESLOPE_HOLD,	//  glideslope hold
	AUTOPILOT_APROACH_HOLD,		//  approach hold
	AUTOPILOT_BACKCOURSE_HOLD,	//  backcourse hold
	AUTOPILOT_YAW_DAMPER,		//  yaw damper
	AUTOPILOT_AIRSPEED_HOLD,	//  airspeed hold
	AUTOPILOT_AIRSPEED_HOLD_VAR,//  airspeed hold var
	AUTOPILOT_MACH_HOLD,		//  airspeed hold
	AUTOPILOT_MACH_HOLD_VAR,	//  airspeed hold var
	AUTOPILOT_VERTICAL_HOLD, 	//  vertical hold
	AUTOPILOT_VERTICAL_HOLD_VAR,//  vertical speed hold var in appropriate units
	AUTOPILOT_ALTITUDE_MANUALLY_TUNABLE,
	AUTOPILOT_HEADING_MANUALLY_TUNABLE,
	AUTOPILOT_AUTO_THROTTLE_ARM,
	AUTOPILOT_TAKEOFF_POWER_ACTIVE,
	ENGINE_RPM_HOLD,
	ENGINE_CONTROL_SELECT,				//  which engine is being controlled
	ENGINE1,
	ENGINE1_THROTTLE_LEVER_POS,	//	throttle position			(16k = 100% throttle position)
	ENGINE1_PROPELLER_LEVER_POS,	//	propeller lever position	(16k = 100% prop setting)
	ENGINE1_MIXTURE_LEVER_POS,		//	mixture position			(16k = 100% mixture position)
	ENGINE1_COMBUSTION,			//	combustion flag				(combustion = TRUE)
	ENGINE1_STARTER_SWITCH_POS,	//	starter switch position
	ENGINE1_MAGNETO_LEFT,			//	left magneto status			(activated = 1)
	ENGINE1_MAGNETO_RIGHT,			//	right magneto status		(activated = 1)
	ENGINE1_N1_RPM,				//	gas producer (RPM)			(16k = 100% RPM)
	ENGINE1_N2_RPM,				//	power (RPM)					(16k = 100% RPM)
	ENGINE1_FF_GPH,
	ENGINE1_FF_PPH,				//	fuel flow PPH
	ENGINE1_FF_PPH_SSL,			//	fuel flow (PPH)				(16k = 100%, Standard sea level conditions)
	ENGINE1_TORQUE,				//	torque produced ( FT*LBS )
	ENGINE1_ANTI_ICE_SWITCH,		//	anti ice switch
	ENGINE1_PRESSURE_RATIO,		//	engine pressure ratio		(65k = 6.4)
	ENGINE1_PRESSURE_BUG_POS,		//	epr governed engine setting (16k = 100% epr setting)
	ENGINE1_EGT,					//	exhaust gas temp (degC)		(16k = 860 deg)
	ENGINE1_EGT_BUG_POS,			//	egt governed engine setting (16k = 100% egt setting)
	ENGINE1_CHT,					//	cylinder head temperature
	ENGINE1_OIL_TEMPERATURE,		//	oil temperature (degC)		(16k = 140 deg)
	ENGINE1_OIL_PRESSURE,			//	oil pressure (PSI)			(16k = 55 PSI)
	ENGINE1_OIL_QUANTITY,			//	oil quantity				(16k = 100%)
	ENGINE1_HYDRAULIC_PRESSURE,	//	hydraulic pressure (PSI)	(16k = 4 psi)
	ENGINE1_HYDRAULIC_QUANTITY,	//	hydraulic quantity			(16k = 100%)
	ENGINE1_MANIFOLD_PRESSURE,		//	manifold pressure			(65k = 64)
	ENGINE1_ENGINE_VIBRATION,		//	oil quantity				(16k = 5)
	ENGINE1_RPM_SCALER,			//	*16384 gives actual prop rpm in dx (= 65535 for jets)
	ENGINE1_TURBINE_TEMPERATURE,	//	(DegC * 16384)
	ENGINE1_TORQUE_PERCENT,			//	(FT/LBS * 16384)
	ENGINE1_FUEL_PRESSURE,				//	(PSI * 16384)
	ENGINE1_ELECTRICAL_LOAD,			//	(Max Load * 16384)
	ENGINE1_TRANSMISSION_PRESSURE,		//	(PSI * 16384)
	ENGINE1_TRANSMISSION_TEMPERATURE,	//	(DegC * 16384)
	ENGINE1_ROTOR_RPM,					//	(Max 8 16384)
	ENGINE2,
	ENGINE2_THROTTLE_LEVER_POS,	//	throttle position (0-16384=>0-100%throttle position)
	ENGINE2_PROPELLER_LEVER_POS,//	propeller lever position (0-16384=>0-100%prop setting)
	ENGINE2_MIXTURE_LEVER_POS,	//	mixture position (0-16384=>0-100%mixture position)
	ENGINE2_COMBUSTION,			//	combustion flag (combustion = TRUE)
	ENGINE2_STARTER_SWITCH_POS,	//	starter switch position
	ENGINE2_MAGNETO_LEFT,		//	left magneto status (activated = 1)
	ENGINE2_MAGNETO_RIGHT,		//	right magneto status (activated = 1)
	ENGINE2_N1_RPM,				//	gas producer RPM (0-16384=>0-100%RPM)
	ENGINE2_N2_RPM,				//	power RPM (0-16384=>0-100%RPM)
	ENGINE2_FF_GPH,
	ENGINE2_FF_PPH,				//	PPH
	ENGINE2_FF_PPH_SSL,			//	fuel flow (0-16384=>0-100%)PPH, Standard sea level conditions
	ENGINE2_TORQUE,				//	torque produced ( FT*LBS )
	ENGINE2_ANTI_ICE_SWITCH,	//	anti ice switch
	ENGINE2_PRESSURE_RATIO,		//	engine pressure ratio (0-65536=>0-6.4)
	ENGINE2_PRESSURE_BUG_POS,	//	epr governed engine setting (0-16384=>0-100%epr setting)
	ENGINE2_EGT,				//	exhaust gas temperature (degC)
	ENGINE2_EGT_BUG_POS,		//	egt governed engine setting (0-16384=>0-100%egt setting)
	ENGINE2_CHT,				//	cylinder head temperature
	ENGINE2_OIL_TEMPERATURE,	//	oil temperature (degC)
	ENGINE2_OIL_PRESSURE,		//	oil pressure (PSI)
	ENGINE2_OIL_QUANTITY,		//	oil quantity (0-16384 => 0-100%)
	ENGINE2_HYDRAULIC_PRESSURE,	//	hydraulic pressure (0-16384 => 0-4 psi)
	ENGINE2_HYDRAULIC_QUANTITY,	//	hydraulic quantity (0-16384 => 0-100%)
	ENGINE2_MANIFOLD_PRESSURE,	//	manifold pressure (0-65536=>0-64)
	ENGINE2_ENGINE_VIBRATION,	//	oil quantity (0-16384 => 0-5)
	ENGINE2_RPM_SCALER,			//	*16384 gives actual prop rpm in dx (= 65535 for jets)
	ENGINE2_TURBINE_TEMPERATURE,		//	(DegC * 16384)
	ENGINE2_TORQUE_PERCENT,				//	(FT/LBS * 16384)
	ENGINE2_FUEL_PRESSURE,				//	(PSI * 16384)
	ENGINE2_ELECTRICAL_LOAD,			//	(Max Load * 16384)
	ENGINE2_TRANSMISSION_PRESSURE,		//	(PSI * 16384)
	ENGINE2_TRANSMISSION_TEMPERATURE,	//	(DegC * 16384)
	ENGINE2_ROTOR_RPM,					//	(Max 8 16384)
	ENGINE3,
	ENGINE3_THROTTLE_LEVER_POS,	//	throttle position (0-16384=>0-100%throttle position)
	ENGINE3_PROPELLER_LEVER_POS,//	propeller lever position (0-16384=>0-100%prop setting)
	ENGINE3_MIXTURE_LEVER_POS,	//	mixture position (0-16384=>0-100%mixture position)
	ENGINE3_COMBUSTION,			//	combustion flag (combustion = TRUE)
	ENGINE3_STARTER_SWITCH_POS,	//	starter switch position
	ENGINE3_MAGNETO_LEFT,		//	left magneto status (activated = 1)
	ENGINE3_MAGNETO_RIGHT,		//	right magneto status (activated = 1)
	ENGINE3_N1_RPM,				//	gas producer RPM (0-16384=>0-100%RPM)
	ENGINE3_N2_RPM,				//	power RPM (0-16384=>0-100%RPM)
	ENGINE3_FF_GPH,
	ENGINE3_FF_PPH,				//	fuel flow PPH
	ENGINE3_FF_PPH_SSL,			//	fuel flow (0-16384=>0-100%)PPH, Standard sea level conditions
	ENGINE3_TORQUE,				//	torque produced ( FT*LBS )
	ENGINE3_ANTI_ICE_SWITCH,	//	anti ice switch
	ENGINE3_PRESSURE_RATIO,		//	engine pressure ratio (0-65536=>0-6.4)
	ENGINE3_PRESSURE_BUG_POS,	//	epr governed engine setting (0-16384=>0-100%epr setting)
	ENGINE3_EGT,				//	exhaust gas temperature (degC)
	ENGINE3_EGT_BUG_POS,		//	egt governed engine setting (0-16384=>0-100%egt setting)
	ENGINE3_CHT,				//	cylinder head temperature
	ENGINE3_OIL_TEMPERATURE,	//	oil temperature (degC)
	ENGINE3_OIL_PRESSURE,		//	oil pressure (PSI)
	ENGINE3_OIL_QUANTITY,		//	oil quantity (0-16384 => 0-100%)
	ENGINE3_HYDRAULIC_PRESSURE,	//	hydraulic pressure (0-16384 => 0-4 psi)
	ENGINE3_HYDRAULIC_QUANTITY,	//	hydraulic quantity (0-16384 => 0-100%)
	ENGINE3_MANIFOLD_PRESSURE,	//	manifold pressure (0-65536=>0-64)
	ENGINE3_ENGINE_VIBRATION,	//	oil quantity (0-16384 => 0-5)
	ENGINE3_RPM_SCALER,			//	*16384 gives actual prop rpm in dx (= 65535 for jets)
	ENGINE3_TURBINE_TEMPERATURE,		//	(DegC * 16384)
	ENGINE3_TORQUE_PERCENT,				//	(FT/LBS * 16384)
	ENGINE3_FUEL_PRESSURE,				//	(PSI * 16384)
	ENGINE3_ELECTRICAL_LOAD,			//	(Max Load * 16384)
	ENGINE3_TRANSMISSION_PRESSURE,		//	(PSI * 16384)
	ENGINE3_TRANSMISSION_TEMPERATURE,	//	(DegC * 16384)
	ENGINE3_ROTOR_RPM,					//	(Max 8 16384)
	ENGINE4,
	ENGINE4_THROTTLE_LEVER_POS,	//	throttle position (0-16384=>0-100%throttle position)
	ENGINE4_PROPELLER_LEVER_POS,//	propeller lever position (0-16384=>0-100%prop setting)
	ENGINE4_MIXTURE_LEVER_POS,	//	mixture position (0-16384=>0-100%mixture position)
	ENGINE4_COMBUSTION,			//	combustion flag (combustion = TRUE)
	ENGINE4_STARTER_SWITCH_POS,	//	starter switch position
	ENGINE4_MAGNETO_LEFT,		//	left magneto status (activated = 1)
	ENGINE4_MAGNETO_RIGHT,		//	right magneto status (activated = 1)
	ENGINE4_N1_RPM,				//	gas producer RPM (0-16384=>0-100%RPM)
	ENGINE4_N2_RPM,				//	power RPM (0-16384=>0-100%RPM)
	ENGINE4_FF_GPH,
	ENGINE4_FF_PPH,				//	fuel flow PPH
	ENGINE4_FF_PPH_SSL,			//	fuel flow (0-16384=>0-100%)PPH, Standard sea level conditions
	ENGINE4_TORQUE,				//	torque produced ( FT*LBS )
	ENGINE4_ANTI_ICE_SWITCH,	//	anti ice switch
	ENGINE4_PRESSURE_RATIO,		//	engine pressure ratio (0-65536=>0-6.4)
	ENGINE4_PRESSURE_BUG_POS,	//	epr governed engine setting (0-16384=>0-100%epr setting)
	ENGINE4_EGT,				//	exhaust gas temperature (degC)
	ENGINE4_EGT_BUG_POS,		//	egt governed engine setting (0-16384=>0-100%egt setting)
	ENGINE4_CHT,				//	cylinder head temperature
	ENGINE4_OIL_TEMPERATURE,	//	oil temperature (degC)
	ENGINE4_OIL_PRESSURE,		//	oil pressure (PSI)
	ENGINE4_OIL_QUANTITY,		//	oil quantity (0-16384 => 0-100%)
	ENGINE4_HYDRAULIC_PRESSURE,	//	hydraulic pressure (0-16384 => 0-4 psi)
	ENGINE4_HYDRAULIC_QUANTITY,	//	hydraulic quantity (0-16384 => 0-100%)
	ENGINE4_MANIFOLD_PRESSURE,	//	manifold pressure (0-65536=>0-64)
	ENGINE4_ENGINE_VIBRATION,	//	oil quantity (0-16384 => 0-5)
	ENGINE4_RPM_SCALER,			//	*16384 gives actual prop rpm in dx (= 65535 for jets)
	ENGINE4_TURBINE_TEMPERATURE,		//	(DegC * 16384)
	ENGINE4_TORQUE_PERCENT,				//	(FT/LBS * 16384)
	ENGINE4_FUEL_PRESSURE,				//	(PSI * 16384)
	ENGINE4_ELECTRICAL_LOAD,			//	(Max Load * 16384)
	ENGINE4_TRANSMISSION_PRESSURE,		//	(PSI * 16384)
	ENGINE4_TRANSMISSION_TEMPERATURE,	//	(DegC * 16384)
	ENGINE4_ROTOR_RPM,					//	(Max 8 16384)
	NUMBER_OF_ENGINES,			//  1=single 2=twin ...
	PROP_ADVANCE_SELECTION,		//  0=fixed 1=optimal 2=manual
	THROTTLE_LOWER_LIMIT,		//  set by sim for thrust reversers
	OIL_QUANTITY_TOTAL,			//  0..7fff (8 qt.)
	SYSTEMS_AVAILABLE,
	INSTRUMENTS_AVAILABLE,
	PP_ADF,						//  partial panel variables
	PP_AIR,
	PP_ALTIM,
	PP_ATTITUDE,
	PP_COM,
	PP_COMPASS,
	PP_ELECT,					// there is no electricity in panels circuit
	PP_ENGINE,
	PP_FUEL_IND,
	PP_HEADING,
	PP_VERT_VEL,
	PP_XPNDR,
	PP_NAV,
	PP_PITOT,
	PP_TURN_COORD,
	PP_VACUUM,
	FUEL_TANK_CENTER_LEVEL,
	FUEL_TANK_CENTER_CAPACITY,
	FUEL_TANK_LEFT_MAIN_LEVEL,
	FUEL_TANK_LEFT_MAIN_CAPACITY,
	FUEL_TANK_LEFT_AUX_LEVEL,
	FUEL_TANK_LEFT_AUX_CAPACITY,
	FUEL_TANK_LEFT_TIP_LEVEL,
	FUEL_TANK_LEFT_TIP_CAPACITY,
	FUEL_TANK_RIGHT_MAIN_LEVEL,
	FUEL_TANK_RIGHT_MAIN_CAPACITY,
	FUEL_TANK_RIGHT_AUX_LEVEL,
	FUEL_TANK_RIGHT_AUX_CAPACITY,
	FUEL_TANK_RIGHT_TIP_LEVEL,
	FUEL_TANK_RIGHT_TIP_CAPACITY,
	FUEL_QUANTITY_RIGHT,		//	Total Gallons
	FUEL_QUANTITY_LEFT,			//	Total Gallons
	FUEL_QUANTITY_CENTER,		//	Total Gallons
	FUEL_WEGHT_PER_GALLON,		//  in pounds I.F  (6 lbs/gal = 1536)
	FUEL_TANK_SELECTOR,			//  see FUEL_TANK_SELECTOR_ enum values
	CROSS_FEED_SELECTOR,		//	OFF, LEFT_TO_RIGHT, or RIGHT_TO_LEFT
	OBSOLETE_YOKE_POS_Y,		// use ELEVATOR_DEFLECTION
	OBSOLETE_YOKE_IND_Y,		// use ELEVATOR_DEFLECTION
	OBSOLETE_YOKE_POS_X,		// use AILERON_DEFLECTION
	OBSOLETE_YOKE_IND_X,		// use AILERON_DEFLECTION
	OBSOLETE_AILERON_POS,		// use AILERON_DEFLECTION
	OBSOLETE_RUDDER_PEDAL_POS,	// use RUDDER_DEFLECTION
	OBSOLETE_RUDDER_PEDAL_IND,	// use RUDDER_DEFLECTION
	OBSOLETE_RUDDER_POS,		// use RUDDER_DEFLECTION
	OBSOLETE_ELEVATOR_POS,		// use ELEVATOR_DEFLECTION
	OBSOLETE_ELEVATOR_TRIM_POS,	// use ELEVATOR_TRIM
	OBSOLETE_ELEVATOR_TRIM_IND,	// use ELEVATOR_TRIM
	BRAKES_LEFT_POS,			//  0=off 32k=full brakes
	BRAKES_RIGHT_POS,			//  0=off 32k=full brakes
	BRAKE_IND,					//  0=off 16k=full brakes
	PARKING_BRAKE_POS,			//  0=off 32k=full	parking brakes
	SPOILERS_ARMED,
	SPOILERS_HANDLE_POS,
	SPOILERS_POS_LEFT,
	SPOILERS_POS_RIGHT,
	FLAPS_HANDLE_POS,
	FLAPS_POS_LEFT,
	FLAPS_POS_RIGHT,
	GEAR_HANDLE_POS,
	GEAR_POS_NOSE,
	GEAR_POS_LEFT,
	GEAR_POS_RIGHT,
	DISPLAY_UNITS,				//  english vs. metric system
	SIM_SPEED,					//  time dilation factor for sim equations
	ZOOM_FACTOR,				//	zoom value of current window in real units
	REALISM_SENSE,
	REALISM_SYSTEMS,
	RELIABILITY_SENSE,			//  0 = unreliable - 100 = totally reliable
	AMBIENT_TEMP_DEGREES_C,		//
	AMBIENT_PRES_MBAR,			//  Millibars * 16
	AMBIENT_WIND_VEL,			//
	AMBIENT_WIND_DIR,			//
	AMBIENT_WINDE,				//  MPS x(east) wind component
	AMBIENT_WINDN,				//  MPS z(up) wind component
	AMBIENT_WINDA,				//  MPS y(north) wind component
	BAROMETRIC_PRESSURE,		//	barometric pressure experienced
	ANGLE_OF_ATTACK_INDICATOR,
	TOTAL_AIR_TEMP,
	G_FORCE,
	CHARGING_AMPS,				//  charging system amps - 1 amp=65535
	SUCTION_PRESSURE,			//	in hg
	MARKER_BEACON_STATE,		//	0=no beacon, 1=outer, 2=middle, 3=inner
	CURRENT_DME,				//  DMECUR_DME1 or DMECUR_DME2
	PANEL_STATE_FLAGS,
	GET_GUN_AMMO,
	GET_CANNON_AMMO,
	GET_ROCKET_AMMO,
	GET_BOMB_AMMO,
	ENGINE_PRIMER,				// 0.0 -> 1.0 == in -> out
	COWL_FLAPS,					// 0.0 -> 1.0 == closed -> open
	MASTER_ALTERNATOR,			// 0.0 -> 1.0 == off -> on
	MASTER_BATTERY,				// 0.0 -> 1.0 == off -> on
	CARB_HEAT,					// 0.0 -> 1.0 == off -> on
	FLIGHT_TIME,				// in 1/10 of hours
	FUEL_PUMP,					// 0.0 -> 1.0 == off -> on
	BEACON_LIGHTS,				// 0.0 -> 1.0 == off -> on
	TAXI_LIGHTS,				// 0.0 -> 1.0 == off -> on
	RADIO_STACK_VISIBLE,		// 0.0 -> 1.0 == off -> on
	HORIZON_BAR_OFFSET,			// -10 deg to + 10 deg
	CURRENT_DME_DISTANCE,
	CURRENT_DME_SPEED,
	CURRENT_DME_MIN,
	WARNING_FUEL,
	WARNING_FUEL_L,
	WARNING_FUEL_R,
	WARNING_VACUUM,
	WARNING_VACUUM_L,
	WARNING_VACUUM_R,
	WARNING_OIL_PSI,
	WARNING_VOLTAGE,
	FUEL_TANK_CENTER2_LEVEL,
	FUEL_TANK_CENTER2_CAPACITY,
	FUEL_QUANTITY_CENTER2,                       // Total Gallons
	TOTAL_FUEL_QUANTITY_GALLONS,
	SELECTED_FUEL_QUANTITY_GALLONS,
	SELECTED_FUEL_QUANTITY_LITERS,
	SELECTED_FUEL_QUANTITY_PERCENT,
	RECIP_ENGINE1_ENGINE_RPM,
	RECIP_ENGINE1_MANIFOLD_PRESSURE,
	RECIP_ENGINE1_THROTTLE_LEVER_POS,
	RECIP_ENGINE1_MIXTURE_LEVER_POS,
	RECIP_ENGINE1_PROP_LEVER_POS,
	RECIP_ENGINE1_COWL_FLAP_POS,                //0 = closed, 1 = open
	RECIP_ENGINE1_CARB_HEAT_POS,                //0 = off, 1 = on
	RECIP_ENGINE1_ALTERNATE_AIR_POS,            //0 = closed, 1 = off
	RECIP_ENGINE1_COOLANT_RESERVOIR_PCT,
	RECIP_ENGINE1_LEFT_MAG,
	RECIP_ENGINE1_RIGHT_MAG,
	RECIP_ENGINE1_STARTER,
	RECIP_ENGINE1_BRAKE_POWER,                  //power delivered to the shaft
	RECIP_ENGINE1_SHAFT_TORQUE,                 //torque delivered to the shaft
	RECIP_ENGINE1_PROP_TORQUE,                  //torque required by prop
	RECIP_ENGINE1_STARTER_TORQUE,               //torque applied by	starter
	RECIP_ENGINE1_COMBUSTION,                   //combustion flag
	RECIP_ENGINE1_TURBOCHARGER_FAILED,
	RECIP_ENGINE1_EMERGENCY_BOOST_ACTIVE,       //like WEP in the P51
	RECIP_ENGINE1_EMERGENCY_BOOST_ELAPSED_TIME, //how long emergency has been active
	RECIP_ENGINE1_WASTEGATE_POS,                //position of wastegate controller 1=closed (full boost), 0=open (no boost)
	RECIP_ENGINE1_PROP_BETA,                    //blade angle (relative to plane of rotation)
	RECIP_ENGINE1_THRUST,                       //lbs
	RECIP_ENGINE1_EGT_DEGR,                     //EGT degrees Rankine
	RECIP_ENGINE1_TIT_DEGR,                     //Turbine Inlet Temperature degrees Rankine
	RECIP_ENGINE1_CHT_DEGR,                     //CHT degrees Rankine
	RECIP_ENGINE1_OIL_TEMP_DEGR,                //Oil Temperature degrees Rankine
	RECIP_ENGINE1_RADIATOR_DEGR,                //Radiator temperature
	RECIP_ENGINE1_OIL_PRESS_PSF,                //Oil Pressure lbs/sqft
	RECIP_ENGINE1_OIL_LEAK_PCT,                 //Percent Oil leaked
	RECIP_ENGINE1_FUEL_AVAILABLE,               //Fuel available to engine?
	RECIP_ENGINE1_FUELFLOW_PPH,                 //Fuel flow in lbs/hr
	RECIP_ENGINE1_TANK_SELECTOR,                //Fuel tank selector
	RECIP_ENGINE1_TANKS_USED,                   //Fuel tanks used
	RECIP_ENGINE1_NUMBER_OF_TANKS_USED,         //Number of fuel tanks used
	RECIP_ENGINE1_FUEL_PRESSURE_PSF,            //Fuel pressure in lbs/sqft
	RECIP_ENGINE1_COMBUSTION_SOUND_PCT,         //Percent of Sound (0 - 1)
	RECIP_ENGINE1_INDUCED_VELOCITY,             //fps, velocity induced by prop
	RECIP_ENGINE1_DAMAGE_PERCENT,               //0-100%
	RECIP_ENGINE2_ENGINE_RPM,
	RECIP_ENGINE2_MANIFOLD_PRESSURE,
	RECIP_ENGINE2_THROTTLE_LEVER_POS,
	RECIP_ENGINE2_MIXTURE_LEVER_POS,
	RECIP_ENGINE2_PROP_LEVER_POS,
	RECIP_ENGINE2_COWL_FLAP_POS,                //0 = closed, 1 = open
	RECIP_ENGINE2_CARB_HEAT_POS,                //0 = off, 1 = on
	RECIP_ENGINE2_ALTERNATE_AIR_POS,            //0 = closed, 1 = off
	RECIP_ENGINE2_COOLANT_RESERVOIR_PCT,
	RECIP_ENGINE2_LEFT_MAG,
	RECIP_ENGINE2_RIGHT_MAG,
	RECIP_ENGINE2_STARTER,
	RECIP_ENGINE2_BRAKE_POWER,                  //power delivered to the shaft
	RECIP_ENGINE2_SHAFT_TORQUE,                 //torque delivered to the shaft
	RECIP_ENGINE2_PROP_TORQUE,                  //torque required by prop
	RECIP_ENGINE2_STARTER_TORQUE,               //torque applied by	starter
	RECIP_ENGINE2_COMBUSTION,                   //combustion flag
	RECIP_ENGINE2_TURBOCHARGER_FAILED,
	RECIP_ENGINE2_EMERGENCY_BOOST_ACTIVE,       //like WEP in the P51
	RECIP_ENGINE2_EMERGENCY_BOOST_ELAPSED_TIME, //how long emergency has been active
	RECIP_ENGINE2_WASTEGATE_POS,                //position of wastegate controller 1=closed (full boost), 0=open (no boost)
	RECIP_ENGINE2_PROP_BETA,                    //blade angle (relative to plane of rotation)
	RECIP_ENGINE2_THRUST,                       //lbs
	RECIP_ENGINE2_EGT_DEGR,                     //EGT degrees Rankine
	RECIP_ENGINE2_TIT_DEGR,                     //Turbine Inlet Temperature degrees Rankine
	RECIP_ENGINE2_CHT_DEGR,                     //CHT degrees Rankine
	RECIP_ENGINE2_OIL_TEMP_DEGR,                //Oil Temperature degrees Rankine
	RECIP_ENGINE2_RADIATOR_DEGR,                //Radiator temperature
	RECIP_ENGINE2_OIL_PRESS_PSF,                //Oil Pressure lbs/sqft
	RECIP_ENGINE2_OIL_LEAK_PCT,                 //Percent Oil leaked
	RECIP_ENGINE2_FUEL_AVAILABLE,               //Fuel available to engine?
	RECIP_ENGINE2_FUELFLOW_PPH,                 //Fuel flow in lbs/hr
	RECIP_ENGINE2_TANK_SELECTOR,                //Fuel tank selector
	RECIP_ENGINE2_TANKS_USED,                   //Fuel tanks used
	RECIP_ENGINE2_NUMBER_OF_TANKS_USED,         //Number of fuel tanks used
	RECIP_ENGINE2_FUEL_PRESSURE_PSF,            //Fuel pressure in lbs/sqft
	RECIP_ENGINE2_COMBUSTION_SOUND_PCT,         //Percent of Sound (0 - 1)
	RECIP_ENGINE2_INDUCED_VELOCITY,             //fps, velocity induced by prop
	RECIP_ENGINE2_DAMAGE_PERCENT,               //0-100%
	RECIP_ENGINE3_ENGINE_RPM,
	RECIP_ENGINE3_MANIFOLD_PRESSURE,
	RECIP_ENGINE3_THROTTLE_LEVER_POS,
	RECIP_ENGINE3_MIXTURE_LEVER_POS,
	RECIP_ENGINE3_PROP_LEVER_POS,
	RECIP_ENGINE3_COWL_FLAP_POS,                //0 = closed, 1 = open
	RECIP_ENGINE3_CARB_HEAT_POS,                //0 = off, 1 = on
	RECIP_ENGINE3_ALTERNATE_AIR_POS,            //0 = closed, 1 = off
	RECIP_ENGINE3_COOLANT_RESERVOIR_PCT,
	RECIP_ENGINE3_LEFT_MAG,
	RECIP_ENGINE3_RIGHT_MAG,
	RECIP_ENGINE3_STARTER,
	RECIP_ENGINE3_BRAKE_POWER,                  //power delivered to the shaft
	RECIP_ENGINE3_SHAFT_TORQUE,                 //torque delivered to the shaft
	RECIP_ENGINE3_PROP_TORQUE,                  //torque required by prop
	RECIP_ENGINE3_STARTER_TORQUE,               //torque applied by	starter
	RECIP_ENGINE3_COMBUSTION,                   //combustion flag
	RECIP_ENGINE3_TURBOCHARGER_FAILED,
	RECIP_ENGINE3_EMERGENCY_BOOST_ACTIVE,       //like WEP in the P51
	RECIP_ENGINE3_EMERGENCY_BOOST_ELAPSED_TIME, //how long emergency has been active
	RECIP_ENGINE3_WASTEGATE_POS,                //position of wastegate controller 1=closed (full boost), 0=open (no boost)
	RECIP_ENGINE3_PROP_BETA,                    //blade angle (relative to plane of rotation)
	RECIP_ENGINE3_THRUST,                       //lbs
	RECIP_ENGINE3_EGT_DEGR,                     //EGT degrees Rankine
	RECIP_ENGINE3_TIT_DEGR,                     //Turbine Inlet Temperature degrees Rankine
	RECIP_ENGINE3_CHT_DEGR,                     //CHT degrees Rankine
	RECIP_ENGINE3_OIL_TEMP_DEGR,                //Oil Temperature degrees Rankine
	RECIP_ENGINE3_RADIATOR_DEGR,                //Radiator temperature
	RECIP_ENGINE3_OIL_PRESS_PSF,                //Oil Pressure lbs/sqft
	RECIP_ENGINE3_OIL_LEAK_PCT,                 //Percent Oil leaked
	RECIP_ENGINE3_FUEL_AVAILABLE,               //Fuel available to engine?
	RECIP_ENGINE3_FUELFLOW_PPH,                 //Fuel flow in lbs/hr
	RECIP_ENGINE3_TANK_SELECTOR,                //Fuel tank selector
	RECIP_ENGINE3_TANKS_USED,                   //Fuel tanks used
	RECIP_ENGINE3_NUMBER_OF_TANKS_USED,         //Number of fuel tanks used
	RECIP_ENGINE3_FUEL_PRESSURE_PSF,            //Fuel pressure in lbs/sqft
	RECIP_ENGINE3_COMBUSTION_SOUND_PCT,         //Percent of Sound (0 - 1)
	RECIP_ENGINE3_INDUCED_VELOCITY,             //fps, velocity induced by prop
	RECIP_ENGINE3_DAMAGE_PERCENT,               //0-100%
	RECIP_ENGINE4_ENGINE_RPM,
	RECIP_ENGINE4_MANIFOLD_PRESSURE,
	RECIP_ENGINE4_THROTTLE_LEVER_POS,
	RECIP_ENGINE4_MIXTURE_LEVER_POS,
	RECIP_ENGINE4_PROP_LEVER_POS,
	RECIP_ENGINE4_COWL_FLAP_POS,                //0 = closed, 1 = open
	RECIP_ENGINE4_CARB_HEAT_POS,                //0 = off, 1 = on
	RECIP_ENGINE4_ALTERNATE_AIR_POS,            //0 = closed, 1 = off
	RECIP_ENGINE4_COOLANT_RESERVOIR_PCT,
	RECIP_ENGINE4_LEFT_MAG,
	RECIP_ENGINE4_RIGHT_MAG,
	RECIP_ENGINE4_STARTER,
	RECIP_ENGINE4_BRAKE_POWER,                  //power delivered to the shaft
	RECIP_ENGINE4_SHAFT_TORQUE,                 //torque delivered to the shaft
	RECIP_ENGINE4_PROP_TORQUE,                  //torque required by prop
	RECIP_ENGINE4_STARTER_TORQUE,               //torque applied by	starter
	RECIP_ENGINE4_COMBUSTION,                   //combustion flag
	RECIP_ENGINE4_TURBOCHARGER_FAILED,
	RECIP_ENGINE4_EMERGENCY_BOOST_ACTIVE,       //like WEP in the P51
	RECIP_ENGINE4_EMERGENCY_BOOST_ELAPSED_TIME, //how long emergency has been active
	RECIP_ENGINE4_WASTEGATE_POS,                //position of wastegate controller 1=closed (full boost), 0=open (no boost)
	RECIP_ENGINE4_PROP_BETA,                    //blade angle (relative to plane of rotation)
	RECIP_ENGINE4_THRUST,                       //lbs
	RECIP_ENGINE4_EGT_DEGR,                     //EGT degrees Rankine
	RECIP_ENGINE4_TIT_DEGR,                     //Turbine Inlet Temperature degrees Rankine
	RECIP_ENGINE4_CHT_DEGR,                     //CHT degrees Rankine
	RECIP_ENGINE4_OIL_TEMP_DEGR,                //Oil Temperature degrees Rankine
	RECIP_ENGINE4_RADIATOR_DEGR,                //Radiator temperature
	RECIP_ENGINE4_OIL_PRESS_PSF,                //Oil Pressure lbs/sqft
	RECIP_ENGINE4_OIL_LEAK_PCT,                 //Percent Oil leaked
	RECIP_ENGINE4_FUEL_AVAILABLE,               //Fuel available to engine?
	RECIP_ENGINE4_FUELFLOW_PPH,                 //Fuel flow in lbs/hr
	RECIP_ENGINE4_TANK_SELECTOR,                //Fuel tank selector
	RECIP_ENGINE4_TANKS_USED,                   //Fuel tanks used
	RECIP_ENGINE4_NUMBER_OF_TANKS_USED,         //Number of fuel tanks used
	RECIP_ENGINE4_FUEL_PRESSURE_PSF,            //Fuel pressure in lbs/sqft
	RECIP_ENGINE4_COMBUSTION_SOUND_PCT,         //Percent of Sound (0 - 1)
	RECIP_ENGINE4_INDUCED_VELOCITY,             //fps, velocity induced by prop
	RECIP_ENGINE4_DAMAGE_PERCENT,               //0-100%
	FUEL_QUANTITY_CENTER3,                      //Total Gallons
	SCORE_STRING_QUICK_COMBAT,
	SCORE_STRING_MULTIPLAYER,
	IS_MULTIPLAYER_TEAM_COMBAT,
	VOR1_BEARING_DEGREES,
	FORWARD_GROUND_VELOCITY,					// in ft/sec
	SIDE_GROUND_VELOCITY,						// in ft/sec
	VERTICAL_GROUND_VELOCITY,					// in ft/sec
	NORTH_VELOCITY,								// in ft/sec
	EAST_VELOCITY,								// in ft/sec
	VERTICAL_VELOCITY,							// in ft/sec
	CLOCK_TOTAL_SECONDS,				//  local clock time, seconds since midnight
	GENERAL_ENGINE1_THROTTLE_LEVER_POS,
	GENERAL_ENGINE1_PROPELLER_LEVER_POS,
	GENERAL_ENGINE1_MIXTURE_LEVER_POS ,
	GENERAL_ENGINE1_OIL_TEMP,
	GENERAL_ENGINE1_OIL_PRES,
	GENERAL_ENGINE1_STARTER,
	GENERAL_ENGINE1_FAILURE,
	GENERAL_ENGINE1_GENERATOR_SWITCH,
	GENERAL_ENGINE1_GENERATOR_ACTIVE,
	GENERAL_ENGINE1_EGT,
	GENERAL_ENGINE2_THROTTLE_LEVER_POS,
	GENERAL_ENGINE2_PROPELLER_LEVER_POS,
	GENERAL_ENGINE2_MIXTURE_LEVER_POS ,
	GENERAL_ENGINE2_OIL_TEMP,
	GENERAL_ENGINE2_OIL_PRES,
	GENERAL_ENGINE2_STARTER ,
	GENERAL_ENGINE2_FAILURE,
	GENERAL_ENGINE2_GENERATOR_SWITCH,
	GENERAL_ENGINE2_GENERATOR_ACTIVE,
	GENERAL_ENGINE2_EGT,
	GENERAL_ENGINE3_THROTTLE_LEVER_POS,
	GENERAL_ENGINE3_PROPELLER_LEVER_POS,
	GENERAL_ENGINE3_MIXTURE_LEVER_POS ,
	GENERAL_ENGINE3_OIL_TEMP,
	GENERAL_ENGINE3_OIL_PRES,
	GENERAL_ENGINE3_STARTER ,
	GENERAL_ENGINE3_FAILURE,
	GENERAL_ENGINE3_GENERATOR_SWITCH,
	GENERAL_ENGINE3_GENERATOR_ACTIVE,
	GENERAL_ENGINE3_EGT,
	GENERAL_ENGINE4_THROTTLE_LEVER_POS,
	GENERAL_ENGINE4_PROPELLER_LEVER_POS,
	GENERAL_ENGINE4_MIXTURE_LEVER_POS ,
	GENERAL_ENGINE4_OIL_TEMP,
	GENERAL_ENGINE4_OIL_PRES,
	GENERAL_ENGINE4_STARTER ,
	GENERAL_ENGINE4_FAILURE,
	GENERAL_ENGINE4_GENERATOR_SWITCH,
	GENERAL_ENGINE4_GENERATOR_ACTIVE,
	GENERAL_ENGINE4_EGT,
	NAV1_COMMNAV_TEST,
	NAV2_COMMNAV_TEST,
	COM1_AUTOSWITCH_ON,
	NAV1_AUTOSWITCH_ON,
	COM2_AUTOSWITCH_ON,
	NAV2_AUTOSWITCH_ON,
	ELAPSED_SECONDS,
	G_FORCE_MAXIMUM,
	G_FORCE_MINIMUM,
	ENGINE_WORKING_TIME,
	ENGINE1_MAX_RPM,
	ENGINE2_MAX_RPM,
	ENGINE3_MAX_RPM,
	ENGINE4_MAX_RPM,
	ATTITUDE_BARS_POSITION,
	RAD_INS_SWITCH,		// used in concorde only
	RADIO_HEIGHT,			// meters
	DECISION_HEIGHT,		// meters
	LOW_HEIGHT_WARNING,		// boolean
	COM_STBY_FREQUENCY,		// BCD; same as COM_FREQUENCY
	COM_RADIO_25_KHZ_TUNABLE, // Boolean
	NAV_LIGHTS,
	LOGO_LIGHTS,
	WING_LIGHTS,
	RECOGNITION_LIGHTS,
	RADIO_MORSE_IDENT_STATES,
	TURB_ENGINE_1_N1,
	TURB_ENGINE_1_N2,
	TURB_ENGINE_1_CORRECTED_N1,
	TURB_ENGINE_1_CORRECTED_N2,
	TURB_ENGINE_1_CORRECTED_FF,
	TURB_ENGINE_1_PCT_MAX_TORQUE,
	TURB_ENGINE_1_EPR,
	TURB_ENGINE_1_ITT,
	TURB_ENGINE_1_AFTERBURNER,
	TURB_ENGINE_1_JET_THRUST,
	TURB_ENGINE_1_BLEEDAIRPSI,
	TURB_ENGINE_1_TANK_SELECTOR,
	TURB_ENGINE_1_TANKS_USED,
	TURB_ENGINE_1_NUMBER_TANKS,
	TURB_ENGINE_1_FUELFLOW_PPH,
	TURB_ENGINE_1_FUEL_AVAILABLE,
	TURB_ENGINE_1_PCT_AREA,
	TURB_ENGINE_1_PCT_REVERSER,
	TURB_ENGINE_1_VIBRATION,
	TURB_ENGINE_2_N1,
	TURB_ENGINE_2_N2,
	TURB_ENGINE_2_CORRECTED_N1,
	TURB_ENGINE_2_CORRECTED_N2,
	TURB_ENGINE_2_CORRECTED_FF,
	TURB_ENGINE_2_PCT_MAX_TORQUE,
	TURB_ENGINE_2_EPR,
	TURB_ENGINE_2_ITT,
	TURB_ENGINE_2_AFTERBURNER,
	TURB_ENGINE_2_JET_THRUST,
	TURB_ENGINE_2_BLEEDAIRPSI,
	TURB_ENGINE_2_TANK_SELECTOR,
	TURB_ENGINE_2_TANKS_USED,
	TURB_ENGINE_2_NUMBER_TANKS,
	TURB_ENGINE_2_FUELFLOW_PPH,
	TURB_ENGINE_2_FUEL_AVAILABLE,
	TURB_ENGINE_2_PCT_AREA,
	TURB_ENGINE_2_PCT_REVERSER,
	TURB_ENGINE_2_VIBRATION,
	TURB_ENGINE_3_N1,
	TURB_ENGINE_3_N2,
	TURB_ENGINE_3_CORRECTED_N1,
	TURB_ENGINE_3_CORRECTED_N2,
	TURB_ENGINE_3_CORRECTED_FF,
	TURB_ENGINE_3_PCT_MAX_TORQUE,
	TURB_ENGINE_3_EPR,
	TURB_ENGINE_3_ITT,
	TURB_ENGINE_3_AFTERBURNER,
	TURB_ENGINE_3_JET_THRUST,
	TURB_ENGINE_3_BLEEDAIRPSI,
	TURB_ENGINE_3_TANK_SELECTOR,
	TURB_ENGINE_3_TANKS_USED,
	TURB_ENGINE_3_NUMBER_TANKS,
	TURB_ENGINE_3_FUELFLOW_PPH,
	TURB_ENGINE_3_FUEL_AVAILABLE,
	TURB_ENGINE_3_PCT_AREA,
	TURB_ENGINE_3_PCT_REVERSER,
	TURB_ENGINE_3_VIBRATION,
	TURB_ENGINE_4_N1,
	TURB_ENGINE_4_N2,
	TURB_ENGINE_4_CORRECTED_N1,
	TURB_ENGINE_4_CORRECTED_N2,
	TURB_ENGINE_4_CORRECTED_FF,
	TURB_ENGINE_4_PCT_MAX_TORQUE,
	TURB_ENGINE_4_EPR,
	TURB_ENGINE_4_ITT,
	TURB_ENGINE_4_AFTERBURNER,
	TURB_ENGINE_4_JET_THRUST,
	TURB_ENGINE_4_BLEEDAIRPSI,
	TURB_ENGINE_4_TANK_SELECTOR,
	TURB_ENGINE_4_TANKS_USED,
	TURB_ENGINE_4_NUMBER_TANKS,
	TURB_ENGINE_4_FUELFLOW_PPH,
	TURB_ENGINE_4_FUEL_AVAILABLE,
	TURB_ENGINE_4_PCT_AREA,
	TURB_ENGINE_4_PCT_REVERSER,
	TURB_ENGINE_4_VIBRATION,
	PROPELLER_1_RPM,						// Propeller 1
	PROPELLER_1_PCT_MAX_RPM,
	PROPELLER_1_THRUST,
	PROPELLER_1_BETA,
	PROPELLER_1_FEATHERING_INHIBIT,
	PROPELLER_1_FEATHERED,
	PROPELLER_1_SYNC_DELTA_LEVER,
	PROPELLER_1_AUTOFEATHER_ARMED,
	PROPELLER_2_RPM,						// Propeller 2
	PROPELLER_2_PCT_MAX_RPM,
	PROPELLER_2_THRUST,
	PROPELLER_2_BETA,
	PROPELLER_2_FEATHERING_INHIBIT,
	PROPELLER_2_FEATHERED,
	PROPELLER_2_SYNC_DELTA_LEVER,
	PROPELLER_2_AUTOFEATHER_ARMED,
	PROPELLER_3_RPM,						// Propeller 3
	PROPELLER_3_PCT_MAX_RPM,
	PROPELLER_3_THRUST,
	PROPELLER_3_BETA,
	PROPELLER_3_FEATHERING_INHIBIT,
	PROPELLER_3_FEATHERED,
	PROPELLER_3_SYNC_DELTA_LEVER,
	PROPELLER_3_AUTOFEATHER_ARMED,
	PROPELLER_4_RPM,						// Propeller 4
	PROPELLER_4_PCT_MAX_RPM,
	PROPELLER_4_THRUST,
	PROPELLER_4_BETA,
	PROPELLER_4_FEATHERING_INHIBIT,
	PROPELLER_4_FEATHERED,
	PROPELLER_4_SYNC_DELTA_LEVER,
	PROPELLER_4_AUTOFEATHER_ARMED,
	HYDRAULICS1_PRESSURE_PSF,
	HYDRAULICS1_RESERVOIR_PCT,
	HYDRAULICS2_PRESSURE_PSF,
	HYDRAULICS2_RESERVOIR_PCT,
	HYDRAULICS3_PRESSURE_PSF,
	HYDRAULICS3_RESERVOIR_PCT,
	HYDRAULICS4_PRESSURE_PSF,
	HYDRAULICS4_RESERVOIR_PCT,
	AVIONICS_MASTER_SWITCH,
	PANEL_AUTOFEATHER_SWITCH,				// Panel States
	PANEL_ANTIICE_SWITCH,
	PANEL_AUTOBRAKE_SWITCH,
	DAY_OF_WEEK,			// 0-6
	DAY_OF_MONTH,			// 1-31
	CURRENT_MONTH,			// 1-12
	CURRENT_YEAR,			// 1-????
	TIME_ZONE_OFFSET,		// in minutes, positive west of GMT
	DAYLIGHT_SAVING_ACTIVE,	// 0 or 1
	TOTAL_LOAD_AMPS,
	BATTERY_LOAD,
	BATTERY_VOLTAGE,
	MAIN_BUS_VOLTAGE,
	MAIN_BUS_AMPS,
	AVIONICS_BUS_VOLTAGE,
	AVIONICS_BUS_AMPS,
	HOT_BATTERY_BUS_VOLTAGE,
	HOT_BATTERY_BUS_AMPS,
	BATTERY_BUS_VOLTAGE,
	BATTERY_BUS_AMPS,
	GENERATOR_ALTERNATOR_1_BUS_VOLTAGE,
	GENERATOR_ALTERNATOR_1_BUS_AMPS,
	GENERATOR_ALTERNATOR_2_BUS_VOLTAGE,
	GENERATOR_ALTERNATOR_2_BUS_AMPS,
	GENERATOR_ALTERNATOR_3_BUS_VOLTAGE,
	GENERATOR_ALTERNATOR_3_BUS_AMPS,
	GENERATOR_ALTERNATOR_4_BUS_VOLTAGE,
	GENERATOR_ALTERNATOR_4_BUS_AMPS,
	GENERAL_PANEL_CIRCUIT_ON,
	FLAP_MOTOR_CIRCUIT_ON,
	GEAR_MOTOR_CIRCUIT_ON,
	AUTOPILOT_CIRCUIT_ON,
	AVIONICS_CIRCUIT_ON,
	PITOT_HEAT_CIRCUIT_ON,
	PROP_SYNC_CIRCUIT_ON,
	AUTO_FEATHER_CIRCUIT_ON,
	AUTO_BRAKES_CIRCUIT_ON,
	STANDBY_VACUUM_CIRCUIT_ON,
	MARKER_BEACON_CIRCUIT_ON,
	GEAR_WARNING_CIRCUIT_ON,
	HYDRAULIC_PUMP_CIRCUIT_ON,
	ELEVATOR_DEFLECTION,	//	radians
	ELEVATOR_TRIM,			//	radians
	AILERON_DEFLECTION,		//	radians
	AILERON_TRIM,			//	radians
	RUDDER_DEFLECTION,		//	radians
	RUDDER_TRIM,			//	radians
	PROPSYNC_ACTIVE,
	INCIDENCE_ALPHA,
	INCIDENCE_BETA,
	TOTAL_FUEL_QUANTITY_LBS,
	FLIGHT_DIRECTOR_ACTIVE,
	FLIGHT_DIRECTOR_PITCH,		// degrees
	FLIGHT_DIRECTOR_BANK,		// degrees
	CG_PERCENT,
	CG_AFT_LIMIT,
	CG_FWD_LIMIT,
	CG_MAX_MACH,
	CG_MIN_MACH,
	STANDARD_ATM_TEMPERATURE,	// standard atmosphere temperature at aircraft's altitude; celsius
	ENGINE_1_FUELFLOW_BUG_POSITION,		// lbs per hour
	ENGINE_2_FUELFLOW_BUG_POSITION,
	ENGINE_3_FUELFLOW_BUG_POSITION,
	ENGINE_4_FUELFLOW_BUG_POSITION,
	CONCORDE_VISOR_NOSE_HANDLE,	// 0 - Visor Up, Nose Up, 1 - Visor Dn, Nose Up, 2 - Visor Dn, Nose 5 deg, 3 - Visor Dn, Nose 12.5 deg
	CONCORDE_VISOR_POS_PCT,		// 0=Up, 1.0 Extended/Down
	CONCORDE_NOSE_ANGLE,		// degrees; 0 - up
	GEAR_POS_TAIL,
	ELEVON_1_DEFLECTION,		// The elevon indices start at 1 at the far left and increase to the right.
	ELEVON_2_DEFLECTION,		// radians
	ELEVON_3_DEFLECTION,
	ELEVON_4_DEFLECTION,
	ELEVON_5_DEFLECTION,
	ELEVON_6_DEFLECTION,
	ELEVON_7_DEFLECTION,
	ELEVON_8_DEFLECTION,
	PANEL_AUTOPILOT_SPEED_SETTING,		// Knots
	AUTOPILOT_AIRSPEED_ACQUISITION,		// boolean
	AUTOPILOT_AIRSPEED_HOLD_CURRENT,	// boolean
	AUTOPILOT_MAX_SPEED,				// boolean
	AUTOPILOT_CRUISE_SPEED,				// boolean
	BARBER_POLE_MACH,					// real mach
	SELECTED_FUEL_TRANSFER_MODE,		// -1 off, 0 auto, 1 forward, 2 aft
	HYDRAULIC_SYSTEM_INTEGRITY,			// 0.0 - complete failure; 1.0 - everything is ok
	ATTITUDE_CAGE_BUTTON,
	VOR1_NEEDLE_RADIO,					// +-127 correspond to +-10 if VOR or to +-2.5 if localiser. Driven always by VOR
	GPS_POSITION_LAT,
	GPS_POSITION_LON,
	GPS_POSITION_ALT,
	GPS_MAGVAR,							// magnetic deviation (radians)
	GPS_FLAGS,							// GPS_FLAG_ACTIVE_FLIGHT_PLAN = 0x00002	there is an active flight plan
	// GPS_FLAG_ACTIVE_WAY_POINT   = 0x00004	there is an active way point
	// GPS_FLAG_ARRIVED            = 0x00008	last waypoint reached
	// GPS_FLAG_DIRECTTO_FLIGHTPLAN= 0x00020	manual flight plan
	GPS_GROUND_SPEED,					// meters per second
	GPS_GROUND_HEADING,					// radians (0 - 2PI); true heading, yaw
	GPS_GROUND_TRACK,					// radians (0 - 2PI); heading + magvar, magnetic yaw
	GPS_WP_DISTANCE,					// meters to next wp
	GPS_WP_BEARING,						// heading (radians) to next wp + magvar
	GPS_WP_CROSS_TRK,					// cross_trk (meters)
	GPS_WP_REQ_HDG,						// required heading, magnetic, radians (0 - 2PI), from prev wp to next wp
	GPS_WP_STRING,						// name of next waypoint
	GPS_WP_NEXT_LAT,
	GPS_WP_NEXT_LON,
	GPS_WP_NEXT_ALT,
	GPS_WP_PREV_LAT,
	GPS_WP_PREV_LON,
	GPS_WP_PREV_ALT,
	GPS_WP_TRUE_BEARING,				// true bearing, degrees
	GPS_WP_TRUE_REQ_HDG,				// true required heading, degrees
	GPS_DRIVES_NAV1,
	HSI_VERTICAL_NEEDLE,				// -1.0 .. 1.0 corresponds to -10deg .. 10deg if VOR or to -2.5deg .. +2.5deg if localiser +5NM .. -5NM  if GPS
	HSI_HORIZONTAL_NEEDLE,				// -1.0 .. 1.0 corresponds to -0.7deg .. +0.7deg
	HSI_VERTICAL_VALID,					// 0 - Nav flag on
	HSI_HORIZONTAL_VALID,				// 0 - GS flag on
	HSI_TF_FLAG,						// -1.0 - from. 0.0 - none, 1.0 - to
	HSI_OBI_NEEDLE,						// 0 .. 360
	HSI_DESIRED_HEADING_NEEDLE,			// 0 .. 360
	HSI_BEARING,						// 0 .. 360
	HSI_BEARING_VALID,					// 1 - true
	HSI_SIGNAL_LOCALISER,				// 1 - true
	HSI_SPEED,							// knots
	HSI_DISTANCE,						// NM
	HSI_STATION_NAME,					// string
	GEAR_POS_AUX,						//      Aux gear	0 - 16k
	TOOLTIP_UNITS,						// enum TOOLTIP_UNITS_TYPE
	LSO_TEXTURE_ID,						// current LSO_Texture_Id in AI_PLAYER.mw
	LSO_TEXT,							// text
	LEFT_FOLDING_WING_PERCENT,			// 0 - not folded; 1 - folded
	RIGHT_FOLDING_WING_PERCENT,			// 0 - not folded; 1 - folded
	MAIN_EXIT_OPEN,						// 0 - not open; 1 - open
	TAILHOOK_POSITION,				      // 0 - retracted; 1 - extended
	COM2_FREQUENCY,						// BCD same as COM_FREQUENCY
	COM2_STBY_FREQUENCY,			    // BCD; same as COM_FREQUENCY
	NAV1_STBY_FREQUENCY,			    // BCD NAV1 radio freq; same as NAV1_FREQUENCY
	NAV2_STBY_FREQUENCY,			    // BCD NAV2 radio freq; same as NAV2_FREQUENCY
	COM1_TRANSMIT_SELECT,				// 1.0 - yes
	COM2_TRANSMIT_SELECT,				// 1.0 - yes
	COM_BOTH_RECEIVE,					// 1.0 - yes
	NAV1_SOUND_TOGGLE,
	NAV2_SOUND_TOGGLE,
	DME_SOUND_TOGGLE,
	ADF_SOUND_TOGGLE,
	MARKER_SOUND_TOGGLE,
	VOR2_GS_NEEDLE,
	GENERAL_ENGINE1_ANTI_ICE_POS,	    //0 - off 1 - on
	GENERAL_ENGINE2_ANTI_ICE_POS,	    //0 - off 1 - on
	GENERAL_ENGINE3_ANTI_ICE_POS,	    //0 - off 1 - on
	GENERAL_ENGINE4_ANTI_ICE_POS,	    //0 - off 1 - on
	ENGINE1_ON_FIRE,					// 0 - no, 1 - yes
	ENGINE2_ON_FIRE,
	ENGINE3_ON_FIRE,
	ENGINE4_ON_FIRE,
	ENGINE1_FUEL_PUMP_ON,				// 0 - no, 1 - yes
	ENGINE2_FUEL_PUMP_ON,				// 0 - no, 1 - yes
	ENGINE3_FUEL_PUMP_ON,				// 0 - no, 1 - yes
	ENGINE4_FUEL_PUMP_ON,				// 0 - no, 1 - yes
	GENERAL_ENGINE1_FUEL_VALVE,			//1 = Open, 0 = Closed
	GENERAL_ENGINE2_FUEL_VALVE,			//1 = Open, 0 = Closed
	GENERAL_ENGINE3_FUEL_VALVE,			//1 = Open, 0 = Closed
	GENERAL_ENGINE4_FUEL_VALVE,			//1 = Open, 0 = Closed
	GENERAL_ENGINE1_FUEL_PRESSURE,
	GENERAL_ENGINE2_FUEL_PRESSURE,
	GENERAL_ENGINE3_FUEL_PRESSURE,
	GENERAL_ENGINE4_FUEL_PRESSURE,
	WATER_RUDDER_ON,					// 0 - up, 1 - down
	PROP_DEICE_SWITCH,					// 0 = off, 1 = on
	STRUCTURAL_DEICE_SWITCH,			// 0 = off, 1 = on
	FUEL_TANK_SELECTOR_2,				//  see FUEL_TANK_SELECTOR_ enum values
	TRAILING_EDGE_FLAPS0_LEFT_ANGLE,	// Angle of primary trailing edge flaps
	TRAILING_EDGE_FLAPS0_RIGHT_ANGLE,	// Angle of primary trailing edge flaps

	C_GAUGE_TOKEN						// Always the last

} GAUGE_TOKEN;

typedef enum    VAR_TYPE {
	VAR_TYPE_NONE,

	TYPE_BOOL8,
	TYPE_UINT8,
	TYPE_SINT8,
	TYPE_FLAGS8,
	TYPE_ENUM8,

	TYPE_BOOL16,
	TYPE_ANGL16,
	TYPE_UINT16,
	TYPE_SINT16,
	TYPE_UIF16,
	TYPE_SIF16,
	TYPE_FLAGS16,
	TYPE_ENUM16,
	TYPE_BCD16,
	TYPE_BCO16,
	TYPE_VAR16,

	TYPE_BOOL32,
	TYPE_ANGL32,
	TYPE_UINT32,
	TYPE_SINT32,
	TYPE_UIF32,
	TYPE_SIF32,
	TYPE_FLAGS32,
	TYPE_ENUM32,
	TYPE_VAR32,

	TYPE_ANGL48,
	TYPE_SINT48,
	TYPE_UIF48,
	TYPE_SIF48,

	TYPE_UINT64,
	TYPE_SINT64,
	TYPE_SIF64,
	TYPE_FLOAT64,

	TYPE_BOOL,
	TYPE_FLAGS,
	TYPE_ENUM,

	TYPE_VOID,
	TYPE_PVOID,

	TYPE_PUINT32,
	TYPE_PSINT32,
	TYPE_PFLOAT64,

	VAR_TYPE_MAX
} VAR_TYPE;

/**
* struct definitions
*/
typedef union UNIVERSAL_VAR {
	FLOAT64 n;              // any number
	BOOL    b;              // any boolean
	ENUM    e;              // any enumerated value
	FLAGS   f;              // any flags field
	PVOID   p;              // any pointer
	VAR32   d;              // any binary coded decimal
	SINT32  i;              // any signed integer
} UNIVERSAL_VAR, *PUNIVERSAL_VAR, **PPUNIVERSAL_VAR;

typedef struct MODULE_VAR {
	GAUGE_TOKEN             id;
	PVOID                   var_ptr;
	VAR_TYPE                var_type;
	UNIVERSAL_VAR           var_value;
	UNIVERSAL_VAR           var_old;                // value of global var last iteration
} MODULE_VAR, *PMODULE_VAR, **PPMODULE_VAR;

#define FSLINKAGE		\
	ID      ModuleID;						\
	void    (FSAPI *ModuleInit)(void);		\
	void    (FSAPI *ModuleDeinit)(void);	\
	FLAGS32 ModuleFlags;					\
	UINT32  ModulePriority;					\
	UINT32  ModuleVersion;

typedef	struct PANELS
{
	FSLINKAGE
	void		(FSAPI *ignored1[30])(void);
	ERR         (FSAPI *trigger_key_event) ( ID32 event_id, UINT32 value );
	void   		(FSAPI *register_var_by_name) ( PVOID var, VAR_TYPE var_type, PSTRINGZ name );
	void   		(FSAPI *initialize_var) ( PMODULE_VAR module_var );
	void   		(FSAPI *initialize_var_by_name) ( PMODULE_VAR module_var, PSTRINGZ name );
	void   		(FSAPI *lookup_var) ( PMODULE_VAR module_var );
	void (FSAPI *ignored2[12])(void);
	FLOAT64 	(FSAPI *get_named_variable_value) (ID id);
	FLOAT64 	(FSAPI *get_named_variable_typed_value) (ID id, ENUM units);
	void		(FSAPI *set_named_variable_value) (ID id, FLOAT64 value);
	void		(FSAPI *set_named_variable_typed_value) (ID id, FLOAT64 value, ENUM units);
	void (FSAPI *ignored3[12])(void);
	BOOL		(FSAPI *execute_calculator_code) (PCSTRINGZ code, FLOAT64* fvalue, SINT32* ivalue, PCSTRINGZ* svalue);
	BOOL		(FSAPI *format_calculator_string) (PSTRINGZ result, UINT32 resultsize, PCSTRINGZ format);
	BOOL		(FSAPI *reserved32) (void);
	BOOL		(FSAPI *reserved33) (void);
	ENUM		(FSAPI *get_units_enum) (PCSTRINGZ unitname);
	ENUM		(FSAPI *get_aircraft_var_enum) (PCSTRINGZ simvar);
	FLOAT64 	(FSAPI *aircraft_varget) (ENUM simvar, ENUM units, SINT32 index);
	void (FSAPI *ignored4[3])(void);
	void		(FSAPI *send_key_event) (ID32 event_id, UINT32 value);
	void		(FSAPI *register_key_event_handler) (GAUGE_KEY_EVENT_HANDLER handler, PVOID userdata);
	void		(FSAPI *unregister_key_event_handler) (GAUGE_KEY_EVENT_HANDLER handler, PVOID userdata);
} PANELS, *PPANELS;

typedef enum ELEMENT_TYPE_ENUM {
    ELEMENT_TYPE_STATIC_IMAGE,
    ELEMENT_TYPE_NEEDLE,
    ELEMENT_TYPE_STRING,
    ELEMENT_TYPE_SLIDER,
    ELEMENT_TYPE_ICON,
    ELEMENT_TYPE_MOVING_IMAGE,
    ELEMENT_TYPE_SPRITE
} ELEMENT_TYPE_ENUM;

//  2D data structures
typedef SINT32  PIXEL, *PPIXEL, **PPPIXEL;      // screen pixel

typedef struct  PIXPOINT
{
    PIXEL x;
    PIXEL y;
} PIXPOINT, *PPIXPOINT, **PPPIXPOINT;

typedef struct  PIXBOX
{
    PIXEL x;
    PIXEL y;
    PIXEL size_x;
    PIXEL size_y;
} PIXBOX, *PPIXBOX, **PPPIXBOX;

typedef struct ELEMENT_HEADER *PELEMENT_HEADER, **PPELEMENT_HEADER;
typedef struct GAUGEHDR *PGAUGEHDR, **PPGAUGEHDR;

#define ELEMENT_INFO    ELEMENT_TYPE_ENUM           element_type;       \
                        ID                          resource_id;        \
                        PIXPOINT                    position;           \
                        PIXPOINT                    previous_position;  \
                        PIXPOINT                    ofs;                \
                        PGAUGEHDR                   gauge_header;       \
                        struct ELEMENT_HEADER       *previous_element;  \
                        struct ELEMENT_HEADER       **next_element;     \
                        void*                       failure_systems;    \
                        FLAGS                       image_flags;        \
                        FLAGS                       aircraft_special_instrumentation;\
                        FLAGS                       reserved;



typedef struct ELEMENT_HEADER
{
    ELEMENT_INFO
} ELEMENT_HEADER, *PELEMENT_HEADER, **PPELEMENT_HEADER;


typedef void GAUGE_CALLBACK( PGAUGEHDR pgauge, int service_id, UINT32 extra_data );
typedef     GAUGE_CALLBACK      *PGAUGE_CALLBACK;

// defines for mouse sense rect stuff

#define MOUSE_RIGHTSINGLE   BIT31
#define MOUSE_MIDDLESINGLE  BIT30
#define MOUSE_LEFTSINGLE    BIT29
#define MOUSE_RIGHTDOUBLE   BIT28
#define MOUSE_MIDDLEDOUBLE  BIT27
#define MOUSE_LEFTDOUBLE    BIT26
#define MOUSE_RIGHTDRAG     BIT25
#define MOUSE_MIDDLEDRAG    BIT24
#define MOUSE_LEFTDRAG      BIT23
#define MOUSE_MOVE          BIT22
#define MOUSE_DOWN_REPEAT   BIT21
#define MOUSE_KEYBOARD      BIT20

#define MOUSE_NONE          0

typedef enum
{
    MOUSE_RECT_EOL,
    MOUSE_RECT_PARENT,
    MOUSE_RECT_CHILD,
    MOUSE_RECT_END_PARENT,
	MOUSE_RECT_USER
} MOUSE_RECT_TYPE;

typedef enum
{
    CURSOR_NONE = -1,
    CURSOR_NORMAL = 0,
    CURSOR_UPARROW,
    CURSOR_DOWNARROW,
    CURSOR_LEFTARROW,
    CURSOR_RIGHTARROW,
    CURSOR_HAND,
    CURSOR_CROSSHAIR,
} CURSOR_TYPE;

typedef BOOL FSAPI  MOUSE_FUNCTION( PPIXPOINT relative_point, FLAGS32 mouse_flags );
typedef             MOUSE_FUNCTION      *PMOUSE_FUNCTION;

typedef struct  MOUSERECT
{
    MOUSE_RECT_TYPE rect_type;          // type of mouse rectangle (parent, child, eol)
    PIXBOX          relative_box;       // relative sense rectangle (relative to parameter to register function)
    CURSOR_TYPE     cursor;             // cursor to display when over this window
    ID              help_id;            // pop-up help id
    FLAGS           mouse_flags;        // types of mouse activities to look for
    ID              event_id;           // event to generate if mouse_flags is satisfied (implies simple mouse_flags)
    PMOUSE_FUNCTION mouse_function;     // function to call if mouse_flag is satisfied
    PVOID           api_data;           // data for FS6API's use
} MOUSERECT, *PMOUSERECT, **PPMOUSERECT;

typedef struct  GAUGEHDR
{
    UINT32              gauge_header_version;
    char                *gauge_name;
    PPELEMENT_HEADER    elements_list;
    void* query_routine;
    void* install_routine;
    void* initialize_routine;
    void* update_routine;
    void* generate_routine;
    void* draw_routine;
    void* kill_routine;
    char                reserved_1[4];
    UINT32              size_x_mm;
    char                reserved_2[32];
    PMOUSERECT          mouse_rect;
    PGAUGE_CALLBACK     gauge_callback;
    UINT32              user_data;
    PVOID               parameters;
    char*               usage;
    char                reserved_3[16];
}
GAUGEHDR, *PGAUGEHDR, **PPGAUGEHDR;

typedef struct  GAUGESLINKAGE
{
    FSLINKAGE
    PGAUGEHDR       gauge_header_ptr[1];
} GAUGESLINKAGE, *PGAUGESLINKAGE, **PPGAUGESLINKAGE;


#pragma pack()

#endif