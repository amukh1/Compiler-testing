#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

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
  virtual void codegen();
//   Node(const Node &) = default;
};

class Literal : public Node {
public:
  Literal() = default; // string type, string value
  // ~Literal() = default;
  string ntype = "LITERAL";
  string JSON();

};

class Expression : public Node {
public:
  Expression() = default;
  string ntype = "EXPRESSION";
  vector<shared_ptr<Node>> body;
 string JSON();
};

class Identifier : public Node {
public:
  Identifier() = default; // string type, string value
                // ~Identifier() = default;
//   Identifier(const Identifier &) = default;
//   ~Identifier() = default;

  vector<string> token;
  string ntype = "IDENTIFIER";
  string JSON();
};

class variableDeclaration : public Node {
public:
  variableDeclaration() = default;
  string ntype = "VARIABLEDECLARATION";
  shared_ptr<Identifier> identifier;
  bool isDefined;
  shared_ptr<Expression> body;
  string JSON();
};

class funcCall : public Node {
  public:
  funcCall() = default;
  string ntype = "FUNCCALL";
  string name;
  shared_ptr<Expression> params;
  string JSON();
};

class seperator : public Node {
  public:
  seperator() = default;
  string ntype = "SEPERATOR";
  string JSON();
};