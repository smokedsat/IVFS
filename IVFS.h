#pragma once

#include <fstream>

enum mode
{
	none = 0,
	read = 1,
	write,
	readwrite
};

namespace TestTask
{
	struct File:public std::fstream
	{
		mode _openMode = mode::none;

		 File& operator=(File& other)
		{
			 *this = other;
			 return *this;
		}

	}; // Вы имеете право как угодно задать содержимое этой структуры

	struct IVFS
	{
		virtual File* Open(const char* name) = 0; // Открыть файл в readonly режиме. Если нет такого файла или же он открыт
		// во writeonly режиме - вернуть nullptr.

		virtual File* Create(const char* name) = 0; // Открыть или создать файл в writeonly режиме. Если нужно, то создать 
		// все нужные поддиректории, упомянутые в пути. Вернуть nullptr, если этот файл уже открыт в readonly режиме.

		virtual size_t Read(File* f, char* buff, size_t len) = 0; // Прочитать данные из файла. Возвращаемое значение- 
		// сколько реально байт удалось прочитать.

		virtual size_t Write(File* f, char* buff, size_t len) = 0;// Записать данные в файл. Возвращаемое значение - 
		// сколько реально байт удалось записать

		virtual void Close(File* f) = 0; // Закрыть файл. 
	};
}




