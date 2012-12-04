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

class GameLayer;

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
    cocos2d::CCTexture2D *m_pTexture;
    
};

class RollNumGroup : public cocos2d::CCObject
{
public:
    RollNumGroup();
    virtual ~RollNumGroup();
    static RollNumGroup *createWithGameLayer(GameLayer *pGameLayer, int nDigit);
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode, BatchNode);
    CC_SYNTHESIZE(GameLayer *, m_pGameLayer, GameLayer);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pRollNumArray, RollNumArray);
    void setValue(int nValue);
    void setPosition(cocos2d::CCPoint pt);
private:
    cocos2d::CCPoint m_ptPosition;
    int m_nDigit;
    int m_nValue;
    bool initWithGameLayer(GameLayer *pGameLayer, int nDigit);
};

#endif /* defined(__FishingJoy__RollNum__) */
