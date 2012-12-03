//
//  RollNum.cpp
//  FishingJoy
//
//  Created by jie ding on 12/3/12.
//
//

#include "RollNum.h"
#include "cocos2d.h"

using namespace cocos2d;

#define NUMBERHEIGHT 16
#define NUMBERWIDTH  12

RollNum::RollNum():m_nNumber(0), m_bUp(true), m_nCurTexH(0), m_nEndTexH(0), m_bRolling(false)
{
    
}

RollNum::~RollNum()
{
    this->unscheduleAllSelectors();
}

bool RollNum::init()
{
    CCTexture2D *pTex = CCTextureCache::sharedTextureCache()->addImage("number.png");
    CCSpriteFrame *pFrame = CCSpriteFrame::createWithTexture(pTex, CCRectMake(0, 0, NUMBERWIDTH, NUMBERHEIGHT));
    this->initWithSpriteFrame(pFrame);
    this->setScale(1.0f);
    return true;
}

void RollNum::updateNumber(cocos2d::CCTime dt)
{
    if(m_bRolling && m_nCurTexH == m_nEndTexH)
    {
        this->unschedule(schedule_selector(RollNum::updateNumber));
        m_bRolling = false;
        return;
    }
    CCTexture2D *pTex = CCTextureCache::sharedTextureCache()->textureForKey("number.png");
    CCSpriteFrame *pFrame = NULL;
    
    if(m_bUp)
    {
        m_nCurTexH += 4;
        if(m_nCurTexH >= 196)
            m_nCurTexH = 0;
    }
    else
    {
        m_nCurTexH -= 4;
        if(m_nCurTexH <= 0)
            m_nCurTexH = 196;
    }

    int h = m_nCurTexH;
    if(m_nCurTexH >= 180)
        h = 180;
    
    pFrame = CCSpriteFrame::createWithTexture(pTex, CCRectMake(0, h, NUMBERWIDTH, NUMBERHEIGHT));
    this->setDisplayFrame(pFrame);   
    m_bRolling = true;
}

void RollNum::setNumber(int var, bool bUp)
{    
    m_nNumber = var;
    m_bUp = bUp;
    m_nEndTexH = m_nNumber * (NUMBERHEIGHT + 4);
    this->schedule(schedule_selector(RollNum::updateNumber), 0.01f);
   
}

int RollNum::getNumber()
{
    return m_nNumber;
}
