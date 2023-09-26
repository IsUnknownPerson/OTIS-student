#pragma once

#include <QtCore>
#include <QList>
#include <cstring>
#include <iterator>
#define dop_size 20

class save_array
{
	using It=uchar*;
public:
	save_array(void *array, unsigned len);
	save_array(const char *array);
	save_array(const save_array &over);
	save_array(const QByteArray &over);
	save_array(std::initializer_list<int> init);

	save_array(It start, It end);
	save_array(save_array &&over);
	save_array();
	~save_array();
	void resize (unsigned size);
	save_array & operator = (const save_array &over);
	save_array & operator = (std::initializer_list<int> init);
	save_array & operator = (const QByteArray &init);
	save_array operator + (const save_array &over) const;
	save_array operator + (char c) const;
	save_array operator + (const char *c) const;

	save_array &operator += (save_array const &over);
	bool operator ==(const save_array &over) const;
	bool operator ==(std::initializer_list<int> init) const;
	bool operator !=(const save_array &over) const;
	uchar & operator [] (const unsigned i) const;
	uchar &last() const;
	unsigned size_array() const {return len; }
	unsigned size() const {return len;}
	uchar *u_data() const {return array;}
	char *data() const {return (char *)array;}
	char *c_data() const {return (char *)array;}
	save_array& append(char *array, unsigned len);
	save_array& append(void *array, unsigned len);
	save_array& append(char c);
	save_array& append(save_array const &over);
	save_array& append_s(short c);
	save_array& append_i(int c);
	save_array mid(unsigned start = 0, unsigned k = 0) const;
	void clear();
	save_array in_bit(unsigned start = 0, unsigned k = 0) const;
	QString	in_QString(unsigned start = 0, unsigned k = 0) const;
	QString byte_in_string(unsigned start = 0, unsigned k = 0) const;
	static unsigned short two_byte_in_short(const save_array &array, unsigned start = 0, bool flag = false);
	unsigned short two_byte_in_short(unsigned start = 0, bool flag = false) const;
	unsigned char bits_in_byte(unsigned start = 0, unsigned k = 0) const;
	unsigned int byte_in_int(unsigned start = 0, unsigned k = 4) const;
	QList<save_array> split_number(unsigned i = 0) const;
//	QList<save_array> split(uchar r) const;
	QList<save_array> split(const save_array &r) const;
	It begin() {return array;}
	It end() {return array + len;}
	It begin() const {return array;}
	It end() const {return array + len;}
	static uchar *find(It begin, It end, const save_array &f);
	uchar *find(const save_array &f) const;
	bool contains(const save_array &f) const;

//private :
//    save_array(char *array, unsigned len, bool flag);
	friend QDataStream &operator <<(QDataStream &stream, const save_array &array);
	friend QDataStream &operator >>(QDataStream &stream, save_array &array);
private:
	uchar		*array = nullptr;
	unsigned	len = 0;
	unsigned	max_size = 0;
};


Q_DECLARE_METATYPE(save_array)

save_array operator +(std::initializer_list<int> init , const save_array &second);
