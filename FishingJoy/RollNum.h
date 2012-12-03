//
//  RollNum.h
//  FishingJoy
//
//  Created by jie ding on 12/3/12.
//
//

#ifndef __FishingJoy__RollNum__
#define __FishingJoy__RollNum__

#include <iostream>
#include "cocos2d.h"

class RollNum : public cocos2d::CCObject
{
public:
    RollNum();
    virtual ~RollNum();
    CREATE_FUNC(RollNum);
    CC_PROPERTY(int, m_nNumber, Number);
    CC_SYNTHESIZE(cocos2d::CCSprite *, m_pSprite, Sprite);
    CC_SYNTHESIZE(bool, m_bUp, UpDirection);
    CC_SYNTHESIZE(cocos2d::CCTexture2D *, m_pTexture, Texture);
private:
    bool init();
    
};

#endif /* defined(__FishingJoy__RollNum__) */
