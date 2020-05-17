#!/bin/sh
install_name_tool -add_rpath /Library/Frameworks src/main/resources/com/kunstmusik/csoundjni/native/libcsoundjni.jnilib
install_name_tool -add_rpath /usr/local/opt/csound/Frameworks src/main/resources/com/kunstmusik/csoundjni/native/libcsoundjni.jnilib
