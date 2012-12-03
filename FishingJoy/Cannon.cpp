//
//  Cannon.cpp
//  FishingJoy
//
//  Created by 胡 蓉 on 12-11-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Cannon.h"
#include "Bullet.h"

using namespace cocos2d;

Cannon *Cannon::createWithCannonType(int cannonType, GameLayer* pGameLayer, CCSpriteBatchNode *pBatchNode)
{
    Cannon *pCannon = new Cannon();
    if(pCannon && pCannon->initWithCannonType(cannonType, pGameLayer, pBatchNode))
    {
        pCannon->autorelease();
        return pCannon;
    }
    else
    {
        CC_SAFE_DELETE(pCannon);
        return NULL;
    }
}

bool Cannon::initWithCannonType(int cannonType, GameLayer* pGameLayer, CCSpriteBatchNode *pBatchNode)
{
    this->setCannonType(cannonType);
    this->setGameLayer(pGameLayer);
    m_pSprite = CCSprite::createWithSpriteFrameName("actor_cannon1_71.png");
    m_pSprite->setPosition(ccp(520, 50));
    pBatchNode->addChild(m_pSprite);
    return true;
}

void Cannon::rotateToPoint(cocos2d::CCPoint ptTo)
{
    CCPoint ptFrom = m_pSprite->getPosition();
    float angle = atan2f(ptTo.y - ptFrom.y, ptTo.x - ptFrom.x) / M_PI * 180.0f;
    this->setRotation(90.0f - angle);
    this->setDirection(ptTo);
}

float Cannon::getRotation()
{
    return m_fRotation;
}

void Cannon::setRotation(float var)
{
    m_fRotation = var;
    
    float duration = fabsf(m_fRotation - m_pSprite->getRotation()) / 180.0f * 0.2f;
    
    CCFiniteTimeAction *pAction = CCRotateTo::create(duration, m_fRotation);
    m_pSprite->runAction(pAction);
}

void Cannon::fire()
{
    CCSpriteFrame *pFrame1 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("actor_cannon1_71.png");
    CCSpriteFrame *pFrame2 = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("actor_cannon1_72.png");
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(CCArray::create(pFrame1, pFrame2, NULL), 0.1f);
    animation->setRestoreOriginalFrame(true);
    CCFiniteTimeAction *pAction = CCAnimate::create(animation);
    m_pSprite->runAction(pAction);
    
    int type = 1;
    Bullet *pBullet = Bullet::createWithBulletType(type, m_pGameLayer, m_pGameLayer->getBatchNode2(), m_pGameLayer->getBatchNode3());
    pBullet->shootTo(m_ptDirection);
}
