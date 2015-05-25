#ifndef __minesweeper__PanelSprite__
#define __minesweeper__PanelSprite__

#include <cocos2d.h>

class PanelSprite : public cocos2d::Sprite
{
public:
    enum class PanelType
    {
        Unknown,
        Safety,
        Bomb,
        Flag
    };
    struct PositionIndex
    {
        int x;
        int y;
        PositionIndex()
        {
            x = 0;
            y = 0;
        }
        PositionIndex(int _x, int _y)
        {
            x = _x;
            y = _y;
        }
    };
    PanelSprite();
    virtual bool init();
    void onEnter();
    CREATE_FUNC(PanelSprite);
    CC_SYNTHESIZE(PanelType, _panelType, PanelType);
    CC_SYNTHESIZE(PositionIndex, _positionIndex, PositionIndex);
protected:
    void setTexture();
};
#endif /* defined(__minesweeper__PanelSprite__) */
