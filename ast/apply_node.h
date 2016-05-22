#ifndef __ZU_APPLY_NODE_H__
#define __ZU_APPLY_NODE_H__

#include <string>

namespace zu {

  /**
   * Class APPLnode
   */
  class apply_node: public cdk::expression_node {
  protected:
	zu::function_call_node *_func;

  public:
    inline apply_node(int lineno, zu::function_call_node *func) :
        cdk::expression_node(lineno), _func(func) {
    }

  public:

    void accept(basic_ast_visitor *sp, int level) {
      sp->do_apply_node(this, level);
    }

  };

} // zu

#endif
