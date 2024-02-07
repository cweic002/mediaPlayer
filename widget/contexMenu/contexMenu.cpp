#include "contexMenu.h"
#include "ui_contexMenu.h"

Widget::ContexMenu::ContexMenu(QWidget *parent):QMenu(parent),ui(new Ui::ContexMenu)
{
    QWidget::setParent(parent);
    ui->setupUi(this);
}

Widget::ContexMenu::~ContexMenu()
{
    delete ui;
}
