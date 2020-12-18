#pragma once

#include <QFileInfo>
#include "cpp_code.h"
#include "python_code.h"

QStringList LANGUAGES = {"C++", "Python"};

// Builds a Code subclass according to the submitted file's language, and 
// returns it as a Code*, or nullptr on failure.
Code *code_factory(const QString &language, const QString &file,
                   QObject *parent = nullptr)
{
    // C++
    if (language.toLower() == "c++" || language.toLower() == "cpp")
    {
        QFileInfo path("code/cpp/" + file);
        if (path.exists())
        {
            return new Cpp_Code(file, path.absoluteFilePath(), parent);
        }
        else
        {
            return nullptr;
        }
    }
    // Python
    else if (language.toLower() == "python")
    {
        QFileInfo path("code/py/" + file);
        if (path.exists())
        {
            return new Python_Code(file, path.absoluteFilePath(), parent);
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
