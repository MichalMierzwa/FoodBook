#include "categorycombobox.h"

categorycombobox::categorycombobox(QWidget *parent) :
    QComboBox(parent)
{

}

categorycombobox::~categorycombobox()
{

}

void categorycombobox::showPopup()
{
    if(QComboBox::itemText(0) == "Wybierz kategorię")
    {
        QComboBox::removeItem(0);
    }
    QComboBox::showPopup();
}

void categorycombobox::hidePopup()
{
    if(QComboBox::itemText(0) != "Wybierz kategorię")
    {
        QComboBox::insertItem(0,"Wybierz kategorię");
        QComboBox::setCurrentIndex(0);
    }

    QComboBox::hidePopup();
}
