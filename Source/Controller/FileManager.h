#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "ApplicationData.h"

#include <string>

class FileManager
{
public:
    FileManager(ApplicationData* d) :
        m_AppData(d)
        {}

    bool open_document(const std::string& path);

    void close_document(const std::string& path);

    bool save_document(const std::string& path);

private:
    ApplicationData * const m_AppData;
};

#endif // FILEMANAGER_H
