/***************************************************************************
                          SkillOrder.h 
                             -------------------
    begin                : Thu Nov 19 2003
    copyright            : (C) 2003 by Alex Dribin
    email                : alexliza@netvision.net.il
 ***************************************************************************/
#ifndef SKILL_ORDER_H
#define SKILL_ORDER_H

#include "OrderPrototype.h"

/**
  *@author Alex Dribin
  */
class Reporter;
class AbstractData;

class SkillOrder : public OrderPrototype  {
public: 
	SkillOrder();
	~SkillOrder(){}
  STATUS loadParameters(Parser * parser, vector <AbstractData *>  &parameters, Entity * entity );
  ORDER_STATUS process (Entity * entity, vector <AbstractData *>  &parameters);
    protected:
};

#endif
