/***************************************************************************
 *   Copyright (C) 2009 by Alessandro Diaferia <alediaferia@gmail.com>     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA .        *
 **************************************************************************/

#include "selectionwidget.h"

#include <QPainter>

SelectionWidget::SelectionWidget(QWidget *parent) : QWidget(parent)
{
}

SelectionWidget::~SelectionWidget()
{}

void SelectionWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    QColor pcolor(palette().color(QPalette::Highlight));
    painter.setPen(pcolor);

    QColor icolor(pcolor);
    icolor.setAlpha(127);
    painter.setBrush(icolor);

    QRect fillRect(rect());
    fillRect.setWidth(fillRect.width() - 1);
    fillRect.setHeight(fillRect.height() - 1);
    painter.drawRect(fillRect);

    painter.end();
}

QPixmap SelectionWidget::getSelection()
{
    QPixmap pixmap(size());
    pixmap.fill(Qt::transparent);
    QRect selection(pos(), size());
    hide();
    parentWidget()->render(&pixmap, QPoint(), QRegion(selection));

    return pixmap;
}

#include "selectionwidget.moc"
