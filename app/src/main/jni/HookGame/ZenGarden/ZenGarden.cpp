//
// Created by Administrator on 2024/3/8.
//

#ifndef PVZ_TV_1_1_5_ZENGARDEN_CPP
#define PVZ_TV_1_1_5_ZENGARDEN_CPP

void (*old_ZenGarden_DrawBackdrop)(int *zenGarden, int *graphics);

void ZenGarden_DrawBackdrop(int *zenGarden, int *graphics) {
    old_ZenGarden_DrawBackdrop(zenGarden, graphics);
}

 enum PottedPlantAge //Prefix: PLANTAGE
{
    Sprout,
    Small,
    Medium,
    Full
};

enum GardenType //Prefix: GARDEN
{
    Main,
    Mushroom,
    Wheelbarrow,
    Aquarium
};

//void ZenGarden_DrawPottedPlant(int *a1,Sexy::Graphics *g, float x,float y,PottedPlant *thePottedPlant,float theScale,bool theDrawPot){
//
//    char aPottedPlantGMemory[sizeof (Sexy::Graphics)];
//    Sexy::Graphics *aPottedPlantG = (Sexy::Graphics*)aPottedPlantGMemory;
//    Sexy_Graphics_Graphics(aPottedPlantG, g);
//    aPottedPlantG->mScaleX = theScale;
//    aPottedPlantG->mScaleY = theScale;
//    SeedType::SeedType mSeedType = (SeedType::SeedType) (thePottedPlant->unk[0] & 0x7F);
//    DrawVariation::DrawVariation aPlantVariation = DrawVariation::Normal;
//    PottedPlantAge mPlantAge = (PottedPlantAge) (thePottedPlant->unk[2] >> 6);
//    GardenType mWhichZenGarden = (GardenType) (thePottedPlant->unk[1] & 3);
//    bool mFacing = thePottedPlant->unk[0] >> 7;
//    if (mPlantAge == Sprout) {
//        if (mSeedType != SeedType::Marigold) {
//            aPlantVariation = DrawVariation::SproutNoFlower;
//        }
//        mSeedType = SeedType::Sprout;
//    } else if ((mSeedType == SeedType::Tanglekelp || mSeedType == SeedType::Seashroom) && mWhichZenGarden == Aquarium) {
//        aPlantVariation = DrawVariation::Aquarium;
//    } else {
//        aPlantVariation = (DrawVariation::DrawVariation) (thePottedPlant->unk[1] >> 4);
//    }
//
//    float aOffsetX = PlantDrawHeightOffset(*((Board **)a1 + 1), NULL, mSeedType, -1, -1);
//    float aOffsetY = 0.0f;
//    if (theDrawPot) {
//        DrawVariation::DrawVariation theDrawVariation2 = DrawVariation::ZenGarden;
//        if (mSeedType == SeedType::Lilypad || mSeedType == SeedType::Tanglekelp || mSeedType == SeedType::Seashroom || mSeedType == SeedType::Cattail) {
//            theDrawVariation2 = DrawVariation::ZenGardenWater;
//        }
//            Plant_DrawSeedType(aPottedPlantG, SeedType::Flowerpot, SeedType::None,theDrawVariation2, x, y);
//    }
//    if (mFacing) { // Left
//        aPottedPlantG->mScaleX = -theScale;
//    }
//
//    if (mPlantAge == Small) {
//        aOffsetX += aPottedPlantG->mScaleX * 40.0;
//        aOffsetY += aPottedPlantG->mScaleY * 20.0;
//        aPottedPlantG->mScaleX *= 0.5;
//        aPottedPlantG->mScaleY *= 0.5;
//    } else if (mPlantAge == Medium) {
//        aOffsetX += aPottedPlantG->mScaleX * 20.0;
//        aOffsetY += aPottedPlantG->mScaleY * 10.0;
//        aPottedPlantG->mScaleX *= 0.75;
//        aPottedPlantG->mScaleY *= 0.75;
//    }
//
//    if ( theDrawPot )
//        aOffsetX += PlantFlowerPotHeightOffset(mSeedType, theScale);
//    Plant_DrawSeedType(aPottedPlantG, mSeedType, SeedType::None, aPlantVariation, aOffsetY + x, aOffsetX + y);
//    Sexy_Graphics_Delete2(aPottedPlantG);
//}

#endif //PVZ_TV_1_1_5_ZENGARDEN_CPP
