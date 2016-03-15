// $Id: basic_ast_visitor.h,v 1.1 2016/02/19 19:29:48 david Exp $ -*- c++ -*-
#ifndef __ZU_BASIC_AST_VISITOR_H__
#define __ZU_BASIC_AST_VISITOR_H__

#include <string>
#include <memory>
#include <iostream>
#include <cdk/compiler.h>

/* include node forward declarations */
#define __NODE_DECLARATIONS_ONLY__
#include "ast/all.h"  // automatically generated
#undef __NODE_DECLARATIONS_ONLY__

//!
//! Print nodes as XML elements to the output stream.
//!
class basic_ast_visitor {
protected:
  //! The owner compiler
  std::shared_ptr<cdk::compiler> _compiler;

protected:
  basic_ast_visitor(std::shared_ptr<cdk::compiler> compiler) :
      _compiler(compiler) {
  }

  inline bool debug() {
    return _compiler->debug();
  }

  inline std::ostream &os() {
    return *_compiler->ostream();
  }

public:
  virtual ~basic_ast_visitor() {
  }

public:
  // CDK nodes (general)
  virtual void do_nil_node(cdk::nil_node * const node, int lvl) {
    // Zu does not use this node
  }
  virtual void do_data_node(cdk::data_node * const node, int lvl) {
    // Zu does not use this node
  }
  virtual void do_composite_node(cdk::composite_node * const node, int lvl) {
    // Zu does not use this node
  }
  virtual void do_sequence_node(cdk::sequence_node * const node, int lvl) = 0;

public:
  virtual void do_integer_node(cdk::integer_node * const node, int lvl) = 0;
  virtual void do_double_node(cdk::double_node * const node, int lvl) 	= 0;
  virtual void do_string_node(cdk::string_node * const node, int lvl) 	= 0;
  virtual void do_identifier_node(cdk::identifier_node * const node, int lvl) {
    // Zu does not use this node
  }


public:
  virtual void do_neg_node(cdk::neg_node * const node, int lvl) = 0;
  virtual void do_simetry_node(zu::simetry_node * const node, int lvl) = 0;
  virtual void do_reference_node(zu::reference_node * const node, int lvl) = 0;
  virtual void do_identity_node(zu::identity_node * const node, int lvl) = 0;
  virtual void do_priority_node(zu::priority_node * const node, int lvl) = 0;

public:
  virtual void do_and_node(zu::and_node * const node, int lvl) = 0;
  virtual void do_or_node(zu::or_node * const node, int lvl) = 0;
  virtual void do_allocation_node(zu::allocation_node * const node, int lvl) = 0;
  virtual void do_index_node(zu::index_node * const node, int lvl) = 0;

public:
  virtual void do_add_node(cdk::add_node * const node, int lvl) = 0;
  virtual void do_sub_node(cdk::sub_node * const node, int lvl) = 0;
  virtual void do_mul_node(cdk::mul_node * const node, int lvl) = 0;
  virtual void do_div_node(cdk::div_node * const node, int lvl) = 0;
  virtual void do_mod_node(cdk::mod_node * const node, int lvl) = 0;
  virtual void do_lt_node(cdk::lt_node * const node, int lvl) = 0;
  virtual void do_le_node(cdk::le_node * const node, int lvl) = 0;
  virtual void do_ge_node(cdk::ge_node * const node, int lvl) = 0;
  virtual void do_gt_node(cdk::gt_node * const node, int lvl) = 0;
  virtual void do_ne_node(cdk::ne_node * const node, int lvl) = 0;
  virtual void do_eq_node(cdk::eq_node * const node, int lvl) = 0;

public:
  virtual void do_lvalue_node(zu::lvalue_node * const node, int lvl) = 0;
  virtual void do_rvalue_node(zu::rvalue_node * const node, int lvl) = 0;

public:
  virtual void do_program_node(zu::program_node * const node, int lvl) = 0;
  virtual void do_evaluation_node(zu::evaluation_node * const node, int lvl) = 0;
  virtual void do_print_node(zu::print_node * const node, int lvl) = 0;
  virtual void do_read_node(zu::read_node * const node, int lvl) = 0;
  virtual void do_assignment_node(zu::assignment_node * const node, int lvl) = 0;

public:
  virtual void do_for_node(zu::for_node * const node, int lvl) = 0;
  virtual void do_if_node(zu::if_node * const node, int lvl) = 0;
  virtual void do_if_else_node(zu::if_else_node * const node, int lvl) = 0;

};

#endif
