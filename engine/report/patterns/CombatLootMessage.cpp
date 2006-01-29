/***************************************************************************
                          CombatLootMessage.cpp
                             -------------------
    begin                : Mar 22 2005
    copyright            : (C) 2005 by Alex Dribin
    email                : alexliza@netvision.net.il
 ***************************************************************************/
#include "CombatLootMessage.h"

extern string longtostr(long in);


CombatLootMessage::CombatLootMessage(vector <ItemElement> loot)
{
	loot_ = loot;
}



void CombatLootMessage::printReport(ReportPrinter &out) const
{
	if(loot_.empty())
		out << "No loot";
	else
	{
		out << "Loot: ";
  	for (vector <ItemElement>::const_iterator iter  = loot_.begin();
	 	iter != loot_.end();	  ++iter)
    {
			if(iter != loot_.begin())
				out << ", ";
			out << (*iter).print();
		}
	}
	out <<"."<<endl;
}




