#ifndef DOCUMENT_DATA_H
#define DOCUMENT_DATA_H

#include "document.h"
#include <QAbstractListModel>
#include <QQmlContext>
#include <map>

class DocumentData:
    public QAbstractListModel
{
public:
    DocumentData();

    int rowCount(const QModelIndex& ) const override;

    QVariant data(const QModelIndex&, int role = Qt::DisplayRole) const;

private:
    std::map<std::string, Document> m_documents;
};

#endif // DOCUMENT_DATA_H
