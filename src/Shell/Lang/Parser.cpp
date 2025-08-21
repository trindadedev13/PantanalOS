#include "Pantanal/Shell/Lang/Parser.hpp"

#include "Pantanal/Asm.hpp"
#include "Pantanal/Kernel/Kernel.hpp"
#include "Pantanal/Std/Vec.hpp"
#include "Pantanal/Std/SharedPtr.hpp"
#include "Pantanal/Std/Optional.hpp"
#include "Pantanal/Shell/Lang/Ast.hpp"
#include "Pantanal/Shell/Lang/Lexer.hpp"

#define PARSER_ERROR(msg) \
    do { \
        Kernel::terminal.printf("Parsing error in " + std::String(__func__) + ": ", Graphics::Color::Red); \
        Kernel::terminal.println(msg); \
        Asm::hlt(); \
    } while(0)

namespace Pantanal {
  namespace Shell {
    namespace Lang {
      Parser::Parser(const std::Vec<Token>& t) : tokens(t), pos(0) { }
      Parser::~Parser() { }

      std::Vec<std::SharedPtr<ASTNode>> Parser::parse() {
        std::Vec<std::SharedPtr<ASTNode>> nodes;
        while (current().type != Token::Unknown) {
          auto node = parseToken(current());
          if (!node) break;
          nodes.push(node.value());
        }
        return nodes;
      }

      std::Optional<std::SharedPtr<ASTNode>> Parser::parseToken(Token token) {
        if (token.type == Token::Keyword && token.value == "def") {
          auto func = parseFunction();
          if (!func) return {};
          return std::SharedPtr<ASTNode>(new FunctionNode(*func));
        }

        if (token.type == Token::Identifier && next().type == Token::LParen) {
          auto call = parseCall();
          if (!call) return {};
          return std::SharedPtr<ASTNode>(new CallNode(*call));
        }

        PARSER_ERROR("Unexpected token");
        return {};
      }

      std::Optional<FunctionNode> Parser::parseFunction() {
        consume(Token::Keyword);

        auto idToken = consume(Token::Identifier);
        if (!idToken) {
          PARSER_ERROR("Expected Identifier after 'def' keyword.");
          return {};
        }

        if (!consume(Token::LParen)) {
          PARSER_ERROR("Expected Left Parentesis after function identifier.");
          return {};
        }

        std::Vec<std::String> params;
        while (current().type != Token::RParen && current().type != Token::Unknown) {
          auto p = consume(Token::Identifier);
          if (!p) {
            PARSER_ERROR("Expected identifier after " + std::String(((tokens[pos-1].type == Token::Comma) ? "Comma" : "Left Parentesis")));
            return {};
          }
          params.push(p->value);
          if (current().type == Token::Comma) advance();
        }

        if (!consume(Token::RParen)) {
          PARSER_ERROR("Expected Right Parentesis after " + std::String(((tokens[pos-1].type == Token::Identifier) ? "Params" : "Left Parentesis")));
          return {};
        }

        std::Vec<std::SharedPtr<ASTNode>> body;
        while (!(current().type == Token::Keyword && current().value == "end") &&
               current().type != Token::Unknown) {
          auto node = parseToken(current());
          if (!node) return {};
          body.push(node.value());
        }

        if (!(current().type == Token::Keyword && current().value == "end")) return {};
        advance();

        return FunctionNode{idToken->value, params, body};
      }

      std::Optional<CallNode> Parser::parseCall() {
        auto idToken = consume(Token::Identifier);

        if (!consume(Token::LParen)) {
          PARSER_ERROR("Invalid function call: Expect left parentesis after function name");
          return {};
        }

        std::Vec<std::SharedPtr<ASTNode>> args;
        while (current().type != Token::RParen && current().type != Token::Unknown) {
          auto t = consume(Token::Identifier);
          if (!t) {
            PARSER_ERROR("Expected identifier after " + std::String(((tokens[pos-1].type == Token::Comma) ? "Comma" : "Left Parentesis")));
            return {};
          }
          args.push(std::SharedPtr<ASTNode>(new LiteralNode{t->value}));
          if (current().type == Token::Comma) advance();
        }

        if (!consume(Token::RParen)) {
          PARSER_ERROR("Expected Right Parentesis after " + std::String(((tokens[pos-1].type == Token::Identifier) ? "Params" : "Left Parentesis")));
          return {};
        }

        return CallNode{idToken->value, args};
      }

      Token Parser::current() const {
        return (pos >= tokens.size()) ? Token() : tokens[pos];
      }

      Token Parser::next() const {
        return (pos + 1 >= tokens.size()) ? Token() : tokens[pos + 1];
      }

      Token Parser::advance() {
        return (++pos >= tokens.size()) ? Token() : tokens[pos];
      }

      std::Optional<Token> Parser::consume(Token::Type type) {
        Token t = current();
        if (t.type != type) return {};
        advance();
        return t;
      }
    }
  }
}