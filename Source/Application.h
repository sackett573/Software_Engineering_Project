#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QString>
#include <QDebug>
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

    Q_PROPERTY(int docIndex READ currentIndex NOTIFY documentIndexChanged)

public:
    Application();

    Document* getCurrentDocument();

    int currentIndex() const {return m_data.m_currentDocIndex;}

    int cursorPosition() const {return m_data.cursorPosition;}

    void setCursorPosition(int newPos) {m_data.cursorPosition = newPos;}

    Q_INVOKABLE void open_document(const QString& s)
    {
        m_FileManager.open_document(s.toStdString());
        emit documentChanged();
    }

    Q_INVOKABLE void close_document(int docIndex)
    {
        m_FileManager.close_document(docIndex);
    }

    Q_INVOKABLE void save_document(int docIndex)
    {
        m_FileManager.save_document(docIndex);
    }

    Q_INVOKABLE void cut(int docIndex, unsigned int begindex, unsigned int endex)
    {
        m_DocManager.cut(docIndex, begindex, endex);
        emit documentChanged();
    }

    Q_INVOKABLE void copy(int docIndex, unsigned int begindex, unsigned int endex)
    {
        m_DocManager.copy(docIndex, begindex, endex);
    }

    Q_INVOKABLE void paste(int docIndex, unsigned int index)
    {
        m_DocManager.paste(docIndex, index);
        emit documentChanged();
    }

    Q_INVOKABLE void find(int docIndex, const QString& token)
    {
        m_DocManager.find(docIndex, token.toStdString());
    }

    Q_INVOKABLE void replace(int docIndex, const QString& token, const QString& replaceToken)
    {
        m_DocManager.replace(docIndex, token.toStdString(), replaceToken.toStdString());
        emit documentChanged();
    }

    Q_INVOKABLE void insert(int docIndex, unsigned int pos, QString a)
    {
        m_DocManager.insert(docIndex, pos, a.toStdString()[0]);
        emit documentChanged();
    }

signals:
    void documentChanged();

    void documentIndexChanged();

    void cursorMoved();

private:
    ApplicationData m_data;
    DocumentManager m_DocManager;
    FileManager m_FileManager;
    Parser m_Parser;
};

#endif // APPLICATION_H
