#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>

#include "ui_MainWindow.h"
#include <opencv2/core.hpp>

#include "ShortClose.h"
#include "Camera.h"
#include "DataAnalyzer.h"
#include "FaceClassifier.h"
#include "EyeRegions.h"
#include "EyeClassifier.h"
#include "ImageDataCollector.h"
#include "PupilDetector.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

public slots:
    void update_cap();
    void task1_clicked();
    void continuous_close_clicked();
    void sides_clicked();
	
private:
    ImageDataCollector collector_;
    DataAnalyzer analyzer_;

    std::unique_ptr<QTimer> timer_;
    Ui::MainWindowClass ui_;
    std::unique_ptr<QWidget> task_;
};

