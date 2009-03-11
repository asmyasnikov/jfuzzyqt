#include "jfuzzyqt.h"
#include "ruleconnectionmethod.h"
#include "ruleconnectionmethodandmin.h"
#include "ruleconnectionmethodormax.h"
#include "fclruletree.h"
#include <QDebug>
#include <QRegExp>
#include <QFile>
#include <QTextStream>

JFuzzyQt::JFuzzyQt(QObject *parent) 
: QObject(parent)
{
}

JFuzzyQt::~JFuzzyQt()
{

}
bool JFuzzyQt::load(QString fileUri)
{
	bool toReturn = false;
	
	/*for( int childNum = 0; childNum < parseTree.getChildCount(); childNum++ ) {
			Tree child = parseTree.getChild(childNum);
			if( debug ) Gpr.debug("Child " + childNum + ":\t" + child + "\tTree:'" + child.toStringTree() + "'");

			// Create a new FunctionBlock
			FunctionBlock functionBlock = new FunctionBlock(fis);

			// Generate fuzzyRuleSet based on tree
			String name = functionBlock.fclTree(child);
			if( debug ) Gpr.debug("FunctionBlock Name: '" + name + "'");
			fis.addFunctionBlock(name, functionBlock);
		}*/

	QFile file(fileUri);
	 if (!file.open(QIODevice::ReadOnly))
	 {
		 QString str = "Unable to open the file (";
		 str.append( fileUri );
		 str.append( ")" ); 
		 qFatal(str.toAscii());
		 return false;
	 }
	QRegExp rxFunctionBlock("FUNCTION_BLOCK\\s+(\\w+)");
	QRegExp rxFunctionBlockEnd("END_FUNCTION_BLOCK");

	QRegExp rxVarInput("VAR_INPUT");
	QRegExp rxVarOutput("VAR_OUTPUT");
	QRegExp rxFuziffy("FUZZIFY\\s+(\\w+)");
	QRegExp rxDefuzzify("DEFUZZIFY\\s+(\\w+)");
	QRegExp rxRulleBlock("RULEBLOCK\\s+(\\w+)");
    
	QTextStream in(&file);
	QString line = in.readLine();

	FunctBlock functionBlock(NULL);

	while (!line.isNull()) { ///<File Cycle (only works for one function block
		
		if (rxFunctionBlock.indexIn(line) > -1) //If Function Block
		{
			//output.append( rxFunctionBlock.cap(1) );
			functionBlock.setName(rxFunctionBlock.cap(1));
			
			line = in.readLine();

			while (!line.isNull())
			{
				if (rxVarInput.indexIn(line) > -1) 
				{
					///< Input variable block
					loadVarInput(in,functionBlock);
				}
				else if ( rxVarOutput.indexIn(line) > -1 )
				{
					///< Output Variable block
					loadVarOutput(in,functionBlock);
				}
				else if (rxDefuzzify.indexIn(line) > -1) 
				{
					///< Defuzzify block
					QString varName= rxDefuzzify.cap(1);
					loadDefuzzify(in,functionBlock,varName);
				}
				else if (rxFuziffy.indexIn(line) > -1) 
				{
					///< Fuzzify block
					loadFuzzify(in, functionBlock, rxFuziffy.cap(1));
				}
				else if (rxRulleBlock.indexIn(line) > -1) 
				{
					///< Rule block
					loadRuleBlock(in, functionBlock, rxRulleBlock.cap(1));
				}
				else if (rxFunctionBlockEnd.indexIn(line) > -1)
				{
					///< End of Function block
					this->addFunctionBlock(functionBlock);
					break;
				}
				line = in.readLine();
			}
		}//END If Function Block
		line = in.readLine();
	} //END File Cycle
	qDebug() << "FIM FICHEIRO \n\n";
	
	return toReturn;
}
void JFuzzyQt::loadVarInput(QTextStream& in, FunctBlock& funcBlock)
{
	QRegExp rxlen("(\\w+)\\s*:\\s*(\\w+)");
	QRegExp rxOut("END_VAR");

	QString line = in.readLine();
	while (!line.isNull()) {
		if (rxlen.indexIn(line) > -1) 
		{
			//output.append( rxlen.cap(1) );
			//output.append( ":" );
			//output.append( rxlen.cap(2) ); 
			//output.append( ";\n" );
			Variable v( rxlen.cap(1) );
			funcBlock.addVariable(v.getName(),v);
		}else if (rxOut.indexIn(line) > -1) 
		{
			//output.append( "}\n" );
			break;
		}
		line = in.readLine();
		line = line.toLower();
	} 
}
void JFuzzyQt::loadVarOutput(QTextStream& in, FunctBlock& funcBlock)
{
	QRegExp rxlen("(\\w+)\\s*:\\s*(\\w+)");
	QRegExp rxOut("END_VAR");

	QString line = in.readLine();
	while (!line.isNull()) {
		if (rxlen.indexIn(line) > -1) 
		{
			//output.append( rxlen.cap(1) );
			//output.append( ":" );
			//output.append( rxlen.cap(2) );
			//output.append( ";\n" );
			Variable v( rxlen.cap(1) );
			funcBlock.addVariable(v.getName(),v);
		}
		if (rxOut.indexIn(line) > -1) 
		{
			//output.append( "}\n" );
			break;
		}
		line = in.readLine();
	} 
}
void JFuzzyQt::loadFuzzify(QTextStream& in, FunctBlock& funcBlock, QString name)
{
	QRegExp rxOut("END_FUZZIFY");
	QRegExp rxExtra("TERM\\s+(\\w+)\\s*:=(.+);");

	QString line = in.readLine();
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
		}else if (rxOut.indexIn(line) > -1) 
		{
			break;
		}
		line = in.readLine();
		line = line.toLower();
	}
}
void JFuzzyQt::loadDefuzzify(QTextStream& in, FunctBlock& funcBlock, QString varName)
{
	QString defuzzificationMethodType = "COG";

	QRegExp rxOut("END_DEFUZZIFY");
	QRegExp rxMethod("METHOD\\s*:\\s*(\\w+)");
	QRegExp rxDefault("DEFAULT\\s*:=\\s*(\\w+)");
	QRegExp rxExtra("TERM\\s+(\\w+)\\s*:=(.+);");

	QString line = in.readLine();

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
		line = in.readLine();
		line = line.toLower();
	}
}
void JFuzzyQt::loadRuleBlock(QTextStream& in, FunctBlock& funcBlock, QString name)
{
	QString line = in.readLine();
	///<RULEBLOCK content
	QRegExp rxlen("RULE\\s+(\\w+)\\s*:\\s*(\\w+[\\s+|\\w+]*)\\s*;");
	QRegExp rxOut("END_RULEBLOCK");
	QRegExp rxAND("AND\\s*:\\s*(\\w+)");
	QRegExp rxACT("ACT\\s*:\\s*(\\w+)");
	QRegExp rxACCU("ACCU\\s*:\\s*(\\w+)");

	RuleConnectionMethod *and = new RuleConnectionMethodAndMin(), *or = new RuleConnectionMethodOrMax();
	QString ruleAccumulationMethodType = "SUM";

	RuleBlock ruleBlock(name);

	while (!line.isNull()) {

		if (rxlen.indexIn(line) > -1) 
		{	
			//RuleBlock ruleBlock(rxlen.cap(1));
			///<"And" and "or" must be deffined before
			//ruleBlock.loadFrom(rxlen.cap(2));
			loadRule(funcBlock, rxlen.cap(2), rxlen.cap(1)); ///< May need pointer to var 'and' or 'or'
			funcBlock.addRuleBlock(ruleBlock);
		}
		if (rxOut.indexIn(line) > -1) 
		{
			break;
		}
		if (rxAND.indexIn(line) > -1) 
		{
			/*output.append( "and(");
			output.append( rxAND.cap(1) );
			output.append( "}\n" );*/
		}
		if (rxACT.indexIn(line) > -1) 
		{
			/*output.append( "act(");
			output.append( rxACT.cap(1) );
			output.append( "}\n" );*/
		}
		if (rxACCU.indexIn(line) > -1) 
		{
			/*output.append( "accu(");
			output.append( rxACCU.cap(1) );
			output.append( "}\n" );*/
		}

		line = in.readLine();
		line = line.toLower();
	} 

}

void JFuzzyQt::loadRule(FunctBlock& funcBlock, QString &rule, QString name)
{
	QRegExp rxIF("IF\\s+(\\w+[\\s+|\\w+]*)\\s*THEN");
	QRegExp rxTHEN ("THEN\\s+(\\w+)\\s+IS\\s+(\\w+)\\s*");

	Rule fuzzyRule(NULL,name);
	fuzzyRule.addAntecedents( &loadRuleIf(funcBlock,rxIF.cap(0)));
	Variable *v = funcBlock.getVariable(rxTHEN.cap(1));
	RuleTerm rt(v,rxTHEN.cap(2),false);
	fuzzyRule.addConsequent(rt);
}
RuleExpression JFuzzyQt::loadRuleIf(FunctBlock& funcBlock, QString &ruleif)
{
	qDebug() << "[JFuzzyQt::loadRuleIF]:no implemented!!";
	FCLRuleTree tree(NULL);
	tree.addExpression(ruleif);
	
	return RuleExpression(NULL);
}
bool JFuzzyQt::addFunctionBlock(FunctBlock functionBlock)
{
	bool toReturn = false;
	if ( !this->functionBlocks.contains( functionBlock.getName() ))
	{
		this->functionBlocks.insert(functionBlock.getName(),functionBlock);
		toReturn = true;
	}
	if ( this->defaultBlockName == "" )
	{
		this->defaultBlockName = functionBlock.getName();
	}
	return toReturn;
}

/*! \brief Sets var from default functions block inserted
*
*/
void JFuzzyQt::setVariable(QString varName, double value)
{
	if( functionBlocks.size() > 0 )
	{
		qWarning("Only one function block is supported");
		this->functionBlocks[ this->defaultBlockName ].setValue(varName,value);
	}
	else
	{
			qWarning("There are no FunctionBlocks");
	}
}
void JFuzzyQt::evaluate()
{
	if( functionBlocks.size() > 0 )
	{
		qWarning("Only one function block is supported");
		this->functionBlocks[ this->defaultBlockName ].evaluate();
	}
	else
	{
			qWarning("There are no FunctionBlocks");
	}
}
double JFuzzyQt::getValue(QString varName)
{
	if( functionBlocks.size() > 0 )
	{
		qWarning("Only one function block is supported");
		return this->functionBlocks[ this->defaultBlockName ].getValue(varName);
	}
	else
	{
		qWarning("There are no FunctionBlocks");
	}
	return 0;

}

void JFuzzyQt::debug() const
{
	this->functionBlocks.value(this->defaultBlockName).debug("");
}