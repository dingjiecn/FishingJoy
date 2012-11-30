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

class GameLayer : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(GameLayer);
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode1, BatchNode1);
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode2, BatchNode2);
    CC_SYNTHESIZE(cocos2d::CCSpriteBatchNode *, m_pBatchNode3, BatchNode3);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCArray *, m_pFishes, Fishes);
private:
    std::set<int> fishInBatchNode1;
    std::set<int> fishInBatchNode2;
    void initFishes();
    void initBackground();
    void initFrames();
    void updateGame(cocos2d::CCTime dt);
    void updateFish(cocos2d::CCTime dt);
    void addFish();
};

#endif /* defined(__FishingJoy__GameLayer__) */
