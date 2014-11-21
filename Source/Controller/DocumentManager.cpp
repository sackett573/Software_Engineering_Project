#include "DocumentManager.h"

void DocumentManager::copy(int docIndex, unsigned int begindex, unsigned int endex) const
{
    QClipboard * clipboard = QApplication::clipboard();

    QString seg = m_AppData->m_documents[docIndex]->m_buffer.mid(begindex, endex - begindex);
    clipboard->setText(seg);
}

void DocumentManager::cut(int docIndex, unsigned int begindex, unsigned int endex)
{
    QClipboard * clipboard = QApplication::clipboard();

    QString seg = m_AppData->m_documents[docIndex]->m_buffer.mid(begindex, endex - begindex);
    clipboard->setText(seg);

    m_AppData->m_documents[docIndex]->m_buffer.remove(begindex, endex - begindex);
}

int DocumentManager::paste(int docIndex, unsigned int pos)
{
    QClipboard * clipboard = QApplication::clipboard();

    Document * doc = m_AppData->m_documents[docIndex];
    QString s = clipboard->text();
    doc->m_buffer.insert(pos, s);

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
    Document * doc = m_AppData->m_documents[docIndex];
    doc->m_buffer.insert(pos, c);
}

void DocumentManager::backspace(int docIndex, unsigned int pos)
{
    Document * doc = m_AppData->m_documents[docIndex];
    doc->m_buffer.remove(pos, 1);
}
