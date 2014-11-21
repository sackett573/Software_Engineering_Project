#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "ApplicationData.h"

#include <string>
#include <QDebug>
#include <QFile>
#include <QUrl>

class FileManager :
    public QObject
{
    Q_OBJECT

public:
    FileManager(ApplicationData* d, QObject * parent) :
        QObject(parent),
        m_AppData(d)
        {}

    int create_document(const QString& name);

    int open_document(const QString& path);

    void close_document(int docIndex);

    bool save_document(const QString& path);

    bool save_document_by_index(int docIndex);

private:
    ApplicationData * const m_AppData;
};

#endif // FILEMANAGER_H
