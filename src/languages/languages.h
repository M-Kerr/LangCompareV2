#pragma once

#include <QFileInfo>
#include "cpp_code.h"
#include "python_code.h"

QStringList LANGUAGES = {"C++", "Python"};

// Builds a Code subclass according to the submitted file's language, and 
// returns it as a Code*, or nullptr on failure.
Code *code_factory(const QString &language, const QString &file_name,
                   QObject *parent = nullptr)
{
    // C++
    if (language.toLower() == "c++" || language.toLower() == "cpp")
    {
        QFileInfo file("code/cpp/" + file_name);
        if (file.exists())
        {
            return new Cpp_Code(file, parent);
        }
        else
        {
            return nullptr;
        }
    }
    // Python
    else if (language.toLower() == "python")
    {
        QFileInfo file("code/py/" + file_name);
        if (file.exists())
        {
            return new Python_Code(file, parent);
        }
        else
        {
            return nullptr;
        }
    }
    else
    {
        return nullptr;
    }
}
