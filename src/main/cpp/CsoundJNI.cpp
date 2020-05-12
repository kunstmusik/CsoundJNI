/*
    CsoundJNI.cpp:

    Copyright (C) 2020 Steven Yi 

    This file is part of CsoundJNI.

    The CsoundJNI Library is free software; you can redistribute it
    and/or modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    CsoundJNI is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with CsoundJNI; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
    02110-1301 USA
*/

#include "com_kunstmusik_csoundjni_CsoundJNI.h" 
#include "csound.h"

#include <iostream>

struct HostData {
  jobject msgCallback;
  jmethodID callbackMethodId;
};

JavaVM* g_VM;

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env;
    g_VM = vm;
    if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR; // JNI version not supported.
    }
  
    return  JNI_VERSION_1_6;
}

void jniMessageStringCallback(CSOUND * csound, int attr, const char * msg) {
  if(csound == NULL) return;
  HostData* hostData = (HostData*)csoundGetHostData(csound);
  
  if(hostData == NULL) return;
  jobject msgcallback = hostData->msgCallback;
  
  JNIEnv *env;
  // double check it's all ok
  int getEnvStat = g_VM->GetEnv((void **)&env, JNI_VERSION_1_6);
//  if (getEnvStat == JNI_EDETACHED) {
//      std::cout << "GetEnv: not attached" << std::endl;
//      if (g_VM->AttachCurrentThread((void **) &env, NULL) != 0) {
//          std::cout << "Failed to attach" << std::endl;
//      }
//  } else if (getEnvStat == JNI_OK) {
//      //
//  } else if (getEnvStat == JNI_EVERSION) {
//      std::cout << "GetEnv: version not supported" << std::endl;
//  }

  jstring string = env->NewStringUTF(msg);
  env->CallVoidMethod(hostData->msgCallback, hostData->callbackMethodId, (jint)attr, string);
  env->DeleteLocalRef(string);
  
  if (env->ExceptionCheck()) {
      env->ExceptionDescribe();
  }

//  g_VM->DetachCurrentThread();
  
}

#ifdef __cplusplus
extern "C"
{
#endif


  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundInitialize
   * Signature: (I)I
   */
  JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundInitialize
    (JNIEnv *env, jclass clazz, jint flags) {
      jint retVal = csoundInitialize(flags); 
      return retVal;
    }
  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundCreate
   * Signature: (I)J
   */
  JNIEXPORT jlong JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundCreate
    (JNIEnv *env, jclass clazz) {
      CSOUND* csound = csoundCreate(new HostData());
      return (jlong)csound;
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundDestroy
   * Signature: (J)V
   */
  JNIEXPORT void JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundDestroy
    (JNIEnv *env, jclass clazz, jlong csoundPtr) {
      CSOUND* csound = (CSOUND*)csoundPtr;
      HostData* hostData = (HostData*) csoundGetHostData(csound);
      
      if(hostData != NULL) {
        if(hostData->msgCallback != NULL) {
          env->DeleteGlobalRef(hostData->msgCallback);
        }
        delete hostData;
      }
      
      csoundDestroy(csound);
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundGetVersion
   * Signature: (J)I
   */
  JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGetVersion
    (JNIEnv *env, jclass clazz) {
      return csoundGetVersion();
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundSetOption
   * Signature: (JLjava/lang/String;)I
   */
  JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundSetOption
    (JNIEnv *env, jclass clazz, jlong csoundPtr, jstring option) {
      CSOUND* csound = (CSOUND*)csoundPtr;
      if(option == NULL) return 0;

      const char *nativeString = env->GetStringUTFChars(option, 0);

      jint retVal = csoundSetOption(csound, nativeString);

      env->ReleaseStringUTFChars(option, nativeString);

      return retVal;
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundEvalCode
   * Signature: (JLjava/lang/String;)D
   */
  JNIEXPORT jdouble JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundEvalCode
    (JNIEnv *env, jclass clazz, jlong csoundPtr, jstring code) {

      CSOUND* csound = (CSOUND*)csoundPtr;
      if(code == NULL) return 0;

      const char *nativeString = env->GetStringUTFChars(code, 0);

      jdouble retVal = csoundEvalCode(csound, nativeString);

      env->ReleaseStringUTFChars(code, nativeString);

      return retVal;
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundCompile
   * Signature: (J[Ljava/lang/String;)I
   */
  JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundCompile
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
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundCompileOrc
   * Signature: (JLjava/lang/String;)I
   */
  JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundCompileOrc
    (JNIEnv *env, jclass clazz, jlong csoundPtr, jstring orcCode) {
      CSOUND* csound = (CSOUND*)csoundPtr;
      if(orcCode == NULL) return 0;

      const char *nativeString = env->GetStringUTFChars(orcCode, 0);

      jint retVal = csoundCompileOrc(csound, nativeString);

      env->ReleaseStringUTFChars(orcCode, nativeString);

      return retVal;
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundCompileOrcAsync
   * Signature: (JLjava/lang/String;)I
   */
  JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundCompileOrcAsync
    (JNIEnv *env, jclass clazz, jlong csoundPtr, jstring orcCode) {
      CSOUND* csound = (CSOUND*)csoundPtr;
      if(orcCode == NULL) return 0;

      const char *nativeString = env->GetStringUTFChars(orcCode, 0);

      jint retVal = csoundCompileOrcAsync(csound, nativeString);

      env->ReleaseStringUTFChars(orcCode, nativeString);

      return retVal;
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundCompileCsdText
   * Signature: (JLjava/lang/String;)I
   */
  JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundCompileCsdText
    (JNIEnv *env, jclass clazz, jlong csoundPtr, jstring csdText) {
      CSOUND* csound = (CSOUND*)csoundPtr;
      if(csdText == NULL) return 0;

      const char *nativeString = env->GetStringUTFChars(csdText, 0);

      jint retVal = csoundCompileOrcAsync(csound, nativeString);

      env->ReleaseStringUTFChars(csdText, nativeString);

      return retVal;
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundGetScoreTime
   * Signature: (J)D
   */
  JNIEXPORT jdouble JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGetScoreTime
    (JNIEnv *env, jclass clazz, jlong csoundPtr) {
      CSOUND* csound = (CSOUND*)csoundPtr;

      return csoundGetScoreTime(csound);
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundInputMessage
   * Signature: (JLjava/lang/String;)I
   */
  JNIEXPORT void JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundInputMessage
    (JNIEnv *env, jclass clazz, jlong csoundPtr, jstring scoreMessage) {
      CSOUND* csound = (CSOUND*)csoundPtr;
      if(scoreMessage == NULL) return;

      const char *nativeString = env->GetStringUTFChars(scoreMessage, 0);

      csoundInputMessage(csound, nativeString);

      env->ReleaseStringUTFChars(scoreMessage, nativeString);
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundInputMessageAsync
   * Signature: (JLjava/lang/String;)I
   */
  JNIEXPORT void JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundInputMessageAsync
    (JNIEnv *env, jclass clazz, jlong csoundPtr, jstring scoreMessage) {
      CSOUND* csound = (CSOUND*)csoundPtr;
      if(scoreMessage == NULL) return;

      const char *nativeString = env->GetStringUTFChars(scoreMessage, 0);

      csoundInputMessageAsync(csound, nativeString);

      env->ReleaseStringUTFChars(scoreMessage, nativeString);
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundReadScore
   * Signature: (JLjava/lang/String;)I
   */
  JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundReadScore
    (JNIEnv *env, jclass clazz, jlong csoundPtr, jstring message) {
      CSOUND* csound = (CSOUND*)csoundPtr;
      if(message == NULL) return 0;

      const char *nativeString = env->GetStringUTFChars(message, 0);

      jint retVal = csoundReadScore(csound, nativeString);

      env->ReleaseStringUTFChars(message, nativeString);

      return retVal;
    }


  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundReadScoreAsync
   * Signature: (JLjava/lang/String;)I
   */
  JNIEXPORT void JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundReadScoreAsync
    (JNIEnv *env, jclass clazz, jlong csoundPtr, jstring message) {
      CSOUND* csound = (CSOUND*)csoundPtr;
      if(message == NULL) return;

      const char *nativeString = env->GetStringUTFChars(message, 0);

      csoundReadScoreAsync(csound, nativeString);

      env->ReleaseStringUTFChars(message, nativeString);
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundStart
   * Signature: (J)V
   */
  JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundStart
    (JNIEnv *env, jclass clazz, jlong csoundPtr) {
      CSOUND* csound = (CSOUND*)csoundPtr;

      jint retVal = csoundStart(csound);
      return retVal;
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundStop
   * Signature: (J)V
   */
  JNIEXPORT void JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundStop
    (JNIEnv *env, jclass clazz, jlong csoundPtr) {
      CSOUND* csound = (CSOUND*)csoundPtr;

      csoundStop(csound);
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundPerformKsmps
   * Signature: (J)I
   */
  JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundPerformKsmps
    (JNIEnv *env, jclass clazz, jlong csoundPtr) {
      CSOUND* csound = (CSOUND*)csoundPtr;

      jint retVal = csoundPerformKsmps(csound);
      return retVal;
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundCleanup
   * Signature: (J)I
   */
  JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundCleanup
    (JNIEnv *env, jclass clazz, jlong csoundPtr) {
      CSOUND* csound = (CSOUND*)csoundPtr;

      jint retVal = csoundCleanup(csound);
      return retVal;
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundReset
   * Signature: (J)V
   */
  JNIEXPORT void JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundReset
    (JNIEnv *env, jclass clazz, jlong csoundPtr) {
      csoundReset((CSOUND*)csoundPtr);
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundGetSr
   * Signature: (J)D
   */
  JNIEXPORT jdouble JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGetSr
    (JNIEnv *env, jclass clazz, jlong csoundPtr) {
      CSOUND* csound = (CSOUND*)csoundPtr;

      jdouble retVal = csoundGetSr(csound);
      return retVal;
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundGetKr
   * Signature: (J)D
   */
  JNIEXPORT jdouble JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGetKr
    (JNIEnv *env, jclass clazz, jlong csoundPtr) {
      CSOUND* csound = (CSOUND*)csoundPtr;

      jdouble retVal = csoundGetKr(csound);
      return retVal;
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundGetKsmps
   * Signature: (J)I
   */
  JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGetKsmps
    (JNIEnv *env, jclass clazz, jlong csoundPtr) {
      CSOUND* csound = (CSOUND*)csoundPtr;

      jint retVal = csoundGetKsmps(csound);
      return retVal;
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundGetNchnls
   * Signature: (J)I
   */
  JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGetNchnls
    (JNIEnv *env, jclass clazz, jlong csoundPtr) {
      CSOUND* csound = (CSOUND*)csoundPtr;

      jint retVal = csoundGetNchnls(csound);
      return retVal;
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundGetNchnlsInput
   * Signature: (J)I
   */
  JNIEXPORT jint JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGetNchnlsInput
    (JNIEnv *env, jclass clazz, jlong csoundPtr) {
      CSOUND* csound = (CSOUND*)csoundPtr;

      jint retVal = csoundGetNchnlsInput(csound);
      return retVal;
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundGet0dBFS
   * Signature: (J)D
   */
  JNIEXPORT jdouble JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGet0dBFS
    (JNIEnv *env, jclass clazz, jlong csoundPtr) {
      CSOUND* csound = (CSOUND*)csoundPtr;

      jdouble retVal = csoundGet0dBFS(csound);
      return retVal;
    }

  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundSetControlChannel
   * Signature: (JLjava/lang/String;D)V
   */
  JNIEXPORT void JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundSetControlChannel
    (JNIEnv *env, jclass clazz, jlong csoundPtr, jstring channel, jdouble value) {
      CSOUND* csound = (CSOUND*)csoundPtr;
      if(channel == NULL) return;

      const char *nativeString = env->GetStringUTFChars(channel, 0);

      csoundSetControlChannel(csound, nativeString, value);

      env->ReleaseStringUTFChars(channel, nativeString);
    }
  /*
   * Class:     com_kunstmusik_csoundjni_CsoundJNI
   * Method:    csoundSetStringChannel
   * Signature: (JLjava/lang/String;Ljava/lang/String;)V
   */
  JNIEXPORT void JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundSetStringChannel
    (JNIEnv *env, jclass clazz, jlong csoundPtr, jstring channel, jstring value) {
      CSOUND* csound = (CSOUND*)csoundPtr;
      if(channel == NULL || value == NULL) return;

      const char *chanName = env->GetStringUTFChars(channel, 0);
      const char *chanValue = env->GetStringUTFChars(value, 0);

      csoundSetStringChannel(csound, chanName, (char*)chanValue);

      env->ReleaseStringUTFChars(channel, chanName);
      env->ReleaseStringUTFChars(value, chanValue);
    }




/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    setMessageCallbackNative
 * Signature: (Lcom/kunstmusik/csoundjni/MessageCallback;)V
 */
JNIEXPORT void JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundSetMessageCallback
  (JNIEnv * env, jclass clazz, jlong csoundPtr, jobject jobj) {
    CSOUND* csound = (CSOUND*)csoundPtr;
    
    HostData* data = (HostData*)csoundGetHostData(csound);
    
    data->msgCallback = env->NewGlobalRef(jobj);
    
    jclass cls = env->GetObjectClass(jobj);
    

    data->callbackMethodId = env->GetMethodID(cls,
                                              "callback",
                                              "(ILjava/lang/String;)V");
        
    csoundSetMessageStringCallback(csound, &jniMessageStringCallback);
  }


/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundGetSpin
 * Signature: (J)Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGetSpin
(JNIEnv *env, jclass clazz, jlong csoundPtr) {
  CSOUND* csound = (CSOUND*)csoundPtr;
  if(csoundPtr == 0) return NULL;
  
  MYFLT* spin = csoundGetSpin(csound);
  
  jobject retVal = NULL;
  
  if(spin != NULL) {
    int nchnls_i = csoundGetNchnlsInput(csound);
    int ksmps = csoundGetKsmps(csound);
    
    retVal = env->NewDirectByteBuffer(spin, sizeof(MYFLT) * nchnls_i * ksmps);
  }
  
  return retVal;
}

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundGetSpout
 * Signature: (J)Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGetSpout
(JNIEnv *env, jclass clazz, jlong csoundPtr) {
  CSOUND* csound = (CSOUND*)csoundPtr;
  if(csoundPtr == 0) return NULL;
  
  MYFLT* spout = csoundGetSpout(csound);
  
  jobject retVal = NULL;
  
  if(spout != NULL) {
    int nchnls = csoundGetNchnls(csound);
    int ksmps = csoundGetKsmps(csound);
    
    retVal = env->NewDirectByteBuffer(spout, sizeof(MYFLT) * nchnls * ksmps);
  }
  
  return retVal;
}

/*
 * Class:     com_kunstmusik_csoundjni_CsoundJNI
 * Method:    csoundGetChannelPtr
 * Signature: (JLjava/lang/String;I)Ljava/nio/ByteBuffer;
 */
JNIEXPORT jobject JNICALL Java_com_kunstmusik_csoundjni_CsoundJNI_csoundGetChannelPtr
(JNIEnv *env, jclass clazz, jlong csoundPtr, jstring channel, jint chanType) {
  CSOUND* csound = (CSOUND*)csoundPtr;
  if(csoundPtr == 0 || channel == NULL) return NULL;

  const char *chanName = env->GetStringUTFChars(channel, 0);
  MYFLT* data;
  
  int res = csoundGetChannelPtr(csound, &data, chanName, (int)chanType);

  env->ReleaseStringUTFChars(channel, chanName);
  
  jobject retVal = NULL;
  
  if(res == 0) {
    if((chanType & CSOUND_CONTROL_CHANNEL) == CSOUND_CONTROL_CHANNEL) {
      retVal = env->NewDirectByteBuffer(data, sizeof(MYFLT));
    } else if((chanType & CSOUND_AUDIO_CHANNEL) == CSOUND_AUDIO_CHANNEL) {
      int ksmps = csoundGetKsmps(csound);
      retVal = env->NewDirectByteBuffer(data, sizeof(MYFLT) * ksmps);
    }
    
  }
  
  return retVal;
  
}
#ifdef __cplusplus
}
#endif
