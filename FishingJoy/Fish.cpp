//
//  Fish.cpp
//  FishingJoy
//
//  Created by jie ding on 11/28/12.
//
//

#include "Fish.h"

using namespace cocos2d;

Fish *Fish::createWithFishType(int fishType)
{
    Fish *fish = new Fish();
    if(fish && fish->initWithFishType(fishType))
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

bool Fish::initWithFishType(int fishType)
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish.plist");
    int type = rand() % 8 + 1;
    
    CCArray *frames = CCArray::create();
    for(int i = 1; i < 10; i++)
    {
        CCString *frameName = CCString::createWithFormat("fish0%d_0%d.png", type, i);
        frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName->getCString()));
    }
    
    CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames, 0.2f);
    animation->setRestoreOriginalFrame(true);
    CCAnimate *animate = CCAnimate::create(animation);
    CCAction *swing = CCRepeatForever::create(animate);
    
    CCString *originalFrameName = CCString::createWithFormat("fish0%d_0%d.png", type, 1);
    m_pSprite = CCSprite::createWithSpriteFrameName(originalFrameName->getCString());

    m_pSprite->runAction(swing);
    m_pSprite->setPosition(ccp(rand() % 1024, rand() % 768));

    return true;
}
