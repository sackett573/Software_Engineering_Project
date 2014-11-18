
#include "TextViewer.h"

void TextViewer::paint(QPainter *painter)
{
    if(m_currentDoc != NULL)
    {
        QFont font;
        font.setBold(false);
        font.setFamily("consolas");
        font.setKerning(false);
        font.setPointSize(12);

        QPen penText(QColor("#000000"));

        painter->setFont(font);
        painter->setPen(penText);

        QFontMetrics m(font);

        int charWidth = m.width('A');
        int charHeight = m.height();

        int maxLineWidth = 0;
        int numLines = 0;
        int i = 0;

        while(m_currentDoc->m_buffer[i] != '\0')
        {
            int pos = m_currentDoc->m_buffer.find('\n', i);
            QString temp = QString::fromStdString(m_currentDoc->m_buffer.substr(i, pos - i));

            painter->drawText(0, (numLines)*charHeight, (temp.size() * charWidth), (numLines+1)*charHeight,Qt::TextSingleLine, temp);

            maxLineWidth = (maxLineWidth > (temp.size() * charWidth))?maxLineWidth:(temp.size() * charWidth);
            numLines++;

            i = pos + 1;
            if(pos == -1)
                break;
        }

        this->setWidth(maxLineWidth);
        this->setHeight((numLines * charHeight));
    }


}
