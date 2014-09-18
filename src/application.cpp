#include "application.h"

#include <QtDebug>

#include <QTimer>
#include <QTranslator>

#include "settings.h"

Application::Application(int &argc, char **argv) :
    QApplication(argc, argv)
{
    setApplicationName("Simple Resize");
    setOrganizationName("Sergey Gavrushkin");

    setWindowIcon(QIcon(":/icons/icons/cat.png"));
}

Application::~Application()
{
    delete m_mainWindow;
}

void Application::start()
{
    QTimer::singleShot(0, this, SLOT(launchApplication()));
}

void Application::launchApplication()
{
    installTranslation();

    m_mainWindow = new MainWindow();
    m_mainWindow->show();
}

void Application::installTranslation()
{
    QTranslator *translator = new QTranslator(this);
#ifdef Q_OS_WIN
    translator->load(qApp->applicationDirPath() + "/simple-resize_ru.qm");
#else
    translator->load("/usr/share/ssimple-resize/translations/simple-resize_ru.qm");
#endif
    installTranslator(translator);
}
