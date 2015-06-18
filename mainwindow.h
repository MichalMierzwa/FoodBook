#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "recipe.h"
#include <QMetaType>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private slots:

    void AddToList(QString Ingredient);
    void showTime();
    void defaultInfoLineText();

    void on_MainPageButton_clicked();
    void on_MainPageButton_2_clicked();
    void on_MainPageButton_3_clicked();
    void on_MainPageButton_4_clicked();
    void on_MainPageButton_5_clicked();
    void on_MainPageButton_6_clicked();
    void on_MainPageButton_7_clicked();

    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_SaveButton_clicked();

    void on_PickComboBox_activated(const QString &arg1);

    void IngredientUpdateUP();
    void IngredientUpdateDOWN();

    void on_quitAppButton_released();

    void on_CategoryComboBox_activated(const QString &arg1);

    void on_pushButton_RemoveNumber_released();

    void on_pushButton_Settings_clicked();

    void on_pushButton_released();

    void LoadIngredients();

    void on_listWidget_AllIngr_itemClicked(QListWidgetItem *item);

    void setDefaultStyleSheet();

    void EditButtonActivation();

    void on_pushButton_EditRecipe_released();

private:
    QList<recipe> ListaPrzepisow;

    void LoadTable();
    void LoadRecipes();
    void SaveRecipes();
    void addRecipe();

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
