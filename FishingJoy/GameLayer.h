//
//  GameLayer.h
//  FishingJoy
//
//  Created by jie ding on 11/28/12.
//
//

#ifndef __FishingJoy__GameLayer__
#define __FishingJoy__GameLayer__

#include <iostream>
#include "cocos2d.h"
#include "GameConfig.h"
#include "Cannon.h"
#include "RollNum.h"

class GameLayer : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    GameLayer();
    virtual ~GameLayer();
    virtual bool init();
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameLayer);
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode1, BatchNode1);
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode2, BatchNode2);
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode3, BatchNode3);
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode4, BatchNode4);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pFishes, Fishes);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pBullets, Bullets);
    CC_SYNTHESIZE_RETAIN(Cannon *, m_pCannon, Cannon);
    CC_SYNTHESIZE_RETAIN(RollNumGroup *, m_pRollNumGroup, RollNumGroup);
private:
    std::set<int> fishInBatchNode1;
    std::set<int> fishInBatchNode2;
    std::set<int> fishInBatchNode3;
    std::set<int> fishInBatchNode4;
    int m_nScore;
    void initFishes();
    void initBackground();
    void initCannon();
    void initFrames();
    void updateGame(cocos2d::CCTime dt);
    void updateFish(cocos2d::CCTime dt);
    void addFish();
};

#endif /* defined(__FishingJoy__GameLayer__) */
