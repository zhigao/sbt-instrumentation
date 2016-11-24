#ifndef REWRITER_H
#define REWRITER_H

#include <list>
#include <string>
#include <iostream>
#include <fstream>


// Configuration
enum class InstrumentPlacement {
	BEFORE,
	AFTER,
	REPLACE
};

class InstrumentInstruction {
 public:
	std::string returnValue;
	std::string instruction;
	std::list<std::string> parameters;
	std::string getSizeTo;
	std::string stripInboundsOffsets;
};

class InstrumentGlobalVar {
 public:
	std::string globalVariable;
	std::string getSizeTo;
};

typedef std::list<InstrumentInstruction> InstrumentSequence;

class RewriteRule {
 public:
	InstrumentSequence foundInstrs;
	InstrumentGlobalVar globalVar;
	InstrumentInstruction newInstr;
	InstrumentPlacement where;
	std::string inFunction;
	std::list<std::string> condition;
};

typedef std::list<RewriteRule> RewriterConfig;

// Rewriter
class Rewriter {
	RewriterConfig config;
	public:
		RewriterConfig getConfig();
		void parseConfig(std::ifstream &config_file);
		std::list<std::string> analysisPaths;
};

#endif
