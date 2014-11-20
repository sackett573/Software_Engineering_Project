#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "ApplicationData.h"

#include <string>
#include <QDebug>
#include <QFile>
#include <QUrl>

class FileManager
{
public:
    FileManager(ApplicationData* d) :
        m_AppData(d)
        {}

    bool open_document(const std::string& path);

    void close_document(int docIndex);

    bool save_document(int docIndex);

private:
    ApplicationData * const m_AppData;
};

#endif // FILEMANAGER_H
