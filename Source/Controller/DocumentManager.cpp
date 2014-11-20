#include "DocumentManager.h"

void DocumentManager::copy(int docIndex, unsigned int begindex, unsigned int endex) const
{
    QClipboard * clipboard = QApplication::clipboard();

    std::string seg = m_AppData->m_documents[docIndex].m_buffer.substr(begindex, endex - begindex);
    QString segment = QString::fromStdString(seg);
    clipboard->setText(segment);

    qDebug() << "text copied: " + segment;
}

void DocumentManager::cut(int, unsigned int, unsigned int)
{
    // stub
}

int DocumentManager::paste(int docIndex, unsigned int pos)
{
    QClipboard * clipboard = QApplication::clipboard();

    Document& doc = m_AppData->m_documents[docIndex];
    std::string s = clipboard->text().toStdString();
    doc.m_buffer.insert(pos, s);

    return s.size();
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
    Document& doc = m_AppData->m_documents[docIndex];
    std::string::iterator insertit = doc.m_buffer.begin() + pos;
    doc.m_buffer.insert(insertit, c);
}

void DocumentManager::backspace(int docIndex, unsigned int pos)
{
    Document& doc = m_AppData->m_documents[docIndex];
    std::string::iterator removeit = doc.m_buffer.begin() + pos;
    doc.m_buffer.erase(removeit);
}
