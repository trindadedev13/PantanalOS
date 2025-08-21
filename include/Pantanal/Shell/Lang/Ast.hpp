#ifndef __PANTANAL_SHELL_AST_HPP__
#define __PANTANAL_SHELL_AST_HPP__

#include "Pantanal/Std/String.hpp"
#include "Pantanal/Std/Vec.hpp"
#include "Pantanal/Std/SharedPtr.hpp"
#include "Pantanal/Kernel/Kernel.hpp"

namespace Pantanal {
  namespace Shell {
    namespace Lang {
      struct ASTNode {
        enum class Type {
          Function,
          Call,
          Literal,
        };
        virtual ~ASTNode() = default;
        virtual Type getType() const = 0;
      };
  
      struct FunctionNode : public ASTNode {
        std::String name;
        std::Vec<std::String> params;
        std::Vec<std::SharedPtr<ASTNode>> body;
  
        FunctionNode(): name(""), params(), body() {};
        FunctionNode(
          const std::String& n,
          const std::Vec<std::String>& p,
          const std::Vec<std::SharedPtr<ASTNode>>& b
        ): name(n), params(p), body(b) {}
  
        Type getType() const override { return Type::Function; }
      };
  
      struct CallNode : public ASTNode {
        std::String fnName;
        std::Vec<std::SharedPtr<ASTNode>> params;
  
        CallNode(): fnName(""), params() {}
        CallNode(
          const std::String& fn,
          const std::Vec<std::SharedPtr<ASTNode>>& p
        ): fnName(fn), params(p) {}
  
        Type getType() const override { return Type::Call; }
      };

      struct LiteralNode : public ASTNode {
        std::String value;

        LiteralNode(): value("") {}
        LiteralNode(const std::String& v) : value(v) {}
  
        Type getType() const override { return Type::Literal; }
      };
  
      static inline void printNode(const std::SharedPtr<ASTNode>& node, int indent = 0) {
        auto pad = [&](int n) {
          for (int i = 0; i < n; i++) Kernel::terminal.printf("  ");
        };
  
        switch (node->getType()) {
          case ASTNode::Type::Function: {
            auto fn = static_cast<FunctionNode*>(node.operator->());
            pad(indent);
            Kernel::terminal.printf("Function: " + fn->name + "(");
            for (size_t i = 0; i < fn->params.size(); i++) {
              Kernel::terminal.printf(fn->params[i]);
              if (i + 1 < fn->params.size()) Kernel::terminal.printf(", ");
            }
            Kernel::terminal.println(")");
            pad(indent);
            Kernel::terminal.println("{");
            for (auto& stmt : fn->body) printNode(stmt, indent + 1);
            pad(indent);
            Kernel::terminal.println("}");
            break;
          }
          case ASTNode::Type::Call: {
            auto call = static_cast<CallNode*>(node.operator->());
            pad(indent);
            Kernel::terminal.printf("Call: " + call->fnName + "(");
            for (size_t i = 0; i < call->params.size(); i++) {
              printNode(call->params[i], indent + 1);
              if (i + 1 < call->params.size()) Kernel::terminal.printf(", ");
            }
            Kernel::terminal.println(")");
            break;
          }
          case ASTNode::Type::Literal: {
            auto literal = static_cast<LiteralNode*>(node.operator->());
            pad(indent);
            Kernel::terminal.printf("Literal(" + literal->value + ")");
            break;
          }
        }
      }
    }
  }
}

#endif