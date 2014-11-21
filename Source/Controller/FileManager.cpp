#include "FileManager.h"

int FileManager::create_document(const QString &name)
{
    Document * doc = new Document(m_AppData);
    doc->m_path = "";
    doc->m_buffer = "";
    doc->m_filename = name;
    m_AppData->m_documents.push_back(doc);
    m_AppData->m_currentDocIndex = m_AppData->m_documents.size() - 1;
    return m_AppData->m_currentDocIndex;
}

int FileManager::open_document(const QString& s)
{
    QUrl pathUrl(s);
    QFile f(pathUrl.toLocalFile());
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    Document * doc = new Document(m_AppData);
    doc->m_path = pathUrl.path(QUrl::FullyDecoded);
    doc->m_filename = pathUrl.fileName();
    QTextStream in(&f);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        doc->m_buffer.append(line);
        doc->m_buffer.push_back('\n');
    }
    m_AppData->m_documents.push_back(doc);
    f.close();
    m_AppData->m_currentDocIndex = m_AppData->m_documents.size() - 1;
    return m_AppData->m_currentDocIndex;
}

void FileManager::close_document(int docIndex)
{
    auto eraseit = m_AppData->m_documents.begin() + docIndex;
    m_AppData->m_documents.erase(eraseit);
    if(m_AppData->m_currentDocIndex > 0)
        m_AppData->m_currentDocIndex--;

    if(m_AppData->m_documents.empty())
        m_AppData->m_currentDocIndex = -1;
}

bool FileManager::save_document(const QString& path)
{
    QUrl pathUrl(path);
    QFile f(pathUrl.toLocalFile());
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&f);
    Document* doc = m_AppData->m_documents[m_AppData->m_currentDocIndex];
    out << doc->m_buffer;
    f.close();
    return true;
}

bool FileManager::save_document_by_index(int)
{
    Document * doc = m_AppData->m_documents[m_AppData->m_currentDocIndex];
    QUrl pathUrl(doc->m_path);
    QFile f(pathUrl.toLocalFile());
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QTextStream out(&f);
    out << doc->m_buffer;
    f.close();
    return true;
}
