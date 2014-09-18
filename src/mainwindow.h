#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidgetItem>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void deleteItem();

    void on_openFilesButton_clicked();
    void on_resizeButton_clicked();

    void on_actionQuit_triggered();
    void on_actionAbout_triggered();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

private:
    void abortResize(QString titleText, QString text);

    Ui::MainWindow *ui;

    QStringList m_fileList;
};

#endif // MAINWINDOW_H
