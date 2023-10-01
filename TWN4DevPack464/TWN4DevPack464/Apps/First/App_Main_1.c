#include "twn4.sys.h"
#include "apptools.h"
#include "prs.h"

// ****** Event Handler *********************************************

void OnStartup(void)
{
    LEDInit(REDLED | GREENLED);
    LEDOn(GREENLED);
    LEDOff(REDLED);
    
    SetVolume(10);
    BeepLow();
    BeepLow();
}

// ******************************************************************
// ****** Main Program **********************************************
// ******************************************************************
int main(void)
{
    OnStartup();
    TCOMParameters COMParameters;
    COMParameters.BaudRate = 115200;
  	COMParameters.WordLength = COM_WORDLENGTH_8;
    COMParameters.Parity = COM_PARITY_NONE;
  	COMParameters.StopBits = COM_STOPBITS_1;
    COMParameters.FlowControl = COM_FLOWCONTROL_NONE;
    SetCOMParameters(CHANNEL_COM5,&COMParameters);
    SimpleProtoInit(CHANNEL_COM5,PRS_COMM_MODE_ASCII | PRS_COMM_CRC_OFF);

    while (true)
    {
        int TagType;
        int IDBitCnt;
        byte ID[32];

        if (SearchTag(&TagType, &IDBitCnt, ID, sizeof(ID)) )
        {
            LEDOn(BLUELED);
            ApplePay_SelectOSE();
        }
    }
}