#include "document_data.h"

DocumentData::DocumentData()
{
    m_documents["wakka"].m_filename = "super duper";
    m_documents["wakka"].m_data = NULL;
}

int DocumentData::rowCount(const QModelIndex &) const
{
    m_documents.size();
}

QVariant DocumentData::data(const QModelIndex &i, int) const
{
    int index = i.row();
    int j = 0;

    const Document * target = NULL;
    for(auto & pair: m_documents)
    {
        const Document& doc = pair.second;

        if(j == index)
            target = &doc;

        j++;
    }

    QVariant var(*target);
    return var;
}
