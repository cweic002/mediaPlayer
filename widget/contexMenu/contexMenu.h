#pragma once
#include <QMenu>

namespace Ui {
class ContexMenu;
}

namespace Widget {
    class ContexMenu : public QMenu{
        Q_OBJECT
    public:
        explicit ContexMenu(QWidget *parent = nullptr);
        virtual ~ContexMenu();
    private:
        Ui::ContexMenu *ui;
    };
}

