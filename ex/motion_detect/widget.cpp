#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_pMDector = new CMotionDetecter();
}

Widget::~Widget()
{
    m_pMDector->stop();
    delete m_pMDector;
    delete ui;
}

void Widget::on_bntEnMotion_clicked()
{
    if(!m_pMDector->isRunning()){
        m_pMDector->start();
        ui->bntEnMotion->setText("stop Motion Detect");
    }
    else {
        m_pMDector->stop();
        ui->bntEnMotion->setText("Start Motion Detect");
    }
}

void Widget::on_bntUpdate_clicked()
{
    m_pMDector->updateGround();
}

void Widget::on_sldX_actionTriggered(int action)
{
    m_pMDector->setGaussianBlurSize(ui->sldX->value() ,ui->sldY->value());
}

void Widget::on_sldY_actionTriggered(int action)
{
    m_pMDector->setGaussianBlurSize(ui->sldX->value() ,ui->sldY->value());
}

void Widget::on_sldY_thro_actionTriggered(int action)
{
    m_pMDector->setThreshold(ui->sldY_thro->value());
}
