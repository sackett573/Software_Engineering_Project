#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QString>
#include "ApplicationData.h"
#include "DocumentManager.h"
#include "FileManager.h"
#include "Parser.h"

class Application :
    public QObject
{
    Q_OBJECT

    Q_PROPERTY(Document* document READ getCurrentDocument NOTIFY documentChanged)

    Q_PROPERTY(int cursorPosition READ cursorPosition WRITE setCursorPosition NOTIFY cursorMoved)

public:
    Application();

    Document* getCurrentDocument();

    int cursorPosition() const {return m_data.cursorPosition;}

    void setCursorPosition(int newPos) {m_data.cursorPosition = newPos;}

    Q_INVOKABLE void open_document(const QString& s) {m_FileManager.open_document(s.toStdString()); emit documentChanged();}

    Q_INVOKABLE void close_document(const QString& s) {m_FileManager.close_document(s.toStdString());}

    Q_INVOKABLE void save_document(const QString& s) {m_FileManager.save_document(s.toStdString());}


signals:
    void documentChanged();

    void cursorMoved();

private:
    ApplicationData m_data;
    DocumentManager m_DocManager;
    FileManager m_FileManager;
    Parser m_Parser;
};

#endif // APPLICATION_H
