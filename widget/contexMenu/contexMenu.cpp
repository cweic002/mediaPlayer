#include "contexMenu.h"
#include "ui_contexMenu.h"

Widget::ContexMenu::ContexMenu(QWidget *parent):QMenu(parent),ui_(new Ui::ContexMenu)
{
    QWidget::setParent(parent);
    ui_->setupUi(this);
}

Widget::ContexMenu::~ContexMenu()
{
    delete ui_;
}
