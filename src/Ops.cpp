#include "Ops.h"
#include "Machine.h"
#include "Exceptions.h"
#include <string>

void Exit::Execute(Machine& machine)
{
	machine.setFlag("exit", true);
}

void MovI::Execute(Machine& machine)
{
	if (std::get<0>(this->mParameters) == "sc")
	{
		throw NonFatal(10);
		return;
	}

	if (std::get<0>(this->mParameters) == "r0")
	{
		throw NonFatal(11);
		return;
	}

	if (std::get<0>(this->mParameters) == "tc" && (std::get<1>(this->mParameters) < 0 || std::get<1>(this->mParameters) > 7))
	{
		throw NonFatal(14);
		return;
	}

	machine.setRegister(std::get<0>(this->mParameters), std::get<1>(this->mParameters));
}

void Add::Execute(Machine& machine)
{
	if (std::get<0>(this->mParameters) == "sc")
	{
		throw NonFatal(10);
		return;
	}

	if (std::get<0>(this->mParameters) == "r0")
	{
		throw NonFatal(11);
		return;
	}

	std::string inputRegister = std::get<0>(this->mParameters);
	std::string firstRegister = std::get<1>(this->mParameters);
	std::string secondRegister = std::get<2>(this->mParameters);
	int firstValue = machine.getRegister(firstRegister);
	int secondValue = machine.getRegister(secondRegister);

	if (std::get<0>(this->mParameters) == "tc" && (firstValue + secondValue < 0 || firstValue + secondValue > 7))
	{
		throw NonFatal(14);
		return;
	}

	machine.setRegister(inputRegister, firstValue + secondValue);

	int64_t firstValueTest = static_cast<int64_t>(firstValue);
	int64_t secondValueTest = static_cast<int64_t>(secondValue);
	if (firstValueTest + secondValueTest > INT32_MAX)
	{
		throw NonFatal(12);
	}
	if (firstValueTest + secondValueTest < INT32_MIN)
	{
		throw NonFatal(13);
	}
}

void Mov::Execute(Machine& machine)
{
	if (std::get<0>(this->mParameters) == "sc")
	{
		throw NonFatal(10);
		return;
	}

	if (std::get<0>(this->mParameters) == "r0")
	{
		throw NonFatal(11);
		return;
	}

	std::string inputRegister = std::get<0>(this->mParameters);
	std::string firstRegister = std::get<1>(this->mParameters);
	int firstValue = machine.getRegister(firstRegister);

	machine.setRegister(inputRegister, firstValue);
}

void Sub::Execute(Machine& machine)
{
	if (std::get<0>(this->mParameters) == "sc")
	{
		throw NonFatal(10);
		return;
	}

	if (std::get<0>(this->mParameters) == "r0")
	{
		throw NonFatal(11);
		return;
	}

	std::string inputRegister = std::get<0>(this->mParameters);
	std::string firstRegister = std::get<1>(this->mParameters);
	std::string secondRegister = std::get<2>(this->mParameters);
	int firstValue = machine.getRegister(firstRegister);
	int secondValue = machine.getRegister(secondRegister);

	machine.setRegister(inputRegister, firstValue - secondValue);

	int64_t firstValueTest = static_cast<int64_t>(firstValue);
	int64_t secondValueTest = static_cast<int64_t>(secondValue);
	if (firstValueTest - secondValueTest > INT32_MAX)
	{
		throw NonFatal(12);
	}
	if (firstValueTest - secondValueTest < INT32_MIN)
	{
		throw NonFatal(13);
	}

	
}

void Mul::Execute(Machine& machine)
{
	if (std::get<0>(this->mParameters) == "sc")
	{
		throw NonFatal(10);
		return;
	}

	if (std::get<0>(this->mParameters) == "r0")
	{
		throw NonFatal(11);
		return;
	}

	std::string inputRegister = std::get<0>(this->mParameters);
	std::string firstRegister = std::get<1>(this->mParameters);
	std::string secondRegister = std::get<2>(this->mParameters);
	int firstValue = machine.getRegister(firstRegister);
	int secondValue = machine.getRegister(secondRegister);

	machine.setRegister(inputRegister, firstValue * secondValue);

	int64_t firstValueTest = static_cast<int64_t>(firstValue);
	int64_t secondValueTest = static_cast<int64_t>(secondValue);
	if (firstValueTest * secondValueTest > INT32_MAX)
	{
		throw NonFatal(12);
	}
	if (firstValueTest * secondValueTest < INT32_MIN)
	{
		throw NonFatal(13);
	}

	
}

void Div::Execute(Machine& machine)
{
	if (std::get<0>(this->mParameters) == "sc")
	{
		throw NonFatal(10);
		return;
	}

	if (std::get<0>(this->mParameters) == "r0")
	{
		throw NonFatal(11);
		return;
	}

	std::string inputRegister = std::get<0>(this->mParameters);
	std::string firstRegister = std::get<1>(this->mParameters);
	std::string secondRegister = std::get<2>(this->mParameters);
	int firstValue = machine.getRegister(firstRegister);
	int secondValue = machine.getRegister(secondRegister);

	if (secondValue == 0)
	{
		throw Fatal(102);
		return;
	}

	machine.setRegister(inputRegister, firstValue / secondValue);

	int64_t firstValueTest = static_cast<int64_t>(firstValue);
	int64_t secondValueTest = static_cast<int64_t>(secondValue);
	if (firstValueTest / secondValueTest > INT32_MAX)
	{
		throw NonFatal(12);
	}
	if (firstValueTest / secondValueTest < INT32_MIN)
	{
		throw NonFatal(13);
	}

	
}

void Inc::Execute(Machine& machine)
{
	if (std::get<0>(this->mParameters) == "sc")
	{
		throw NonFatal(10);
		return;
	}

	if (std::get<0>(this->mParameters) == "r0")
	{
		throw NonFatal(11);
		return;
	}

	std::string inputRegister = std::get<0>(this->mParameters);
	int firstValue = machine.getRegister(inputRegister);

	machine.setRegister(inputRegister, firstValue + 1);

	int64_t firstValueTest = static_cast<int64_t>(firstValue);
	if (firstValueTest + 1 > INT32_MAX)
	{
		throw NonFatal(12);
	}
	if (firstValueTest + 1 < INT32_MIN)
	{
		throw NonFatal(13);
	}

	
}

void Dec::Execute(Machine& machine)
{
	if (std::get<0>(this->mParameters) == "sc")
	{
		throw NonFatal(10);
		return;
	}

	if (std::get<0>(this->mParameters) == "r0")
	{
		throw NonFatal(11);
		return;
	}

	std::string inputRegister = std::get<0>(this->mParameters);
	int firstValue = machine.getRegister(inputRegister);

	machine.setRegister(inputRegister, firstValue - 1);

	int64_t firstValueTest = static_cast<int64_t>(firstValue);
	if (firstValueTest - 1 > INT32_MAX)
	{
		throw NonFatal(12);
	}
	if (firstValueTest - 1 < INT32_MIN)
	{
		throw NonFatal(13);
	}

	
}

void Jmp::Execute(Machine& machine)
{

	std::string inputRegister = std::get<0>(this->mParameters);
	int firstValue = machine.getRegister(inputRegister);

	machine.setRegister("pc", firstValue);
}

void Cmpeq::Execute(Machine& machine)
{

	std::string inputRegister = std::get<0>(this->mParameters);
	std::string firstRegister = std::get<1>(this->mParameters);
	int firstValue = machine.getRegister(inputRegister);
	int secondValue = machine.getRegister(inputRegister);

	machine.setFlag("test", firstValue == secondValue);
}

void Cmplt::Execute(Machine& machine)
{

	std::string inputRegister = std::get<0>(this->mParameters);
	std::string firstRegister = std::get<1>(this->mParameters);
	int firstValue = machine.getRegister(inputRegister);
	int secondValue = machine.getRegister(firstRegister);

	machine.setFlag("test", firstValue < secondValue);
}

void Jt::Execute(Machine& machine)
{

	std::string inputRegister = std::get<0>(this->mParameters);
	int firstValue = machine.getRegister(inputRegister);

	if (machine.getFlag("test"))
	{
		machine.setRegister("pc", firstValue);
	}	
}

void Push::Execute(Machine& machine)
{

	std::string inputRegister = std::get<0>(this->mParameters);
	int firstValue = machine.getRegister(inputRegister);
	int scValue = machine.getRegister("sc");

	if (scValue == 256)
	{
		throw Fatal(101);
		return;
	}
	
	machine.addToStack(firstValue);
	machine.setRegister("sc", scValue + 1);	
}

void Pop::Execute(Machine& machine)
{
	if (std::get<0>(this->mParameters) == "sc")
	{
		throw NonFatal(10);
		return;
	}

	if (std::get<0>(this->mParameters) == "r0")
	{
		throw NonFatal(11);
		return;
	}

	std::string inputRegister = std::get<0>(this->mParameters);
	int scValue = machine.getRegister("sc");

	if (scValue == 0)
	{
		throw Fatal(103);
		return;
	}

	int firstValue = machine.removeFromStack();
	

	
	
	machine.setRegister(inputRegister, firstValue);
	machine.setRegister("sc", scValue - 1);	
}

void Load::Execute(Machine& machine)
{
	if (std::get<0>(this->mParameters) == "sc")
	{
		throw NonFatal(10);
		return;
	}

	if (std::get<0>(this->mParameters) == "r0")
	{
		throw NonFatal(11);
		return;
	}

	std::string inputRegister = std::get<0>(this->mParameters);
	std::string firstRegister = std::get<1>(this->mParameters);
	int index = machine.getRegister(firstRegister);
	int firstValue = machine.getIndex(index);

	if (index < 0 || index >= machine.getRegister("sc"))
	{
		throw Fatal(100);
		return;
	}
	
	machine.setRegister(inputRegister, firstValue);	
}

void Store::Execute(Machine& machine)
{

	std::string inputRegister = std::get<0>(this->mParameters);
	std::string firstRegister = std::get<1>(this->mParameters);
	int index = machine.getRegister(inputRegister);
	int firstValue = machine.getRegister(firstRegister);

	if (index < 0 || index >= machine.getRegister("sc"))
	{
		throw Fatal(100);
		return;
	}

	machine.setIndex(index, firstValue);
}

void Loadi::Execute(Machine& machine)
{
	if (std::get<0>(this->mParameters) == "sc")
	{
		throw NonFatal(10);
		return;
	}

	if (std::get<0>(this->mParameters) == "r0")
	{
		throw NonFatal(11);
		return;
	}

	std::string inputRegister = std::get<0>(this->mParameters);
	int index = std::get<1>(this->mParameters);

	if (index < 0 || index >= machine.getRegister("sc"))
	{
		throw Fatal(100);
		return;
	}

	int firstValue = machine.getIndex(index);

	
	machine.setRegister(inputRegister, firstValue);	
}

void Storei::Execute(Machine& machine)
{

	std::string inputRegister = std::get<1>(this->mParameters);
	int index = std::get<0>(this->mParameters);
	int firstValue = machine.getRegister(inputRegister);
	machine.setIndex(index, firstValue);
}

void Loadsc::Execute(Machine& machine)
{
	if (std::get<0>(this->mParameters) == "sc")
	{
		throw NonFatal(10);
		return;
	}

	if (std::get<0>(this->mParameters) == "r0")
	{
		throw NonFatal(11);
		return;
	}

	std::string inputRegister = std::get<0>(this->mParameters);
	std::string firstRegister = std::get<1>(this->mParameters);
	int scValue = machine.getRegister("sc");
	int firstValue = machine.getRegister(firstRegister);
	int outputValue = machine.getIndex(scValue - firstValue - 1);

	machine.setRegister(inputRegister, outputValue);	
}

void Storesc::Execute(Machine& machine)
{

	std::string inputRegister = std::get<0>(this->mParameters);
	std::string firstRegister = std::get<1>(this->mParameters);
	int scValue = machine.getRegister("sc");
	int firstValue = machine.getRegister(inputRegister);
	int secondValue = machine.getRegister(firstRegister);
	int index = scValue - firstValue - 1;

	if (index < 0 || index >= machine.getRegister("sc"))
	{
		throw Fatal(100);
		return;
	}

	machine.setIndex(index, secondValue);	
}

void PenDown::Execute(Machine& machine)
{
	machine.setFlag("pen", true);	
}

void PenUp::Execute(Machine& machine)
{
	machine.setFlag("pen", false);	
}

void Fwd::Execute(Machine& machine)
{
	std::string inputRegister = std::get<0>(this->mParameters);
	int firstValue = machine.getRegister(inputRegister);
	machine.implementFwd(firstValue);	
}

void Back::Execute(Machine& machine)
{
	std::string inputRegister = std::get<0>(this->mParameters);
	int firstValue = machine.getRegister(inputRegister);
	machine.implementBack(firstValue);	
}
