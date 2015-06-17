#include "ingredientcombobox.h"
#include <QDebug>

IngredientCombobox::IngredientCombobox(QWidget *parent) :
    QComboBox(parent)

{

}

IngredientCombobox::~IngredientCombobox()
{

}

void IngredientCombobox::showPopup()
{
    if(QComboBox::itemText(0) == "Wybierz składnik")
    {
        QComboBox::removeItem(0);
    }
    QComboBox::showPopup();
}

void IngredientCombobox::hidePopup()
{
    if(QComboBox::itemText(0) != "Wybierz składnik")
    {
        QComboBox::insertItem(0,"Wybierz składnik");
        QComboBox::setCurrentIndex(0);
    }

    QComboBox::hidePopup();
}
