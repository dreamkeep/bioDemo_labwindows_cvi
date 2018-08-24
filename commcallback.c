/********************************************************************************************/
/********************************************************************************************/
/* File:    InstallCommCallback.c                                                           */
/* Purpose: This example illustrates the use of the RS232 Library's InstallComCallback      */
/*          function to respond to the LWRS_RXFLAG event. The user will be asked to enter   */
/*          an event character. Whenever this event character is detected on the COM port,  */
/*          a callback function will be executed.                                           */
/* Notes:   To run this example you need to do a Loopback Test, i.e. connect pin 2 to       */
/*          pin 3 on the serial port.                                                       */
/*          The example uses port 1 by default. To use another port, change the COM_PORT    */
/*          defined value.                                                                  */
/********************************************************************************************/
/********************************************************************************************/

/********************************************************************************************/
/* Include files                                                                            */
/********************************************************************************************/
#include <rs232.h>
#include <ansi_c.h>
//#include <cvirte.h>
//#include <userint.h>
#include "commcallback.h"
#include <formatio.h>

/********************************************************************************************/
/* Constants                                                                                    */
/********************************************************************************************/
#define COM_PORT    36

/********************************************************************************************/
/* Globals                                                                                  */
/********************************************************************************************/


/********************************************************************************************/
/* Prototypes                                                                               */
/********************************************************************************************/
void CVICALLBACK Event_Char_Detect_Func (int portNo,int eventMask,void *callbackData);

/********************************************************************************************/
/* Application entry point.                                                                 */
/********************************************************************************************/
int Init_ComPort (void)
{

    /*  Open and Configure Com port */
    OpenComConfig (COM_PORT, "", 19200, 0, 8, 1, 512, 512);

    /*  Turn off Hardware handshaking (loopback test will not function with it on) */
    SetCTSMode (COM_PORT, LWRS_HWHANDSHAKE_OFF);

    /*  Make sure Serial buffers are empty */
    FlushInQ (COM_PORT);
    FlushOutQ (COM_PORT);


    /*  Install a callback such that if the event character appears at the
        receive buffer, our function will be notified.  */
//  InstallComCallback (COM_PORT, LWRS_RXFLAG, 0, (int)gEventChar[0] , Event_Char_Detect_Func, 0);



    return 0;
}

/********************************************************************************************/
/* SendData ():  Respond to the Send button to send characters out of the serial port.      */
/********************************************************************************************/
int SendData (unsigned char *data,int dlen)
{
    FlushInQ (COM_PORT);
    ComWrt (COM_PORT, data, dlen);
    return 0;
}

/********************************************************************************************/
/* Event_Char_Detect_Func ():  Fuction called when the event character is detected.         */
/********************************************************************************************/
void CVICALLBACK Event_Char_Detect_Func (int portNo,int eventMask,void *callbackData)
{
    return;
}



/********************************************************************************************/
/* ReceiveData ():  Read the data on the serial COM port.                                   */
/********************************************************************************************/
int  ReceiveData (unsigned char *buf,int buflen)
{
    int     strLen;


    /*  Read the characters from the port */
    strLen = GetInQLen (COM_PORT);
    if(strLen > buflen)
        strLen = buflen;
    ComRd (COM_PORT, buf, strLen);

    return strLen;
}

int ShutDownCom (void)
{

   

    return  CloseCom(COM_PORT);   
}