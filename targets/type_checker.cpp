// $Id: type_checker.cpp,v 1.5 2016/03/18 13:03:56 ist169481 Exp $ -*- c++ -*-
#include <string>
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

#define ASSERT_UNSPEC \
    { if (node->type() != nullptr && \
          node->type()->name() != basic_type::TYPE_UNSPEC) return; }

//---------------------------------------------------------------------------

void zu::type_checker::do_integer_node(cdk::integer_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void zu::type_checker::do_double_node(cdk::double_node * const node, int lvl) {
	/* TODO */
}

void zu::type_checker::do_string_node(cdk::string_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->type(new basic_type(4, basic_type::TYPE_STRING));
}

//---------------------------------------------------------------------------

inline void zu::type_checker::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
  if (node->argument()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in argument of unary expression");

  // in Zu, expressions are always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void zu::type_checker::do_neg_node(cdk::neg_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

void zu::type_checker::do_simetry_node(zu::simetry_node * const node, int lvl) {/* TODO */}
void zu::type_checker::do_not_node(zu::not_node * const node, int lvl) {/* TODO */}
void zu::type_checker::do_reference_node(zu::reference_node * const node, int lvl) {/* TODO */}
void zu::type_checker::do_identity_node(zu::identity_node * const node, int lvl) {/* TODO */}
void zu::type_checker::do_position_node(zu::position_node * const node, int lvl) {/* TODO */}

//---------------------------------------------------------------------------

void zu::type_checker::do_and_node(zu::and_node * const node, int lvl) {/* TODO */}
void zu::type_checker::do_or_node(zu::or_node * const node, int lvl) {/* TODO */}
void zu::type_checker::do_allocation_node(zu::allocation_node * const node, int lvl)  {/* TODO */}
void zu::type_checker::do_index_node(zu::index_node * const node, int lvl) {/* TODO */}
void zu::type_checker::do_id_node(zu::id_node * const node, int lvl) {/* TODO */}
void zu::type_checker::do_variable_node(zu::variable_node * const node, int lvl) {/* TODO */}

//---------------------------------------------------------------------------

inline void zu::type_checker::processBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
  ASSERT_UNSPEC;
  node->left()->accept(this, lvl + 2);
  if (node->left()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in left argument of binary expression");

  node->right()->accept(this, lvl + 2);
  if (node->right()->type()->name() != basic_type::TYPE_INT)
    throw std::string("wrong type in right argument of binary expression");

  // in Zu, expressions are always int
  node->type(new basic_type(4, basic_type::TYPE_INT));
}

void zu::type_checker::do_add_node(cdk::add_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::type_checker::do_sub_node(cdk::sub_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::type_checker::do_mul_node(cdk::mul_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::type_checker::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::type_checker::do_mod_node(cdk::mod_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::type_checker::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::type_checker::do_le_node(cdk::le_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::type_checker::do_ge_node(cdk::ge_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::type_checker::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::type_checker::do_ne_node(cdk::ne_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::type_checker::do_eq_node(cdk::eq_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void zu::type_checker::do_rvalue_node(zu::rvalue_node * const node, int lvl) {
  node->lvalue()->accept(this, lvl);
  node->type(node->lvalue()->type());
}

//---------------------------------------------------------------------------

void zu::type_checker::do_lvalue_node(zu::lvalue_node * const node, int lvl) {
  //const std::string &id = node->value();
  //std::shared_ptr<zu::symbol> symbol = _symtab.find(id);
  //if (symbol == nullptr) throw id + " undeclared";
  //// hackish stuff...
  //node->type(new basic_type(4, basic_type::TYPE_INT));
}

void zu::type_checker::do_function_declaration_node(zu::function_declaration_node * const node, int lvl){/*TODO*/}
void zu::type_checker::do_function_body_node(zu::function_body_node * const node, int lvl){/*TODO*/}
void zu::type_checker::do_function_call_node(zu::function_call_node * const node, int lvl){/*TODO*/}
//---------------------------------------------------------------------------

void zu::type_checker::do_assignment_node(zu::assignment_node * const node, int lvl) {
  //ASSERT_UNSPEC;

  //// DAVID: horrible hack!
  //// (this is caused by Zu not having explicit variable declarations)
  //const std::string &id = node->lvalue()->value();
  //if (!_symtab.find(id)) {
  //  _symtab.insert(id, std::make_shared<zu::symbol>(new basic_type(4, basic_type::TYPE_INT), id, -1)); // put in the symbol table
  //}

  //node->lvalue()->accept(this, lvl + 2);
  //if (node->lvalue()->type()->name() != basic_type::TYPE_INT)
  //  throw std::string("wrong type in left argument of assignment expression");

  //node->rvalue()->accept(this, lvl + 2);
  //if (node->rvalue()->type()->name() != basic_type::TYPE_INT)
  //  throw std::string("wrong type in right argument of assignment expression");

  //// in Zu, expressions are always int
  //node->type(new basic_type(4, basic_type::TYPE_INT));
}

//---------------------------------------------------------------------------

void zu::type_checker::do_evaluation_node(zu::evaluation_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

void zu::type_checker::do_print_node(zu::print_node * const node, int lvl) {
  node->argument()->accept(this, lvl + 2);
}

//---------------------------------------------------------------------------

void zu::type_checker::do_read_node(zu::read_node * const node, int lvl) {
  //node->argument()->accept(this, lvl + 2);
}

//---------------------------------------------------------------------------

void zu::type_checker::do_for_node(zu::for_node * const node, int lvl) {
  //node->condition()->accept(this, lvl + 4);
}

//---------------------------------------------------------------------------

void zu::type_checker::do_if_node(zu::if_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}

void zu::type_checker::do_if_else_node(zu::if_else_node * const node, int lvl) {
  node->condition()->accept(this, lvl + 4);
}
void zu::type_checker::do_return_node(zu::return_node * const node, int lvl) {/*TODO*/}
void zu::type_checker::do_continue_node(zu::continue_node * const node, int lvl) {/*TODO*/}
void zu::type_checker::do_break_node(zu::break_node * const node, int lvl) {/*TODO*/}
