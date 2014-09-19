#include "specialspinbox.h"

#include <QKeyEvent>

#include "application.h"

SpecialSpinBox::SpecialSpinBox(QWidget *parent) :
    QSpinBox(parent)
{
}

void SpecialSpinBox::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Return) {
        ((Application*)qApp->instance())->mainWindow()->on_resizeButton_clicked();
    }

    QSpinBox::keyPressEvent(event);
}
