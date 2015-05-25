#include "GameLayer.h"

// Create関数不要にする
USING_NS_CC;

// パネルの１番目位置
#define PANEL_1_X 0
#define PANEL_1_Y 530

// パネルの縦横数
#define PANEL_WIDTH_CNT 6
#define PANEL_HEIGHT_CNT 5

// パネルのサイズ
#define PANEL_SIZE 106

#define BOMB_SIZE 15


// シーンの作成
Scene* GameLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = GameLayer::create();
    auto bg = LayerColor::create(Color4B(0,255,0,128), 640, 1136);
    layer->addChild(bg, GameLayer::ZOrder::BG);
    scene->addChild(layer);
    return scene;
}

//初期化
bool GameLayer::init()
{
    if (!Layer::init())
        return false;
    
    // シングルタップイベントの取得
    // _sqallowsTouchesはNodeが持つ変数
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(_swallowsTouches);
    touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    //乱数の初期化
    std::random_device rd;
    _mt = std::mt19937(rd());
    
    initBomb();
    
    initPanel();
    
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

// パネルを初期化
void GameLayer::initPanel()
{
    int panelIndex = 0;
    for (int x = 1; x <= PANEL_WIDTH_CNT; x++)
    {
        for (int y = 1; y <= PANEL_HEIGHT_CNT; y++)
        {
            auto positionIndex = PanelSprite::PositionIndex(x, y);
            auto type = PanelSprite::PanelType::Unknown;
            
            // ボム配列に含まれるインデックスはボムになる
            bool isBomb = false;
            if (checkBombIndex(panelIndex)) {
                isBomb = true;
            }
            panelIndex++;
            
            newPanel(positionIndex, type, isBomb);
        }
    }
    
}

PanelSprite* GameLayer::newPanel(PanelSprite::PositionIndex positionIndex, PanelSprite::PanelType type, bool isBomb)
{
    auto sprite = PanelSprite::create();
    sprite->setPanelType(type);
    sprite->setPositionIndex(positionIndex);
    sprite->setPosition(PANEL_1_X + ((positionIndex.x - 0.5) * PANEL_SIZE),
                        PANEL_1_Y - ((positionIndex.y - 0.5) * PANEL_SIZE));
    sprite->setIsBomb(isBomb);
    addChild(sprite, GameLayer::ZOrder::BALL);
    return sprite;
}

PanelSprite* GameLayer::getTouchPanel(cocos2d::Point touchPos, PanelSprite::PositionIndex withoutPosIndex)
{
    for (int x = 1; x <= PANEL_WIDTH_CNT; x++)
    {
        for (int y = 1; y <= PANEL_HEIGHT_CNT; y++) {
            if (x == withoutPosIndex.x && y == withoutPosIndex.y)
            {
                //指定位置のボールの場合は、以下の処理を行わない
                continue;
            }
            
            //タップ位置にあるボールかどうかを判断する
            int tag = PanelSprite::generateTag(PanelSprite::PositionIndex(x, y));
            auto panel = (PanelSprite*)(getChildByTag(tag));
            if (panel)
            {
                //2点間の距離を求める
                float distance = panel->getPosition().getDistance(touchPos);
                
                //ボールの当たり判定は円形。つまりボールの中心からの半径で判断する
                if (distance <= PANEL_SIZE / 2)
                {
                    //タップした位置にボールが存在する
                    return panel;
                }
            }
        }
    }
    return nullptr;
}

void GameLayer::touchPanelEvent(PanelSprite* target)
{
    // タイプを取得
    auto type = target->getPanelType();
    // フラグなら踏めない
    
    //　ボムなら爆発
    if (target->getIsBomb())
    {
        target->setPanelType(PanelSprite::PanelType::Open);
    }
    else
    {
        target->setPanelType(PanelSprite::PanelType::Bomb);
    }
}

void GameLayer::initBomb()
{
    for (int i=0; i < BOMB_SIZE; i++)
    {
        int index = arc4random()%30;
        _bombs.push_back(index);
    }
}

bool GameLayer::checkBombIndex(int target)
{
    for (int i=0; i < _bombs.size(); i++)
    {
        if (target == _bombs[i])
        {
            return true;
        }
    }
    return false;
}

// タッチ処理
bool GameLayer::onTouchBegan(Touch* touch, Event* unused_event)
{
    PanelSprite* touchPanel = getTouchPanel(touch->getLocation());
    
    if (touchPanel != nullptr)  
    {
        touchPanelEvent(touchPanel);
        return true;
    }
    else
    {
        return false;
    }
}

void GameLayer::onTouchMoved(Touch* touch, Event* unused_event)
{
}

void GameLayer::onTouchEnded(Touch* touch, Event* unused_event)
{
}

void GameLayer::onTouchCancelled(Touch* touch, Event* unused_event)
{
    onTouchEnded(touch, unused_event);
}
