#include "fclrulenode.h"
#include <QDebug>
#include <QRegExp>

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
RuleExpression FCLRuleNode::toRuleExpression(FunctBlock &fb, RuleConnectionMethod *and, RuleConnectionMethod *or)const
{
	RuleExpression re;
		
	if( this->left!=NULL )
	{
		//If it has a left node
		re.addTerm1Expression(&this->left->toRuleExpression(fb,and,or)); //penso estar correcto
	}
	else
	{
		//If it is RuleTerm
		re.addTerm1Rule(&this->toRuleTermLeft(fb)); 
	}
	
	if( this->oper == "and" )
	{
		//If the operator is 'and'
		re.setRuleConnectionMethod(and);
	}
	else
	{
		//If the operator is 'or'
		re.setRuleConnectionMethod(or);
	}
	
	if(this->right!=NULL)
	{

		re.addTerm2Expression(&this->right->toRuleExpression(fb,and,or));
	}
	else
	{
		//If right is NULL -> it is RuleTerm
		re.addTerm2Rule(&this->toRuleTermRight(fb));
	}

	return re;
}
RuleTerm FCLRuleNode::toRuleTermLeft(FunctBlock &fb)const
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
	QRegExp rxMember("(\\w+)\\s+(is not|is)\\s+(\\w+)");
	RuleTerm rt;
	
	if (rxMember.indexIn(this->value1))
	{
		rt.setName( rxMember.cap(3) );
		if(  rxMember.cap(2) == "is" ) 
		{
			rt.setNegated(false);
		}
		else
		{
			rt.setNegated(true);
		}
		rt.setVariable(fb.getVariable( rxMember.cap(1) ));
	}
	else
	{
		qWarning() << "[FCLRuleNode::toRuleTermLeft]: Error reading regular expression";
	}

	qDebug()<< "[FCLRuleNode::toRuleTermLeft]: " << this->value1;
	return rt;
}
RuleTerm FCLRuleNode::toRuleTermRight(FunctBlock &fb)const
{
	qDebug()<< "[FCLRuleNode::toRuleTermRight]: " << this->value2;
	QRegExp rxMember("(\\w+)\\s+(is not|is)\\s+(\\w+)");
	RuleTerm rt;
	
	if (rxMember.indexIn(this->value2))
	{
		rt.setName( rxMember.cap(3) );
		if(  rxMember.cap(2) == "is" ) 
		{
			rt.setNegated(false);
		}
		else
		{
			rt.setNegated(true);
		}
		rt.setVariable(fb.getVariable( rxMember.cap(1) ));
	}
	else
	{
		qWarning() << "[FCLRuleNode::toRuleTermLeft]: Error reading regular expression";
	}
	return rt;
}
