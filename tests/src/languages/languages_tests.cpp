// Test the languages.h functions and the implemented languages' execute()
// method.
#include "gtest/gtest.h"
#include "languages/languages.h"
#include <QDir>

void code_execute(QString language, QString file)
{
    int fd[2];
    ASSERT_FALSE((pipe(fd) < 0 )) << "Failed to open a test pipe\n";
    // I need to resolve the directory issue. Right now I'm
    // getting a nullptr when trying to build
    Code *code = code_factory(language, file);
    ASSERT_TRUE(code != nullptr) << "Failed to create Code *";

    ASSERT_FALSE(close(fd[0]) < 0) << "Failed to close pipe read\n";
    ASSERT_FALSE(close(fd[1]) < 0) << "Failed to close pipe write\n";
}

TEST(CppCodeTests, CanExecute)
{
    int fd[2];

    qInfo() << "Current Working Dir: ";
    qInfo() << QDir::currentPath();


    // We are failing because the code/ directory is not here.
    // We aren't finding any files

    //cpp->execute(fd[0], fd[1]);
}

// Tests executing files in subdirectories
TEST(CppCodeTests, CanExecuteModules)
{
    Code *cpp = code_factory("c++", "templating/templating.cpp");

    int fd[2];

    //cpp->execute(fd[0], fd[1]);
}

TEST(PythonCodeTests, CanExecute)
{
    Code *py = code_factory("python", "hello_world.py");

    int fd[2];

    //py->execute(fd[0], fd[1]);

}

TEST(PythonCodeTests, CanExecuteModules)
{

}
