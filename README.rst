LangCompare
===========
LangCompare is a simple tool to time code in multiple languages.

|

**Place the code you'd like to time inside a function called** ``execute``.
Inside LangCompare, select the files with the code. LangCompare will compile (if
necessary) then run the files in a subprocess, timing how long it takes for the
code to complete. 

|
.. image:: https://github.com/M-Kerr/assets/blob/master/LangCompareV2/LangCompareV2.gif?raw=true


Supported Platforms 
    * Linux 
    * MacOS 

Supported Languages
    * C++ via clang++ or g++ compiler 
    * Python >= 3.7


For a description of LangCompare's architecture and information on how to
contribute, please see CONTRIBUTING.rst. We'd love contributions that contain
support for your favorite language, additional algorithm demonstrations, and
interesting features.

FAQ
---
* **What compiler settings does LangCompare use for code it compiles?**

C++ currently compiles with compiler optimizations using the -O3 flag
and supports multithreading using the -pthread flag. 
In the future, we'd like to provide the user the ability to define their
own compiler options.
      
* **My code includes additional header files or python modules, but
  LangCompare can't read them?**

If on MacOS, right click the .app and select "Show package contents",
then navigate to Contents > MacOS > code. Move the files into the "code/"
directory.

While not currently supported on Linux, you should be able to mount or
extract the AppImage and then place the files inside the "code/"
directory that resides next to the LangCompareV2 executable.
