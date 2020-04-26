#include "com_kunstmusik_jcsound_JCsound.h" 
#include "csound.h"

#include <iostream>

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundCreate
 * Signature: (I)J
 */
JNIEXPORT jlong JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundCreate
  (JNIEnv *env, jobject obj, jint args) {
    
     CSOUND* csound = csoundCreate(NULL); 
     return (jlong)csound;
  }

/*
 * Class:     com_kunstmusik_jcsound_JCsound
 * Method:    csoundReset
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_com_kunstmusik_jcsound_JCsound_csoundReset
  (JNIEnv *env, jobject obj, jlong csoundPtr) {
    std::cout << "Csound Reset Called." << std::endl;
    csoundReset((CSOUND*)csoundPtr);
    return 1; 
  }

