#ifndef LINGUISTICTERM_H
#define LINGUISTICTERM_H

#include <QString>

class MembershipFunction;

class LinguisticTerm
{
public:
	QString termName;///<Terms's name
	MembershipFunction* membershipFunction;///< Membership function 
	
	LinguisticTerm();
	LinguisticTerm(QString& termName, MembershipFunction* membershipFunction);
	~LinguisticTerm();
	
	QString getTermName() const;
	void setTermName(const QString name);
	const MembershipFunction* getMembershipFunction();
	bool loadFrom(QString qString);
	void debug(QString tbs) const;
private:
};

#endif // LINGUISTICTERM_H
