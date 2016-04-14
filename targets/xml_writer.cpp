// $Id: xml_writer.cpp,v 1.5 2016/03/18 13:03:56 ist169481 Exp $ -*- c++ -*-
#include <string>
#include "targets/xml_writer.h"
#include "targets/type_checker.h"
#include "ast/all.h"  // automatically generated

//---------------------------------------------------------------------------

void zu::xml_writer::do_sequence_node(cdk::sequence_node * const node, int lvl) {
  os() << std::string(lvl, ' ') << "<sequence_node size='" << node->size() << "'>" << std::endl;
  for (size_t i = 0; i < node->size(); i++) {
    node->node(i)->accept(this, lvl + 2);
  }
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_integer_node(cdk::integer_node * const node, int lvl) {
  processSimple(node, lvl);
}

void zu::xml_writer::do_double_node(cdk::double_node * const node, int lvl){
  processSimple(node, lvl);
}

void zu::xml_writer::do_string_node(cdk::string_node * const node, int lvl) {
  processSimple(node, lvl);
}

//---------------------------------------------------------------------------

inline void zu::xml_writer::processUnaryExpression(cdk::unary_expression_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void zu::xml_writer::do_neg_node(cdk::neg_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

void zu::xml_writer::do_simetry_node(zu::simetry_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}
void zu::xml_writer::do_not_node(zu::not_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}
void zu::xml_writer::do_identity_node(zu::identity_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}
void zu::xml_writer::do_position_node(zu::position_node * const node, int lvl) {
  processUnaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_and_node(zu::and_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_or_node(zu::or_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_allocation_node(zu::allocation_node * const node, int lvl)  {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  if(node->size() != NULL) {
    openTag("size", lvl + 2);
    node->size()->accept(this, lvl + 4);
    closeTag("size", lvl + 2);
  }
  closeTag(node, lvl);
}
void zu::xml_writer::do_index_node(zu::index_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  if(node->lvalue() != NULL) {
    openTag("lvalue", lvl + 2);
    node->lvalue()->accept(this, lvl + 4);
    closeTag("lvalue", lvl + 2);
  }
  if(node->rvalue() != NULL) {
    openTag("rvalue", lvl + 2);
    node->rvalue()->accept(this, lvl + 4);
    closeTag("rvalue", lvl + 2);
  }
  closeTag(node, lvl);
}

void zu::xml_writer::do_id_node(zu::id_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  os() << std::string(lvl + 2, ' ') << "<" << node->name() << ">" << node->identifier() << "</" << node->name() << ">" << std::endl;
  closeTag(node, lvl);
}

void zu::xml_writer::do_variable_node(zu::variable_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  os() << std::string(lvl + 2, ' ') << "<" << node->name() << ">" << node->identifier() << "</" << node->name() << ">" << std::endl;
  ProcessZuType(node->zu_type(), lvl + 2);
  os() << std::string(lvl + 2, ' ') << "<isPublic>" << node->isPublic() << "</isPublic>" << std::endl;
  os() << std::string(lvl + 2, ' ') << "<isImported>" << node->isImported() << "</isImported>" << std::endl;
  if(node->value() != NULL) {
    openTag("value", lvl + 2);
    node->value()->accept(this, lvl + 4);
    closeTag("value", lvl + 2);
  }
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

inline void zu::xml_writer::processBinaryExpression(cdk::binary_expression_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->left()->accept(this, lvl + 2);
  node->right()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void zu::xml_writer::do_add_node(cdk::add_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_sub_node(cdk::sub_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_mul_node(cdk::mul_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_div_node(cdk::div_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_mod_node(cdk::mod_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_lt_node(cdk::lt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_le_node(cdk::le_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_ge_node(cdk::ge_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_gt_node(cdk::gt_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_ne_node(cdk::ne_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}
void zu::xml_writer::do_eq_node(cdk::eq_node * const node, int lvl) {
  processBinaryExpression(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_rvalue_node(zu::rvalue_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 4);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_lvalue_node(zu::lvalue_node * const node, int lvl) {
	// ABSTRACT
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_assignment_node(zu::assignment_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->lvalue()->accept(this, lvl + 2);
  openTag("rvalue", lvl + 2);
  node->rvalue()->accept(this, lvl + 4);
  closeTag("rvalue", lvl + 2);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_function_declaration_node(zu::function_declaration_node * const node, int lvl){
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  os() << std::string(lvl + 2, ' ') << "<" << node->name() << ">" << node->identifier() << "</" << node->name() << ">" << std::endl;
  ProcessZuType(node->zu_type(), lvl + 2);
  if(node->literal() != NULL) {
    openTag("literal", lvl + 2);
    node->literal()->accept(this, lvl + 4);
    closeTag("literal", lvl + 2);
  }
  if(node->args() != NULL) {
    openTag("args", lvl + 2);
    node->args()->accept(this, lvl + 4);
    closeTag("args", lvl + 2);
  }
  os() << std::string(lvl + 2, ' ') << "<isPublic>" << node->isPublic() << "</isPublic>" << std::endl;
  os() << std::string(lvl + 2, ' ') << "<isImported>" << node->isImported() << "</isImported>" << std::endl;
  closeTag(node, lvl);
}
void zu::xml_writer::do_function_body_node(zu::function_body_node * const node, int lvl){
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  os() << std::string(lvl + 2, ' ') << "<" << node->name() << ">" << node->identifier() << "</" << node->name() << ">" << std::endl;
  ProcessZuType(node->zu_type(), lvl + 2);
  if(node->literal() != NULL) {
    openTag("literal", lvl + 2);
    node->literal()->accept(this, lvl + 4);
    closeTag("literal", lvl + 2);
  }
  if(node->args() != NULL) {
    openTag("args", lvl + 2);
    node->args()->accept(this, lvl + 4);
    closeTag("args", lvl + 2);
  }
  if(node->block() != NULL) {
    openTag("block", lvl + 2);
    node->block()->accept(this, lvl + 4);
    closeTag("block", lvl + 2);
  }
  os() << std::string(lvl + 2, ' ') << "<isPublic>" << node->isPublic() << "</isPublic>" << std::endl;
  os() << std::string(lvl + 2, ' ') << "<isImported>" << node->isImported() << "</isImported>" << std::endl;
  closeTag(node, lvl);
}
void zu::xml_writer::do_function_call_node(zu::function_call_node * const node, int lvl){
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  os() << std::string(lvl + 2, ' ') << "<" << node->name() << ">" << node->identifier() << "</" << node->name() << ">" << std::endl;
  if(node->args() != NULL) {
    openTag("args", lvl + 2);
    node->args()->accept(this, lvl + 4);
    closeTag("args", lvl + 2);
  }
  closeTag(node, lvl);
}
void zu::xml_writer::do_block_node(zu::block_node * const node, int lvl){
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  if(node->declarations() != NULL) {
    openTag("declarations", lvl + 2);
    node->declarations()->accept(this, lvl + 4);
    closeTag("declarations", lvl + 2);
  }
  if(node->instructions() != NULL) {
    openTag("instructions", lvl + 2);
    node->instructions()->accept(this, lvl + 4);
    closeTag("instructions", lvl + 2);
  }
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_evaluation_node(zu::evaluation_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  closeTag(node, lvl);
}

void zu::xml_writer::do_print_node(zu::print_node * const node, int lvl) {
  CHECK_TYPES(_compiler, _symtab, node);
  openTag(node, lvl);
  node->argument()->accept(this, lvl + 2);
  os() << std::string(lvl + 2, ' ') << "<newLine>" << node->newLine() << "</newLine>" << std::endl;
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_read_node(zu::read_node * const node, int lvl) {
  openTag(node, lvl);
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_for_node(zu::for_node * const node, int lvl) {
  openTag(node, lvl);
  if(node->init() != NULL) {
	  openTag("init", lvl + 2);
	  node->init()->accept(this, lvl + 4);
	  closeTag("init", lvl + 2);
  }
  if(node->test() != NULL) {
	  openTag("test", lvl + 2);
	  node->test()->accept(this, lvl + 4);
	  closeTag("test", lvl + 2);
  }
  if(node->step() != NULL) {
	  openTag("step", lvl + 2);
	  node->step()->accept(this, lvl + 4);
	  closeTag("step", lvl + 2);
  }
  if(node->block() != NULL) {
	  openTag("block", lvl + 2);
	  node->block()->accept(this, lvl + 4);
	  closeTag("block", lvl + 2);
  }
  closeTag(node, lvl);
}

//---------------------------------------------------------------------------

void zu::xml_writer::do_if_node(zu::if_node * const node, int lvl) {
  openTag(node, lvl);
  if(node->condition() != NULL) {
	  openTag("condition", lvl + 2);
	  node->condition()->accept(this, lvl + 4);
	  closeTag("condition", lvl + 2);
  }
  if(node->block() != NULL) {
	  openTag("then", lvl + 2);
	  node->block()->accept(this, lvl + 4);
	  closeTag("then", lvl + 2);
  }
  closeTag(node, lvl);
}

void zu::xml_writer::do_if_else_node(zu::if_else_node * const node, int lvl) {
  openTag(node, lvl);
  if(node->condition() != NULL) {
	  openTag("condition", lvl + 2);
	  node->condition()->accept(this, lvl + 4);
	  closeTag("condition", lvl + 2);
  }
  if(node->thenblock() != NULL) {
	  openTag("then", lvl + 2);
	  node->thenblock()->accept(this, lvl + 4);
	  closeTag("then", lvl + 2);
  }
  if(node->elseblock() != NULL) {
	  openTag("else", lvl + 2);
	  node->elseblock()->accept(this, lvl + 4);
	  closeTag("else", lvl + 2);
  }
  closeTag(node, lvl);
}
void zu::xml_writer::do_return_node(zu::return_node * const node, int lvl) {
  openTag(node, lvl);
  closeTag(node, lvl);
}
void zu::xml_writer::do_continue_node(zu::continue_node * const node, int lvl) {
  openTag(node, lvl);
  closeTag(node, lvl);
}
void zu::xml_writer::do_break_node(zu::break_node * const node, int lvl) {
  openTag(node, lvl);
  closeTag(node, lvl);
}
