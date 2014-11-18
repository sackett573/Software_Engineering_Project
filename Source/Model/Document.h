#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Style.h"
#include <QObject>
#include <string>
#include <vector>

class Document :
    public QObject
{
    Q_OBJECT

public:
    Document() {}

    Document(const Document& doc) :
        QObject(),
        m_filename(doc.m_filename),
        m_buffer(doc.m_buffer),
        m_styleEntries(doc.m_styleEntries)
    {}

    std::string m_filename;
    std::string m_buffer;
    std::vector<StyleEntry> m_styleEntries;
};

#endif // DOCUMENT_H
