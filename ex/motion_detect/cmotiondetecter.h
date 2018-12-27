#ifndef CMOTIONDETECTER_H
#define CMOTIONDETECTER_H

#include <QObject>
#include <QThread>

class CMotionDetecter : public QThread
{
    Q_OBJECT
    bool m_bRunning;
    bool m_bUpdate;
    int  m_nGaussianBlurX;
    int  m_nGaussianBlurY;
    double  m_nThresholdLev;
public:
    explicit CMotionDetecter();
    void run();
signals:

public slots:
    void start();
    void stop();
    void updateGround();
    void setGaussianBlurSize(int x,int y);
    void setThreshold(int nLev);

};

#endif // CMOTIONDETECTER_H
