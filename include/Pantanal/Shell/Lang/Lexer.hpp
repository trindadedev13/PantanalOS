#ifndef __PANTANAL_SHELL_LEXER_HPP__
#define __PANTANAL_SHELL_LEXER_HPP__

#include "Pantanal/types.h"
#include "Pantanal/Std/String.hpp"
#include "Pantanal/Std/Vec.hpp"

namespace Pantanal {
  namespace Shell {
    namespace Lang {

      class Token {
        public:
          enum Type {
            Unknown    = -1,     // ???
            Identifier = 0,  // hello
            Keyword    = 1,     // def, end
            LParen     = 2,      // (
            RParen     = 3,      // )
            Comma      = 4,       // ,
            Eof        = 5
          };

          static const std::String typeToString(Type type) {
            switch (type) {
              case Identifier: return "Identifier";
              case Keyword:    return "Keyword";
              case LParen:     return "Left Parenteses";
              case RParen:     return "Right Parenteses";
              case Comma:      return "Comma";
              case Eof:        return "End of File";
              default:         return "Unknown";
            };
          }

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