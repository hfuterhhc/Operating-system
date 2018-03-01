#include "widget.h"
#include "ui_widget.h"
#include "test.h"
#include "hhc.h"
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *){

    QPainter p;
    p.begin(this);
    p.drawPixmap(0,0,width(),height(),QPixmap("/home/hhc/QT/test.jpg"));
    p.end();

}

// 信号与槽机制
void Widget::on_pushButton_1_clicked()
{
    test test1;
    int N1,N2,T1,T2;
    test1.config(&N1,&N2,&T1,&T2);
    gettimeofday(&start,NULL);
    f1(N1,N2,T1,T2,(void*)product,(void*)consumer);
}

void Widget::on_pushButton_2_clicked()
{
    test test1;
    int N1,N2,T1,T2;
    test1.config(&N1,&N2,&T1,&T2);
    gettimeofday(&start,NULL);
    f2(N1,N2,T1,T2,(void*)product1,(void*)consumer1);
}

void Widget::on_pushButton_3_clicked()
{
    test test1;
    int N1,N2,T1,T2;
    test1.config(&N1,&N2,&T1,&T2);
    gettimeofday(&start,NULL);
    f2(1,1,T1,T2,(void*)product1,(void*)consumer1);
}

void Widget::on_pushButton_4_clicked()
{
    test test1;
    int N1,N2,T1,T2;
    test1.config(&N1,&N2,&T1,&T2);
    gettimeofday(&start,NULL);
    f1(1,1,T1,T2,(void*)product,(void*)consumer);
}

void Widget::on_pushButton_5_clicked()
{
    test test1;
    int N1,N2,T1,T2;
    test1.config(&N1,&N2,&T1,&T2);
    gettimeofday(&start,NULL);
    f1(1,N2,T1,T2,(void*)product,(void*)consumer);
}

void Widget::on_pushButton_6_clicked()
{
    test test1;
    int N1,N2,T1,T2;
    test1.config(&N1,&N2,&T1,&T2);
    gettimeofday(&start,NULL);
    f2(1,N2,T1,T2,(void*)product1,(void*)consumer1);
}

void Widget::on_pushButton_7_clicked()
{
    test test1;
    int N1,N2,T1,T2;
    test1.config(&N1,&N2,&T1,&T2);
    gettimeofday(&start,NULL);
    f1(N1,1,T1,T2,(void*)product,(void*)consumer);
}

void Widget::on_pushButton_8_clicked()
{
    test test1;
    int N1,N2,T1,T2;
    test1.config(&N1,&N2,&T1,&T2);
    gettimeofday(&start,NULL);
    f2(N1,1,T1,T2,(void*)product1,(void*)consumer1);
}



