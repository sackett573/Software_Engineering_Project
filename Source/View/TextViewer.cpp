
#include "TextViewer.h"

void TextViewer::paint(QPainter *painter)
{
    if(m_currentDoc != NULL)
    {
        m_currentFont.setBold(false);
        m_currentFont.setFamily("consolas");
        m_currentFont.setKerning(false);
        m_currentFont.setPointSize(12);

        QPen penText(QColor("#000000"));

        painter->setFont(m_currentFont);
        painter->setPen(penText);

        QFontMetrics m(m_currentFont);
        int charWidth = m.width('A');
        int charHeight = m.height();

        int maxLineWidth = 0;
        m_numLines = 0;
        int i = 0;

        while(m_currentDoc->m_buffer[i] != '\0')
        {
            int pos = m_currentDoc->m_buffer.find('\n', i);
            QString temp = QString::fromStdString(m_currentDoc->m_buffer.substr(i, pos - i));

            painter->drawText(0, (m_numLines)*charHeight, (temp.size() * charWidth), (m_numLines+1)*charHeight,Qt::TextSingleLine, temp);

            maxLineWidth = (maxLineWidth > (temp.size() * charWidth))?maxLineWidth:(temp.size() * charWidth);

            m_lineData[m_numLines].lineStartIndex = i;
            if(pos == -1)
            {
                m_lineData[m_numLines].lineEndIndex = m_currentDoc->m_buffer.size();
                break;
            }
            else
                m_lineData[m_numLines].lineEndIndex = pos;

            m_numLines++;
            i = pos + 1;
        }

        if(m_cursorPos == -1)
            m_cursorPos = 0;

        if(m_cursorVisible)
        {
            for(auto& d : m_lineData)
            {
                if(m_cursorPos >= d.second.lineStartIndex && m_cursorPos <= d.second.lineEndIndex)
                {
                    int charsFromLeft = m_cursorPos - d.second.lineStartIndex;
                    int x = (charsFromLeft * charWidth);
                    int y1 = (d.first) * charHeight;
                    int y2 = (d.first + 1) * charHeight;
                    painter->drawLine(x, y1, x, y2);
                    break;
                }
            }
        }

        this->setWidth(maxLineWidth + 1);
        this->setHeight(((m_numLines+1) * charHeight));
    }
}

int TextViewer::getNewSelection(int x, int y)
{
    int index = 0;
    if(m_currentDoc != NULL)
    {
        QFontMetrics m(m_currentFont);

        int line = y/m.height();

        if(line > m_numLines)
            line = m_numLines;

        int numCharsFromLeft = x/m.width('A');
        numCharsFromLeft += (((x%m.width('A'))/static_cast<float>(m.width('A')))>0.5)?1:0;
        int lineLength = m_lineData[line].lineEndIndex - m_lineData[line].lineStartIndex;


        if(numCharsFromLeft > lineLength)
            index = m_lineData[line].lineEndIndex;
        else
            index = m_lineData[line].lineStartIndex + numCharsFromLeft;
    }

    return index;
}
