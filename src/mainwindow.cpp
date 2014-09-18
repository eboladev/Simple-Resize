#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtDebug>

#include <QDesktopServices>
#include <QFileDialog>
#include <QMessageBox>
#include <QShortcut>
#include <QUrl>

#include "settings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar->setVisible(false);
    ui->widthSpinBox->setValue(Settings::instance()->width());
    ui->heightSpinBox->setValue(Settings::instance()->height());

    new QShortcut(QKeySequence(Qt::Key_Delete), this, SLOT(deleteItem()));
}

MainWindow::~MainWindow()
{
    Settings::instance()->setWidth(ui->widthSpinBox->value());
    Settings::instance()->setHeight(ui->heightSpinBox->value());

    delete ui;
}

void MainWindow::deleteItem()
{
    if(ui->listWidget->currentItem())
    {
        QList<QListWidgetItem*> itemList = ui->listWidget->selectedItems();
        foreach(QListWidgetItem *item , itemList)
        {
            m_fileList.removeOne(item->data(1001).toString());
            delete item;
        }
    }
}

void MainWindow::on_openFilesButton_clicked()
{
    QFileDialog fileDialog(this, tr("Open files"), Settings::instance()->lastDirectory(), tr("Image Files (*.png *.jpg *.jpeg *.bmp *.gif)"));
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    if(fileDialog.exec())
    {
        m_fileList = fileDialog.selectedFiles();

        ui->listWidget->clear();
        for(int i = 0; i < m_fileList.length(); i++)
        {
            QListWidgetItem * item = new QListWidgetItem(QIcon(m_fileList[i]), QFileInfo(m_fileList[i]).fileName(),ui->listWidget );
            item->setData(1001, m_fileList[i]);
            ui->listWidget->addItem(item);
        }

        qDebug() << "Images to process:" << m_fileList;
        Settings::instance()->setLastDirectory(QFileInfo(m_fileList[0]).dir().absolutePath());
    }
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox messageBox(this);
    messageBox.setWindowTitle(tr("About Simple Resize"));
    messageBox.setText(tr("It is simple image resize application"));
    messageBox.setIconPixmap(QPixmap(":/icons/icons/cat.png"));
    messageBox.exec();
}

void MainWindow::abortResize(QString titleText, QString text)
{
    qWarning() << text;

    ui->progressBar->reset();
    ui->progressBar->setVisible(false);

    QMessageBox::warning(0, titleText, text);
}

void MainWindow::on_resizeButton_clicked()
{
    if(m_fileList.isEmpty())
    {
        qDebug() << "No files choosed";
        return;
    }

    ui->statusBar->showMessage(tr("Initialization..."));
    ui->progressBar->setVisible(true);

    // create 'backup' dir
    QString backupDirPath = QFileInfo(m_fileList[0]).dir().absolutePath() + "/backup/";

    if(!QFile::exists(backupDirPath)
            && QDir().mkdir(backupDirPath))
    {
        abortResize(tr("Can't create backup directory"),  tr("Can't create backup directory") + " " + backupDirPath);
        return;
    }

    // copy old files to backup dir
    for(int i = 0; i < m_fileList.length(); i++)
    {
        QString fileName = QFileInfo(m_fileList[i]).fileName();
        QString destinationFilename = backupDirPath + fileName;
        if(!QFile::copy(m_fileList[i], destinationFilename) && !QFile::exists(destinationFilename))
        {
            abortResize(tr("Can't backup image"), tr("Can't backup image") + " " + fileName);
            return;
        }
    }

    qDebug() << "Start scale" << "Width:" << ui->widthSpinBox->value() << "Height:" << ui->heightSpinBox->value();

    // scale and replace
    for(int i = 0; i < m_fileList.length(); i++)
    {
        ui->progressBar->setMaximum(m_fileList.length());
        ui->progressBar->setValue(i + 1);

        QString fileName = QFileInfo(m_fileList[i]).fileName();

        ui->statusBar->showMessage(tr("Processing ") + QString::number(i+1) + "/" + QString::number(m_fileList.length()));
        QImage image(m_fileList[i]);
        qDebug() << "Scale image " << fileName;
        QImage resultImage = image.scaled(ui->widthSpinBox->value(), ui->heightSpinBox->value(), Qt::KeepAspectRatio);
        if(!resultImage.save(m_fileList[i]))
        {
            qWarning() << "Can't save image" << fileName;
            QMessageBox::warning(0, tr("Can't save image"), tr("Can't save image") + " " + fileName);
        }
    }

    ui->statusBar->showMessage(tr("Done!"));
    qDebug() << "Finish scaling";
    ui->progressBar->setVisible(false);
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(item->data(1001).toString()));
}
