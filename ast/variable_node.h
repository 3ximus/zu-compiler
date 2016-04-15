// $Id: variable_node.h,v 1.3 2016/03/18 12:33:18 ist169481 Exp $
#ifndef __ZU_NODE_EXPRESSION_VARIABLE_H__
#define __ZU_NODE_EXPRESSION_VARIABLE_H__

#include "lvalue_node.h"
#include <string>

namespace zu {

  /**
   * Class for describing syntactic tree leaves for holding lvalues.
   */
  class variable_node: public zu::lvalue_node {
	cdk::basic_type *_type;
	std::string _name;
	bool _isPublic;

  public:
    inline variable_node(int lineno, cdk::basic_type *type, const char *s, bool isPublic) :
        zu::lvalue_node(lineno), _type(type), _name(s), _isPublic(isPublic) {
    }
    inline variable_node(int linenoint lineno, cdk::basic_type *type, const std::string &s, bool isPublic) :
        zu::lvalue_node(lineno), _type(type), _name(s), _isPublic(isPublic) {
    }
    inline variable_node(int lineno, cdk::basic_type *type, const std::string *s, bool isPublic) :
        zu::lvalue_node(lineno), _type(type), _name(*s), _isPublic(isPublic) {
    }
    inline variable_node(int lineno) :
        zu::lvalue_node(lineno) {
    }

  public:
  	inline cdk::basic_type type() {
		return _type;
	}

    inline std::string name() {
      return _name;
    }

	inline bool isPublic() {
		return _isPublic;
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
