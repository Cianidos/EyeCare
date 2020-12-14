// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
#include <QtWidgets/QApplication>
#include <QGuiApplication>

#include "MainWindow.h"


int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	
	w.show();

	return a.exec();
}

