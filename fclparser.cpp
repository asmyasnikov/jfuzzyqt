#include "fclparser.h"
#include "ruleconnectionmethod.h"
#include "ruleconnectionmethodandmin.h"
#include "ruleconnectionmethodormax.h"
#include "fclruletree.h"
#include "ruleactivationmethodmin.h"
#include "ruleactivationmethodproduct.h"
#include <QRegExp>

FCLParser::FCLParser(): QObject ()
{
}
FCLParser::FCLParser(QObject* parent) : QObject (parent)
{
}
FCLParser::FCLParser(const FCLParser& parser)
{
}
FCLParser::~FCLParser()
{

}
QString FCLParser::readLine(QTextStream &in)
{
	QString str = in.readLine();
	str = str.toLower();
	str.remove(QRegExp("//.*")); ///< remove comments 
	str.replace(QRegExp("\\s*")," "); ///< convert tabs and multiple spaces to single space
	return str;
}
void FCLParser::loadVarInput(QTextStream& in, FunctBlock& funcBlock)
{
	QRegExp rxlen("(\\w+)\\s*:\\s*(\\w+)");
	QRegExp rxOut("END_VAR");

	QString line = readLine(in);
	while (!line.isNull()) {
		if (rxlen.indexIn(line) > -1) 
		{
			Variable v( rxlen.cap(1) );
			funcBlock.addVariable(v.getName(),v);
		}else if (rxOut.indexIn(line) > -1) 
		{
			break;
		}
		line = readLine(in);
	} 
}
void FCLParser::loadVarOutput(QTextStream& in, FunctBlock& funcBlock)
{
	QRegExp rxlen("(\\w+)\\s*:\\s*(\\w+)");
	QRegExp rxOut("END_VAR");

	QString line = readLine(in);
	while (!line.isNull()) {
		if (rxlen.indexIn(line) > -1) 
		{
			Variable v( rxlen.cap(1) );
			funcBlock.addVariable(v.getName(),v);
		}
		if (rxOut.indexIn(line) > -1) 
		{
			break;
		}
		line = readLine(in);
	} 
}
void FCLParser::loadDefuzzify(QTextStream& in, FunctBlock& funcBlock, QString varName)
{
	QString defuzzificationMethodType = "COG";

	QRegExp rxOut("END_DEFUZZIFY");
	QRegExp rxMethod("METHOD\\s*:\\s*(\\w+)");
	QRegExp rxDefault("DEFAULT\\s*:=\\s*(\\w+)");
	QRegExp rxExtra("TERM\\s+(\\w+)\\s*:=(.+);");

	QString line = readLine(in);

	while ( !line.isNull() ) 
	{	
		if ( rxExtra.indexIn(line) > -1)
		{
			Variable v ( rxExtra.cap(1) );
			funcBlock.addVariable( v.getName() , v );
			LinguisticTerm lt;
			lt.setTermName( rxExtra.cap(1) );
			lt.loadFrom( rxExtra.cap(2) );
			funcBlock.setVariable( rxExtra.cap(1) , lt );
		}
		else if (rxOut.indexIn(line) > -1) 
		{
			break;
		}
		else if ( rxMethod.indexIn(line) > -1)
		{
			Defuzzifier* d = funcBlock.createDefuzzifier( rxMethod.cap(1) );
			funcBlock.setDefuzzifier(varName, d);
		}
		else if ( rxDefault.indexIn(line) > -1)
		{
			QString str = rxDefault.cap(1);
			funcBlock.setDefaultValue(varName, str.toDouble() );
		}
		line = readLine(in);
	}
}
void FCLParser::loadFuzzify(QTextStream& in, FunctBlock& funcBlock, QString name)
{
	QRegExp rxOut("END_FUZZIFY");
	QRegExp rxExtra("TERM\\s+(\\w+)\\s*:=(.+);");

	QString line = readLine(in);
	while (!line.isNull()) 
	{
		if ( rxExtra.indexIn(line) > -1)
		{
			Variable v ( rxExtra.cap(1) );
			funcBlock.addVariable( v.getName() , v );
			LinguisticTerm lt;
			lt.setTermName( rxExtra.cap(1) );
			lt.loadFrom( rxExtra.cap(2) );
			funcBlock.setVariable( rxExtra.cap(1) , lt );
		}
		else if (rxOut.indexIn(line) > -1) 
		{
			break;
		}
		line = readLine(in);
	}
}
void FCLParser::loadRuleBlock(QTextStream& in, FunctBlock& funcBlock, QString name)
{
	QString line = readLine(in);
	///<RULEBLOCK content
	QRegExp rxlen("RULE\\s+(\\w+)\\s*:\\s*(\\w+[\\s+|\\w+]*)\\s*;");
	QRegExp rxOut("END_RULEBLOCK");
	QRegExp rxAND("AND\\s*:\\s*(\\w+)");
	QRegExp rxACT("ACT\\s*:\\s*(\\w+)");
	QRegExp rxACCU("ACCU\\s*:\\s*(\\w+)");
	QRegExp rxOR("OR\\s*:\\s*(\\w+)");

	RuleConnectionMethod *and = new RuleConnectionMethodAndMin(), *or = new RuleConnectionMethodOrMax();
	QString ruleAccumulationMethodType = "sum";
	QString type;

	RuleBlock ruleBlock(name);

	while (!line.isNull()) {

		if (rxlen.indexIn(line) > -1) 
		{	
			loadRule(funcBlock, rxlen.cap(2), rxlen.cap(1),and,or); ///< May need pointer to var 'and' or 'or'
			funcBlock.addRuleBlock(ruleBlock);
		}
		else if (rxOut.indexIn(line) > -1) 
		{
			funcBlock.addRuleBlock(ruleBlock);
			break;
		}
		else if (rxAND.indexIn(line) > -1) 
		{
			type = rxAND.cap(1);
			//---
			// Which 'AND' method to use? (Note: We also set 'OR' method accordingly to fulfill DeMorgan's law
			//---
			if( type == "min")  {
				delete and;
				delete or;
				and = new RuleConnectionMethodAndMin();
				or = new RuleConnectionMethodOrMax();
			/*} else if( type == "PROD" ) {
				and = new RuleConnectionMethodAndProduct();
				or = new RuleConnectionMethodOrProbOr();
			} else if( type == "BDIF" ) {
				and = new RuleConnectionMethodAndBoundedDif();
				or = new RuleConnectionMethodOrBoundedSum();*/
			}
			else
			{
				qWarning()<<"Unknown (or unimplemented) 'AND' method: "<<type;
			}
		}
		else if (rxACT.indexIn(line) > -1) 
		{
			type = rxACT.cap(1);
			if( type == "min")
			{
				ruleBlock.addRuleActivationMethod (new RuleActivationMethodMin(NULL));
			}
			else if( type=="prod" )
			{
				ruleBlock.addRuleActivationMethod (new RuleActivationMethodProduct(NULL));
			}
			else
			{
				qWarning()<<"Unknown (or unimplemented) 'ACT' method: "<<type;
			}
		}
		else if (rxACCU.indexIn(line) > -1) 
		{
			ruleAccumulationMethodType = rxACCU.cap(1);
		}
		else if ( rxOR.indexIn(line)> -1 )
		{
			//---
			// Which 'OR' method to use? (Note: We also set 'OR' method accordingly to fulfill DeMorgan's law
			//---
			type = rxOR.cap(1);
			if( type == "max" ) {
				delete and;
				delete or;
				or = new RuleConnectionMethodOrMax();
				and = new RuleConnectionMethodAndMin();
			/*} else if( type.equalsIgnoreCase("asum") ) {
				or = new RuleConnectionMethodOrProbOr();
				and = new RuleConnectionMethodAndProduct();
			} else if( type.equalsIgnoreCase("bsum") ) {
				or = new RuleConnectionMethodOrBoundedSum();
				and = new RuleConnectionMethodAndBoundedDif();
			*/
			}else{
				qWarning()<<"Unknown (or unimplemented) 'OR' method: "<<type;
			}
		}
		line = readLine(in);
	} 

}
void FCLParser::loadRule(FunctBlock& funcBlock, QString &rule, QString name,RuleConnectionMethod *and, RuleConnectionMethod *or)
{
	QRegExp rxIF("IF\\s+(\\w+[\\s+|\\w+]*)\\s*THEN");
	QRegExp rxTHEN ("THEN\\s+(\\w+)\\s+IS\\s+(\\w+)\\s*");

	Rule fuzzyRule(NULL,name);
	fuzzyRule.addAntecedents( &loadRuleIf(funcBlock,rxIF.cap(0),and,or));
	Variable *v = funcBlock.getVariable(rxTHEN.cap(1));
	RuleTerm rt(NULL, v, rxTHEN.cap(2), false);
	fuzzyRule.addConsequent(rt);
}
RuleExpression FCLParser::loadRuleIf(FunctBlock& funcBlock, QString &ruleif,RuleConnectionMethod *and, RuleConnectionMethod *or)
{
	FCLRuleTree tree(NULL);
	tree.addExpression(ruleif);
	return tree.getRuleExpression(and, or );
}
void FCLParser::loadFunctBlock(QTextStream &in,FunctBlock& funcBlock)
{
	QRegExp rxFunctionBlockEnd("END_FUNCTION_BLOCK");

	QRegExp rxVarInput("VAR_INPUT");
	QRegExp rxVarOutput("VAR_OUTPUT");
	QRegExp rxFuziffy("FUZZIFY\\s+(\\w+)");
	QRegExp rxDefuzzify("DEFUZZIFY\\s+(\\w+)");
	QRegExp rxRulleBlock("RULEBLOCK\\s+(\\w+)");

	QString line = readLine(in);
	while (!line.isNull())
	{
		if (rxVarInput.indexIn(line) > -1) 
		{
			loadVarInput(in,funcBlock);///< Input variable block
		}
		else if ( rxVarOutput.indexIn(line) > -1 )
		{
			loadVarOutput(in,funcBlock);///< Output Variable block
		}
		else if (rxDefuzzify.indexIn(line) > -1) 
		{
			loadDefuzzify(in,funcBlock,rxDefuzzify.cap(1));///< Defuzzify block
		}
		else if (rxFuziffy.indexIn(line) > -1) 
		{
			loadFuzzify(in, funcBlock, rxFuziffy.cap(1));///< Fuzzify block
		}
		else if (rxRulleBlock.indexIn(line) > -1) 
		{
			loadRuleBlock(in, funcBlock, rxRulleBlock.cap(1));///< Rule block
		}
		else if (rxFunctionBlockEnd.indexIn(line) > -1)
		{
			return;///< End of Function block
		}
		line = readLine(in);
	}
}