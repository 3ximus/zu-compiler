// $Id: lvalue_node.h,v 1.2 2016/03/16 22:16:34 ist169481 Exp $
#ifndef __ZU_NODE_EXPRESSION_LEFTVALUE_H__
#define __ZU_NODE_EXPRESSION_LEFTVALUE_H__

#include <cdk/ast/simple_value_node.h>
#include <string>

namespace zu {

  /**
   * Class for describing syntactic tree leaves for holding lvalues.
   */
  class lvalue_node: public cdk::simple_value_node<std::string> {
  public:
    inline lvalue_node(int lineno, const char *s) :
        cdk::simple_value_node<std::string>(lineno, s) {
    }
    inline lvalue_node(int lineno, const std::string &s) :
        cdk::simple_value_node<std::string>(lineno, s) {
    }
    inline lvalue_node(int lineno, const std::string *s) :
        cdk::simple_value_node<std::string>(lineno, *s) {
    }

    inline lvalue_node(int lineno) :
        cdk::simple_value_node<std::string>(lineno, NULL) {
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    virtual void accept(basic_ast_visitor *sp, int level) {
      sp->do_lvalue_node(this, level);
    }

  };

} // zu

#endif
