#pragma once

#include <QWidget>
#include "ui_LookAtSides.h"

#include "DataAnalyzer.h"
#include "Exercise.h"

#include <QTimer>
#include <QState>
#include <QFinalState>
#include <QStateMachine>


class LookAtSides : public QWidget
{
	Q_OBJECT

public:
	using Action = Exercise;
	using ActionSequence = std::vector<Action>;

	LookAtSides(DataAnalyzer& analyzer, ActionSequence sequence, QWidget *parent = Q_NULLPTR);
	~LookAtSides();

signals:
	void action_starts();
	void action_terminated();
	void action_over();
	void mission_complete();

public slots:
	void update_();
	void next_action();
	void reset_timer();
	

private:
	using clock_ = std::chrono::system_clock;
	Ui::LookAtSides ui;
	std::unique_ptr<QTimer> timer_;
	std::unique_ptr<QStateMachine> machine_;

	DataAnalyzer& analyzer_;

	ActionSequence actions_;
	ActionSequence::iterator current_action_;

	std::chrono::time_point<clock_> start_;
};
