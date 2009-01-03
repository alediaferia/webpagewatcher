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

#include "mwindow.h"

#include <QLineEdit>
#include <QIcon>

#include <QDebug>

MWindow::MWindow(QWidget *parent) : QMainWindow(parent)
{
    ui.setupUi(this);
    statusBar()->addPermanentWidget(ui.progressBar);
    connect (ui.webView, SIGNAL(loadProgress(int)), ui.progressBar, SLOT(setValue(int)));
    connect (ui.webView, SIGNAL(loadFinished(bool)), this, SLOT(completeOperations(bool)));
    connect (ui.urlBox->lineEdit(), SIGNAL(returnPressed()), this, SLOT(goToUrl()));
    connect (ui.goButton, SIGNAL(clicked()), this, SLOT(goToUrl()));
}

MWindow::~MWindow()
{}

void MWindow::loadPage(QString page)
{
    if (!page.contains("://")) {
        page.prepend("http://");
    }
    loadUrl(QUrl(page));
}

void MWindow::loadUrl(const QUrl &url)
{
    ui.webView->load(url);
}

void MWindow::goToUrl()
{
    loadPage(ui.urlBox->currentText());
}

void MWindow::completeOperations(bool ok)
{
    if (!ok) {
        ui.urlBox->setItemIcon(ui.urlBox->currentIndex(), QIcon());        
        return;
    }
    ui.urlBox->setEditText(ui.webView->url().toString());
    ui.urlBox->setItemIcon(ui.urlBox->currentIndex(), ui.webView->icon());
}

#include "mwindow.moc"
