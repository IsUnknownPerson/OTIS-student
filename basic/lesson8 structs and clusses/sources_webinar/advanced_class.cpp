#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <math.h>

//class wrapper for read only file using posix api
class ReadOnlyFileWrapper
{
public:
    ReadOnlyFileWrapper(const std::string& path)
        : m_path(path)
    {
        std::cout << "Constructor" << std::endl;
        fd = open(path.c_str(), Flags); //posix native
    }

    ReadOnlyFileWrapper(const ReadOnlyFileWrapper& other)
    {
        std::cout << "Copy constructor" << std::endl;
        m_path = other.m_path;
        fd = open(other.m_path.c_str(), Flags);
    }

    ReadOnlyFileWrapper& operator= (const ReadOnlyFileWrapper& other) //can not be non member operator
    {
        std::cout << "Copy assignment operator" << std::endl;
        if (this == &other)
            return *this;

        close(fd);
        this->m_path = other.m_path;
        fd = open(m_path.c_str(), O_RDONLY);
        return *this;
    }

    ~ReadOnlyFileWrapper()
    {
        std::cout << "Destructor" << std::endl;
        close(fd);
    }

    void read()
    {
        /* some implementation of read file */
    }

    static int GetFlags() //work only with static variables, no static constructor!
    {
        //std::cout << this; this is unavailable here
        return Flags;
    }

    static int GetMode();

private:
    int fd;
    std::string m_path;

    static const int Flags = O_RDONLY; //declaration + definition
    static int Mode; //declaration only, non-const must be initialized out of class
};

int ReadOnlyFileWrapper::Mode = S_IRUSR; //definition without static

int ReadOnlyFileWrapper::GetMode()
{
    return Mode;
}

void use_file_wrapper()
{
    ReadOnlyFileWrapper f("config.json");

    ReadOnlyFileWrapper f2 = f; //call to copy constructor
    f2.read();
    f = f2; //call to copy assignment operator
    f = f;

    ReadOnlyFileWrapper::GetFlags();

    std::cout << "File flags " << ReadOnlyFileWrapper::GetFlags()
              << " mode " << ReadOnlyFileWrapper::GetMode() << std::endl;
}

int main() {
    use_file_wrapper();

	return 0;
}
