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

    Q_PROPERTY(int begindex READ begindex WRITE setBegindex NOTIFY begindexChanged)

    Q_PROPERTY(int endex READ endex WRITE setEndex NOTIFY endexChanged)

    Q_PROPERTY(int currentRow READ currentRow NOTIFY rowChanged)

    Q_PROPERTY(int currentColumn READ currentColumn NOTIFY columnChanged)

    struct LineData
    {
        int lineStartIndex;
        int lineEndIndex;
    };

public:
    TextViewer(QQuickItem* parent = NULL) :
        QQuickPaintedItem(parent),
        m_currentDoc(NULL),
        m_cursorPos(-1),
        m_begindex(-1),
        m_endex(-1)
        {}

    // Getters
    Document* currentDocument() const {return m_currentDoc;}

    int cursorPos() const {return m_cursorPos;}

    bool cursorVisible() const {return m_cursorVisible;}

    int begindex() const {return m_begindex;}

    int endex() const {return m_endex;}

    int currentRow() const {return m_currentRow;}

    int currentColumn() const {return m_currentColumn;}

    // Setters
    void setDocument(Document* doc) {m_currentDoc = doc;}

    void setCursorPos(int pos) {m_cursorPos = pos;}

    void setCursorVisible(bool b) {m_cursorVisible = b;}

    void setBegindex(int pos) {m_begindex = pos;}

    void setEndex(int pos) {m_endex = pos;}

    // Invokables
    Q_INVOKABLE int getNewSelection(int x, int y);

    Q_INVOKABLE int newSelectionFromRowCol(int col, int row);

    // Event Handlers
    void paint(QPainter *painter);

signals:
    void documentChanged();

    void cursorPosChanged();

    void cursorVisibilityChanged();

    void begindexChanged();

    void endexChanged();

    void rowChanged();

    void columnChanged();

private:
    QFont m_currentFont;
    Document* m_currentDoc;
    std::map<int, LineData> m_lineData;
    int m_numLines;
    int m_cursorPos;
    int m_currentRow;
    int m_currentColumn;
    int m_begindex;
    int m_endex;
    bool m_cursorVisible;
};

#endif // TEXTVIEWER_H
