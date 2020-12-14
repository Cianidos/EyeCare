#pragma once


#include <QWidget>
#include "ui_ShortClose.h"

#include <QTimer>
#include <QStateMachine>
#include <QState>
#include <QFinalState>

#include "DataAnalyzer.h"

using namespace std;

class ShortClose : public QWidget
{
	Q_OBJECT

public:
	ShortClose(DataAnalyzer& analyzer, int counter_limit, std::chrono::milliseconds duration, QWidget* parent = Q_NULLPTR);
	~ShortClose();

signals:
	void eyes_closed();
	void eyes_closing_long();
	void eyes_opened();
	void eyes_opening_long();
	void task_end();


public slots:
	void update_();
	void increment_counter();
	void init_start();

	
private:
	int counter_ = 0;
	int counter_limit_ = 10;
	std::chrono::microseconds closing_time = 5000ms;
	std::chrono::milliseconds opening_time = 30ms;
	Ui::ShortClose ui{};
	std::chrono::time_point<std::chrono::system_clock> start;
	std::unique_ptr<QStateMachine> training_machine_;
	std::unique_ptr<QTimer> timer_;
	DataAnalyzer& analyzer_;
};
