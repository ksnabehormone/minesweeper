#include "PanelSprite.h"


PanelSprite::PanelSprite()
{
}

bool PanelSprite::init()
{
    if (!Sprite::init())
    {
        return false;
    }
    return true;
}

void PanelSprite::onEnter()
{
    Sprite::onEnter();
    
    // ※initのタイミングではダメだった。謎
    setTexture();
}

//位置インデックスを返す
PanelSprite::PositionIndex PanelSprite::getPositionIndex()
{
    //位置インデックスを返す
    return _positionIndex;
}

//位置インデックスとタグを変更する
void PanelSprite::setPositionIndex(PositionIndex positionIndex)
{
    //位置インデックスを保持する
    _positionIndex = positionIndex;
    
    //タグをセットする
    setTag(generateTag(_positionIndex));
}

void PanelSprite::setTexture()
{
    switch (_panelType) {
        case PanelType::Unknown:
            this->cocos2d::Sprite::setTexture("green.png");
            break;
        case PanelType::Safety:
            this->cocos2d::Sprite::setTexture("yellow.png");
            break;
        case PanelType::Bomb:
            this->cocos2d::Sprite::setTexture("red.png");
            break;
        case PanelType::Flag:
            this->cocos2d::Sprite::setTexture("purple.png");
            break;
        default:
            break;
    }
}

//位置インデックスからタグを取得
int PanelSprite::generateTag(PositionIndex positionIndex)
{
    return positionIndex.x * 100 + positionIndex.y;
}
