// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include "ShortClose.h"


ShortClose::ShortClose(DataAnalyzer& analyzer, int counter_limit, std::chrono::milliseconds duration, QWidget* parent)
	: 
	counter_limit_(counter_limit),
	closing_time(duration),
	QWidget(parent),
	analyzer_(analyzer)
{
	setWindowFlags(Qt::Dialog);
	ui.setupUi(this);
	timer_ = std::make_unique<QTimer>();
	timer_->setInterval(3);
	connect(timer_.get(), &QTimer::timeout, this, &ShortClose::update_);
	timer_->start();


	training_machine_ = std::make_unique<QStateMachine>();

	auto* init = new QState();
	auto* closing = new QState(init);
	auto* closed = new QState(init);
	auto* post_closed = new QState(init);
	auto* opening = new QState(init);
	auto* opened = new QState(init);
	auto* end = new QFinalState();

	init->setInitialState(opened);

	opened->addTransition(this, &ShortClose::eyes_closed, closing);
	closing->addTransition(this, &ShortClose::eyes_closing_long, closed);
	closing->addTransition(this, &ShortClose::eyes_opened, opened);
	closed->addTransition(timer_.get(), &QTimer::timeout, post_closed);
	post_closed->addTransition(this, &ShortClose::eyes_opened, opening);
	opening->addTransition(this, &ShortClose::eyes_closed, post_closed);
	opening->addTransition(this, &ShortClose::eyes_opening_long, opened);

	init->assignProperty(ui.state_lable, "text", "init");
	opened->assignProperty(ui.state_lable, "text", "opened");
	opening->assignProperty(ui.state_lable, "text", "opening");
	closed->assignProperty(ui.state_lable, "text", "closed");
	closing->assignProperty(ui.state_lable, "text", "closing");
	post_closed->assignProperty(ui.state_lable, "text", "post_closed");

	connect(opening, &QState::entered, this, &ShortClose::init_start);
	connect(closing, &QState::entered, this, &ShortClose::init_start);
	connect(closed, &QState::entered, this, &ShortClose::increment_counter);
	
	init->addTransition(this, &ShortClose::task_end, end);

	training_machine_->addState(init);
	training_machine_->addState(end);
	training_machine_->setInitialState(init);
	connect(training_machine_.get(), &QStateMachine::finished, this, &ShortClose::close);

	training_machine_->start();
	
	showFullScreen();
}


ShortClose::~ShortClose()
{
}


void ShortClose::update_()
{
	
	ui.label->setFixedSize(analyzer_.idc_.img_qsize());
	ui.label->setPixmap(QPixmap::fromImage(analyzer_.idc_.get_image()));
	auto [l, r] = analyzer_.eyes_opened();
	l = l & r;

	auto now = std::chrono::system_clock::now();

	if (l)
	{
		eyes_opened();
		if ((now - start) > opening_time)
		{
			eyes_opening_long();
		}
	}
	else
	{
		eyes_closed();
		if ((now - start) > closing_time)
		{
			eyes_closing_long();
		}
	}

	if (counter_ >= counter_limit_)
	{
		task_end();
	}

	ui.counter->setText(QString::number(counter_));
}


void ShortClose::increment_counter()
{
	counter_++;
}


void ShortClose::init_start()
{
	start = std::chrono::system_clock::now();
}


