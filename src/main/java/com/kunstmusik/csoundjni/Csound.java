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
import static com.kunstmusik.csoundjni.ControlChannelType.*;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.DoubleBuffer;

/**
 *
 * @author stevenyi
 */
public class Csound {

    private long csoundPtr;
    private MessageCallback messageCallback;

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

    public double evalCode(String s) {
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

    public double getSr() {
        return csoundGetSr(csoundPtr);
    }

    public double getKr() {
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

    public DoubleBuffer getSpin() {
        ByteBuffer buffer = csoundGetSpin(csoundPtr);
        DoubleBuffer retVal = null; 
        
        if(buffer != null) { 
            buffer.order(ByteOrder.nativeOrder());
            retVal = buffer.asDoubleBuffer();
        }
        return retVal;
    }
    
    public DoubleBuffer getSpout() {
        ByteBuffer buffer = csoundGetSpout(csoundPtr);
        DoubleBuffer retVal = null; 
        
        if(buffer != null) { 
            buffer.order(ByteOrder.nativeOrder());
            retVal = buffer.asDoubleBuffer();
        }
        return retVal;
    }
    

    public void setChannel(String name, double value) {
        csoundSetControlChannel(csoundPtr, name, value);
    }

    public void setStringChannel(String channelName, String channelValue) {
        csoundSetStringChannel(csoundPtr, channelName, channelValue);
    }

    public void setMessageCallback(MessageCallback msgCallback) {
        csoundSetMessageCallback(csoundPtr, msgCallback);
        this.messageCallback = msgCallback;
    }
    
    public DoubleBuffer getControlChannelPtr(String name) {
        ByteBuffer buffer = csoundGetChannelPtr(csoundPtr, name, 
                CSOUND_CONTROL_CHANNEL | CSOUND_INPUT_CHANNEL | CSOUND_OUTPUT_CHANNEL);
        DoubleBuffer retVal = null; 
        
        if(buffer != null) { 
            buffer.order(ByteOrder.nativeOrder());
            retVal = buffer.asDoubleBuffer();
        }
        return retVal;
    }
    
    public DoubleBuffer getAudioChannelPtr(String name) {
        ByteBuffer buffer = csoundGetChannelPtr(csoundPtr, name, 
                CSOUND_AUDIO_CHANNEL | CSOUND_INPUT_CHANNEL | CSOUND_OUTPUT_CHANNEL);
        
        DoubleBuffer retVal = null; 
        
        if(buffer != null) { 
            buffer.order(ByteOrder.nativeOrder());
            retVal = buffer.asDoubleBuffer();
        }
        
        return retVal;
    }
}
