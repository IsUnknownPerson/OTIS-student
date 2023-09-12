#include "save_array.h"

save_array ::save_array(void *array, unsigned len)
{
	max_size = dop_size + len;
	this->len = len;
	this->array = new uchar [max_size +1];
	memset(this->array, 0, max_size +1);
	memmove(this->array, array, len);
}

save_array::save_array(const char *array)
{
	max_size = dop_size + strlen(array);
	this->len = strlen(array);
	this->array = new uchar [max_size + 1];
	memset(this->array, 0, max_size + 1);
	memmove(this->array, array, this->len);
}

//save_array ::save_array(char *array, unsigned len, bool flag)
//{
//	max_size = len;
//	this->size = len;
//	if (flag)
//	{
//		this->array = array;
//		return;
//	}
//	this->array = new char [len + 1];
//	this->array[len] = 0;
//	memmove(this->array, array, len);
//}

save_array :: save_array(const save_array &over)
{
	max_size = over.max_size;
	array = new uchar [max_size +1];
	memset(array, 0, max_size +1);
	len = over.len;
	memmove(array, over.array, len);
}

save_array :: save_array(save_array &&over)
{
	max_size = over.max_size;
	array = over.array;
	len = over.len;

	over.len = 0;
	over.max_size = 0;
	over.array = nullptr;
//	memmove(array, over.array, len);
}

save_array :: save_array(const QByteArray &over)
{
	max_size = over.size() + dop_size;
	array = new uchar [max_size +1];
	memset(array, 0, max_size +1);
	len = over.size();
	memmove(array, over.data(), len);
}

save_array::save_array(std::initializer_list<int> init)
{
	auto n = init.begin();
	max_size = dop_size + init.size();
	array = new uchar [max_size + 1];
	memset(array, 0, max_size + 1);
	this->len = static_cast<unsigned>(init.size());
	unsigned i = 0;
	while (n != init.end())
	{
		array[i] = static_cast<char>(*n);
		++n;
		++i;
	}
}

save_array::save_array(It start, It end)
{
	*this = save_array(start, end - start);
}

save_array ::save_array()
{
	max_size = dop_size;
	array = new uchar [max_size + 1];
	memset(array, 0, max_size + 1);
	len = 0;
}

save_array :: ~save_array()
{
	delete []array;
	array = nullptr;
}

save_array & save_array :: append(char *array, unsigned int len)
{
	if (this->len + len < max_size)
	{
		memmove(this->array + this->len, array, len);
		this->len += len;
		return *this;
	}
	uchar	*temp = nullptr;
	auto	temp_size = this->len;
	auto	temp_max_size = max_size;
	this->len += len;
	max_size = this->len + dop_size;
	temp = new uchar [max_size +1];
	memset(temp, 0, max_size +1);
	memmove(temp, this->array, temp_size);
	memmove(temp + temp_size, array, len);
	if (temp_max_size)
		delete [] this->array;
	this->array = temp;
	return *this;
}

save_array &save_array::append(void *array, unsigned len)
{
	return append(static_cast<char *>(array), len);
}

save_array &save_array::append(char c)
{
	return append(&c, 1);
}

save_array &save_array::append(save_array const &over)
{
	return append(over.array, over.len);
}

save_array &save_array::append_s(short c)
{
	//unsigned char temp;
	unsigned char temp[2] = {static_cast<unsigned char>(c >> 8), static_cast<unsigned char>(c & 0xff)};
	return append(temp, 2);
}

save_array &save_array::append_i(int c)
{
	unsigned short temp;

	temp = static_cast<unsigned short>(c >> 16);
	append_s(static_cast<short>(temp));
	temp = (c & 0xffff);
	append_s(static_cast<short>(temp));
	return *this;
}

save_array save_array::operator +(const save_array &over) const
{
	auto	v = *this;
	v.append(over.array, over.len);
	return v;
}

save_array save_array::operator +(char c) const
{
	auto	v = *this;
	v.append(&c, 1);
	return v;
}

save_array save_array::operator +(const char *c) const
{
	auto	v = *this;
	v.append(c);
	return v;
}

//save_array save_array::operator +(std::initializer_list<int> init) const
//{
//	auto	v = *this;
//	save_array translate(init);
//	return v + init;
//}

save_array &save_array::operator +=(save_array const &over)
{
	append(over.array, over.len);
	return *this;
}

save_array &save_array::operator =(const save_array &over)
{
	if (array == over.array)
		return *this;
	if (this->max_size < over.len)
	{
		if (this->max_size)
			delete array;
		max_size = over.max_size;
		array = new uchar [max_size +1];
		this->len = over.len;
		memset(array, 0, max_size + 1);
		memmove(array, over.array, len);
		return *this;
	}
	this->len = over.len;
	memmove(array, over.array, len);
	memset(array + len, 0, this->max_size - len);
	return *this;

}

save_array &save_array::operator =(const QByteArray &init)
{
	return *this = save_array((void *)init.data(), (unsigned)init.size());
}

save_array &save_array::operator =(std::initializer_list<int> init)
{
	len = static_cast<unsigned>(init.size());
	if (len < max_size)
		memset(array, 0, max_size);
	else
	{
		if (max_size)
			delete array;
		max_size = len + dop_size;
		array = new uchar [max_size +1];
		memset(array, 0, max_size + 1);
	}
	unsigned i = 0;
	auto n = init.begin();
	while (n != init.end())
	{
		this->array[i] = static_cast<char>(*n);
		++n;
		++i;
	}
	return *this;
}

uchar &save_array ::operator [](const unsigned i) const
{
	return array[i];
}

uchar &save_array::last() const
{
	return array[len - 1];
}

bool save_array::operator==(const save_array &over) const
{
	unsigned start;
	unsigned finish;

	if (this->len != over.len)
		return (false);
	if (!len)
		return (true);
	start = 0;
	finish = len;
	auto *a = this->data();
	auto *b = over.data();
	while(start != finish)
	{
		if (a[start] != b[start])
			return (false);
		++start;
	}
	return (true);
}

bool save_array::operator ==(std::initializer_list<int> init) const
{
	if (len != init.size())
		return false;
	unsigned i = 0;
	auto start = init.begin();
	auto end = init.end();
	while (start != end)
	{
		if (static_cast<uchar>(array[i]) != static_cast<uchar>(*start))
			return false;
		++i;
		++start;
	}
	return true;
}

bool save_array::operator != (const save_array &over) const
{
	unsigned start;
	unsigned finish;

	if (this->len != over.len)
		return (true);
	if (!len)
		return (false);
	start = 0;
	finish = len;
	auto *a = this->data();
	auto *b = over.data();
	while(start != finish)
	{
		if (a[start] != b[start])
			return (true);
		++start;
	}
	return (false);
}

save_array save_array::mid(unsigned start, unsigned k) const
{
	if (!k)
	{
		if (len >= start)
			k = len - start;
	}
	return save_array(array + start, k);
}

void save_array::clear()
{
	memset(array, 0, len);
	len = 0;
}

save_array save_array::in_bit(unsigned start, unsigned k) const
{
	unsigned		len;
	unsigned		r = 0; // текущей индекс массива байт
	unsigned char	byte_in_progress; // байт к которому применяем операции
	unsigned last_index;


	if (!k)
		k = this->len - start;
	if (!this->len || this->len < k)
		return (save_array());
	len = 8 * k;
	save_array v;
	v.resize(len);
	last_index = start + k;
	while (start < last_index)
	{
		byte_in_progress = static_cast <unsigned char>(array[start]);
		v[r++] = static_cast <char>(byte_in_progress >> 7) & 1;
		v[r++] = static_cast <char>(byte_in_progress >> 6) & 1;
		v[r++] = static_cast <char>(byte_in_progress >> 5) & 1;
		v[r++] = static_cast <char>(byte_in_progress >> 4) & 1;
		v[r++] = static_cast <char>(byte_in_progress >> 3) & 1;
		v[r++] = static_cast <char>(byte_in_progress >> 2) & 1;
		v[r++] = static_cast <char>(byte_in_progress >> 1) & 1;
		v[r++] = static_cast <char>(byte_in_progress >> 0) & 1;
		++start;
	}
	return v;
}

QString save_array::in_QString(unsigned start, unsigned finish) const
{
	if (!finish)
		finish = static_cast<int>(static_cast<int>(len) - start);
	char *temp = new char [static_cast<unsigned>(finish) + 1];
	memmove(temp, array + start, static_cast<unsigned>(finish));
	temp[finish] = 0;
	QString v = temp;
	delete []temp;
	return (v);
}

QString save_array::byte_in_string(unsigned start, unsigned k) const
{
	unsigned		len;
	QString			str;
	unsigned char	temp;

	len = k ? start + k : this->len;
	while (start < len)
	{
		temp = static_cast<unsigned char>(array[start]);
		if (temp > 15)
			str.append(QString :: number(temp, 16) + ' ');
		else
			str.append('0' + QString :: number(temp, 16) + ' ');
		++start;
	}
	return (str);
}

unsigned short save_array::two_byte_in_short(const save_array &array, unsigned start, bool flag)
{
	unsigned short temp;

	if (flag == false)
	{
		temp = static_cast<unsigned short>(array[start]);
		temp <<= 8;
		temp |= static_cast<unsigned short>(array[start + 1]);
	}
	else
		memmove(&temp, array.data() + start, 2);
	return (temp);
}

unsigned short save_array::two_byte_in_short(unsigned start, bool flag) const
{
	unsigned short temp;

	if (flag == false)
	{
		temp = static_cast<unsigned short>(array[start]);
		temp <<= 8;
		temp |= static_cast<unsigned short>(array[start + 1]);
	}
	else
		memmove(&temp, array + start, 2);
	return (temp);
}

unsigned char save_array::bits_in_byte(unsigned start, unsigned k) const
{
	unsigned char	temp = 0;
	unsigned		r;

	r = k ? start + k : this->len;
	while (r != start)
	{
		temp <<= 1;
		temp |= array[r - 1];
		--r;
	}
	return (temp);
}

unsigned int save_array::byte_in_int(unsigned start, unsigned k) const
{
	unsigned int temp = 0;

	while (k > 0)
	{
		temp <<= 8;
		temp |= static_cast<unsigned char>(array[start]);
		--k;
		++start;
	}
	return (temp);
}

QList<save_array> save_array::split_number(unsigned i) const
{
	int r = 0;
	QList<save_array> list;
	auto full_size = len;
	while (full_size > i)
	{
		list.append(mid(r, static_cast<int>(i)));
		full_size -= i;
		r += i;
	}
	if (full_size)
		list.append(mid(r, static_cast<int>(full_size)));
	return (list);
}

//QList<save_array> save_array::split(uchar r) const
//{
//	QList<save_array> v;
//	unsigned start = 0;
//	unsigned prev = 0;
//	while (start < this->len)
//	{
//		if (this->array[start] == r && start - prev > 0)
//		{
//			v += save_array(this->array + prev, start - prev - 1);
//			prev = start + 1;
//		}
//		++start;
//	}
//	return v;
//}

uchar *save_array::find(It begin, It end, const save_array &f)
{
	size_t i = 0;
	size_t j;
	auto size = end - begin;
	if (size < f.size())
		return nullptr;
	while (i < size - f.size())
	{
		j = 0;
		while (j < f.size())
		{
			if (begin[i + j] != f.u_data()[j])
				break;
			++j;
		}
		if (j == f.size())
			return begin + i;

		++i;
	}
	return nullptr;
}

uchar *save_array::find(const save_array &f) const
{
	size_t i = 0;
	size_t j;
	if (this->size() < f.size())
		return nullptr;
	while (i < this->size() && this->size() - f.size() >= 0)
	{
		j = 0;
		while (j < f.size())
		{
			if (this->u_data()[i + j] != f.u_data()[j])
				break;
			++j;
		}
		if (j == f.size())
			return this->u_data() + i;

		++i;
	}
	return nullptr;
}

bool save_array::contains(const save_array &f) const
{
	return find(f) == nullptr ? false : true;
}

QList<save_array> save_array::split(const save_array &r) const
{
	QList<save_array> v;
	auto start = this->begin();
	auto end = this->end();
	auto prev = start;
	while (start < end)
	{
		start = find(start, end, r);
		if (start && start != prev)
		{
			v += save_array(prev, start);
		}
		else if (start == nullptr)
		{
			v += save_array(prev, end);
			break;
		}
		start += r.size();
		prev = start;
	}
	return v;
}

void save_array::resize(unsigned size)
{
	this->len = size;

	if (size + 1 < this->max_size)
	{
		array[size + 1] = 0;
		return;
	}
	if(this->max_size)
		delete [] array;
	this->max_size = size + dop_size;
	array = new uchar [max_size + 1];
	memset(array, 0, max_size + 1);
}

QDataStream &operator <<(QDataStream &stream, const save_array &array)
{
	QByteArray temp(array.data(), array.size());
	stream << temp;
	return stream;
}

QDataStream &operator >>(QDataStream &stream, save_array &array)
{
	QByteArray temp;
	stream >> temp;
	array = save_array(temp.data(), temp.size());
	return stream;
}
save_array operator + (std::initializer_list<int> init , const save_array &second)
{
	save_array temp = init;
	return temp + second;
}
