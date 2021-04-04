#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include "networking/headers/Fetcher.hpp"
#include "networking/headers/Poster.hpp"
#include "data_structs/headers/Food.hpp"
#include "data_structs/headers/Meal.hpp"
#include "data_structs/headers/Product.hpp"
#include "data_structs/headers/Dish.hpp"
#include "data_structs/headers/Dishes.hpp"
#include "data_structs/headers/Products.hpp"
#include "global_obj.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <iostream>
#include <QCheckBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void fetch();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_7_clicked();

    void on_yourMealsBut_clicked();

    void on_yourProductsBut_clicked();

    void on_addProductBut_clicked();

    void on_pushButton_clicked();

    void on_yourDishesBut_clicked();

    void on_dishesTable_2_cellDoubleClicked(int row);

    void on_pushButton_2_clicked();

    void on_dishesTable_cellDoubleClicked(int row);

    void on_backButton_clicked();

    void on_addMealBut_2_clicked();

    void on_dishSet1Next_clicked();

    void on_pushButton_3_clicked();

    void on_addProductBut_2_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

    void on_addMealBut_clicked();

    void on_mealAddProdBut_clicked();

    void on_addProductBut_3_clicked();

    void on_pushButton_10_clicked();

    void on_mealAddDishButton_clicked();

    void on_mealAddDishBut_clicked();

    void on_pushButton_11_clicked();

    void on_addMealButton_clicked();

protected:
    void showEvent(QShowEvent *ev);
private:
    void showEventHelper();
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
