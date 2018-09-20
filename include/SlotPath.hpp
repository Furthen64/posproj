#ifndef SLOTPATH_H
#define SLOTPATH_H

#include <list>

#include "Utilities/Utils.hpp"
#include "SlotPos.hpp"

class SlotPath
{
public:
    SlotPath();

    void drawAllSlots(sf::RenderTarget &rt);
    void add(SlotPos *slotpos);
    SlotPos *stepAndGetGpixPos(int steps);
    void reset();
    void dump();
    bool hasValues();

    SlotPos *nowPos_gpix = nullptr;
    void setListOfSlotPositions(std::list<SlotPos *> *_slotPositions);
    void addListOfSlotPositions(std::list<SlotPos *> *_slotPositions);

    /// \brief Generates a list of SlotPoses for a particular traffic situation
    /// \param posOfReference Allocated HPos with values of where this traffic situation is, with gpix values!
    /// \param textureId 101 for road001, 102 for road002 and so on
    /// \param direction ?? not sure yet. Alpha-0.2 candidate?
    // (--)
    static std::list<SlotPos *> *getSlotPosesOnBlockSituation(CanvasPos *posOfReference, int textureId, int direction)
    {
        std::string cn = "SlotPath.hpp";
        logErr(cn + " getSlotPosesOnBlockSituation stub\n");
        /*


        if(posOfReference == nullptr) {
            std::cout << "ERROR " << cn << " nullptr in to getSlotPosesOnBlockSituation\n";
            return nullptr;
        }


        std::list<SlotPos *> *slotPoses = new std::list<SlotPos *>();

        int xOffset = 0;
        int yOffset = 0;
        int skipStep = 0;

        switch(textureId) {


            // One type of road.... add the others!

            case 101:

                skipStep = 1;
                yOffset = 0; //yOffset = -8;
                xOffset = 0;


                // This needs rethinking
                SlotPos *workPos = nullptr;
                CanvasPos  *hpos = nullptr;

                for(int n = 0; n < 4; n+=skipStep) {

                    // Safer code:
                    hpos = new CanvasPos (
                        (posOfReference->y + n) + yOffset,
                        (posOfReference->x + n) + xOffset ) ;



                    workPos = new SlotPos(hpos);
                    slotPoses->push_back(workPos);
                }

                break;
        }




               case 101: return "ROAD001";
        case 102: return "ROAD002";
        case 103: return "ROAD003";
        case 104: return "ROAD004";
        case 105: return "ROAD005";
        case 106: return "ROAD006";
        case 107: return "ROAD007";
        case 108: return "ROAD008";
        case 109: return "ROAD009";
        case 110: return "ROAD010";


        return slotPoses;

        */

        return nullptr;

    }


private:

    // slotPositions: Is this really the best datastructure for this...? I need to use it like an Array

    std::list<SlotPos *> *slotPositions = nullptr;




};



#endif
