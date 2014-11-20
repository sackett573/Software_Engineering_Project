#ifndef DOCUMENTMANAGER_H
#define DOCUMENTMANAGER_H

#include "ApplicationData.h"

#include <string>
#include <QDebug>
#include <QClipboard>
#include <QApplication>

class DocumentManager
{
public:
    DocumentManager(ApplicationData* d) :
        m_AppData(d)
        {}

    void copy(int docIndex, unsigned int begindex, unsigned int endex) const;

    void cut(int docIndex, unsigned int begindex, unsigned int endex);

    int paste(int docIndex, unsigned int index);

    int find(int docIndex, const std::string& token) const;

    void replace(int docIndex, const std::string& token, const std::string& replace);

    void insert(int docIndex, unsigned int index, char toInsert);

    void backspace(int docIndex, unsigned int index);

private:
    ApplicationData * const m_AppData;
};

#endif // DOCUMENTMANAGER_H
