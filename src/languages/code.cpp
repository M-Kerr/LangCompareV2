#include "code.h"

Code::Code(const QString language, const QFileInfo file,
           QObject *parent, unsigned iters, unsigned limit)

    : QObject(parent), language_(language), file_(file),
      iters_(iters), limit_(limit), results(this)
{
}

const QString &Code::get_language() const
{
    return language_;
}

const QFileInfo &Code::get_file() const
{
    return file_;
}

const QString Code::file_name() const
{
    return file_.completeBaseName();
}

const QString Code::file_path() const
{
    return file_.absoluteFilePath();
}

const QString Code::output_file() const
{
    return file_.absolutePath() + "/" + file_name();
}

const unsigned &Code::get_iters() const
{
    return iters_;
}

const unsigned &Code::get_limit() const
{
    return limit_;
}

const Results &Code::get_results() const
{
    return results;
}

void Code::print_results() const
{
    qInfo().noquote().nospace() << "\n\t" << language_ << " "
                                << file_.completeBaseName() << " results:";
    results.print();
}
