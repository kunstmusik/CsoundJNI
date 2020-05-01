# CsoundJNI 

Java bindings for Csound using JNI

## Build Instructions

### Native Extensions

Compiled versions are maintained in the src/main/resources folder and packaged with the jar compiled by Maven. To compile the native extension on a platform:

1. Create a build directory 
2. cd build
3. cmake .. 
4. make install

This should build the native library and then install the native extension to the correct place.  This should only be necessary to build when the Java files with native bindings is updated. 

