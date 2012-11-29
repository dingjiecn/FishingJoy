//
//  Fish.h
//  FishingJoy
//
//  Created by jie ding on 11/28/12.
//
//

#ifndef __FishingJoy__Fish__
#define __FishingJoy__Fish__

#include <iostream>
#include "cocos2d.h"

class GameLayer;

class Fish : public cocos2d::CCObject
{
public:
    virtual ~Fish();
    static Fish *createWithFishType(int fishType, GameLayer *gameLayer);
    CC_SYNTHESIZE(GameLayer *, m_pGameLayer, GameLayer);
    CC_SYNTHESIZE(int, m_nFishType, FishType);
    CC_SYNTHESIZE(cocos2d::CCSprite *, m_pSprite, Sprite);
private:
    bool initWithFishType(int fishType, GameLayer *gameLayer);
    void removeSelf();
    void getPathAndRotation(cocos2d::CCMoveTo *&moveto, float &rotation);

};

#endif /* defined(__FishingJoy__Fish__) */
