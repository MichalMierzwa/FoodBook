#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ingredientcombobox.h"
#include "recipe.h"

#include <QtCore>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QTimer>
#include <QMouseEvent>
#include <QFileDialog>
#include <QMetaType>
#include <QVariant>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("FoodBook");

    //CUSTOM OBJECT "RECIPE" ENABLED
    qRegisterMetaType<recipe>("recipe");
    qRegisterMetaTypeStreamOperators<recipe>("recipe");

    //LOAD LISTAPRZEPISOW FROM QSETTINGS
    QSettings mySettings("MichaU", "FoodBook");
    LoadIngredients();
    LoadRecipes();
    LoadTable();

    //Removes the red fields on page2 when user corrects his choice
    connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(setDefaultStyleSheet()));
    connect(ui->CategoryComboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(setDefaultStyleSheet()));
    //connect(ui->listWidget, SIGNAL(indexesMoved(QModelIndexList)),this, SLOT(setDefaultStyleSheet()));
    connect(ui->PickComboBox, SIGNAL(currentTextChanged(QString)), this, SLOT(setDefaultStyleSheet()));

    connect(ui->lineEdit_EditRecipe, SIGNAL(textChanged(QString)), this, SLOT(EditButtonActivation()));

// ---------------------------------------------PLAYGROUND---------------------------------------------


    // ========================= DZIAŁAJĄCE QVARIANT CUSTOM OBJECT DO QSETTINGS!!! ====================
    // ================================================================================================
    //    recipe przepis;
    //    przepis.setName("M");
    //    przepis.setDescription("asdasdasd");

    //    mySettings.setValue("recipe",QVariant::fromValue(przepis));
    //    qDebug() << mySettings.value("recipe");

    //    QVariant value = mySettings.value("recipe");
    //    recipe rec = value.value<recipe>();
    //    qDebug() << rec.Name() << rec.Description();
    // ================================================================================================

    // WAŻNE !!! NIE USUWAĆ !!! WCZYTYWANIE QSETTINGS WRZUCANYCH DO GRUPY!
    // EXAMPLE
    //    settings.beginGroup("Whatever");
    //    QStringList keys = settings.childKeys();
    //    foreach (QString key, keys) {
    //         map[key] = settings.value(key).toInt();
    //    }
    //    settings.endGroup();
    // ================================================================================================
    // ================================================================================================



// ======================================================================================



    // SETTING THE TIMER
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
    showTime();

    // MOUSE ACTIONS USING EVENTFILTER
    ui->label->installEventFilter(this);
    ui->label_2->installEventFilter(this);
    ui->label_3->installEventFilter(this);
    ui->label_4->installEventFilter(this);
    ui->label_5->installEventFilter(this);
    ui->label_6->installEventFilter(this);
    ui->label_8->installEventFilter(this);
    ui->PickComboBox->installEventFilter(this);
    ui->CategoryComboBox->installEventFilter(this);

    ui->label->setAttribute(Qt::WA_Hover, true);
    ui->label_2->setAttribute(Qt::WA_Hover, true);
    ui->label_3->setAttribute(Qt::WA_Hover, true);
    ui->label_4->setAttribute(Qt::WA_Hover, true);
    ui->label_5->setAttribute(Qt::WA_Hover, true);
    ui->label_6->setAttribute(Qt::WA_Hover, true);

    connect(ui->PickComboBox, SIGNAL(activated(QString)),this, SLOT(AddToList(QString)));

    //PREPARE TIME LIMITED TO 24h, 60 min
    //    QValidator *validatorHours = new QIntValidator(1, 24, this);
    //    ui->lineEditTimeHr->setValidator(validatorHours);
    //    ui->lineEditTimeHr->setInputMask("DD");

    //SETS INGREDIENT COUNTER INVIS (QDoubleSpinBox'y)
    QList<QDoubleSpinBox*> SpinBoxList = this->findChildren<QDoubleSpinBox *> ();
    foreach(QDoubleSpinBox* dblSpinBoxPtr, SpinBoxList)
    {
        dblSpinBoxPtr->setValue(0);
        dblSpinBoxPtr->setVisible(false);
    }

    //WHITE BACKGROUND TURNED OFF UNDER INGREDIENTS
    ui->listWidget->viewport()->setAutoFillBackground(false);

    //TABLEWIDGET COLUMNS WIDTH
    ui->tableWidget->setColumnWidth(0,200);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,50);
    ui->tableWidget->setColumnWidth(3,50);
    ui->tableWidget->setColumnWidth(4,50);
    ui->tableWidget->setColumnWidth(5,120);
    ui->tableWidget->setColumnWidth(6,20);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//==========================================================================================
//==========================================================================================

// SETS THE TIMER
void MainWindow::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    ui->lcdNumber->display(text);
}

// BEGIN - EVENTFILTER
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{

    //  BEGIN - MAIN MENU BUTTONS - STACKED WIDGET PAGES ------------------------
    if(obj == ui->label)
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
            ui->tableWidget->setRowCount(0);
            LoadRecipes();
            LoadTable();
            ui->stackedWidget->setCurrentIndex(1);
            return false;
        }

        if(event->type() == QEvent::HoverEnter)
        {
            ui->InfoLineEdit->setText("Wyświetl wszystkie przepisy");
            return false;
        }

        if(event->type() == QEvent::HoverLeave)
        {
            defaultInfoLineText();
            return false;
        }
    }

    if(obj == ui->label_2)
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
            ui->lineEdit->setStyleSheet("border-radius: 8px;");
            ui->CategoryComboBox->setStyleSheet("");
            ui->PickComboBox->setStyleSheet("");

            ui->lineEdit->clear();
            ui->PickComboBox->clear();
            ui->listWidget->clear();
            LoadIngredients();

            QList<QDoubleSpinBox*> SpinBoxList = this->findChildren<QDoubleSpinBox *> ();
            foreach(QDoubleSpinBox* dblSpinBoxPtr, SpinBoxList)
            {
                dblSpinBoxPtr->setValue(0);
                dblSpinBoxPtr->setVisible(false);
            }
            ui->stackedWidget->setCurrentIndex(2);
            return false;
        }

        if(event->type() == QEvent::HoverEnter)
        {
            ui->InfoLineEdit->setText("Dodaj/modyfikuj przepisy");
            return false;
        }

        if(event->type() == QEvent::HoverLeave)
        {
            defaultInfoLineText();
            return false;
        }
    }

    if(obj == ui->label_3)
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
            ui->stackedWidget->setCurrentIndex(3);
            return false;
        }

        if(event->type() == QEvent::HoverEnter)
        {
            ui->InfoLineEdit->setText("Kalendarz");
            return false;
        }

        if(event->type() == QEvent::HoverLeave)
        {
            defaultInfoLineText();
            return false;
        }
    }

    if(obj == ui->label_4)
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
            ui->stackedWidget->setCurrentIndex(4);
            return false;
        }

        if(event->type() == QEvent::HoverEnter)
        {
            ui->InfoLineEdit->setText("Ustaw Składniki");
            return false;
        }

        if(event->type() == QEvent::HoverLeave)
        {
            defaultInfoLineText();
            return false;
        }
    }

    if(obj == ui->label_5)
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
            ui->stackedWidget->setCurrentIndex(5);
            return false;
        }

        if(event->type() == QEvent::HoverEnter)
        {
            ui->InfoLineEdit->setText("Generuj Dania");
            return false;
        }

        if(event->type() == QEvent::HoverLeave)
        {
            defaultInfoLineText();
            return false;
        }
    }

    if(obj == ui->label_6)
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
            ui->stackedWidget->setCurrentIndex(6);
            return false;
        }

        if(event->type() == QEvent::HoverEnter)
        {
            ui->InfoLineEdit->setText("Tablica Kalorii");
            return false;
        }

        if(event->type() == QEvent::HoverLeave)
        {
            defaultInfoLineText();
            return false;
        }
    }

    if(obj == ui->label_6)
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
            ui->stackedWidget->setCurrentIndex(6);
            return false;
        }

        if(event->type() == QEvent::HoverEnter)
        {
            ui->InfoLineEdit->setText("Tablica Kalorii");
            return false;
        }

        if(event->type() == QEvent::HoverLeave)
        {
            defaultInfoLineText();
            return false;
        }
    }
    // END - MAIN MENU BUTTONS - STACKED WIDGET PAGES  ----------------------

    // BROWSE IMAGE AFTER THE CLICK
    if(obj == ui->label_8)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"));

            if(fileName.isEmpty())
            {
                 return false;
            }

            else
            {
                // WPROWADZIC FILTR ROZSZERZEN!!!!!!!!!!!!!!!!!!!
                QPixmap *Image = new QPixmap(fileName);
                ui->label_8->setPixmap(*Image);
                return false;
            }
        }
    }
    return false;

    // BEGIN - COMBOBOX - CHOOSE INGREDIENT --------------------------------------------
    if(obj == ui->PickComboBox)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            ui->PickComboBox->showPopup();
            return false;
        }
        if(event->type() == QEvent::MouseButtonPress)
        {
            ui->PickComboBox->hidePopup();
            return false;
        }

    }
    // END - COMBOBOX - CHOOSE INGREDIENT --------------------------------------------

    // BEGIN - COMBOBOX - PICK CATEGORY --------------------------------------------
    if(obj == ui->CategoryComboBox)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            ui->CategoryComboBox->showPopup();
            return false;
        }
        if(event->type() == QEvent::MouseButtonPress)
        {
            ui->CategoryComboBox->hidePopup();
            return false;
        }
    }
    // END - COMBOBOX - PICK CATEGORY --------------------------------------------
}
// END - EVENTFILTER

// DEFAULT TEXT IN THE TOP LINEEDIT
void MainWindow::defaultInfoLineText()
{
    ui->InfoLineEdit->setText("");
    ui->InfoLineEdit->setPlaceholderText("Miejsce na informacje");
}

// BACK TO MAIN MENU BUTTONS ON EACH PAGE
void MainWindow::on_MainPageButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_MainPageButton_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_MainPageButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_MainPageButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_MainPageButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_MainPageButton_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_MainPageButton_7_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
}

// ADD CHOSEN INGREDIENT FROM COMBOBOX TO THE LIST
void MainWindow::AddToList(QString Ingredient)
{
    if(ui->listWidget->count() < 13)
    {
        ui->listWidget->addItem(Ingredient);
        ui->listWidget->repaint();

        IngredientUpdateUP();
    }
}

// REMOVE CLICKED INGREDIENT FROM THE LIST
void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    IngredientUpdateDOWN();

    int rowClicked = item->listWidget()->row(item);
    ui->listWidget->takeItem(rowClicked);
}

void MainWindow::addRecipe()
{
//    //DODAJE KOLEJNY RZĄD
//    ui->tableWidget->insertRow(ui->tableWidget->rowCount());

//    //SPOSOB PIERWSZY - ZAPISAC DANE DO TAB. PODSUMOWANIA ==================================

//    //DODAJE NAZWE PRZEPISU DO PODSUMOWANIA
//    static int freeRow = 0;
//    QTableWidgetItem *newItem = new QTableWidgetItem;
//    ui->tableWidget->setItem(freeRow,0, newItem);
//    newItem->setText(ui->lineEdit->text());

//    //DODAJE KATEGORIE DO PODSUMOWANIA
//    QString Kategoria;
//    if(ui->CategoryComboBox->currentText() != "Wybierz kategorię")
//    {
//        Kategoria = ui->CategoryComboBox->currentText();
//        QTableWidgetItem *newItem = new QTableWidgetItem;
//        newItem->setText(Kategoria);
//        ui->tableWidget->setItem(freeRow,1, newItem);
//    }

//    //DODAJE LICZBE SKLADNIKOW DO PODSUMOWANIA
//    {
//    QTableWidgetItem *newItem = new QTableWidgetItem;
//    newItem->setText(QString::number(ui->listWidget->count()));
//    ui->tableWidget->setItem(freeRow,2, newItem);
//    }

//    //Utworzenie listy wybranych skladnikow w przepisie
//    QStringList ListaSkladnikow;
//    for(int i = 0; i < ui->listWidget->count(); i++)
//    {
//        ListaSkladnikow.append(ui->listWidget->item(i)->text());
//    }
//    ===========================================================================================

    // SPOSOB DRUGI - QSETTINGS ==================================================
    SaveRecipes();
}

void MainWindow::on_SaveButton_clicked()
{
    if(ui->lineEdit->text().isEmpty())
    {
        ui->lineEdit->setStyleSheet("border : 3px solid red; border-radius: 10px;");   
    }
    if(ui->labelPickedCategory->text().isEmpty())
    {
        ui->CategoryComboBox->setStyleSheet("border : 3px solid red;");
    }
    if(ui->listWidget->count() == 0)
    {
        ui->PickComboBox->setStyleSheet("border-style: outset ;border : 3px solid red;");
    }

    //CAN RECIPE BE ADDED CONDITIONS:
    if(!ui->lineEdit->text().isEmpty() && !ui->labelPickedCategory->text().isEmpty()
            && ui->listWidget->count() != 0)
    {
        addRecipe();

        ui->lineEdit->clear();
        ui->lineEdit_Source->clear();
        ui->textEdit->clear();
        ui->listWidget->clear();
        ui->labelPickedCategory->clear();
        ui->CategoryComboBox->setCurrentIndex(0);
        ui->lineEdit_Portion->clear();
        ui->lineEditTimeHr->clear();
        ui->lineEditTimeMin->clear();

        QList<QDoubleSpinBox*> SpinBoxList = this->findChildren<QDoubleSpinBox *> ();
        for(int i = 0; i < SpinBoxList.count(); i++)
        {
            SpinBoxList.at(i)->setValue(0);
            SpinBoxList.at(i)->setVisible(false);
        }

        ui->InfoLineEdit->setText("ZAPISANO PRZEPIS");

        QPixmap *defaultPic = new QPixmap("://splash.jpg");
        ui->label_8->setPixmap(*defaultPic);
    }
}

void MainWindow::on_PickComboBox_activated(const QString &arg1)
{
    if(ui->PickComboBox->currentIndex() == 0 && ui->PickComboBox->currentText() != "Wybierz składnik")
    {
          ui->PickComboBox->insertItem(0, "Wybierz składnik");
    }
    ui->PickComboBox->setCurrentIndex(0);
}

void MainWindow::on_CategoryComboBox_activated(const QString &arg1)
{
    ui->labelPickedCategory->setText(arg1);
    ui->CategoryComboBox->setCurrentIndex(0);
}

// BEGIN - TURNING SPINBOXES ON ACCORDING TO ITEMS ON THE LIST ---------------------
void MainWindow::IngredientUpdateUP()
{
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        QList<QDoubleSpinBox*> SpinBoxList = this->findChildren<QDoubleSpinBox *> ();

        SpinBoxList.at(i)->setVisible(true);
    }
}
void MainWindow::IngredientUpdateDOWN()
{
    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        QList<QDoubleSpinBox*> SpinBoxList = this->findChildren<QDoubleSpinBox *> ();
        SpinBoxList.at(ui->listWidget->count()-1)->setVisible(false);
    }
}
// END - TURNING SPINBOXES ON ACCORDING TO ITEMS ON THE LIST ------------------------

void MainWindow::on_quitAppButton_released()
{
    qApp->quit();
}

void MainWindow::LoadRecipes()
{
    QSettings mySettings("MichaU", "FoodBook");
    mySettings.beginGroup("All Recipes");
    QStringList keys = mySettings.childKeys();
    ListaPrzepisow.clear();
    for(int i = 0; i < keys.count(); i++)
    {
        QVariant value = mySettings.value(keys.at(i));
        recipe rec = value.value<recipe>();


        ListaPrzepisow.insert(i,rec);
    }
    mySettings.endGroup();
}

void MainWindow::SaveRecipes()
{
    recipe przepis;
    przepis.setName(ui->lineEdit->text());
    przepis.setSourceName(ui->lineEdit_Source->text());
    przepis.setDescription(ui->textEdit->toPlainText());
    przepis.setPortionNumber(ui->lineEdit_Portion->text().toInt());
    przepis.setCategory(ui->labelPickedCategory->text());
    przepis.setPrepareTimeHr(ui->lineEditTimeHr->text().toInt());
    przepis.setPrepareTimeMin(ui->lineEditTimeMin->text().toInt());
    przepis.setIngredientCounter(ui->listWidget->count());

    for (int i = 0; i < ui->listWidget->count(); i++)
    {
        QList<QDoubleSpinBox*> SpinBoxList = this->findChildren<QDoubleSpinBox *> ();

        przepis.IngredientList.append(ui->listWidget->item(i)->text());
        przepis.IngredientCountList.append(SpinBoxList.at(i)->text().toInt());
    }
    QSettings mySettings("MichaU", "FoodBook");

    mySettings.beginGroup("All Recipes");
    mySettings.setValue(przepis.Name(),QVariant::fromValue(przepis));
    mySettings.endGroup();
}

void MainWindow::LoadTable()
{
    //FILL THE ALLRECIPE TABLE (ui->tableWidget)
    for(int i = 0; i < ListaPrzepisow.count(); i++)
    {

    ui->tableWidget->insertRow(i);
    ui->tableWidget->setItem(i,0, new QTableWidgetItem(ListaPrzepisow.at(i).Name()));
    ui->tableWidget->setItem(i,1, new QTableWidgetItem(ListaPrzepisow.at(i).Category()));
    ui->tableWidget->setItem(i,2, new QTableWidgetItem(QString::number(ListaPrzepisow.at(i).IngredientCounter())));
    ui->tableWidget->setItem(i,3, new QTableWidgetItem(QString::number(ListaPrzepisow.at(i).PortionNumber())));

    if(ListaPrzepisow.at(i).Description().isEmpty())
    {
        ui->tableWidget->setItem(i,4, new QTableWidgetItem("NO"));
    }
    else (ui->tableWidget->setItem(i,4, new QTableWidgetItem("YES")));

    //Time format - Column 5 ========================================================================
    QString timeString("");
    if(ListaPrzepisow.at(i).PrepareTimeHr() == 0 && ListaPrzepisow.at(i).PrepareTimeMin() == 0)
    {
        timeString = QString("Brak danych");
    }
    if(ListaPrzepisow.at(i).PrepareTimeHr() != 0 && ListaPrzepisow.at(i).PrepareTimeMin() == 0)
    {
        if(ListaPrzepisow.at(i).PrepareTimeHr() == 1)
        {
            timeString = QString((QString::number(ListaPrzepisow.at(i).PrepareTimeHr()))) + QString(" godzina");
        }
        if(ListaPrzepisow.at(i).PrepareTimeHr() > 1 && ListaPrzepisow.at(i).PrepareTimeHr() < 5)
        {
            timeString = QString((QString::number(ListaPrzepisow.at(i).PrepareTimeHr()))) + QString(" godziny");
        }

        if(ListaPrzepisow.at(i).PrepareTimeHr() > 4)
        {
            timeString = QString((QString::number(ListaPrzepisow.at(i).PrepareTimeHr()))) + QString(" godzin");
        }
    }
    if(ListaPrzepisow.at(i).PrepareTimeHr() == 0 && ListaPrzepisow.at(i).PrepareTimeMin() != 0)
    {
        if(ListaPrzepisow.at(i).PrepareTimeMin() == 1)
        {
            timeString = QString((QString::number(ListaPrzepisow.at(i).PrepareTimeMin()))) + QString(" minuta");
        }
        if(ListaPrzepisow.at(i).PrepareTimeMin() > 1 && ListaPrzepisow.at(i).PrepareTimeMin() < 5)
        {
            timeString = QString((QString::number(ListaPrzepisow.at(i).PrepareTimeMin()))) + QString(" minuty");
        }
        if(ListaPrzepisow.at(i).PrepareTimeMin() > 4)
        {
            timeString = QString((QString::number(ListaPrzepisow.at(i).PrepareTimeMin()))) + QString(" minut");
        }
    }
    if(ListaPrzepisow.at(i).PrepareTimeHr() != 0 && ListaPrzepisow.at(i).PrepareTimeMin() != 0)
    {
        timeString = QString(" : ") ;
        timeString.prepend(QString::number(ListaPrzepisow.at(i).PrepareTimeHr()) + "h");
        timeString.append(QString::number(ListaPrzepisow.at(i).PrepareTimeMin()) + "min");
    }
    // =======================================================================================================

    ui->tableWidget->setItem(i,5, new QTableWidgetItem(timeString));
    ui->tableWidget->setItem(i,6, new QTableWidgetItem());
    ui->tableWidget->item(i,6)->setCheckState(Qt::Unchecked);

    ui->tableWidget->item(i,1)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->item(i,2)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->item(i,4)->setTextAlignment(Qt::AlignCenter);
    ui->tableWidget->item(i,5)->setTextAlignment(Qt::AlignCenter);
    }
}

void MainWindow::on_pushButton_RemoveNumber_released()
{    
    QSettings mySettings("MichaU", "FoodBook");
    mySettings.beginGroup("All Recipes");

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
    {
        if(ui->tableWidget->item(i, 6)->checkState() == Qt::Checked)
        {
            mySettings.remove(ui->tableWidget->item(i, 0)->text());
        }
    }
//  REFRESH TABLEWIDGET!!
    ui->tableWidget->setRowCount(0);
    LoadRecipes();
    LoadTable();
//  =====================
    mySettings.endGroup();
}

void MainWindow::on_pushButton_Settings_clicked()
{
    ui->listWidget_AllIngr->clear();
    LoadIngredients();
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_pushButton_released()
{
    QSettings mySettings("MichaU", "FoodBook");
    mySettings.beginGroup("All Ingredients");

    if(!ui->lineEdit_newIngr->text().isEmpty())
    {
        ui->listWidget_AllIngr->addItem(ui->lineEdit_newIngr->text());
        for(int i = 0; i < ui->listWidget_AllIngr->count(); i++)
        {
            mySettings.setValue(ui->listWidget_AllIngr->item(i)->text(), ui->listWidget_AllIngr->item(i)->text());
        }
        qDebug() << ui->lineEdit_newIngr->text();

        ui->lineEdit_newIngr->clear();
    }
    mySettings.endGroup();
}

void MainWindow::LoadIngredients()
{
    ui->PickComboBox->addItem("Wybierz składnik");

    QSettings mySettings("MichaU", "FoodBook");
    mySettings.beginGroup("All Ingredients");

    QStringList ingList = mySettings.childKeys();
    foreach(QString Ing, ingList)
    {
        ui->PickComboBox->addItem(Ing);
        ui->listWidget_AllIngr->addItem(Ing);
    }
    mySettings.endGroup();   
}

void MainWindow::on_listWidget_AllIngr_itemClicked(QListWidgetItem *item)
{
    QSettings mySettings("MichaU", "FoodBook");
    mySettings.beginGroup("All Ingredients");
    mySettings.remove(item->text());

    ui->listWidget_AllIngr->clear();
    LoadIngredients();

    mySettings.endGroup();
}

// Resets lineEdit stylesheet after markedRed to default...
void MainWindow::setDefaultStyleSheet()
{
    if(ui->lineEdit->styleSheet() != QString("border-radius: 8px") && !ui->lineEdit->text().isEmpty())
    {
        ui->lineEdit->setStyleSheet("border-radius: 8px");
    }

    if(!ui->labelPickedCategory->text().isEmpty())
    {
        ui->CategoryComboBox->setStyleSheet("");
    }

    if(ui->listWidget->count() != 0)
    {
        ui->PickComboBox->setStyleSheet("");

    }

}

// is lineEdit to edit recipe Empty - disables/enables Edit button
void MainWindow::EditButtonActivation()
{
    if(!ui->lineEdit_EditRecipe->text().isEmpty())
    {
        ui->pushButton_EditRecipe->setEnabled(true);
    }
    else ui->pushButton_EditRecipe->setEnabled(false);
}

void MainWindow::on_pushButton_EditRecipe_released()
{
    QSettings mySettings("MichaU", "FoodBook");
    mySettings.beginGroup("All Recipes");

    //Conversion from QVariant to custom object, 'recipe' type
    QString RecName = QString(ui->tableWidget->item(ui->lineEdit_EditRecipe->text().toInt(), 0)->text());
    QVariant value = mySettings.value(RecName);
    recipe rec = value.value<recipe>();

    ui->lineEdit->setText(rec.Name());
    ui->lineEdit_Source->setText(rec.SourceName());
    ui->textEdit->setText(rec.Description());
    ui->lineEdit_Portion->setText(QString::number(rec.PortionNumber()));
    ui->labelPickedCategory->setText(rec.Category());
    ui->lineEditTimeHr->setText(QString::number(rec.PrepareTimeHr()));
    ui->lineEditTimeMin->setText(QString::number(rec.PrepareTimeMin()));

    mySettings.endGroup();

//    przepis.setIngredientCounter(ui->listWidget->count());

//    for (int i = 0; i < ui->listWidget->count(); i++)
//    {
//        QList<QDoubleSpinBox*> SpinBoxList = this->findChildren<QDoubleSpinBox *> ();

//        przepis.IngredientList.append(ui->listWidget->item(i)->text());
//        przepis.IngredientCountList.append(SpinBoxList.at(i)->text().toInt());
//    }
    ui->stackedWidget->setCurrentIndex(2);
    ui->lineEdit_EditRecipe->clear();
}
