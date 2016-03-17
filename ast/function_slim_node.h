#ifndef __ZU_FUNCTION_SLIM_NODE_H__
#define __ZU_FUNCTION_SLIM_NODE_H__

#include <string>

namespace zu {

  /**
   * Class function_slim describing function nodes.
   */
  class function_slim_node: public cdk::simple_value_node<std::string> {
    cdk::sequence_node *_args;

  public:
    inline function_slim_node(int lineno, cdk::sequence_node *args, const char *s) :
        cdk::simple_value_node<std::string>(lineno, s), _args(args) {
    }
    inline function_slim_node(int lineno, cdk::sequence_node *args, const std::string &s) :
        cdk::simple_value_node<std::string>(lineno, s), _args(args) {
    }
    inline function_slim_node(int lineno, cdk::sequence_node *args, const std::string *s) :
        cdk::simple_value_node<std::string>(lineno, *s), _args(args) {
    }

  public:
    inline cdk::sequence_node *args() {
      return _args;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_slim_node(this, level);
    }

  };

} // zu

#endif
