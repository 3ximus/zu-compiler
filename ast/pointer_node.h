// $Id: pointer_node.h,v 1.2 2016/03/18 13:03:56 ist169481 Exp $ -*- c++ -*-
#ifndef __ZU_POINTER_H__
#define __ZU_POINTER_H__

namespace zu {

  /**
   * Class for describing pointers in zu.
   */
  class pointer_node: public cdk::simple_value_node<int> {
	  basic_type *_type;

  public:
    inline pointer_node(int lineno, int i, basic_type *type) :
        simple_value_node(lineno, i), _type(type) {
    }

    inline basic_type *type() {
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
