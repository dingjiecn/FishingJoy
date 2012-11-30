#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "Fish.h"

using namespace cocos2d;
using namespace CocosDenshion;

const int FishInBatchNode1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 13, 14};
const int FishInBatchNode2[] = {10, 18};

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
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish2.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish3.plist");
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
    this->setBatchNode1(CCSpriteBatchNode::createWithTexture(texture));
    this->addChild(m_pBatchNode1);
    
    texture = CCTextureCache::sharedTextureCache()->addImage("fish2.png");
    this->setBatchNode2(CCSpriteBatchNode::createWithTexture(texture));
    this->addChild(m_pBatchNode2);
    
    texture = CCTextureCache::sharedTextureCache()->addImage("fish3.png");
    this->setBatchNode3(CCSpriteBatchNode::createWithTexture(texture));
    this->addChild(m_pBatchNode3);

    for(int i = 0; i < GET_ARRAY_LEN(FishInBatchNode1); i++)
    {
        fishInBatchNode1.insert(FishInBatchNode1[i]);
    }
    for(int i = 0; i < GET_ARRAY_LEN(FishInBatchNode2); i++)
    {
        fishInBatchNode2.insert(FishInBatchNode2[i]);
    }
    
    m_pFishes->removeAllObjects();
    for(int i = 0; i < MAX_FISH_COUNT; i++)
    {
        this->addFish();
    }
}

void GameLayer::addFish()
{
    while(1)
    {
        int type = rand() % 18 + 1;
        std::set<int>::iterator it = fishInBatchNode1.find(type);
        if(it != fishInBatchNode1.end())
        {
            Fish::createWithFishType(type, this, m_pBatchNode1);
            return;
        }
     
        it = fishInBatchNode2.find(type);
        if(it != fishInBatchNode2.end())
        {
            Fish::createWithFishType(type, this, m_pBatchNode2);
            return;
        }
    }
}

void GameLayer::updateGame(CCTime dt)
{
    if(m_pFishes->count() < MAX_FISH_COUNT)
    {
        int n = MAX_FISH_COUNT - m_pFishes->count();
        for(int i = 0; i < n; i++)
        {
            this->addFish();
        }
    }
    
    
    
}
