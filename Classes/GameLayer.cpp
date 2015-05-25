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
    
    //乱数の初期化
    std::random_device rd;
    _mt = std::mt19937(rd());
    
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

void GameLayer::initPanel()
{
    for (int x = 0; x < PANEL_WIDTH_CNT; x++)
    {
        for (int y = 0; y < PANEL_HEIGHT_CNT; y++) {
            auto positionIndex = PanelSprite::PositionIndex(x, y);
            auto type = PanelSprite::PanelType::Unknown;
            newPanel(positionIndex, type);
        }
    }
    
}

PanelSprite* GameLayer::newPanel(PanelSprite::PositionIndex positionIndex, PanelSprite::PanelType type)
{
    auto sprite = PanelSprite::create();
    sprite->setPanelType(type);
    sprite->setPositionIndex(positionIndex);
    sprite->setPosition(PANEL_1_X + (positionIndex.x * PANEL_SIZE),
                        PANEL_1_Y - (positionIndex.y * PANEL_SIZE));
    log("x%i",PANEL_1_X + (positionIndex.x * PANEL_SIZE));
    log("y%i",PANEL_1_X + (positionIndex.y * PANEL_SIZE));
    sprite->setAnchorPoint(Point(0, 1));
    addChild(sprite, GameLayer::ZOrder::BALL);
    return sprite;
}