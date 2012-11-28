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

class Fish : public cocos2d::CCObject
{
public:
    int m_nFishType;
    cocos2d::CCSprite *m_pSprite;
    cocos2d::CCSpriteBatchNode *m_pFishesBatchNode;
    static Fish *createWithFishType(int fishType, cocos2d::CCSpriteBatchNode *pBatchNode);
private:
    bool initWithFishType(int fishType, cocos2d::CCSpriteBatchNode *pBatchNode);

};

#endif /* defined(__FishingJoy__Fish__) */
