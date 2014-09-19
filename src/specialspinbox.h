#ifndef SPECIALSPINBOX_H
#define SPECIALSPINBOX_H

#include <QSpinBox>

class SpecialSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    explicit SpecialSpinBox(QWidget *parent = 0);

protected:
    virtual void keyPressEvent(QKeyEvent * event);

};

#endif // SPECIALSPINBOX_H
