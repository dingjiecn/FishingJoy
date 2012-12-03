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

#define NUMBERHEIGHT 20
#define NUMBERWIDTH  20

RollNum::RollNum():m_nNumber(0), m_pSprite(NULL), m_bUp(true)
{
    
}

RollNum::~RollNum()
{
    
}

bool RollNum::init()
{
    this->setTexture(CCTextureCache::sharedTextureCache()->addImage("number.png"));
    CCSpriteFrame *pFrame = CCSpriteFrame::createWithTexture(m_pTexture, CCRectMake(0, 0, NUMBERWIDTH, NUMBERHEIGHT));
    m_pSprite = CCSprite::createWithSpriteFrame(pFrame);
    return true;
}

void RollNum::setNumber(int var)
{
    m_nNumber = var;
}

int RollNum::getNumber()
{
    return m_nNumber;
}
