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

class RollNum : public cocos2d::CCSprite
{
public:
    RollNum();
    virtual ~RollNum();
    CREATE_FUNC(RollNum);
    CC_SYNTHESIZE(bool, m_bUp, UpDirection);
    void updateNumber(cocos2d::CCTime dt);
    void setNumber(int var, bool bUp);
    int getNumber();
private:
    bool init();
    int m_nNumber;
    int m_nCurTexH;
    int m_nEndTexH;
    bool m_bRolling;
    
};

#endif /* defined(__FishingJoy__RollNum__) */
