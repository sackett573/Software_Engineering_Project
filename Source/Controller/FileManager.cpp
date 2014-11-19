#include "FileManager.h"

bool FileManager::open_document(const std::string& s)
{
    QUrl pathUrl(QString::fromStdString(s));
    QFile f(pathUrl.toLocalFile());
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    Document doc;
    doc.m_filename = pathUrl.path(QUrl::FullyDecoded).toStdString();
    QTextStream in(&f);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        doc.m_buffer.append(line.toStdString());
        doc.m_buffer.push_back('\n');
    }
    m_AppData->m_documents.push_back(doc);
    f.close();
    m_AppData->m_currentDocIndex = m_AppData->m_documents.size() - 1;

    return true;
}

void FileManager::close_document(const std::string &)
{
    // stub
}

bool FileManager::save_document(const std::string &)
{
    // stub
    return true;
}
