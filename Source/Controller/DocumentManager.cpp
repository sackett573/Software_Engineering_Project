#include "DocumentManager.h"

void DocumentManager::copy(const std::string&, unsigned int, unsigned int) const
{
    // stub
}

void DocumentManager::cut(const std::string&, unsigned int, unsigned int)
{
    // stub
}

void DocumentManager::paste(const std::string&, unsigned int)
{
    // stub
}

int DocumentManager::find(const std::string&, const std::string&) const
{
    // stub
    return 0;
}

void DocumentManager::replace(const std::string&, const std::string&, const std::string&)
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
