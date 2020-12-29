//! Test the languages.h functions and the Code subclass' execute() method
#include "gtest/gtest.h"
#include "languages/languages.h"
#include <QDir>

class LanguagesF : public testing::Test
{
    int fd[2];

public:
    ~LanguagesF()
    {if (code) delete code;}

    void SetUp() override
    {
        ASSERT_FALSE((pipe(fd) < 0 )) << "Failed to open a test pipe\n";
    }

    void TearDown() override
    {
        ASSERT_FALSE(close(fd[0]) < 0) << "Failed to close pipe read\n";
        ASSERT_FALSE(close(fd[1]) < 0) << "Failed to close pipe write\n";
    }

    void execute(QString language, QString file,
                  long iters = 1, long timeout = 0)
    {
        if (code) delete code;
        code = code_factory(language, file, nullptr, iters, timeout);
        ASSERT_TRUE(code != nullptr) << "Failed to create Code *";
        EXPECT_TRUE(code->execute(fd[0], fd[1])) << "execute() failed";
    }

    Code *code = nullptr;
};

TEST_F(LanguagesF, CanExecuteCpp)
{
    execute("c++", "hello_world.cpp");
}

//! Tests executing files in subdirectories
TEST_F(LanguagesF, CanExecuteCppModules)
{
    execute("c++", "templating/templating.cpp");
}

//TEST_F(LanguagesF, CanExecuteCppIters)
//{
//    FAIL() << "NOT IMPLEMENTED";
//}

TEST_F(LanguagesF, CanTimeoutCpp)
{
    execute("c++", "timeout.cpp", 1, 1);
    EXPECT_FALSE(code->get_results().get_success());

    execute("c++", "timeout.cpp", 1, 2);
    EXPECT_TRUE(code->get_results().get_success());
}

TEST_F(LanguagesF, CanExecutePy)
{
    execute("python", "hello_world.py");
}

TEST_F(LanguagesF, CanExecutePyModules)
{
    execute("python", "test_package/hello_module.py");
}

//TEST_F(LanguagesF, CanExecutePyIters)
//{
//    FAIL() << "NOT IMPLEMENTED";
//}
//
TEST_F(LanguagesF, CanTimeoutPy)
{
    execute("python", "timeout.py", 1, 1);
    EXPECT_FALSE(code->get_results().get_success());

    execute("python", "timeout.py", 1, 2);
    EXPECT_TRUE(code->get_results().get_success());
}
