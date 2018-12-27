#include "cmotiondetecter.h"

#include <opencv2/opencv.hpp>
//#include <opencv2/tracking.hpp>
#include <opencv2/core/ocl.hpp>
#include <unistd.h>
#include <QDebug>

using namespace cv;
using namespace std;

CMotionDetecter::CMotionDetecter()
{
    m_bRunning = false;
    m_nGaussianBlurX = 21;
    m_nGaussianBlurY = 21;
    m_nThresholdLev  = 25;
}

void CMotionDetecter::run()
{
    int nMotionCnt=0;
    m_bRunning = true;
    Mat frame, gray, frameDelta, thresh, firstFrame;
    vector<vector<Point> > cnts;
    VideoCapture camera(0); //open camera

    //set the video size to 512x288 to process faster
    camera.set(3, 512);
    camera.set(4, 288);

    //sleep(3);
    camera.read(frame);

    //convert to grayscale and set the first frame
    cvtColor(frame, firstFrame, COLOR_BGR2GRAY);
    GaussianBlur(firstFrame, firstFrame, Size(m_nGaussianBlurX, m_nGaussianBlurY), 0);

    while(camera.read(frame)) {
//qDebug("[%d,%d]\n",m_nGaussianBlurX,m_nGaussianBlurY);
        //|| nMotionCnt > 30
        if(m_bUpdate==true ){
            cvtColor(frame, firstFrame, COLOR_BGR2GRAY);
            GaussianBlur(firstFrame, firstFrame, Size(m_nGaussianBlurX, m_nGaussianBlurY), 0);
            m_bUpdate = false;
            nMotionCnt = 0;
        }

        //convert to grayscale
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        GaussianBlur(gray, gray, Size(m_nGaussianBlurX, m_nGaussianBlurY), 0);


        //compute difference between first frame and current frame
        absdiff(firstFrame, gray, frameDelta);
        threshold(frameDelta, thresh, m_nThresholdLev, 255, THRESH_BINARY);

        dilate(thresh, thresh, Mat(), Point(-1,-1), 10);
        findContours(thresh, cnts, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        printf("cnts=%d\n",cnts.size());
        for(int i = 0; i< cnts.size(); i++) {
            printf("cnts[%d]=%d\n",i,contourArea(cnts[i]));
            if(contourArea(cnts[i]) < 500) {
                continue;
            }
            putText(frame, "Motion Detected", Point(10, 20), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
            ++nMotionCnt;
         }

        imshow("Camera", frame);
        imshow("gray", gray);
        imshow("thresh", thresh);
        imshow("frameDelta", frameDelta);
        waitKey(30);

        if(m_bRunning==false)break;

    }
    m_bRunning = false;
}
void CMotionDetecter::start()
{
    QThread::start();
}
void CMotionDetecter::stop()
{
    m_bRunning = false;
    wait();
}
void CMotionDetecter::updateGround()
{
    m_bUpdate = true;
}

void CMotionDetecter::setGaussianBlurSize(int x,int y)
{
    m_nGaussianBlurX = 2*x + 1;
    m_nGaussianBlurY = 2*y + 1;
}

void CMotionDetecter::setThreshold(int nLev)
{
    m_nThresholdLev = nLev;
}
