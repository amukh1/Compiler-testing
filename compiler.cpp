#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Verifier.h>
#include <llvm/IR/Instructions.h>
#include <llvm/Support/raw_ostream.h>

#include "AST.h"
#include "LLVMController.h"

using namespace std;

llvm::Value *Literal::codegen(LLVMController* Controller) { return nullptr; }
llvm::Value *Expression::codegen(LLVMController* Controller) { return nullptr; }
llvm::Value *Identifier::codegen(LLVMController* Controller) { return nullptr; }
llvm::Value *variableDeclaration::codegen(LLVMController* Controller) { return nullptr; }
llvm::Value *funcCall::codegen(LLVMController* Controller) { return nullptr; }
llvm::Value *seperator::codegen(LLVMController* Controller) { return nullptr; }
llvm::Value *funcDecl::codegen(LLVMController* Controller) { return nullptr; }