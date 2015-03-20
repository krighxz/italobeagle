/**
 * Copyright (c) 2014,2015 Enzien Audio, Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, and/or
 * sublicense copies of the Software, strictly on a non-commercial basis,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * DO NOT MODIFY. THIS CODE IS MACHINE GENERATED BY THE SECTION6 HEAVY COMPILER.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "Utils.h" 

#if !HV_MSVC
#pragma mark - Heavy Table
#endif

#ifndef _HEAVY_TABLE_H_
#define _HEAVY_TABLE_H_

typedef struct HvTable HvTable;

/**
 * Resizes the table to the given length. Length must be positive.
 * Existing contents are copied to the new table. Remaining space is cleared.
 */
HV_EXPORT void hv_table_resize(HvTable *o, hv_uint32_t newLength);

/** Returns a pointer to the raw buffer backing this table. DO NOT free it. */
HV_EXPORT float *hv_table_getBuffer(HvTable *o);

/** Returns the length of this table in samples. */
HV_EXPORT int hv_table_getLength(HvTable *o);

#endif // _HEAVY_TABLE_H_



#if !HV_MSVC
#pragma mark - Heavy Message
#endif

#ifndef _HEAVY_MESSAGE_H_
#define _HEAVY_MESSAGE_H_

HV_EXPORT typedef struct HvMessage HvMessage;

/** Returns the byte size of a HvMessage with a number of elements on the heap. */
HV_EXPORT hv_size_t hv_msg_getByteSize(int numElements);

/** Create a HvMessage on the stack with a number of elements. This message does MUST NOT be freed. */
HV_EXPORT HV_FORCE_INLINE HvMessage *hv_msg_onStack(hv_uint32_t numElements) {
  return (HvMessage *) hv_alloca(hv_msg_getByteSize(numElements)); // this will not work until Utils.h is included
}

/** Initialise a message with the number of elements and a timestamp (in milliseconds). */
HV_EXPORT void hv_msg_init(HvMessage *m, int numElements, double timestamp);

/** Returns the number of elements in this message. */
HV_EXPORT int hv_msg_getNumElements(HvMessage *m);

/** Returns the time at which this message exists (in milliseconds). */
HV_EXPORT hv_uint32_t hv_msg_getTimestamp(HvMessage *m);

/** Set the time at which this message should be executed (in milliseconds). */
HV_EXPORT void hv_msg_setTimestamp(HvMessage *m, double timestamp);

/** Returns true of the indexed element is a bang. False otherwise. Index is not bounds checked. */
HV_EXPORT bool hv_msg_isBang(HvMessage *m, int i);

/** Sets the indexed element to a bang. Index is not bounds checked. */
HV_EXPORT void hv_msg_setBang(HvMessage *m, int i);

/** Returns true of the indexed element is a float. False otherwise. Index is not bounds checked. */
HV_EXPORT bool hv_msg_isFloat(HvMessage *m, int i);

/** Returns the indexed element as a float value. Index is not bounds checked. */
HV_EXPORT float hv_msg_getFloat(HvMessage *m, int i);

/** Sets the indexed element to float value. Index is not bounds checked. */
HV_EXPORT void hv_msg_setFloat(HvMessage *m, int i, float f);

/** Returns true of the indexed element is a symbol. False otherwise. Index is not bounds checked. */
HV_EXPORT bool hv_msg_isSymbol(HvMessage *m, int i);

/** Returns the indexed element as a symbol value. Index is not bounds checked. */
HV_EXPORT char *hv_msg_getSymbol(HvMessage *m, int i);

/** Sets the indexed element to symbol value. Index is not bounds checked. */
HV_EXPORT void hv_msg_setSymbol(HvMessage *m, int i, const char *s);

/**
 * Returns true if the message has the given format, in number of elements and type. False otherwise.
 * Valid element types are:
 * 'b': bang
 * 'f': float
 * 's': symbol
 *
 * For example, a message with three floats would have a format of "fff". A single bang is "b".
 * A message with two symbols is "ss". These types can be mixed and matched in any way.
 */
HV_EXPORT bool hv_msg_hasFormat(HvMessage *m, const char *fmt);

/**
 * Returns a basic string representation of the message.
 * The character array MUST be deallocated by the caller.
 */
HV_EXPORT char *hv_msg_toString(HvMessage *msg);

/** Copy a message onto the stack. The message persists. */
HV_EXPORT HvMessage *hv_msg_copy(HvMessage *m);

/** Free a copied message. */
HV_EXPORT void hv_msg_free(HvMessage *m);

#endif // _HEAVY_MESSAGE_H_



#if !HV_MSVC
#pragma mark - Heavy Patch
#endif

#ifndef _HEAVY_BEAGLESEQUENCER_H_
#define _HEAVY_BEAGLESEQUENCER_H_

typedef struct Hv_beagleSequencer Hv_beagleSequencer;

/**
 * Creates a new patch instance.
 * Sample rate should be positive and in Hertz.
 * Input and output channels should be non-negative.
 */
HV_EXPORT Hv_beagleSequencer *hv_beagleSequencer_new(double sampleRate);

/** Frees a patch instance. */
HV_EXPORT void hv_beagleSequencer_free(Hv_beagleSequencer *c);

/** Processes one block of samples for a patch instance. The buffer format is an array of arrays. */
HV_EXPORT int hv_beagleSequencer_process(Hv_beagleSequencer *c, float **const inputBuffers, float **const outputBuffers, int n4);

/** Processes one block of samples for a patch instance. The buffer format is an uninterleaved array of channels. */
HV_EXPORT int hv_beagleSequencer_process_inline(Hv_beagleSequencer *c, float *const inputBuffers, float *const outputBuffers, int n4);

#endif // _HEAVY_BEAGLESEQUENCER_H_



#if !HV_MSVC
#pragma mark - Heavy Common
#endif

#ifndef _HEAVY_COMMON_H_
#define _HEAVY_COMMON_H_

typedef void Heavy;

/** Returns the sample rate with which this patch has been configured. */
HV_EXPORT double hv_getSampleRate(Heavy *c);

/** Returns the number of input channels with which this patch has been configured. */
HV_EXPORT int hv_getNumInputChannels(Heavy *c);

/** Returns the number of output channels with which this patch has been configured. */
HV_EXPORT int hv_getNumOutputChannels(Heavy *c);

/** Set the print hook. The function is called whenever a message is sent to a print object. */
HV_EXPORT void hv_setPrintHook(Heavy *c,
    void (*f)(double timestamp, const char *printName, const char *message, void *userData));

/**
 * Set the send hook. The function is called whenever a message is sent to any send object.
 * Messages returned by this function should NEVER be freed. If the message must persist, call
 * hv_msg_copy() first.
 */
HV_EXPORT void hv_setSendHook(Heavy *c, void (*f)(const char *receiverName, HvMessage *m, void *userData));

HV_EXPORT void hv_vscheduleMessageForReceiver(
    Heavy *c, const char *receiverName, double delayMs, const char *format, ...);

HV_EXPORT void hv_scheduleMessageForReceiver(Heavy *c, const char *receiverName, double delayMs, HvMessage *m);

/** Cancels a previously scheduled message. */
HV_EXPORT void hv_cancelMessage(Heavy *c, HvMessage *m);

/** Returns a table object given its name. NULL if no table with that name exists. */
HV_EXPORT HvTable *hv_getTableForName(Heavy *c, const char *tableName);

/** Returns the current patch time in milliseconds. */
HV_EXPORT double hv_getCurrentTime(Heavy *c);

/** Sets a user-definable value. This value is never manipulated by Heavy. */
HV_EXPORT void hv_setUserData(Heavy *c, void *userData);

/** Returns the user-defined data. */
HV_EXPORT void *hv_getUserData(Heavy *c);

/** Define the base path of the patch. Used as the root path to locate assets. */
HV_EXPORT void hv_setBasePath(Heavy *c, const char *basePath);

#endif // _HEAVY_COMMON_H_

#ifdef __cplusplus
} // extern "C"
#endif
