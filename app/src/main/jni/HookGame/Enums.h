//
// Created by Administrator on 2024/3/10.
//

#ifndef PVZ_TV_1_1_5_ENUMS_H
#define PVZ_TV_1_1_5_ENUMS_H
// 使用指定的值定义枚举类型
#include "SpecialConstraints.h"

namespace SeedType {
    enum SeedType {//直接从WP复制过来的，怀疑其中有错误，因为TV有重型武器关卡，多了三个种子
        Peashooter = 0,
        Sunflower = 1,
        Cherrybomb = 2,
        Wallnut = 3,
        Potatomine = 4,
        Snowpea = 5,
        Chomper = 6,
        Repeater = 7,
        Puffshroom = 8,
        Sunshroom = 9,
        Fumeshroom = 10,
        Gravebuster = 11,
        Hypnoshroom = 12,
        Scaredyshroom = 13,
        Iceshroom = 14,
        Doomshroom = 15,
        Lilypad = 16,
        Squash = 17,
        Threepeater = 18,
        Tanglekelp = 19,
        Jalapeno = 20,
        Spikeweed = 21,
        Torchwood = 22,
        Tallnut = 23,
        Seashroom = 24,
        Plantern = 25,
        Cactus = 26,
        Blover = 27,
        Splitpea = 28,
        Starfruit = 29,
        Pumpkinshell = 30,
        Magnetshroom = 31,
        Cabbagepult = 32,
        Flowerpot = 33,
        Kernelpult = 34,
        InstantCoffee = 35,
        Garlic = 36,
        Umbrella = 37,
        Marigold = 38,
        Melonpult = 39,
        Gatlingpea = 40,
        Twinsunflower = 41,
        Gloomshroom = 42,
        Cattail = 43,
        Wintermelon = 44,
        GoldMagnet = 45,
        Spikerock = 46,
        Cobcannon = 47,
        Imitater = 48,
        SeedsInChooserCount = 49,
        ExplodeONut = 50,
        GiantWallnut = 51,
        Sprout = 52,
        Leftpeater = 53,
        SeedTypeCount = 54,
        BeghouledButtonShuffle = 55,
        BeghouledButtonCrater = 56,
        SlotMachineSun = 57,
        SlotMachineDiamond = 58,
        ZombiquariumSnorkel = 59,
        ZombiquariumTrophy = 60,
        ZombieTombsTone = 61,
        ZombieNormal = 62,
        ZombieTrashBin = 63,
        ZombieTrafficCone = 64,
        ZombiePolevaulter = 65,
        ZombiePail = 66,
        ZombieFlag = 67,
        ZombieNewsPaper = 68,
        ZombieScreenDoor = 69,
        ZombieFootball = 70,
        ZombieDancer = 71,
        Zomboni = 72,
        ZombieJackInTheBox = 73,
        ZombieDigger = 74,
        ZombiePogo = 75,
        ZombieBungee = 76,
        ZombieLadder = 77,
        ZombieCatapult = 78,
        ZombieGargantuar = 79,
        ZombieUnknown = 80,
        ZombieDuckyTube = 81,
        ZombieSnorkel = 82,
        ZombieDolphinRider = 83,
        ZombieImp = 84,
        ZombieBalloon = 85,
        None = -1
    };
}
namespace ProjectileType {
    enum ProjectileType {
        Pea = 0,
        Snowpea = 1,
        Cabbage = 2,
        Melon = 3,
        Puff = 4,
        Wintermelon = 5,
        Fireball = 6,
        Star = 7,
        Spike = 8,
        Basketball = 9,
        Kernel = 10,
        Cobbig = 11,
        Butter = 12,
        ZombiePea = 13,
        ProjectilesCount
    };
}
namespace ScaryPotType {
    enum ScaryPotType {
        None = 0,
        Seed = 1,
        Zombie = 2,
        Sun = 3
    };
}
namespace AdviceType {
    enum AdviceType {
        None = -1,
        ClickOnSun,
        ClickedOnSun,
        ClickedOnCoin,
        SeedRefresh,
        CantAffordPlant,
        PlantGravebustersOnGraves,
        PlantLilypadOnWater,
        PlantTanglekelpOnWater,
        PlantSeashroomOnWater,
        PlantPotatoMineOnLily,
        PlantWrongArtType,
        PlantNeedPot,
        PlantNotOnGrave,
        PlantNotOnCrater,
        CantPlantThere,
        PlantNotOnWater,
        PlantingNeedsGround,
        BeghouledDragToMatch3,
        BeghouledMatch3,
        BeghouledMatch4,
        BeghouledSaveSun,
        BeghouledUseCrater1,
        BeghouledUseCrater2,
        PlantNotPassedLine,
        PlantOnlyOnRepeaters,
        PlantOnlyOnMelonpult,
        PlantOnlyOnSunflower,
        PlantOnlyOnSpikeweed,
        PlantOnlyOnKernelpult,
        PlantOnlyOnMagnetshroom,
        PlantOnlyOnFumeshroom,
        PlantOnlyOnLilypad,
        PlantNeedsRepeater,
        PlantNeedsMelonpult,
        PlantNeedsSunflower,
        PlantNeedsSpikeweed,
        PlantNeedsKernelpult,
        PlantNeedsMagnetshroom,
        PlantNeedsFumeshroom,
        PlantNeedsLilypad,
        SlotMachinePull,
        HugeWave,
        ShovelRefresh,
        PortalRelocating,
        SlotMachineCollectSun,
        DestroyPotsToFinisihLevel,
        UseShovelOnPots,
        AlmostThere,
        ZombiquariumClickTrophy,
        ZombiquariumCollectSun,
        ZombiquariumClickToFeed,
        ZombiquariumBuySnorkel,
        IZombiePlantsNotReal,
        IZombieNotPassedLine,
        IZombieLeftOfLine,
        SlotMachineSpinAgain,
        IZombieEatAllBrains,
        PeashooterDied,
        StinkySleeping,
        BeghouledNoMoves,
        PlantSunflower5,
        PlantingNeedSleeping,
        ClickToContinue,
        SurviveFlags,
        UnlockedMode,
        NeedWheelbarrow,
        AchievementEarned = 66,
        AdviceTypeCount
    };
}

namespace MessageStyle
{
    enum MessageStyle
    {
        Off = 0,
        TutorialLevel1 = 1,
        TutorialLevel1Stay = 2,
        TutorialLevel2 = 3,
        TutorialLater = 4,
        TutorialLaterStay = 5,
        HintLong = 6,
        HintFast = 7,
        HintStay = 8,
        HintTallFast = 9,
        HintTallUnlockmessage = 10,
        HintTallLong = 11,
        BigMiddle = 12,
        BigMiddleFast = 13,
        HouseName = 14,
        HugeWave = 15,
        SlotMachine = 16,
        ZenGardenLong = 17,
        Achievement = 3
    };
}

namespace ParticleEffect {
    enum ParticleEffect {
        None = -1,
        Melonsplash = 0,
        Wintermelon = 1,
        Fumecloud,
        Popcornsplash = 3,
        Powie = 4,
        Jackexplode,
        ZombieHead,
        ZombieArm,
        ZombieTrafficCone,
        ZombiePail,
        ZombieHelmet,
        ZombieFlag,
        ZombieDoor,
        ZombieTrashCan = 13,
        ZombieNewspaper = 14,
        ZombieHeadlight,
        Pow,
        ZombiePogo,
        ZombieNewspaperHead,
        ZombieBalloonHead,
        SodRoll,
        GraveStoneRise,
        Planting = 22,
        PlantingPool = 23,
        ZombieRise,
        GraveBuster,
        GraveBusterDie,
        PoolSplash,
        IceSparkle,
        SeedPacket = 29,
        TallNutBlock,
        Doom,
        DiggerRise,
        DiggerTunnel,
        DancerRise,
        PoolSparkly = 35,
        WallnutEatSmall,
        WallnutEatLarge,
        PeaSplat = 38,
        ButterSplat =39,
        CabbageSplat = 40,
        PuffSplat = 41,
        StarSplat = 42,
        IceTrap,
        SnowpeaSplat = 44,
        SnowpeaPuff,
        SnowpeaTrail,
        LanternShine,
        SeedPacketPickup,
        PotatoMine,
        PotatoMineRise,
        PuffshroomTrail,
        PuffshroomMuzzle,
        SeedPacketFlash = 53,
        WhackAZombieRise,
        ZombieLadder,
        UmbrellaReflect,
        SeedPacketPick,
        IceTrapZombie,
        IceTrapRelease,
        ZamboniSmoke,
        Gloomcloud,
        ZombiePogoHead,
        ZamboniTire,
        ZamboniExplosion,
        ZamboniExplosion2,
        CatapultExplosion,
        MowerCloud,
        BossIceBall,
        Blastmark = 69,
        CoinPickupArrow = 70,
        PresentPickup,
        ImitaterMorph,
        MoweredZombieHead,
        MoweredZombieArm,
        ZombieHeadPool,
        ZombieBossFireball,
        FireballDeath,
        IceballDeath,
        IceballTrail,
        FireballTrail,
        BossExplosion,
        ScreenFlash,
        TrophySparkle = 83,
        PortalCircle,
        PortalSquare,
        PottedPlantGlow,
        PottedWaterPlantGlow,
        PottedZenGlow,
        MindControl,
        VaseShatter,
        VaseShatterLeaf,
        VaseShatterZombie,
        AwardPickupArrow = 93,
        ZombieSeaweed,
        ZombieMustache,
        ZombieFutureGlasses,
        Pinata = 97,
        DustSquash,
        DustFoot,
        Daisy = 100,
        Starburst,
        UpsellArrow,
        ParticleCount
    };
}


namespace ProjectileMotion {
    enum ProjectileMotion {
        Straight = 0,
        Lobbed = 1,
        Threepeater = 2,
        Bee = 3,
        BeeBackwards = 4,
        Puff = 5,
        Backwards = 6,
        Star = 7,
        FloatOver = 8,
        Homing = 9
    };
}

namespace PlantWeapon
{
     enum PlantWeapon //Prefix: WEAPON
    {
        Primary = 0,
        Secondary = 1
    };
}

namespace GameObjectType {
    enum GameObjectType {
        None = 0,
        Plant = 1,
        Projectile = 2,
        Coin = 3,
        Seedpacket = 4,
        Shovel = 5,
        WateringCan = 6,
        Fertilizer = 7,
        BugSpray = 8,
        Phonograph = 9,
        Chocolate = 10,
        Glove = 11,
        MoneySign = 12,
        Wheelbarrow = 13,
        TreeFood = 14,
        MushRoomGarden = 15,
        QuariumGarden = 16,
        ZenGarden = 17,
        TreeOfWisdomGarden = 18,
        SlotMachineHandle = 22,
        ScaryPot = 23,
        Stinky = 24,
        SeedBankBlank = 49,
        Butter = 50,
    };
}

namespace CursorType {
    enum CursorType {
        Normal = 0,
        PlantFromBank = 1,
        PlantFromUsableCoin = 2,
        PlantFromGlove = 3,
        PlantFromDuplicator = 4,
        PlantFromWheelBarrow = 5,
        Shovel = 6,
        Hammer = 7,
        CobcannonTarget = 8,
        WateringCan = 9,
        Fertilizer = 10,
        BugSpray = 11,
        Phonograph = 12,
        Chocolate = 13,
        Glove = 14,
        MoneySign = 15,
        Wheelbarrow = 16,
        TreeFood = 17,
        MushRoomGarden = 18,
        QuariumGarden = 19,
        ZenGarden = 20,
        TreeOfWisdomGarden = 21
    };
}
namespace TouchState {
    enum TouchState {
        None = 0,
        SeedBank = 1,
        ShovelRect = 2,
        ButterRect = 3,
        Board = 4,
        BoardMovedFromSeedBank = 5,
        BoardMovedFromShovelRect = 6,
        BoardMovedFromButterRect = 7,
        ValidCobCannon = 8,
        UsefulSeedPacket = 9,
        Unused = 10,
        HeavyWeapon = 11,
        PickingSomething = 12,
        ZenGardenTools = 13,
        BoardMovedFromZenGardenTools = 14,
        ValidCobCannonSecond = 15,
    };
}

namespace TouchPlayerIndex {
    enum TouchPlayerIndex {
        None = -1,
        Player1 = 0,
        Player2 = 1
    };
}

namespace CrazyDaveState {
    enum CrazyDaveState {
        Off = 0,
        Entering = 1,
        Leaving = 2,
        Idling = 3,
        Talking = 4,
        HandingTalking = 5,
        HandingIdling = 6
    };
}
namespace BoardResult {
    enum BoardResult {
        None = 0,
        Won = 1,
        Lost = 2,
        Restart = 3,
        Quit = 4,
        QuitApp = 5,
        Cheat = 6,
        VSPlantWon = 7,
        VSZombieWon = 8
    };
}

namespace GameMode {
    enum GameMode {
        Adventure = 0,
        AdventureHide = 1,
        SurvivalNormalStage1 = 2,
        SurvivalNormalStage2 = 3,
        SurvivalNormalStage3 = 4,
        SurvivalNormalStage4 = 5,
        SurvivalNormalStage5 = 6,
        SurvivalHardStage1 = 7,
        SurvivalHardStage2 = 8,
        SurvivalHardStage3 = 9,
        SurvivalHardStage4 = 10,
        SurvivalHardStage5 = 11,
        SurvivalEndlessStage1 = 12,
        SurvivalEndlessStage2 = 13,
        SurvivalEndlessStage3 = 14,
        SurvivalEndlessStage4 = 15,
        SurvivalEndlessStage5 = 16,
        ChallengeWarAndPeas = 17,
        ChallengeWallnutBowling = 18,
        ChallengeSlotMachine = 19,
        ChallengeHeavyWeapon = 20,
        ChallengeBeghouled = 21,
        ChallengeInvisighoul = 22,
        ChallengeSeeingStars = 23,
        ChallengeZombiquarium = 24,
        ChallengeBeghouledTwist = 25,
        ChallengeLittleTrouble = 26,
        ChallengePortalCombat = 27,
        ChallengeColumn = 28,
        ChallengeBobsledBonanza = 29,
        ChallengeSpeed = 30,
        ChallengeWhackAZombie = 31,
        ChallengeLastStand = 32,
        ChallengeWarAndPeas2 = 33,
        ChallengeWallnutBowling2 = 34,
        ChallengePogoParty = 35,
        ChallengeFinalBoss = 36,
        ChallengeArtChallenge1 = 37,
        ChallengeSunnyDay = 38,
        ChallengeResodded = 39,
        ChallengeBigTime = 40,
        ChallengeArtChallenge2 = 41,
        ChallengeAirRaid = 42,
        ChallengeIce = 43,
        ChallengeZenGarden = 44,
        ChallengeHighGravity = 45,
        ChallengeGraveDanger = 46,
        ChallengeShovel = 47,
        ChallengeStormyNight = 48,
        ChallengeBungeeBlitz = 49,
        ChallengeSquirrel = 50,
        ChallengeTreeOfWisdom = 51,
        ScaryPotter1 = 52,
        PuzzleIZombie1 = 53,
        ScaryPotter2 = 54,
        PuzzleIZombie2 = 55,
        ScaryPotter3 = 56,
        PuzzleIZombie3 = 57,
        ScaryPotter4 = 58,
        PuzzleIZombie4 = 59,
        ScaryPotter5 = 60,
        PuzzleIZombie5 = 61,
        ScaryPotter6 = 62,
        PuzzleIZombie6 = 63,
        ScaryPotter7 = 64,
        PuzzleIZombie7 = 65,
        ScaryPotter8 = 66,
        PuzzleIZombie8 = 67,
        ScaryPotter9 = 68,
        PuzzleIZombie9 = 69,
        ScaryPotterEndless = 70,
        PuzzleIZombieEndless = 71,
        Upsell = 72,
        Intro = 73,
        MultiPlayer = 74,
        TwoPlayerVSHide = 75,
        TwoPlayerVS = 76,
        TwoPlayerCoopDay = 79,
        TwoPlayerCoopNight = 80,
        TwoPlayerCoopPool = 81,
        TwoPlayerCoopRoof = 82,
        TwoPlayerCoopBowling = 83,
        TwoPlayerCoopDayHard = 84,
        TwoPlayerCoopNightHard = 85,
        TwoPlayerCoopPoolHard = 86,
        TwoPlayerCoopRoofHard = 87,
        TwoPlayerCoopBoss = 88,
        TwoPlayerCoopEndless = 89,
        ChallengeRainingSeeds = 90,
        ChallengeButteredPopcorn = 91,
        ChallengePoolParty = 92

    };
}


struct HitResult {
    int *mObject;
    GameObjectType::GameObjectType mObjectType;
};


namespace StoreItem {
    enum StoreItem {
        STORE_ITEM_PLANT_GATLINGPEA = 0,
        STORE_ITEM_PLANT_TWINSUNFLOWER = 1,
        STORE_ITEM_PLANT_GLOOMSHROOM = 2,
        STORE_ITEM_PLANT_CATTAIL = 3,
        STORE_ITEM_PLANT_WINTERMELON = 4,
        STORE_ITEM_PLANT_GOLD_MAGNET = 5,
        STORE_ITEM_PLANT_SPIKEROCK = 6,
        STORE_ITEM_PLANT_COBCANNON = 7,
        STORE_ITEM_PLANT_IMITATER = 8,
        STORE_ITEM_BONUS_LAWN_MOWER,
        STORE_ITEM_POTTED_MARIGOLD_1,
        STORE_ITEM_POTTED_MARIGOLD_2,
        STORE_ITEM_POTTED_MARIGOLD_3,
        STORE_ITEM_GOLD_WATERINGCAN = 13,
        STORE_ITEM_FERTILIZER = 14,
        STORE_ITEM_BUG_SPRAY = 15,
        STORE_ITEM_PHONOGRAPH = 16,
        STORE_ITEM_GARDENING_GLOVE = 17,
        STORE_ITEM_MUSHROOM_GARDEN = 18,
        STORE_ITEM_WHEEL_BARROW = 19,
        STORE_ITEM_STINKY_THE_SNAIL = 20,
        STORE_ITEM_PACKET_UPGRADE = 21,
        STORE_ITEM_POOL_CLEANER = 22,
        STORE_ITEM_ROOF_CLEANER = 23,
        STORE_ITEM_RAKE = 24,
        STORE_ITEM_AQUARIUM_GARDEN = 25,
        STORE_ITEM_CHOCOLATE = 26,
        STORE_ITEM_TREE_OF_WISDOM = 27,
        STORE_ITEM_TREE_FOOD = 28,
        STORE_ITEM_FIRSTAID = 29,
        STORE_ITEM_PVZ_ICON = 30,
        STORE_ITEM_BLUEPRINT_BLING = 31,
        STORE_ITEM_BLUEPRINT_SCARY = 32,
        STORE_ITEM_BLUEPRINT_TRAILER = 33,
        STORE_ITEM_BLUEPRINT_FUTURE = 34,
        STORE_ITEM_BLUEPRINT_CLOWN = 35,
        STORE_ITEM_BLUEPRINT_CHANGE = 36,
        STORE_ITEM_INVALID = -1
    };
}

namespace AchievementId {
    enum AchievementId {
        ACHIEVEMENT_HOME_SECURITY = 0, // 完成冒险模式
        ACHIEVEMENT_MORTICULTURALIST = 1, // 收集全部49种植物
        ACHIEVEMENT_IMMORTAL = 2, // 生存泳池无尽达到40波
        ACHIEVEMENT_SOILPLANTS = 3, // 在一个关卡内种植10个豌豆射手
        ACHIEVEMENT_CLOSESHAVE = 4, // 用完全部小推车过一关
        ACHIEVEMENT_CHOMP = 5, // 只使用大嘴花、坚果墙、向日葵过一关
        ACHIEVEMENT_VERSUS = 6, // 对战模式获得5连胜
        ACHIEVEMENT_GARG = 7, // 打败巨人僵尸
        ACHIEVEMENT_COOP = 8, // 通关结盟坚果保龄球关卡
        ACHIEVEMENT_SHOP = 9, // 在戴夫商店消费25000元
        ACHIEVEMENT_EXPLODONATOR = 10, // 使用一个樱桃炸弹消灭10只僵尸
        ACHIEVEMENT_TREE = 11, // 让智慧树长到100英尺高
        MAX_ACHIEVEMENTS
    };
}

enum MainMenuButtonId {
    START_ADVENTURE_BUTTON = 0,
    ADVENTURE_BUTTON = 1,
    MORE_WAYS_BUTTON = 2,
    HOUSE_BUTTON = 3,
    ACHIEVEMENTS_BUTTON = 4,
    HELP_AND_OPTIONS_BUTTON = 5,
    UNLOCK_BUTTON = 6,
    RETURN_TO_ARCADE_BUTTON = 7,
    MORE_BUTTON = 8,
    BACK_STONE_BUTTON = 9,
    VS_BUTTON = 10,
    VS_COOP_BUTTON = 11,
    MINI_GAMES_BUTTON = 12,
    SURVIVAL_BUTTON = 13,
    PUZZLE_BUTTON = 14,
    BACK_POT_BUTTON = 15,
    STORE_BUTTON = 16,
    ZEN_BUTTON = 17,
    ALMANAC_BUTTON = 18,
    MAIL_BUTTON = 19,
    HELP_BAR = 20,



    ACHIEVEMENTS_BACK_BUTTON = 21
};


namespace SeedChooserTouchState {
    enum SeedChooserTouchState {
        ViewLawnButton,
        SeedChooser,
        StoreButton,
        StartButton,
        AlmanacButton,
        None
    };
}

namespace StoreScreenTouchState {
    enum StoreScreenTouchState {
        Prev,
        Next,
        Back,
        None
    };
}
namespace DebugTextMode {
    enum DebugTextMode {
        None = 0,
        ZombieSpawn = 1,
        Music = 2,
        Memory = 3,
        Collision = 4
    };
}
namespace DrawStringJustification {
    enum DrawStringJustification {
        Left = 0,
        Right = 1,
        Center = 2,
        LeftVerticalMiddle = 3,
        RightVerticalMiddle = 4,
        CenterVerticalMiddle = 5
    };
}
namespace TutorialState {
    enum TutorialState {
        Off,
        Level1PickUpPeashooter,
        Level1PlantPeashooter,
        Level1RefreshPeashooter,
        Level1Completed,
        Level2PickUpSunflower,
        Level2PlantSunflower,
        Level2RefreshSunflower,
        Level2Completed,
        MoresunPickUpSunflower,
        MoresunPlantSunflower,
        MoresunRefreshSunflower,
        MoresunCompleted,
        SlotMachinePull,
        SlotMachineCompleted,
        ShovelPickup,
        ShovelDig,
        ShovelKeepDigging,
        ShovelCompleted,
        ZombiquariumBuySnorkel,
        ZombiquariumBoughtSnorkel,
        ZombiquariumClickTrophy,
        ZenGardenPickupWater = 22,
        ZenGardenWaterPlant = 23,
        ZenGardenKeepWatering = 24,
        ZenGardenVisitStore = 25,
        ZenGardenFertilizePlants = 26,
        ZenGardenCompleted = 27,
        WhackAZombieBeforePickSeed,
        WhackAZombiePickSeed,
        WhackAZombieCompleted
    };
}

namespace BackgroundType {
    enum BackgroundType {
        Num1Day = 0,
        Num2Night = 1,
        Num3Pool = 2,
        Num4Fog = 3,
        Num5Roof = 4,
        Num6Boss = 5,
        MushroomGarden = 6,
        Greenhouse = 7,
        Zombiquarium = 8,
        TreeOfWisdom = 9
    };
}

namespace PlantRowType
{
    enum PlantRowType
    {
        Dirt = 0,
        Normal = 1,
        Pool = 2,
        HighGround = 3
    };
}
namespace GridSquareType
{
    enum GridSquareType
    {
        None,
        Grass,
        Dirt,
        Pool,
        HighGround
    };
}
namespace ParticleSystemID
{
    enum ParticleSystemID
    {
        Null
    };
}


namespace PlantingReason {
    enum PlantingReason {
        Ok = 0,
        NotHere=1,
        OnlyOnGraves=2,
        OnlyInPool=3,
        OnlyOnGround=4,
        NeedsPot=5,
        NotOnArt=6,
        NotPassedLine=7,
        NeedsUpgrade=8,
        NotOnGrave=9,
        NotOnCrater=10,
        NotOnWater=11,
        NeedsGround=12,
        NeedsSleeping=13,
        VSModeNotPassedLine = 15,
    };
}


namespace ZombieType
{
    enum ZombieType
    {
        Invalid = -1,
        Normal=0,
        Flag=1,
        TrafficCone=2,
        Polevaulter=3,
        Pail=4,
        Newspaper=5,
        Door=6,
        Football=7,
        Dancer=8,
        BackupDancer=9,
        DuckyTube=10,
        Snorkel=11,
        Zamboni=12,
        Bobsled=13,
        DolphinRider=14,
        JackInTheBox=15,
        Balloon=16,
        Digger=17,
        Pogo=18,
        Yeti=19,
        Bungee=20,
        Ladder=21,
        Catapult=22,
        Gargantuar=23,
        Imp=24,
        Boss=25,
        TrashBin = 26,
        PeaHead=27,
        WallnutHead=28,
        JalapenoHead=29,
        GatlingHead=30,
        SquashHead=31,
        TallnutHead=32,
        RedeyeGargantuar=33,
        ZombieTypesCount = 34,
        CachedPolevaulterWithPole = 35,
        CachedZombieTypesCount = 36
    };
}

namespace ChosenSeedState
{
    enum ChosenSeedState
    {
        SEED_FLYING_TO_BANK = 0,
        SEED_IN_BANK = 1,
        SEED_FLYING_TO_CHOOSER = 2,
        SEED_IN_CHOOSER = 3,
        SEED_PACKET_HIDDEN = 4
    };
}


namespace FoleyType
{
    enum FoleyType
    {
        Splat = 1,
        Throw = 3,
        Plant = 7,
        UseShovel = 8,
        Brains = 12,
        Brains2 = 13,
        Jackinthebox = 14,
        ArtChallenge=15,
        Zamboni=16,
        Thunder=17,
        Frozen=18,
        Zombiesplash=19,
        Bowlingimpact=20,
        Squish=21,
        TirePop=22,
        Explosion=23,
        Slurp=24,
        LimbsPop=25,
        PogoZombie=26,
        SnowPeaSparkles=27,
        ZombieFalling=28,
        Puff=29,
        Fume=30,
        Coin=31,
        KernelSplat=32,
        Digger=33,
        JackSurprise=34,
        VaseBreaking=35,
        PoolCleaner=36,
        Basketball=37,
        Ignite=38,
        Firepea=39,
        Thump=40,
        SquashHmm=41,
        Magnetshroom=42,
        Butter=43,
        BungeeScream=44,
        BossExplosionSmall=45,
        ShieldHit=46,
        Swing=47,
        Bonk=48,
        Rain=49,
        DolphinBeforeJumping=50,
        DolphinAppears=51,
        PlantWater=52,
        ZombieEnteringWater=53,
        Gravebusterchomp=54,
        Cherrybomb=55,
        JalapenoIgnite=56,
        ReverseExplosion=57,
        PlasticHit=58,
        Winmusic=59,
        Ballooninflate=60,
        Bigchomp=61,
        Melonimpact=62,
        Plantgrow=63,
        Shoop=64,
        Juicy=65,
        NewspaperRarrgh=66,
        NewspaperRip=67,
        Floop=68,
        Coffee=69,
        Lowgroan=70,
        Prize=71,
        Yuck=72,
        Umbrella=73,
        Grassstep=74,
        Shovel=75,
        Coblaunch=76,
        Watering=77,
        Polevault=78,
        GravestoneRumble=79,
        DirtRise=80,
        Fertilizer=81,
        Portal=82,
        Wakeup=83,
        Bugspray=84,
        Scream=85,
        Paper=86,
        Moneyfalls=87,
        Imp=88,
        HydraulicShort=89,
        Hydraulic=90,
        Gargantudeath=91,
        Ceramic=92,
        Bossboulderattack=93,
        Chime=94,
        Crazydaveshort=95,
        Crazydavelong=96,
        Crazydaveextralong=97,
        Crazydavecrazy=98,
        Phonograph=99,
        Dancer=100,
        Finalfanfare=101,
        Crazydavescream=102,
        Crazydavescream2=103,
        FoleyCount = 104,
        MenuLeft = 105,
        MenuCenter = 106,
        MenuRight = 107
    };
}


namespace ShieldType {
    enum ShieldType {
        None = 0,
        Door = 1,
        Newspaper = 2,
        Ladder = 3,
        TrashBin = 4
    };
}

namespace HelmType {
    enum HelmType {
        None = 0,
        TrafficCone = 1,
        Pail = 2,
        Football = 3,
        Digger = 4,
        Redeyes = 5,
        Headband = 6,
        Bobsled = 7,
        Wallnut = 8,
        Tallnut = 9
    };
}


namespace FilterEffectType {
    enum FilterEffectType {
        None = -1,
        WashedOut = 0,
        LessWashedOut = 1,
        White = 2,
        FilterEffectCount
    };
}

namespace DrawVariation
{
    enum DrawVariation
    {
        Normal = 0,
        Imitater = 1,
        MarigoldWhite,
        MarigoldMagenta,
        MarigoldOrange,
        MarigoldPink,
        MarigoldLightBlue,
        MarigoldRed,
        MarigoldBlue,
        MarigoldViolet,
        MarigoldLavender,
        MarigoldYellow,
        MarigoldLightGreen,
        ZenGarden = 13,
        ZenGardenWater = 14,
        SproutNoFlower = 15,
        ImitaterLess = 16,
        Aquarium,
        Bigidle
    };
}

namespace ZombiePhase
{
    enum ZombiePhase
    {
        ZombieNormal,
        ZombieDying,
        ZombieBurned,
        ZombieMowered,
        BungeeDiving,
        BungeeDivingScreaming,
        BungeeAtBottom,
        BungeeGrabbing,
        BungeeRising,
        BungeeHitOuchy,
        BungeeCutscene,
        PolevaulterPreVault,
        PolevaulterInVault,
        PolevaulterPostVault,
        RisingFromGrave = 14,
        JackInTheBoxRunning,
        JackInTheBoxPopping,
        BobsledSliding,
        BobsledBoarding,
        BobsledCrashing,
        PogoBouncing,
        PogoHighBounce1,
        PogoHighBounce2,
        PogoHighBounce3,
        PogoHighBounce4,
        PogoHighBounce5,
        PogoHighBounce6,
        PogoForwardBounce2,
        PogoForwardBounce7,
        NewspaperReading,
        NewspaperMaddening,
        NewspaperMad,
        DiggerTunneling,
        DiggerRising,
        DiggerTunnelingPauseWithoutAxe,
        DiggerRiseWithoutAxe,
        DiggerStunned,
        DiggerWalking,
        DiggerWalkingWithoutAxe = 38,
        DiggerCutscene,
        DancerDancingIn = 40,
        DancerSnappingFingers,
        DancerSnappingFingersWithLight,
        DancerSnappingFingersHold,
        DancerDancingLeft,
        DancerWalkToRaise,
        DancerRaiseLeft1,
        DancerRaiseRight1,
        DancerRaiseLeft2,
        DancerRaiseRight2,
        DancerRising,
        DolphinWalking,
        DolphinIntoPool,
        DolphinRiding,
        DolphinInJump,
        DolphinWalkingInPool = 55,
        DolphinWalkingWithoutDolphin,
        SnorkelWalking,
        SnorkelIntoPool,
        SnorkelWalkingInPool = 59,
        SnorkelUpToEat,
        SnorkelEatingInPool,
        SnorkelDownFromEat,
        ZombiquariumAccel,
        ZombiquariumDrift,
        ZombiquariumBackAndForth,
        ZombiquariumBite,
        CatapultLaunching,
        CatapultReloading,
        GargantuarThrowing,
        GargantuarSmashing,
        ImpGettingThrown,
        ImpLanding,
        BalloonFlying,
        BalloonPopping,
        BalloonWalking,
        LadderCarrying,
        LadderPlacing,
        BossEnter,
        BossIdle,
        BossSpawning = 80,
        BossStomping,
        BossBungeesEnter,
        BossBungeesDrop,
        BossBungeesLeave = 84,
        BossDropRv,
        BossHeadEnter,
        BossHeadIdleBeforeSpit,
        BossHeadIdleAfterSpit,
        BossHeadSpit,
        BossHeadLeave,
        YetiRunning,
        SquashPreLaunch,
        SquashRising,
        SquashFalling,
        SquashDoneFalling
    };
}

namespace TopPlant {
    enum TopPlant {
        EatingOrder = 0,
        DiggingOrder = 1,
        BungeeOrder = 2,
        CatapultOrder = 3,
        ZenToolOrder = 4,
        Any = 5,
        OnlyNormalPosition = 6,
        OnlyFlying = 7,
        OnlyPumpkin = 8,
        OnlyUnderPlant = 9
    };
}

namespace ZombieHeight {
    enum ZombieHeight
    {
        ZombieNormal = 0,
        InToPool,
        OutOfPool,
        DraggedUnder,
        UpToHighGround,
        DownOffHighGround,
        UpLadder = 6,
        Falling,
        InToChimney,
        GettingBungeeDropped,
        Zombiquarium
    };
}


namespace Dialogs {
    enum Dialogs {
        DIALOG_NEW_GAME,
        DIALOG_OPTIONS,
        DIALOG_NEWOPTIONS = 2,
        DIALOG_HELPOPTIONS = 3,
        DIALOG_SETTINGS = 4,
        DIALOG_ALMANAC = 5,
        DIALOG_STORE = 6,
        DIALOG_PREGAME_NAG,
        DIALOG_LOAD_GAME,
        DIALOG_CONFIRM_UPDATE_CHECK,
        DIALOG_CHECKING_UPDATES,
        DIALOG_REGISTER_ERROR,
        DIALOG_COLORDEPTH_EXP,
        DIALOG_OPENURL_WAIT,
        DIALOG_OPENURL_FAIL,
        DIALOG_CONFIRM_QUIT = 13,
        DIALOG_HIGH_SCORES,
        DIALOG_NAG,
        DIALOG_INFO,
        DIALOG_GAME_OVER = 16,
        DIALOG_LEVEL_COMPLETE,
        DIALOG_PAUSED = 20,
        DIALOG_NO_MORE_MONEY,
        DIALOG_BONUS,
        DIALOG_CONFIRM_BACK_TO_MAIN = 23,
        DIALOG_CONFIRM_IN_GAME_RESTART = 24,
        DIALOG_THANKS_FOR_REGISTERING,
        DIALOG_NOT_ENOUGH_MONEY = 26,
        DIALOG_UPGRADED = 27,
        DIALOG_NO_UPGRADE,
        DIALOG_CHOOSER_WARNING = 29,
        DIALOG_USERDIALOG,
        DIALOG_CREATEUSER,
        DIALOG_CONFIRMDELETEUSER,
        DIALOG_RENAMEUSER,
        DIALOG_CREATEUSERERROR,
        DIALOG_RENAMEUSERERROR,
        DIALOG_CHEAT = 36,
        DIALOG_CHEATCODE = 37,
        DIALOG_CHEATERROR,
        DIALOG_CONTINUE = 39,
        DIALOG_GETREADY,
        DIALOG_RESTARTCONFIRM = 41,
        DIALOG_CONFIRMPURCHASE,
        DIALOG_CONFIRMSELL,
        DIALOG_TIMESUP,
        DIALOG_VIRTUALHELP,
        DIALOG_JUMPAHEAD,
        DIALOG_CRAZY_DAVE,
        DIALOG_STORE_PURCHASE = 48,
        DIALOG_VISIT_TREE_OF_WISDOM = 49,
        DIALOG_ZEN_SELL = 50,
        DIALOG_MESSAGE = 51,
        DIALOG_IMITATER = 52,
        DIALOG_PURCHASE_PACKET_SLOT = 53,
        DIALOG_PROFILE_CHANGED = 54,
        DIALOG_WAITING_FOR_LEADERBOARD = 56,
        DIALOG_MAIL = 60,
        DIALOG_RETRY_LEADERBOARD = 61,
        DIALOG_RETRY_ACHIEVEMENTS = 62,
        DIALOG_HANDLE_OLDGAMEFILE = 63,
        DIALOG_HANDLE_NODEVICE = 64,
        DIALOG_HANDLE_INVALID_LEVEL = 65,
        DIALOG_PROFILE_LOAD_ERROR = 66,
        DIALOG_PROFILE_SAVE_ERROR = 67,
        DIALOG_CONTENT_LOADING = 68,
        DIALOG_ABOUT,
        RESTART_WARNING,
        DIALOG_UPSELL,
        DIALOG_ACHIEVEMENT_LOCKED,
        DIALOG_UPDATE_NOW,
        DIALOG_MORE_GAMES,
        DIALOG_SKIP_TUTORIAL,
        DIALOG_LEADERBOARD,
        NUM_DIALOGS
    };
}

namespace HouseType {
    enum HouseType {
        Invalid = -1,
        BLUEPRINT_BLING = 0,
        BLUEPRINT_SCARY = 1,
        BLUEPRINT_TRAILER = 2,
        BLUEPRINT_FUTURE = 3,
        BLUEPRINT_CLOWN = 4,
    };
}

namespace MusicTune {
    enum MusicTune {
        None = -1,
        DayGrasswalk = 1,
        NightMoongrains = 2,
        PoolWaterygraves = 3,
        FogRigormormist = 4,
        RoofGrazetheroof = 5,
        ChooseYourSeeds = 6,
        TitleCrazyDaveMainTheme = 7,
        ZenGarden = 8,
        PuzzleCerebrawl = 9,
        MinigameLoonboon = 10,
        Conveyer = 11,
        FinalBossBrainiacManiac = 12,
        ZombiesOnYourLawn = 13,
        MusicTuneCount = 14
    };
}

namespace MusicFile {
    enum MusicFile {
        MUSIC_FILE_NONE = -1,
        MUSIC_FILE_MAIN_MUSIC = 1,
        MUSIC_FILE_DRUMS = 2,
        MUSIC_FILE_DRUMS_NIGHTMOONGRAINS = 3,
        MUSIC_FILE_HIHATS = 4,
        MUSIC_FILE_CREDITS_ZOMBIES_ON_YOUR_LAWN = 5,
        NUM_MUSIC_FILES = 6,
    };
}
namespace MusicBurstState {
    enum MusicBurstState {
        MUSIC_BURST_OFF = 0,
        MUSIC_BURST_STARTING = 1,
        MUSIC_BURST_ON = 2,
        MUSIC_BURST_FINISHING = 3,
    };
}
namespace MusicDrumsState {
    enum MusicDrumsState {
        MUSIC_DRUMS_OFF = 0,
        MUSIC_DRUMS_ON_QUEUED = 1,
        MUSIC_DRUMS_ON = 2,
        MUSIC_DRUMS_OFF_QUEUED = 3,
        MUSIC_DRUMS_FADING = 4,
    };
}

namespace ResType {
    enum ResType {
        ResType_Image,
        ResType_Sound,
        ResType_Font,
        ResType_Music,
        ResType_Reanim,
        ResType_Particle,
        ResType_Trail
    };
}

namespace GridItemState {
    enum GridItemState {
        Normal,
        GravestoneSpecial,
        PortalClosed,
        ScaryPotQuestion,
        ScaryPotLeaf,
        ScaryPotZombie,
        SquirrelWaiting,
        SquirrelPeeking = 7,
        SquirrelRunningUp = 8,
        SquirrelRunningDown = 9,
        SquirrelRunningLeft = 10,
        SquirrelRunningRight = 11,
        SquirrelCaught,
        SquirrelZombie,
        ZenToolWateringCan,
        ZenToolFertilizer,
        ZenToolBugSpray,
        ZenToolPhonograph,
        ZenToolGoldWateringCan,
        StinkyWalkingLeft,
        StinkyTurningLeft,
        StinkyWalkingRight,
        StinkyTurningRight,
        StinkySleeping,
        StinkyFallingAsleep,
        StinkyWakingUp,
        RakeAttracting,
        RakeWaiting,
        RakeTriggered,
        BrainSquished
    };
}
namespace GridItemType {
    enum GridItemType {
        None = 0,
        Gravestone = 1,
        Crater,
        Ladder = 3,
        PortalCircle,
        PortalSquare,
        Brain,
        ScaryPot,
        Squirrel,
        ZenTool,
        Stinky,
        Rake,
        IzombieBrain,
        VSTargetZombie = 14
    };
}

namespace ChallengePage {
    enum ChallengePage {
        CHALLENGE_PAGE_SURVIVAL = 0,
        CHALLENGE_PAGE_CHALLENGE = 1,
        CHALLENGE_PAGE_LIMBO = 2,
        CHALLENGE_PAGE_COOP = 3,
        CHALLENGE_PAGE_PUZZLE = 4,
        MAX_CHALLANGE_PAGES = 5
    };
}
namespace UnlockingState {
    enum UnlockingState {
        Off,
        Shaking,
        Fading
    };
}

namespace CoinMotion {
    enum CoinMotion {
        FromSky = 0,
        FromSkySlow = 1,
        FromPlant = 2,
        Coin = 3,
        LawnmowerCoin = 4,
        FromPresent = 5,
        FromBoss = 6,
        NearCursor = 7,
        FromVSWon = 8,
        FromGrave = 9
    };
}

namespace CoinType {
    enum CoinType {
        None = 0,
        Silver = 1,
        Gold = 2,
        Diamond = 3,
        Sun = 4,
        Smallsun = 5,
        Largesun = 6,
        FinalSeedPacket = 7,
        Trophy = 8,
        Shovel = 9,
        Almanac = 10,
        Carkeys = 11,
        ScaryPot = 12,
        WateringCan = 13,
        Taco = 14,
        Note = 15,
        UsableSeedPacket = 16,
        PresentPlant = 17,
        AwardMoneyBag = 18,
        AwardPresent = 19,
        AwardBagDiamond = 20,
        SunflowerSilverTrophy = 21,
        SunflowerGoldTrophy = 22,
        Chocolate = 23,
        AwardChocolate = 24,
        PresentMinigames = 25,
        PresentPuzzleMode = 26,
        Present32 = 27,
        Present1024 = 28,
        CoopDoubleSun = 29,
        VSZombieBrain = 30,
        VSPlantTrophy = 31,
        VSZombieTrophy = 32
    };
}

namespace GameScenes
{
    enum GameScenes
    {
        Loading = 0,
        Menu = 1,
        LevelIntro = 2,
        Playing = 3,
        ZombiesWon = 4,
        Award = 5,
        Credit = 6,
        Challenge = 7,
        Leaderboard = 8
    };
}

namespace ChallengeState
{
    enum ChallengeState
    {
        Normal = 0,
        BeghouledMoving,
        BeghouledFalling,
        BeghouledNoMatches,
        SlotMachineRolling,
        StormFlash1,
        StormFlash2,
        StormFlash3,
        ZenFading,
        ScaryPotterMalleting,
        LastStandOnslaught = 10,
        TreeJustGrew,
        TreeGiveWisdom,
        TreeWaitingToBabble,
        TreeBabbling,
        ShovelFlashing = 15
    };
}
namespace ReanimatorRenderGroup
{
    enum ReanimatorRenderGroup
    {
        RENDER_GROUP_HIDDEN = -1,
        RENDER_GROUP_NORMAL = 0
    };
}

namespace PlantOnBungeeState
{
    enum PlantOnBungeeState
    {
        NotOnBungee = 0,
        GettingGrabbedByBungee = 1,
        RisingWithBungee = 2
    };
}

namespace PixelFormat
{
    enum PixelFormat
    {
        kPixelFormat_None = -1,
        kPixelFormat_Automatic,
        kPixelFormat_RGBA8888,
        kPixelFormat_RGBA4444,
        kPixelFormat_RGBA5551,
        kPixelFormat_RGB565,
        kPixelFormat_RGB888,
        kPixelFormat_L8,
        kPixelFormat_A8,
        kPixelFormat_LA88,
        kPixelFormat_RGB_PVRTC2,
        kPixelFormat_RGB_PVRTC4,
        kPixelFormat_RGBA_PVRTC2,
        kPixelFormat_RGBA_PVRTC4
    };
}

namespace PlantState
{
     enum PlantState //Prefix: STATE
    {
        Notready,
        Ready,
        Doingspecial,
        SquashLook,
        SquashPreLaunch,
        SquashRising,
        SquashFalling,
        SquashDoneFalling,
        GravebusterLanding,
        GravebusterEating,
        ChomperBiting,
        ChomperBitingGotOne,
        ChomperBitingMissed,
        ChomperDigesting,
        ChomperSwallowing,
        PotatoRising,
        PotatoArmed,
        PotatoMashed,
        SpikeweedAttacking,
        SpikeweedAttacking2,
        ScaredyshroomLowering,
        ScaredyshroomScared,
        ScaredyshroomRaising,
        SunshroomSmall,
        SunshroomGrowing,
        SunshroomBig,
        MagnetshroomSucking,
        MagnetshroomCharging,
        BowlingUp,
        BowlingDown,
        CactusLow,
        CactusRising,
        CactusHigh,
        CactusLowering,
        TanglekelpGrabbing,
        CobcannonArming,
        CobcannonLoading,
        CobcannonReady = 37,
        CobcannonFiring,
        KernelpultButter,
        UmbrellaTriggered,
        UmbrellaReflecting,
        ImitaterMorphing,
        ZenGardenWatered,
        ZenGardenNeedy,
        ZenGardenHappy,
        MarigoldEnding,
        FlowerpotInvulnerable,
        LilypadInvulnerable
    };
}

namespace ReanimLoopType {
    enum ReanimLoopType {
        Loop = 0,
        LoopFullLastFrame = 1,
        PlayOnce = 2,
        PlayOnceAndHold = 3,
        PlayOnceFullLastFrame,
        PlayOnceFullLastFrameAndHold
    };
}

namespace MagnetItemType {
    enum MagnetItemType  {
        None,
        Pail1,
        Pail2,
        Pail3,
        FootballHelmet1,
        FootballHelmet2,
        FootballHelmet3,
        Door1,
        Door2,
        Door3,
        Pogo1,
        Pogo2,
        Pogo3,
        JackInTheBox,
        Ladder1,
        Ladder2,
        Ladder3,
        LadderPlaced,
        SilverCoin,
        GoldCoin,
        Diamond,
        PickAxe
    };
}

namespace DrawMode {
    enum DrawMode {
        DRAWMODE_NORMAL = 0,
        DRAWMODE_ADDITIVE = 1
    };
}
namespace SeedChooserState {
    enum SeedChooserState {
        Normal = 0,
        ViewLawn = 1
    };
}
namespace TodCurves {
    enum TodCurves {
        Constant = 0,
        Linear = 1,
        EaseIn = 2,
        EaseOut = 3,
        EaseInOut = 4,
        EaseInOutWeak = 5,
        FastInOut = 6,
        FastInOutWeak = 7,
        WeakFastInOut = 8,
        Bounce = 9,
        BounceFastMiddle = 10,
        BounceSlowMiddle = 11,
        SinWave = 12,
        EaseSinWave = 13
    };
}

namespace ReanimationType {
    enum ReanimationType {
        None = -1,
        LoadbarSprout = 0,
        LoadbarZombiehead = 1,
        Sodroll,
        FinalWave,
        Peashooter,
        Wallnut,
        Lilypad,
        Sunflower,
        Lawnmower,
        Readysetplant,
        Cherrybomb,
        Squash,
        Doomshroom,
        Snowpea,
        Repeater,
        Sunshroom,
        Tallnut,
        Fumeshroom,
        Puffshroom,
        Hypnoshroom,
        Chomper,
        Zombie = 21,
        Sun = 22,
        Potatomine,
        Spikeweed,
        Spikerock,
        Threepeater,
        Marigold,
        Iceshroom,
        ZombieFootball,
        ZombieNewspaper,
        ZombieZamboni,
        Splash,
        Jalapeno,
        JalapenoFire = 34,
        CoinSilver,
        ZombieCharred,
        ZombieCharredImp,
        ZombieCharredDigger,
        ZombieCharredZamboni,
        ZombieCharredCatapult,
        ZombieCharredGargantuar,
        Scrareyshroom,
        Pumpkin,
        Plantern,
        Torchwood,
        Splitpea,
        Seashroom,
        Blover,
        FlowerPot,
        Cactus,
        Disco,
        Tanglekelp,
        Starfruit,
        Polevaulter,
        Balloon,
        Gargantuar,
        Imp,
        Digger,
        DiggerDirt,
        ZombieDolphinrider,
        Pogo,
        BackupDancer,
        Bobsled,
        Jackinthebox,
        Snorkel,
        Bungee,
        Catapult,
        Ladder,
        Puff,
        Sleeping,
        GraveBuster,
        ZombiesWon,
        Magnetshroom,
        Boss,
        Cabbagepult,
        Kernelpult,
        Melonpult,
        Coffeebean,
        Umbrellaleaf,
        Gatlingpea,
        Cattail,
        Gloomshroom,
        BossIceball,
        BossFireball,
        Cobcannon,
        Garlic,
        GoldMagnet,
        WinterMelon,
        TwinSunflower,
        PoolCleaner,
        RoofCleaner,
        FirePea,
        Imitater,
        Yeti = 94,
        BossDriver,
        LawnMoweredZombie,
        CrazyDave,
        TextFadeOn,
        Hammer,
        SlotMachineHandle,
        SelectorScreen,
        PortalCircle,
        PortalSquare,
        ZengardenSprout,
        ZengardenWateringcan,
        ZengardenFertilizer,
        ZengardenBugspray,
        ZengardenPhonograph,
        Diamond,
        Stinky,
        Rake,
        RainCircle,
        RainSplash,
        ZombieSurprise,
        CoinGold,
        Woodsign,
        ZombieFlagpole = 141,
        LeaderboardsHouse = 147,
        LeaderboardsHouseScene = 148,
        LeaderboardsHouseBgTrees = 149,
        LeaderboardsHouseBgHouses = 150,
        LeaderboardsHouseClouds = 151,
        AchievementHomeSecurity = 162,
        AchievementMorticulturalist = 163,
        AchievementSmartyBranches = 164,
        AchievementCrashOfTheTitan = 165,
        AchievementZffs4Evr = 166,
        AchievementAliveAndPlanting = 167,
        AchievementVersus = 168,
        AchievementSoilYourPlants = 169,
        AchievementExplodonator = 170,
        AchievementCloseShave = 171,
        AchievementShop = 172,
        AchievementNomNomNom = 173,
        ZombatarHead = 178
    };
}

struct ChallengeDefinition {
    GameMode::GameMode mChallengeMode; // 0
    int mChallengeIconIndex; // 1
    ChallengePage::ChallengePage mPage; // 2
    int mRow;// 3 无用
    int mCol;// 4 无用
    const char *mChallengeName; // 5
};

struct PlantDefinition {
    SeedType::SeedType mSeedType; // 0
    int **mPlantImage; // 1
    ReanimationType::ReanimationType mReanimationType; // 2
    int mPacketIndex; // 3
    int mSeedCost; // 4
    int mRefreshTime; // 5
    int mSubClass; // 6
    int mLaunchRate; // 7
    const char *mPlantName; // 8
};


struct ProjectileDefinition {
    ProjectileType::ProjectileType mProjectileType; // 0
    int mImageRow; // 1
    int mDamage; // 2
};

struct ZombieDefinition {
    ZombieType::ZombieType mZombieType; // 0
    ReanimationType::ReanimationType mReanimationType; // 1
    int mZombieValue; // 2
    int mStartingLevel; // 3
    int mFirstAllowedWave; // 4
    int mPickWeight; // 5
    const char *mZombieName; // 6
};

struct ZombiePicker {
    int mZombieCount;
    int mZombiePoints;
    int mZombieTypeCount[ZombieType::ZombieTypesCount];
    int mAllWavesZombieTypeCount[ZombieType::ZombieTypesCount];
};


struct Color {
    int mRed;
    int mGreen;
    int mBlue;
    int mAlpha;
};

struct TRect {
    int mX;
    int mY;
    int mWidth;
    int mHeight;
};

struct MotionTrailFrame{
 float mPosX;
 float mPosY;
 float mAnimTime;
};

struct MagnetItem {
    float mPosX;
    float mPosY;
    float mDestOffsetX;
    float mDestOffsetY;
    MagnetItemType::MagnetItemType mItemType;
};

struct ChosenSeed {
    int mX; // 0
    int mY; // 1
    int mTimeStartMotion; // 2
    int mTimeEndMotion; // 3
    int mStartX; // 4
    int mStartY; // 5
    int mEndX; // 6
    int mEndY; // 7
    int mChosenPlayerIndex; // 8
    SeedType::SeedType mSeedType; // 9
    ChosenSeedState::ChosenSeedState mSeedState; // 10
    int mSeedIndexInBank; // 11
    bool mRefreshing; // 12
    int mRefreshCounter; // 13
    SeedType::SeedType mImitaterType; // 14
    bool mCrazyDavePicked; // 60
};

class Board;
class GamepadControls;
class PlayerInfo;
class PoolEffect;
class Reanimation;
class SeedChooserScreen;
class Music;
class Music2;

class SexyAppBase {
public:
    int* vTable; //0
    int unkMem1[164]; // 1 ~ 164
    int* mWidgetManager; // 165
    int unkMem2[70]; // 166 ~ 235, musicinterface 193
    bool mLawnMouseMode; // 944
    int unkMem3[77]; // 237 ~ 313
    int *mSoundManager; // 314
    int unkMem4[71]; // 315 ~ 385
    bool mIs3DAcclerated; // 1544
    int unkMem5[SexyAppBasePartSize - 387]; // 387 ~ 525
    bool unkBool1 ;// 2104
    bool mGamePad1IsOn; // 2105
    int unkMem6[22]; // 527 ~ 548
    bool unkBool2 ;// 2196
    bool mGamePad2IsOn; // 2197
    int unkMem7[2]; // 550 ~ 551
}; // 115： 552 , 111： 553


struct FoleyParams {
    FoleyType::FoleyType mFoleyType;
    float mPitchRange;
    int* mSfxID[10];
    uint mFoleyFlags;
};

struct FoleyInstance {
    int *mInstance;
    int mRefCount;
    bool _paused;
    int mStartTime;
    int mPauseOffset;
};

struct FoleyTypeData {
    FoleyInstance mFoleyInstances[8];
    int mLastVariationPlayed;
};

struct TodFoley {
    FoleyTypeData mTypeData[110];
};

class ReanimatorCache;


struct FlagsMod {
public:
    int mAddFlags;
    int mRemoveFlags;
};

struct TodSmoothArray {
    int mItem;
    float mWeight;
    float mLastPicked;
    float mSecondLastPicked;
};

struct Insets {
public:
    int mLeft;
    int mTop;
    int mRight;
    int mBottom;
};

class LawnApp;

class Sexy {
public:
    class Image {
    public :
        int* vTable; // 0
        int placeHolder[2]; // 1 ~ 2
        bool unkBool; // 12
        int unkMems1[2]; // 4 ~ 5
        int* stringUnk1; // 6
        int* stringUnk2; // 7
        int* stringUnk3; // 8
        int mWidth; // 9
        int mHeight; // 10
        int mPitch; // 11
        int mStride; // 12
        PixelFormat::PixelFormat mFormat; // 13
        int mPixelFormatHint; // 14
        int mNumRows; // 15
        int mNumCols; // 16
        int *mAnimInfo; // 17
        int unk[6]; // 18 ~ 23
        int mHorizonWrapMode; // 24
        int mVertWrapMode; // 25
        int mTag; // 26
        int unkMems3; // 27 ，实际上Sexy::Image就到这里，下面是MemoryImage的成员
        LawnApp* mApp; // 28
        int unkMems4; // 29
        unsigned int *mBits; // 30
        int mBitsChangedCount; // 31
        int unk1[4]; // 32 ~ 35
        bool mUnkModeRelated; // 144
        bool mUnkMode1; // 145
        bool mUnkMode2; // 146
        bool mUnkBool; // 147
        bool mVolatile; // 148
        int unk2[20]; // 38 ~ 57
    }; // 大小58个整数


public:
    class Font {
    public:
        int *vTable ;
        int mAscent;
        int mAscentPadding;
        int mHeight;
        int mLineSpacingOffset;
    };

public:
    class Graphics {
    public :
        int *vTable; // 0
        Sexy::Image* mDestImage; // 1
        float mTransX; // 2
        float mTransY; // 3
        float mScaleX; // 4
        float mScaleY; // 5
        float unk1[2]; // 6 ~ 7
        TRect mClipRect; //8 ~ 11
        int unk2[3]; // 12 ~ 14
        Color mColorUnknown; // 15 ~ 18
        Color mColor; // 19 ~ 22
        int *mFont; // 23
        DrawMode::DrawMode mDrawMode; // 24
        bool mColorizeImages; // 100
        bool mFastStretch; // 101
        bool unkbool1; // 102
        bool mLinearBlend; // 103
        bool unkbool2; // 104
        bool mGlobalScale; // 105
        bool mGlobalTrackDeviceState; // 106
        int* unkPushPopTramsform; // 27
        int unkInt; // 28
        int m3D; // 29
        int unk3[6]; // 30 ~ 35
    };// 大小36个整数

public:
    class WidgetContainer {
    public:
        int *vTable; // 0
        int mWidgetsUnk[5]; // 1 ~ 5
        int *mWidgetManager; // 6
        WidgetContainer *mParent; // 7
        bool mUpdateIteratorModified; // 32
        int *mUpdateIterator; // 9
        int mLastWMUpdateCount; // 10
        int mUpdateCnt; // 11
        int unkMember; // 12
        int mX; // 13
        int mY; // 14
        int mWidth; // 15
        int mHeight; // 16
        bool mHasAlpha; // 68
        bool mClip; // 69
        FlagsMod mWidgetFlagsMod; // 18 ~ 19
        int mPriority; // 20
        int mZOrder; // 21
        int unk[6]; // 22 ~ 27
        int mWidgetId; // 28
    }; // 大小未知，目前认为是29个整数。反正Widget是64个整数，足够了。

    class Widget : public WidgetContainer {
    public:
        bool mVisible; // 116
        bool mMouseVisible; // 117
        bool mDisabled; // 118
        bool mHasFocus; // 119
        bool mIsDown; // 120
        bool mIsOver; // 121
        bool mHasTransparencies; // 122
        int mColorsUnk[2] ; // 32 ~ 33
        Insets mMouseInsets ; // 34 ~ 37
        bool mDoFinger; // 152
        bool mWantsFocus; // 153
        int unk1[11]; // 38 ~ 48
        Widget* mFocusLinks[4]; // 49 ~ 52 ，上下左右
        int unk2[2]; // 53 ~ 54
        Widget* mFocusedChildWidget; // 55
        int unk3[4]; // 56 ~ 59
        int* mAnimatorForState[4]; // 60 ~ 63
    }; // 大小64个整数！

    class Checkbox : public Widget {
    public:
        int unknownMember[8]; // 64 ~ 71
        int *mListener; // 72
        Image *mUncheckedImage; // 73
        Image *mCheckedImage; // 74
        int mId; // 75
        bool mChecked; // 304
        TRect mCheckedRect; // 77 ~ 80
        TRect mUncheckedRect; // 81 ~ 84
        Color mOutlineColor; // 85 ~ 88
        Color mBkgColor; // 89 ~ 92
        Color mCheckColor; // 93 ~ 96
    }; // 大小97个整数


    class SelectableWidget : public Widget {
    public:
        Color mUnkColor; // 64 ~ 67
        float unkMems[4]; // 68 ~ 71
    }; // 大小72个整数

    struct TextLayout{
        int unk[84];
    }; // 大小84个整数

    class ButtonWidget : public SelectableWidget {
    public:
        int *mLabel; // 72
        int *mStringUnk2; // 73
        TextLayout mTextLayout; // 74 ~ 157
        int unkMem1[9]; // 158 ~ 166
        Insets mInsets; // 167 ~ 170
        int unkMems2[2]; // 171 ~ 172
        Image *mButtonImage; // 173
        Image *mOverImage; // 174
        Image *mDownImage; // 175
        Image *mDisabledImage; // 176
        TRect mNormalRect; // 177 ~ 180
        TRect mOverRect; // 181 ~ 184
        TRect mDownRect; // 185 ~ 188
        TRect mDisabledRect; // 189 ~ 192
        bool unkBool1; // 772
        bool mBtnNoDraw; // 773
        bool unkBool2; // 774
        int unkMems3[2]; // 194 ~ 195
        double mOverAlpha; // 197 ~ 198
        int unkMems4[4]; // 198 ~ 201
        bool unkBool3; // 808
        bool unkBool4; // 809
        int unkMem2; // 203
    }; // 大小204个整数

    class DialogButton :public ButtonWidget {
    public:
        Image* mImage; // 204
        int unkMems4[4]; // 205 ~ 208
        LawnApp* mApp; // 209
    }; // 大小210个整数

    class GameButton : public DialogButton {
    public:
        int unkMems4[2]; // 210  ~ 211
        bool unkBool5; //848
        int unkMems5[2]; // 213 ~ 214
        Sexy::Image* mOverOverlayImage; // 215
        bool mDrawStoneButton; // 864
        int unkMems6[13]; // 217 ~ 229
    }; // 大小230个整数


    class ScrollbarWidget : public Widget {
    public:
        int unkMem; // 64
        Widget *mUpButton; // 65
        Widget *mDownButton; // 66
        bool mInvisIfNoScroll; // 268
        int mId; // 68
        double mValue; // 69 ~ 70
        double mMaxValue; // 71 ~ 72
        double mPageSize; // 73 ~ 74
        bool mHorizontal; // 300
        int mButtonLength; // 76
        bool mPressedOnThumb; // 77
        int mMouseDownThumbPos; // 78
        int mMouseDownX; // 79
        int mMouseDownY; // 80
        int mUpdateMode; // 81
        int mUpdateAcc; // 82
        int mButtonAcc; // 83
        int mLastMouseX; // 84
        int mLastMouseY; // 85
        int *mScrollListener; // 86
        Image* mThumbImage; // 87
        Image* mBarImage; // 88
        Image* mPagingImage; // 89
    }; // 大小90个整数

    class CustomScrollbarWidget : public ScrollbarWidget {
        // 没有新增任何成员，6，这个类不知道什么意义
    }; // 大小90个整数


    class MemoryImage : public Image {

    }; // 大小58个整数

    struct SexyMatrix3 {
        float m[3][3]; // 9
    };

    struct ButtonListenerVTable {
        void *Delete;
        void *Delete2;
        void *ButtonPress;
        void *ButtonPress2;
        void *ButtonDepress;
        void *ButtonDownTick;
        void *ButtonMouseEnter;
        void *ButtonMouseLeave;
        void *ButtonMouseMove;
    };

    struct ButtonListener {
        ButtonListenerVTable* vTable;
    };

    class MenuWidget : public Widget {
    public:
        Sexy::ButtonListener mButtonListener; // 64
        bool mIsFading; // 260
        bool unkBool2; // 261
        int *mMenuParser; // 66
        int *mSourceFileName; // 67
        int unkInt1; // 68
        Sexy::Image* mImage; // 69
    }; // 大小70个整数

    class Dialog : public Widget {
    public:
        Sexy::ButtonListener mButtonListener; // 64
        int *mDialogListener; // 65
        Image* mComponentImage; // 66
        DialogButton* mYesButton; // 67
        DialogButton* mNoButton; // 68
        int mNumButtons; // 69
        int * mDialogHeader; // 70
        int * mDialogFooter; // 71
        int * mDialogLines; // 72
        int * mUnkText; // 73
        TextLayout mTextLayout; // 74 ~ 157
        int unk1[3]; // 158 ~ 160
        int mButtonMode; // 161
        int* mHeaderFont; // 162
        int* mLinesFont; // 163
        int mTextAlign; // 164
        int mLineSpacingOffset; // 165
        int mButtonHeight; // 166
        Insets mBackgroundInsets; // 167 ~ 170
        Insets mContentInsets; // 171 ~ 174
        int mSpaceAfterHeader; // 175
        bool mDragging; // 176
        int mDragMouseX; // 177
        int mDragMouseY; // 178
        int mId; // 179
        bool mIsModal; // 180
        int mResult; // 181
        int mButtonHorzSpacing; // 182
        int mButtonSidePadding; // 183
    }; // 大小184个整数

    enum KeyCode {
        Invalid = -1,
        Ok = 13,
        Back = 27,
        Back2 = 305,
        Left = 37,
        Up = 38,
        Right = 39,
        Down = 40,
        Shovel = 49,
        Hammer = 50
    };

    class WidgetAnimator {
    public:
        int* vTable; // 0
        int unk[2]; // 1 ~ 2
        Widget* mWidget; // 3
        int mUpdateCounter; // 4
        bool mHideOnCompletion; // 20
    };
};

class ReanimTrackWidgetAnimator : public Sexy::WidgetAnimator {
public:
    LawnApp* mApp; // 6
    Sexy::Widget* mLawnMenuWidget; // 7
    int * mTrackName1; // 8
    int * mTrackName2; // 9
    int * mTrackName3; // 10
    int unk2[2]; // 11 ~ 12
};

class CreditScreen;

class MainMenu;

class ChallengeScreen;

class LawnApp : public SexyAppBase {
public:
    Board *mBoard;// 552
    int *mTitleScreen; // 553
    MainMenu *mGameSelector; // 554
    int unk1[2]; // 555 ~ 556
    int *mHelpTextScreen; // 557
    int unkUnk; // 558
    int *mVSSetupScreen; // 559
    int *mVSResultsScreen; // 560
    SeedChooserScreen *mSeedChooserScreen; // 561
    SeedChooserScreen *mZombieChooserScreen; // 562
    int *mAwardScreen; // 563
    CreditScreen* mCreditScreen; // 564
    ChallengeScreen *mChallengeScreen; // 565
    TodFoley *mSoundSystem; // 566
    int *unk3[7]; // 567 ~ 573
    bool mRegisterResourcesLoaded; // 2296
    bool mTodCheatKeys; // 2297
    bool mNewIs3DAccelerated; // 2298，在对齐间隙插入新成员
    GameMode::GameMode mGameMode; // 575
    GameScenes::GameScenes mGameScene; // 576
    bool					mLoadingZombiesThreadCompleted; // 2308
    bool					mFirstTimeGameSelector; // 2309
    int						mGamesPlayed; // 578
    int mMaxExecutions; // 579
    int mMaxPlays; // 580
    int mMaxTime; // 581
    bool mEasyPlantingCheat; // 2328
    PoolEffect *mPoolEffect; // 583
    int *mZenGarden; // 584
    int *mEffectSystem; // 585
    ReanimatorCache *mReanimatorCache; // 586
    PlayerInfo *mPlayerInfo; // 587
    int unk6; // 588
    int *mLastLevelStats; // 589
    bool mCloseRequest; // 2360
    int mAppCounter; // 591
    Music2 *mMusic; // 592
    int mCrazyDaveReanimID; // 593
    CrazyDaveState::CrazyDaveState mCrazyDaveState; // 594
    int mCrazyDaveBlinkCounter; // 595
    int mCrazyDaveBlinkReanimID; // 596
    int mCrazyDaveMessageIndex; // 597
    int *mCrazyDaveMessageText; // 598
    int mAppRandSeed; // 599;
    int unk7; // 600
    int *mProfileMgr; // 601
    int unk8[35]; // 602 ~ 636
    Sexy::Image* mQRCodeImage; // 637
    int unk8_1[7]; // 638 ~ 644
    int mInitialSunMoney; // 645     // 这个数据能给玩家加初始阳光
    bool mIsFullVersion; // 2584
    int unk9[7]; // 647 ~ 653
    BoardResult::BoardResult mBoardResult; // 654
    bool mKilledYetiAndRestarted; // 2620
    int *mKonamiCheck; // 656
    int *mMustacheCheck; // 657
    int *mMoustacheCheck; // 658
    int *mSuperMowerCheck; // 659
    int *mSuperMowerCheck2; // 660
    int *mFutureCheck; // 661
    int *mPinataCheck; // 662
    int *mDanceCheck; // 663
    int *mDaisyCheck; // 664
    int *mSukhbirCheck; // 665
    bool mMustacheMode; // 2664
    bool mSuperMowerMode; // 2665
    bool mFutureMode; // 2666
    bool mPinataMode; // 2667
    bool mDanceMode; // 2668
    bool mDaisyMode; // 2669
    bool mSukhbirMode; // 2670
    int unk10; // 668
    bool mMuteSoundsForCutscene; // 2676
    bool unkBool2; // 2677
    int unk11; // 670
    int mTwoPlayerState; // 671
    int unk12[3]; // 672 ~ 674
    int* mMailBox; // 675
    int unk13[26]; // 676 ~ 701
    int *mHelpBarWidget; // 702
    int unk14; // 703
    int* mLogComposer; // 704
    int* MLogManager; // 705
    int mLaunchTime; // 706
    int* mDaveHelp; // 707
    int* mMaskHelpWidget; // 708
};

struct SexyTransform2D : Sexy::SexyMatrix3 {

};


class ChallengeScreen;

class CutScene {
public:
    LawnApp *mApp; // 0
    Board *mBoard; // 1
    int mCutsceneTime; // 2
    int mSodTime; // 3
    int mGraveStoneTime; // 4
    int mReadySetPlantTime; // 5
    int mFogTime; // 6
    int mBossTime; // 7
    int mCrazyDaveTime; // 8
    int mLawnMowerTime; // 9
    int mCrazyDaveDialogStart; // 10
    bool mSeedChoosing; // 44
    Reanimation *mZombiesWonReanimID; // 12
    bool mPreloaded; // 52
    bool mPlacedZombies; // 53
    bool mPlacedLawnItems; // 54
    int mCrazyDaveCountDown; // 14
    int mCrazyDaveLastTalkIndex; // 15
    bool mUpsellHideBoard; // 64
    ChallengeScreen* mUpsellChallengeScreen; // 17
    bool mPreUpdatingBoard; // 72
    int unk[11];// 19 ~ 29
}; // 大小30个整数

class ReanimatorTrackInstance;

class ReanimatorTransform;

class ReanimatorDefinition;

class Reanimation {
public:
    int unk1[4]; // 0 ~ 3
    ReanimationType::ReanimationType mReanimationType; // 4
    float mAnimTime; // 5
    float mAnimRate; // 6
    ReanimatorDefinition *mDefinition; // 7
    ReanimLoopType::ReanimLoopType mLoopType; // 8
    bool mDead; // 36
    int mFrameStart; // 10
    int mFrameCount; // 11
    int mFrameBasePose; // 12
    SexyTransform2D mOverlayMatrix; // 13 ~ 21
    Color mColorOverride; // 22 ~ 25
    ReanimatorTrackInstance* mTrackInstances; // 26
    int mLoopCount; // 27
    int*  mReanimationHolder; // 28
    bool mIsAttachment; // 116
    int mRenderOrder; // 30
    Color mExtraAdditiveColor; // 31 ~ 34
    bool mEnableExtraAdditiveDraw; // 140
    Color mExtraOverlayColor; // 36 ~ 39
    bool mEnableExtraOverlayDraw; // 160
    float mLastFrameTime; // 41
    FilterEffectType::FilterEffectType mFilterEffect; // 42
    Color mUnkColor; // 43 ~ 46
    int unk2[4]; // 47 ~ 50
    ReanimatorTransform *mReanimatorTransforms; // 51
    bool unkBool; // 208
    float unkFloatWithInitialValue_1; // 53
    int mReanimationID; // 54
}; // 大小55个整数

class GameObject {
public:
    int* vTable; // 0
    int placeHolder[3]; // 1 ~ 3
    LawnApp *mApp; // 4
    Board *mBoard; // 5
    int mX; // 6
    int mY; // 7
    int mWidth; // 8
    int mHeight; // 9
    bool mVisible; // 40
    int mRow; // 11
    int mRenderOrder; // 12
}; // 大小13个整数

class SeedBank;

class SeedPacket : public GameObject {
public:
    int mRefreshCounter; // 13
    int mRefreshTime;  //14
    int mIndex; // 15
    int mOffsetY; // 16
    SeedType::SeedType mPacketType; // 17
    SeedType::SeedType mImitaterType; // 18
    int mSlotMachineCountDown; // 19
    SeedType::SeedType mSlotMachiningNextSeed; // 20
    float mSlotMachiningPosition; // 21
    bool mActive; // 88
    bool mRefreshing; // 89
    int mTimesUsed; // 23
    SeedBank *mSeedBank; // 24
    float mLastSelectedTime; // 25
    int unknownIntMember1;  // 26
    int unknownIntMember2; // 27
    bool mSelectedBy2P; // 112
    bool mSelectedBy1P; // 113
}; // 大小29个整数

class Coin : public GameObject {
public:
    float mPosX; // 13
    float mPosY; // 14
    float mPrevPosX; // 15
    float mPrevPosY; // 16
    float mVelX; // 17
    float mVelY; // 18
    float mScale; // 19
    bool mDead; // 80
    int mFadeCount; // 21
    float mCollectX; // 22
    float mCollectY; // 23
    int mGroundY; // 24
    int mCoinAge; // 25
    bool mIsBeingCollected; // 104
    int mCollectedByPlayerIndex; // 27
    int mDisappearCounter; // 28
    CoinType::CoinType mType; // 29
    CoinMotion::CoinMotion mCoinMotion; // 30
    int mAttachment[3]; // 31 ~ 33
    float mCollectionDistance; // 34
    SeedType::SeedType mUsableSeedType; // 35
    int *mPottedPlantSpec; // 36
    int unknownMember[4]; // 37 ~ 40
    bool mNeedsBouncyArrow; // 164
    bool mHasBouncyArrow; // 165
    bool mHitGround; // 166
    int mTimesDropped; // 42
    int mPlayerIndex; // 43
    float unk2; // 44
    bool unk3; // 180
    int unk4; // 46
    bool unk5; // 188
    int mAutoCollectAge; // 48
    bool unk7; // 196
    bool unk8; // 197
    int unkInt; // 50
}; // 大小51个整数


class Zombie;

class Plant : public GameObject {
public:
    SeedType::SeedType mSeedType; // 13
    int mPlantCol; // 14
    int mAnimCounter; // 15
    int mFrame; // 16
    int mFrameLength; // 17
    int mNumFrames; // 18
    PlantState::PlantState mState; // 19
    int mPlantHealth; // 20
    int mPlantMaxHealth; // 21
    int mSubclass; // 22
    int mDisappearCountdown; // 23
    int mDoSpecialCountdown; // 24
    int mStateCountdown; // 25
    int mLaunchCounter; // 26
    int mLaunchRate; // 27
    TRect mPlantRect; // 28 ~ 31
    TRect mPlantAttackRect; // 32 ~ 35
    int mTargetX; // 36
    int mTargetY; // 37
    int mStartRow; // 38
    int *mParticleID; // 39
    int mShootingCounter; // 40
    int mBodyReanimID; // 41
    int mHeadReanimID; // 42
    int mHeadReanimID2; // 43
    int mHeadReanimID3; // 44
    int mBlinkReanimID; // 45
    int mLightReanimID; // 46
    int mSleepingReanimID; // 47
    int mBlinkCountdown; // 48
    int mRecentlyEatenCountdown; // 49
    int mEatenFlashCountdown; // 50
    int mBeghouledFlashCountdown; // 51
    float mShakeOffsetX; // 52
    float mShakeOffsetY; // 53
    MagnetItem mMagnetItems[5]; // 54 ~ 78
    int mTargetZombieID; // 79
    int mWakeUpCounter; // 80
    PlantOnBungeeState::PlantOnBungeeState mOnBungeeState; // 81
    SeedType::SeedType mImitaterType; // 82
    int mPottedPlantIndex; // 83
    bool mAnimPing; // 336
    bool mDead; // 337
    bool mSquished; // 338
    bool mIsAsleep; // 339
    bool mIsOnBoard; // 340
    bool mHighlighted; // 341
    bool mInFlowerPot; // 342
    bool mGloveGrabbed; // 343
    int unk; // 86
    int mPlantIndexInList; // 87
}; // 大小88个整数

class Zombie : public GameObject {
public:
    ZombieType::ZombieType mZombieType; // 13
    ZombiePhase::ZombiePhase mZombiePhase; // 14
    float mPosX; // 15
    float mPosY; // 16
    float mVelX; // 17
    int mAnimCounter; // 18
    int mGroanCounter; // 19
    int mAnimTicksPerFrame; // 20
    int mAnimFrames; // 21
    int mFrame; // 22
    int mPrevFrame; // 23
    bool mVariant; // 96
    bool mIsEating; // 97
    int mJustGotShotCounter; // 25
    int mShieldJustGotShotCounter; // 26
    int mShieldRecoilCounter; // 27
    int mZombieAge; // 28
    ZombieHeight::ZombieHeight mZombieHeight; // 29
    int mPhaseCounter; // 30
    int mFromWave; // 31
    bool mDroppedLoot; // 128
    int mZombieFade; // 33
    bool mFlatTires;  // 136
    int mUseLadderCol; // 35
    int mTargetCol; // 36
    float mAltitude; // 37
    bool mHitUmbrella; // 152
    TRect mZombieRect; // 39 ~ 42
    TRect mZombieAttackRect ; // 43 ~ 46
    int mChilledCounter; // 47
    int mButteredCounter; // 48
    int mIceTrapCounter; // 49
    bool mMindControlled; // 200
    bool mBlowingAway; // 201
    bool mHasHead; // 202
    bool mHasArm; // 203
    bool mHasObject; // 204
    bool mInPool; // 205
    bool mOnHighGround; // 206
    bool mYuckyFace; // 207
    int mYuckyFaceCounter; // 52
    HelmType::HelmType mHelmType; // 53
    int mBodyHealth; // 54
    int mBodyMaxHealth; // 55
    int mHelmHealth; // 56
    int mHelmMaxHealth; // 57
    ShieldType::ShieldType mShieldType; // 58
    int mShieldHealth; // 59
    int mShieldMaxHealth; // 60
    int mFlyingHealth; // 61
    int mFlyingMaxHealth; // 62
    bool mDead; // 252
    Zombie *mRelatedZombieID; // 64
    Zombie *mFollowerZombieID[4]; // 65 ~ 68
    bool mPlayingSong; // 276
    int mParticleOffsetX; // 70
    int mParticleOffsetY; // 71
    int* mAttachmentID; // 72
    int mSummonCounter; // 73
    int mBodyReanimID; // 74
    float mScaleZombie; // 75
    float mVelZ; //76
    float mOrginalAnimRate; // 77
    Plant *mTargetPlantID; // 78
    int mBossMode; // 79
    int mTargetRow; // 80
    int mBossBungeeCounter; // 81
    int mBossStompCounter; // 82
    int mBossHeadCounter; // 83
    int mBossFireBallReanimID; // 84
    int mSpecialHeadReanimID; // 85
    int mFireballRow; // 86
    bool mIsFireBall; // 348
    int mMoweredReanimID; // 88
    int mLastPortalX; // 89
    bool mBloated; // 360
    int unkMems[6]; // 91 ~ 96
    int mZombieID; // 97
}; // 大小98个整数

class GridItem {
public :
    int placeHolder[4];
    LawnApp* mApp; // 4
    Board* mBoard; // 5
    GridItemType::GridItemType mGridItemType; // 6
    GridItemState::GridItemState mGridItemState; // 7
    int mGridX; // 8
    int mGridY; // 9
    int mGridItemCounter; // 10
    int mRenderOrder; // 11
    bool mDead; // 48
    float mPosX; // 13
    float mPosY; // 14
    float mGoalX; // 15
    float mGoalY; // 16
    Reanimation *mGridItemReanimID; // 17
    int *mGridItemParticleID; // 18
    ZombieType::ZombieType mZombieType; // 19
    SeedType::SeedType mSeedType; // 20
    ScaryPotType::ScaryPotType mScaryPotType; // 21
    bool mHighlighted; // 88
    int mTransparentCounter; // 23
    int mSunCount; // 24
    MotionTrailFrame mMotionTrailFrames[12]; // 25 ~ 60
    int mMotionTrailCount; // 61
    int unkMems[14]; // 62 ~ 75
}; // 大小76个整数


class SeedChooserScreen : public Sexy::Widget {
public:
    Sexy::ButtonListener mButtonListener; // 64
    int unkMem1; // 65
    Sexy::GameButton* mImitaterButton; // 66
    ChosenSeed mChosenSeeds[54]; // 67 ~ 930
    LawnApp *mApp; // 931
    Board *mBoard; // 932
    int mSeedChooserAge; // 933
    int mSeedsInFlight; // 934
    int mSeedsInBothBank; // 935
    int mSeedsIn1PBank; // 936
    int unkMem2; // 937
    int *mToolTipWidget1; // 938
    int *mToolTipWidget2; // 939
    int mToolTipWidgetState1; // 940
    int mToolTipWidgetState2; // 941
    int mCursorPositionX1; // 942
    int mCursorPositionX2; // 943
    int mCursorPositionY1; // 944
    int mCursorPositionY2; // 945
    SeedChooserState::SeedChooserState mChooseState; // 946
    int mViewLawnTime; // 947
    bool unkBool; // 3792
    int mPlayerIndex; // 949
    SeedType::SeedType mSeedType1; // 950
    SeedType::SeedType mSeedType2; // 951
    float unkF; // 952
    bool mIsZombieChooser; // 3812
    SeedBank *mSeedBank1; // 954
    SeedBank *mSeedBank2; // 955
    int unkCounter; // 956
    int mImitaterDialogOpened; // 957
    Sexy::GameButton* mViewLawnButton; // 958
    Sexy::GameButton* mStoreButton; // 959
    Sexy::GameButton* mStartButton; // 960
    Sexy::GameButton* mAlmanacButton; // 961
    int unkMems3[4]; // 962 ~ 965
}; // 大小966个整数

class Projectile : public GameObject {
public:
    int mFrame; // 13
    int mNumFrames; // 14
    int mAnimCounter; // 15
    float mPosX; // 16
    float mPosY; // 17
    float mPosZ; // 18
    float mVelX; // 19
    float mVelY; // 20
    float mVelZ; // 21
    float mAccZ; // 22
    float mShadowY; // 23
    bool mDead; // 96
//    short mNewProjectileLastX; // 在对齐空隙新增成员，98 ~ 99
    int mAnimTicksPerFrame; // 25
    ProjectileMotion::ProjectileMotion mMotionType; // 26
    ProjectileType::ProjectileType mProjectileType; // 27
    int mProjectileAge; // 28
    int mClickBackoffCounter; // 29
    float mRotation; // 30
    float mRotationSpeed; // 31
    bool mOnHighGround; // 128
//    short mNewProjectileLastY; // 在对齐空隙新增成员，130 ~ 131
    int mDamageRangeFlags; // 33
    int mHitTorchwoodGridX; // 34
    int *mAttachmentID; // 35
    float mCobTargetX; // 36
    int mCobTargetRow; // 37
    Zombie *mTargetZombieID; // 38
    int mLastPortalX; // 39
    int unkInt; // 40
}; // 大小41个整数


class CursorObject : public GameObject {
public:
    int mSeedBankIndex; // 13
    SeedType::SeedType mType; // 14
    SeedType::SeedType mImitaterType; // 15
    CursorType::CursorType mCursorType; // 16
    Coin *mCoinID; // 17
    Plant *mGlovePlantID; // 18
    Plant *mDuplicatorPlantID; // 19
    Plant *mCobCannonPlantID; // 20
    int mHammerDownCounter; // 21
    int mReanimCursorID; // 22
}; // 大小23个整数



class CursorPreview : public GameObject {
public:
 int mGridX; // 13
 int mGridY; // 14
 int playerIndex; // 15
};// 大小16个整数

struct ShopSeedPacket {
    int unknown[21];
}; // 大小21个整数

class SeedBank : public GameObject {
public :
    int mNumPackets; // 13
    int mCutSceneDarken; // 14
    int mConveyorBeltCounter; // 15
    bool mPlayerIndex; // 64
    int* mToolTipWidget; // 17
    SeedPacket mSeedPackets[10]; // 18 ~ 307
    ShopSeedPacket mShopSeedPackets[7]; // 308 ~ 354
    int unknownMembers[100]; // 355 ~ 454
}; // 大小455个整数

class MessageWidget;

class Challenge;

struct PlantRbTree {
    int unk[6];
};

class Board : public Sexy::Widget {
public:
    Sexy::ButtonListener mButtonListener; // 64
    int unknownMembers1[4]; // 65 ~ 68
    LawnApp* mApp; // 69
    Zombie *mZombiesBlock; // 70
    unsigned int mZombiesMaxUsedCount; // 71
    unsigned int mZombiesMaxSize; // 72
    unsigned int mZombiesFreeListHead; // 73
    unsigned int mZombiesSize; // 74
    unsigned int mZombiesNextKey; // 75
    const char *mZombiesName; // 76
    Plant *mPlantsBlock; // 77
    unsigned int mPlantsMaxUsedCount; // 78
    unsigned int mPlantsMaxSize; // 79
    unsigned int mPlantsFreeListHead; // 80
    unsigned int mPlantsSize; // 81
    unsigned int mPlantsNextKey; // 82
    const char *mPlantsName; // 83
    Projectile *mProjectilesBlock; // 84
    unsigned int mProjectilesMaxUsedCount; // 85
    unsigned int mProjectilesMaxSize; // 86
    unsigned int mProjectilesFreeListHead; // 87
    unsigned int mProjectilesSize; // 88
    unsigned int mProjectilesNextKey; // 89
    const char *mProjectilesName; // 90
    Coin *mCoinsBlock; // 91
    unsigned int mCoinsMaxUsedCount; // 92
    unsigned int mCoinsMaxSize; // 93
    unsigned int mCoinsFreeListHead; // 94
    unsigned int mCoinsSize; // 95
    unsigned int mCoinsNextKey; // 96
    const char *mCoinsName; // 97
    int *mLawnMowersBlock; // 98
    unsigned int mLawnMowersMaxUsedCount; // 99
    unsigned int mLawnMowersMaxSize; // 100
    unsigned int mLawnMowersFreeListHead; // 101
    unsigned int mLawnMowersSize; // 102
    unsigned int mLawnMowersNextKey; // 103
    const char *mLawnMowersName; // 104
    GridItem *mGridItemsBlock; // 105
    unsigned int mGridItemsMaxUsedCount; // 106
    unsigned int mGridItemsMaxSize; // 107
    unsigned int mGridItemsFreeListHead; // 108
    unsigned int mGridItemsSize; // 109
    unsigned int mGridItemsNextKey; // 110
    const char *mGridItemsName; // 111
    PlantRbTree mTangleKelpTree; // 112 ~ 117
    PlantRbTree mFlowerPotTree; // 118 ~ 123
    PlantRbTree mPumpkinTree; // 124 ~ 129
    MessageWidget *mAdvice; // 130
    SeedBank *mSeedBank1; // 131
    SeedBank *mSeedBank2; // 132
    int unknownMembers3[7]; // 133 ~ 139
    GamepadControls * mGamepadControls1; // 140
    GamepadControls * mGamepadControls2; // 141
    CursorObject *mCursorObject1; // 142
    CursorObject *mCursorObject2; // 143
    CursorPreview *mCursorPreview1; // 144
    CursorPreview *mCursorPreview2; // 145
    int *mToolTipWidget; // 146
    int *mToolTipFont; // 147
    CutScene *mCutScene; // 148
    Challenge *mChallenge; // 149
    bool unknownBool; // 600
    bool mPaused; // 601
    GridSquareType::GridSquareType mGridSquareType[9][6]; // 151 ~ 204
    int mGridCelLook[9][6]; // 205 ~ 258
    int mGridCelOffset[9][6][2]; // 259 ~ 366
    int mGridCelFog[9][7]; // 367 ~ 429
    bool mEnableGraveStones; // 1720
    int mSpecialGraveStoneX; // 431
    int mSpecialGraveStoneY; // 432
    float mFogOffset; // 433
    int mOffsetMoved; // 434
    int mCoverLayerAnimIDs[7];// 435 ~ 441
    int mFogBlownCountDown; // 442
    PlantRowType::PlantRowType mPlantRow[6]; // 443 ~ 448
    int mWaveRowGotLawnMowered[6]; // 449 ~ 454
    int mBonusLawnMowersRemaining; // 455
    int mIceMinX[6]; // 456 ~ 461
    int mIceTimer[6]; // 462 ~ 467
    ParticleSystemID::ParticleSystemID mIceParticleID[6]; // 468 ~ 473
    TodSmoothArray mRowPickingArray[6]; // 474 ~ 497
    ZombieType::ZombieType mZombiesInWave[100][50]; // 498 ~ 5497
    bool mZombieAllowed[100]; // 5498 ~ 5522
    int mSunCountDown; //5523
    int mNumSunsFallen; // 5524
    int mShakeCounter; // 5525
    int mShakeAmountX; // 5526
    int mShakeAmountY; // 5527
    BackgroundType::BackgroundType mBackgroundType; // 5528
    int mLevel; // 5529
    int mSodPosition; // 5530
    int mPrevMouseX; // 5531
    int mPrevMouseY; // 5532
    int mSunMoney1; // 5533
    int mSunMoney2; // 5534
    int mDeathMoney; // 5535
    int mNumWaves; // 5536
    int mMainCounter; // 5537
    int mEffectCounter; // 5538
    int mDrawCount; // 5539
    int mRiseFromGraveCounter; // 5540
    int mOutOfMoneyCounter; // 5541
    int mCurrentWave; // 5542
    int mTotalSpawnedWaves; // 5543
    TutorialState::TutorialState mTutorialState; // 5544
    int* mTutorialParticleID; // 5545
    int mTutorialTimer; // 5546
    int mLastBungeeWave; // 5547
    int mZombieHealthToNextWave; // 5548
    int mZombieHealthWaveStart; // 5549
    int mZombieCountDown; // 5550
    int mZombieCountDownStart; // 5551
    int mHugeWaveCountDown; // 5552
    bool mHelpDisplayed[72]; // 5553 ~ 5570
    AdviceType::AdviceType mHelpIndex; // 5571
    bool mFinalBossKilled; // 22288
    bool mShowShovel; // 22289
    bool mShowButter; // 22290
    bool mShowHammer; // 22291
    int mCoinBankFadeCount; // 5573
    DebugTextMode::DebugTextMode mDebugTextMode; // 5574
    bool mLevelComplete; // 22300
    bool mNewWallNutAndSunFlowerAndChomperOnly; // 在对齐间隙插入成员，22301
    char mNewPeaShooterCount; // 在对齐间隙插入成员，22302
    int mBoardFadeOutCounter; // 5576
    int mNextSurvivalStageCounter; // 5577
    int mScoreNextMowerCounter; // 5578
    bool mLevelAwardSpawned; // 22316
    int mProgressMeterWidth; // 5580
    int mFlagRaiseCounter; // 5581
    int mIceTrapCounter; // 5582
    int mBoardRandSeed; // 5583
    int mPoolSparklyParticleID; // 5584
    Reanimation *mFwooshID[6][12]; // 5585 ~ 5656
    int mFwooshCountDown; // 5657
    int mTimeStopCounter; // 5658
    bool mDroppedFirstCoin; // 22636
    int mFinalWaveSoundCounter; // 5660
    int mCobCannonCursorDelayCounter; // 5661
    int mCobCannonMouseX; // 5662
    int mCobCannonMouseY; // 5663
    bool mKilledYeti; // 22656
    bool mMustacheMode; // 22657
    bool mSuperMowerMode; // 22658
    bool mFutureMode; // 22659
    bool mPinataMode; // 22660
    bool mDanceMode; // 22661
    bool mDaisyMode; // 22662
    bool mSukhbirMode; // 22663
    int mPrevBoardResult; // 5666
    int mTriggeredLawnMowers; // 5667
    int mPlayTimeActiveLevel; // 5668
    int mPlayTimeInactiveLevel; // 5669
    int mMaxSunPlants; // 5670
    int mStartDrawTime; // 5671
    int mIntervalDrawTime; // 5672
    int mIntervalDrawCountStart; // 5673
    float mMinFPS; // 5674
    int mPreloadTime; // 5675
    int mGameID; // 5676
    int mGravesCleared; // 5677
    int mPlantsEaten; // 5678
    int mPlantsShoveled; // 5679
    int mCoinsCollected; // 5680
    int mDiamondsCollected; // 5681
    int mPottedPlantsCollected; // 5682
    int mChocolateCollected; // 5683
    bool mPeaShooterUsed; // 22736
    bool mCatapultPlantsUsed; // 22737
    int mCollectedCoinStreak; // 5685
    int mUnkIntSecondPlayer1; // 5686
    bool mUnkBoolSecondPlayer; // 22748
    int mUnkIntSecondPlayer2; // 5688
    int* mStringSecondPlayer; // 5689
    int unknownMembers[8]; // 5690 ~ 5697
};

class BaseGamepadControls {
public:
    int *mVtable; // 0
    GameObject mGameObject; // 1 ~ 13
    Board * mBoard; // 14
    SeedBank* mSeedBank; // 15
    float mUnkFirstHighlightRelated; // 16
    int mShovelRelated1; // 17
    float mGamepadAccLeftX;
    float mGamepadAccLeftY;
    float mGridCenterPositionX; // 20
    float mGridCenterPositionY; // 21
    float mRightPositionX; // 22
    float mRightPositionY; // 23
    int mGamepadState; // 24
    int unk1; // 25
    float mDigIndicatorPercentage; // 26 , 每按下一次铲除键就加2.3
    float mCursorPositionX; // 27
    float mCursorPositionY; // 28
    float mGamepadVelocityLeftX; // 29
    float mGamepadVelocityLeftY; // 30
    float mGamepadVelocityRightX; // 31
    float mGamepadVelocityRightY; // 32
    int unk2[4]; // 33 ~ 36
    int mPlayerIndex1; // 37
    int mPlayerIndex2; // 38
    float mCursorPositionYJitter; // 39
    float mUpdateAdd0Dot016; // 40
    int unkMems[2]; // 41 ~ 42
}; // 大小43个整数

class GamepadControls : public BaseGamepadControls {
public:
    float mRangeFrom0to30UpdateFresh; // 43
    int * mSelectorParticle; // 44
    int mSelectedSeedIndex; // 45
    SeedType::SeedType mSelectedSeedType; // 46
    bool mIsZombie; // 188
    bool mCanPickUp; // 189
    int mSelectedUpgradableType; // 48
    int mCobCannonPlantIndexInList; // 49
    bool mIsCobCannonSelected ; // 200
    float mUpdateAdd_a2_Or_Minus_2xa2; // 51
    Reanimation *mPreviewReanim1; // 52
    Reanimation *mCobCannonReanim; // 53
    int mPreviewReanimID3; // 54
    int mUnkCobCannonRelated; // 55
    int mPreviewReanimID4; // 56
    SeedType::SeedType mPreviewingSeedType; // 57
    Sexy::Image * mPreviewImage; // 58
    Zombie* mButterZombie; // 59
    int mShovelRelated2; // 60
    bool mIsShowingDigIndicator; // 244
    bool mIsInShopSeedBank; // 245
    int mSelectedShopSeedIndex; // 62
    int unk4[3]; // 63 ~ 65
}; // 大小66个整数

class ZenGardenControls : public GamepadControls {
public:
    GameObjectType::GameObjectType mObjectType; // 66
}; // 大小67个整数



struct GameStats {

    enum MiscStat {
        ZOMBIES_KILLED = 0,
        PLANTS_KILLED = 1,
        MONEY = 2,
        TREE_HEIGHT = 4,
        ENDLESS_FLAGS = 5,
        MOWED_ZOMBIES = 6,
        STINKY_CHOCOLATES = 7
    };

    HouseType::HouseType mHouseType; // 0
    int unk; // 1
    int mMiscStats[9]; // 2 ~ 10
    char mFavoritePlants[49]; // 44 ~ 92
    char mFavoriteZombies[47]; // 93 ~ 139
    float mSurvivalCompletion; // 35
    float mMiniGameCompletion; // 36
    float mPuzzleCompletion; // 37
}; // 大小38个整数

struct PottedPlant {
    unsigned char unk[20];
};

class PlayerInfo {
public:
    int * vTable; // 0
    int unk1; // 1
    int *mProFileMgr; // 2
    int unk2; // 3
    char* mName; // 4
    int mUseSeq; // 5
    int mId; // 6
    int mProfileId; // 7
    int mFlags; // 8
    int mLevel; // 9
    int mCoins; // 10
    int mChallengeRecords[100]; // 11 ~ 110 ， 但末尾6个完全不会用到，可以成为我的自己存数据的空间。
    int mPurchases[36]; // 111 ~ 146 ，本应该是mPurchases[80]，111 ~ 190，但仅用到了前36个。
    bool mAchievements[12]; // 147 ~ 149, 从mPurchases[80]分出来的
    bool mUnused[147]; // 150 ~
    unsigned char mZombatarHat;
    unsigned char mZombatarHatColor;
    unsigned char mZombatarHair;
    unsigned char mZombatarHairColor;
    unsigned char mZombatarFacialHair;
    unsigned char mZombatarFacialHairColor;
    unsigned char mZombatarAccessory;
    unsigned char mZombatarAccessoryColor;
    unsigned char mZombatarEyeWear;
    unsigned char mZombatarEyeWearColor;
    unsigned char mZombatarTidBit;
    unsigned char mZombatarTidBitColor;
    bool mIs3DAcceleratedClosed; // ~ 189, 从mPurchases[80]分出来的
    int mUsedCoins; // 190, 从mPurchases[80]分出来的
    int unkMem4[2]; // 191 ~ 192
    int mLastStinkyChocolateTime; // 193
    int	mStinkyPosX; // 194
    int	mStinkyPosY; // 195
    int mNumPottedPlants; // 196
    int unk4; // 197
    PottedPlant mPottedPlants[50]; // 198 ~ 447
    double mMusicVolume; // 448 ~ 449
    double mSoundVolume;  // 450 ~ 451
    int unkMems6[5]; // 452 ~ 456
    bool mHelpTextSeen[6]; // 1828 ~ 1833
    int unk5; // 459
    bool unkBool1; // 1840
    bool unkBool2; // 1841
    bool mPassedShopSeedTutorial; // 1842
    bool mMailMessageRead[32]; // 1843 ~ 1874 ，紧密存放，可以存放32x8个bool
    bool mMailMessageSeen[32]; // 1875 ~ 1906 ，紧密存放，可以存放32x8个bool
    GameStats mGameStats; // 477 ~ 514
    int unk6; // 515
}; // 大小516个整数

struct CausticEffect {
   bool mTextureAlpha[256][256];
};


struct SexyVertex2D {
    float x;
    float y;
    int unk1;
    int unk2;
    unsigned int color;
    int unk3;
    float u;
    float v;
};

struct TriVertex {
    float x;
    float y;
    float u;
    float v;
    unsigned int color;
};


class PoolEffect {
public:
    CausticEffect *mCausticGrayscaleImage; // 0
    Sexy::Image* mCausticImage; // 1
    LawnApp* mApp; // 2
    int mPoolCounter; // 3
}; // 大小4个整数

class Music {  // 加载XBOX版xm格式音乐时用。优：音质好、有鼓点。缺：鼓点BUG多，xm格式难以修改
public:
    int* vTable; // 0
    int unkMems[3]; // 1 ~ 3
    LawnApp *mApp; // 4
    int *mMusicInterface; // 5
    MusicTune::MusicTune mCurMusicTune; // 6
    MusicTune::MusicTune mLastMusicTune; // 7
    MusicFile::MusicFile mCurMusicFileMain; // 8
    MusicFile::MusicFile mCurMusicFileDrums; // 9
    MusicFile::MusicFile mCurMusicFileHihats; // 10
    int mBurstOverride; // 11
    int mBaseBPM; // 12
    int mBaseModSpeed; // 13
    MusicBurstState::MusicBurstState mMusicBurstState; // 14
    int mBurstStateCounter; // 15
    MusicDrumsState::MusicDrumsState mMusicDrumsState; // 16
    int mQueuedDrumTrackPackedOrder; // 17
    int mDrumsStateCounter; // 18
    int mPauseOffset; // 19
    int mPauseOffsetDrums; // 20
    bool mPaused; // 84
    bool mMusicDisabled; // 85
    int mFadeOutCounter; // 22
    int mFadeOutDuration; // 23
    float mVolume1; // 24
    float mVolume2; // 25
}; // 大小26个整数

class Music2 : public Music { // 加载TV版ogg格式音乐时用。无鼓点。

}; // 大小26个整数

class ProfileMgr {
public:
    int* vTable; // 0
    int* mProfileEventListener; // 1
};

class DefaultProfileMgr : public ProfileMgr{
public:
    int * mProfileMap; // 2
    int *mProfileMapEnd; // 3

    int mNumProfiles; // 7

    int mNextProfileUseSeq; // 9
};

class BaseRes {
public:
    int *vTable; // 0
    ResType::ResType mType; // 1
    int *mResourceRef; // 2
    int unk[8]; // 3 ~ 10
    char *mPath; // 11
    int unk2[13]; // 12 ~ 24
}; // 大小25个整数

class SoundRes : public BaseRes {
public:
    int mSoundId; // 25
    double mVolume; // 26 ~ 27
    int mPanning; // 28
    int unk3; // 29
}; // 大小30个整数

class MessageWidget {
public:
    int *vTable; // 0
    int unk[3]; // 1 ~ 3
    LawnApp *mApp; // 4
    char mLabel[128]; // 5 ~ 36
    int mDisplayTime; // 37
    int mDuration; // 38
    MessageStyle::MessageStyle mMessageStyle; // 39
    Reanimation *mTextReanimID[128]; // 40 ~ 167
    ReanimationType::ReanimationType mReanimType; // 168
    int mSlideOffTime; // 169
    float unkFloatWithInitValue1; // 170
    char mLabelNext[128]; // 171 ~ 202
    MessageStyle::MessageStyle mMessageStyleNext; // 203
}; // 大小204个整数

class CustomMessageWidget : public MessageWidget {
public:
    Sexy::Image *mIcon; // 204
}; // 大小205个整数

struct Curve1DUtil {
    int unk[16];
};

class ChallengeScreen : public Sexy::Widget {
public:
    Sexy::ButtonListener mButtonListener; // 64
    Sexy::ButtonWidget* mButtons[94]; // 65 ~ 158
    LawnApp* mApp; // 159
    int* mToolTipWidget; // 160
    ChallengePage::ChallengePage mPage; // 161
    bool mCheatEnableChallenges; // 648
    UnlockingState::UnlockingState mUnlockState; // 163
    int mUnlockStateCounter; // 164
    int mUnlockChallengeIndex; // 165
    float mLockShakeX ; // 166
    float mLockShakeY ; // 167
    Curve1DUtil mUtil; // 168 ~ 183
    int* mHelpBarWidget; // 184
    int mScreenTopChallengeIndex; // 185
    int mSelectedChallengeIndex; //186
    float mUnkFloat; // 187
    GameMode::GameMode mUnk1[94]; // 188 ~ 281
    int mUnk2[94]; // 282 ~ 375
    int mTotalGameInPage; // 376
    int mSelectedChallenge; // 377 其值固定比mSelectedMode小2
    GameMode::GameMode mSelectedMode; // 378
    int unk4; // 379
};  // 大小380个整数


class AchievementsWidget : public Sexy::Widget {
public:
    Sexy::ButtonListener mButtonListener; // 64
    LawnApp *mApp; // 65
}; // 我想用AchievementsWidget取代MaskHelpWidget。MaskHelpWidget的大小是66个整数，所以AchievementsWidget也保持66个整数。

struct LeaderboardReanimations {
    Reanimation* backgroundReanim[5];
    Reanimation* achievementReanim[12];
};

class TrashBin : public Sexy::Widget {
public:

    enum TrashPileType {
        PLANT_PILE = 0,
        ZOMBIE_PILE = 1
    };

    TrashPileType mTrashPileType; // 64
    float mTrashHeight; // 65
    Sexy::Image* mPileImage[10]; // 66 ~ 75
    bool mMirrorPile[10]; // 76 ~ 78
    int mRandomPileWeight[6]; // 79 ~ 84
    int mPileNum; // 85

}; // 大小86个整数

class LeaderboardsWidget : public Sexy::Widget {
public:
    LawnApp *mApp; // 64
    TrashBin* mZombieTrashBin; // 65
    TrashBin* mPlantTrashBin; // 66
    bool mAchievements[12]; // 67 ~ 69
    LeaderboardReanimations* mLeaderboardReanimations; // 70
    int mLongestRecordPool; // 71
    Sexy::GameButton* mBackButton;
    Sexy::ButtonListener* mButtonListener;
    int mFocusedAchievementIndex;
    bool mHighLightAchievement;
};// 我想用LeaderboardsWidget取代DaveHelp。

class ZombatarWidget : public Sexy::MenuWidget {
public:
    enum TabType {
        SKIN = 0,
        HAIR = 1,
        FHAIR = 2,
        TIDBIT = 3,
        EYEWEAR = 4,
        CLOTHES = 5,
        ACCESSORY = 6,
        HAT = 7,
        BACKGROUND = 8,
        MaxTabNum = 9
    };

    enum AccessoryNum {
        HairNum = 16,
        FHairNum = 24,
        TidBitNum = 14,
        EyeWearNum = 16,
        ClothNum = 12,
        AccessoryNum = 15,
        HatNum = 14,
        BackgroundNum = 83,
    };

    Sexy::ButtonListener* mButtonListener;
    LawnApp* mApp;
    Zombie *mPreviewZombie;
    Sexy::GameButton* mBackButton;
    Sexy::GameButton* mFinishButton;
    Sexy::GameButton* mViewPortraitButton;
    Sexy::GameButton* mNewButton;
    Sexy::GameButton* mDeleteButton;
    Reanimation* mZombatarReanim;
    bool mShowExistingZombatarPortrait;
    bool mShowZombieTypeSelection;
    unsigned char mSelectedTab;
    unsigned char mSelectedSkinColor;
    unsigned char mSelectedHair;
    unsigned char mSelectedHairColor;
    unsigned char mSelectedFHair;
    unsigned char mSelectedFHairColor;
    unsigned char mSelectedFHairPage; // 0 or 1
    unsigned char mSelectedTidBit;
    unsigned char mSelectedTidBitColor;
    unsigned char mSelectedEyeWear;
    unsigned char mSelectedEyeWearColor;
    unsigned char mSelectedCloth;
    unsigned char mSelectedAccessory;
    unsigned char mSelectedAccessoryColor;
    unsigned char mSelectedHat;
    unsigned char mSelectedHatColor;
    unsigned char mSelectedBackground;
    unsigned char mSelectedBackgroundColor;
    unsigned char mSelectedBackgroundPage;

};// 我想用ZombatarWidget取代TestMenuWidget。


class MainMenu : public Sexy::MenuWidget {
public:
    int mMainMenuReanimID; // 70
    float mCameraPositionX; // 71
    float mCameraPositionY; // 72
    LawnApp *mApp; // 73
    int unkMem1; // 74
    int mScene; // 75
    int mSceneNext; // 76
    char *MPlayingTrackName; // 77
    int mTransitionCounter; // 78
    int mSkyReanimID; // 79
    int mSky2ReanimID; // 80
    int mUnkReanimID; // 81
    int mZombieHandReanimID; // 82
    int mCrowReanimID; // 83
    int mFallingLeavesReanimID; // 84
    int mButterflyReanimID; // 85
    int mUnkReanimID2; // 86
    MainMenuButtonId mPressedButtonId; // 87
    char * mExitTrackName; // 88
    int mEnterReanimationCounter; // 89
    int mExitCounter; // 90
    bool unk1; // 364
    bool mFirstTimeAdventure; // 365
    bool mMiniGameLocked; // 366
    bool mCoopModeLocked; // 367
    bool mPuzzleModeLocked; // 368
    bool mSurvivalModeLocked; // 369
    bool mVSModeLocked; // 370
    bool unkBool3; // 371
    bool unkBool4; // 372
    bool unkBool5; // 373
    int unkMems3[5]; // 94 ~ 98
    bool mRetainWidgetsOnExit; // 396
    float mXUnkFloat1; // 100
    float mYUnkFloat2; // 101
    float mFadeCounterFloat; // 102
    bool unkMems4[16]; // 103 ~ 106
    Sexy::Image* m2DMarkImage; // 107
}; // 大小108个整数

class Challenge {
public:
    int *vTable; // 0
    int unk1[3]; // 1 ~ 3
    LawnApp *mApp; // 4
    Board *mBoard; // 5
    int *mHelpBarWidget; // 6
    bool mBeghouledMouseCapture; // 28
    int mBeghouledMouseDownX; // 8
    int mBeghouledMouseDownY; // 9
    bool mBeghouledEated[9][6]; // 40 ~  93
    bool mBeghouledPurcasedUpgrade[3]; // 94 ~ 96
    int mBeghouledMatchesThisMove; // 25
    ChallengeState::ChallengeState mChallengeState; // 26
    int mChallengeStateCounter; // 27
    int mConveyorBeltCounter; // 28
    int unk2; // 29
    int mChallengeScore; // 30
    bool mShowBowlingLine; // 124
    SeedType::SeedType mLastConveyorSeedType; // 32
    int mSurvivalStage; // 33
    int mSlotMachineRollCount; // 34
    Reanimation *mReanimChallenge; // 35
    Reanimation *mReanimCloud[6]; // 36 ~ 41
    int mCloudCounter[6]; // 42 ~ 47
    int mChallengeGridX; // 48
    int mChallengeGridY; // 49
    int mScaryPotterPots; // 50
    int mRainCounter; // 51
    int mTreeOfWisdomTalkIndex; // 52
    int unk3[14]; // 53 ~ 66
    float mHeavyWeaponX;  // 67
    float mHeavyWeaponY; // 68
    float mHeavyWeaponAngle; // 69
    int unkHeavyWeaponWithInitValue1000; // 70
    int mHeavyWeaponCatTailAttackCounter; // 71
    int mHeavyWeaponCatTailLevel; // 72
    int mHeavyWeaponPeaLevel; // 73
    int mHeavyWeaponSnowPeaCounter; // 74
    int mHeavyWeaponTorchWoodCounter; // 75
    int unkHeavyWeaponWithInitValue10; // 76
    Reanimation *mReanimHeavyWeapon1; // 77
    Reanimation *mReanimHeavyWeapon2; // 78
    Reanimation *mReanimHeavyWeapon3; // 79
}; // 大小80个整数

struct ReanimatorTrack {
    int unk;
    char *name;
    ReanimatorTransform *mTransforms;
    int mTransformCount;
    bool IsAttacher;
};

struct ReanimatorFrameTime {
    float mFraction; // 0
    int mAnimFrameBeforeInt; // 1
    int mAnimFrameAfterInt; // 2
};

class ReanimatorTransform {
public:
    float mTransX; // 0
    float mTransY; // 1
    float mSkewX; // 2
    float mSkewY; // 3
    float mScaleX; // 4
    float mScaleY; // 5
    float mFrame; // 6
    float mAlpha; // 7
    Sexy::Image *mImage; // 8
    Sexy::Image *mImage2; // 9
    int *mFont; // 10
    char* mName; // 11
};// 大小12个整数

class Attachment;

class ReanimatorTrackInstance {
public:
    int mBlendCounter; // 0
    int mBlendTime; // 1
    ReanimatorTransform mBlendTransform; // 2 ~ 13
    float mShakeOverride; // 14
    float mShakeX; // 15
    float mShakeY; // 16
    unsigned short mAttachmentID; // 17
    Sexy::Image *mImageOverride; // 18
    ReanimatorRenderGroup::ReanimatorRenderGroup mRenderGroup; // 19
    Color mTrackColor; // 20 ~ 23
    bool mIgnoreClipRect; // 96
    bool mTruncateDisappearingFrames; // 97
    bool mIgnoreColorOverride; // 98
    bool mIgnoreExtraAdditiveColor; // 99
}; // 大小25个整数

class ReanimatorDefinition {
public:
    ReanimatorTrack* mTracks; // 0
    int mTrackCount; // 1
    float mFPS; // 2
    int *mReanimAtlas; // 3
}; // 大小4个整数

class ReanimationParams {
public:
    ReanimationType::ReanimationType mReanimationType;
    char* mReanimFileName;
    int mReanimParamFlags;
};

class TodParticleSystem {
public:
    int *vTable; // 0
    int unk1[3]; // 1 ~ 3
    ParticleEffect::ParticleEffect mEffectType; // 4
    int *mParticleDef; // 5
    int* mParticleHolder; // 6
    int mEmitterList[4]; // 7 ~ 10
    bool mDead; // 44
    bool mIsAttachment; // 45
    int mRenderOrder; // 12
    bool mDontUpdate; // 52
    bool mActive; // 53
    int mParticleId; // 14
};// 大小15个整数


struct AttachEffect {
    enum EffectType {
        Particle,
        Trail,
        Reanim,
        Attachment,
        Other
    };
    int mEffectID; // 0
    EffectType mEffectType; // 1
    SexyTransform2D mOffset; // 2 ~ 10
    bool mDontDrawIfParentHidden; // 44
    bool mDontPropogateColor; // 45
}; // 大小12个整数

class Attachment {
public:
    int unk[4]; // 0 ~ 3
    AttachEffect mEffectArray[16]; // 4 ~ 195
    int mNumEffects; // 196
    bool mDead; //
    bool mActive;
    bool mUsesClipping;
    int mAttachmentID;
}; // 大小199个整数

struct ReanimCacheImageVariation {
    SeedType::SeedType mSeedType;
    DrawVariation::DrawVariation mDrawVariation;
    Sexy::Image *mImage;
};

struct TodListNode_ReanimCacheImageVariation {
    ReanimCacheImageVariation mValue;
    TodListNode_ReanimCacheImageVariation *mNext;
    TodListNode_ReanimCacheImageVariation *mPrev;
};

struct TodAllocator {
    void *mFreeList;
    void *mBlockList;
    int mGrowCount;
    int mTotalItems;
    int mItemSize;
};

struct TodList_ReanimCacheImageVariation {
    TodListNode_ReanimCacheImageVariation *mHead;
    TodListNode_ReanimCacheImageVariation *mTail;
    int mSize;
    TodAllocator *mpAllocator;
};

class ReanimatorCache {
public:
    TodList_ReanimCacheImageVariation mImageVariationList;
    Sexy::MemoryImage *mPlantImages[SeedType::SeedTypeCount]; // 4 ~ 57
    Sexy::MemoryImage *mLawnMowers[4]; // 58 ~ 61
    Sexy::MemoryImage *mZombieImages[ZombieType::CachedZombieTypesCount]; // 62 ~ 97
    LawnApp *mApp; // 98
};// 大小99个整数



struct PerfTimer {
    int unk[5];
};

class CreditScreen : public Sexy::Widget {
public:
    enum CreditsPhase {
        CREDITS_MAIN1 = 0,
        CREDITS_MAIN2 = 1,
        CREDITS_MAIN3 = 2,
        CREDITS_END = 3,
    };

public:
    Sexy::ButtonListener mButtonListener; // 64
    LawnApp *mApp; // 65
    CreditsPhase mCreditsPhase; // 66
    int mCreditsPhaseCounter; // 67
    int mCreditsReanimID; // 68
    int mFogParticleID; // 69
    int mBlinkCountdown; // 70
    Sexy::Widget *mOverlayWidget; // 71
    bool mDrawBrain; // 288
    float mBrainPosX; // 73
    float mBrainPosY; // 74
    int mUpdateCount; // 75
    int mDrawCount; // 76
    int unkInt1; // 77
    PerfTimer mTimerSinceStart; // 78 ~ 82
    int unkInt2; // 83
    bool mDontSync; // 336
    bool mCreditsPaused; // 337
    int unkInt3[3]; // 85 ~ 87
    bool mPreloaded; // 352
    int unkInt4; // 89
    double mScrollPositionY1; // 90 ~ 91
    double mScrollPositionY2; // 92 ~ 93
    bool mIsFromMainMenu; // 376,即94

};  // 大小95个整数



class LawnDialog : public Sexy::Dialog {
public:
    LawnApp *mApp; // 184
#ifdef VERSION_111
    int mPlayerIndex;
#endif
    int mButtonDelay; // 185
    Sexy::Widget* mReanimationWidget; // 186
    bool mDrawStandardBack; // 748
    Sexy::GameButton* mLawnYesButton; // 188
    Sexy::GameButton* mLawnNoButton; // 189
    bool mTallBottom; // 760
    bool mVerticalCenterText; // 761
    bool unkBool; // 762
#ifdef VERSION_111
    int unk2;
#endif
}; // 115: 191, 111: 193


class AlmanacDialog : public LawnDialog {
public:
    int* mScrollListener; // 191
    LawnApp * mApp; // 192
    Sexy::GameButton* mViewPlantButton; // 193
    Sexy::GameButton* mViewZombieButton; // 194
    Sexy::CustomScrollbarWidget* mScrollTextView; // 195
    int mOpenPage; // 196
    SeedType::SeedType mSelectedSeed; // 197
    ZombieType::ZombieType mSelectedZombie; // 198
    Plant* mPlant; // 199
    Zombie* mZombie; // 200
    int unk[4]; // 201 ~ 204
    TRect mDescriptionRect; // 205 ~ 208
    TRect mCostRect; // 209 ~ 212
    TRect mWaitTimeRect; // 213 ~ 216
    int unk2[2]; // 217 ~ 218
    int *mNameString; // 219
    int *mDescriptionHeaderString; // 220
    int *mDescriptionStringTmp; // 221
    int *mDescriptionString; // 222
    int *mCostString; // 223
    int *mWaitTimeString; // 224
    int unk4; // 225
    DrawStringJustification::DrawStringJustification mJustification; // 226
    bool mSetupFinished; // 227 * 4
    int unk3[14]; // 228 ~ 233
}; // 115: 234, 111: 236

class HelpOptionsDialog : public LawnDialog {
public:
    LawnApp * mApp; // 191
    Sexy::GameButton* mHowToPlayButton; // 192
    Sexy::GameButton* mSwitchUserButton; // 193
    Sexy::GameButton* mSettingsButton; // 194
    Sexy::GameButton* mCreditsButton; // 195
    Sexy::GameButton* mBackButton; // 196
    Sexy::GameButton* mUnkButton; // 197
}; // 115: 198, 111: 200

class ConfirmBackToMainDialog : public LawnDialog {
public:
    Sexy::GameButton* mRestartButton; // 191
}; // 115: 192, 111: 194

class SettingsDialog : public LawnDialog {
public:
    int *mSliderListener; // 191
    int *mCheckboxListener; // 192
    LawnApp * mApp; // 193
    Sexy::Widget* mMusicSlider; // 194
    Sexy::Widget* mSoundSlider; // 195
    Sexy::GameButton* mBackButton; // 196
    Sexy::GameButton* mSelectDeviceButton; // 197
    int unk[5]; // 198 ~ 202
}; // 115: 203, 111: 205

class HouseChooserDialog : public LawnDialog {
public:
    HouseType::HouseType mSelectedHouseType; // 191
    int unk[2]; // 192 ~ 193
};// 115: 194, 111: 196


class MailScreen : public LawnDialog {
public:
    int unk[3]; // 191 ~ 193
    int mPage; // 194
    int unk2[12]; // 195 ~ 206
};// 115: 207, 111: 209

namespace ImageLib {
    class Image {
    public:
        int *vTable; // 0
        int mWidth; // 1
        int mHeight; // 2
        unsigned int *mBits; // 3
        int *mText1; // 4
        int *mText2; // 5
        bool unkBool; // 24
        int unk1[256]; // 7 ~ 262
        int unkInt; // 263
    }; // 264个整数
}

struct ZombieDrawPosition {
    int mHeadX;
    int mHeadY;
    int mArmY;
    float mBodyY;
    float mImageOffsetX;
    float mImageOffsetY;
    float mClipHeight;
};

#endif //PVZ_TV_1_1_5_ENUMS_H
