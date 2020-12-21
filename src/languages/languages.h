#pragma once

#include <QFileInfo>
#include "cpp_code.h"
#include "python_code.h"

static const QStringList LANGUAGES = {"C++", "Python"};

/**
 * @brief code_factory builds Code subclasses.
 *
 * Builds a Code subclass according to the submitted file's language
 *
 * @param language code file language
 * @param file_name code file name and extension
 * @param parent Q_OBJECT parent pointer
 * @return Code *, nullptr on failure
 */
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
