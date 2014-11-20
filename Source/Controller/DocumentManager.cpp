#include "DocumentManager.h"

void DocumentManager::copy(int, unsigned int, unsigned int) const
{
    // stub
}

void DocumentManager::cut(int, unsigned int, unsigned int)
{
    // stub
}

void DocumentManager::paste(int, unsigned int)
{
    // stub
}

int DocumentManager::find(int, const std::string&) const
{
    // stub
    return 0;
}

void DocumentManager::replace(int, const std::string&, const std::string&)
{
    // stub
}

void DocumentManager::insert(int docIndex, unsigned int pos, char c)
{
    qDebug() << "insert func: " << c;
    Document& doc = m_AppData->m_documents[docIndex];
    std::string::iterator insertit = doc.m_buffer.begin() + pos;
    doc.m_buffer.insert(insertit, c);
}
