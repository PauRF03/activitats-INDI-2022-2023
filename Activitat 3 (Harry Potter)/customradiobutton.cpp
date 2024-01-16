#include "customradiobutton.h"

customRadioButton::customRadioButton(QWidget *parent)
    : QRadioButton{parent}
{

}

void customRadioButton::gestorClic(){
    if(this -> objectName() == "Esquerra"){
        emit canviaEspelma(1);
    }else{
        emit canviaEspelma(0);
    }
}

void customRadioButton::canviEstat(bool esquerra){
    if(this -> objectName() == "Esquerra"){
        setChecked(esquerra);
    }else{
        setChecked(not esquerra);
    }
}
