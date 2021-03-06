
#include "Application.h"

Application::Application() :
    m_DocManager(&m_data),
    m_FileManager(&m_data, this),
    m_Parser(&m_data),
    m_data(this)
{
}

Document* Application::getCurrentDocument()
{
    if(m_data.m_currentDocIndex != -1)
        return m_data.m_documents[m_data.m_currentDocIndex];
    else
        return NULL;
}
