class ChargeRuleProcessor
	: RuleProcessor
{
%TypeHeaderCode
	#include <BALL/MOLMEC/COMMON/chargeRuleProcessor.h>
%End
	public:
	ChargeRuleProcessor();
	ChargeRuleProcessor(INIFile&, const String& prefix = "ChargeRules");
	ChargeRuleProcessor(const ChargeRuleProcessor&);
	~ChargeRuleProcessor();
	Processor::Result operator () (Atom&);
%MethodCode
	sipRes = sipCpp->operator () (*a0);
%End
};
