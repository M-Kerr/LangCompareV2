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
    
    1.) Build a wrapper file in the language that matches the requirements for
        wrapper files enumerated in the "Detailed program structure" section.
        The wrapper will execute through a system() call receiving command
        line arguments.
        The timer should begin execution as close as possible to the execute()
        call, and stop upon its return.

        Use the existing wrapper files for inspiration.

    2.) Create a Code subclass using the file naming convention 
        <language>_code.h and class name <Language_Name_Code>.
        
        The <language>_code.h header file should contain a global QString
        variable containing the path to the language's wrapper file:

static const QString <LANGUAGE>_WRAPPER_FILE("code/wrapper.<extension>");

        
        Implement the class' execute method with the following signature:

                bool execute(int read_fd, int write_fd) override;

        The execute method should:

            Compile the wrapper and user code together if necessary, then run
            the wrapper, passing the required command line arguments and any
            others if necessary. Finally, the method should call
            this->results.receive(read_fd) before returning successfully.

            Additionally, the compile and run calls should support the user
            adding a single file directly in the code/<language_abbreviation>/ directory, 
            or multiple files within a package.

                See cpp_code.cpp for an example of a compiled language,
                and python_code.cpp for an interpreted language.

            *note*
            A pipe is used to communicate when running instead of stdin/stdout 
            in the event that the user code is timing IO operations.

            Throw a Compile_And_Run_Failure in the event of a failure during
            the compilation or run system() calls, using the error code
            returned from the call.

    3.) Inside /src/languages/languages.h:

            - #include the <language>_code.h header file
        
            - Add the language name to the LANGAUGES QStringList

            - Add an `else if` segment to the `code_factory` function,
              building and returning a pointer to a <Language>_Code object.
              The segment should follow this basic pattern:

    // <Language>
    else if (language.toLower() == "<language>")
    {
        QFileInfo file("code/<language_abbreviation>/" + file_name);
        if (file.exists())
        {
            return new <Language>_Code(file, parent);
        }
        else
        {
            return nullptr;
        }

    
    4.) Add a code/<language_abbreviation> directory and an example hello_world
        user file that prints the string "Hello, World!" within an execute()
        function.

    5.) Build and run the application, testing your language's hello_world
        code.
            
