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
    this->initFrames();
    this->initBackground();
    this->initFishes();
    this->schedule(schedule_selector(GameLayer::updateGame), 0.05f);
    return true;
}

void::GameLayer::initFrames()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish.plist");
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
    this->setFishes(CCArray::createWithCapacity(MAX_FISH_COUNT));    
    
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("fish.png");
    m_pFishesBatchNode = CCSpriteBatchNode::createWithTexture(texture, MAX_FISH_COUNT);
    this->addChild(m_pFishesBatchNode);
    
    m_pFishes->removeAllObjects();
    for(int i = 0; i < MAX_FISH_COUNT; i++)
    {
        int type = rand() % 9 + 1;
        Fish::createWithFishType(type, this);
    }
}

void GameLayer::updateGame(CCTime dt)
{
    if(m_pFishes->count() < MAX_FISH_COUNT)
    {
        int n = MAX_FISH_COUNT - m_pFishes->count();
        for(int i = 0; i < n; i++)
        {
            int type = rand() % 9 + 1;
            Fish::createWithFishType(type, this);
        }
    }
    
    
    
}
