#include "map.h"
#include "ui_map.h"

Map::Map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);

    XOffset = 0;
    YOffset = 0;
    LastXPos = 0;
    LastYPos = 0;

    Path.moveTo(this->geometry().width()/2, this->geometry().height()/2);

    Tim = new QTimer;
    connect(Tim, &QTimer::timeout, this, &Map::CallRepaint);
    connect(ui->ResetButton, &QAbstractButton::clicked, this, &Map::ClearMap);
    Tim->start(10);
}

Map::~Map()
{
    delete Tim;
    delete ui;
}

void Map::AddPoint(double X, double Y){
    LastPoint = QPoint(this->geometry().width()/2+X+XOffset, this->geometry().height()/2-Y+YOffset);
    Path.lineTo(LastPoint);
    LastXPos = X;
    LastYPos = Y;
}

void Map::paintEvent(QPaintEvent *){
    QPainter Painter(this);
    QPen Pen(Qt::blue, 10, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    Painter.setPen(Pen);
    Painter.drawPath(Path);
    Pen.setColor(Qt::red);
    Pen.setWidth(20);
    Painter.setPen(Pen);
    Painter.drawPoint(LastPoint);
}

void Map::CallRepaint(){
    repaint();
}

void Map::ClearMap(){
    XOffset = -LastXPos;
    YOffset = LastYPos;
    Path = QPainterPath(QPoint(this->geometry().width()/2, this->geometry().height()/2));
}
