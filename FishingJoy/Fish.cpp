//
//  Fish.cpp
//  FishingJoy
//
//  Created by jie ding on 11/28/12.
//
//

#include "Fish.h"

using namespace cocos2d;

Fish *Fish::createWithFishType(int fishType, CCSpriteBatchNode *pBatchNode)
{
    Fish *fish = new Fish();
    if(fish && fish->initWithFishType(fishType, pBatchNode))
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

bool Fish::initWithFishType(int fishType, CCSpriteBatchNode *pBatchNode)
{
    CCArray *frames = CCArray::create();
    for(int i = 1; i <= 10; i++)
    {
        CCString *frameName = CCString::createWithFormat("fish%02d_%02d.png", fishType, i);
        frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString()));
    }
    
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.2f);
    animation->setRestoreOriginalFrame(false);
    CCAnimate *animate = CCAnimate::create(animation);
    CCAction *swing = CCRepeatForever::create(animate);
    
    CCString *originalFrameName = CCString::createWithFormat("fish%02d_01.png", fishType);
    
    m_pSprite = CCSprite::createWithSpriteFrameName(originalFrameName->getCString());
    m_pSprite->runAction(swing);
    m_pSprite->setPosition(ccp(rand() % 1024, rand() % 768));
    m_pSprite->setScale(1.5f);
    m_pSprite->setRotation(90);
    m_pFishesBatchNode = pBatchNode;
    m_pFishesBatchNode->addChild(m_pSprite);

    return true;
}
