
#include "Application.h"

Application::Application() :
    m_currentDocIndex(-1)
{
    // test
    Document * doc = new Document;
    std::string s = "#include <iostream>\n\nint main()\n{\n    std::cout << \"hello!\" << std::endl;\n}";
    doc->m_filename = "test.h";
    doc->m_buffer = new char[s.size()];
    for(uint i = 0; i < s.size(); i++)
    {
        doc->m_buffer[i] = s[i];
    }

    doc->m_bufferLength = s.size();
    m_data.m_documents.push_back(*doc);
    m_currentDocIndex = 0;
    // test
}

Document* Application::getCurrentDocument()
{
    if(m_currentDocIndex != -1)
        return &m_data.m_documents[m_currentDocIndex];
    else
        return NULL;
}
