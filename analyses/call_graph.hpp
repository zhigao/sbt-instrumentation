#ifndef CALLGRAPH_H
#define CALLGRAPH_H

#include <map>
#include <llvm/IR/Module.h>
#include <llvm/IR/Instruction.h>
#include "llvm/analysis/PointsTo/PointsTo.h"
#include "analysis/PointsTo/PointsToFlowInsensitive.h"

class CGNode {
	public:
		CGNode(const llvm::Function* callerF, int id);
		bool containsCall(const llvm::Function* call);
		const llvm::Function* getCaller() const;
		int getId() const;
		std::vector<const CGNode*> calls;

	private:
		int id;
		const llvm::Function* caller;
};

class CallGraph {
	public:
		CallGraph(llvm::Module &M, std::unique_ptr<dg::LLVMPointerAnalysis> &PTA);
		bool containsCall(const llvm::Function* caller, const llvm::Function* callee);
		bool containsDirectCall(const llvm::Function* caller, const llvm::Function* callee);
		bool isRecursive(const llvm::Function* function);

	private:
		std::map<const llvm::Function*, CGNode*> nodes;
		int lastId;
		void handleCallInst(std::unique_ptr<dg::LLVMPointerAnalysis> &PTA, const llvm::Function *F, const llvm::CallInst *CI);
		void BFS(const CGNode *startNode, std::vector<bool> &visited);
};

#endif
