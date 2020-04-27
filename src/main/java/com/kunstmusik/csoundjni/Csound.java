/*
    Csound.java:

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

import static com.kunstmusik.csoundjni.CsoundJNI.*;

/**
 *
 * @author stevenyi
 */
public class Csound {

    private long csoundPtr;

    public Csound() {
        csoundPtr = csoundCreate();
    }

    @SuppressWarnings("deprecation")
    protected void finalize() {
        delete();
    }

    public void delete() {
        if (csoundPtr != 0) {
            csoundDestroy(csoundPtr);
            csoundPtr = 0;
        }
    }

    public int getVersion() {
        return csoundGetVersion();
    }

    public int setOption(String option) {
        return csoundSetOption(csoundPtr, option);
    }

    public int evalCode(String s) {
        return csoundEvalCode(csoundPtr, s);
    }

    public int compile(String[] args) {
        return csoundCompile(csoundPtr, args);
    }

    public int compileOrc(String s) {
        return csoundCompileOrc(csoundPtr, s);
    }

    public int compileOrcAsync(String s) {
        return csoundCompileOrcAsync(csoundPtr, s);
    }

    public int compileCsdText(String csdText) {
        return csoundCompileCsdText(csoundPtr, csdText);
    }

    public double getScoreTime() {
        return csoundGetScoreTime(csoundPtr);
    }

    public void inputMessage(String s) {
        csoundInputMessage(csoundPtr, s);
    }

    public void inputMessageAsync(String s) {
        csoundInputMessageAsync(csoundPtr, s);
    }

    public int readScore(String s) {
        return csoundReadScore(csoundPtr, s);
    }

    public void readScoreAsync(String s) {
        csoundReadScoreAsync(csoundPtr, s);
    }

    public void start() {
        csoundStart(csoundPtr);
    }

    public void stop() {
        csoundStop(csoundPtr);
    }

    public int performKsmps() {
        return csoundPerformKsmps(csoundPtr);
    }

    public int cleanup() {
        return csoundCleanup(csoundPtr);
    }

    public void reset() {
        csoundReset(csoundPtr);
    }

//    public void setMessageCallback(MessageCallback cb) {
//        csoundSetMessageStringCallback(csoundPtr, cb);
//    }
    public int getSr() {
        return csoundGetSr(csoundPtr);
    }

    public int getKr() {
        return csoundGetKr(csoundPtr);
    }

    public int getKsmps() {
        return csoundGetKsmps(csoundPtr);
    }

    public int getNchnls() {
        return csoundGetNchnls(csoundPtr);
    }

    public int getNchnlsInput() {
        return csoundGetNchnlsInput(csoundPtr);
    }

    public double get0dBFS() {
        return csoundGet0dBFS(csoundPtr);
    }

//    public DoubleBuffer getSpin(){
//        Pointer p = csoundGetSpin(csoundPtr);
//        int nchnls_i = csoundGetNchnlsInput(csoundPtr);
//        int ksmps = csoundGetKsmps(csoundPtr);
//        // 8 since double is 8 bytes in size
//        ByteBuffer b = p.getByteBuffer(0, nchnls_i * ksmps * 8);
//        return b.asDoubleBuffer();
//    }
//
//    public DoubleBuffer getSpout(){
//        Pointer p = csoundGetSpout(csoundPtr);
//        int nchnls = csoundGetNchnls(csoundPtr);
//        int ksmps = csoundGetKsmps(csoundPtr);
//
//        // 8 since double is 8 bytes in size
//        ByteBuffer b = p.getByteBuffer(0, nchnls * ksmps * 8);
//        return b.asDoubleBuffer();
//    }
    public void setChannel(String name, double value) {
        csoundSetControlChannel(csoundPtr, name, value);
    }

    public void setStringChannel(String channelName, String channelValue) {
        csoundSetStringChannel(csoundPtr, channelName, channelValue);
    }

//    public void getChannelPtr(Pointer p, String name, int type) {
//        csoundGetChannelPtr(csoundPtr, p, name, type);
//    }
}
