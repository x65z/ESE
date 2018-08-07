//Interface Proj Interface v1  header Zack H
//Oct. 30, 2016
//Modified assignment 2 that uses trees

#ifndef HEADER
# define HEADER

#pragma comment(lib, "Ws2_32.lib")	   // Make sure we are linking against the Ws2_32.lib library
#pragma comment(lib, "Winmm.lib")      // Make sure we are linking against the Winmm.lib library - some functions/symbols from this library (Windows sound API) are used


#include <windows.h>
#include <mmsystem.h>
#include <math.h>

#pragma warning(disable:4996) // Disable annoying warnings

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime> 
#include <conio.h>
#include <stdlib.h>
#include <strsafe.h>
#define NUMMESSAGES 10
#define MLENGTH 140
#define SLENGTH 300000 //Max Length of entered string, huge so can store contents of file

int GetBigMessageFromFile(char szBuf[]);

struct Header {

long lSignature; // must be 0xDEADBEEF
BYTE bReceiverAddr; // receiver ID. 0xff=broadcast
BYTE bSenderAddr; // receiver ID. 0xff=broadcast
BYTE bSenderAddrb; // receiver ID. 0xff=broadcast
int hash; //For checking text
BYTE bVersion; // must be 1 for version 1
long lDataLength; // size of message
char bBools[2]; // Booleans, 0 reps text or audio, 1 reps compression or no
BYTE bPattern[4]; // must be 0xaa 0x55 0xaa 0x55

};

struct Node { //frame
	struct Header *H;
	char buf[MLENGTH];	
	struct Node *nextL;
	struct Node *nextR;
	struct Node *prev;
};

DWORD WINAPI Thread_Receiver(LPVOID lpParam); 
void recmenu(); //receiving submenu
void sendmenu(); //sending submenu
int textmenu();
int audmenu();
int GetMessageFromFile(char szBuf[], int iLen);
void create_node(char message[MLENGTH]);
void find_ordered_tail(char fbuf);
void search(char fbuf);
int height_list(char flag);
void display_list(char flag);
int count_list(char flag); //counts messages
void clear_list(char flag);
void Visit(struct Node *vptr);
///compression
void RLEncode( char *iBuf, int InLen, char *out);
void RLDecode(char *iBuf, int InLen, char *out);
int hashU(char *v, int M);

//////////////////////////////////////////////////////////
//Comm stuff
// Prototype the functions to be used
void initPort(); 
void purgePort();
void outputToPort(LPCVOID buf, DWORD szBuf);
void inputFromPort(LPVOID buf, DWORD szBuf);
int inputFromPortBackground(LPVOID buf, DWORD szBuf);

// Sub functions
void createPortFile();
static int SetComParms();



//Audio stuff////////////////////////////////////////////////////////////////
#define	DEFAULT_NSAMPLES	4000	// 8000 is one second
#define MIN_BUFSIZE			1000

static float fFrequencies[] = {
/* C0 */  16.35, 17.32, 18.35, 19.45, 20.6,  21.83, 23.12, 24.5, 25.96, 27.5, 29.14, 30.87,			// 0 - 11
/* C1 */  32.7,  34.65, 36.71, 38.89, 41.2,  43.65, 46.25, 49.0, 51.91, 55.0, 58.27, 61.74,			// 12-23
/* C2 */  65.41, 69.3,  73.42, 77.78, 82.41, 87.31, 92.5,  98.0,103.83,110.0,116.54,123.47,			// 24-35
/* C3 */ 130.81,138.59,146.83,155.56,164.81,174.61,185.0, 196.0,207.65,220.0,233.08,246.94,			// 36-47
/* C4 */ 261.63,277.18,293.66,311.13,329.63,349.23,369.99,392.0,415.30,440.0,466.16,493.88,			// 48-59
/* C5 */ 523.25,554.37,587.33,622.25,659.26,698.46,739.99,783.99,830.6,880.0,932.33,987.77,			// 60-71
/* C6 */1046.5,1108.73,1174.66,1244.51,1318.51,1396.91,1479.98,1567.98,1661.22,1760.0,1864.66,1975.53,
/* C7 */2093,2217.46,2349.32,2489.02,2637.02,2793.83,2959.96,3135.96,3322.44,3520.0,3729.31,3951.07
};

#define	NFREQUENCIES (sizeof(fFrequencies)/sizeof(float))
#define RECORD_TIME		6		// seconds to record for
#define SAMPLES_SEC		8000	// samples per second

// Buffers for the notes, plus 1 big buffer for recording.
static short *pFreqBufs[NFREQUENCIES] = {NULL};
static short nSamples[NFREQUENCIES] = { 0 };
static short iBigBuf[SAMPLES_SEC * RECORD_TIME];		
static long	 lBigBufSize = SAMPLES_SEC * RECORD_TIME;	// in samples

// output and input channel parameters
static	int		g_nSamplesPerSec = SAMPLES_SEC;
static	int		g_nBitsPerSample = 16;
static	HWAVEOUT	HWaveOut;				/* Handle of opened WAVE Out and In device */
static  HWAVEIN		HWaveIn;
static	WAVEFORMATEX WaveFormat;			/* WAVEFORMATEX structure for reading in the WAVE fmt chunk */
static  WAVEHDR	WaveHeader[NFREQUENCIES];	/* WAVEHDR structures - 1 per buffer */
static  WAVEHDR	WaveHeaderSilence;
static  WAVEHDR WaveHeaderIn;


static void SetupFormat( WAVEFORMATEX *wf );
static void FreeNoteBuffers(void);
static int CreateSound( short *pBuf, int nSamples, float fFreq );
int	InitializePlayback(void);
int InitializeNotes(void);
int PlayBuffer( short *piBuf, long lSamples );
int PlayNote( int iNote, int iDuration );	// duration in mS
static int WaitOnHeader( WAVEHDR *wh, char cDit );
int WaitForNotePlayback(int iNote);
void ClosePlayback(void);
int InitializeRecording(void);
int	RecordBuffer( short *piBuf, long lBufSize );
void CloseRecording(void);

#endif //HEADER

