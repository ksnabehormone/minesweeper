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
