/*
    JCsound.cpp:

    Copyright (C) 2020 Steven Yi 

    This file is part of jcsound.

    The jcsound Library is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    jcsound is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with jcsound; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
    02110-1301 USA
*/

#include "com_kunstmusik_jcsound_JCsound.h" 
#include "csound.h"

#include <iostream>

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundCreate
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundCreate
(JNIEnv *env, jclass clazz) {
  CSOUND* csound = csoundCreate(NULL); 
  return (jlong)csound;
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundDestroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundDestroy
(JNIEnv *env, jclass clazz, jlong csoundPtr) {
  CSOUND* csound = (CSOUND*)csoundPtr;
  csoundDestroy(csound);
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundGetVersion
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundGetVersion
(JNIEnv *env, jclass clazz) {
  return csoundGetVersion();
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundSetOption
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundSetOption
(JNIEnv *env, jclass clazz, jlong csoundPtr, jstring option) {
  CSOUND* csound = (CSOUND*)csoundPtr;
  if(option == NULL) return 0;

  const char *nativeString = env->GetStringUTFChars(option, 0);

  jint retVal = csoundSetOption(csound, nativeString);

  env->ReleaseStringUTFChars(option, nativeString);

  return retVal;
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundEvalCode
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundEvalCode
(JNIEnv *env, jclass clazz, jlong csoundPtr, jstring code) {

  CSOUND* csound = (CSOUND*)csoundPtr;
  if(code == NULL) return 0;

  const char *nativeString = env->GetStringUTFChars(code, 0);

  jint retVal = csoundEvalCode(csound, nativeString);

  env->ReleaseStringUTFChars(code, nativeString);

  return retVal;
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundCompile
 * Signature: (J[Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundCompile
(JNIEnv *env, jclass clazz, jlong csoundPtr, jobjectArray args) {
  const char *argv[256]; //up to 256 commandline args...
  CSOUND* csound = (CSOUND*)csoundPtr;
  if(args == NULL) return 0;
  int argc = env->GetArrayLength(args);

  for(int i = 0; i < argc; i++) {
    jstring string = (jstring) (env->GetObjectArrayElement(args, i));
    argv[i] = env->GetStringUTFChars(string, 0);
  }

  int retVal = csoundCompile(csound, argc, argv);

  // cleanup java strings
  for(int i = 0; i < argc; i++) {
    jstring string = (jstring) (env->GetObjectArrayElement(args, i));
    env->ReleaseStringUTFChars(string, argv[i]);
  }

  return retVal;
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundCompileOrc
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundCompileOrc
(JNIEnv *env, jclass clazz, jlong csoundPtr, jstring orcCode) {
  CSOUND* csound = (CSOUND*)csoundPtr;
  if(orcCode == NULL) return 0;

  const char *nativeString = env->GetStringUTFChars(orcCode, 0);

  jint retVal = csoundCompileOrc(csound, nativeString);

  env->ReleaseStringUTFChars(orcCode, nativeString);

  return retVal;
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundCompileOrcAsync
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundCompileOrcAsync
(JNIEnv *env, jclass clazz, jlong csoundPtr, jstring orcCode) {
  CSOUND* csound = (CSOUND*)csoundPtr;
  if(orcCode == NULL) return 0;

  const char *nativeString = env->GetStringUTFChars(orcCode, 0);

  jint retVal = csoundCompileOrcAsync(csound, nativeString);

  env->ReleaseStringUTFChars(orcCode, nativeString);

  return retVal;
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundCompileCsdText
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundCompileCsdText
(JNIEnv *env, jclass clazz, jlong csoundPtr, jstring csdText) {
  CSOUND* csound = (CSOUND*)csoundPtr;
  if(csdText == NULL) return 0;

  const char *nativeString = env->GetStringUTFChars(csdText, 0);

  jint retVal = csoundCompileOrcAsync(csound, nativeString);

  env->ReleaseStringUTFChars(csdText, nativeString);

  return retVal;
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundGetScoreTime
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundGetScoreTime
(JNIEnv *env, jclass clazz, jlong csoundPtr) {
  CSOUND* csound = (CSOUND*)csoundPtr;

  return csoundGetScoreTime(csound);
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundInputMessage
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT void JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundInputMessage
(JNIEnv *env, jclass clazz, jlong csoundPtr, jstring scoreMessage) {
  CSOUND* csound = (CSOUND*)csoundPtr;
  if(scoreMessage == NULL) return;

  const char *nativeString = env->GetStringUTFChars(scoreMessage, 0);

  csoundInputMessage(csound, nativeString);

  env->ReleaseStringUTFChars(scoreMessage, nativeString);
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundInputMessageAsync
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT void JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundInputMessageAsync
(JNIEnv *env, jclass clazz, jlong csoundPtr, jstring scoreMessage) {
  CSOUND* csound = (CSOUND*)csoundPtr;
  if(scoreMessage == NULL) return;

  const char *nativeString = env->GetStringUTFChars(scoreMessage, 0);

  csoundInputMessageAsync(csound, nativeString);

  env->ReleaseStringUTFChars(scoreMessage, nativeString);
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundReadScore
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundReadScore
(JNIEnv *env, jclass clazz, jlong csoundPtr, jstring message) {
  CSOUND* csound = (CSOUND*)csoundPtr;
  if(message == NULL) return 0;

  const char *nativeString = env->GetStringUTFChars(message, 0);

  jint retVal = csoundReadScore(csound, nativeString);

  env->ReleaseStringUTFChars(message, nativeString);

  return retVal;
}


/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundReadScoreAsync
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT void JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundReadScoreAsync
(JNIEnv *env, jclass clazz, jlong csoundPtr, jstring message) {
  CSOUND* csound = (CSOUND*)csoundPtr;
  if(message == NULL) return;

  const char *nativeString = env->GetStringUTFChars(message, 0);

  csoundReadScoreAsync(csound, nativeString);

  env->ReleaseStringUTFChars(message, nativeString);
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundStart
 * Signature: (J)V
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundStart
(JNIEnv *env, jclass clazz, jlong csoundPtr) {
  CSOUND* csound = (CSOUND*)csoundPtr;

  jint retVal = csoundStart(csound);
  return retVal;
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundStop
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundStop
(JNIEnv *env, jclass clazz, jlong csoundPtr) {
  CSOUND* csound = (CSOUND*)csoundPtr;

  csoundStop(csound);
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundPerformKsmps
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundPerformKsmps
(JNIEnv *env, jclass clazz, jlong csoundPtr) {
  CSOUND* csound = (CSOUND*)csoundPtr;

  jint retVal = csoundPerformKsmps(csound);
  return retVal;
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundCleanup
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundCleanup
(JNIEnv *env, jclass clazz, jlong csoundPtr) {
  CSOUND* csound = (CSOUND*)csoundPtr;

  jint retVal = csoundCleanup(csound);
  return retVal;
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundReset
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundReset
(JNIEnv *env, jclass clazz, jlong csoundPtr) {
  csoundReset((CSOUND*)csoundPtr);
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundGetSr
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundGetSr
(JNIEnv *env, jclass clazz, jlong csoundPtr) {
  CSOUND* csound = (CSOUND*)csoundPtr;

  jint retVal = csoundGetSr(csound);
  return retVal;
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundGetKr
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundGetKr
(JNIEnv *env, jclass clazz, jlong csoundPtr) {
  CSOUND* csound = (CSOUND*)csoundPtr;

  jint retVal = csoundGetKr(csound);
  return retVal;
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundGetKsmps
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundGetKsmps
(JNIEnv *env, jclass clazz, jlong csoundPtr) {
  CSOUND* csound = (CSOUND*)csoundPtr;

  jint retVal = csoundGetKsmps(csound);
  return retVal;
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundGetNchnls
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundGetNchnls
(JNIEnv *env, jclass clazz, jlong csoundPtr) {
  CSOUND* csound = (CSOUND*)csoundPtr;

  jint retVal = csoundGetNchnls(csound);
  return retVal;
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundGetNchnlsInput
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundGetNchnlsInput
(JNIEnv *env, jclass clazz, jlong csoundPtr) {
  CSOUND* csound = (CSOUND*)csoundPtr;

  jint retVal = csoundGetNchnlsInput(csound);
  return retVal;
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundGet0dBFS
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundGet0dBFS
(JNIEnv *env, jclass clazz, jlong csoundPtr) {
  CSOUND* csound = (CSOUND*)csoundPtr;

  jdouble retVal = csoundGet0dBFS(csound);
  return retVal;
}

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundSetControlChannel
 * Signature: (JLjava/lang/String;D)V
 */
JNIEXPORT void JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundSetControlChannel
(JNIEnv *env, jclass clazz, jlong csoundPtr, jstring channel, jdouble value) {
  CSOUND* csound = (CSOUND*)csoundPtr;
  if(channel == NULL) return;

  const char *nativeString = env->GetStringUTFChars(channel, 0);

  csoundSetControlChannel(csound, nativeString, value);

  env->ReleaseStringUTFChars(channel, nativeString);
}
/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundSetStringChannel
 * Signature: (JLjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundSetStringChannel
(JNIEnv *env, jclass clazz, jlong csoundPtr, jstring channel, jstring value) {
  CSOUND* csound = (CSOUND*)csoundPtr;
  if(channel == NULL || value == NULL) return;

  const char *chanName = env->GetStringUTFChars(channel, 0);
  const char *chanValue = env->GetStringUTFChars(value, 0);

  csoundSetStringChannel(csound, chanName, (char*)chanValue);

  env->ReleaseStringUTFChars(channel, chanName);
  env->ReleaseStringUTFChars(value, chanValue);
}

