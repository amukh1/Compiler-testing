#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "AST.h"
#include "parser.h"

using namespace std;

void Parser::parse(
    vector<vector<string>> tokens, string pType) { // this->AST.push_back((shared_ptr<Node>)
                                     // make_shared<Literal>(move(CHILD_NODE)));
  // cout << tokens[tokens.size() - 1][0] << endl;

  for (int i = 0; i < tokens.size(); i++) {
    vector<string> token = tokens[i];
    if (token[0] == "TYPE" &&
        (tokens[i + 2][0] == "ASSIGN" || tokens[i + 2][0] == "SEMI")) {
      if (tokens[i + 1][0] != "WORD") {
        // error, Identifier must be of type WORD.
        cout << "error, Identifier must be of type WORD." << endl;
        return;
      }
      shared_ptr<variableDeclaration> node = make_shared<variableDeclaration>();
      shared_ptr<Identifier> id = make_shared<Identifier>();
      shared_ptr<Expression> body = make_shared<Expression>();



      id->token = tokens[i + 1];
      node->identifier = move(id);
      node->type = token[1];

      if (tokens[i + 2][0] == "SEMI") {
        node->isDefined = false;
        this->AST.push_back((shared_ptr<Node>)(move(node)));
        i+= 2;
      } else {
        node->isDefined = true;
        int j = i+3;
        vector<vector<string>> tokenBody;
        while (tokens[j][0] != "SEMI") {
          tokenBody.push_back(tokens[j]);
          j++;
        }
        Parser par;
        par.parse(tokenBody, "Expression");
        body->body = (par.AST);
        node->body = move(body);
        this->AST.push_back((shared_ptr<Node>)(move(node)));
        i = j;
      }
    }
    
    
    else if(pType == "Expression" && tokens[i][0] == "WORD" && tokens[i+1][0] == "O-PAREN") {
      shared_ptr<funcCall> node = make_shared<funcCall>();
      shared_ptr<Expression> params = make_shared<Expression>();

      node->name = tokens[i][1];
      int j = i+2;
      vector<vector<string>> tokenBody;

      int parenCount = 1;

      while (parenCount != 0) {
        if(tokens[j][0] == "O-PAREN") {
          parenCount++;
        }else if(tokens[j][0] == "C-PAREN") {
          parenCount--;
        }
        if(parenCount == 0) {
          break;
        }
        tokenBody.push_back(tokens[j]);
        j++;
      }

      Parser par;
      par.parse(tokenBody, "Expression");
      params->body = (par.AST);
      node->params = move(params);
      this->AST.push_back((shared_ptr<Node>)(move(node)));
      i = j;
    }else if(tokens[i][0] == "WORD" && tokens[i+1][0] == "O-PAREN") {
      shared_ptr<funcCall> node = make_shared<funcCall>();
      shared_ptr<Expression> params = make_shared<Expression>();

      node->name = tokens[i][1];
      int j = i+2;
      vector<vector<string>> tokenBody;

      int parenCount = 1;

      while (parenCount != 0) {
        if(tokens[j][0] == "O-PAREN") {
          parenCount++;
        }else if(tokens[j][0] == "C-PAREN") {
          parenCount--;
        }
        if(parenCount == 0) {
          break;
        }
        tokenBody.push_back(tokens[j]);
        j++;
      }

      Parser par;
      par.parse(tokenBody, "Expression");
      params->body = (par.AST);
      node->params = move(params);
      this->AST.push_back((shared_ptr<Node>)(move(node)));
      i = j+1;
    }
    
    else if(token[0] == "COMMA") {
      shared_ptr<seperator> node = make_shared<seperator>();
      this->AST.push_back((shared_ptr<Node>)(move(node)));
    }else if (token[0] == "STRING" || token[0] == "NUMBER") {
      Literal literal = Literal();
      literal.type = token[0];
      literal.value = token[1];

      this->AST.push_back(
          (shared_ptr<Node>)make_shared<Literal>(move(literal)));
    }else {
      cout << "error: unexpected token at" << i << endl;
    }
  }
  return;
}