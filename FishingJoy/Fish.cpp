//
//  Fish.cpp
//  FishingJoy
//
//  Created by jie ding on 11/28/12.
//
//

#include "Fish.h"
#include "GameLayer.h"

using namespace cocos2d;

Fish::~Fish()
{
    CCLOG("destruct fish %d", m_nFishType);
}

Fish *Fish::createWithFishType(int fishType, GameLayer *gameLayer, CCSpriteBatchNode *pBatchNode)
{
    Fish *fish = new Fish();
    if(fish && fish->initWithFishType(fishType, gameLayer, pBatchNode))
    {
        fish->autorelease();
        return fish;
    }
    else
    {
        delete fish;
        return NULL;
    }
}


bool Fish::initWithFishType(int fishType, GameLayer *gameLayer, CCSpriteBatchNode *pBatchNode)
{
    m_bCaught = false;
    this->setFishType(fishType);
    this->setGameLayer(gameLayer);
    this->setBatchNode(pBatchNode);
    m_bParticleBubble = false;
    
    if(m_nFishType == 11 || m_nFishType == 12)  //mermaid
        m_bParticleBubble = true;
    
    CCArray *frames = CCArray::create();
    for(int i = 1; i <= 16; i++)
    {
        CCString *frameName = CCString::createWithFormat("fish%02d_%02d.png", fishType, i);
        CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
        if(pFrame)
            frames->addObject(pFrame);
    }
    
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.2f);
    animation->setRestoreOriginalFrame(false);
    CCAnimate *animate = CCAnimate::create(animation);
    CCAction *swing = CCRepeatForever::create(animate);
    
    CCString *originalFrameName = CCString::createWithFormat("fish%02d_01.png", fishType);
    
    m_pSprite = CCSprite::createWithSpriteFrameName(originalFrameName->getCString());
    m_pSprite->runAction(swing);
    
    m_pSprite->setAnchorPoint(ccp(0.5f, 0.5f));
    
    CCMoveTo *moveto = NULL;
    this->getPath(moveto);

    CCFiniteTimeAction *releaseFunc = CCCallFunc::create(this, callfunc_selector(Fish::removeSelf));
    CCFiniteTimeAction *sequence = CCSequence::create(moveto, releaseFunc, NULL);
    m_pSprite->runAction(sequence);
    
    this->getGameLayer()->getFishes()->addObject(this);
    this->getBatchNode()->addChild(m_pSprite);

    return true;
}

void Fish::showCaught()
{
    m_bCaught = true;
    m_pSprite->stopAllActions();
    
    CCArray *frames = CCArray::createWithCapacity(11);
    for(int i = 1; i <= 4; i++)
    {
        CCString *frameName = CCString::createWithFormat("fish%02d_catch_%02d.png", m_nFishType ,i);
        CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString());
        if(pFrame)
            frames->addObject(pFrame);
    }
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.3f);
    CCAnimate *animate = CCAnimate::create(animation);
    CCFiniteTimeAction *callFunc = CCCallFunc::create(this, callfunc_selector(Fish::removeSelf));
    CCFiniteTimeAction *sequence = CCSequence::create(animate, callFunc, NULL);
    m_pSprite->runAction(sequence);
    
}

void offsetPoint(CCPoint& pt, float offsetX, float offsetY)
{
    pt.x += offsetX;
    pt.y += offsetY;
}

void Fish::getPath(cocos2d::CCMoveTo *&moveto)
{
    CCSize fishSize = m_pSprite->getContentSize();
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint ptStart, ptEnd;
    float radius = fmaxf(fishSize.width, fishSize.height) / 2;
    switch (rand() % 4) {
        case 0:
            ptStart.x = - radius;
            ptStart.y = rand() % (int)winSize.height;
            ptEnd.x = winSize.width + radius;
            ptEnd.y = rand() % (int)winSize.height;
            break;
        case 1:
            ptStart.x = winSize.width + radius;
            ptStart.y = rand() % (int)winSize.height;
            ptEnd.x = - radius;
            ptEnd.y = rand() % (int)winSize.height;
            break;
        case 2:
            ptStart.x = rand() % (int)winSize.width;
            ptStart.y = - radius;
            ptEnd.x = rand() % (int)winSize.width;
            ptEnd.y = winSize.height + radius;
            break;
        case 3:
            ptStart.x = rand() % (int)winSize.width;
            ptStart.y = winSize.height + radius;
            ptEnd.x = rand() % (int)winSize.width;
            ptEnd.y = - radius;
            break;
        default:
            break;
    }

    float angle = atan2f(ptEnd.y - ptStart.y, ptEnd.x - ptStart.x);
    float rotation = 180.0f - angle * 180.0f / M_PI;
    
    float duration = rand() % 10 + 4.0f;
    m_pSprite->setPosition(ptStart);
    m_pSprite->setRotation(rotation);
    moveto = CCMoveTo::create(duration, ptEnd);
    
    if(m_bParticleBubble)
    {
        this->setParticleBubble(CCParticleSystemQuad::create("bubble.plist"));
        m_pGameLayer->addChild(m_pParticleBubble);
        float w = m_pSprite->getContentSize().width / 2.0f;
        offsetPoint(ptStart, cosf(angle) * w, sinf(angle) * w);
        m_pParticleBubble->setPosition(ptStart);
        offsetPoint(ptEnd, cosf(angle) * w, sinf(angle) * w);
        CCAction *act = CCMoveTo::create(moveto->getDuration(), ptEnd);
        m_pParticleBubble->setAutoRemoveOnFinish(false);
        m_pParticleBubble->setPositionType(kCCPositionTypeFree);
        m_pParticleBubble->runAction(act);
    }
    
}

void Fish::removeSelf()
{
    this->getGameLayer()->getFishes()->removeObject(this);
    m_pSprite->removeFromParentAndCleanup(true);
    if(m_bParticleBubble && m_pParticleBubble)
        m_pParticleBubble->removeFromParentAndCleanup(true);
}
