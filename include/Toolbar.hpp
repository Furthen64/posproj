#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <SFML/Graphics.hpp>
#include "CRect.hpp"
#include "Utilities/Utils.hpp"


enum TOOLBARBUTTONS { TB_NEW_FILE, TB_SAVE_FILE, TB_LOAD_FILE, TB_ONE, TB_TWO, TB_EXIT, TB_NONE };



/// //////////////////////////////////////////////
/// and up comes the Toolbar

class Toolbar
{
public:

    Toolbar(CanvasPos *);

    void setTopLeft(CanvasPos *_cpos);
    void setButtonPushed(int );

    int pushButton(CanvasPos *mousecpos);
    void resetButton(int indexNr);
    void resetButtons();

    void draw( sf::RenderTarget& rt);

    int whatButtonDidIPress(CanvasPos *mousecpos);
    CanvasPos *get_cpos();
    CRect *get_crect();
    int *getVisibleSpritesTopArr();

    bool inside(CanvasPos *mousecpos);

private:

    std::string cn = "Toolbar.cpp";
    CanvasPos *cpos;
    CRect *crect;

    sf::Texture texture;    // we need one texture but
    sf::Sprite *sprites;      // we need 12 sprites for each of the 6 buttons

    int toolbarXOffset = 240;

    int *visibleSpritesTopArr;  // Top array that controls which are visible
                                // 1 = show the top one (unpressed)
                                // 0 = show the one below (pressed)

    const int nrButtons = 6;
    const int widthPx = 16;


    unsigned int toolbarHeightPx = 20;
    unsigned int toolbarWidthPx = widthPx * nrButtons;
};


#endif
