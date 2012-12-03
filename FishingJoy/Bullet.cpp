//
//  Bullet.cpp
//  FishingJoy
//
//  Created by 胡 蓉 on 12-11-30.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Bullet.h"

using namespace cocos2d;

Bullet *Bullet::createWithBulletType(int bulletType, GameLayer *gameLayer, CCSpriteBatchNode *pBatchNodeBullet, CCSpriteBatchNode *pBatchNodeNet)
{
    Bullet *pBullet = new Bullet();
    if(pBullet && pBullet->initWithBulletType(bulletType, gameLayer, pBatchNodeBullet, pBatchNodeNet))
    {
        pBullet->autorelease();
        return pBullet;
    }
    else
    {
        CC_SAFE_DELETE(pBullet);
        return NULL;
    }
}

bool Bullet::initWithBulletType(int bulletType, GameLayer *gameLayer, CCSpriteBatchNode *pBatchNodeBullet, CCSpriteBatchNode *pBatchNodeNet)
{
    m_bCaught = false;
    
    this->setBulletType(bulletType);
    this->setGameLayer(gameLayer);
    CCString *bulletName = CCString::createWithFormat("bullet0%d.png", m_nBulletType);
    this->setSpriteBullet(CCSprite::createWithSpriteFrameName(bulletName->getCString()));
    m_pSpriteBullet->setPosition(ccp(520, 50));
    pBatchNodeBullet->addChild(m_pSpriteBullet);

    
    this->setSpriteNet(CCSprite::createWithSpriteFrameName("net01.png"));
    m_pSpriteNet->setVisible(false);
    pBatchNodeNet->addChild(m_pSpriteNet);
    
    m_pGameLayer->getBullets()->addObject(this);    
    return true;
}

void Bullet::shootTo(CCPoint targetDirection)
{
    CCPoint ptFrom = m_pSpriteBullet->getPosition();
    CCPoint ptTo = targetDirection;
    float angle = atan2f(ptTo.y - ptFrom.y, ptTo.x - ptFrom.x);
    float rotation = angle / M_PI * 180.0f;
    m_pSpriteBullet->setRotation(90.0f - rotation);
    
    float distance = 1000.0f;
    CCPoint targetPt = ccp(ptFrom.x + distance * cosf(angle), ptFrom.y + distance * sinf(angle));
    CCFiniteTimeAction *moveto = CCMoveTo::create(1.0f, targetPt);
    CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Bullet::removeSelf));
    CCFiniteTimeAction *sequence = CCSequence::create(moveto, callFunc, NULL);
    m_pSpriteBullet->runAction(sequence);
}

void Bullet::showNet()
{
    m_bCaught = true;
    m_pSpriteBullet->stopAllActions();
    m_pSpriteBullet->setVisible(false);
    m_pSpriteNet->setVisible(true);
    m_pSpriteNet->setScale(1.25f);
    CCArray *frames = CCArray::createWithCapacity(11);
    for(int i = 1; i <= 11; i++)
    {
        CCString *frameName = CCString::createWithFormat("net0%d.png", i);
        CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
        frames->addObject(frame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.2f);
    CCAnimate *animate = CCAnimate::create(animation);
    CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Bullet::removeSelf));
    CCFiniteTimeAction *sequence = CCSequence::create(animate, callFunc, NULL);
    m_pSpriteNet->runAction(sequence);
    m_pSpriteNet->setPosition(m_pSpriteBullet->getPosition());
    
    
    CCParticleSystem *particle = CCParticleSystemQuad::create("netparticle.plist");
    particle->setPosition(m_pSpriteNet->getPosition());
    particle->setPositionType(kCCPositionTypeGrouped);
    particle->setAutoRemoveOnFinish(true);
    m_pGameLayer->addChild(particle, 100);
  
}

void Bullet::removeSelf()
{
    CCLOG("remove bullet");
    this->getGameLayer()->getBullets()->removeObject(this);
    m_pSpriteBullet->removeFromParentAndCleanup(true);
    m_pSpriteNet->removeFromParentAndCleanup(true);
}

