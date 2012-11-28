//
//  Fish.cpp
//  FishingJoy
//
//  Created by jie ding on 11/28/12.
//
//

#include "Fish.h"


Fish *Fish::createWithFishType(int fishType)
{
    Fish *fish = new Fish();
    if(fish && fish->initWithFishType(fishType))
    {
        fish->initWithFishType(fishType);
        return fish;
    }
    else
    {
        delete fish;
        return NULL;
    }
}

bool Fish::initWithFishType(int fishType)
{
    return false;
}
