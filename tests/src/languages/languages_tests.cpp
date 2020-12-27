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

    EXPECT_TRUE(code->execute(fd[0], fd[1])) << "execute() failed";

    ASSERT_FALSE(close(fd[0]) < 0) << "Failed to close pipe read\n";
    ASSERT_FALSE(close(fd[1]) < 0) << "Failed to close pipe write\n";
}

TEST(CodeCppTests, CanExecute)
{
    code_execute("c++", "hello_world.cpp");
}

// Tests executing files in subdirectories
TEST(CodeCppTests, CanExecuteModules)
{
    code_execute("c++", "templating/templating.cpp");
}

TEST(CodePythonTests, CanExecute)
{
    code_execute("python", "hello_world.py");
}

TEST(CodePythonTests, CanExecuteModules)
{
    code_execute("python", "test_package/hello_module.py");
}
