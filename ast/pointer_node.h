// $Id: integer_node.h,v 1.3 2014/02/26 18:53:32 david Exp $ -*- c++ -*-
#ifndef __ZU_AST_EXPRESSION_POINTER_H__
#define __ZU_AST_EXPRESSION_POINTER_H__


namespace zu {

  /**
   * Class for describing pointers in zu.
   */
  class pointer_node: public cdk::simple_value_node<int> {
	  cdk::basic_type _type;

  public:
    inline pointer_node(int lineno, int i, cdk::basic_type type) :
        simple_value_node(lineno, i), _type(type) {
    }

    inline cdk::basic_type *type() {
      return _type;
    }

    /**
     * @param sp semantic processor visitor
     * @param level syntactic tree level
     */
    void accept(basic_ast_visitor *sp, int level) {
      sp->do_pointer_node(this, level);
    }

  };

} // zu

#endif
