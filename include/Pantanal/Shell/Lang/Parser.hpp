#ifndef __PANTANAL_SHELL_PARSER_HPP__
#define __PANTANAL_SHELL_PARSER_HPP__

#include "Pantanal/types.h"
#include "Pantanal/Std/Vec.hpp"
#include "Pantanal/Std/SharedPtr.hpp"
#include "Pantanal/Std/Optional.hpp"
#include "Pantanal/Shell/Lang/Ast.hpp"
#include "Pantanal/Shell/Lang/Lexer.hpp"

namespace Pantanal {
  namespace Shell {
    namespace Lang {
      class Parser {
        public:
          Parser(const std::Vec<Token>&);
          ~Parser();

          std::Vec<std::SharedPtr<ASTNode>> parse();
        private:
          std::Vec<Token> tokens;
          size_t pos;

          Token current() const;
          Token next() const;
          Token advance();
          std::Optional<Token> consume(Token::Type);

          std::Optional<std::SharedPtr<ASTNode>> parseToken(Token);
          std::Optional<FunctionNode> parseFunction();
          std::Optional<CallNode> parseCall();
      };
    }
  }
}

#endif