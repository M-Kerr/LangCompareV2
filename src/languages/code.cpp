#include "code.h"

Code::Code(const QString language, const QFileInfo file,
           QObject *parent, unsigned iters, unsigned limit)

    : QObject(parent), _language(language), _file(file),
      _iters(iters), _limit(limit), results(this)
{
}

const QString &Code::get_language() const
{
    return _language;
}

const QFileInfo &Code::get_file() const
{
    return _file;
}

const unsigned &Code::get_iters() const
{
    return _iters;
}

const unsigned &Code::get_limit() const
{
    return _limit;
}

const Results &Code::get_results() const
{
    return results;
}

void Code::print_results() const
{
    qInfo().noquote().nospace() << "\n\t" << _language << " "
                                << _file.completeBaseName() << " results:";
    results.print();
}
