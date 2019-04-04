#include "Machine.h"
#include "Exceptions.h"
#include <fstream>
#include <string>
#include <sstream>

template <typename T>
std::shared_ptr<Op> CreateOp()
{
	return std::make_shared<T>();
}


Machine::Machine() : image(320, 240), draw(image)
{
	//add to opMap
	opMap.emplace("movi", &CreateOp<MovI>);
	opMap.emplace("exit", &CreateOp<Exit>);
	opMap.emplace("add", &CreateOp<Add>);
	opMap.emplace("mov", &CreateOp<Mov>);
	opMap.emplace("sub", &CreateOp<Sub>);
	opMap.emplace("mul", &CreateOp<Mul>);
	opMap.emplace("div", &CreateOp<Div>);
	opMap.emplace("inc", &CreateOp<Inc>);
	opMap.emplace("dec", &CreateOp<Dec>);
	opMap.emplace("jmp", &CreateOp<Jmp>);
	opMap.emplace("cmpeq", &CreateOp<Cmpeq>);
	opMap.emplace("cmplt", &CreateOp<Cmplt>);
	opMap.emplace("jt", &CreateOp<Jt>);
	opMap.emplace("push", &CreateOp<Push>);
	opMap.emplace("pop", &CreateOp<Pop>);
	opMap.emplace("load", &CreateOp<Load>);
	opMap.emplace("store", &CreateOp<Store>);
	opMap.emplace("loadi", &CreateOp<Loadi>);
	opMap.emplace("storei", &CreateOp<Storei>);
	opMap.emplace("loadsc", &CreateOp<Loadsc>);
	opMap.emplace("storesc", &CreateOp<Storesc>);
	opMap.emplace("pendown", &CreateOp<PenDown>);
	opMap.emplace("penup", &CreateOp<PenUp>);
	opMap.emplace("fwd", &CreateOp<Fwd>);
	opMap.emplace("back", &CreateOp<Back>);

	//initialize registers
	registers["r0"] = 0;
	registers["r1"] = 0;
	registers["r2"] = 0;
	registers["r3"] = 0;
	registers["r4"] = 0;
	registers["r5"] = 0;
	registers["r6"] = 0;
	registers["r7"] = 0;
	registers["pc"] = 0;
	registers["sc"] = 0;
	registers["ex"] = 0;
	registers["tx"] = 0;
	registers["ty"] = 0;
	registers["tr"] = 0;
	registers["tc"] = 0;

	//initialize flags
	flags["exit"] = false;
	flags["test"] = false;
	flags["pen"] = false;

	//image
	image.set_all_channels(0, 0, 0);
	draw.pen_width(1);
}

void Machine::parseFile(const char* filename)
{
	std::ifstream myfile(filename);
	std::string line;

	if (myfile.is_open())
	{
		while (static_cast<bool>(getline(myfile, line)))
		{
            // Get the string for op name and params
			std::vector<std::string> currentLine;
			std::string token;
			std::stringstream ss(line);
			
			//gets name and parameters
			while (static_cast<bool>(getline(ss, token, ' ')))
			{
				currentLine.push_back(token);
			}

			std::string opName = currentLine[0];
			std::string params = currentLine.size() > 1 ? currentLine[1] : "";
			std::shared_ptr<Op> ptr = opMap.at(opName)();
			ptr->Parse(params);
			mOps.push_back(ptr);
		}
		myfile.close();
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
	}

}

int Machine::getRegister(std::string name)
{
	std::map<std::string, int>::iterator it = registers.find(name);

	if (it == registers.end())
	{
		return -1;
	}
	return it->second;
}

bool Machine::getFlag(std::string name)
{
	std::map<std::string, bool>::iterator it = flags.find(name);

	if (it == flags.end())
	{
		return false;
	}
	return it->second;
}

void Machine::setRegister(std::string name, int value)
{
	std::map<std::string, int>::iterator it = registers.find(name);

	if (it != registers.end())
	{
		if (name == "tc" && (value < 0 || value > 7))
		{
			throw NonFatal(14);
			return;
		}
		it->second = value;
	}
}

void Machine::setFlag(std::string name, bool value)
{
	std::map<std::string, bool>::iterator it = flags.find(name);

	if (it != flags.end())
	{
		it->second = value;
	}
}

void Machine::execute()
{
	std::ofstream myfile("log.txt");
	std::ofstream myfile1("stack.txt");

	if (myfile.is_open())
	{
		myfile << "********************\n";
		myfile << "r0=" << getRegister("r0") << "\n";
		myfile << "r1=" << getRegister("r1") << "\n";
		myfile << "r2=" << getRegister("r2") << "\n";
		myfile << "r3=" << getRegister("r3") << "\n";
		myfile << "r4=" << getRegister("r4") << "\n";
		myfile << "r5=" << getRegister("r5") << "\n";
		myfile << "r6=" << getRegister("r6") << "\n";
		myfile << "r7=" << getRegister("r7") << "\n";
		myfile << "pc=" << getRegister("pc") << "\n";
		myfile << "sc=" << getRegister("sc") << "\n";
		myfile << "ex=" << getRegister("ex") << "\n";
		myfile << "tx=" << getRegister("tx") << "\n";
		myfile << "ty=" << getRegister("ty") << "\n";
		myfile << "tr=" << getRegister("tr") << "\n";
		myfile << "tc=" << getRegister("tc") << "\n";
		myfile << "exit=" << getFlag("exit") << "\n";
		myfile << "test=" << getFlag("test") << "\n";
		myfile << "pen=" << getFlag("pen") << "\n";

		myfile1 << "pc: " << getRegister("pc") << " Stack: ";
		for (int i = 0; i < stack.size(); i++)
		{
			myfile1 << stack[i] << " ";
		}
		myfile1 << "\n";
	}
	else
	{
		std::cout << "Unable to open file" << std::endl;
	}

	while (!getFlag("exit"))
	{
		int pcValue = getRegister("pc");
		std::shared_ptr<Op> ptr = mOps[pcValue];
		setRegister("pc", pcValue + 1);

		try
		{
			ptr->Execute(*this);
		}
		catch (NonFatal& e)
		{
			setRegister("ex", e.getCode());
		}
		catch (Fatal& e)
		{
			setRegister("ex", e.getCode());
			setFlag("exit", true);
		}

		myfile << "Executing: " << ptr->GetName() << "\n";
		myfile << "********************\n";
		myfile << "r0=" << getRegister("r0") << "\n";
		myfile << "r1=" << getRegister("r1") << "\n";
		myfile << "r2=" << getRegister("r2") << "\n";
		myfile << "r3=" << getRegister("r3") << "\n";
		myfile << "r4=" << getRegister("r4") << "\n";
		myfile << "r5=" << getRegister("r5") << "\n";
		myfile << "r6=" << getRegister("r6") << "\n";
		myfile << "r7=" << getRegister("r7") << "\n";
		myfile << "pc=" << getRegister("pc") << "\n";
		myfile << "sc=" << getRegister("sc") << "\n";
		myfile << "ex=" << getRegister("ex") << "\n";
		myfile << "tx=" << getRegister("tx") << "\n";
		myfile << "ty=" << getRegister("ty") << "\n";
		myfile << "tr=" << getRegister("tr") << "\n";
		myfile << "tc=" << getRegister("tc") << "\n";
		myfile << "exit=" << getFlag("exit") << "\n";
		myfile << "test=" << getFlag("test") << "\n";
		myfile << "pen=" << getFlag("pen") << "\n";

		myfile1 << "pc: " << getRegister("pc") << " Stack: ";
		for (int i = 0; i < stack.size(); i++)
		{
			myfile1 << stack[i];
			if (i < stack.size() - 1)
			{
				myfile1 << " ";
			}
		}
		myfile1 << "\n";
	}

	myfile.close();
	image.save_image("output.bmp");
}

void Machine::addToStack(int value)
{
	stack.push_back(value);
}

int Machine::removeFromStack()
{
	int backValue = stack.back();
	stack.pop_back();
	return backValue;
}

int Machine::getIndex(int index)
{
	return stack[index];
}

void Machine::setIndex(int index, int value)
{
	stack[index] = value;
}

void Machine::implementFwd(int reg1)
{
	int currentTx = getRegister("tx");
	int currentTy = getRegister("ty");
	float currentTr = getRegister("tr") * 0.0174533f;
	int endx = currentTx + static_cast<int>(std::cos(currentTr) * reg1);
	int endy = currentTy + static_cast<int>(std::sin(currentTr) * reg1);

	if (getFlag("pen"))
	{
		if (getRegister("tc") == 0)
		{
			draw.pen_color(255, 255, 255);
		}
		else if (getRegister("tc") == 1)
		{
			draw.pen_color(255, 255, 0);
		}
		else if (getRegister("tc") == 2)
		{
			draw.pen_color(255, 0, 255);
		}
		else if (getRegister("tc") == 3)
		{
			draw.pen_color(255, 0, 0);
		}
		else if (getRegister("tc") == 4)
		{
			draw.pen_color(0, 255, 255);
		}
		else if (getRegister("tc") == 5)
		{
			draw.pen_color(0, 255, 0);
		}
		else if (getRegister("tc") == 6)
		{
			draw.pen_color(0, 0, 255);
		}
		else if (getRegister("tc") == 7)
		{
			draw.pen_color(0, 0, 0);
		}
		draw.line_segment(currentTx, currentTy, endx, endy);
	}

	setRegister("tx", endx);
	setRegister("ty", endy);
}

void Machine::implementBack(int reg1)
{
	int currentTx = getRegister("tx");
	int currentTy = getRegister("ty");
	float currentTr = getRegister("tr") * 0.0174533f;
	int endx = currentTx + static_cast<int>(std::cos(currentTr) * reg1 * -1);
	int endy = currentTy + static_cast<int>(std::sin(currentTr) * reg1 * -1);

	if (getFlag("pen"))
	{
		if (getRegister("tc") == 0)
		{
			draw.pen_color(255, 255, 255);
		}
		else if (getRegister("tc") == 1)
		{
			draw.pen_color(255, 255, 0);
		}
		else if (getRegister("tc") == 2)
		{
			draw.pen_color(255, 0, 255);
		}
		else if (getRegister("tc") == 3)
		{
			draw.pen_color(255, 0, 0);
		}
		else if (getRegister("tc") == 4)
		{
			draw.pen_color(0, 255, 255);
		}
		else if (getRegister("tc") == 5)
		{
			draw.pen_color(0, 255, 0);
		}
		else if (getRegister("tc") == 6)
		{
			draw.pen_color(0, 0, 255);
		}
		else if (getRegister("tc") == 7)
		{
			draw.pen_color(0, 0, 0);
		}
		draw.line_segment(currentTx, currentTy, endx, endy);
	}

	setRegister("tx", endx);
	setRegister("ty", endy);
}
