/*!
\file    Serial.h
\brief   Header file of the class Serial. This class is used for communication over a serial device.
\author  Philippe Lucidarme (University of Angers)
\version 2.0
\date    december the 27th of 2019
This Serial library is used to communicate through serial port.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

This is a licence-free software, it can be used by anyone who try to build a better world.
*/


#ifndef SERIALIB_H
#define SERIALIB_H

// Used for TimeOut operations
#include <sys/time.h>
// Include for windows
#if defined (_WIN32) || defined (_WIN64)
    // Accessing to the serial port under Windows
    #include <windows.h>
#endif

// Include for Linux
#if defined (__linux__) || defined(__APPLE__)
    #include <stdlib.h>
    #include <sys/types.h>
    #include <sys/shm.h>
    #include <termios.h>
    #include <string.h>
    #include <iostream>
    // File control definitions
    #include <fcntl.h>
    #include <unistd.h>
    #include <sys/ioctl.h>
#endif


/*! To avoid unused parameters */
#define UNUSED(x) (void)(x)

namespace Serialib
{

/**
 * number of serial data bits
 */
enum SerialDataBits {
    SERIAL_DATABITS_5, /**< 5 databits */
    SERIAL_DATABITS_6, /**< 6 databits */
    SERIAL_DATABITS_7, /**< 7 databits */
    SERIAL_DATABITS_8,  /**< 8 databits */
    SERIAL_DATABITS_16,  /**< 16 databits */
};

/**
 * number of serial stop bits
 */
enum SerialStopBits {
    SERIAL_STOPBITS_1, /**< 1 stop bit */
    SERIAL_STOPBITS_1_5, /**< 1.5 stop bits */
    SERIAL_STOPBITS_2, /**< 2 stop bits */
};

/**
 * type of serial parity bits
 */
enum SerialParity {
    SERIAL_PARITY_NONE, /**< no parity bit */
    SERIAL_PARITY_EVEN, /**< even parity bit */
    SERIAL_PARITY_ODD, /**< odd parity bit */
    SERIAL_PARITY_MARK, /**< mark parity */
    SERIAL_PARITY_SPACE /**< space bit */
};

/*!  \class     Serial
     \brief     This class is used for communication over a serial device.
*/
class Serial
{
public:

    //_____________________________________
    // ::: Constructors and destructors :::



    // Constructor of the class
    Serial    ();

    // Destructor
    ~Serial   ();



    //_________________________________________
    // ::: Configuration and initialization :::


    // Open a device
    char OpenDevice(const char *Device, const unsigned int Bauds,
                    SerialDataBits Databits = SERIAL_DATABITS_8,
                    SerialParity Parity = SERIAL_PARITY_NONE,
                    SerialStopBits Stopbits = SERIAL_STOPBITS_1);

    // Close the current device
    void    CloseDevice();




    //___________________________________________
    // ::: Read/Write operation on characters :::


    // Write a char
    char    WriteChar   (char);

    // Read a char (with timeout)
    char    ReadChar    (char *pByte,const unsigned int Timeout_ms=0);




    //________________________________________
    // ::: Read/Write operation on strings :::


    // Write a string
    char    WriteString (const char *String);

    // Read a string (with timeout)
    int     ReadString  (   char *receivedString,
                            char finalChar,
                            unsigned int maxNbBytes,
                            const unsigned int Timeout_ms=0);



    // _____________________________________
    // ::: Read/Write operation on bytes :::


    // Write an array of bytes
    char    WriteBytes  (const void *Buffer, const unsigned int NbBytes);

    // Read an array of byte (with timeout)
    int     ReadBytes   (void *buffer,unsigned int maxNbBytes,const unsigned int Timeout_ms=0, unsigned int sleepDuration_us=100);




    // _________________________
    // ::: Special operation :::


    // Empty the received buffer
    char    FlushReceiver();

    // Return the number of bytes in the received buffer
    int     Available();




    // _________________________
    // ::: Access to IO bits :::


    // Set CTR status (Data Terminal Ready, pin 4)
    bool    DTR(bool status);
    bool    SetDTR();
    bool    ClearDTR();

    // Set RTS status (Request To Send, pin 7)
    bool    RTS(bool status);
    bool    SetRTS();
    bool    ClearRTS();

    // Get RI status (Ring Indicator, pin 9)
    bool    RI();

    // Get DCD status (Data Carrier Detect, pin 1)
    bool    DCD();

    // Get CTS status (Clear To Send, pin 8)
    bool    CTS();

    // Get DSR status (Data Set Ready, pin 9)
    bool    DSR();

    // Get RTS status (Request To Send, pin 7)
    bool    RTS();

    // Get CTR status (Data Terminal Ready, pin 4)
    bool    DTR();


private:
    // Read a string (no timeout)
    int             readStringNoTimeOut  (char *String,char FinalChar,unsigned int MaxNbBytes);

    // Current DTR and RTS state (can't be read on WIndows)
    bool            currentStateRTS;
    bool            currentStateDTR;





#if defined (_WIN32) || defined( _WIN64)
    // Handle on serial device
    HANDLE          hSerial;
    // For setting serial port timeouts
    COMMTIMEOUTS    timeouts;
#endif
#if defined (__linux__) || defined(__APPLE__)
    int             fd;
#endif

};



/*!  \class     Timeout
     \brief     This class can manage a timer which is used as a timeout.
   */
// Class Timeout
class Timeout
{
public:

    // Constructor
    Timeout();

    // Init the timer
    void                initTimer();

    // Return the elapsed time since initialization
    unsigned long int   elapsedTime_ms();

private:
    // Used to store the previous time (for computing timeout)
    struct timeval      previousTime;
};


}
#endif // Serial_H
