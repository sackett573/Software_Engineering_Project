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

public:
    TextViewer(QQuickItem* parent = NULL) :
        QQuickPaintedItem(parent),
        m_currentDoc(NULL)
        {}

    Document* currentDocument() const {return m_currentDoc;}

    void setDocument(Document* doc) {m_currentDoc = doc;}

    void paint(QPainter *painter);

signals:
    void documentChanged();

private:
    Document* m_currentDoc;
};

#endif // TEXTVIEWER_H
