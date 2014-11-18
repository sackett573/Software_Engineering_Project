#ifndef TEXTVIEWER_H
#define TEXTVIEWER_H

#include <QQuickPaintedItem>
#include <QPainter>
#include <QDebug>
#include <QString>

#include "Document.h"

class TextViewer :
    public QQuickPaintedItem
{
    Q_OBJECT

    Q_PROPERTY(Document* document READ currentDocument WRITE setDocument NOTIFY documentChanged)

    Q_PROPERTY(int cursorPos READ cursorPos WRITE setCursorPos NOTIFY cursorPosChanged)

    Q_PROPERTY(bool cursorVisible READ cursorVisible WRITE setCursorVisible NOTIFY cursorVisibilityChanged)

    Q_PROPERTY(int selectionPos READ selectionPos WRITE setSelectionPos NOTIFY selectionPosChanged)

    struct LineData
    {
        int lineStartIndex;
        int lineEndIndex;
    };

public:
    TextViewer(QQuickItem* parent = NULL) :
        QQuickPaintedItem(parent),
        m_currentDoc(NULL),
        m_cursorPos(-1)
        {}

    // Getters
    Document* currentDocument() const {return m_currentDoc;}

    int cursorPos() const {return m_cursorPos;}

    bool cursorVisible() const {return m_cursorVisible;}

    int selectionPos() const {return m_selectionPos;}

    // Setters
    void setDocument(Document* doc) {m_currentDoc = doc;}

    void setCursorPos(int pos) {m_cursorPos = pos;}

    void setCursorVisible(bool b) {m_cursorVisible = b;}

    void setSelectionPos(int pos) {m_selectionPos = pos;}

    // Invokables
    Q_INVOKABLE int getNewSelection(int x, int y);

    // Event Handlers
    void paint(QPainter *painter);

signals:
    void documentChanged();

    void cursorPosChanged();

    void cursorVisibilityChanged();

    void selectionPosChanged();

private:
    QFont m_currentFont;
    Document* m_currentDoc;
    std::map<int, LineData> m_lineData;
    int m_numLines;
    int m_cursorPos;
    int m_selectionPos;
    bool m_cursorVisible;
};

#endif // TEXTVIEWER_H
