//
//  Cannon.h
//  FishingJoy
//
//  Created by 胡 蓉 on 12-11-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef FishingJoy_Cannon_h
#define FishingJoy_Cannon_h

#include "cocos2d.h"

class GameLayer;

class Cannon : public cocos2d::CCObject
{
public:
    static Cannon *createWithCannonType(int cannonType, GameLayer *pGameLayer, cocos2d::CCSpriteBatchNode *pBatchNode);
    CC_SYNTHESIZE(int, m_nCannonType, CannonType);
    CC_SYNTHESIZE(cocos2d::CCSprite *, m_pSprite, Sprite);
    CC_PROPERTY(float, m_fRotation, Rotation);
    CC_SYNTHESIZE(GameLayer *, m_pGameLayer, GameLayer);
    CC_SYNTHESIZE(cocos2d::CCPoint, m_ptDirection, Direction);
    void rotateToPoint(cocos2d::CCPoint pt);
    void fire();
private:
    bool initWithCannonType(int cannonType, GameLayer* pGameLayer, cocos2d::CCSpriteBatchNode *pBatchNode);
};

#endif
