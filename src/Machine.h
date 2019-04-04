#pragma once
#include "Ops.h"
#include "../img/bitmap_image.hpp"
#include <memory>
#include <vector>
#include <map>
#include <functional>

class Machine
{
public:
	Machine();
	void parseFile(const char* filename);
	std::map<std::string, std::function<std::shared_ptr<Op>()>> opMap;
	int getRegister(std::string name);
	bool getFlag(std::string name);
	void setRegister(std::string name, int value);
	void setFlag(std::string name, bool value);
	void execute();
	void addToStack(int value);
	int removeFromStack();
	int getIndex(int index);
	void setIndex(int index, int value);
	void implementFwd(int reg1);
	void implementBack(int reg1);
private:
	std::vector<std::shared_ptr<Op>> mOps;
	std::map<std::string, int> registers;
	std::map<std::string, bool> flags;
	std::vector<int> stack;

	bitmap_image image;
	image_drawer draw;
};
