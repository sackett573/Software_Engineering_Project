#ifndef APPLICATIONDATA_H
#define APPLICATIONDATA_H

#include "Style.h"
#include "Document.h"

#include <string>
#include <map>
#include <QVector>
#include <QObject>

class ApplicationData :
    public QObject
{
    Q_OBJECT

public:
    ApplicationData(QObject * parent = NULL) :
        QObject(parent),
        m_currentDocIndex(-1)
        {}

    int cursorPosition;
    int m_currentDocIndex;
    std::map<std::string, StyleEntry> m_styles;
    QList<Document *> m_documents;
};

#endif // APPLICATIONDATA_H
