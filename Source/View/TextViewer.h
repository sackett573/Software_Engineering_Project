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

    Document* currentDocument() const {return m_currentDoc;}

    int cursorPos() const {return m_cursorPos;}

    void setDocument(Document* doc) {m_currentDoc = doc;}

    void setCursorPos(int pos) {m_cursorPos = pos;}

    void paint(QPainter *painter);

    Q_INVOKABLE int getNewSelection(int x, int y);

signals:
    void documentChanged();

    void cursorPosChanged();

private:
    QFont m_currentFont;
    Document* m_currentDoc;
    std::map<int, LineData> m_lineData;
    int m_boundX;
    int m_boundY;
    int m_numLines;
    int m_cursorPos;
};

#endif // TEXTVIEWER_H
