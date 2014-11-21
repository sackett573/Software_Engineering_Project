#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QQmlListProperty>
#include "ApplicationData.h"
#include "DocumentManager.h"
#include "FileManager.h"
#include "Parser.h"

class Application :
    public QObject
{
    Q_OBJECT

    Q_PROPERTY(int cursorPosition READ cursorPosition WRITE setCursorPosition NOTIFY cursorMoved)

    Q_PROPERTY(int docIndex READ currentIndex WRITE setCurrentIndex NOTIFY documentIndexChanged)

public:
    Application();

    Document* getCurrentDocument();

    int currentIndex() const {return m_data.m_currentDocIndex;}

    int cursorPosition() const {return m_data.cursorPosition;}

    void setCurrentIndex(int index) {m_data.m_currentDocIndex = index;}

    void setCursorPosition(int newPos) {m_data.cursorPosition = newPos;}

    Q_INVOKABLE Document* get_document_at(int docIndex)
    {
        if(docIndex != -1)
            return m_data.m_documents[docIndex];
        else
            return NULL;
    }

    Q_INVOKABLE int create_document(const QString& s)
    {
        return m_FileManager.create_document(s);
    }

    Q_INVOKABLE int open_document(const QString& s)
    {
        return m_FileManager.open_document(s);
        emit documentChanged();
    }

    Q_INVOKABLE void close_document(int docIndex)
    {
        m_FileManager.close_document(docIndex);
    }

    Q_INVOKABLE void save_document(const QString& s)
    {
        m_FileManager.save_document(s);
    }

    Q_INVOKABLE void save_document_by_index(int docIndex)
    {
        m_FileManager.save_document_by_index(docIndex);
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

    Q_INVOKABLE int paste(int docIndex, unsigned int index)
    {
        int size = m_DocManager.paste(docIndex, index);
        emit documentChanged();
        return size;
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

    Q_INVOKABLE void backspace(int docIndex, unsigned int pos)
    {
        m_DocManager.backspace(docIndex, pos);
        emit documentChanged();
    }

signals:
    void documentChanged();

    void documentIndexChanged();

    void cursorMoved();

private:
    int m_currentDocIndex;
    ApplicationData m_data;
    DocumentManager m_DocManager;
    FileManager m_FileManager;
    Parser m_Parser;
};

#endif // APPLICATION_H
