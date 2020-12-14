// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "MainWindow.h"
#include <QObject>
#include <opencv2/highgui.hpp>

#include "LookAtSides.h"
#include "Exercise.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), collector_(ImageDataCollector()), analyzer_(DataAnalyzer(collector_))
{
    ui_.setupUi(this);
	
  
    timer_ = std::make_unique<QTimer>(this);
    connect(timer_.get(), &QTimer::timeout, this,  &MainWindow::update_cap);
    timer_->start(100);
}


const char* to_string(EyeSide e)
{
	switch (e)
	{
    case EyeSide::left: return "nalevo";
    case EyeSide::right: return "napravo";
    case EyeSide::up: return "vverh";
    case EyeSide::down: return "vniz";
    case EyeSide::vcenter: return "vcenter";
    case EyeSide::hcenter: return "hcenter";
	default: return "unknown";
	}
}


void MainWindow::update_cap()
{
    collector_.update();
    ui_.label_1->setFixedSize(collector_.img_qsize());
    ui_.label_1->setPixmap(QPixmap::fromImage(collector_.get_image()));

    std::string str;
    auto s = analyzer_.side_eyes_looks();
    for (const auto& i : s)
    {
        str.append(to_string(i)).append(" ");
    }
    ui_.label_2->setText(QString(str.c_str()));
    auto [a, b] = analyzer_.eyes_opened();
}


void MainWindow::task1_clicked()
{   
    task_ = std::make_unique<ShortClose>(analyzer_, 15, 30ms, this);
    task_->show();
}


void MainWindow::continuous_close_clicked()
{
    task_ = std::make_unique<ShortClose>(analyzer_, 5, 3000ms, this);
    task_->show();
}


void MainWindow::sides_clicked()
{
    task_ = std::make_unique<LookAtSides>(analyzer_, 
        LookAtSides::ActionSequence{ {
            {EState::left, 200ms},
            {EState::right, 200ms}
        } });
    task_->show();
}

