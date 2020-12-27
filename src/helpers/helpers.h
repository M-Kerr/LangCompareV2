#pragma once
#include <QDir>
#include <QFileInfo>
#include <QDebug>

/**
 * @brief Clears the terminal
 */
void clear_console();

/** Ensures working dir is the application's directory.
 *  Required for correct paths to user submitted code.
 */
bool set_cwd_to_application_dir(char *argv[]);
