#ifndef __ZU_FUNCTION_CALL_NODE_H__
#define __ZU_FUNCTION_CALL_NODE_H__

#include <string>

namespace zu {

  /**
   * Class function_declaration describing function nodes.
   */
  class function_call_node: public cdk::expression_node {
  protected:
	std::string *_identifier;
    cdk::sequence_node *_args;

  public:
    inline function_call_node(int lineno, const char *s, cdk::sequence_node *args) :
        cdk::expression_node(lineno), _identifier(s), _args(args) {
    }
    inline function_call_node(int lineno, const std::string &s, cdk::sequence_node *args) :
        cdk::expression_node(lineno), _identifier(s), _args(args) {
    }
    inline function_call_node(int lineno, const std::string *s, cdk::sequence_node *args) :
        cdk::expression_node(lineno), _identifier(*s), _args(args) {
    }

  public:

    inline std::string name() {
      return _identifier;
    }

    inline cdk::sequence_node *args() {
      return _args;
    }

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_function_call_node(this, level);
    }

  };

} // zu

#endif
