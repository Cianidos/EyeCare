// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "LookAtSides.h"

#include <utility>

LookAtSides::LookAtSides(DataAnalyzer& analyzer, ActionSequence sequence, QWidget* parent)
	:
QWidget(parent),
analyzer_(analyzer),
actions_(std::move(sequence)),
current_action_(std::begin(actions_))
{
	ui.setupUi(this);

	timer_ = std::make_unique<QTimer>();
	timer_->setInterval(64);
	connect(timer_.get(), &QTimer::timeout, this, &LookAtSides::update_);
	timer_->start();

	machine_ = std::make_unique<QStateMachine>();

	auto* init = new QState();
	auto* take_action = new QState(init);
	auto* wait_action = new QState(init);
	auto* making_action = new QState(init);
	auto* done_action = new QState(init);
	auto* exercises_ends = new QState();

	take_action->addTransition(timer_.get(), &QTimer::timeout, wait_action);
	wait_action->addTransition(this, &LookAtSides::action_starts, making_action);
	making_action->addTransition(this, &LookAtSides::action_terminated, wait_action);
	making_action->addTransition(this, &LookAtSides::action_over, done_action);
	done_action->addTransition(timer_.get(), &QTimer::timeout, take_action);
	init->addTransition(this, &LookAtSides::mission_complete, exercises_ends);

	connect(take_action, &QState::entered, this, &LookAtSides::next_action);
	connect(making_action, &QState::entered, this, &LookAtSides::reset_timer);

	init->setInitialState(take_action);

	machine_->addState(init);
	machine_->addState(exercises_ends);

	machine_->setInitialState(init);

	machine_->start();
}

LookAtSides::~LookAtSides()
{
}

void LookAtSides::update_()
{
	auto state = analyzer_.get_eyes_state();
	auto& act = *current_action_;

	ui.label->setText({ to_string(state).c_str() });
	ui.label_2->setText({ to_string(act.expected).c_str() });
	


	if ((static_cast<int>(state) & static_cast<int>(act.expected)) 
		&& (clock_::now() - start_ > act.continues))
	{
		action_starts();
	}
	else
	{
		action_terminated();
	}

	if (clock_::now() - start_ >= act.continues)
	{
		action_over();
	}
}


void LookAtSides::next_action()
{
	++current_action_;
	if (current_action_ == std::end(actions_))
	{
		mission_complete();
	}
}


void LookAtSides::reset_timer()
{
	start_ = clock_::now();
}

