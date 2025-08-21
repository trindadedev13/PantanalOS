#include "Pantanal/Shell/Lang/Lexer.hpp"

#include "Pantanal/char.h"
#include "Pantanal/types.h"
#include "Pantanal/Std/String.hpp"
#include "Pantanal/Std/Vec.hpp"

namespace Pantanal {
  namespace Shell {
    namespace Lang {
      Token::Token(Type t, const std::String& v) : type(t), value(v) {}

      Lexer::Lexer(const std::String& code) : src(code), pos(0), len(code.size()) {}

      char Lexer::peek() const {
        return (pos >= len) ? '\0' : src[pos];
      }

      char Lexer::advance() {
        return (pos >= len) ? '\0' : src[pos++];
      }

      void Lexer::skipWhitespace() {
        while (is_space(peek())) {
          advance();
        }
      }

      std::Vec<Token> Lexer::lex() {
        std::Vec<Token> tokens;
        Token token;
        while ((token = nextToken()).type != Token::Eof) {
          tokens.push(token);
        }
        return tokens;
      }

      Token Lexer::nextToken() {
        skipWhitespace();
        char c = peek();
        if (c == '\0') return Token(Token::Eof, "");

        if (is_alpha(c) || c == '_') {
          std::String word = "";
          while (is_alpha(peek()) || is_digit(peek()) || peek() == '_') {
            word += advance();
          }
          if (word == "def" || word == "end") {
            return Token(Token::Keyword, word);
          }
          return Token(Token::Identifier, word);
        }

        switch (c) {
          case '(': advance(); return Token(Token::LParen, "(");
          case ')': advance(); return Token(Token::RParen, ")");
          case ',': advance(); return Token(Token::Comma, ",");
        }

        advance();
        return Token(Token::Unknown, std::String(c));
      }
    }
  }
}