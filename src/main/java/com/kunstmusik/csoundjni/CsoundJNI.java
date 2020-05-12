/*
    CsoundJNI.java:

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
package com.kunstmusik.csoundjni;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.logging.Level;
import java.util.logging.Logger;

public class CsoundJNI {

    private static boolean CSOUND_AVAILABLE = false;

    public static int CSOUNDINIT_NO_SIGNAL_HANDLER = 1;
    public static int CSOUNDINIT_NO_ATEXIT = 2;

    static {
        String os = System.getProperty("os.name").toLowerCase();
        String libraryName = "libcsoundjni.so"; // default case

        if (os.contains("mac")) {
            libraryName = "libcsoundjni.jnilib";
        } else if (os.contains("win")) {
            libraryName = "csoundjni.dll";
        }

        try {
            NativeUtils.loadLibraryFromJar("/com/kunstmusik/csoundjni/native/" + libraryName);
            //System.loadLibrary("CsoundJNI");
            CSOUND_AVAILABLE = true;
        } catch (IOException ex) {
            Logger.getLogger(CsoundJNI.class.getName()).log(Level.SEVERE, "Error: " + ex.getMessage(), ex);
            CSOUND_AVAILABLE = false;
        }
    }

    public static native int csoundInitialize(int flags);

    public static native long csoundCreate();

    public static native void csoundDestroy(long csoundPtr);

    public static native int csoundGetVersion();

    public static native int csoundSetOption(long csoundPtr, String option);

    public static native double csoundEvalCode(long csoundPtr, String s);

    public static native int csoundCompile(long csoundPtr, String[] args);

    public static native int csoundCompileOrc(long csoundPtr, String s);

    public static native int csoundCompileOrcAsync(long csoundPtr, String s);

    public static native int csoundCompileCsdText(long csoundPtr, String csdText);

    public static native double csoundGetScoreTime(long csoundPtr);

    public static native void csoundInputMessage(long csoundPtr, String s);

    public static native void csoundInputMessageAsync(long csoundPtr, String s);

    public static native int csoundReadScore(long csoundPtr, String s);

    public static native void csoundReadScoreAsync(long csoundPtr, String s);

    public static native int csoundStart(long csoundPtr);

    public static native void csoundStop(long csoundPtr);

    public static native int csoundPerformKsmps(long csoundPtr);

    public static native int csoundCleanup(long csoundPtr);

    public static native void csoundReset(long csoundPtr);

    //public void setMessageCallback(MessageCallback cb) {
    //    csoundSetMessageStringCallback(csoundPtr, cb);
    //}
    public static native double csoundGetSr(long csoundPtr);

    public static native double csoundGetKr(long csoundPtr);

    public static native int csoundGetKsmps(long csoundPtr);

    public static native int csoundGetNchnls(long csoundPtr);

    public static native int csoundGetNchnlsInput(long csoundPtr);

    public static native double csoundGet0dBFS(long csoundPtr);

    public static native void csoundSetControlChannel(long csoundPtr, String name, double value);

    public static native void csoundSetStringChannel(long csoundPtr, String channelName, String channelValue);

    public static native void csoundSetMessageCallback(long csoundPtr, MessageCallback msgCallback);

    /* BYTE BUFFER Related Code that wraps MYFLT* */
    public static native ByteBuffer csoundGetSpin(long csoundPtr);

    public static native ByteBuffer csoundGetSpout(long csoundPtr);

    public static native ByteBuffer csoundGetChannelPtr(long csoundPtr, String name, int type);
}
