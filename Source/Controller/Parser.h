#ifndef PARSER_H
#define PARSER_H

#include "ApplicationData.h"

#include <string>

class Parser
{
public:
    Parser(ApplicationData* d) :
        m_AppData(d)
        {}

    void reparse(const std::string& docName, unsigned int begindex, unsigned int endex);

    void parse(const std::string& docName);

private:
    ApplicationData* const m_AppData;
};

#endif // PARSER_H
