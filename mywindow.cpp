#include "mywindow.h"
#include <QLabel>
#include <QVBoxLayout>
#define PI 3.14159265
Punkt::~Punkt(){}

Punkt::Punkt(Punkt &p)
{
    x = p.x;
    y = p.y;
    z = p.z;
    w = p.w;
}

void Punkt::operator=(Punkt p)
{
    x = p.x;
    y = p.y;
    z = p.z;
    w = p.w;
}

void Punkt::values()
{
    std::cout<<"x: "<<x<<" y: "<<y<<" z: "<<z<<" w: "<<w<<std::endl;
}

int Punkt::dot(Punkt p)
{
     return x * p.x + y * p.y + z * p.z;
}

Matrix::Matrix() {
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            data[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

}

void Matrix::setTranslation(float x, float y, float z) {
    Matrix temp;
    temp.data[0][3] = x;
    temp.data[1][3] = y;
    temp.data[2][3] = z;
    multiply(temp);
}

void Matrix::setRotationX(float angle) {
    Matrix temp;
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
    temp.data[0][0] = scaleX+1;
    temp.data[1][1] = scaleY+1;
    temp.data[2][2] = scaleZ+1;
    temp.data[3][3] = 1;
    multiply(temp);
}

void Matrix::multiply(Matrix& matrix) {
    Matrix result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.data[i][j] = 0;
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

Punkt Matrix::operator*(Punkt &p)
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
    QString path = "C:/Users/Kuba/Desktop/grafika/trzyDe_oswietlenie/img2.png";
    texture = new QImage(path);

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
    SscalingX->setRange(0, 100);
    SscalingX->setValue(0);

    SscalingY = new QSlider(Qt::Horizontal);
    SscalingY->setRange(0, 100);
    SscalingY->setValue(0);

    SscalingZ = new QSlider(Qt::Horizontal);
    SscalingZ->setRange(0, 100);
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
    connect(SrotationZ, SIGNAL(valueChanged(int)), this, SLOT(slot_rotationZ(int)));
    connect(SscalingX, SIGNAL(valueChanged(int)), this, SLOT(slot_scalingX(int)));
    connect(SscalingY, SIGNAL(valueChanged(int)), this, SLOT(slot_scalingY(int)));
    connect(SscalingZ, SIGNAL(valueChanged(int)), this, SLOT(slot_scalingZ(int)));

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
    delete texture;
}

void MyWindow::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    p.drawImage(poczX,poczY,*screen);
//    p.drawImage(poczX,poczY,*texture);
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

std::array<int, 3> MyWindow::getPixelColor(Punkt p1)
{
    unsigned char *ptr = texture->bits();

    return {
        ptr[texture->width()*4*p1.y + 4*p1.x],
        ptr[texture->width()*4*p1.y + 4*p1.x + 1],
        ptr[texture->width()*4*p1.y + 4*p1.x + 2]
    };
}

void MyWindow::setPixelColor(int x, int y, std::array<int, 3> color)
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
    unsigned char *origPtr = texture->bits();
    unsigned char *screenPtr = screen->bits();
    int imageSize = texture->width() * texture->height() * 4;

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

    cubePoints[0] = Punkt(centerX-r,centerY-r,r); //lgf
    cubePoints[1] = Punkt(centerX+r,centerY-r,r); //pgf
    cubePoints[2] = Punkt(centerX+r,centerY+r,r); //pdf
    cubePoints[3] = Punkt(centerX-r,centerY+r,r); //ldf
    cubePoints[4] = Punkt(centerX-r,centerY-r,-r); //lgb
    cubePoints[5] = Punkt(centerX+r,centerY-r,-r); //pgb
    cubePoints[6] = Punkt(centerX+r,centerY+r,-r); //pdb
    cubePoints[7] = Punkt(centerX-r,centerY+r,-r); //ldb

    for(int i=0;i<8;i++)
    {
        cubePointsT[i] = cubePoints[i];
    }
}

void MyWindow::barycentric( Punkt& P,  Punkt& A,  Punkt& B,  Punkt& C, float &u, float &v, float &w) {
    Punkt v0 = {B.x - A.x, B.y - A.y};
    Punkt v1 = {C.x - A.x, C.y - A.y};
    Punkt v2 = {P.x - A.x, P.y - A.y};
    float d00 = v0.x * v0.x + v0.y * v0.y;
    float d01 = v0.x * v1.x + v0.y * v1.y;
    float d11 = v1.x * v1.x + v1.y * v1.y;
    float d20 = v2.x * v0.x + v2.y * v0.y;
    float d21 = v2.x * v1.x + v2.y * v1.y;
    float denom = d00 * d11 - d01 * d01;
    v = (d11 * d20 - d01 * d21) / denom;
    w = (d00 * d21 - d01 * d20) / denom;
    u = 1.0f - v - w;
}

void MyWindow::mapTextureFromTriangleToTriangle(Punkt& A,  Punkt& B,  Punkt& C, Punkt& At,  Punkt& Bt,  Punkt& Ct) {
    for (int y = 0; y < 600; ++y) {
        for (int x = 0; x < 600; ++x) {
            Punkt P = Punkt(x,y);
            float u, v, w;
            barycentric(P, A, B, C, u, v, w);
            if (u >= 0 && v >= 0 && w >= 0) {  // Punkt P leży wewnątrz trójkąta ABC
                Punkt Pt = Punkt(
                    At.x * u + Bt.x * v + Ct.x * w,
                    At.y * u + Bt.y * v + Ct.y * w);
                std::array<int,3> color = getPixelColor(Pt);
                setPixelColor(x, y, color);
            }
        }
    }
}

void MyWindow::drawCube()
{
    Punkt viewDirection = {0, 0, 1};

    int faces[6][4] = {
        {0, 1, 2, 3},
        {4, 7, 6, 5},
        {0, 4, 5, 1},
        {3, 2, 6, 7},
        {0, 3, 7, 4},
        {1, 5, 6, 2}
    };



    for (int i = 0; i < 6; i++) {
        Punkt p1 = cubePointsT[faces[i][0]];
        Punkt p2 = cubePointsT[faces[i][1]];
        Punkt p3 = cubePointsT[faces[i][2]];

        Punkt edge1 = {p2.x - p1.x, p2.y - p1.y, p2.z - p1.z};
        Punkt edge2 = {p3.x - p1.x, p3.y - p1.y, p3.z - p1.z};
        Punkt normal;
        normal.x = edge1.y * edge2.z - edge1.z * edge2.y;
        normal.y = edge1.z * edge2.x - edge1.x * edge2.z;
        normal.z = edge1.x * edge2.y - edge1.y * edge2.x;

        if (normal.dot(viewDirection) < 0) {
            for (int j = 0; j < 4; j++) {
                Punkt start = cubePointsT[faces[i][j]];
                Punkt end = cubePointsT[faces[i][(j+1)%4]];
                drawLine(start, end);

            }
            Punkt t1Start = cubePointsT[faces[i][0]];
            Punkt t1Prosty = cubePointsT[faces[i][1]];
            Punkt t1End = cubePointsT[faces[i][2]];
            drawLine(t1Start, t1End);

            Punkt txt1Start = Punkt(0,0);
            Punkt txt1Prosty = Punkt(texture->width(),0);
            Punkt txt1End = Punkt(0,texture->height());

            Punkt t2Start = cubePointsT[faces[i][0]];
            Punkt t2Prosty = cubePointsT[faces[i][3]];
            Punkt t2End = cubePointsT[faces[i][2]];
            drawLine(t2Start, t2End);

            Punkt txt2Start = Punkt(texture->width(),texture->height());
            Punkt txt2Prosty = Punkt(0,0);
            Punkt txt2End = Punkt(0,texture->height());

            mapTextureFromTriangleToTriangle(t1End,t1Start,t1Prosty,txt2Start,txt2Prosty,txt2End);

            mapTextureFromTriangleToTriangle(t2End,t2Start,t2Prosty,txt1Prosty,txt1Start,txt1End);
        }
    }
}

void MyWindow::przeksztalc()
{
    int d = 400;
    tMatrix.setTranslation(300,240,0);
    tMatrix.setRotationX(VrotationX);
    tMatrix.setRotationY(VrotationY);
    tMatrix.setRotationZ(VrotationZ);
    tMatrix.setScale(VscalingX/20,VscalingY/20,VscalingZ/20);
    tMatrix.setTranslation(VtranslationX,VtranslationY,VtranslationZ);
    tMatrix.values();

    for(int i=0;i<8;i++)
    {
        cubePointsT[i].x = tMatrix.data[0][0] * cubePoints[i].x + tMatrix.data[0][1] * cubePoints[i].y + tMatrix.data[0][2] * cubePoints[i].z + tMatrix.data[0][3];
        cubePointsT[i].y = tMatrix.data[1][0] * cubePoints[i].x + tMatrix.data[1][1] * cubePoints[i].y + tMatrix.data[1][2] * cubePoints[i].z + tMatrix.data[1][3];
        cubePointsT[i].z = tMatrix.data[2][0] * cubePoints[i].x + tMatrix.data[2][1] * cubePoints[i].y + tMatrix.data[2][2] * cubePoints[i].z + tMatrix.data[2][3];
        cubePointsT[i].x = (float) cubePointsT[i].x * d/(cubePointsT[i].z+d);
        cubePointsT[i].y = (float) cubePointsT[i].y * d/(cubePointsT[i].z+d);
        cubePointsT[i].z = 0;
    }
    drawCube();
    update();
    tMatrix = Matrix();
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
    przeksztalc();
    update();
}

void MyWindow::slot_scalingY(int value)
{
    VscalingY = value;
    czysc();
    przeksztalc();
    update();
}

void MyWindow::slot_scalingZ(int value)
{
    VscalingZ = value;
    czysc();
    przeksztalc();
    update();
}
