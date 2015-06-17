#ifndef CATEGORYCOMBOBOX_H
#define CATEGORYCOMBOBOX_H

#include <QWidget>
#include <QComboBox>

class categorycombobox : public QComboBox
{
    Q_OBJECT

public:
    explicit categorycombobox(QWidget *parent = 0);

    void showPopup();
    void hidePopup();

    ~categorycombobox();
};

#endif // CATEGORYCOMBOBOX_H
