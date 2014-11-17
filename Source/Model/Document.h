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
    Document() :
        m_buffer(NULL),
        m_bufferLength(-1)
    {}

    ~Document()
    {
        if(m_buffer != NULL)
            delete [] m_buffer;
    }

    Document(const Document& doc) :
        QObject(),
        m_filename(doc.m_filename),
        m_buffer(doc.m_buffer),
        m_bufferLength(doc.m_bufferLength),
        m_styleEntries(doc.m_styleEntries)
    {}

    std::string m_filename;
    char * m_buffer;
    unsigned int m_bufferLength;
    std::vector<StyleEntry> m_styleEntries;
};

#endif // DOCUMENT_H
