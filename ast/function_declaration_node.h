#ifndef __ZU_FUNCTION_DECLARATION_NODE_H__
#define __ZU_FUNCTION_DECLARATION_NODE_H__

#include <string>

namespace zu {

  /**
   * Class function_declaration describing function nodes.
   */
  class function_declaration_node: public cdk::simple_value_node<std::string> {
    cdk::sequence_node *_args;

  public:
    inline function_declaration_node(int lineno, const char *s, cdk::sequence_node *args) :
        cdk::simple_value_node<std::string>(lineno, s), _args(args) {
    }
    inline function_declaration_node(int lineno, const std::string &s, cdk::sequence_node *args) :
        cdk::simple_value_node<std::string>(lineno, s), _args(args) {
    }
    inline function_declaration_node(int lineno, const std::string *s, cdk::sequence_node *args) :
        cdk::simple_value_node<std::string>(lineno, *s), _args(args) {
    }

  public:
    inline cdk::sequence_node *args() {
      return _args;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_declaration_node(this, level);
    }

  };

} // zu

#endif
