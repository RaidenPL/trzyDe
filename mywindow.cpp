#include "mywindow.h"
#include <QLabel>
#include <QVBoxLayout>
#define PI 3.14159265
Punkt::~Punkt(){}

void Punkt::operator=(Punkt p)
{
    x = p.x;
    y = p.y;
    z = p.z;
    w = p.w;
}

Matrix::Matrix() {
    memset(data, 0, sizeof(data));
    setIdentity();
}

void Matrix::setIdentity() {
    memset(data, 0, sizeof(data));
    data[0][0] = 1.0f;
    data[1][1] = 1.0f;
    data[2][2] = 1.0f;
    data[3][3] = 1.0f;
}

void Matrix::setTranslation(float x, float y, float z) {
    Matrix temp;
    temp.setIdentity();
    temp.data[3][0] = x;
    temp.data[3][1] = y;
    temp.data[3][2] = z;

//    data[3][0] = x;
//    data[3][1] = y;
//    data[3][2] = z;
    multiply(temp);
}

void Matrix::setRotationX(float angle) {
    Matrix temp;
    temp.setIdentity();
    float cosVal = cos(angle * PI / 180.0);
    float sinVal = sin(angle * PI / 180.0);
    temp.data[1][1] = cosVal;
    temp.data[1][2] = -sinVal;
    temp.data[2][1] = sinVal;
    temp.data[2][2] = cosVal;
    multiply(temp);
}

void Matrix::setRotationY(float angle) {
    Matrix temp;
    temp.setIdentity();
    float cosVal = cosf(angle);
    float sinVal = sinf(angle);
    temp.data[0][0] = cosVal;
    temp.data[0][2] = sinVal;
    temp.data[2][0] = -sinVal;
    temp.data[2][2] = cosVal;
    multiply(temp);
}

void Matrix::setRotationZ(float angle) {
    Matrix temp;
    temp.setIdentity();
    float cosVal = cosf(angle);
    float sinVal = sinf(angle);
    temp.data[0][0] = cosVal;
    temp.data[0][1] = -sinVal;
    temp.data[1][0] = sinVal;
    temp.data[1][1] = cosVal;
    multiply(temp);
}

void Matrix::setScale(float scaleX, float scaleY, float scaleZ) {
    Matrix temp;
    temp.setIdentity();
    temp.data[0][0] = scaleX;
    temp.data[1][1] = scaleY;
    temp.data[2][2] = scaleZ;
    multiply(temp);
}

void Matrix::multiply(Matrix& matrix) {
    Matrix result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                result.data[i][j] += data[i][k] * matrix.data[k][j];
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                data[i][j] = result.data[i][j];
            }
        }
    }
}

void Matrix::values()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            std::cout << data[j][i] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void Matrix::setPoints(Punkt &p)
{
    data[0][0] = p.x;
    data[0][1] = p.y;
    data[0][2] = p.z;
    data[0][3] = p.w;
}

Punkt Matrix::multiply(Punkt &p)
{
    Punkt temp;
    temp.x = data[0][0] * p.x + data[0][1] * p.y + data[0][2] * p.z + data[0][3]*p.w;
    temp.y = data[1][0] * p.x + data[1][1] * p.y + data[1][2] * p.z + data[1][3]*p.w;
    temp.z = data[2][0] * p.x + data[2][1] * p.y + data[2][2] * p.z + data[2][3]*p.w;
    temp.w = data[3][0] * p.x + data[3][1] * p.y + data[3][2] * p.z + data[3][3]*p.w;
    return temp;
}

MyWindow::MyWindow(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    setWindowTitle("Rysowanie pikseli w Qt");

    resize(800,700);

    szer = 600;
    wys = 480;
    poczX = 25;
    poczY = 25;

    screen = new QImage(szer,wys,QImage::Format_RGB32);
    orig = new QImage(szer,wys,QImage::Format_RGB32);

    grupa = new QGroupBox("Sterowanie",this);

    grupa->setGeometry(QRect(poczX+szer+poczX,poczY,800-szer-2*poczX,poczY+400));

    QVBoxLayout *boxLayout = new QVBoxLayout;

    translationX = new QLabel("Translation X:", this);
    translationY = new QLabel("Translation Y:", this);
    translationZ = new QLabel("Translation Z:", this);
    rotationX = new QLabel("Rotation X:", this);
    rotationY = new QLabel("Rotation Y:", this);
    rotationZ = new QLabel("Rotation Z:", this);
    scalingX = new QLabel("Scaling X:", this);
    scalingY = new QLabel("Scaling Y:", this);
    scalingZ = new QLabel("Scaling Z:", this);

    StranslationX = new QSlider(Qt::Horizontal);
    StranslationX->setRange(-100, 100);
    StranslationX->setValue(0);

    StranslationY = new QSlider(Qt::Horizontal);
    StranslationY->setRange(-100, 100);
    StranslationY->setValue(0);

    StranslationZ = new QSlider(Qt::Horizontal);
    StranslationZ->setRange(-100, 100);
    StranslationZ->setValue(0);

    SrotationX = new QSlider(Qt::Horizontal);
    SrotationX->setRange(0, 360);
    SrotationX->setValue(0);

    SrotationY = new QSlider(Qt::Horizontal);
    SrotationY->setRange(0, 360);
    SrotationY->setValue(0);

    SrotationZ = new QSlider(Qt::Horizontal);
    SrotationZ->setRange(0, 360);
    SrotationZ->setValue(0);

    SscalingX = new QSlider(Qt::Horizontal);
    SscalingX->setRange(-100, 100);
    SscalingX->setValue(0);

    SscalingY = new QSlider(Qt::Horizontal);
    SscalingY->setRange(-100, 100);
    SscalingY->setValue(0);

    SscalingZ = new QSlider(Qt::Horizontal);
    SscalingZ->setRange(-100, 100);
    SscalingZ->setValue(0);

    boxLayout->addWidget(translationX);
    boxLayout->addWidget(StranslationX);

    boxLayout->addWidget(translationY);
    boxLayout->addWidget(StranslationY);

    boxLayout->addWidget(translationZ);
    boxLayout->addWidget(StranslationZ);

    boxLayout->addWidget(rotationX);
    boxLayout->addWidget(SrotationX);

    boxLayout->addWidget(rotationY);
    boxLayout->addWidget(SrotationY);

    boxLayout->addWidget(rotationZ);
    boxLayout->addWidget(SrotationZ);

    boxLayout->addWidget(scalingX);
    boxLayout->addWidget(SscalingX);

    boxLayout->addWidget(scalingY);
    boxLayout->addWidget(SscalingY);

    boxLayout->addWidget(scalingZ);
    boxLayout->addWidget(SscalingZ);

    grupa->setLayout(boxLayout);

    connect(StranslationX, SIGNAL(valueChanged(int)), this, SLOT(slot_translationX(int)));
    connect(StranslationY, SIGNAL(valueChanged(int)), this, SLOT(slot_translationY(int)));
    connect(StranslationZ, SIGNAL(valueChanged(int)), this, SLOT(slot_translationZ(int)));
    connect(SrotationX, SIGNAL(valueChanged(int)), this, SLOT(slot_rotationX(int)));
    connect(SrotationY, SIGNAL(valueChanged(int)), this, SLOT(slot_rotationY(int)));
    connect(SrotationZ, SIGNAL(valueChanged(int)), this, SLOT(slot_rotationY(int)));
    connect(SscalingX, SIGNAL(valueChanged(int)), this, SLOT(slot_scalingX(int)));
    connect(SscalingY, SIGNAL(valueChanged(int)), this, SLOT(slot_scalingY(int)));
    connect(SscalingZ, SIGNAL(valueChanged(int)), this, SLOT(slot_scalingY(int)));

    VtranslationX= 0;
    VtranslationY= 0;
    VtranslationZ= 0;
    VrotationX= 0;
    VrotationY= 0;
    VrotationZ= 0;
    VscalingX= 0;
    VscalingY= 0;
    VscalingZ= 0;

    int r = 50;
    makeCube(r);
    drawCube();

}

MyWindow::~MyWindow()
{
    delete screen;
    delete orig;
}

void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    p.drawImage(poczX,poczY,*screen);
}

void MyWindow::mousePressEvent(QMouseEvent *event)
{

}

void MyWindow::mouseReleaseEvent(QMouseEvent *event)
{

}

void MyWindow::mouseMoveEvent(QMouseEvent *event)
{

}

void MyWindow::setPixelColor(int x, int y, int color[3])
{
    if (x >= 0 && x <= szer && y >= 0 && y <= wys) {
        unsigned char *ptr = screen->bits();
        int temp = 4 * screen->width() * y + 4 * x;
        ptr[temp] = color[0];
        ptr[temp + 1] = color[1];
        ptr[temp + 2] = color[2];
    }
}

void MyWindow::copy() {
    unsigned char *origPtr = orig->bits();
    unsigned char *screenPtr = screen->bits();
    int imageSize = orig->width() * orig->height() * 4;

    for (int i = 0; i < imageSize; i++) {
        screenPtr[i] = origPtr[i];
    }
}

void MyWindow::czysc() {
    unsigned char *screenPtr = screen->bits();
    int imageSize = wys * szer * 4;

    for (int i = 0; i < imageSize; i++) {
        screenPtr[i] = 0;
    }
}

void MyWindow::drawLine(Punkt p1,Punkt p2)
{
    int iterX = (p1.x>p2.x) ? -1 : 1;
    int iterY = (p1.y>p2.y) ? -1 : 1;

    if(p1.x == p2.x)
    {
        for(int currY = p1.y; currY != p2.y; currY+=iterY)
        {
            Punkt loop = Punkt(p1.x,currY);
            setPixelColor(loop.x,loop.y,red);
        }

        return;
    }

    float r1 = p1.y - p2.y;
    float r2 = p1.x - p2.x;

    float a = r1/r2;
    float b = p1.y - a*p1.x;

    if(std::abs(a)<=1)
    {
        for(int currX = p1.x ; currX != p2.x ; currX+=iterX)
        {
            int nowyY = (a*currX+b);
            Punkt curr = Punkt(currX,nowyY);
            setPixelColor(curr.x,curr.y,red);
        }
    }
    else
    {
        for(int currY = p1.y ; currY != p2.y; currY+=iterY)
        {
            float n1 = (currY - b);
            int nowyX = n1/a;
            Punkt curr = Punkt(nowyX,currY);
            setPixelColor(curr.x,curr.y,red);
        }
    }

}

void MyWindow::makeCube(int r)
{
    int centerX = 0;
    int centerY = 0;

    Matrix cubeTransformated[8];

    cubeTransformated[0].setTranslation(centerX-r,centerY-r,r); //lgf
    cubeTransformated[1].setTranslation(centerX+r,centerY-r,r); //pgf
    cubeTransformated[2].setTranslation(centerX+r,centerY+r,r); //pdf
    cubeTransformated[3].setTranslation(centerX-r,centerY+r,r); //ldf
    cubeTransformated[4].setTranslation(centerX-r,centerY-r,r); //lgb
    cubeTransformated[5].setTranslation(centerX+r,centerY-r,r); //pgb
    cubeTransformated[6].setTranslation(centerX+r,centerY+r,r); //pdb
    cubeTransformated[7].setTranslation(centerX-r,centerY+r,r); //ldb

    for(int i=0;i<8;i++)
    {
        float x = cubeTransformated[i].data[3][0];
        float y = cubeTransformated[i].data[3][1];
        float z = cubeTransformated[i].data[3][2];
        float w = cubeTransformated[i].data[3][3];

        cubePoints[i].x = x;
        cubePoints[i].y = y;
        cubePoints[i].z = z;
        cubePoints[i].w = w;

        cubePointsT[i].x = cubePoints[i].x;
        cubePointsT[i].y = cubePoints[i].y;
        cubePointsT[i].z = cubePoints[i].z;
        cubePointsT[i].w = cubePoints[i].w;
    }
}

void MyWindow::drawCube()
{
    Punkt p1;
    Punkt p2;
    //sciana przednia
    p1 = cubePointsT[0];
    p2 = cubePointsT[1];
    drawLine(p1,p2);

    p1 = cubePointsT[1];
    p2 = cubePointsT[2];
    drawLine(p1,p2);


    p1 = cubePointsT[2];
    p2 = cubePointsT[3];
    drawLine(p1,p2);

    p1 = cubePointsT[3];
    p2 = cubePointsT[0];
    drawLine(p1,p2);
    //sciana tylnia
    p1 = cubePointsT[4];
    p2 = cubePointsT[5];
    drawLine(p1,p2);

    p1 = cubePointsT[5];
    p2 = cubePointsT[6];
    drawLine(p1,p2);


    p1 = cubePointsT[6];
    p2 = cubePointsT[7];
    drawLine(p1,p2);

    p1 = cubePointsT[7];
    p2 = cubePointsT[4];
    drawLine(p1,p2);

    //Laczenie scian
    p1 = cubePointsT[0];
    p2 = cubePointsT[4];
    drawLine(p1,p2);

    p1 = cubePointsT[1];
    p2 = cubePointsT[5];
    drawLine(p1,p2);

    p1 = cubePointsT[2];
    p2 = cubePointsT[6];
    drawLine(p1,p2);

    p1 = cubePointsT[3];
    p2 = cubePointsT[7];
    drawLine(p1,p2);
}

void MyWindow::przeksztalc()
{
    czysc();
    Matrix transformations;
//    transformations.setPoints()
    transformations.setTranslation(VtranslationX,VtranslationY,VtranslationZ);
//    transformations.values();

    for(int i=0;i<8;i++)
    {
        cubePointsT[i] = transformations.multiply(cubePoints[i]);

    }

    drawCube();
    update();
}

void MyWindow::slot_translationX(int value)
{
    VtranslationX = value;
    czysc();
    przeksztalc();
    update();
}

void MyWindow::slot_translationY(int value)
{
    VtranslationY = value;
    czysc();
    przeksztalc();
    update();
}

void MyWindow::slot_translationZ(int value)
{
    VtranslationZ = value;
    czysc();
    przeksztalc();
    update();
}

void MyWindow::slot_rotationX(int value)
{
    VrotationX = value;
    czysc();
    przeksztalc();
    update();
}

void MyWindow::slot_rotationY(int value)
{
    VrotationY = value;
    czysc();
    przeksztalc();
    update();
}

void MyWindow::slot_rotationZ(int value)
{
    VrotationZ = value;
    czysc();
    przeksztalc();
    update();
}

void MyWindow::slot_scalingX(int value)
{
    VscalingX = value;
    czysc();
    VscalingX = (VscalingX / (float)100)+1;
    przeksztalc();
    update();
}

void MyWindow::slot_scalingY(int value)
{
    VscalingY = value;
    czysc();
    VscalingY = VscalingY / (float)100;
    przeksztalc();
    update();
}

void MyWindow::slot_scalingZ(int value)
{
    VscalingZ = value;
    czysc();
    VscalingZ = VscalingY / (float)100;
    przeksztalc();
    update();
}
