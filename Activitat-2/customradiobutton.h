#ifndef CUSTOMRADIOBUTTON_H
#define CUSTOMRADIOBUTTON_H

#include <QWidget>
#include <QRadioButton>

class customRadioButton : public QRadioButton {
	Q_OBJECT
	public:
		explicit customRadioButton(QWidget *parent = nullptr);
	public slots:
		void gestorclic(); //Slot que rep quan es clica un botó
		void canviEstat(bool primeraPersona); //Slot per rebre el signal "teclaC(bool)" per part de myGLWidget
	signals:
		void enviacamera(int value); //Signal per enviar a myGLWidget quina càmera ha d'utilitzar
};
#endif // CUSTOMRADIOBUTTON_H
