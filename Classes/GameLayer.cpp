#include "GameLayer.h"

//初期化
bool GameLayer::init()
{
    if (!Layer::init())
        return false;
    
    //乱数の初期化
    std::random_device rd;
    _mt = std::mt19937(rd());
    
    
    return true;
}

//レイヤー表示時処理
void GameLayer::onEnter()
{
    Layer::onEnter();
    
}

//update関数（毎フレーム処理）
void GameLayer::update(float dt)
{
    //ゲーム時間の積算
    _totalTime += dt;
    
}

