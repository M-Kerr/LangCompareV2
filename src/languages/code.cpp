#include "code.h"

Code::Code(const QString language, const QString file, const QString path,
           QObject *parent, unsigned iters, unsigned limit)
    : QObject(parent), _language(language), _file_name(file), _file_path(path),
      _iters(iters), _limit(limit), results(this)
{
}

const QString &Code::get_language()
{
    return _language;
}

const QString &Code::get_file_name()
{
    return _file_name;
}

const QString &Code::get_file_path()
{
    return _file_path;
}

const unsigned &Code::get_iters()
{
    return _iters;
}

const unsigned &Code::get_limit()
{
    return _limit;
}

const Results &Code::get_results()
{
    return results;
}

void Code::print_results()
{
    qInfo() << "\n\t" << _file_name << " results:";
    results.print();
}
