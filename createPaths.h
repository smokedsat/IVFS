#pragma once

#include <filesystem>
#include <string>



// That function create directories if name of file includes directories && 
void createPaths(const char* name)
{
	
		auto file = new fs::path(name);

		// Create all directories from name
		std::filesystem::create_directories(name);

		// Removes directory with filename (if name is ./sam/sefa/file.txt, it will remove file.txt directory
		if (std::filesystem::is_directory(file->string()))
		{
			std::filesystem::remove(file->string());
		}
	
	return;
}