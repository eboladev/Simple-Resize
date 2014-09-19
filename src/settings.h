#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT

public:
    static Settings *instance();
    ~Settings();

    QString lastDirectory();
    void setLastDirectory(QString lastDirectory);

    int width();
    void setWidth(int width);

    int height();
    void setHeight(int height);

    QByteArray windowGeometry();
    void setWindowGeometry(QByteArray windowGeometry);

private:
    explicit Settings(QObject *parent = 0);
    QSettings m_settings;
};

#endif // SETTINGS_H
