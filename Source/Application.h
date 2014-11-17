#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include "ApplicationData.h"

class Application :
    public QObject
{
    Q_OBJECT

public:
    Application();

    Q_PROPERTY(Document* document READ getCurrentDocument NOTIFY documentChanged)

    Document* getCurrentDocument();

signals:
    void documentChanged();

private:
    int m_currentDocIndex;
    ApplicationData m_data;
};

#endif // APPLICATION_H
