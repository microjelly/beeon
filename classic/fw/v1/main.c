#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */
#include <stdlib.h>

#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include "usbdrv.h"

#define BIT_KEY 2
#define BIT_LED 1

#define EEPROM_OSC	0
#define EEPROM_DM   1
#define EEPROM_DR	2
#define EEPROM_KK	3
#define EEPROM_MM	4

#define MOUSE_B     1
#define MOUSE_X     2
#define MOUSE_Y     3
#define MOUSE_W	    4

#define DS_IDLE     10
#define DS_ACTIVE   20

#define DR_FAST     1
#define DR_NORMAL   8
#define DR_SLOW     16
#define DR_EXSLOW   32

#define DM_MOUSE    10
#define DM_KEYBOARD 20

#define MM_CIRCLE   10
#define MM_RANDOM   20

#define LED_MAX		9

#define FR_DS		1
#define FR_DM		2
#define FR_DR		3
#define FR_KK		4
#define FR_MM		5

#define KK_0	    0x27
#define KK_CAPS     0x39
#define KK_DEFAULT	KK_0

/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */

PROGMEM const char usbHidReportDescriptor[USB_CFG_HID_REPORT_DESCRIPTOR_LENGTH] = {

// Mouse 
//	-------------------------------------------------------------------------
	0x05, 0x01,//	Usage Page (Generic Desktop),							|
	0x09, 0x02,//	Usage (Mouse),											|
	0xA1, 0x01,//	Collection (Application),								|
	0x09, 0x01,//		Usage (Pointer)										|
	0xA1, 0x00,//		Collection (Physical),								|
//	-------------------------------------------------------------------------
	0x85, 0x01,//			Report Id (1).									|
//	-------------------------------------------------------------------------
	0x05, 0x09,//			Usage Page (Buttons),							|
	0x19, 0x01,//			Usage Minimum (01),								|
	0x29, 0x03,//			Usage Maximun (03),								|
	0x15, 0x00,//			Logical Minimum (0),							|
	0x25, 0x01,//			Logical Maximum (1),							|
	0x95, 0x03,//			Report Count (3),								|
	0x75, 0x01,//			Report Size (1),								|
	0x81, 0x02,//			Input (Data, Var, Abs),							|
	0x95, 0x01,//			Report Count (1),								|
	0x75, 0x05,//			Report Size (5),								|
	0x81, 0x03,//			Input (Constant), ;5 bit padding				|
//	-------------------------------------------------------------------------
	0x05, 0x01,//			Usage Page (Generic Desktop),					|
	0x09, 0x30,//			Usage (X),										|
	0x09, 0x31,//			Usage (Y),										|
	0x09, 0x38,//			Usage (Wheel),									|
	0x15, 0x81,//			Logical Minimum (-127),							|
	0x25, 0x7F,//			Logical Maximum (127),							|
	0x75, 0x08,//			Report Size (8),								|
	0x95, 0x03,//			Report Count (3),								|
	0x81, 0x06,//			Input (Data, Var, Rel)							|
//	-------------------------------------------------------------------------
	0xC0,//				End Collection,										|
//	-------------------------------------------------------------------------
// Configuration interface
//	-------------------------------------------------------------------------
	0x09, 0x00,//	    USAGE (Vendor Usage 1)								|
//	-------------------------------------------------------------------------
	0x85, 0x03,//		Report Id (3)										|
//	-------------------------------------------------------------------------
	0x15, 0x00,//		LOGICAL_MINIMUM (0)									|
	0x26, 0xff, 0x00,//	LOGICAL_MAXIMUM (255)								|
	0x75, 0x08,//		REPORT_SIZE (8)										|
	0x95, 0x05,//		REPORT_COUNT (5)									|
	0xb1, 0x02,//		FEATURE (Data,Var,Abs)								|
	0xC0,//			End Collection											|
//	-------------------------------------------------------------------------

// Keyboard
//	-------------------------------------------------------------------------
	0x05, 0x01,//	USAGE_PAGE (Generic Desktop)							|
	0x09, 0x06,//	USAGE (Keyboard)										|
	0xa1, 0x01,//	COLLECTION (Application)								|
//	-------------------------------------------------------------------------
	0x85, 0x02,//		Report Id (2)										|
//	-------------------------------------------------------------------------
	0x05, 0x07,//		USAGE_PAGE (Keyboard)								|
	0x19, 0xe0,//		USAGE_MINIMUM (Keyboard LeftControl)				|
	0x29, 0xe7,//		USAGE_MAXIMUM (Keyboard Right GUI)					|
	0x15, 0x00,//		LOGICAL_MINIMUM (0)									|
	0x25, 0x01,//		LOGICAL_MAXIMUM (1)									|
	0x75, 0x01,//		REPORT_SIZE (1)										|
	0x95, 0x08,//		REPORT_COUNT (8)									|
	0x81, 0x02,//		INPUT (Data,Var,Abs)								|
//	-------------------------------------------------------------------------
	0x95, 0x05,//		REPORT_COUNT (5)									|
	0x75, 0x01,//		REPORT_SIZE (1)										|
	0x05, 0x08,//		USAGE_PAGE (LEDs)									|
	0x19, 0x01,//		USAGE_MINIMUM (Num Lock)							|
	0x29, 0x05,//		USAGE_MAXIMUM (Kana)								|
	0x91, 0x02,//		OUTPUT (Data,Var,Abs)								|
//	-------------------------------------------------------------------------
	0x95, 0x01,//		REPORT_COUNT (1)									|
	0x75, 0x03,//		REPORT_SIZE (3)										|
	0x91, 0x03,//		OUTPUT (Cnst,Var,Abs)								|
//	-------------------------------------------------------------------------
	0x95, 0x06,//		REPORT_COUNT (6)									|
	0x75, 0x08,//		REPORT_SIZE (8)										|
	0x15, 0x00,//		LOGICAL_MINIMUM (0)									|
	0x25, 0x65,//		LOGICAL_MAXIMUM (101)								|
	0x05, 0x07,//		USAGE_PAGE (Keyboard)								|
	0x19, 0x00,//		USAGE_MINIMUM (Reserved (no event indicated))		|
	0x29, 0x65,//		USAGE_MAXIMUM (Keyboard Application)				|
	0x81, 0x00,//		INPUT (Data,Ary,Abs)								|
//	-------------------------------------------------------------------------
	0xc0,//			END_COLLECTION  										|
//	-------------------------------------------------------------------------
};



static uchar currentAddress;
static uchar bytesRemaining;

static uchar mouseReportBuffer[5]    = { 1, 0,0,0,0 };
static uchar keyboardReportBuffer[8] = { 2, 0,0,0,0,0,0,0 };
static uchar featureReportBuffer[6]  = { 3, 0,0,0,0,0 };

static int   	sinus = 7 << 6, cosinus = 0;
static uchar    idleRate;   /* repeat rate for keyboards, never used for mice */

static uchar 	deviceStatus = DS_IDLE;
static uchar	deviceRate   = DR_NORMAL;
static uchar	deviceMode   = DM_MOUSE;
static uchar	mouseMode    = MM_RANDOM;
static uchar	keyboardKey  = KK_DEFAULT;
static uchar    runToken     = 1; 

static void toggleDeviceStatus()
{
    if(deviceStatus==DS_ACTIVE){

        deviceStatus = DS_IDLE;
        PORTB |= 1 << BIT_LED;      /* LED on */
    }else{
    
        deviceStatus = DS_ACTIVE;
        PORTB &= ~(1 << BIT_LED);   /* LED off */
    }
}


static void keyPoll(void)
{
static uchar    keyMirror;
uchar           key;

    key = PINB & (1 << BIT_KEY);
    if(keyMirror != key){   /* status changed */
        keyMirror = key;
        if(!key) toggleDeviceStatus();
    }
}

static void timerPoll(void)
{
static int timerCnt;
static int timerCnt2;
static int timerLed;

    if(TIFR & (1 << TOV1)){
        TIFR = (1 << TOV1); /* clear overflow */
        keyPoll();
        if(++timerCnt >= deviceRate){
          timerCnt = 0;
          if(++timerCnt2 >= deviceRate){
            timerCnt2 = 0;
            runToken = 1;
          }
        }
        if(++timerLed >= LED_MAX){
            timerLed = 0;
            if(deviceStatus==DS_ACTIVE && (PINB & (1 << BIT_KEY)) ){
              PORTB &= ~(1 << BIT_LED);   /* LED off */
            }
        }
    }
}

/* The following function advances sin/cos by a fixed angle
 * and stores the difference to the previous coordinates in the report
 * descriptor.
 * The algorithm is the simulation of a second order differential equation.
 */
static void advanceCircleByFixedAngle(void)
{
char    d;

#define DIVIDE_BY_64(val)  (val + (val > 0 ? 32 : -32)) >> 6    /* rounding divide */

    mouseReportBuffer[MOUSE_X] = d = DIVIDE_BY_64(cosinus);
    sinus += d;
    mouseReportBuffer[MOUSE_Y] = d = DIVIDE_BY_64(sinus);
    cosinus -= d;
}

static void randomMouse(void)
{

    mouseReportBuffer[MOUSE_X] = ((rand() / (RAND_MAX / 254 + 1))-128)/8;
    mouseReportBuffer[MOUSE_Y] = ((rand() / (RAND_MAX / 254 + 1))-128)/8;
}

/* ------------------------------------------------------------------------- */

/* usbFunctionWrite() is called when the host sends a chunk of data to the
 * device. For more information see the documentation in usbdrv/usbdrv.h.
 */
uchar usbFunctionWrite(uchar *data, uchar len) {

	uchar i;
	
    if(bytesRemaining == 0)
        return 1;               /* end of transfer */
    if(len > bytesRemaining)
        len = bytesRemaining;

	for(i = 0; i < len; i++) {

		if(currentAddress==FR_DS && data[i]!=0xff && data[i]!=deviceStatus) toggleDeviceStatus();
		else if(currentAddress==FR_DM && data[i]!=0xff && data[i]!=deviceMode && (data[i]==DM_MOUSE||data[i]==DM_KEYBOARD) ) {
			eeprom_write_byte(EEPROM_DM, data[i]);
			deviceMode=data[i];
		} else if(currentAddress==FR_DR && data[i]!=0xff && data[i]!=deviceRate) {
			eeprom_write_byte(EEPROM_DR, data[i]);
			deviceRate=data[i];
		} else if(currentAddress==FR_KK && data[i]!=0xff && data[i]!=keyboardKey) {
			eeprom_write_byte(EEPROM_KK, data[i]);
			keyboardKey=data[i];
		} else if(currentAddress==FR_MM && data[i]!=0xff && data[i]!=mouseMode && (data[i]==MM_CIRCLE||data[i]==MM_RANDOM) ) {
			eeprom_write_byte(EEPROM_MM, data[i]);
			mouseMode=data[i];
		}

    	currentAddress++;
    }
      
    currentAddress += len;
    bytesRemaining -= len;
    return bytesRemaining == 0; /* return 1 if this was the last chunk */
}

usbMsgLen_t usbFunctionSetup(uchar data[8])
{
usbRequest_t    *rq = (void *)data;

    /* The following requests are never used. But since they are required by
     * the specification, we implement them in this example.
     */
    if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS){    /* class request type */
        if(rq->bRequest == USBRQ_HID_GET_REPORT){
            /* wValue: ReportType (highbyte), ReportID (lowbyte) */
            if (rq->wValue.bytes[0] == 1) {
                usbMsgPtr = (void *)&mouseReportBuffer;
                return sizeof(mouseReportBuffer);
            } else if (rq->wValue.bytes[0] == 2) {
                usbMsgPtr = (void *)&keyboardReportBuffer;
                return sizeof(keyboardReportBuffer);
            } else if (rq->wValue.bytes[0] == 3) {
            	featureReportBuffer[FR_DS] = deviceStatus;
            	featureReportBuffer[FR_DM] = deviceMode;
            	featureReportBuffer[FR_DR] = deviceRate;
            	featureReportBuffer[FR_KK] = keyboardKey;
            	featureReportBuffer[FR_MM] = mouseMode;
                usbMsgPtr = (void *)&featureReportBuffer;
                return sizeof(featureReportBuffer);
            }
            return 0;
        } else if(rq->bRequest == USBRQ_HID_SET_REPORT){
        	if (rq->wValue.bytes[0] == 3) {
            	bytesRemaining = rq->wLength.word;
            	currentAddress = 0;
            	return USB_NO_MSG;
            }
        } else if(rq->bRequest == USBRQ_HID_GET_IDLE){
            usbMsgPtr = &idleRate;
            return 1;
        }else if(rq->bRequest == USBRQ_HID_SET_IDLE){
            idleRate = rq->wValue.bytes[1];
        }
    }else{
        /* no vendor specific requests implemented */
    }
    return 0;   /* default for not implemented requests: return no data back to host */
}

/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* ------------------------ Oscillator Calibration ------------------------- */
/* ------------------------------------------------------------------------- */

/* Calibrate the RC oscillator to 8.25 MHz. The core clock of 16.5 MHz is
 * derived from the 66 MHz peripheral clock by dividing. Our timing reference
 * is the Start Of Frame signal (a single SE0 bit) available immediately after
 * a USB RESET. We first do a binary search for the OSCCAL value and then
 * optimize this value with a neighboorhod search.
 * This algorithm may also be used to calibrate the RC oscillator directly to
 * 12 MHz (no PLL involved, can therefore be used on almost ALL AVRs), but this
 * is wide outside the spec for the OSCCAL value and the required precision for
 * the 12 MHz clock! Use the RC oscillator calibrated to 12 MHz for
 * experimental purposes only!
 */
static void calibrateOscillator(void)
{
uchar       step = 128;
uchar       trialValue = 0, optimumValue;
int         x, optimumDev, targetValue = (unsigned)(1499 * (double)F_CPU / 10.5e6 + 0.5);

    /* do a binary search: */
    do{
        OSCCAL = trialValue + step;
        x = usbMeasureFrameLength();    /* proportional to current real frequency */
        if(x < targetValue)             /* frequency still too low */
            trialValue += step;
        step >>= 1;
    }while(step > 0);
    /* We have a precision of +/- 1 for optimum OSCCAL here */
    /* now do a neighborhood search for optimum value */
    optimumValue = trialValue;
    optimumDev = x; /* this is certainly far away from optimum */
    for(OSCCAL = trialValue - 1; OSCCAL <= trialValue + 1; OSCCAL++){
        x = usbMeasureFrameLength() - targetValue;
        if(x < 0)
            x = -x;
        if(x < optimumDev){
            optimumDev = x;
            optimumValue = OSCCAL;
        }
    }
    OSCCAL = optimumValue;
}
/*
Note: This calibration algorithm may try OSCCAL values of up to 192 even if
the optimum value is far below 192. It may therefore exceed the allowed clock
frequency of the CPU in low voltage designs!
You may replace this search algorithm with any other algorithm you like if
you have additional constraints such as a maximum CPU clock.
For version 5.x RC oscillators (those with a split range of 2x128 steps, e.g.
ATTiny25, ATTiny45, ATTiny85), it may be useful to search for the optimum in
both regions.
*/

void    hadUsbReset(void)
{
    calibrateOscillator();
    eeprom_write_byte(EEPROM_OSC, OSCCAL);   /* store the calibrated value in EEPROM */
}

static void timerInit(void)
{
    TCCR1 = 0x0b;           /* select clock: 16.5M/1k -> overflow rate = 16.5M/256k = 62.94 Hz */
}

int __attribute__((noreturn)) main(void)
{
uchar   i;
uchar   calibrationValue;

    PORTB |= 1 << BIT_KEY;  /* pull-up on key input */
    DDRB |= 1 << BIT_LED;   /* output for LED */
    
    calibrationValue = eeprom_read_byte(EEPROM_OSC); /* calibration value from last time */
    if(calibrationValue != 0xff){
        OSCCAL = calibrationValue;
    }

    i = eeprom_read_byte(EEPROM_DM);
    if(i != 0xff) deviceMode = i;
    
    i = eeprom_read_byte(EEPROM_DR);
    if(i != 0xff) deviceRate = i;
    else deviceRate = DR_EXSLOW;
    
    i = eeprom_read_byte(EEPROM_KK);
    if(i != 0xff) keyboardKey = i;
    
    i = eeprom_read_byte(EEPROM_MM);
    if(i != 0xff) mouseMode = i;
    
    usbInit();
    usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */
    for(i=0;i<20;i++){ /* 300 ms disconnect */
        _delay_ms(15);
    }
    usbDeviceConnect();

    wdt_enable(WDTO_1S);

    timerInit();
    usbInit();
    sei();

    PORTB |= 1 << BIT_LED;      /* LED on */

    for(;;){                /* main event loop */
        wdt_reset();
        usbPoll();
        if(usbInterruptIsReady() && keyboardReportBuffer[2]!=0) {
        
                keyboardReportBuffer[2] = 0;
                usbSetInterrupt((void *)&keyboardReportBuffer, sizeof(keyboardReportBuffer));
        } else if(usbInterruptIsReady() && (deviceStatus==DS_ACTIVE) && runToken){

	    	if(deviceMode==DM_MOUSE) {
		    
	        	if(mouseMode==MM_CIRCLE) advanceCircleByFixedAngle();
	        	else randomMouse();
                PORTB |= 1 << BIT_LED;      /* LED on */
               	usbSetInterrupt((void *)&mouseReportBuffer, sizeof(mouseReportBuffer));
           	} else {

               	keyboardReportBuffer[2] = keyboardKey;
               	usbSetInterrupt((void *)&keyboardReportBuffer, sizeof(keyboardReportBuffer));
           	}
           	runToken = 0;
        }
        timerPoll();
    }
}

/* ------------------------------------------------------------------------- */
