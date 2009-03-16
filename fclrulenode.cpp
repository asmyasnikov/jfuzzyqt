#include "fclrulenode.h"
#include <QDebug>

FCLRuleNode::FCLRuleNode(QObject *parent, QString oper)
	: QObject(parent)
{
	this->left = NULL;
	this->right = NULL;
	this->oper = oper;
	this->oper=this->oper.toLower();
	if ( this->oper.compare("and")==0 )
	{
		this->priority = 0;
	}else
	{
		this->priority = 1;
	}
}

FCLRuleNode::~FCLRuleNode()
{

}
bool FCLRuleNode::isPriorThen(int priority)
{
	if (this->priority < priority)
	{
		return true;
	}else
	{
		return false;
	}
}
void FCLRuleNode::setLeft(FCLRuleNode* node)
{
	this->left = node;
}
int FCLRuleNode::getPriority()
{
	return this->priority;
}
void FCLRuleNode::setRight(FCLRuleNode* node)
{
	this->right = node;
}
FCLRuleNode* FCLRuleNode::getRight()
{
	return this->right;
}
bool FCLRuleNode::hasRightMember()
{
	if (this->right == NULL)
	{
		return false;
	}else
	{
		return true;
	}
}
QString FCLRuleNode::print()const
{
	QString str;
	str.append("(");
	if( this->left!=NULL )
	{
		str.append(this->left->print());
	}else {
		str.append(this->value1);
	}
	str.append(" ");
	str.append(this->oper.toUpper());
	str.append(" ");
	if(this->right!=NULL)
	{
		str.append(this->right->print());
	}else{
		str.append(this->value2);
	}
	str.append(")");
	return str;
}
void FCLRuleNode::insertLeaveValues(QList<QString> &values)
{
	
	if( this->left!=NULL )
	{
		this->left->insertLeaveValues(values);
	}
	else
	{
		this->value1 = values.takeFirst();
	}

	if(this->right!=NULL)
	{
		this->right->insertLeaveValues(values);
	}
	else
	{
		this->value2 = values.takeFirst();
	}
}
const QString FCLRuleNode::getOperator()const
{
	return this->oper;
}
RuleExpression FCLRuleNode::toRuleExpression(RuleConnectionMethod *and, RuleConnectionMethod *or)const
{
	RuleExpression re;
		
	if( this->left!=NULL )
	{
		re.addTerm1Expression(&this->left->toRuleExpression(and,or)); //penso estar correcto
	}
	else
	{
		re.addTerm1Rule(&this->left->toRuleTerm()); 
	}
	
	if( this->oper == "and" )
	{
		re.setRuleConnectionMethod(and);
	}
	else
	{
		re.setRuleConnectionMethod(or);
	}
	
	if(this->right!=NULL)
	{
		re.addTerm2Expression(&this->right->toRuleExpression(and,or));
	}
	else
	{
		re.addTerm2Rule(&this->right->toRuleTerm());
	}
	return re;
}
RuleTerm FCLRuleNode::toRuleTerm()const
{
	/*
	String varName = tree.getText();
	String lingTerm = tree.getChild(0).getText();
	boolean negate = false;
	if( lingTerm.equalsIgnoreCase("NOT") ) {
		lingTerm = tree.getChild(1).getText();
		negate = true;
	}
	Variable variable = getVariable(varName);
	*/
	
	qDebug()<< "[FCLRuleNode::toRuleTerm]:IN" << this->print();


	RuleTerm rt;

	if (this->value1 != "")
	{
		qDebug() << "[FCLRuleNode::toRuleTerm]:"<<this->value1;
		rt.setName(this->value1);
	}
	else
	{
		rt.setName(this->value2);
		qDebug() << "[FCLRuleNode::toRuleTerm]:"<<this->value2;
	}
	return rt;
}