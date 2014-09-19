#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

#include "mainwindow.h"

class Application : public QApplication
{
    Q_OBJECT

public:
    explicit Application(int &argc, char **argv);
    ~Application();

    void start();

    MainWindow * mainWindow();

private slots:
    void launchApplication();

private:
    void installTranslation();

    MainWindow * m_mainWindow;
};

#endif // APPLICATION_H
