/***************************************************************************
                          StanceElement.h  -  description
                             -------------------
    begin                : Fri Jan 10 2003
    copyright            : (C) 2003 by Alex Dribin
    email                : alexliza@netvision.net.il
 ***************************************************************************/

#ifndef STANCE_ELEMENT_H
#define STANCE_ELEMENT_H

#include   <vector>
#include "Element.h"
//class StanceVariety;
#include "StanceVariety.h"

typedef  Element2<StanceVariety,Entity *> StanceElement;
typedef vector<StanceElement>::iterator StanceIterator;

#endif
