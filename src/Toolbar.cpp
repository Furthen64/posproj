#include "Toolbar.hpp"

#define TOOLBAR_BUTTONS 6
///
/// This is the main toolbar that you see in the top of the editor (maybe even in the game later on)
/// So far it has not much functionality, it just sits there- Some code in Core class for Clicking on Buttons




Toolbar::Toolbar(CanvasPos *_cpos)
{
    cpos = _cpos->clone();



    // Create a pixel rectangle
    crect = new CRect(cpos, new CanvasPos( (int) (cpos->y + toolbarHeightPx), (int) (cpos->x + toolbarWidthPx) ) );

    toolbarXOffset = cpos->x;

    // get the whole texture for all the buttons
    texture.loadFromFile(getFullUri("data\\textures\\TOOLBAR.png"));



    // allocate all the sprites
    sprites = new sf::Sprite[nrButtons*2];
    visibleSpritesTopArr = new int [nrButtons];
    for(int i = 0; i < nrButtons; i++) { visibleSpritesTopArr[i] = true; }


    // map all the sprites correctly
    // position the sprites
    float x, y;

    for(int i = 0; i < nrButtons*2; i++){
        sprites[i] = sf::Sprite(texture);
        sprites[i].setTextureRect( {i*widthPx, 0, 16, 16} );        // HARDCODED

        x = i*widthPx+ toolbarXOffset;
        y = 0;

        sprites[i].setPosition({x,y});
    }

}


void Toolbar::setTopLeft(CanvasPos *_cpos)
{
    cpos = _cpos->clone();

}




// used by Core
/// \brief Sets the graphics of the button to be in "set" state
// (--)
void Toolbar::setButtonPushed(int indexNr)
{
    if(indexNr > nrButtons) {
        std::cout << "ERROR " << cn << " pushButton index out of bounds\n";
    }

    // set the status of the dang thing
    visibleSpritesTopArr[indexNr] = !visibleSpritesTopArr[indexNr];
}



// Figure out what button the user pressed on and return the enum for that menu item
int Toolbar::pushButton(CanvasPos *mousecpos)
{
    int toolbarResult = this->whatButtonDidIPress(mousecpos);
    this-> setButtonPushed(toolbarResult);
    return toolbarResult;
}





// used by Core
// (--)
void Toolbar::resetButton(int indexNr)
{
    visibleSpritesTopArr[indexNr] = true;
}



void Toolbar::resetButtons()
{
    for(int n = 0; n < nrButtons; n++)
    {
        visibleSpritesTopArr[n] = true;
    }

}




// Draws only the visible sprites according to var visibleSpritesTopArr
// (-+)
void Toolbar::draw( sf::RenderTarget& rt)
{
    // draw all the buttons individually
    for(int i = 0; i < nrButtons; i++){
        if(visibleSpritesTopArr[i] == true) {
            sprites[i].setTextureRect( {i*widthPx, 0, 16, 16} );    // Show the top one         HARDCODED
        } else {
            sprites[i].setTextureRect( {i*widthPx, 16, 16, 16} );       // HARDCODED
        }

        rt.draw( sprites[i] );
    }
}





/// \brief Returns true if the given hpos is inside the rectangle of the toolbar
/// \param mousepos An hpos with gpix values set
// (--)
bool Toolbar::inside(CanvasPos *mousecpos)
{

    if(mousecpos == nullptr) { std::cout << "ERROR " << cn << " isPosInsideToolbar nullptr!\n"; return false; }

    return crect->inside(mousecpos);
}


// used by Core
// (-+)
int Toolbar::whatButtonDidIPress(CanvasPos  *mousecpos)
{
    int toolbarInts [TOOLBAR_BUTTONS] {TB_NEW_FILE, TB_SAVE_FILE, TB_LOAD_FILE, TB_ONE, TB_TWO, TB_EXIT};

    if(mousecpos == nullptr) { std::cout << "ERROR " << cn << " isPosInsideToolbar nullptr!\n"; return false; }
    if(crect->topLeft == nullptr) { std::cout << "ERROR " << cn << " toolbar's rect->absStart is nullptr!\n"; return false; }
    if(crect->bottomRight == nullptr) { std::cout << "ERROR " << cn << " toolbar's rect->absEnd is nullptr!\n"; return false; }



    // std::cout << "what button did I press()------------!\n";
    // std::string ind = "   ";

    int buttonStartY = crect->topLeft->y;
    int buttonStartX = crect->topLeft->x;
    int buttonEndY = crect->bottomRight->y;
    int buttonEndX = crect->bottomRight->x;


    for(int n = 0; n < TOOLBAR_BUTTONS; n++) {

        buttonStartY = crect->topLeft->y;
        buttonStartX = crect->topLeft->x + (n *16);

        buttonEndY = crect->bottomRight->y;
        buttonEndX = buttonStartX +  16;

        if(mousecpos->y >= buttonStartY && mousecpos->y <= buttonEndY) {
            if(mousecpos->x >= buttonStartX && mousecpos->x <= buttonEndX) {

               // std::cout << "n=" << n << ",  toolbarInts[n]=" << toolbarInts[n] << " pressed\n";

                return toolbarInts[n];
            }
        }
    }

    std::cout << "Warning" << cn << " whatButtonDidIPress returns TB_NONE\n";
    return TB_NONE;
}




// (++)
CanvasPos *Toolbar::get_cpos() { return cpos; }
CRect *Toolbar::get_crect() {     return crect; }
int *Toolbar::getVisibleSpritesTopArr() {     return visibleSpritesTopArr; }

