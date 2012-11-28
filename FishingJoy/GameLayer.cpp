#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "Fish.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* GameLayer::scene()
{
    CCScene *scene = CCScene::create();
    GameLayer *layer = GameLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    srand(time(NULL));
    this->initBackground();
    this->initFishes();
    return true;
}

void GameLayer::initBackground()
{
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("bj01.jpg");
    CCSprite *pBackground = CCSprite::createWithTexture(texture);
    pBackground->setAnchorPoint(ccp(0.5f, 0.5f));
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    pBackground->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(pBackground);
}

void GameLayer::initFishes()
{
    if(m_fishes == NULL)
    {
        m_fishes = CCArray::createWithCapacity(MAX_FISH_COUNT);
    }
    
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("fish.png");
    m_pFishesBatchNode = CCSpriteBatchNode::createWithTexture(texture, MAX_FISH_COUNT);
    this->addChild(m_pFishesBatchNode);
    
    m_fishes->removeAllObjects();
    for(int i = 0; i < MAX_FISH_COUNT; i++)
    {
        Fish *pFish = Fish::createWithFishType(1);
        m_fishes->addObject(pFish);
        m_pFishesBatchNode->addChild(pFish->m_pSprite);
    }
}
