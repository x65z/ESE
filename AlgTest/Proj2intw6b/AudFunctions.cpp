//////////////////////////////////
//Audio Starts

//Project 2 Week 1 - Zack Henkusens
//Audio recording and Playback

#ifndef AUD
# define AUD

#include "Header.h" 

int	 Errorp( const char *szFormat, ... )
{
    char		szBuf[300];
	char		*ptr = szBuf;
    va_list		arg_ptr;
    int         i;
	int			iMode = MB_OK|MB_SETFOREGROUND;

    /* build a buffer with the message */
    va_start( arg_ptr, szFormat );
    i = vsprintf( szBuf, szFormat, arg_ptr );
    va_end( arg_ptr );
	// allow the first character to customize the box 
	if ( *ptr == '!' ) {
		iMode |= MB_ICONEXCLAMATION;
		++ptr;
	} else 
	if ( *ptr == '@' ) {
		iMode |= MB_ICONINFORMATION;
		++ptr;
	} else 
	if ( *ptr == '?' ) {
		iMode |= MB_ICONQUESTION;
		++ptr;
	} else 
	if ( *ptr == '#' ) {
		iMode |= MB_ICONSTOP;
		++ptr;
	} 

	// display the box
    MessageBox( NULL, ptr, "NOTE", iMode);
    return(i);
}




/* SetupFormat() initializes a WAVEFORMATEX structure to the required 
 *				 parameters (sample rate, bits per sample, etc)
 */
static void SetupFormat( WAVEFORMATEX *wf )
{	
	wf->wFormatTag = WAVE_FORMAT_PCM;
	wf->nChannels = 1;
	wf->nSamplesPerSec = g_nSamplesPerSec;
	wf->wBitsPerSample = g_nBitsPerSample;
	wf->nBlockAlign = wf->nChannels * (wf->wBitsPerSample/8);
	wf->nAvgBytesPerSec = wf->nSamplesPerSec * wf->nBlockAlign;
	wf->cbSize = 0;
	return;
}

/* FreeNoteBuffers() releases the buffers holding the set of all notes.  
  */
static void FreeNoteBuffers(void)
{
	int	i;
	for ( i=0; i < NFREQUENCIES; ++i ) {
		if ( pFreqBufs[i] ) free( pFreqBufs[i] );
	}
	return;
}

/* CreateSound: This routine fills a buffer with a tone at a specified 
 *				frequency.  
 *				TODO: add some harmonics to make it sound nice?
 *				TODO: use different volumes?
 *
 * Returns the index of the last 0 in the buffer, This can be used by the caller
 * to ensure that the buffer ends on a 0 crossing, handy for splicing. TODO: Should probably
 * make sure it's a 0 crossing that complete a cycle. 
 */
static int CreateSound( short *pBuf, int nSamples, float fFreq )
{
	int		i, iLastZero;
	double	lfTime, lfTimeStep, lfValue, lfAmp, lfOmega;

	lfTime = 0.0;
	lfTimeStep = (double)1.0 / (float)g_nSamplesPerSec;

	// calculate 2*PI*f
	lfOmega = 2.0 * 3.14159 * fFreq;

	// make the maximum signal 75% of the range
	switch ( g_nBitsPerSample ) {
		case 16 : lfAmp = 65536 * .75; break;
		case 8  : lfAmp = 256 * .75; break;
		default : 
			Errorp("Bad playback sample size. Using 8 bits." );
			lfAmp = 256.0 * .75;
	}
	lfAmp /= 2.0;	// making it signed so half range. 

	iLastZero = 0;
	for (i=0; i < nSamples; ++i) {
		// TODO for every point in the curve....init to first curve, then add rest. 
		lfValue = (float)(lfAmp*sin(lfOmega*lfTime));
		if ( lfValue >= 0.0 ) 
			*pBuf = (short)(lfValue + 0.5);
		else
			*pBuf = (short)(lfValue - 0.5);
		if ( labs(*pBuf) < 320 ) iLastZero = i;	// close enough to 0
		++pBuf;
		lfTime += lfTimeStep;
	}
	return(iLastZero);
}


/* Errorp() : Windows style popup error. Called like a printf().
 * First character may be used to select an icon to appear.
 */



/* InitializePlayback()
 */

int	InitializePlayback(void)
{
	int		rc;

	// set up the format structure, needed for playback (and recording)
	SetupFormat( &WaveFormat );

	// open the playback device
	rc = waveOutOpen(&HWaveOut, WAVE_MAPPER, &WaveFormat, (DWORD)NULL, 0, CALLBACK_NULL);
	if ( rc ) {
		Errorp("Unable to open Output sound Device! Error %x.", rc);
		return(0);
	}

	return(1);
}

/* Initializ es() : create buffers for however many notes 
 * in the score.  
 */
int InitializeNotes(void)
{
	int		nFreqs, i;
	int		iLastZero;
	MMRESULT rc;

	// determine the number of buffers required (one per frequency)
	nFreqs = NFREQUENCIES;
	
	// for each buffer, determine space and allocate it, then fill it
	for ( i=0; i < nFreqs; ++i ) {
		// how many samples make up 1 minimum note duration? 
		nSamples[i] = DEFAULT_NSAMPLES;

		pFreqBufs[i] = (short *)malloc( nSamples[i] * sizeof(short) );
		if ( pFreqBufs[i] == NULL ) {
			// out of space
			Errorp("Unable to allocate space for note %d %d. Playback disabled.", 
				i, nSamples[i] );
			FreeNoteBuffers();
			return(0);
		}

		// fill the buffer with a note of chosen frequency
		iLastZero = CreateSound( pFreqBufs[i], nSamples[i], fFrequencies[i] );

		#ifdef NEVER
		// shorten the buffer so that it ends on a zero crossing, to make it 
		// sound better when played. But not too short.
		if ( iLastZero > MIN_BUFSIZE ) {
			nSamples[i] = iLastZero + 1;
			// TODO - free old buffer and create new. realloc() not efficient. 
			// realloc(pFreqBufs[i], nSamples[i]*sizeof(short) );
		}
		#endif
	}

	if ( HWaveOut == NULL ) 
		InitializePlayback();
	
	// prepare the buffer headrs for use later on
	for ( i=0; i < nFreqs; ++i ) {
		WaveHeader[i].lpData = (char *)pFreqBufs[i];
		WaveHeader[i].dwBufferLength = nSamples[i]*sizeof(short);
		rc = waveOutPrepareHeader(HWaveOut, &WaveHeader[i], sizeof(WAVEHDR));
		if ( rc ) {
			Errorp( "Failed preparing WAVEHDR, error 0x%x.", rc);
			return(0);
		}
	}

#ifdef NEVER
	// Prepare a bit of silence. TODO check for errors. 
	WaveHeaderSilence.lpData = (char *)calloc( DEFAULT_NSAMPLES * sizeof(short),1 );
	WaveHeaderSilence.dwBufferLength = DEFAULT_NSAMPLES*sizeof(short);
	WaveHeaderSilence.dwFlags &= ~(WHDR_BEGINLOOP|WHDR_ENDLOOP);
	rc = waveOutPrepareHeader(HWaveOut, &WaveHeaderSilence, sizeof(WAVEHDR));
	if ( rc ) {
		Errorp( "Failed preparing WAVEHDR for silence, error 0x%x.", rc);
		return(0);
	}
#endif

	return(1);
}


/* PlayBuffer()
 */
int PlayBuffer( short *piBuf, long lSamples )
{
	static	WAVEFORMATEX WaveFormat;	/* WAVEFORMATEX structure for reading in the WAVE fmt chunk */
	static  WAVEHDR	WaveHeader;			/* WAVEHDR structure for this buffer */
	MMRESULT	mmErr;
	int		rc;

	// stop previous note (just in case)
	waveOutReset(HWaveOut);   // is this good?

	// get the header ready for playback
	WaveHeader.lpData = (char *)piBuf;
	WaveHeader.dwBufferLength = lSamples*sizeof(short);
	rc = waveOutPrepareHeader(HWaveOut, &WaveHeader, sizeof(WAVEHDR));
	if ( rc ) {
		Errorp( "Failed preparing WAVEHDR, error 0x%x.", rc);
		return(0);
	}
	WaveHeader.dwFlags &= ~(WHDR_BEGINLOOP|WHDR_ENDLOOP);

	// play the buffer. This is NON-blocking.
	mmErr = waveOutWrite(HWaveOut, &WaveHeader, sizeof(WAVEHDR));
	if ( mmErr != MMSYSERR_NOERROR ) {
		char	szErrBuf[150];
		waveOutGetErrorText(mmErr, szErrBuf, sizeof(szErrBuf) );
		Errorp("Error 0x%x writing to playback device. %s", mmErr, szErrBuf );
		return(0);
	}

	// wait for completion
	rc = WaitOnHeader(&WaveHeader, 0);

	// give back resources
	waveOutUnprepareHeader(HWaveOut, &WaveHeader, sizeof(WAVEHDR));

	return(rc);
}

/* PlayNote() : the specified note is played for the specified duration. 
 *
 * Buffers of all expected frequencies already exist. 
 * If less than a buffer is required, the length is shortened. 
 * If more than a buffer is required, the buffer is repeated. 
 * PROBLEM: Only want to issue one write. so stuck with a multiple. 
 */
int PlayNote( int iNote, int iDuration )	// duration in mS
{
	MMRESULT	mmErr;
	int			iBuffers, iBufSamples;
	long		lSamples;

	if ( iNote < 0 || iNote >= NFREQUENCIES ) return(0);

	// figure out how much to play. For now only 2 choices - part of 1 buffer 
	// or repetitions of full buffer. 
	lSamples = (int)(((double)iDuration * (double)g_nSamplesPerSec)/1000. + .9);
	if ( lSamples > nSamples[iNote] ) {
		// need to repeat the buffer. Figure out how many times, then shorten the buffer 
		// make the total length <= desired. 
		WaveHeader[iNote].dwLoops = iBuffers = (lSamples+nSamples[iNote]-1)/nSamples[iNote];
		iBufSamples = lSamples / iBuffers;
		WaveHeader[iNote].dwBufferLength = iBufSamples * sizeof(short);
		WaveHeader[iNote].dwFlags |= (WHDR_BEGINLOOP|WHDR_ENDLOOP);
	} else {
		// need to play just part of the buffer
		WaveHeader[iNote].dwBufferLength = lSamples * sizeof(short);
		WaveHeader[iNote].dwFlags &= ~(WHDR_BEGINLOOP|WHDR_ENDLOOP);
	}
//	iBufTime = (nSamples[i]*1000) / g_nSamplesPerSec;
//	iBuffers = iDuration / iBufTime; 

	// stop previous note (just in case)
	// waveOutReset(HWaveOut);   // is this good?

	// play the note. This is NON-blocking.
	mmErr = waveOutWrite(HWaveOut, &WaveHeader[iNote], sizeof(WAVEHDR));
	if ( mmErr != MMSYSERR_NOERROR ) {
		char	szErrBuf[150];
		waveOutGetErrorText(mmErr, szErrBuf, sizeof(szErrBuf) );
		Errorp("Error 0x%x writing to playback device. %s", mmErr, szErrBuf );
		return(-1);
	}

#ifdef NEVER
	// play some silence after the note to eiminate "clicks"
	mmErr = waveOutWrite(HWaveOut, &WaveHeaderSilence, sizeof(WAVEHDR));
	if ( mmErr != MMSYSERR_NOERROR ) {
		char	szErrBuf[150];
		waveOutGetErrorText(mmErr, szErrBuf, sizeof(szErrBuf) );
		Errorp("Error 0x%x writing silence to playback device. %s", mmErr, szErrBuf );
		return(-1);
	}
#endif
	 
	return(0);
}


static int WaitOnHeader( WAVEHDR *wh, char cDit )
{
	long	lTime = 0;

	// wait for whatever is being played, to finish. Quit after 10 seconds.
	for ( ; ; ) {
		if ( wh->dwFlags & WHDR_DONE ) return(1);
		// idle for a bit so as to free CPU
		Sleep(100L);
		lTime += 100; 
		if ( lTime >= 10000 ) return(0);  // timeout
		if ( cDit ) printf("%c", cDit);
	}
}

/* WaitForNotePlayback() : wait for the playback of specified note to finish. 
 * If note is playing more than once, this will return the current one - bit of a hole.
 */
int WaitForNotePlayback(int iNote)
{
	// wait for whatever is being played, to finish. Quit after 10 seconds.
	return ( WaitOnHeader( &WaveHeader[iNote],0 ) );
}

void ClosePlayback(void)
{
	int		i;

	for ( i=0; i < NFREQUENCIES; ++i ) {
		waveOutUnprepareHeader(HWaveOut, &WaveHeader[i], sizeof(WAVEHDR));
	}

	// close the playback device
	waveOutClose(HWaveOut);
	
	return;
}

int InitializeRecording(void)
{
	MMRESULT rc;

	// set up the format structure, needed for recording.
	SetupFormat( &WaveFormat );

	// open the recording device
	rc = waveInOpen(&HWaveIn, WAVE_MAPPER, &WaveFormat, (DWORD)NULL, 0, CALLBACK_NULL);
	if ( rc ) {
		Errorp("Unable to open Input sound Device! Error %x.", rc);
		return(0);
	}

	// prepare the buffer header for use later on
	WaveHeaderIn.lpData = (char *)iBigBuf;
	WaveHeaderIn.dwBufferLength = lBigBufSize*sizeof(short);
	rc = waveInPrepareHeader(HWaveIn, &WaveHeaderIn, sizeof(WAVEHDR));
	if ( rc ) {
		Errorp( "Failed preparing input WAVEHDR, error 0x%x.", rc);
		return(0);
	}

	return(1);

}

int	RecordBuffer( short *piBuf, long lBufSize )
{
	static	WAVEFORMATEX WaveFormat;	/* WAVEFORMATEX structure for reading in the WAVE fmt chunk */
	static  WAVEHDR	WaveHeader;			/* WAVEHDR structure for this buffer */
	MMRESULT	mmErr;
	int		rc;

	printf("Recording now....." );

	// stop previous recording (just in case)
	waveInReset(HWaveIn);   // is this good?

	// get the header ready for recording.  This should not be needed here AND in init.
	WaveHeader.lpData = (char *)piBuf;
	WaveHeader.dwBufferLength = lBufSize*sizeof(short);
	rc = waveInPrepareHeader(HWaveIn, &WaveHeader, sizeof(WAVEHDR));
	if ( rc ) {
		Errorp( "Failed preparing WAVEHDR, error 0x%x.", rc);
		return(0);
	}
	WaveHeader.dwFlags &= ~(WHDR_BEGINLOOP|WHDR_ENDLOOP);

	// Give the buffer to the recording device to fill.
	mmErr = waveInAddBuffer(HWaveIn, &WaveHeader, sizeof(WAVEHDR) ); 
	if ( mmErr != MMSYSERR_NOERROR ) {
		char	szErrBuf[150];
		waveOutGetErrorText(mmErr, szErrBuf, sizeof(szErrBuf) );
		Errorp("Error 0x%x writing to playback device. %s", mmErr, szErrBuf );
		return(0);
	}

	// Record the buffer. This is NON-blocking.
	mmErr = waveInStart(HWaveIn); 
	if ( mmErr != MMSYSERR_NOERROR ) {
		char	szErrBuf[150];
		waveOutGetErrorText(mmErr, szErrBuf, sizeof(szErrBuf) );
		Errorp("Error 0x%x writing to playback device. %s", mmErr, szErrBuf );
		return(0);
	}

	// wait for completion
	rc = WaitOnHeader(&WaveHeader, '.');

	// probably not necessary
	waveInStop(HWaveIn);

	return(rc);
}

void CloseRecording(void)
{
	waveInUnprepareHeader(HWaveIn, &WaveHeaderIn, sizeof(WAVEHDR));

	// close the playback device
	waveInClose(HWaveIn);
	
	return;
}
#endif //AUD