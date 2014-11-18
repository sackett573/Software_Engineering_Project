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

    Q_PROPERTY(int cursorPosition READ cursorPosition WRITE setCursorPosition NOTIFY cursorMoved)

    Document* getCurrentDocument();

    int cursorPosition() const {return m_data.cursorPosition;}

    void setCursorPosition(int newPos) {m_data.cursorPosition = newPos;}

signals:
    void documentChanged();

    void cursorMoved();

private:
    int m_currentDocIndex;
    ApplicationData m_data;
};

#endif // APPLICATION_H
