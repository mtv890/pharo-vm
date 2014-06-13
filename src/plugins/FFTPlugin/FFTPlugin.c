/* Automatically generated by
	VMPluginCodeGenerator * VMMaker.oscog-EstebanLorenzano.768, VMMaker.oscog-eem.771 uuid: 1abbe9c7-13f0-4972-9779-d982037d7f17
   from
	FFTPlugin * VMMaker.oscog-EstebanLorenzano.768, VMMaker.oscog-eem.771 uuid: 1abbe9c7-13f0-4972-9779-d982037d7f17
 */
static char __buildInfo[] = "FFTPlugin * VMMaker.oscog-EstebanLorenzano.768, VMMaker.oscog-eem.771 uuid: 1abbe9c7-13f0-4972-9779-d982037d7f17 " __DATE__ ;



#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Default EXPORT macro that does nothing (see comment in sq.h): */
#define EXPORT(returnType) returnType

/* Do not include the entire sq.h file but just those parts needed. */
/*  The virtual machine proxy definition */
#include "sqVirtualMachine.h"
/* Configuration options */
#include "sqConfig.h"
/* Platform specific definitions */
#include "sqPlatformSpecific.h"

#define true 1
#define false 0
#define null 0  /* using 'null' because nil is predefined in Think C */
#ifdef SQUEAK_BUILTIN_PLUGIN
#undef EXPORT
// was #undef EXPORT(returnType) but screws NorCroft cc
#define EXPORT(returnType) static returnType
#endif

#include "sqMemoryAccess.h"


/*** Constants ***/


/*** Function Prototypes ***/
static float * checkedFloatPtrOf(sqInt oop);
static unsigned int * checkedWordPtrOf(sqInt oop);
static VirtualMachine * getInterpreter(void);
EXPORT(const char*) getModuleName(void);
static sqInt halt(void);
static sqInt loadFFTFrom(sqInt fftOop);
static sqInt msg(char *s);
static sqInt permuteData(void);
EXPORT(sqInt) primitiveFFTPermuteData(void);
EXPORT(sqInt) primitiveFFTScaleData(void);
EXPORT(sqInt) primitiveFFTTransformData(void);
static sqInt scaleData(void);
EXPORT(sqInt) setInterpreter(struct VirtualMachine*anInterpreter);
static sqInt transformData(sqInt forward);
static sqInt transformForward(sqInt forward);


/*** Variables ***/
static sqInt fftSize;
static float * imagData;
static sqInt imagDataSize;

#if !defined(SQUEAK_BUILTIN_PLUGIN)
static sqInt (*booleanValueOf)(sqInt obj);
static sqInt (*failed)(void);
static sqInt (*fetchIntegerofObject)(sqInt fieldIndex, sqInt objectPointer);
static sqInt (*fetchPointerofObject)(sqInt index, sqInt oop);
static void * (*firstIndexableField)(sqInt oop);
static sqInt (*isWords)(sqInt oop);
static sqInt (*pop)(sqInt nItems);
static sqInt (*slotSizeOf)(sqInt oop);
static sqInt (*stSizeOf)(sqInt oop);
static sqInt (*stackObjectValue)(sqInt offset);
static sqInt (*stackValue)(sqInt offset);
static sqInt (*success)(sqInt aBoolean);
#else /* !defined(SQUEAK_BUILTIN_PLUGIN) */
extern sqInt booleanValueOf(sqInt obj);
extern sqInt failed(void);
extern sqInt fetchIntegerofObject(sqInt fieldIndex, sqInt objectPointer);
extern sqInt fetchPointerofObject(sqInt index, sqInt oop);
extern void * firstIndexableField(sqInt oop);
extern sqInt isWords(sqInt oop);
extern sqInt pop(sqInt nItems);
extern sqInt slotSizeOf(sqInt oop);
extern sqInt stSizeOf(sqInt oop);
extern sqInt stackObjectValue(sqInt offset);
extern sqInt stackValue(sqInt offset);
extern sqInt success(sqInt aBoolean);
extern
#endif
struct VirtualMachine* interpreterProxy;
static const char *moduleName =
#ifdef SQUEAK_BUILTIN_PLUGIN
	"FFTPlugin * VMMaker.oscog-EstebanLorenzano.768, VMMaker.oscog-eem.771 (i)"
#else
	"FFTPlugin * VMMaker.oscog-EstebanLorenzano.768, VMMaker.oscog-eem.771 (e)"
#endif
;
static sqInt nu;
static unsigned int * permTable;
static sqInt permTableSize;
static float * realData;
static sqInt realDataSize;
static float * sinTable;
static sqInt sinTableSize;



/*	Return the first indexable word of oop which is assumed to be
	variableWordSubclass 
 */

static float *
checkedFloatPtrOf(sqInt oop)
{
	// FFTPlugin>>#checkedFloatPtrOf:
	success(isWords(oop));
	if (failed()) {
		return 0;
	}
	return ((float *) (firstIndexableField(oop)));
}


/*	Return the first indexable word of oop which is assumed to be
	variableWordSubclass 
 */

static unsigned int *
checkedWordPtrOf(sqInt oop)
{
	// FFTPlugin>>#checkedWordPtrOf:
	success(isWords(oop));
	return ((unsigned int *) (firstIndexableField(oop)));
}


/*	Note: This is coded so that plugins can be run from Squeak. */

static VirtualMachine *
getInterpreter(void)
{
	// InterpreterPlugin>>#getInterpreter
	return interpreterProxy;
}


/*	Note: This is hardcoded so it can be run from Squeak.
	The module name is used for validating a module *after*
	it is loaded to check if it does really contain the module
	we're thinking it contains. This is important! */

EXPORT(const char*)
getModuleName(void)
{
	// InterpreterPlugin>>#getModuleName
	return moduleName;
}

static sqInt
halt(void)
{
	// InterpreterPlugin>>#halt
	;
	return 0;
}

static sqInt
loadFFTFrom(sqInt fftOop)
{
	// FFTPlugin>>#loadFFTFrom:
    sqInt oop;

	success((slotSizeOf(fftOop)) >= 6);
	if (failed()) {
		return 0;
	}
	nu = fetchIntegerofObject(0, fftOop);
	fftSize = fetchIntegerofObject(1, fftOop);
	oop = fetchPointerofObject(2, fftOop);
	sinTableSize = stSizeOf(oop);
	/* begin checkedFloatPtrOf: */
	success(isWords(oop));
	if (failed()) {
		sinTable = 0;
		goto l1;
	}
	sinTable = ((float *) (firstIndexableField(oop)));
l1:	/* end checkedFloatPtrOf: */;
	oop = fetchPointerofObject(3, fftOop);
	permTableSize = stSizeOf(oop);
	/* begin checkedWordPtrOf: */
	success(isWords(oop));
	permTable = ((unsigned int *) (firstIndexableField(oop)));
	oop = fetchPointerofObject(4, fftOop);
	realDataSize = stSizeOf(oop);
	/* begin checkedFloatPtrOf: */
	success(isWords(oop));
	if (failed()) {
		realData = 0;
		goto l2;
	}
	realData = ((float *) (firstIndexableField(oop)));
l2:	/* end checkedFloatPtrOf: */;
	oop = fetchPointerofObject(5, fftOop);
	imagDataSize = stSizeOf(oop);
	/* begin checkedFloatPtrOf: */
	success(isWords(oop));
	if (failed()) {
		imagData = 0;
		goto l3;
	}
	imagData = ((float *) (firstIndexableField(oop)));
l3:	/* end checkedFloatPtrOf: */;
	success((((((1 << nu) == fftSize) && (((((sqInt) fftSize >> 2)) + 1) == sinTableSize)) && (fftSize == realDataSize)) && (fftSize == imagDataSize)) && (realDataSize == imagDataSize));
	return (failed()) == 0;
}

static sqInt
msg(char *s)
{
	// InterpreterPlugin>>#msg:
	fprintf(stderr, "\n%s: %s", moduleName, s);
	return 0;
}

static sqInt
permuteData(void)
{
	// FFTPlugin>>#permuteData
    sqInt a;
    sqInt b;
    sqInt end;
    sqInt i;
    float  tmp;

	i = 0;
	end = permTableSize;
	while (i < end) {
a = (permTable[i]) - 1;
		b = (permTable[i + 1]) - 1;
		if (!((a < realDataSize)
			 && (b < realDataSize))) {
			return success(0);
		}
		tmp = realData[a];
		realData[a] = (realData[b]);
		realData[b] = tmp;
		tmp = imagData[a];
		imagData[a] = (imagData[b]);
		imagData[b] = tmp;
		i += 2;
	}
}

EXPORT(sqInt)
primitiveFFTPermuteData(void)
{
	// FFTPlugin>>#primitiveFFTPermuteData
    sqInt rcvr;

	rcvr = stackObjectValue(0);
	if (!(loadFFTFrom(rcvr))) {
		return null;
	}
	permuteData();
	if (failed()) {

		/* permuteData went wrong. Do the permutation again -- this will restore the original order */

permuteData();
	}
}

EXPORT(sqInt)
primitiveFFTScaleData(void)
{
	// FFTPlugin>>#primitiveFFTScaleData
    sqInt rcvr;

	rcvr = stackObjectValue(0);
	if (!(loadFFTFrom(rcvr))) {
		return null;
	}
	scaleData();
}

EXPORT(sqInt)
primitiveFFTTransformData(void)
{
	// FFTPlugin>>#primitiveFFTTransformData
    sqInt fftScale;
    sqInt fftSize2;
    sqInt fftSize4;
    sqInt forward;
    sqInt i;
    sqInt ii;
    float  imagT;
    float  imagU;
    sqInt ip;
    sqInt j;
    sqInt lev;
    sqInt lev1;
    sqInt level;
    sqInt rcvr;
    float  realT;
    float  realU;
    sqInt theta;

	forward = booleanValueOf(stackValue(0));
	rcvr = stackObjectValue(1);
	if (!(loadFFTFrom(rcvr))) {
		return null;
	}
	/* begin transformData: */
	permuteData();
	if (failed()) {

		/* permuteData went wrong. Do the permutation again -- this will restore the original order */

permuteData();
		null;
		goto l1;
	}
	/* begin transformForward: */
	fftSize2 = ((sqInt) fftSize >> 1);
	fftSize4 = ((sqInt) fftSize >> 2);
	for (level = 1; level <= nu; level += 1) {
		lev = 1 << level;
		lev1 = ((sqInt) lev >> 1);
		fftScale = fftSize / lev;
		for (j = 1; j <= lev1; j += 1) {

			/* pi * (j-1) / lev1 mapped onto 0..n/2 */

theta = (j - 1) * fftScale;
			if (theta < fftSize4) {

				/* Compute U, the complex multiplier for each level */


				/* Compute U, the complex multiplier for each level */

realU = sinTable[(sinTableSize - theta) - 1];
				imagU = sinTable[theta];
			}
			else {
realU = 0.0 - (sinTable[theta - fftSize4]);
				imagU = sinTable[fftSize2 - theta];
			}
			if (!forward) {
imagU = 0.0 - imagU;
			}
			i = j;
			while (i <= fftSize) {
				ip = (i + lev1) - 1;
				ii = i - 1;
				realT = ((realData[ip]) * realU) - ((imagData[ip]) * imagU);
				imagT = ((realData[ip]) * imagU) + ((imagData[ip]) * realU);
				realData[ip] = ((realData[ii]) - realT);
				imagData[ip] = ((imagData[ii]) - imagT);
				realData[ii] = ((realData[ii]) + realT);
				imagData[ii] = ((imagData[ii]) + imagT);
				i += lev;
			}
		}
	}
	if (!forward) {
scaleData();
	}
l1:	/* end transformData: */;
	if (!(failed())) {
		pop(1);
	}
}


/*	Scale all elements by 1/n when doing inverse */

static sqInt
scaleData(void)
{
	// FFTPlugin>>#scaleData
    sqInt i;
    float  realN;

	if (fftSize <= 1) {
		return null;
	}
	realN = ((float) (1.0 / (((double) fftSize))));
	for (i = 0; i < fftSize; i += 1) {
		realData[i] = ((realData[i]) * realN);
		imagData[i] = ((imagData[i]) * realN);
	}
}


/*	Note: This is coded so that it can be run in Squeak. */

EXPORT(sqInt)
setInterpreter(struct VirtualMachine*anInterpreter)
{
	// InterpreterPlugin>>#setInterpreter:
    sqInt ok;

	interpreterProxy = anInterpreter;
	ok = ((interpreterProxy->majorVersion()) == (VM_PROXY_MAJOR))
	 && ((interpreterProxy->minorVersion()) >= (VM_PROXY_MINOR));
	if (ok) {

#if !defined(SQUEAK_BUILTIN_PLUGIN)
		booleanValueOf = interpreterProxy->booleanValueOf;
		failed = interpreterProxy->failed;
		fetchIntegerofObject = interpreterProxy->fetchIntegerofObject;
		fetchPointerofObject = interpreterProxy->fetchPointerofObject;
		firstIndexableField = interpreterProxy->firstIndexableField;
		isWords = interpreterProxy->isWords;
		pop = interpreterProxy->pop;
		slotSizeOf = interpreterProxy->slotSizeOf;
		stSizeOf = interpreterProxy->stSizeOf;
		stackObjectValue = interpreterProxy->stackObjectValue;
		stackValue = interpreterProxy->stackValue;
		success = interpreterProxy->success;
#endif /* !defined(SQUEAK_BUILTIN_PLUGIN) */
	}
	return ok;
}

static sqInt
transformData(sqInt forward)
{
	// FFTPlugin>>#transformData:
    sqInt fftScale;
    sqInt fftSize2;
    sqInt fftSize4;
    sqInt i;
    sqInt ii;
    float  imagT;
    float  imagU;
    sqInt ip;
    sqInt j;
    sqInt lev;
    sqInt lev1;
    sqInt level;
    float  realT;
    float  realU;
    sqInt theta;

	permuteData();
	if (failed()) {

		/* permuteData went wrong. Do the permutation again -- this will restore the original order */

permuteData();
		return null;
	}
	/* begin transformForward: */
	fftSize2 = ((sqInt) fftSize >> 1);
	fftSize4 = ((sqInt) fftSize >> 2);
	for (level = 1; level <= nu; level += 1) {
		lev = 1 << level;
		lev1 = ((sqInt) lev >> 1);
		fftScale = fftSize / lev;
		for (j = 1; j <= lev1; j += 1) {

			/* pi * (j-1) / lev1 mapped onto 0..n/2 */

theta = (j - 1) * fftScale;
			if (theta < fftSize4) {

				/* Compute U, the complex multiplier for each level */


				/* Compute U, the complex multiplier for each level */

realU = sinTable[(sinTableSize - theta) - 1];
				imagU = sinTable[theta];
			}
			else {
realU = 0.0 - (sinTable[theta - fftSize4]);
				imagU = sinTable[fftSize2 - theta];
			}
			if (!forward) {
imagU = 0.0 - imagU;
			}
			i = j;
			while (i <= fftSize) {
				ip = (i + lev1) - 1;
				ii = i - 1;
				realT = ((realData[ip]) * realU) - ((imagData[ip]) * imagU);
				imagT = ((realData[ip]) * imagU) + ((imagData[ip]) * realU);
				realData[ip] = ((realData[ii]) - realT);
				imagData[ip] = ((imagData[ii]) - imagT);
				realData[ii] = ((realData[ii]) + realT);
				imagData[ii] = ((imagData[ii]) + imagT);
				i += lev;
			}
		}
	}
	if (!forward) {
scaleData();
	}
}

static sqInt
transformForward(sqInt forward)
{
	// FFTPlugin>>#transformForward:
    sqInt fftScale;
    sqInt fftSize2;
    sqInt fftSize4;
    sqInt i;
    sqInt ii;
    float  imagT;
    float  imagU;
    sqInt ip;
    sqInt j;
    sqInt lev;
    sqInt lev1;
    sqInt level;
    float  realT;
    float  realU;
    sqInt theta;

	fftSize2 = ((sqInt) fftSize >> 1);
	fftSize4 = ((sqInt) fftSize >> 2);
	for (level = 1; level <= nu; level += 1) {
		lev = 1 << level;
		lev1 = ((sqInt) lev >> 1);
		fftScale = fftSize / lev;
		for (j = 1; j <= lev1; j += 1) {

			/* pi * (j-1) / lev1 mapped onto 0..n/2 */

theta = (j - 1) * fftScale;
			if (theta < fftSize4) {

				/* Compute U, the complex multiplier for each level */


				/* Compute U, the complex multiplier for each level */

realU = sinTable[(sinTableSize - theta) - 1];
				imagU = sinTable[theta];
			}
			else {
realU = 0.0 - (sinTable[theta - fftSize4]);
				imagU = sinTable[fftSize2 - theta];
			}
			if (!forward) {
imagU = 0.0 - imagU;
			}
			i = j;
			while (i <= fftSize) {
				ip = (i + lev1) - 1;
				ii = i - 1;
				realT = ((realData[ip]) * realU) - ((imagData[ip]) * imagU);
				imagT = ((realData[ip]) * imagU) + ((imagData[ip]) * realU);
				realData[ip] = ((realData[ii]) - realT);
				imagData[ip] = ((imagData[ii]) - imagT);
				realData[ii] = ((realData[ii]) + realT);
				imagData[ii] = ((imagData[ii]) + imagT);
				i += lev;
			}
		}
	}
}


#ifdef SQUEAK_BUILTIN_PLUGIN

void* FFTPlugin_exports[][3] = {
	{"FFTPlugin", "getModuleName", (void*)getModuleName},
	{"FFTPlugin", "primitiveFFTPermuteData\000\002", (void*)primitiveFFTPermuteData},
	{"FFTPlugin", "primitiveFFTScaleData\000\002", (void*)primitiveFFTScaleData},
	{"FFTPlugin", "primitiveFFTTransformData\000\002", (void*)primitiveFFTTransformData},
	{"FFTPlugin", "setInterpreter", (void*)setInterpreter},
	{NULL, NULL, NULL}
};

#else /* ifdef SQ_BUILTIN_PLUGIN */

signed char primitiveFFTPermuteDataAccessorDepth = 2;
signed char primitiveFFTScaleDataAccessorDepth = 2;
signed char primitiveFFTTransformDataAccessorDepth = 2;

#endif /* ifdef SQ_BUILTIN_PLUGIN */
