#ifndef INGREDIENTCOMBOBOX_H
#define INGREDIENTCOMBOBOX_H

#include <QWidget>
#include <QComboBox>

class IngredientCombobox : public QComboBox
{
    Q_OBJECT

public:
    explicit IngredientCombobox(QWidget *parent = 0);

    void showPopup();
    void hidePopup();

    ~IngredientCombobox();
};

#endif // INGREDIENTCOMBOBOX_H
