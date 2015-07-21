/*
    Copyright 2015 Barotte Simon <simon.barotte@gmail.com>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "genpassword.h"

#include <QDebug>
#include <QSettings>
#include <QString>


const QString alpha_min("abcdefghijklmnopqrstuvwxyz");
const QString alpha_up("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
const QString num("0123456789");
const QString symbolset("¬`!\"£$%^&*()_+-={}[];'#:@~<>?,./|\\ ");
const QString hexset("0123456789ABCDEF");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumSize(498,523);
    this->setMaximumSize(498,523);

    readSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent ( QCloseEvent * event )
{
    Q_UNUSED (event);
    saveSettings();
}

void MainWindow::readSettings()
{
    QSettings settings("gen_password.ini", QSettings::IniFormat);
    this->restoreGeometry(settings.value("Window/geometry").toByteArray());
    ui->amount->setValue(settings.value("Options/amount", 1).toInt());
    ui->lengthPwd->setValue(settings.value("Options/pwdLength", 6).toInt());
    ui->typePwd->setCurrentIndex(settings.value("Options/pwdType", 0).toInt());
}

void MainWindow::saveSettings()
{
    QSettings settings("gen_password.ini", QSettings::IniFormat);
    settings.beginGroup("Window");
    settings.setValue("geometry", saveGeometry());
    settings.endGroup();

    settings.beginGroup("Options");
    settings.setValue("amount", ui->amount->value());
    settings.setValue("pwdLength", ui->lengthPwd->value());
    settings.setValue("pwdType", ui->typePwd->currentIndex());
    settings.endGroup();
}

void MainWindow::on_genPwd_clicked()
{
    QFlags<genPassword::Option> flags;
    QString characterset;
    QStringList pwd_list;

    switch (ui->typePwd->currentIndex()) {
    case 0:
        if (ui->uniqueCaractere->isChecked())
            flags |= genPassword::Unique;

        characterset = this->getCharacterSet();
        pwd_list = genPassword::genRandom(ui->lengthPwd->value(), characterset, ui->amount->value(), flags);
        break;
    case 1:
        characterset = hexset;
        pwd_list = genPassword::genRandom(ui->lengthPwd->value(), characterset, ui->amount->value(), flags);
        qDebug() << "hexa";
        break;
    }
    ui->listPwd->clear();
    for(int i=0; i<pwd_list.length(); i++)
    {
        ui->listPwd->appendPlainText(pwd_list[i]);
    }
    ui->copyPwd->setEnabled(true);
}

void MainWindow::on_checkBoxCustomSet_clicked(bool checked)
{
    ui->customSet->setEnabled(checked);
    if(checked){
        ui->customSet->setFocus();
    }else{
        ui->customSet->clear();
    }
}

void MainWindow::on_typePwd_currentIndexChanged(int index)
{
    ui->stackedWidget->setCurrentIndex(index);
}

QString MainWindow::getCharacterSet()
{
    QString characterset;

    if (ui->minuscule->isChecked())
        characterset += alpha_min;

    if (ui->majuscule->isChecked())
        characterset += alpha_up;

    if (ui->symbols->isChecked())
        characterset += symbolset;

    if (ui->numerique->isChecked())
        characterset += num;

    if (ui->checkBoxCustomSet->isChecked())
        characterset += ui->customSet->text();

    return characterset;
}

void MainWindow::on_copyPwd_clicked()
{

}
