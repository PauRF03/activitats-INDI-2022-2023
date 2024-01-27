#ifndef CUSTOMRADIOBUTTON_H
#define CUSTOMRADIOBUTTON_H

#include <QWidget>
#include <QRadioButton>

class customRadioButton : public QRadioButton
{
    Q_OBJECT
public:
    explicit customRadioButton(QWidget *parent = nullptr);

public slots:
    void gestorClic();
    void canviEstat(bool esquerra);
signals:
    void canviaEspelma(int value);
};

#endif // CUSTOMRADIOBUTTON_H
