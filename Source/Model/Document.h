#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "Style.h"
#include <QObject>
#include <string>
#include <vector>
#include <QList>
#include <QDebug>
#include <QByteArray>

class Document :
    public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString filename READ filename NOTIFY filenameChanged)

public:
    Document(QObject* parent = NULL ) :
        QObject(parent)
    {}

    ~Document()
    {
        qDebug() << "Document destroyed";
    }

    QString filename() const {return m_filename;}

    Q_INVOKABLE int filesize() const {return m_buffer.size();}

    QString m_filename;
    QString m_path;
    QString m_buffer;
    QList<StyleEntry> m_styleEntries;

signals:
    void filenameChanged();

    void filesizeChanged();
};

#endif // DOCUMENT_H
