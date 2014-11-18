
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

        QPen test(QColor("#00FF00"));
        QPen* currentPen = &penText;
        QBrush b(QColor("#FF0000"));
        painter->setBackground(b);
        painter->setBackgroundMode(Qt::OpaqueMode);
        currentPen = &test;


        while(m_currentDoc->m_buffer[i] != '\0')
        {
            int pos = m_currentDoc->m_buffer.find('\n', i);
            std::string line = m_currentDoc->m_buffer.substr(i, pos - i);
            QString temp = QString::fromStdString(line);

            /*
            if(m_cursorPos >= i && m_cursorPos <= (i + temp.size()))
                subIndex = m_cursorPos - i;

            if(m_selectionPos >= i && m_selectionPos <= (i + temp.size()))
                subIndex2 = m_selectionPos - i;


            if(m_cursorPos != m_selectionPos && (subIndex != -1 || subIndex2 != -1))
            {
                if(subIndex != -1 && subIndex2 != -1)
                {
                    int first, second;
                    std::string sub1, sub2, sub3;
                    if(subIndex > subIndex2)
                    {
                        first = subIndex2;
                        second = subIndex;
                        sub1 = line.substr(0, subIndex2);
                        sub2 = line.substr(subIndex2, subIndex);
                        sub3 = line.substr(subIndex, temp.size());
                    }
                    else
                    {
                        first = subIndex;
                        second = subIndex2;
                        sub1 = line.substr(0, subIndex);
                        sub2 = line.substr(subIndex, subIndex2);
                        sub3 = line.substr(subIndex2, temp.size());
                    }

                    painter->setPen(penText);
                    painter->drawText(0, (m_numLines) * charHeight,
                                      first * charWidth, (m_numLines+1) * charHeight,
                                      Qt::TextSingleLine, QString::fromStdString(sub1));
                    painter->setPen(selectionText);
                    painter->drawText(first * charWidth, m_numLines * charHeight,
                                      (second * charWidth) - (first * charWidth), (m_numLines+1) * charHeight,
                                      Qt::TextSingleLine, QString::fromStdString(sub2));
                    painter->setPen(selectionText);
                    painter->setBrush(QBrush(c));
                    painter->drawRect(first* charWidth, m_numLines * charHeight,
                                      (second * charWidth) - (first * charWidth), (m_numLines+1) * charHeight);

                    painter->setBrush(QBrush(QColor("#FFFFFF")));
                    painter->setPen(penText);
                    painter->drawText(second * charWidth, m_numLines * charHeight,
                                      (temp.size() * charWidth) - (second * charWidth), (m_numLines+1) *charHeight,
                                      Qt::TextSingleLine, QString::fromStdString(sub3));
                }
                else if(subIndex != -1)
                {
                    std::string sub1, sub2;
                    sub1 = line.substr(0, subIndex);
                    sub2 = line.substr(subIndex, temp.size());

                    if(currentPen == &selectionText)
                    {
                        painter->setBrush(QBrush(c));
                        painter->drawRect(0, m_numLines * charHeight,
                                         (subIndex * charWidth), (m_numLines+1) * charHeight);
                        painter->setBrush(QBrush(QColor("#FFFFFF")));
                    }
                    painter->setPen(*currentPen);
                    painter->drawText(0, (m_numLines) * charHeight,
                                      subIndex * charWidth, (m_numLines+1) * charHeight,
                                      Qt::TextSingleLine, QString::fromStdString(sub1));

                    if(currentPen == &penText)
                        currentPen = &selectionText;
                    else
                        currentPen = &penText;

                    if(currentPen == &selectionText)
                    {
                        painter->setBrush(QBrush(c));
                        painter->drawRect(subIndex* charWidth, m_numLines * charHeight,
                                         (temp.size() * charWidth) - (subIndex * charWidth), (m_numLines+1) * charHeight);
                        painter->setBrush(QBrush(QColor("#FFFFFF")));
                    }
                    painter->setPen(*currentPen);
                    painter->drawText(subIndex * charWidth, m_numLines * charHeight,
                                      (temp.size() * charWidth) - (subIndex * charWidth), (m_numLines+1) * charHeight,
                                      Qt::TextSingleLine, QString::fromStdString(sub2));
                }
                else if(subIndex2 != -1)
                {
                    std::string sub1, sub2;
                    sub1 = line.substr(0, subIndex2);
                    sub2 = line.substr(subIndex2, temp.size());

                    if(currentPen == &selectionText)
                    {
                        painter->setBrush(QBrush(c));
                        painter->drawRect(0, m_numLines * charHeight,
                                         (subIndex2 * charWidth), (m_numLines+1) * charHeight);
                        painter->setBrush(QBrush(QColor("#FFFFFF")));
                    }
                    painter->setPen(*currentPen);
                    painter->drawText(0, (m_numLines) * charHeight,
                                      subIndex2 * charWidth, (m_numLines+1) * charHeight,
                                      Qt::TextSingleLine, QString::fromStdString(sub1));

                    if(currentPen == &penText)
                        currentPen = &selectionText;
                    else
                        currentPen = &penText;

                    if(currentPen == &selectionText)
                    {
                        painter->setBrush(QBrush(c));
                        painter->drawRect(subIndex2* charWidth, m_numLines * charHeight,
                                         (temp.size() * charWidth) - (subIndex2 * charWidth), (m_numLines+1) * charHeight);
                        painter->setBrush(QBrush(QColor("#FFFFFF")));
                    }
                    painter->setPen(*currentPen);
                    painter->drawText(subIndex2 * charWidth, m_numLines * charHeight,
                                      (temp.size() * charWidth) - (subIndex2 * charWidth), (m_numLines+1) * charHeight,
                                      Qt::TextSingleLine, QString::fromStdString(sub2));
                }
            }
            else
            */
            painter->setPen(*currentPen);
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
