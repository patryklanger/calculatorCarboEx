#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTableWidgetItem>
#include <QPushButton>
#include <json/json.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::showEvent(QShowEvent *ev)
{
    QMainWindow::showEvent(ev);
    showEventHelper();
}

void MainWindow::showEventHelper()
{
    starterGlobalObj.init();
    fetch();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fetch()
{
    ui->productsTable->addProductsToTable();
    ui->dishesTable->addProductsToTable();
    ui->dishesTable_2->addProductsToTable();
    ui->yourDishesBut->setEnabled(true);
    ui->yourProductsBut->setEnabled(true);
    ui->yourMealsBut->setEnabled(true);
}

void MainWindow::on_yourMealsBut_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_7_clicked()
{
    Product product = Product(
                (float)ui->protein_2->value(),
                (float)ui->fat_2->value(),
                (float)ui->carbo_2->value(),
                (float)ui->fiber_2->value(),
                ui->productName_2->text().toStdString());

    ui->protein_2->setValue(0);
    ui->fat_2->setValue(0);
    ui->carbo_2->setValue(0);
    ui->fiber_2->setValue(0);
    ui->productName_2->setText("");
    ui->productName_2->setFocus();
    ui->productsTable->addProductsToTable();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_yourProductsBut_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_addProductBut_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_pushButton_clicked()
{
    QItemSelectionModel *select = ui->productsTable->selectionModel();
    auto rows = select->selectedRows();
    auto row = rows.begin();
    while(row)
    {
        std::string name = ui->productsTable->item(row->row(), 0)->text().toStdString();
        float carbo = ui->productsTable->item(row->row(), 1)->text().remove(-1,1).toFloat();
        float fat = ui->productsTable->item(row->row(), 2)->text().remove(-1,1).toFloat();
        float prot = ui->productsTable->item(row->row(), 3)->text().remove(-1,1).toFloat();
        float fiber = ui->productsTable->item(row->row(), 4)->text().remove(-1,1).toFloat();
        ui->productsTable->removeRow(row->row());

        Product* tempProd = new Product(prot,fat,carbo,fiber,name,false);
        tempProd->deleteProduct();
        select = ui->productsTable->selectionModel();
        rows = select->selectedRows();
        row = rows.begin();
        delete tempProd;
    }
}



void MainWindow::on_yourDishesBut_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}





void MainWindow::on_dishesTable_2_cellDoubleClicked(int row)
{

   auto dishName = ui->dishesTable_2->item(row,0)->text();
   ui->dishIngTable->addDishesProductsToTable(dishName.toStdString());
   ui->dishNameLabel->setText("Składniki dania: " + dishName);
   ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->dishIngTable->formatTable();
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_dishesTable_cellDoubleClicked(int row)
{
    auto timestamp = ui->dishesTable->item(row,7)->text();
    auto date = ui->dishesTable->item(row,0)->text();
    ui->mealIngTable->addMealProductsToTable(timestamp.toStdString());
    ui->mealDateLabel->setText("Posiłek z " + date);
    ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::on_backButton_clicked()
{
    ui->mealIngTable->formatTable();
    ui->stackedWidget->setCurrentIndex(1);
}



void MainWindow::on_addMealBut_2_clicked()
{
    ui->dishNameInput->setText("");
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_dishSet1Next_clicked()
{
    ui->newDishProdTable->addProductsToTableWithCheckbox();
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_addProductBut_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
}

void MainWindow::on_pushButton_8_clicked()
{
    Product product = Product(
                (float)ui->protein_3->value(),
                (float)ui->fat_3->value(),
                (float)ui->carbo_3->value(),
                (float)ui->fiber_3->value(),
                ui->productName_3->text().toStdString(), false);

    ui->newDishProdTable->insertProduct(product);

    ui->protein_3->setValue(0);
    ui->fat_3->setValue(0);
    ui->carbo_3->setValue(0);
    ui->fiber_3->setValue(0);
    ui->productName_3->setText("");
    ui->productName_3->setFocus();
    ui->stackedWidget->setCurrentIndex(8);
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_pushButton_6_clicked()
{
    Dish tempDish(ui->dishNameInput->text().toStdString());
    for( int i=0 ; i < ui->newDishProdTable->rowCount() ; i++)
    {
        QCheckBox *checkbox = qobject_cast<QCheckBox*>(ui->newDishProdTable->cellWidget(i, 0));
        if(checkbox->isChecked())
        {
            tempDish.addProduct(
                        ui->newDishProdTable->item(i,1)->text().toStdString(),
                        ui->newDishProdTable->item(i,4)->text().remove(-1,1).toFloat(),
                        ui->newDishProdTable->item(i,3)->text().remove(-1,1).toFloat(),
                        ui->newDishProdTable->item(i,2)->text().remove(-1,1).toFloat(),
                        ui->newDishProdTable->item(i,5)->text().remove(-1,1).toFloat());
        }
    }

    tempDish.post();

    ui->productsTable->addProductsToTable();
    ui->dishesTable_2->addProductsToTable();
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_pushButton_9_clicked()
{
    QItemSelectionModel *select = ui->dishesTable_2->selectionModel();
    auto rows = select->selectedRows();
    auto row = rows.begin();
    while(row)
    {
        std::string dishName = ui->dishesTable_2->item(row->row(),0)->text().toStdString();
        Dish dish = starterGlobalObj.globalDishesObj.getDishByName(dishName);
        dish.deleteDish();
        ui->dishesTable_2->removeRow(row->row());
        select = ui->dishesTable_2->selectionModel();
        rows = select->selectedRows();
        row = rows.begin();
    }
}


void MainWindow::on_addMealBut_clicked()
{
    ui->mealAddedDishTab->formatTable();
    ui->mealAddedProdTab->formatTable();
    ui->mealAddProdTab->addProductsToTable();
    ui->mealAddDishTab->addProductsToTable();
    ui->sumaWW->setText("0");
    ui->sumaWBT->setText("0");
    ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::on_mealAddProdBut_clicked()
{
    ui->stackedWidget->setCurrentIndex(11);

}

void MainWindow::on_addProductBut_3_clicked()
{
    QItemSelectionModel *select = ui->mealAddProdTab->selectionModel();
    auto rows = select->selectedRows();
    auto row = rows.begin();
    while(row)
    {
        auto productName = ui->mealAddProdTab->item(row->row(),0)->text().toStdString();
        ui->mealAddedProdTab->addProductToTable(productName);
        auto product = starterGlobalObj.globalProductsObj.getProductByName(productName);
        auto summedCarboEx = ui->sumaWW->text().toFloat();
        auto summedProtFatEx = ui->sumaWBT->text().toFloat();
        summedCarboEx += product.getCarboEx();
        summedProtFatEx += product.getFatProtEx();
        ui->sumaWW->setText(QString::number(summedCarboEx));
        ui->sumaWBT->setText(QString::number(summedProtFatEx));
        ui->mealAddProdTab->removeRow(row->row());
        select = ui->mealAddProdTab->selectionModel();
        rows = select->selectedRows();
        row = rows.begin();
    }
    ui->stackedWidget->setCurrentIndex(10);
}


void MainWindow::on_pushButton_10_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}



void MainWindow::on_mealAddDishButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(12);
}

void MainWindow::on_mealAddDishBut_clicked()
{
    QItemSelectionModel *select = ui->mealAddDishTab->selectionModel();
    auto rows = select->selectedRows();
    auto row = rows.begin();
    while(row)
    {
        auto dishName = ui->mealAddDishTab->item(row->row(),0)->text().toStdString();
        ui->mealAddedDishTab->addProductToTable(dishName);
        auto dish = starterGlobalObj.globalDishesObj.getDishByName(dishName);
        auto summedCarboEx = ui->sumaWW->text().toFloat();
        auto summedProtFatEx = ui->sumaWBT->text().toFloat();
        summedCarboEx += dish.getCarboEx();
        summedProtFatEx += dish.getFatProtEx();
        ui->sumaWW->setText(QString::number(summedCarboEx));
        ui->sumaWBT->setText(QString::number(summedProtFatEx));
        ui->mealAddDishTab->removeRow(row->row());
        select = ui->mealAddDishTab->selectionModel();
        rows = select->selectedRows();
        row = rows.begin();
    }
    ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
}

void MainWindow::on_addMealButton_clicked()
{
    Meal meal;
    for( int i = 0 ; i < ui->mealAddedProdTab->rowCount() ; i++ )
    {
        auto productName = ui->mealAddedProdTab->item(i,0)->text();
        auto product = starterGlobalObj.globalProductsObj.getProductByName(productName.toStdString());
        meal.addToMap(product);
    }
    for( int i = 0 ; i < ui->mealAddedDishTab->rowCount() ; i++ )
    {
        auto dishName = ui->mealAddedDishTab->item(i,0)->text();
        auto dish = starterGlobalObj.globalDishesObj.getDishByName(dishName.toStdString());
        meal.addToMap(dish);
    }
    meal.post();
    ui->dishesTable->addProductsToTable();
    ui->stackedWidget->setCurrentIndex(1);
}
