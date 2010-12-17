/*
 *  sqMacUnixInterfaceSound.c
 *  SqueakVMForCarbon
 *
 *  Created by John M McIntosh on 2/3/05.
 *  Copyright 2005 __MyCompanyName__. All rights reserved.
 *
 */

#include "sqMacUnixInterfaceSound.h"

#include "sq.h"
#include "SoundPlugin.h"
#include "SqModule.h"
#include "SqSound.h"

extern int sound_Stop(void);
extern void clearDeviceCache();   /* sqMacDeviceList.c */


int soundInit(void)
{
  return 1;
}


int soundShutdown(void)
{
  sound_StopRecording();
  clearDeviceCache();
  return 1;
}


/* output */

int snd_AvailableSpace(void)
{
  return sound_AvailableSpace();
}

sqInt snd_InsertSamplesFromLeadTime(sqInt frameCount, void * srcBufPtr, sqInt samplesOfLeadTime)
{
  return sound_InsertSamplesFromLeadTime(frameCount, (int)srcBufPtr, samplesOfLeadTime);
}

sqInt snd_PlaySamplesFromAtLength(sqInt frameCount, void *srcBufPtr, sqInt startIndex)
{
  return sound_PlaySamplesFromAtLength(frameCount, (int) srcBufPtr, startIndex);
}

int snd_PlaySilence(void)
{
  return sound_PlaySilence();
}

int snd_Start(int frameCount, int samplesPerSec, int stereo, int semaIndex)
{
  return sound_Start(frameCount, samplesPerSec, stereo, semaIndex);
}

int snd_Stop(void)
{
  return sound_Stop();
}

/* input */

int snd_StartRecording(int desiredSamplesPerSec, int stereo, int semaIndex)
{
  return sound_StartRecording(desiredSamplesPerSec, stereo, semaIndex);
}

int snd_StopRecording(void)
{
  return sound_StopRecording();
}

double snd_GetRecordingSampleRate(void)
{
  return sound_GetRecordingSampleRate();
}

sqInt snd_RecordSamplesIntoAtLength(void * buf, sqInt startSliceIndex, sqInt bufferSizeInBytes)
{
  return sound_RecordSamplesIntoAtLength((int)buf, startSliceIndex, bufferSizeInBytes);
}

/* Acoustic echo-cancellation (AEC) is not supported on Macintosh yet. */
int snd_EnableAEC(int trueOrFalse)
{
	if (trueOrFalse) return PrimErrUnsupported;
	else return 0; /* success */
}


/* Acoustic echo-cancellation (AEC) is not supported on Macintosh yet. */
int snd_SupportsAEC()
{
	return 0; /* nope */
}



/* mixer */

void snd_Volume(double *left, double *right)	{ 
	sound_Volume(left, right); }
void snd_SetVolume(double left, double right)	{ 
	sound_SetVolume(left, right); }
void snd_SetRecordLevel(sqInt level)		{ 
	 sound_SetRecordLevel(level); }
int  snd_GetRecordLevel(void)		{	// howard.stearns@qwaq.com October 24 2008
	return sound_GetRecordLevel(); }

	
	