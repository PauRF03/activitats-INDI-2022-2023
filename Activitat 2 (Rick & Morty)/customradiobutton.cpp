#include "customradiobutton.h"

customRadioButton::customRadioButton(QWidget *parent)
    : QRadioButton{parent}
{

}

void customRadioButton::gestorclic(){
    if(this -> objectName() == "POVMorty"){
        emit enviacamera(1);
    }else{
        emit enviacamera(0);
    }
}

void customRadioButton::canviEstat(bool primeraPersona){
    if(primeraPersona){
        if(this -> objectName() == "POVMorty"){
            setChecked(true);
        }else{
            setChecked(false);
        }
    }else{
        if(this -> objectName() == "POVMorty"){
            setChecked(false);
        }else{
            setChecked(true);
        }
    }
}
