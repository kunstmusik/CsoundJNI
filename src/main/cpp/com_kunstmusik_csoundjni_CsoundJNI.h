/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_kunstmusik_csoundjni_CsoundJNI */

#ifndef _Included_com_kunstmusik_csoundjni_CsoundJNI
#define _Included_com_kunstmusik_csoundjni_CsoundJNI
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundInitialize
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundInitialize
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundCreate
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundCreate
  (JNIEnv *, jclass);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundDestroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundDestroy
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundGetVersion
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGetVersion
  (JNIEnv *, jclass);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundSetOption
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundSetOption
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundEvalCode
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundEvalCode
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundCompile
 * Signature: (J[Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundCompile
  (JNIEnv *, jclass, jlong, jobjectArray);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundCompileOrc
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundCompileOrc
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundCompileOrcAsync
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundCompileOrcAsync
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundCompileCsdText
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundCompileCsdText
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundGetScoreTime
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGetScoreTime
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundInputMessage
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundInputMessage
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundInputMessageAsync
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundInputMessageAsync
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundReadScore
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundReadScore
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundReadScoreAsync
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundReadScoreAsync
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundStart
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundStart
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundStop
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundStop
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundPerformKsmps
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundPerformKsmps
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundCleanup
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundCleanup
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundReset
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundReset
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundGetSr
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGetSr
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundGetKr
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGetKr
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundGetKsmps
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGetKsmps
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundGetNchnls
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGetNchnls
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundGetNchnlsInput
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGetNchnlsInput
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundGet0dBFS
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGet0dBFS
  (JNIEnv *, jclass, jlong);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundSetControlChannel
 * Signature: (JLjava/lang/String;D)V
 */
JNIEXPORT void JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundSetControlChannel
  (JNIEnv *, jclass, jlong, jstring, jdouble);

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundSetStringChannel
 * Signature: (JLjava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundSetStringChannel
  (JNIEnv *, jclass, jlong, jstring, jstring);

#ifdef __cplusplus
}
#endif
#endif