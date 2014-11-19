#ifndef APPLICATIONDATA_H
#define APPLICATIONDATA_H

#include "Style.h"
#include "Document.h"

#include <string>
#include <map>
#include <vector>

struct ApplicationData
{
    ApplicationData() :
        m_currentDocIndex(-1)
        {}

    int cursorPosition;
    int m_currentDocIndex;
    std::map<std::string, StyleEntry> m_styles;
    std::vector<Document> m_documents;
};

#endif // APPLICATIONDATA_H
