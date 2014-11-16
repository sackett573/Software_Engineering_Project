#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Style.h"
#include <string>
#include <vector>

class Document
{
public:
    std::string m_filename;
    char * m_buffer;
    unsigned int m_bufferLength;
    std::vector<StyleEntry> m_styleEntries;
};

#endif // DOCUMENT_H
