#pragma once

#include "save_array.h"
#include <QMutexLocker>

class save_transcriotion
{
public:
	save_transcriotion();
public:
	 unsigned size() const {return array.size_array();}
	 void appened(const save_array &buf);
	 save_array mid(unsigned start = 0, unsigned k = 0);
	 void clear();
	 save_array read_all();
	 uchar *begin();
	 uchar *find(const save_array &f);
private:
	save_array array;
	QMutex mut;
//	QFile file_log;
//	 QTextStream stream;
};
