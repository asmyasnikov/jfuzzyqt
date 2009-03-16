#include "fclparser.h"
#include "ruleconnectionmethod.h"
#include "ruleconnectionmethodandmin.h"
#include "ruleconnectionmethodormax.h"
#include "fclruletree.h"
#include "ruleactivationmethodmin.h"
#include "ruleactivationmethodproduct.h"
#include "ruleaccumulationmethodmax.h"
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
	if(str!=NULL){
		str = str.toLower();
		str.remove(QRegExp("//.*")); ///< remove comments 
		str.replace(QRegExp("\\s+")," "); ///< convert tabs and multiple spaces to single space
		qDebug()<<"[FCLParser::readLine]: "<<str;
	}
	return str;
}
void FCLParser::loadVarInput(QTextStream& in, FunctBlock& funcBlock)
{
	QRegExp rxlen("(\\w+)\\s*:\\s*(\\w+)");
	QRegExp rxOut("end_var");

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
	QRegExp rxOut("end_var");

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
	QString defuzzificationMethodType = "cog";

	QRegExp rxOut("end_defuzzify");
	QRegExp rxMethod("method\\s*:\\s*(\\w+)");
	QRegExp rxDefault("default\\s*:=\\s*(\\w+)");
	QRegExp rxExtra("term\\s+(\\w+)\\s*:=(.+);");

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
	QRegExp rxOut("end_fuzzify");
	QRegExp rxExtra("term\\s+(\\w+)\\s*:=(.+);");

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
	QRegExp rxlen("rule\\s+(\\w+)\\s*:\\s*(\\w+[\\s+|\\w+]*)\\s*;");
	QRegExp rxOut("end_ruleblock");
	QRegExp rxAND("and\\s*:\\s*(\\w+)");
	QRegExp rxACT("act\\s*:\\s*(\\w+)");
	QRegExp rxACCU("accu\\s*:\\s*(\\w+)");
	QRegExp rxOR("or\\s*:\\s*(\\w+)");

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
			ruleBlock.addRuleAccumulationMethod( createAccumulationMethod(ruleAccumulationMethodType) );
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
	QRegExp rxIF("if\\s+(\\w+[\\s+|\\w+]*)\\s+then");
	QRegExp rxTHEN ("then\\s+(\\w+)\\s+is\\s+(\\w+)\\s*");

	Rule fuzzyRule(NULL,name);
	if ( rxIF.indexIn(rule) >-1 && rxTHEN.indexIn(rule))
	{
		RuleExpression re = loadRuleIf(funcBlock,rxIF.cap(1),and,or);
		fuzzyRule.addAntecedents( &re );
		Variable *v = funcBlock.getVariable(rxTHEN.cap(1));
		RuleTerm rt(NULL, v, rxTHEN.cap(2), false);
		fuzzyRule.addConsequent(rt);
	}
	else
	{
		qWarning()<<"Unknown rule "<<rule;
	}
}
RuleExpression FCLParser::loadRuleIf(FunctBlock& funcBlock, QString &ruleif,RuleConnectionMethod *and, RuleConnectionMethod *or)
{
	FCLRuleTree tree(this);	
	tree.addExpression(ruleif);
	return tree.getRuleExpression(and, or );
}
void FCLParser::loadFunctBlock(QTextStream &in,FunctBlock& funcBlock)
{
	QRegExp rxFunctionBlockEnd("end_function_block");

	QRegExp rxVarInput("var_input");
	QRegExp rxVarOutput("var_output");
	QRegExp rxFuziffy("fuzzify\\s+(\\w+)");
	QRegExp rxDefuzzify("defuzzify\\s+(\\w+)");
	QRegExp rxRulleBlock("ruleblock\\s+(\\w+)");

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
RuleAccumulationMethod* FCLParser::createAccumulationMethod(QString type)
{
	RuleAccumulationMethod* ruleAccumulationMethod = NULL;
	if( type == "max" ) 
	{
		ruleAccumulationMethod = new RuleAccumulationMethodMax();
	}
	/*else if( type == "bsum" )
	{
		ruleAccumulationMethod = new RuleAccumulationMethodBoundedSum();
	}
	else if( type == "nsum" )
	{
		ruleAccumulationMethod = new RuleAccumulationMethodNormedSum();
	}
	else if( type == "probor" )
	{
		ruleAccumulationMethod = new RuleAccumulationMethodProbOr();
	}
	else if( type == "sum" )
	{
		ruleAccumulationMethod = new RuleAccumulationMethodSum();
	}*/
	else
	{
		qWarning()<<"Unknown/Unimplemented Rule accumulation method "<<type;
	}
	return ruleAccumulationMethod;
}
