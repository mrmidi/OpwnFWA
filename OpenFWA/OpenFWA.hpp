#define NUM_INPUTS 2
#define NUM_OUTPUTS 2

// CTYPE CODES
#define kAVCCommandType_Control 0x00
#define kAVCCommandType_Status 0x01
#define kAVCCommandType_SpecificInquiry 0x02
#define kAVCCommandType_Notify 0x03
#define kAVCCommandType_GeneralInquiry 0x04

// RESPONSE CODES
#define kAVCResponseCode_NotImplemented 0x08
#define kAVCResponseCode_Accepted 0x09
#define kAVCResponseCode_Rejected 0x0A
#define kAVCResponseCode_InTransition 0x0B
#define kAVCResponseCode_Implemented 0x0C
#define kAVCResponseCode_Changed 0x0D
#define kAVCResponseCode_RESERVED 0x0E
#define kAVCResponseCode_Interim 0x0F

// SUBUNIT TYPES
#define kAVCSubunitType_Monitor 0x00
#define kAVCSubunitType_Audio 0x01

