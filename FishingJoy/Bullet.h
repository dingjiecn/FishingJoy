//
//  Bullet.h
//  FishingJoy
//
//  Created by 胡 蓉 on 12-11-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef FishingJoy_Bullet_h
#define FishingJoy_Bullet_h

#include "cocos2d.h"
#include "GameLayer.h"

class Bullet : public cocos2d::CCObject
{
public:
    static Bullet *createWithBulletType(int bulletType, GameLayer *gameLayer, cocos2d::CCSpriteBatchNode *pBatchNodeBullet, cocos2d::CCSpriteBatchNode *pBatchNodeNet);
    CC_SYNTHESIZE(GameLayer *, m_pGameLayer, GameLayer);
    CC_SYNTHESIZE(int, m_nBulletType, BulletType);
    CC_SYNTHESIZE(cocos2d::CCSprite *, m_pSpriteBullet, SpriteBullet);
    CC_SYNTHESIZE(cocos2d::CCSprite *, m_pSpriteNet, SpriteNet);
    CC_SYNTHESIZE_READONLY(bool, m_bCaught, Caught);
    void shootTo(cocos2d::CCPoint targetDirection);
    void showNet();
private:
    bool initWithBulletType(int bulletType, GameLayer *gameLayer, cocos2d::CCSpriteBatchNode *pBatchNodeBullet, cocos2d::CCSpriteBatchNode *pBatchNodeNet);
    void removeSelf();
};

#endif
