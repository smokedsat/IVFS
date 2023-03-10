#include "VFS2.h"


int main()
{

	const char* name = "./semen/smokedsast/mypath/file.txt";
	const char* write = "./semen/smokedsaats/secondPath/writed/write.txt";

	//createPaths(name);
	//createPaths(write);

	char* text = (char*)"Hello from";
	char* buffer = new char[1000];

	VFS vfs;
	size_t writed = vfs.Write(vfs.Create(write), text, 16);
	vfs.Close(vfs._f);

	size_t readed = vfs.Read(vfs.Open(write), buffer, 16);
	vfs.Close(vfs._f);

	std::cout << "Size of writed bytes: " << writed << std::endl;
	std::cout << "Size of readed bytes: " << writed << std::endl;

	
	return 0;
}