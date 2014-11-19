#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include "ApplicationData.h"

#include <string>
#include <QDebug>

class DocumentManager
{
public:
    DocumentManager(ApplicationData* d) :
        m_AppData(d)
        {}

    void copy(const std::string& docName, unsigned int begindex, unsigned int endex) const;

    void cut(const std::string& docName, unsigned int begindex, unsigned int endex);

    void paste(const std::string& docName, unsigned int index);

    int find(const std::string& docName, const std::string& token) const;

    void replace(const std::string& docName, const std::string& token, const std::string& replace);

    void insert(int docIndex, unsigned int index, char toInsert);

private:
    ApplicationData * const m_AppData;
};

#endif // DOCUMENTMANAGER_H
