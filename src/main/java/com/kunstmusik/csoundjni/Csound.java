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
 * Csound engine instance that wraps Csound's C API into an object and
 * simplifies usage of the API.
 *
 * Comments for methods based on documentation from csound.h.
 *
 * @author Steven Yi
 */
public class Csound {

    private long csoundPtr;
    private MessageCallback messageCallback;

    public Csound() {
        csoundPtr = csoundCreate();
    }

    @SuppressWarnings("deprecation")
    @Override
    protected void finalize() throws Throwable {
        try {
            delete();
        } finally {
            super.finalize();
        }
    }

    public void delete() {
        if (csoundPtr != 0) {
            csoundDestroy(csoundPtr);
            csoundPtr = 0;
        }
    }

    /**
     * Returns the version number times 1000 (5.00.0 = 5000).
     *
     * @return version number
     */
    public int getVersion() {
        return csoundGetVersion();
    }

    /**
     * Set a single Csound option (flag). NB: blank spaces are not allowed
     *
     * @param option Single Csound option
     * @return Returns a non-zero error code on failure.
     */
    public int setOption(String option) {
        return csoundSetOption(csoundPtr, option);
    }

    /**
     * Parse and compile an orchestra given on an string, evaluating any global
     * space code (i-time only).On SUCCESS it returns a value passed to the
     * 'return' opcode in global space
     *
     * <pre>
     *       String code = "i1 = 2 + 2 \n return i1 \n";
     *       double retval = csound.evalCode(code);
     * </pre>
     *
     * @param orcCode Csound orchestra code to evaluate
     * @return result of value passed to 'return' opcode in global space
     */
    public double evalCode(String orcCode) {
        return csoundEvalCode(csoundPtr, orcCode);
    }

    /**
     * Compiles Csound input files (such as an orchestra and score, or CSD) as
     * directed by the supplied command-line arguments, but does not perform
     * them. Returns a non-zero error code on failure.This function cannot be
     * called during performance, and before a repeated call, reset() needs to
     * be called. In this (host-driven) mode, the sequence of calls should be as
     * follows:
     *
     * <pre>
     *       csound.compile(args);
     *       while (csound.performKsmps() == 0);
     *       csound.cleanup();
     *       csound.reset();
     * </pre>
     *
     * Calls csoundStart() internally. Can only be called again after reset (see
     * csoundReset())
     *
     * @param args String arguments as if using command-line Csound. First
     * argument should be the name of the command (e.g., "csound").
     * @return Returns a non-zero error code on failure.
     */
    public int compile(String[] args) {
        return csoundCompile(csoundPtr, args);
    }

    /**
     * Parse, and compile the given orchestra from a String, also evaluating any
     * global space code (i-time only) this can be called during performance to
     * compile a new orchestra.
     *
     * <pre>
     *       String orc = "instr 1 \n a1 rand 0dbfs/4 \n out a1 \n";
     *       csound.compileOrc(csound, orc);
     * </pre>
     *
     * @param orc Csound orchestra code
     * @return Returns a non-zero error code on failure.
     */
    public int compileOrc(String orc) {
        return csoundCompileOrc(csoundPtr, orc);
    }

    /**
     * Async version of compileOrc().The code is parsed and compiled, then
     * placed on a queue for asynchronous merge into the running engine, and
     * evaluation.The function returns following parsing and compilation.
     *
     * @param orc Csound orchestra code
     * @return Returns a non-zero error code on failure.
     */
    public int compileOrcAsync(String orc) {
        return csoundCompileOrcAsync(csoundPtr, orc);
    }

    /**
     * Compiles Csound CSD input text, but does not perform it.Returns a
     * non-zero error code on failure.If start() is called before
     * compileCsdText(), the &lt;CsOptions&gt; element is ignored (but
     * csoundSetOption can be called any number of times), the &lt;CsScore&gt;
     * element is not pre-processed, but dispatched as real-time events; and
     * performance continues indefinitely, or until ended by calling csoundStop
     * or some other logic. In this "real-time" mode, the sequence of calls
     * should be:
     *
     * <pre>
     *
     * csound.setOption("-an_option");
     * csound.setOption("-another_option");
     * csound.start(csound);
     * csound.sompileCsdText(csound, csdText);
     * while (1) {
     *    csound.performKsmps(csound);
     *    // Something to break out of the loop
     *    // when finished here...
     * }
     * csound.cleanup(csound);
     * csound.reset(csound);
     *
     * </pre>
     *
     * NB: this function can be called repeatedly during performance to replace
     * or add new instruments and events.
     *
     * But if csoundCompileCsd is called before csoundStart, the
     * &lt;CsOptions&gt; element is used, the &lt;CsScore&gt; section is
     * pre-processed and dispatched normally, and performance terminates when
     * the score terminates, or stop() is called. In this "non-real-time" mode
     * (which can still output real-time audio and handle real-time events), the
     * sequence of calls should be:
     *
     * <pre>
     *
     * csound.compileCsdText(csound, csdText);
     * csound.start();
     * while (1) {
     *    int finished = csound.performKsmps(csound);
     *    if (finished) break;
     * }
     * csound.cleanup();
     * csound.reset();
     *
     * </pre>
     *
     * @param csdText Csound CSD text
     * @return Returns a non-zero error code on failure.
     */
    public int compileCsdText(String csdText) {
        return csoundCompileCsdText(csoundPtr, csdText);
    }

    /**
     * Returns the current score time in seconds since the beginning of
     * performance.
     *
     * @return Current score time in seconds since the beginning of performance.
     */
    public double getScoreTime() {
        return csoundGetScoreTime(csoundPtr);
    }

    /**
     * Input a String (as if from a console), used for line events.
     *
     * @param scoreText Csound score text.
     */
    public void inputMessage(String scoreText) {
        csoundInputMessage(csoundPtr, scoreText);
    }

    /**
     * Asynchronous version of inputMessage().
     *
     * @param scoreText Csound score text.
     */
    public void inputMessageAsync(String scoreText) {
        csoundInputMessageAsync(csoundPtr, scoreText);
    }

    /**
     * Read, preprocess, and load a score from a String.It can be called
     * repeatedly, with the new score events being added to the currently
     * scheduled ones.
     *
     * @param scoreText Csound score text.
     * @return Returns a non-zero error code on failure.
     *
     */
    public int readScore(String scoreText) {
        return csoundReadScore(csoundPtr, scoreText);
    }

    /**
     * Asynchronous version of readScore().
     *
     * @param scoreText Csound score text.
     */
    public void readScoreAsync(String scoreText) {
        csoundReadScoreAsync(csoundPtr, scoreText);
    }

    /**
     * Prepares Csound for performance. Normally called after compiling a csd
     * file or an orc file, in which case score preprocessing is performed and
     * performance terminates when the score terminates.
     *
     * However, if called before compiling a csd file or an orc file, score
     * preprocessing is not performed and "i" statements are dispatched as
     * real-time events, the &lt;CsOptions&gt; tag is ignored, and performance
     * continues indefinitely or until ended using the API.
     */
    public void start() {
        csoundStart(csoundPtr);
    }

    /**
     * Stops a perform() running (may be in another thread). Note that it is not
     * guaranteed that perform() has already stopped when this function returns.
     */
    public void stop() {
        csoundStop(csoundPtr);
    }

    /**
     * Senses input events, and performs one control sample worth (ksmps) of
     * audio output. Note that compile() or compileOrc(), readScore(), start()
     * must be called first. Returns 0 during performance, and 1 when
     * performance is finished. If called until it returns 1, will perform an
     * entire score. Enables external software to control the execution of
     * Csound, and to synchronize performance with audio input and output.
     *
     * @return 1 if performance is done, 0 if still more to perform.
     */
    public int performKsmps() {
        return csoundPerformKsmps(csoundPtr);
    }

     /**
     * Senses input events and performs audio output until the end of score
     * is reached (positive return value), an error occurs (negative return
     * value), or performance is stopped by calling csoundStop() from another
     * thread (zero return value).
     * Note that csoundCompile() or csoundCompileOrc(), csoundReadScore(),
     * csoundStart() must be called first.
     * In the case of zero return value, csoundPerform() can be called again
     * to continue the stopped performance. Otherwise, csoundReset() should be
     * called to clean up after the finished or failed performance.
     */
    public int perform() {
        int res;
        do {
            res = performKsmps();
        } while(res == 0);
        
        return res;
    }

    /**
     * Prints information about the end of a performance, and closes audio and
     * MIDI devices.Note: after calling cleanup(), the operation of the perform
     * functions is undefined.
     *
     * @return Returns a non-zero error code on failure.
     *
     */
    public int cleanup() {
        return csoundCleanup(csoundPtr);
    }

    /**
     * Resets all internal memory and state in preparation for a new
     * performance. Enables external software to run successive Csound
     * performances without reloading Csound. Implies cleanup(), unless already
     * called.
     */
    public void reset() {
        csoundReset(csoundPtr);
    }

    /**
     * Returns the number of audio sample frames per second.
     *
     * @return The number of audio sample frames per second.
     */
    public double getSr() {
        return csoundGetSr(csoundPtr);
    }

    /**
     * Returns the number of control samples per second.
     *
     * @return The number of control samples per second.
     */
    public double getKr() {
        return csoundGetKr(csoundPtr);
    }

    /**
     * Returns the number of audio sample frames per control sample.
     *
     * @return The number of audio sample frames per control sample.
     */
    public int getKsmps() {
        return csoundGetKsmps(csoundPtr);
    }

    /**
     * Returns the number of audio output channels. Set through the nchnls
     * header variable in the csd file.
     *
     * @return The number of audio output channels
     */
    public int getNchnls() {
        return csoundGetNchnls(csoundPtr);
    }

    /**
     * Returns the number of audio input channels. Set through the nchnls_i
     * header variable in the csd file. If this variable is not set, the value
     * is taken from nchnls.
     *
     * @return The number of audio input channels
     */
    public int getNchnlsInput() {
        return csoundGetNchnlsInput(csoundPtr);
    }

    /**
     * Returns the 0dBFS level of the spin/spout buffers.
     *
     * @return The 0dBFS level of the spin/spout buffers.
     */
    public double get0dBFS() {
        return csoundGet0dBFS(csoundPtr);
    }

    /**
     * Returns a DoubleBuffer wrapper of the Csound audio input working buffer
     * (spin).Enables external software to write audio into Csound before
     * calling csoundPerformKsmps. The length of the DoubleBuffer is set to
     * ksmps * nchnls_i.
     *
     * @return DoubleBuffer wrapper of the Csound audio input working buffer
     * (spin).
     */
    public DoubleBuffer getSpin() {
        ByteBuffer buffer = csoundGetSpin(csoundPtr);
        DoubleBuffer retVal = null;

        if (buffer != null) {
            buffer.order(ByteOrder.nativeOrder());
            retVal = buffer.asDoubleBuffer();
        }
        return retVal;
    }

    /**
     * Returns a DoubleBuffer wrapper of the Csound audio output working buffer
     * (spout). Enables external software to read audio from Csound after
     * calling csoundPerformKsmps. The length of the DoubleBuffer is set to
     * ksmps * nchnls.
     *
     * @return DoubleBuffer wrapper of the Csound audio output working buffer
     * (spout).
     */
    public DoubleBuffer getSpout() {
        ByteBuffer buffer = csoundGetSpout(csoundPtr);
        DoubleBuffer retVal = null;

        if (buffer != null) {
            buffer.order(ByteOrder.nativeOrder());
            retVal = buffer.asDoubleBuffer();
        }
        return retVal;
    }

    /**
     * Sets the value of control channel identified by name.
     *
     *
     * @param name Name of channel.
     * @param value Value to set.
     */
    public void setChannel(String name, double value) {
        csoundSetControlChannel(csoundPtr, name, value);
    }

    /**
     * Sets the string channel identified by channelName with channelValue.
     *
     * @param channelName Name of channel.
     * @param channelValue Value to set.
     */
    public void setStringChannel(String channelName, String channelValue) {
        csoundSetStringChannel(csoundPtr, channelName, channelValue);
    }

    /**
     * Sets a MessageCallback to be called by Csound to print an informational
     * message.This callback is never called in --realtime mode.
     *
     * @param msgCallback Callback to execute to print messages.
     */
    public void setMessageCallback(MessageCallback msgCallback) {
        csoundSetMessageCallback(csoundPtr, msgCallback);
        this.messageCallback = msgCallback;
    }

    /**
     * Returns a DoubleBuffer that wraps the data pointer for a control channel.
     * Allows efficient reading and writing of the channel as it does not have
     * to look up the channel each time as it does with setChannel().
     *
     * @param name Name of control channel
     * @return DoubleBuffer that wraps control channel data pointer.
     */
    public DoubleBuffer getControlChannelPtr(String name) {
        ByteBuffer buffer = csoundGetChannelPtr(csoundPtr, name,
                CSOUND_CONTROL_CHANNEL | CSOUND_INPUT_CHANNEL | CSOUND_OUTPUT_CHANNEL);
        DoubleBuffer retVal = null;

        if (buffer != null) {
            buffer.order(ByteOrder.nativeOrder());
            retVal = buffer.asDoubleBuffer();
        }
        return retVal;
    }

    public DoubleBuffer getAudioChannelPtr(String name) {
        ByteBuffer buffer = csoundGetChannelPtr(csoundPtr, name,
                CSOUND_AUDIO_CHANNEL | CSOUND_INPUT_CHANNEL | CSOUND_OUTPUT_CHANNEL);

        DoubleBuffer retVal = null;

        if (buffer != null) {
            buffer.order(ByteOrder.nativeOrder());
            retVal = buffer.asDoubleBuffer();
        }

        return retVal;
    }
}
