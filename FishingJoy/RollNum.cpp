//
//  RollNum.cpp
//  FishingJoy
//
//  Created by jie ding on 12/3/12.
//
//

#include "RollNum.h"
#include "cocos2d.h"
#include "GameLayer.h"

using namespace cocos2d;

#define NUMBERHEIGHT    16
#define NUMBERWIDTH     12
#define TEXTUREHEIGHT   196

RollNum::RollNum():m_nNumber(0), m_bUp(true), m_nCurTexH(0), m_nEndTexH(0), m_bRolling(false), m_pTexture(NULL)
{
    
}

RollNum::~RollNum()
{
    this->unscheduleAllSelectors();
}

bool RollNum::init()
{
    m_pTexture = CCTextureCache::sharedTextureCache()->textureForKey("number.png");
    CCSpriteFrame *pFrame = CCSpriteFrame::createWithTexture(m_pTexture, CCRectMake(0, 0, NUMBERWIDTH, NUMBERHEIGHT));
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

    if(m_bUp)
    {
        m_nCurTexH += 4;
        if(m_nCurTexH >= TEXTUREHEIGHT)
            m_nCurTexH = 0;
    }
    else
    {
        m_nCurTexH -= 4;
        if(m_nCurTexH < 0)
            m_nCurTexH = TEXTUREHEIGHT;
    }

    int h = m_nCurTexH;
    if(m_nCurTexH >= 180)
        h = 180;
    
    CCSpriteFrame *pFrame = CCSpriteFrame::createWithTexture(m_pTexture, CCRectMake(0, h, NUMBERWIDTH, NUMBERHEIGHT));
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

///////////////////////////////////////////////////////////////////////////////////////////////////

RollNumGroup *RollNumGroup::createWithGameLayer(GameLayer *pGameLayer, int nDigit)
{
    RollNumGroup *pRollNumGroup = new RollNumGroup();
    if(pRollNumGroup && pRollNumGroup->initWithGameLayer(pGameLayer, nDigit))
    {
        pRollNumGroup->autorelease();
        return pRollNumGroup;
    }
    else
    {
        CC_SAFE_DELETE(pRollNumGroup);
        return NULL;
    }
}

RollNumGroup::RollNumGroup():m_pRollNumArray(NULL), m_nValue(0)
{
    
}

RollNumGroup::~RollNumGroup()
{
    CC_SAFE_RELEASE(m_pRollNumArray);
}

bool RollNumGroup::initWithGameLayer(GameLayer *pGameLayer, int nDigit)
{
    m_pGameLayer = pGameLayer;
    CCTexture2D *pTex = CCTextureCache::sharedTextureCache()->addImage("number.png");
    m_pBatchNode = CCSpriteBatchNode::createWithTexture(pTex);
    m_pGameLayer->addChild(m_pBatchNode, 100);
    this->setRollNumArray(CCArray::createWithCapacity(nDigit));
    for(int i = 0; i < nDigit; i++)
    {
        RollNum *pRollNum = RollNum::create();
        m_pRollNumArray->addObject(pRollNum);
        m_pBatchNode->addChild(pRollNum);
    }
    
    return true;
}

void RollNumGroup::setPosition(cocos2d::CCPoint pt)
{
    m_ptPosition = pt;
    for(int i = 0; i < m_pRollNumArray->count(); i++)
    {
        RollNum *pRollNum = (RollNum *)m_pRollNumArray->objectAtIndex(i);
        pRollNum->setPosition(pt);
        pt.x -= 20.7f;
    }
}

void RollNumGroup::setValue(int nValue)
{
    if(m_nValue == nValue)
        return;
    
    bool bUp = m_nValue < nValue;
    m_nValue = nValue;
    for(int i = 0; i < m_pRollNumArray->count(); i++)
    {
        RollNum *pRollNum = (RollNum *)m_pRollNumArray->objectAtIndex(i);
        int num = nValue % 10;
        if(pRollNum->getNumber() != num)
            pRollNum->setNumber(num, bUp);
        nValue = nValue / 10;
    }
}




