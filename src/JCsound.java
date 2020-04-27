/*
    JCsound.java:

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

package com.kunstmusik.jcsound;

public class JCsound {
    static {
      System.loadLibrary("jcsound");
    }

    public static native long csoundCreate();
    public static native void csoundDestroy(long csoundPtr);
    public static native int csoundGetVersion(); 
    public static native int csoundSetOption(long csoundPtr, String option);

    public static native int csoundEvalCode(long csoundPtr, String s);     
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

    public static native int csoundGetSr(long csoundPtr); 

    public static native int csoundGetKr(long csoundPtr);

    public static native int csoundGetKsmps(long csoundPtr);

    public static native int csoundGetNchnls(long csoundPtr);

    public static native int csoundGetNchnlsInput(long csoundPtr);

    public static native double csoundGet0dBFS(long csoundPtr);

    //public DoubleBuffer getSpin(){
        //Pointer p = csoundGetSpin(csoundPtr);
        //int nchnls_i = csoundGetNchnlsInput(csoundPtr);
        //int ksmps = csoundGetKsmps(csoundPtr);
        //// 8 since double is 8 bytes in size
        //ByteBuffer b = p.getByteBuffer(0, nchnls_i * ksmps * 8);
        //return b.asDoubleBuffer();
    //}

    //public DoubleBuffer getSpout(){
        //Pointer p = csoundGetSpout(csoundPtr);
        //int nchnls = csoundGetNchnls(csoundPtr);
        //int ksmps = csoundGetKsmps(csoundPtr);

        //// 8 since double is 8 bytes in size
        //ByteBuffer b = p.getByteBuffer(0, nchnls * ksmps * 8);
        //return b.asDoubleBuffer();
    //}
    
    public static native void csoundSetControlChannel(long csoundPtr, String name, double value);

    public static native void csoundSetStringChannel(long csoundPtr, String channelName, String channelValue);

    //public void getChannelPtr(Pointer p, String name, int type) {
        //csoundGetChannelPtr(csoundPtr, p, name, type);
    //}
}
