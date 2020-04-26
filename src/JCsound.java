package com.kunstmusik.jcsound;

public class JCsound {

    public native long csoundCreate(int initFlags);
    public native long csoundReset(long csoundRef);
}
