#include "gtest/gtest.h"
#include "languages/code.h"

// Make concrete class to test ABC
class Concrete_Code: public Code
{
public:
    explicit Concrete_Code(const QString language, const QString file_name,
                  QObject *parent = nullptr, unsigned iters = 1,
                  unsigned limit = 0)
        : Code(language, file_name, parent, iters, limit){}

    virtual bool execute(int read_fd, int write_fd)
    {
        static_cast<void>(read_fd);
        static_cast<void>(write_fd);
        return true;
    }
};

class CodeTestsF: public ::testing::Test
{
public:
    CodeTestsF()
        : file_("/tmp/none"), code{"language", file_} {}

    QString file_;
    Concrete_Code code;
};


TEST_F(CodeTestsF, CanGetLanguage)
{
    ASSERT_STREQ("language", code.get_language().toLatin1());
}

TEST_F(CodeTestsF, CanGetFile)
{
    ASSERT_STREQ(typeid(QFileInfo).name(), typeid(code.get_file()).name());
}

TEST_F(CodeTestsF, CanGetIters)
{
    ASSERT_EQ(1, code.get_iters());
}

TEST_F(CodeTestsF, CanGetLimit)
{
    ASSERT_EQ(0, code.get_limit());
}
