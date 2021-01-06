#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include <iostream>

using namespace std;

// a struct to return two strings
struct Shaders {
	string vertexcode;
	string fragmentscode;
};

class ResourceManager
{
public:
	static Shaders getShadersCode(const char* vertex, const char* fragment);
};

#endif