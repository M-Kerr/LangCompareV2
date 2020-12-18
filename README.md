Goal:
    An application to compare the runtime of similar code constructs in
    multiple languages.

Why:
    A common question among new developers and topic of conversation amongst 
    seasoned developers is the runtime efficiency of languages.
    This application will allow the (somewhat) direct comparison of algorithms
    and code in general between languages.

How:
    The main application is currently built in C++, using Qt.
    The user provides code files using the languages of their choice. The 
    application will compile (if necessary) and run the files in a subprocess, 
    while the wrapper files time how long it takes for the code to complete,
    then return the results back to the application.

Current program structure:
    The application directory contains a subdirectory called "code/",
    containing user submitted code files. Inside the code directory is a
    collection of wrapper files for each supported language. The job of each
    wrapper file is to load the user code, initialize a timer, execute the user
    code, and relay the timing results back to the application (currently via
    pipe, will refactor to sockets soon for cross platform compatibility).


Detailed program structure:







How to contribute support for a language:

