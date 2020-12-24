#pragma once

#include <QFileInfo>
#include "cpp_code.h"
#include "python_code.h"
#include "helpers/helpers.h"

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
                   QObject *parent = nullptr);


/**
 * @brief Fills a vector with Code file objects via user input.
 */
void build_code_list(QVector<Code*> &code_files);
