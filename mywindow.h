// Plik naglowkowy klasy MyWindow
// Obiekt tej klasy to glowne okno naszej aplikacji
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QGroupBox>
#include <QPainter>
#include <QImage>
#include <QSlider>
#include <QMouseEvent>
#include <qlabel.h>
#include <cmath>

class Punkt {
public:
    int x,y,z;
    int w = 1;

    Punkt(int x, int y,int z):x(x),y(y),z(z){};
    Punkt(int x,int y):x(x),y(y){};
    Punkt(){};
    ~Punkt();

    Punkt(Punkt &p);
    void operator=(Punkt p);
    void values();

};


class Matrix {
public:
  float data[4][4];

  Matrix();

  void setTranslation(float x, float y, float z);

  void setRotationX(float angle);

  void setRotationY(float angle);

  void setRotationZ(float angle);

  void setScale(float scaleX, float scaleY, float scaleZ);

  void multiply(Matrix& matrix);

  void transformPoint(float &x, float &y, float &z);

  void values();

  void setPoints(Punkt &p);

  Punkt multiply(Punkt &p);

  Punkt operator*(Punkt &p);
};

class MyWindow : public QWidget
{
    Q_OBJECT
public:
    MyWindow(QWidget *parent = 0);
    ~MyWindow();
private:
    int szer;
    int wys;
    int poczX;
    int poczY;
    QImage *screen;
    QImage *orig;

    QLabel *translationX;
    QLabel *translationY;
    QLabel *translationZ;
    QLabel *rotationX;
    QLabel *rotationY;
    QLabel *rotationZ;
    QLabel *scalingX;
    QLabel *scalingY;
    QLabel *scalingZ;

    QSlider *StranslationX;
    QSlider *StranslationY;
    QSlider *StranslationZ;
    QSlider *SrotationX;
    QSlider *SrotationY;
    QSlider *SrotationZ;
    QSlider *SscalingX;
    QSlider *SscalingY;
    QSlider *SscalingZ;

    QGroupBox *grupa;

    Punkt cubePointsT[8];
    Punkt cubePoints[8];
    Matrix tMatrix;

    std::array<int, 3> getPixelColor(Punkt p1);
    std::array<int, 3> getInterColor(float x, float y);

    int red[3] = {175,0,185};

    void setPixelColor(int x,int y,int color[3]);
    int VtranslationX;
    int VtranslationY;
    int VtranslationZ;
    int VrotationX;
    int VrotationY;
    int VrotationZ;
    float VscalingX;
    float VscalingY;
    float VscalingZ;
    void copy();
    void czysc();
    void przeksztalc();
    void drawLine(Punkt p1, Punkt p2);
    void drawCube();
    void makeCube(int r);

public slots:
    void slot_translationX(int value);
    void slot_translationY(int value);
    void slot_translationZ(int value);
    void slot_rotationX(int value);
    void slot_rotationY(int value);
    void slot_rotationZ(int value);
    void slot_scalingX(int value);
    void slot_scalingY(int value);
    void slot_scalingZ(int value);

    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent*);
};


