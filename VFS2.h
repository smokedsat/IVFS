#pragma once

#include "IVFS.h"
#include <filesystem>
#include <iostream>


using namespace TestTask;

namespace fs = std::filesystem;

struct VFS : public IVFS
{
	// Реализация класса File находится в файле IVFS.h
	File *_f = new File;

	File* Open(const char* name) override; // Открыть файл в readonly режиме. Если нет такого файла или же он открыт
	// во writeonly режиме - вернуть nullptr.

	File* Create(const char* name) override; // Открыть или создать файл в writeonly режиме. Если нужно, то создать 
	// все нужные поддиректории, упомянутые в пути. Вернуть nullptr, если этот файл уже открыт в readonly режиме.

	size_t Read(File* f, char* buff, size_t len) override; // Прочитать данные из файла. Возвращаемое значение- 
	// сколько реально байт удалось прочитать.

	size_t Write(File* f, char* buff, size_t len) override;// Записать данные в файл. Возвращаемое значение - 
	// сколько реально байт удалось записать

	void Close(File* f) override; // Закрыть файл. 

};