#include "settings.h"

#include <QtDebug>

#include <QApplication>

Settings *Settings::instance()
{
    static Settings instance;
    return &instance;
}

Settings::~Settings()
{
}

Settings::Settings(QObject *parent) :
    QObject(parent)
  , m_settings(QSettings::IniFormat, QSettings::UserScope, qApp->organizationName(), qApp->applicationName())
{
}

QString Settings::lastDirectory()
{
    return m_settings.value("lastDirectory").toString();
}

void Settings::setLastDirectory(QString lastDirectory)
{
    m_settings.setValue("lastDirectory", lastDirectory);
}

int Settings::width()
{
    return m_settings.value("width", 640).toInt();
}

void Settings::setWidth(int width)
{
    m_settings.setValue("width", width);
}

int Settings::height()
{
    return m_settings.value("height", 480).toInt();
}

void Settings::setHeight(int height)
{
    m_settings.setValue("height", height);
}
