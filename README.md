Goal:
    An application to compare the runtime of similar code constructs in
    multiple languages.

Why:
    A common question among new developers and topic of conversation amongst 
    seasoned developers is the runtime efficiency of languages.
    This application will allow the direct (somewhat) comparison of algorithms
    and code between languages.

How:
    The main application is currently built in C++, using Qt.
    The user provides code files using the languages of their choice. The 
    application will compile (if necessary) and run the files in a subprocess, 
    using a wrapper that times how long it takes for the code to complete,
    returning the results back to the application.

Current program structure:
    The "code/<language_name>/" subdirectories contain user submitted code 
    files. Inside the code directory is a collection of wrapper files for each
    supported language. The job of each wrapper file is to load the user code,
    initialize a timer, execute the user code, and relay the timing results
    back to the application (currently via pipe, will refactor to sockets soon
    for cross platform compatibility).

Detailed program structure:

    ./src/languages/code.h 
        User submitted code files are abstracted into a Code object containing
        the language, file information, and timing results.
        A Code subclass is created for each language, where the language's
        specific build and run rules are implemented within the Code.execute()
        method. The Code.execute() method should ultimately run the language's
        wrapper file, passing the user code to the wrapper file.

        E.g., Code subclasses:
            ./src/languages/cpp_code.h      //Cpp_Code: public Code
            ./src/languages/python_code.h   //Python_Code: public Code
            etc.

    ./src/languages/languages.h
        Root languages header, contains the factory function called within main
        to build Code objects.

    ./code/<language>/<user_code>
        User submitted code files are expected to have an execute() function 
        containing the code to benchmark.

    ./code/wrapper.<language_extension>
        Through either a macro or command line argument, the wrapper file for
        each language receives the code to wrap; a write pipe file descriptor;
        and optionally receives the number of iterations to execute; and a 
        timeout (seconds) to stop execution upon expiration.

        The wrapper file is expected to:

                - embed the user code,
                - initialize a timer,
                - call the execute() function,
                - stop the timer,
                - average the timing results of the execute() iterations,
                - return the results through the write pipe.
    
    ./src/main.cpp
        The main call first builds a list of Code objects through user input.
        Then it opens a pipe, calls each Code object's execute() method,  
        passing the pipe file descriptor as an argument in order to communicate
        the timing results. Finally, it prints each Code object's results.


How to contribute support for a language:

    * wrapper file
        - timing support
        - embed user code
        - return timing results

    * ./src/languages/<language>_code.h

        - <LANGAUGE>_WRAPPER_FILE macro
            - This macro contains the relative path to the language's wrapper
              file
        - <Language>_Code Code subclass

      ./src/languages/<language>_code.cpp

        - <Language>_Code::execute() method implementation

                (a ./src/languages/compile_and_run_failure.h exception is
                provided in the languages directory to signal compilation 
                failures)
    
    * languages.h 
        - language list
        - code_factory section
    

