#pragma once

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

#include "LLVMController.h"

using namespace std;

class Node {
public:
  string type;
  string ntype;
  string value;
  vector<shared_ptr<Node>> children;
  Node() = default;
  virtual string JSON();
  virtual ~Node() = default;
//   Node(const Node &) = delete;
  Node(Node &&) = default;
  virtual llvm::Value *codegen(LLVMController* Controller);
  // virtual void codegen(LLVMController* Controller);
//   Node(const Node &) = default;
};

class Literal : public Node {
public:
  Literal() = default; // string type, string value
  // ~Literal() = default;
  string ntype = "LITERAL";
  string JSON();
  llvm::Value *codegen(LLVMController* Controller); 
};

class Expression : public Node {
public:
  Expression() = default;
  string ntype = "EXPRESSION";
  vector<shared_ptr<Node>> body;
 string JSON();
 llvm::Value *codegen(LLVMController* Controller);
};

class Identifier : public Node {
public:
  Identifier() = default; // string type, string value
                // ~Identifier() = default;
//   Identifier(const Identifier &) = default;
//   ~Identifier() = default;
  bool isTyped;
  vector<string> token;
  string ntype = "IDENTIFIER";
  string JSON();
  llvm::Value *codegen(LLVMController* Controller);
};

class variableDeclaration : public Node {
public:
  variableDeclaration() = default;
  string ntype = "VARIABLEDECLARATION";
  shared_ptr<Identifier> identifier;
  bool isDefined;
  shared_ptr<Expression> body;
  string JSON();
  llvm::Value *codegen(LLVMController* Controller);
};

class funcCall : public Node {
  public:
  funcCall() = default;
  string ntype = "FUNCCALL";
  string name;
  shared_ptr<Expression> params;
  string JSON();
  llvm::Value *codegen(LLVMController* Controller);
};

class seperator : public Node {
  public:
  seperator() = default;
  string ntype = "SEPERATOR";
  string JSON();
  llvm::Value *codegen(LLVMController* Controller);
};

class funcDecl : public Node {
  public:
  funcDecl() = default;
  string ntype = "FUNCDECL";
  string name;
  shared_ptr<Expression> params;
  shared_ptr<Expression> body;
  string JSON();
  llvm::Value *codegen(LLVMController* Controller);
};