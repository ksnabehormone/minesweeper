//  ゲームレイヤー
//  Created by 川端進悟 on 2015/05/22.
#ifndef __minesweeper__GameLayer__
#define __minesweeper__GameLayer__

#include "cocos2d.h"
#include "PanelSprite.h"
#include <random>

class GameLayer : public cocos2d::Layer
{
protected:
    //タグ　
    enum Tag
    {
        T_BG = 1,
    };
    
    //Zオーダー
    enum ZOrder
    {
        BG = 0,
        BALL
    };
    
    //ゲームの状態
    enum class State
    {
        GameStart,
        Gaming,
        GameOver,
    };
    
    std::mt19937 _mt; //乱数生成エンジン
    std::uniform_real_distribution<double> _height; //乱数の分布
    
    State _state; //ゲームの状態
    float _totalTime; //ゲーム時間
    
    // パネル作成
    PanelSprite* newPanel(PanelSprite::PositionIndex positionIndex, PanelSprite::PanelType type);
    // タッチ地点からパネルを取得
    PanelSprite* getTouchPanel(cocos2d::Point touchPos, PanelSprite::PositionIndex withoutPosIndex = PanelSprite::PositionIndex());
    
public:
    static cocos2d::Scene* createScene(); //シーン生成
    virtual bool init(); //初期化
    CREATE_FUNC(GameLayer); //create関数生成マクロ
    virtual void onEnter(); //レイヤー表示時処理
    virtual void update(float dt); //update関数（毎フレーム処理）
    void initPanel();
    //シングルタップイベント
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    
};


#endif /* defined(__minesweeper__GameLayer__) */
