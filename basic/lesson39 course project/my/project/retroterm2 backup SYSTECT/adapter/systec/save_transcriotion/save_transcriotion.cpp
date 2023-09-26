#include "save_transcriotion.h"

save_transcriotion::save_transcriotion()
{
//	file_log.setFileName("all read.txt");
//	file_log.open(QIODevice::WriteOnly);
//	stream.setDevice(&file_log);
}

void save_transcriotion::appened(const save_array &buf)
{
	QMutexLocker loc(&mut);
//	qDebug()  << "global buf appened" << buf.byte_in_string();
//	stream << buf.byte_in_string() << "\n";
	array.append(buf);
}

save_array save_transcriotion::mid(unsigned start, unsigned k)
{
	QMutexLocker loc(&mut);
	auto temp = array.mid(start, k);
	array = array.mid(k);
	return temp;
}

void save_transcriotion::clear()
{
	QMutexLocker loc(&mut);
	array.clear();
}

save_array save_transcriotion::read_all()
{
	QMutexLocker loc(&mut);
	auto temp = array;
	array.clear();
	return temp;
}

uchar *save_transcriotion::begin()
{
	QMutexLocker loc(&mut);
	return array.begin();
}

uchar *save_transcriotion::find(const save_array &f)
{
	QMutexLocker loc(&mut);
	return array.find(f);
}
