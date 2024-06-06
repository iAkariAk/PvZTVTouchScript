//
// Created by Administrator on 2023/10/23.
//

#ifndef PVZ_TV_1_1_5_GLOBALVARIABLE_CPP
#define PVZ_TV_1_1_5_GLOBALVARIABLE_CPP


#include "HookGame/LawnApp/LawnApp.h"
#include "HookGame/Misc/Misc.h"

#define GET_VARIABLE_NAME(variable) #variable
struct ADDON_IMAGES {
    Sexy::Image *pole_night;
    Sexy::Image *trees_night;
    Sexy::Image *googlyeye;
    Sexy::Image *squirrel;
    Sexy::Image *stripe_day_coop;
    Sexy::Image *stripe_pool_coop;
    Sexy::Image *stripe_roof_left;
    Sexy::Image *butter_glove;
    Sexy::Image *custom_cobcannon;
    Sexy::Image *hood1_house;
    Sexy::Image *hood2_house;
    Sexy::Image *hood3_house;
    Sexy::Image *hood4_house;
    Sexy::Image *house_hill_house;
    Sexy::Image *achievement_homeLawnsecurity;
    Sexy::Image *achievement_chomp;
    Sexy::Image *achievement_closeshave;
    Sexy::Image *achievement_coop;
    Sexy::Image *achievement_explodonator;
    Sexy::Image *achievement_garg;
    Sexy::Image *achievement_immortal;
    Sexy::Image *achievement_morticulturalist;
    Sexy::Image *achievement_shop;
    Sexy::Image *achievement_soilplants;
    Sexy::Image *achievement_tree;
    Sexy::Image *achievement_versusz;
    Sexy::Image *hole;
    Sexy::Image *hole_bjorn;
    Sexy::Image *hole_china;
    Sexy::Image *hole_gems;
    Sexy::Image *hole_chuzzle;
    Sexy::Image *hole_heavyrocks;
    Sexy::Image *hole_duwei;
    Sexy::Image *hole_pipe;
    Sexy::Image *hole_tiki;
    Sexy::Image *hole_worm;
    Sexy::Image *hole_top;
    Sexy::Image *plant_can;
    Sexy::Image *zombie_can;
    Sexy::Image *plant_pile01_stack01;
    Sexy::Image *plant_pile01_stack02;
    Sexy::Image *plant_pile02_stack01;
    Sexy::Image *plant_pile02_stack02;
    Sexy::Image *plant_pile03_stack01;
    Sexy::Image *plant_pile03_stack02;
    Sexy::Image *zombie_pile01_stack01;
    Sexy::Image *zombie_pile01_stack02;
    Sexy::Image *zombie_pile01_stack03;
    Sexy::Image *zombie_pile02_stack01;
    Sexy::Image *zombie_pile02_stack02;
    Sexy::Image *zombie_pile02_stack03;
    Sexy::Image *zombie_pile03_stack01;
    Sexy::Image *zombie_pile03_stack02;
    Sexy::Image *zombie_pile03_stack03;
    Sexy::Image *survival_button;
    Sexy::Image *leaderboards;
    Sexy::Image *SelectorScreen_WoodSign3;
    Sexy::Image *SelectorScreen_WoodSign3_press;
    Sexy::Image *zombatar_portrait;
    Sexy::Image *gamerpic;
    Sexy::Image *zombatar_main_bg;
    Sexy::Image *zombatar_widget_bg;
    Sexy::Image *zombatar_widget_inner_bg;
    Sexy::Image *zombatar_background_crazydave;
    Sexy::Image *zombatar_background_menu;
    Sexy::Image *zombatar_background_menu_dos;
    Sexy::Image *zombatar_background_roof;
    Sexy::Image *zombatar_background_blank;
    Sexy::Image *zombatar_background_aquarium;
    Sexy::Image *zombatar_background_crazydave_night;
    Sexy::Image *zombatar_background_day_RV;
    Sexy::Image *zombatar_background_fog_sunshade;
    Sexy::Image *zombatar_background_garden_hd;
    Sexy::Image *zombatar_background_garden_moon;
    Sexy::Image *zombatar_background_garden_mushrooms;
    Sexy::Image *zombatar_background_hood;
    Sexy::Image *zombatar_background_hood_blue;
    Sexy::Image *zombatar_background_hood_brown;
    Sexy::Image *zombatar_background_hood_yellow;
    Sexy::Image *zombatar_background_mausoleum;
    Sexy::Image *zombatar_background_moon;
    Sexy::Image *zombatar_background_moon_distant;
    Sexy::Image *zombatar_background_night_RV;
    Sexy::Image *zombatar_background_pool_sunshade;
    Sexy::Image *zombatar_background_roof_distant;
    Sexy::Image *zombatar_background_sky_day;
    Sexy::Image *zombatar_background_sky_night;
    Sexy::Image *zombatar_background_sky_purple;
    Sexy::Image *zombatar_background_7;
    Sexy::Image *zombatar_background_8;
    Sexy::Image *zombatar_background_9;
    Sexy::Image *zombatar_background_10;
    Sexy::Image *zombatar_background_11;
    Sexy::Image *zombatar_background_11_1;
    Sexy::Image *zombatar_background_12;
    Sexy::Image *zombatar_background_12_1;
    Sexy::Image *zombatar_background_13;
    Sexy::Image *zombatar_background_13_1;
    Sexy::Image *zombatar_background_14;
    Sexy::Image *zombatar_background_14_1;
    Sexy::Image *zombatar_background_15;
    Sexy::Image *zombatar_background_15_1;
    Sexy::Image *zombatar_background_16;
    Sexy::Image *zombatar_background_16_1;
    Sexy::Image *zombatar_background_17;
    Sexy::Image *zombatar_background_17_1;
    Sexy::Image *zombatar_background_bej3_bridge_shroom_castles;
    Sexy::Image *zombatar_background_bej3_canyon_wall;
    Sexy::Image *zombatar_background_bej3_crystal_mountain_peak;
    Sexy::Image *zombatar_background_bej3_dark_cave_thing;
    Sexy::Image *zombatar_background_bej3_desert_pyramids_sunset;
    Sexy::Image *zombatar_background_bej3_fairy_cave_village;
    Sexy::Image *zombatar_background_bej3_floating_rock_city;
    Sexy::Image *zombatar_background_bej3_horse_forset_tree;
    Sexy::Image *zombatar_background_bej3_jungle_ruins_path;
    Sexy::Image *zombatar_background_bej3_lantern_plants_world;
    Sexy::Image *zombatar_background_bej3_lightning;
    Sexy::Image *zombatar_background_bej3_lion_tower_cascade;
    Sexy::Image *zombatar_background_bej3_pointy_ice_path;
    Sexy::Image *zombatar_background_bej3_pointy_ice_path_purple;
    Sexy::Image *zombatar_background_bej3_rock_city_lake;
    Sexy::Image *zombatar_background_bej3_snowy_cliffs_castle;
    Sexy::Image *zombatar_background_bej3_treehouse_waterfall;
    Sexy::Image *zombatar_background_bej3_tube_forest_night;
    Sexy::Image *zombatar_background_bej3_water_bubble_city;
    Sexy::Image *zombatar_background_bej3_water_fall_cliff;
    Sexy::Image *zombatar_background_bejblitz_6;
    Sexy::Image *zombatar_background_bejblitz_8;
    Sexy::Image *zombatar_background_bejblitz_main_menu;
    Sexy::Image *zombatar_background_peggle_bunches;
    Sexy::Image *zombatar_background_peggle_fever;
    Sexy::Image *zombatar_background_peggle_level1;
    Sexy::Image *zombatar_background_peggle_level4;
    Sexy::Image *zombatar_background_peggle_level5;
    Sexy::Image *zombatar_background_peggle_menu;
    Sexy::Image *zombatar_background_peggle_nights_bjorn3;
    Sexy::Image *zombatar_background_peggle_nights_bjorn4;
    Sexy::Image *zombatar_background_peggle_nights_claude5;
    Sexy::Image *zombatar_background_peggle_nights_kalah1;
    Sexy::Image *zombatar_background_peggle_nights_kalah4;
    Sexy::Image *zombatar_background_peggle_nights_master5;
    Sexy::Image *zombatar_background_peggle_nights_renfield5;
    Sexy::Image *zombatar_background_peggle_nights_tut5;
    Sexy::Image *zombatar_background_peggle_nights_warren3;
    Sexy::Image *zombatar_background_peggle_paperclips;
    Sexy::Image *zombatar_background_peggle_waves;
    Sexy::Image *zombatar_hair_1;
    Sexy::Image *zombatar_hair_1_mask;
    Sexy::Image *zombatar_hair_2;
    Sexy::Image *zombatar_hair_2_mask;
    Sexy::Image *zombatar_hair_3;
    Sexy::Image *zombatar_hair_4;
    Sexy::Image *zombatar_hair_5;
    Sexy::Image *zombatar_hair_6;
    Sexy::Image *zombatar_hair_7;
    Sexy::Image *zombatar_hair_8;
    Sexy::Image *zombatar_hair_9;
    Sexy::Image *zombatar_hair_10;
    Sexy::Image *zombatar_hair_11;
    Sexy::Image *zombatar_hair_11_mask;
    Sexy::Image *zombatar_hair_12;
    Sexy::Image *zombatar_hair_12_mask;
    Sexy::Image *zombatar_hair_13;
    Sexy::Image *zombatar_hair_13_mask;
    Sexy::Image *zombatar_hair_14;
    Sexy::Image *zombatar_hair_14_mask;
    Sexy::Image *zombatar_hair_15;
    Sexy::Image *zombatar_hair_15_mask;
    Sexy::Image *zombatar_hair_16;
    Sexy::Image *zombatar_facialhair_1;
    Sexy::Image *zombatar_facialhair_1_mask;
    Sexy::Image *zombatar_facialhair_2;
    Sexy::Image *zombatar_facialhair_3;
    Sexy::Image *zombatar_facialhair_4;
    Sexy::Image *zombatar_facialhair_4_mask;
    Sexy::Image *zombatar_facialhair_5;
    Sexy::Image *zombatar_facialhair_6;
    Sexy::Image *zombatar_facialhair_7;
    Sexy::Image *zombatar_facialhair_8;
    Sexy::Image *zombatar_facialhair_8_mask;
    Sexy::Image *zombatar_facialhair_9;
    Sexy::Image *zombatar_facialhair_9_mask;
    Sexy::Image *zombatar_facialhair_10;
    Sexy::Image *zombatar_facialhair_10_mask;
    Sexy::Image *zombatar_facialhair_11;
    Sexy::Image *zombatar_facialhair_11_mask;
    Sexy::Image *zombatar_facialhair_12;
    Sexy::Image *zombatar_facialhair_12_mask;
    Sexy::Image *zombatar_facialhair_13;
    Sexy::Image *zombatar_facialhair_14;
    Sexy::Image *zombatar_facialhair_14_mask;
    Sexy::Image *zombatar_facialhair_15;
    Sexy::Image *zombatar_facialhair_15_mask;
    Sexy::Image *zombatar_facialhair_16;
    Sexy::Image *zombatar_facialhair_16_mask;
    Sexy::Image *zombatar_facialhair_17;
    Sexy::Image *zombatar_facialhair_18;
    Sexy::Image *zombatar_facialhair_18_mask;
    Sexy::Image *zombatar_facialhair_19;
    Sexy::Image *zombatar_facialhair_20;
    Sexy::Image *zombatar_facialhair_21;
    Sexy::Image *zombatar_facialhair_21_mask;
    Sexy::Image *zombatar_facialhair_22;
    Sexy::Image *zombatar_facialhair_22_mask;
    Sexy::Image *zombatar_facialhair_23;
    Sexy::Image *zombatar_facialhair_23_mask;
    Sexy::Image *zombatar_facialhair_24;
    Sexy::Image *zombatar_facialhair_24_mask;
    Sexy::Image *zombatar_eyewear_1;
    Sexy::Image *zombatar_eyewear_1_mask;
    Sexy::Image *zombatar_eyewear_2;
    Sexy::Image *zombatar_eyewear_2_mask;
    Sexy::Image *zombatar_eyewear_3;
    Sexy::Image *zombatar_eyewear_3_mask;
    Sexy::Image *zombatar_eyewear_4;
    Sexy::Image *zombatar_eyewear_4_mask;
    Sexy::Image *zombatar_eyewear_5;
    Sexy::Image *zombatar_eyewear_5_mask;
    Sexy::Image *zombatar_eyewear_6;
    Sexy::Image *zombatar_eyewear_6_mask;
    Sexy::Image *zombatar_eyewear_7;
    Sexy::Image *zombatar_eyewear_7_mask;
    Sexy::Image *zombatar_eyewear_8;
    Sexy::Image *zombatar_eyewear_8_mask;
    Sexy::Image *zombatar_eyewear_9;
    Sexy::Image *zombatar_eyewear_9_mask;
    Sexy::Image *zombatar_eyewear_10;
    Sexy::Image *zombatar_eyewear_10_mask;
    Sexy::Image *zombatar_eyewear_11;
    Sexy::Image *zombatar_eyewear_11_mask;
    Sexy::Image *zombatar_eyewear_12;
    Sexy::Image *zombatar_eyewear_12_mask;
    Sexy::Image *zombatar_eyewear_13;
    Sexy::Image *zombatar_eyewear_14;
    Sexy::Image *zombatar_eyewear_15;
    Sexy::Image *zombatar_eyewear_16;
    Sexy::Image *zombatar_accessory_1;
    Sexy::Image *zombatar_accessory_2;
    Sexy::Image *zombatar_accessory_3;
    Sexy::Image *zombatar_accessory_4;
    Sexy::Image *zombatar_accessory_5;
    Sexy::Image *zombatar_accessory_6;
    Sexy::Image *zombatar_accessory_8;
    Sexy::Image *zombatar_accessory_9;
    Sexy::Image *zombatar_accessory_10;
    Sexy::Image *zombatar_accessory_11;
    Sexy::Image *zombatar_accessory_12;
    Sexy::Image *zombatar_accessory_13;
    Sexy::Image *zombatar_accessory_14;
    Sexy::Image *zombatar_accessory_15;
    Sexy::Image *zombatar_accessory_16;
    Sexy::Image *zombatar_hats_1;
    Sexy::Image *zombatar_hats_1_mask;
    Sexy::Image *zombatar_hats_2;
    Sexy::Image *zombatar_hats_3;
    Sexy::Image *zombatar_hats_3_mask;
    Sexy::Image *zombatar_hats_4;
    Sexy::Image *zombatar_hats_5;
    Sexy::Image *zombatar_hats_6;
    Sexy::Image *zombatar_hats_6_mask;
    Sexy::Image *zombatar_hats_7;
    Sexy::Image *zombatar_hats_7_mask;
    Sexy::Image *zombatar_hats_8;
    Sexy::Image *zombatar_hats_8_mask;
    Sexy::Image *zombatar_hats_9;
    Sexy::Image *zombatar_hats_9_mask;
    Sexy::Image *zombatar_hats_10;
    Sexy::Image *zombatar_hats_11;
    Sexy::Image *zombatar_hats_11_mask;
    Sexy::Image *zombatar_hats_12;
    Sexy::Image *zombatar_hats_13;
    Sexy::Image *zombatar_hats_14;
    Sexy::Image *zombatar_tidbits_1;
    Sexy::Image *zombatar_tidbits_2;
    Sexy::Image *zombatar_tidbits_3;
    Sexy::Image *zombatar_tidbits_4;
    Sexy::Image *zombatar_tidbits_5;
    Sexy::Image *zombatar_tidbits_6;
    Sexy::Image *zombatar_tidbits_7;
    Sexy::Image *zombatar_tidbits_8;
    Sexy::Image *zombatar_tidbits_9;
    Sexy::Image *zombatar_tidbits_10;
    Sexy::Image *zombatar_tidbits_11;
    Sexy::Image *zombatar_tidbits_12;
    Sexy::Image *zombatar_tidbits_13;
    Sexy::Image *zombatar_tidbits_14;
    Sexy::Image *zombatar_clothes_1;
    Sexy::Image *zombatar_clothes_2;
    Sexy::Image *zombatar_clothes_3;
    Sexy::Image *zombatar_clothes_4;
    Sexy::Image *zombatar_clothes_5;
    Sexy::Image *zombatar_clothes_6;
    Sexy::Image *zombatar_clothes_7;
    Sexy::Image *zombatar_clothes_8;
    Sexy::Image *zombatar_clothes_9;
    Sexy::Image *zombatar_clothes_10;
    Sexy::Image *zombatar_clothes_11;
    Sexy::Image *zombatar_clothes_12;
    Sexy::Image *zombatar_zombie_blank;
    Sexy::Image *zombatar_zombie_blank_skin;
    Sexy::Image *zombatar_zombie_blank_part;
    Sexy::Image *zombatar_zombie_blank_skin_part;
    Sexy::Image *zombatar_display_window;
    Sexy::Image *zombatar_mainmenuback_highlight;
    Sexy::Image *zombatar_finished_button;
    Sexy::Image *zombatar_finished_button_highlight;
    Sexy::Image *zombatar_view_button;
    Sexy::Image *zombatar_view_button_highlight;
    Sexy::Image *zombatar_colors_bg;
    Sexy::Image *zombatar_skin_button;
    Sexy::Image *zombatar_skin_button_highlight;
    Sexy::Image *zombatar_hair_button;
    Sexy::Image *zombatar_hair_button_highlight;
    Sexy::Image *zombatar_fhair_button;
    Sexy::Image *zombatar_fhair_button_highlight;
    Sexy::Image *zombatar_tidbits_button;
    Sexy::Image *zombatar_tidbits_button_highlight;
    Sexy::Image *zombatar_eyewear_button;
    Sexy::Image *zombatar_eyewear_button_highlight;
    Sexy::Image *zombatar_clothes_button;
    Sexy::Image *zombatar_clothes_button_highlight;
    Sexy::Image *zombatar_accessory_button;
    Sexy::Image *zombatar_accessory_button_highlight;
    Sexy::Image *zombatar_hats_button;
    Sexy::Image *zombatar_hats_button_highlight;
    Sexy::Image *zombatar_next_button;
    Sexy::Image *zombatar_prev_button;
    Sexy::Image *zombatar_backdrops_button;
    Sexy::Image *zombatar_backdrops_button_highlight;
    Sexy::Image *zombatar_colorpicker;
    Sexy::Image *zombatar_colorpicker_none;
    Sexy::Image *zombatar_accessory_bg;
    Sexy::Image *zombatar_accessory_bg_highlight;
    Sexy::Image *zombatar_accessory_bg_none;
} Addon_Images;//此处是新增贴图的列表；

struct ADDON_SOUNDS {

    int achievement;

} Addon_Sounds; // 此处是新增音频的列表。注意新增的音频数量有限制，最多新增62个。（最大总音频256个，原版游戏已经使用了194个，还剩62个空余。未来我也许会拓宽此限制。）


void LawnApp_LoadAddonImages(LawnApp *lawnApp) {
    Addon_Images.pole_night = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/pole_night");
    Addon_Images.trees_night = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/trees_night");
    Addon_Images.googlyeye = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/googlyeye");
    Addon_Images.squirrel = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/squirrel");
    Addon_Images.stripe_day_coop = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/stripe_day_coop");
    Addon_Images.stripe_pool_coop = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/stripe_pool_coop");
    Addon_Images.stripe_roof_left = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/stripe_roof_left");
    Addon_Images.butter_glove = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/butter_glove");
    Addon_Images.custom_cobcannon = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/custom_cobcannon");
    Addon_Images.hood1_house = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hood1_house");
    Addon_Images.hood2_house = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hood2_house");
    Addon_Images.hood3_house = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hood3_house");
    Addon_Images.hood4_house = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hood4_house");
    Addon_Images.house_hill_house = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/house_hill_house");
    Addon_Images.achievement_homeLawnsecurity = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_homeLawnsecurity");
    Addon_Images.achievement_chomp = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_chomp");
    Addon_Images.achievement_closeshave = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_closeshave");
    Addon_Images.achievement_coop = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_coop");
    Addon_Images.achievement_explodonator = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_explodonator");
    Addon_Images.achievement_garg = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_garg");
    Addon_Images.achievement_immortal = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_immortal");
    Addon_Images.achievement_shop = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_shop");
    Addon_Images.achievement_soilplants = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_soilplants");
    Addon_Images.achievement_tree = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_tree");
    Addon_Images.achievement_versusz = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_versusz");
    Addon_Images.achievement_morticulturalist = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/achievement_morticulturalist");
    Addon_Images.hole = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole");
    Addon_Images.hole_bjorn = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_bjorn");
    Addon_Images.hole_china = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_china");
    Addon_Images.hole_gems = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_gems");
    Addon_Images.hole_chuzzle = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_chuzzle");
    Addon_Images.hole_heavyrocks = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_heavyrocks");
    Addon_Images.hole_duwei = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_duwei");
    Addon_Images.hole_pipe = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_pipe");
    Addon_Images.hole_tiki = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_tiki");
    Addon_Images.hole_worm = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_worm");
    Addon_Images.hole_top = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/hole_top");
    Addon_Images.plant_can = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/plant_can");
    Addon_Images.zombie_can = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_can");
    Addon_Images.plant_pile01_stack01 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/plant_pile01_stack01");
    Addon_Images.plant_pile01_stack02 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/plant_pile01_stack02");
    Addon_Images.plant_pile02_stack01 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/plant_pile02_stack01");
    Addon_Images.plant_pile02_stack02 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/plant_pile02_stack02");
    Addon_Images.plant_pile03_stack01 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/plant_pile03_stack01");
    Addon_Images.plant_pile03_stack02 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/plant_pile03_stack02");
    Addon_Images.zombie_pile01_stack01 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_pile01_stack01");
    Addon_Images.zombie_pile01_stack02 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_pile01_stack02");
    Addon_Images.zombie_pile01_stack03 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_pile01_stack03");
    Addon_Images.zombie_pile02_stack01 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_pile02_stack01");
    Addon_Images.zombie_pile02_stack02 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_pile02_stack02");
    Addon_Images.zombie_pile02_stack03 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_pile02_stack03");
    Addon_Images.zombie_pile03_stack01 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_pile03_stack01");
    Addon_Images.zombie_pile03_stack02 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_pile03_stack02");
    Addon_Images.zombie_pile03_stack03 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/zombie_pile03_stack03");
    Addon_Images.survival_button = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/survival_button");
    Addon_Images.leaderboards = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/leaderboards");
    Addon_Images.SelectorScreen_WoodSign3 = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/SelectorScreen_WoodSign3");
    Addon_Images.SelectorScreen_WoodSign3_press = LawnApp_GetImageByFileName(lawnApp, "addonFiles/images/ZombatarWidget/SelectorScreen_WoodSign3_press");
    Addon_Images.zombatar_portrait = LawnApp_GetImageByFileName(lawnApp, "ZOMBATAR");

//    int length = (sizeof(Addon_Images) / sizeof(Sexy::Image *));
//    for (int i = 0; i < length; ++i) {
//        if (*((Sexy::Image **) ((char *) &Addon_Images + i * sizeof(Sexy::Image *))) == NULL){
//            LOGD("没成功%d",i);
//        }
//    }

}//此处写明具体每个贴图对应哪个文件。


void LawnApp_LoadAddonSounds(LawnApp *lawnApp) {

    Addon_Sounds.achievement = LawnApp_GetSoundByFileName(lawnApp,"addonFiles/sounds/achievement");

}//此处写明具体每个音频对应哪个文件。
bool isMainMenu = true;

int mBoardBackground = -1;  //当前的场景，白天、黑夜、泳池、雾夜、屋顶、月夜、花园、蘑菇园、水族馆、智慧树

bool requestPause = false;

bool isKeyboardTwoPlayerMode = false;
bool doKeyboardTwoPlayerDialog = false;
bool requestDrawShovelInCursor = false;
Sexy::GameButton* mBoardMenuButton;
Sexy::GameButton* mBoardStoreButton;
//2P黄油绘制
bool requestDrawButterInCursor = false;

int VSBackGround = 0;

bool seedPacketFastCoolDown = false;//选卡冷却开关

bool projectilePierce = false;

bool m1PChoosingSeeds = true;

bool normalLevel = false; //恢复一二周目正常出怪
bool useNewShovel = false;
bool useNewCobCannon = false;
bool showHouse = false;
bool imitater = false;
bool positionAutoFix = false; //自动光标归位
bool useXboxMusic = false;
bool seedBankPin = false; // 无尽置顶种子栏
bool dynamicPreview = false; // 动态种植预览

int speedUpMode = 0;
int speedUpCounter = 0;

//重型武器角度设定
float angle1 = 0;
float angle2 = 1;

int GamepadVelocityXOfPlayer1 = 0;
int GamepadVelocityYOfPlayer1 = 0;
int GamepadVelocityXOfPlayer2 = 0;
int GamepadVelocityYOfPlayer2 = 0;

TouchPlayerIndex::TouchPlayerIndex mPlayerIndex = TouchPlayerIndex::None;
TouchPlayerIndex::TouchPlayerIndex mPlayerIndexSecond = TouchPlayerIndex::None;


FoleyParams gMenuLeftFoley = {FoleyType::MenuLeft,0.0f,{0},1u};

FoleyParams gMenuCenterFoley = {FoleyType::MenuCenter,0.0f,{0},1u};

FoleyParams gMenuRightFoley = {FoleyType::MenuRight,0.0f,{0},1u};


#define randomInt(a, b) (rand()%(b-a+1)+a)//指定范围随机数产生

bool keyboardMode = false;

LeaderboardsWidget* mMainMenuLeaderboardsWidget = NULL;

ZombatarWidget* mMainMenuZombatarWidget = NULL;

int xx,yy,xw,yh;
int xx1,yy1,xw1,yh1;

#endif //PVZ_TV_1_1_5_GLOBALVARIABLE_CPP
