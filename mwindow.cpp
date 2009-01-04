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
#include <QProgressBar>
#include <QDockWidget>
#include <QLabel>

#include <QDebug>

MWindow::MWindow(QWidget *parent) : QMainWindow(parent)
{
    ////// The MainWindow //////
    ui.setupUi(this);
    progressBar = new QProgressBar(this);
    progressBar->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Minimum);
    statusBar()->addPermanentWidget(progressBar);

    connect (ui.webView, SIGNAL(loadProgress(int)), progressBar, SLOT(setValue(int)));
    connect (ui.webView, SIGNAL(loadFinished(bool)), this, SLOT(completeOperations(bool)));
    connect (ui.webView, SIGNAL(previewReady(const QPixmap &, const QString &)), 
             this, SLOT(showPreview(const QPixmap &, const QString &)));

    connect (ui.urlBox->lineEdit(), SIGNAL(returnPressed()), this, SLOT(goToUrl()));
    connect (ui.goButton, SIGNAL(clicked()), this, SLOT(goToUrl()));

    ////// The PreviewWidget //////
    QDockWidget *dockWidget = new QDockWidget(tr("Page Preview"), this);
    dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    dockWidget->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    QWidget *widget = new QWidget(this);
    pwidget.setupUi(widget);
    dockWidget->setWidget(widget);

    QPalette p = pwidget.scrollArea->palette();
    p.setColor(QPalette::Window, p.color(QPalette::Dark));
    pwidget.scrollArea->setPalette(p);

    QLabel *previewLabel = new QLabel(this);
    previewLabel->setAlignment(Qt::AlignCenter);
    pwidget.scrollArea->setWidget(previewLabel);
    pwidget.scrollArea->setAlignment(Qt::AlignCenter);

    addDockWidget(Qt::RightDockWidgetArea, dockWidget);
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

void MWindow::showPreview(const QPixmap &preview, const QString &html)
{
    static_cast<QLabel*>(pwidget.scrollArea->widget())->setPixmap(preview);
    pwidget.textBrowser->setText(html);
}


#include "mwindow.moc"
