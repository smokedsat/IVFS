#include "VFS2.h"
#include "createPaths.h"

File* VFS::Open(const char* name)
{
	if (fs::exists(name))
	{
		this->_f->open(name, std::fstream::in);
		if (this->_f->is_open())
		{
		/*	std::cout << "Opened file in readmode. Changed mode of file to readonly. (Open). Function returned pointer to FILE(fstream)." << std::endl;*/
			this->_f->_openMode = mode::read;
			return _f;
		}
	}
	else if(this->_f->_openMode == mode::write)
	{
		std::cout << "File opened in mode write. (Open). Returned nullptr." << std::endl;
		return nullptr;
	}
	else
	{
		std::cout << "File doenst exists. (Open). Returned nullptr." << std::endl;
		return nullptr;
	}
	return nullptr;
}; // Открыть файл в readonly режиме. Если нет такого файла или же он открыт
// во writeonly режиме - вернуть nullptr.


File* VFS::Create(const char* name) 
{
	if (fs::exists(name))
	{
		if (this->_f->_openMode == mode::read)
		{
			std::cout << "File is already opened in readonly mode. (Create).Returned nullptr." << std::endl;
			return nullptr;
		}
		else if (this->_f->_openMode == mode::write || this->_f->_openMode == mode::none)
		{
			this->_f->_openMode = mode::write;
			this->_f->open(name, std::fstream::out| std::fstream::ate);

			if (this->_f->is_open())
			{
				return this->_f;
			}
		}
	}
	else
	{
		createPaths(name);
		
		this->_f->_openMode = mode::write;

		this->_f->open(name, std::fstream::out);
		return this->_f;
	}
	return nullptr;
}; // Открыть или создать файл в writeonly режиме. Если нужно, то создать 
// все нужные поддиректории, упомянутые в пути. Вернуть nullptr, если этот файл уже открыт в readonly режиме.



size_t VFS::Read(File* f, char* buff, size_t len)
{
	if (f == nullptr)
	{
		return 0;
	}

	if (f->is_open())
	{
		if (f->_openMode == mode::read)
		{
			f->readsome(buff, len);

			size_t size = strnlen(buff, len);
			return size;
		}
	}
	else
	{
		std::cout << "File is not opened. (Read)." << std::endl;
		return 0;
	}
	return 0;
}; // Прочитать данные из файла. Возвращаемое значение- 
// сколько реально байт удалось прочитать.

size_t VFS::Write(File* f,  char* buff, size_t len)
{
	if (f == nullptr)
	{
		return 0;
	}

	if (f->is_open())
	{
		if (f->_openMode == mode::write)
		{
			f->write(buff, len);
			
			if (strlen(buff) > len)
			{
				return len;
			}
			else if(strlen(buff) < len)
			{
				return strlen(buff);
			}
			else
			{
				return len;
			}
		}
	}
	else
	{
		std::cout << "File is not opened. (Write)." << std::endl;
		return 0;
	}
	return 0;
};// Записать данные в файл. Возвращаемое значение - 
// сколько реально байт удалось записать

void VFS::Close(File* f)
{
	if (f->is_open())
	{
		f->_openMode = mode::none;
		f->close();
	}
	else
	{
		std::cout << "File is already closed. (Close). Openmode is " << f->_openMode << std::endl;
	}

}; // Закрыть файл. 