/***************************************************************************
                          ResourceCompetitiveRequest.cpp 
                             -------------------
    begin                : Fri Apr 18 2003
    copyright            : (C) 2003 by Alex Dribin
    email                : alexliza@netvision.net.il
 ***************************************************************************/
#include "ResourceCompetitiveRequest.h"
#include "ItemElement.h"
#include "AbstractData.h"
#include "UnitEntity.h"
#include "LocationEntity.h"
#include "BinaryPattern.h"
#include "ConstructionEntity.h"
extern Reporter * harvestReporter;

ResourceCompetitiveRequest::ResourceCompetitiveRequest(UnitEntity * unit,
        OrderLine * orderId, ItemRule * resource,  RationalNumber& amount)
                                    :BasicCompetitiveRequest(unit, orderId)
{
   resourceType_ = resource;
  amount_ = amount;  
}



ResourceCompetitiveRequest::~ResourceCompetitiveRequest()
{
}


RationalNumber ResourceCompetitiveRequest::getValue() const
{
  return amount_;
}

//ItemElement * ResourceCompetitiveRequest::getResource() const
//{
//  return resource_;
//}
//

AbstractData * ResourceCompetitiveRequest::getType() const
{
    return resourceType_;
}



RationalNumber ResourceCompetitiveRequest::getTotalAvailableValue() const
{
    return unit_->getLocation()->getAvailableResource(resourceType_);
}



void ResourceCompetitiveRequest::answerRequest(RationalNumber& answer)
{
    RationalNumber bonus = 0;
   if(answer <  amount_)
   {
    // Building effect on harvesting
    ConstructionEntity * containingConstruction = unit_->getContainingConstruction();
    if(containingConstruction)
    {
      bonus = containingConstruction->useProductionBonus(resourceType_, amount_-answer);
    }
   }





  unit_->getLocation()->harvestResource(resourceType_, answer);
  RationalNumber hadBefore = unit_->getItemAmount(resourceType_);
  unit_->addToInventory(resourceType_, answer);
  RationalNumber nowHas = hadBefore + answer + bonus;
  int added = nowHas.getValue() - hadBefore.getValue();

  if(added !=0)
  {
//  cout << unit_->print()<<" harvests " << answer << " "
// << resourceType_->print() << " at "<<  unit_->getLocation()->print() <<endl;
//QQQ
  unit_->addReport(
    new BinaryPattern(harvestReporter, unit_,
    new ItemElement(resourceType_,added)) );
  unit_->getLocation()->addReport(
    new BinaryPattern(harvestReporter, unit_,
    new ItemElement(resourceType_,added))
        /*, 0, observation condition*/);
  }
     orderId_->completeProcessing(unit_,added);
}
