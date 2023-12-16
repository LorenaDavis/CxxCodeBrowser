#ifndef NAV_REPORTFILELIST_H
#define NAV_REPORTFILELIST_H

#include "TableReport.h"
#include <QObject>
#include <QString>
#include <QStringList>
#include <string>

namespace Nav {

class Project;
class File;

class ReportFileList : public TableReport
{
    Q_OBJECT
public:
    explicit ReportFileList(Project &project, QObject *parent = NULL);
    QString title();
    QStringList columns();
    int rowCount();
    const char *text(int row, int column, std::string &tempBuf);
    void select(int row);
    bool activate(int row) { select(row); return true; }

private:
    Project &m_project;
    QStringList m_paths;
};

} // namespace Nav

#endif // NAV_REPORTFILELIST_H
