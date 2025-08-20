#ifndef __PANTANAL_SHELL_LEXER_HPP__
#define __PANTANAL_SHELL_LEXER_HPP__

#include "Pantanal/types.h"
#include "Pantanal/String.hpp"
#include "Pantanal/Vec.hpp"

namespace Pantanal {
  namespace Shell {
    namespace Lang {

      class Token {
        public:
          enum Type {
            Identifier,  // hello
            Keyword,     // def, end
            LParen,      // (
            RParen,      // )
            Unknown,     // ???
            Eof
          };

          Type type;
          std::String value;

          Token(Type type = Unknown, const std::String& value = "");
      };

      class Lexer {
        public:
          Lexer(const std::String&);

          std::Vec<Token> lex();
          Token nextToken();
        private:
          std::String src;
          size_t pos;
          size_t len;

          char peek() const;
          char advance();
          char next() const;
          void skipWhitespace();
      };
    }
  }
}

#endif