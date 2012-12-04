#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "Fish.h"
#include "Cannon.h"
#include "Bullet.h"
#include "RollNum.h"

using namespace cocos2d;
using namespace CocosDenshion;

const int FishInBatchNode1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 13, 14};
const int FishInBatchNode2[] = {10, 18};
const int FishInBatchNode3[] = {};//{16, 17};
const int FishInBatchNode4[] = {11, 12};

CCScene* GameLayer::scene()
{
    CCScene *scene = CCScene::create();
    GameLayer *layer = GameLayer::create();
    scene->addChild(layer);
    return scene;
}

GameLayer::GameLayer():m_pFishes(NULL), m_pBullets(NULL), m_pRollNumGroup(NULL), m_pCannon(NULL), m_nScore(0)
{
    
}

GameLayer::~GameLayer()
{
    CC_SAFE_RELEASE(m_pFishes);
    CC_SAFE_RELEASE(m_pBullets);
    CC_SAFE_RELEASE(m_pCannon);
    CC_SAFE_RELEASE(m_pRollNumGroup);
}

bool GameLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    srand(time(NULL));
    this->setTouchEnabled(true);
    this->initFrames();
    this->initBackground();
    this->initFishes();
    this->initCannon();
    this->schedule(schedule_selector(GameLayer::updateGame), 0.05f);
    this->schedule(schedule_selector(GameLayer::updateFish), 1.0f);
    this->setBullets(CCArray::create());
    return true;
}

void::GameLayer::initFrames()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish2.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish3.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("fish4.plist");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("cannon.plist");
}

void GameLayer::initBackground()
{
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage("bj01.jpg");
    CCSprite *pBackground = CCSprite::createWithTexture(texture);
    pBackground->setAnchorPoint(ccp(0.5f, 0.5f));
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    pBackground->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(pBackground);
 
    texture = CCTextureCache::sharedTextureCache()->addImage("ui_box_01.png");
    CCSprite *pTopBar = CCSprite::createWithTexture(texture);
    pTopBar->setPosition(ccp(500, 700));
    this->addChild(pTopBar, 100);
    
    texture = CCTextureCache::sharedTextureCache()->addImage("ui_box_02.png");
    CCSprite *pBottomBar = CCSprite::createWithTexture(texture);
    pBottomBar->setPosition(ccp(440, 90));
    this->addChild(pBottomBar, 100);
    
    this->setRollNumGroup(RollNumGroup::createWithGameLayer(this, 6));
    m_pRollNumGroup->setPosition(ccp(353, 21));
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
    
    texture = CCTextureCache::sharedTextureCache()->addImage("fish4.png");
    this->setBatchNode4(CCSpriteBatchNode::createWithTexture(texture));
    this->addChild(m_pBatchNode4);

    for(int i = 0; i < GET_ARRAY_LEN(FishInBatchNode1); i++)
    {
        fishInBatchNode1.insert(FishInBatchNode1[i]);
    }
    for(int i = 0; i < GET_ARRAY_LEN(FishInBatchNode2); i++)
    {
        fishInBatchNode2.insert(FishInBatchNode2[i]);
    }
    for(int i = 0; i < GET_ARRAY_LEN(FishInBatchNode3); i++)
    {
        fishInBatchNode3.insert(FishInBatchNode3[i]);
    }
    for(int i = 0; i < GET_ARRAY_LEN(FishInBatchNode4); i++)
    {
        fishInBatchNode4.insert(FishInBatchNode4[i]);
    }
    
    m_pFishes->removeAllObjects();

}

void GameLayer::initCannon()
{
    CCTexture2D *pTexture = CCTextureCache::sharedTextureCache()->addImage("cannon.png");
    CCSpriteBatchNode *pBatchNode = CCSpriteBatchNode::createWithTexture(pTexture);
    this->addChild(pBatchNode, 101);
    this->setCannon(Cannon::createWithCannonType(7, this, pBatchNode));
    m_pCannon->setRotation(0.0f);    
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
        
        it = fishInBatchNode3.find(type);
        if(it != fishInBatchNode3.end())
        {
            Fish::createWithFishType(type, this, m_pBatchNode3);
            return;
        }
        
        it = fishInBatchNode4.find(type);
        if(it != fishInBatchNode4.end())
        {
            Fish::createWithFishType(type, this, m_pBatchNode4);
            return;
        }
    }
}

void GameLayer::updateFish(CCTime dt)
{
    if(m_pFishes->count() < MAX_FISH_COUNT)
    {
        int n = MAX_FISH_COUNT - m_pFishes->count();
        int nAdd = rand() % n + 1;
        for(int i = 0; i < nAdd; i++)
        {
            this->addFish();
        }
    }
}

void GameLayer::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
 	CCSetIterator it = pTouches->begin();
	for(; it != pTouches->end(); it++)
    {
		CCTouch *pTouch = (CCTouch*)*it;
		CCPoint pt = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
        m_pCannon->rotateToPoint(pt);
        break;
	}   
}

void GameLayer::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    while(it != pTouches->end())
    {
        //CCTouch *pTouch = (CCTouch *)*it;
        //CCPoint pt = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
        m_pCannon->fire();
        break;
    }
}

CCRect shrinkRect(CCRect rc, float xr, float yr)
{
    float w = rc.size.width * xr;
    float h = rc.size.height * yr;
    CCPoint pt = ccp(rc.origin.x + rc.size.width * (1.0f - xr) / 2, 
                     rc.origin.y + rc.size.height * (1.0f - yr) / 2);
    return CCRectMake(pt.x, pt.y, w, h);   
}

void GameLayer::updateGame(CCTime dt)
{
    CCObject *pFishObj = NULL;
    CCObject *pBulletObj = NULL;
    CCARRAY_FOREACH(m_pBullets, pBulletObj)
    {
        Bullet *pBullet = (Bullet *)pBulletObj;
        if(pBullet->getCaught())
            continue;
        bool caught = false;
        CCARRAY_FOREACH(m_pFishes, pFishObj)
        {
            Fish *pFish = (Fish *)pFishObj;
            if(pFish->getCaught())
                continue;
            
            CCRect hittestRect = shrinkRect(pFish->getSprite()->boundingBox(), 1.0f, 0.5f);
            
            if(hittestRect.containsPoint(pBullet->getSpriteBullet()->getPosition()))
            {
                caught = true;
                pFish->showCaught();
                m_nScore += 125;
                m_pRollNumGroup->setValue(m_nScore);
            }
        }
        
        if(caught)
        {
            pBullet->showNet();
        }
    }
}
