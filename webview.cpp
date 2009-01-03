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
#include "webview.h"
#include "selectionwidget.h"

#include <QMouseEvent>
#include <QDebug>
#include <QLabel>
#include <QPushButton>

WebView::WebView(QWidget *parent) : QWebView(parent), m_advancedSelection(false),
                                                      m_selectionWidget(0)
{
    setUrl(QUrl("about:blank"));
}

WebView::~WebView()
{}

void WebView::mousePressEvent(QMouseEvent *event)
{
    if (event->modifiers() & Qt::ControlModifier) {
        m_advancedSelection = true;
        delete m_selectionWidget;
        m_selectionWidget = new SelectionWidget(this);
        m_selectionWidget->move(event->pos());
        m_selectionWidget->resize(0, 0);
        m_selectionWidget->show();
    } else {
        QWebView::mousePressEvent(event);
    }
}

void WebView::mouseReleaseEvent(QMouseEvent *event)
{
    if (!m_advancedSelection) {
        delete m_selectionWidget;
        m_selectionWidget = 0;
    } else {
        QLabel *label = new QLabel();
        label->setAttribute(Qt::WA_DeleteOnClose);
        label->setPixmap(m_selectionWidget->getSelection());
        label->show();
    }

    m_advancedSelection = false;
    QWebView::mouseReleaseEvent(event);
}

void WebView::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_advancedSelection) {
        QWebView::mouseMoveEvent(event);
    } else {
        QPoint delta = event->pos();
        delta -= m_selectionWidget->pos();
        // TODO: handle negative deltas
        m_selectionWidget->resize(delta.x(), delta.y());
    }
}

#include "webview.moc"
