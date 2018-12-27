#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "cmotiondetecter.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    CMotionDetecter *m_pMDector;
public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_bntEnMotion_clicked();

    void on_bntUpdate_clicked();

    void on_sldX_actionTriggered(int action);

    void on_sldY_actionTriggered(int action);

    void on_sldY_thro_actionTriggered(int action);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
