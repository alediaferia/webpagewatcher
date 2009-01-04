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

#ifndef MWINDOW_H
#define MWINDOW_H

#include "ui_mwindowui.h"
#include "ui_previewwidget.h"

#include <QMainWindow>

class QProgressBar;

class MWindow : public QMainWindow
{
    Q_OBJECT
public:
    MWindow(QWidget *parent = 0);
    ~MWindow();

public slots:
    void loadPage(QString);

protected slots:
    void loadUrl(const QUrl &);
    void goToUrl();
    void completeOperations(bool);
    void showPreview(const QPixmap &, const QString &);

private:
    Ui::MainWindow ui;
    Ui::PreviewWidget pwidget;
    QProgressBar *progressBar;
};

#endif
