/***************************************************************************
                             ChristenOrder.cpp 
                             -------------------
    begin                : Thu Nov 19 2003
    copyright            : (C) 2003 by Alex Dribin
    email                : alexliza@netvision.net.il
 ***************************************************************************/
#include "ChristenOrder.h"
#include "StringData.h"
#include "Entity.h"
#include "UnitEntity.h"
#include "LocationEntity.h"
#include "ConstructionEntity.h"
#include "UnaryPattern.h"
#include "BinaryPattern.h"
#include "TertiaryPattern.h"
#include "EntitiesCollection.h"
extern Reporter *	cannotChristenReporter;
extern Reporter *	publicChristenReporter;
extern Reporter *	privateChristenReporter;

ChristenOrder * instantiateChristenOrder = new ChristenOrder();

ChristenOrder::ChristenOrder(){
  keyword_ = "Christen";
  registerOrder_();
  description = string("CHRISTEN \"structure name\" \n") +
  "Immediate, structure owner only, one-shot.  Executes as soon as you are the\n" +
  "owner of a location, i.e. the first unit listed in the structure.  The name\n" +
  "of the structure is changed to the new string.  Structure names are used only\n" +
  "in the report.  You may also name any location whose name is equal to the\n" +
  "location type, such as castles named \"castle\", or plains named \"plains\".\n";

  orderType_   = IMMEDIATE_ORDER;
}

STATUS ChristenOrder::loadParameters(Parser * parser,
                            vector <AbstractData *>  &parameters, Entity * entity )
{
   if(!entityIsUnit(entity))
            return IO_ERROR;

	if(!parseStringParameter(entity, parser,parameters))
        return IO_ERROR;
    else    
  		return OK;
}



ORDER_STATUS ChristenOrder::process (Entity * entity, vector <AbstractData *>  &parameters)
{
  UnitEntity * unit = dynamic_cast<UnitEntity *>(entity);
  assert(unit);
  string  newName = (parameters[0])->printName();
  ConstructionEntity * construction = unit->getContainingConstruction();
  if(construction)
  	{
  		if(construction->getFaction() != unit->getFaction())
  		{
        entity->addReport(new UnaryPattern(cannotChristenReporter, 
        					new StringData("construction"))); 		
  			return INVALID;
  		}
  		construction->setName(newName);
        entity->addReport(new BinaryPattern(privateChristenReporter, 
        					construction,new StringData(newName))); 		
        construction->getLocation()->addReport(new TertiaryPattern(publicChristenReporter, 
                        entity, construction,new StringData(newName))); 		
  		return SUCCESS;
  	}
  	
  if(unit->getLocation()->getOwner() != unit->getFaction())	
  	{
        entity->addReport(new UnaryPattern(cannotChristenReporter, 
        					new StringData("location"))); 		
  			return INVALID;
  	}
  		unit->getLocation()->setName(newName);
        entity->addReport(new BinaryPattern(privateChristenReporter, 
        					unit->getLocation(),new StringData(newName))); 		
        unit->getLocation()->addReport(new TertiaryPattern(publicChristenReporter, entity,
        					unit->getLocation(),new StringData(newName))); 		
  		return SUCCESS;
  }

