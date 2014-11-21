
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
        QPen selectionText(QColor("#FFFFFF"));
        QBrush normalBrush(QColor("#FFFFFF"));
        QBrush selectionBrush(QColor("#00CCFF"));

        painter->setFont(m_currentFont);

        QFontMetrics m(m_currentFont);
        int charWidth = m.width('A');
        int charHeight = m.height();

        int maxLineWidth = 0;
        m_numLines = 0;
        int i = 0;

        QPen* currentPen = &penText;
        QBrush* currentBackground = &normalBrush;
        painter->setBackgroundMode(Qt::OpaqueMode);

        while(m_currentDoc->m_buffer[i] != '\0')
        {
            int pos = m_currentDoc->m_buffer.indexOf('\n', i);
            QString line = m_currentDoc->m_buffer.mid(i, pos - i);

            if(m_begindex != -1 && m_endex != -1 && m_begindex != m_endex)
            {
                if(m_begindex >= i && m_begindex <= (i+ static_cast<int>(line.size())))
                {
                    if(m_endex >= i && m_endex <= (i+ static_cast<int>(line.size())))
                    {
                        int lastX = 0;

                        QString sub = line.mid(0, m_begindex - i);

                        painter->setPen(*currentPen);
                        painter->setBackground(*currentBackground);
                        painter->drawText(0, (m_numLines)*charHeight,
                                         (sub.size() * charWidth), (m_numLines+1)*charHeight,
                                          Qt::TextSingleLine, sub);
                        lastX = sub.size() * charWidth;

                        sub = line.mid(m_begindex - i, (m_endex - i) - (m_begindex - i));

                        currentPen = &selectionText;
                        currentBackground = &selectionBrush;
                        painter->setPen(*currentPen);
                        painter->setBackground(*currentBackground);
                        painter->drawText(lastX, (m_numLines)*charHeight,
                                         (sub.size() * charWidth), (m_numLines+1)*charHeight,
                                          Qt::TextSingleLine, sub);
                        lastX = lastX + (sub.size() * charWidth);

                        sub = line.mid(m_endex - i, (line.size()) - (m_endex -i));

                        currentPen = &penText;
                        currentBackground = &normalBrush;
                        painter->setPen(*currentPen);
                        painter->setBackground(*currentBackground);
                        painter->drawText(lastX, (m_numLines)*charHeight,
                                         (sub.size() * charWidth), (m_numLines+1)*charHeight,
                                          Qt::TextSingleLine, sub);
                    }
                    else
                    {
                        int lastX = 0;

                        QString sub = line.mid(0, m_begindex - i);
                        painter->setPen(*currentPen);
                        painter->setBackground(*currentBackground);
                        painter->drawText(0, (m_numLines)*charHeight,
                                         (sub.size() * charWidth), (m_numLines+1)*charHeight,
                                          Qt::TextSingleLine, sub);
                        lastX = sub.size() * charWidth;

                        sub = line.mid(m_begindex - i, (line.size()) - (m_begindex - i));

                        currentPen = &selectionText;
                        currentBackground =&selectionBrush;
                        painter->setPen(*currentPen);
                        painter->setBackground(*currentBackground);
                        painter->drawText(lastX, (m_numLines)*charHeight,
                                         (sub.size() * charWidth), (m_numLines+1)*charHeight,
                                          Qt::TextSingleLine, sub);
                    }
                }
                else if(m_endex >= i && m_endex <= (i+ static_cast<int>(line.size())))
                {
                    int lastX = 0;

                    QString sub = line.mid(0, m_endex - i);
                    painter->setPen(*currentPen);
                    painter->setBackground(*currentBackground);
                    painter->drawText(0, (m_numLines)*charHeight,
                                     (sub.size() * charWidth), (m_numLines+1)*charHeight,
                                      Qt::TextSingleLine, sub);
                    lastX = sub.size() * charWidth;

                    sub = line.mid(m_endex - i, (line.size()) - (m_endex - i));

                    currentPen = &penText;
                    currentBackground =&normalBrush;
                    painter->setPen(*currentPen);
                    painter->setBackground(*currentBackground);
                    painter->drawText(lastX, (m_numLines)*charHeight,
                                     (sub.size() * charWidth), (m_numLines+1)*charHeight,
                                      Qt::TextSingleLine, sub);
                }
                else
                {
                    painter->setPen(*currentPen);
                    painter->setBackground(*currentBackground);
                    painter->drawText(0, (m_numLines)*charHeight, (line.size() * charWidth), (m_numLines+1)*charHeight,Qt::TextSingleLine, line);
                }
            }
            else
            {
                painter->setPen(*currentPen);
                painter->setBackground(*currentBackground);
                painter->drawText(0, (m_numLines)*charHeight, (line.size() * charWidth), (m_numLines+1)*charHeight,Qt::TextSingleLine, line);
            }

            maxLineWidth = (maxLineWidth > (line.size() * charWidth))?maxLineWidth:(line.size() * charWidth);

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
            auto val = std::find_if(m_lineData.begin(), m_lineData.end(),
                [this](std::map<int, LineData>::value_type & p)
                {
                    if(m_cursorPos >= p.second.lineStartIndex && m_cursorPos <= p.second.lineEndIndex)
                        return true;
                    return false;
                });

            if(val != m_lineData.end())
            {
                auto& p = *val;
                int charsFromLeft = m_cursorPos - p.second.lineStartIndex;
                int x = (charsFromLeft * charWidth);
                int y1 = (p.first) * charHeight;
                int y2 = (p.first + 1) * charHeight;
                painter->drawLine(x, y1, x, y2);
            }

        }

        this->setWidth(maxLineWidth + 1);
        this->setHeight(((m_numLines+1) * charHeight));
    }
    else
    {
        this->setWidth(1);
        this->setHeight(1);
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

        m_currentRow = line;

        int numCharsFromLeft = x/m.width('A');
        numCharsFromLeft += (((x%m.width('A'))/static_cast<float>(m.width('A')))>0.5)?1:0;
        int lineLength = m_lineData[line].lineEndIndex - m_lineData[line].lineStartIndex;

        if(numCharsFromLeft > lineLength)
            index = m_lineData[line].lineEndIndex; 
        else
            index = m_lineData[line].lineStartIndex + numCharsFromLeft;

        m_currentColumn = index - m_lineData[line].lineStartIndex;
    }

    return index;
}

int TextViewer::newSelectionFromRowCol(int col, int row)
{
    int index;
    if(m_currentDoc != NULL)
    {
        QFontMetrics m(m_currentFont);

        if(row > m_numLines)
            row = m_numLines;

        int lineLength = m_lineData[row].lineEndIndex - m_lineData[row].lineStartIndex;
        if(col > lineLength)
            index = m_lineData[row].lineEndIndex;
        else
            index = m_lineData[row].lineStartIndex + col;

        m_currentColumn = index - m_lineData[row].lineStartIndex;
        m_currentRow = row;
    }

    return index;
}

void TextViewer::updateRowCol()
{
    if(m_currentDoc != NULL)
    {
        for(auto& d : m_lineData)
        {
            if(d.second.lineStartIndex < m_cursorPos && m_cursorPos < d.second.lineEndIndex)
            {
                m_currentRow = d.first;
                break;
            }
        }

        m_currentColumn = m_cursorPos - m_lineData[m_currentRow].lineStartIndex;
    }
}
