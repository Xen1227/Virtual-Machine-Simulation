#include "SrcMain.h"
#include <iostream>
#include "Machine.h"

void ProcessCommandArgs(int argc, const char* argv[])
{
	Machine m;
	m.parseFile(argv[1]);
	m.execute();
}
