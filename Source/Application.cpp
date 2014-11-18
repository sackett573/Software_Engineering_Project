
#include "Application.h"

Application::Application() :
    m_currentDocIndex(-1)
{
    // test
    Document doc;
    doc.m_filename = "test.h";
    doc.m_buffer = "#include <iostream>\n\nint main()\n{\n    std::cout << \"hello!\" << std::endl;\n}";
    m_data.m_documents.push_back(doc);
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
