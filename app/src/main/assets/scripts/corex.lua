print("corex v2");
print("author: Akari & YingFengTingYu");

local corex = {
    _VERSION = "corex v2",
    _DESCRIPTION = "libpvz.so wrapper for Lua",
    _AUTHOR = "Akari & YingFengTingYu"
}

local class = require "middleclass"

corex.using = function()
    for k, v in pairs(corex) do
        if k ~= "using" then
            _G[k] = v
        end
    end
end

------------------------------------------------------------
local luaType = {
    Boolean = {
        name = "Boolean",
        set = setBoolean,
        get = getBoolean,
        size = 1
    },
    Int8 = {
        name = "Int8",
        set = setInt8,
        get = getInt8,
        size = 1
    },
    Int16 = {
        name = "Int16",
        set = setInt16,
        get = getInt16,
        size = 2
    },
    Int32 = {
        name = "Int32",
        set = setInt32,
        get = getInt32,
        size = 4
    },
    Int64 = {
        name = "Int64",
        set = setInt64,
        get = getInt64,
        size = 8
    },
    UInt8 = {
        name = "UInt8",
        set = setUInt8,
        get = getUInt8,
        size = 1
    },
    UInt16 = {
        name = "UInt16",
        set = setUInt16,
        get = getUInt16,
        size = 2
    },
    UInt32 = {
        name = "UInt32",
        set = setUInt32,
        get = getUInt32,
        size = 4
    },
    Float32 = {
        name = "Float32",
        set = setFloat32,
        get = getFloat32,
        size = 4
    },
    Float64 = {
        name = "Float64",
        set = setFloat64,
        get = getFloat64,
        size = 8
    },
    EAString8 = {
        name = "EAString8",
        set = setEAString8,
        get = getEAString8,
        size = 24
    },
    EAString16 = {
        name = "EAString16",
        set = setEAString16,
        get = getEAString16,
        size = 24
    },
    Pointer = {
        name = "Pointer",
        set = setPointer,
        get = getPointer,
        size = 8
    }
}

corex.Type = luaType

local funcType = {
    DirCall = 1,
    VirCall = 2,
};

local libOffset = core.baseAddress

corex.FunctionType = funcType

------------------------------------------------------------

corex.Array = class("Array")

function corex.Array:initialize(thePtr, theSize, theType)
    self.pointer = thePtr
    self.size = theSize
    self.type = theType
    self._mAutoRelease = false
end

function corex.Array:initialize(theSize, theType)
    self.pointer = malloc(theType.size * theSize)
    self.size = size
    self.type = theType
    self._mAutoRelease = true
end

function corex.Array:destroy()
    if self._mAutoRelease then
        free(self.pointer)
    end
end

function corex.Array:__index(index)
    assert(index >= 0 and index < self.size, "Index was outside the bounds of the array.")
    return self.type.get(self.pointer + index * self.type.size)
end

function corex.Array:__newindex(index, value)
    assert(index >= 0 and index < self.size, "Index was outside the bounds of the array.")
    self.type.set(self.pointer + index * self.type.size, value)
end

function corex.Array:__ipairs()
    local function iterator(self, index)
        index = index + 1
        if index <= self.size then
            local value = self[index]
            return index, value
        else
            return nil
        end
    end
    return iterator, self, -1
end

function corex.Array:__tostring()
    local sb = {}
    table.insert(sb, "Array{")
    for i, v in self do
        table.insert(sb, v)
        table.insert(sb, ", ")
    end
    if #sb > 1 then
        table.remove(sb)
    end
    table.insert(sb, "}")
    return table.concat(sb)
end

------------------------------------------------------------

local onUpdateGameTable = {}

local onUpdateGameFunction = function(board)
    local i = 1
    while i <= #onUpdateGameTable do
        if not onUpdateGameTable[i](board) then
            table.remove(onUpdateGameTable, i)
        else
            i = i + 1
        end
    end
end

corex.onUpdateGame = onUpdateGameTable

table.insert(core.onUpdateGame, onUpdateGameFunction)

------------------------------------------------------------
local functionCaches = {}

corex.bind = function(description)
    local base = class("corex.bind.base")

    function base:initialize(ptr)
        rawset(self, "ptr", ptr)
        if description.extends then
            rawset(self, "extendedObj", description.extends(rawget(self, "ptr")))
        end
    end

    function base:__index(name)
        if description.properties then
            local propertyDescription = description.properties[name]
            if propertyDescription then
                print(description.name, "properties", name, propertyDescription.offset)
                return propertyDescription.type.get(rawget(self, "ptr") + propertyDescription.offset)
            end
        end
        if description.functions then
            local functionDescription = description.functions[name]
            if functionDescription then
                print(description.name, "functions", name)
                local func = functionCaches[functionDescription]
                if not func then
                    print(name)
                    if functionDescription.type == funcType.DirCall then
                        local funcOffset = functionDescription.offset + libOffset
                        local sign = functionDescription.sign
                        func = function(self, ...)
                            return invoke(funcOffset, sign, rawget(self, "ptr"), ...)
                        end
                    elseif functionDescription.type == funcType.VirCall then
                        local funcOffset = functionDescription.offset
                        local sign = functionDescription.sign
                        func = function(self, ...)
                            local aPtr = rawget(self, "ptr")
                            return invoke(getPointer(funcOffset + aPtr), sign, aPtr, ...)
                        end
                    end
                    functionCaches[functionDescription] = func
                end
                return func
            end
        end
        local super = rawget(self, "extendedObj")
        if super then
            print("extendedObj")
            return super[name]
        end
        return nil
    end

    function base:__newindex(name, value)
        print(name, "__newindex")
        if description.properties then
            local prop = description.properties[name]
            if prop then
                prop.type.set(rawget(self, "ptr") + description.offset, value)
                return
            end
        end
        local super = rawget(self, "extendedObj")
        if super then
            super[name] = value
            return
        end
    end

    local c = function(t) if type(t) ~= 'number' then return rawget(t, "ptr") else return t end end
	base.__add = function(t, o) return c(t) + c(o) end
	base.__sub = function(t, o) return c(t) - c(o) end
	base.__mul = function(t, o) return c(t) * c(o) end
	base.__div = function(t, o) return c(t) / c(o) end
	base.__mod = function(t, o) return c(t) % c(o) end
	base.__pow = function(t, o) return c(t) ^ c(o) end
	base.__unm = function(t) return -rawget(t, "ptr") end
	base.__idiv = function(t, o) return c(t) // c(o) end
	base.__band = function(t, o) return c(t) & c(o) end
	base.__bor = function(t, o) return c(t) | c(o) end
	base.__bxor = function(t, o) return c(t) ~ c(o) end
	base.__bnot = function(t) return ~rawget(t, "ptr") end
	base.__shl = function(t, o) return c(t) << c(o) end
	base.__shr = function(t, o) return c(t) >> c(o) end
	base.__eq = function(t, o) return c(t) == c(o) end
	base.__lt = function(t, o) return c(t) < c(o) end
	base.__le = function(t, o) return c(t) <= c(o) end
	-- length of struct
	base.__len = function(t) return description.size end
	-- display name
	base.__tostring = function(t) return string.format('<%s PVZObject to 0x%08x>', description.name, rawget(t, "ptr")) end
	base.__name = function(t) return description.name end

    return function(ptr)
        return base:new(ptr)
    end
end

------------------------------------------------------------

corex.gLawnApp = function()
    return getPointer(core.baseAddress + 0x1C18F10)
end

corex.PlayerInfo = corex.bind({
    name = "PlayerInfo",
    size = 16080,
    properties = {
        mCoins                  = { offset =     8, type = luaType.Int32        },
        mName                   = { offset =    24, type = luaType.EAString8    },
        mLevel2                 = { offset =    60, type = luaType.Int32        },
        mLevel                  = { offset =    64, type = luaType.Int32        },
        mFinishedAdventure      = { offset =   544, type = luaType.Boolean      },
        mZombiesKilled          = { offset = 16016, type = luaType.Int32        },
        mMalletTutorialStatus   = { offset = 16036, type = luaType.Int32        },
    },
})

corex.GameObject = corex.bind({
    name = "GameObject",
    size = 56,
    properties = {
        mApp = { offset = 0, type = luaType.Pointer },
        mBoard = { offset = 8, type = luaType.Pointer },
        mX = { offset = 16, type = luaType.Int32 },
        mY = { offset = 20, type = luaType.Int32 },
        mWidth = { offset = 24, type = luaType.Int32 },
        mHeight = { offset = 28, type = luaType.Int32 },
        mVisible = { offset = 32, type = luaType.Boolean },
        mRow = { offset = 36, type = luaType.Int32 },
        mRenderOrder = { offset = 40, type = luaType.Int32 },
        mPrevTransX = { offset = 44, type = luaType.Float32 },
        mPrevTransY = { offset = 48, type = luaType.Float32 },
        mPosScaled = { offset = 52, type = luaType.Boolean },
    },
})

corex.Plant = corex.bind({
    name = "Plant",
    size = 512,
    extends = corex.GameObject,
    properties = {
        mSeedType = { offset = 56, type = luaType.Int32 },
        mPlantCol = { offset = 60, type = luaType.Int32 },
        mAnimCounter = { offset = 64, type = luaType.Int32 },
        mFrame = { offset = 68, type = luaType.Int32 },
        mFrameLength = { offset = 72, type = luaType.Int32 },
        mNumFrames = { offset = 76, type = luaType.Int32 },
        mState = { offset = 80, type = luaType.Int32 },
        mPlantHealth = { offset = 84, type = luaType.Int32 },
        mPlantMaxHealth = { offset = 88, type = luaType.Int32 },
        mSubClass = { offset = 92, type = luaType.Int32 },
        mDisappearCountdown = { offset = 96, type = luaType.Int32 },
        mDoSpecialCountdown = { offset = 100, type = luaType.Int32 },
        mStateCountdown = { offset = 104, type = luaType.Int32 },
        mLaunchCounter = { offset = 108, type = luaType.Int32 },
        mLaunchRate = { offset = 112, type = luaType.Int32 },
        -- Sexy::Rect mPlantRect;
	    -- Sexy::Rect mPlantAttackRect;
        mTargetX = { offset = 148, type = luaType.Int32 },
        mTargetY = { offset = 152, type = luaType.Int32 },
        mStartRow = { offset = 156, type = luaType.Int32 },
        mParticleID = { offset = 160, type = luaType.Int32 },
        mShootingCounter = { offset = 164, type = luaType.Int32 },
        mBodyReanimID = { offset = 168, type = luaType.Int32 },
        mHeadReanimID = { offset = 172, type = luaType.Int32 },
        mHeadReanimID2 = { offset = 176, type = luaType.Int32 },
        mHeadReanimID3 = { offset = 180, type = luaType.Int32 },
        mBlinkReanimID = { offset = 184, type = luaType.Int32 },
        mLightReanimID = { offset = 188, type = luaType.Int32 },
        mSleepingReanimID = { offset = 192, type = luaType.Int32 },
        mBlinkCountdown = { offset = 196, type = luaType.Int32 },
        mRecentlyEatenCountdown = { offset = 200, type = luaType.Int32 },
        mEatenFlashCountdown = { offset = 204, type = luaType.Int32 },
        mBeghouledFlashCountdown = { offset = 208, type = luaType.Int32 },
        mShakeOffsetX = { offset = 212, type = luaType.Float32 },
        mShakeOffsetY = { offset = 216, type = luaType.Float32 },
        -- MagnetItem mMagnetItems[MAX_MAGNET_ITEMS];
        mTargetZombieID = { offset = 320, type = luaType.Float32 },
        mWakeUpCounter = { offset = 324, type = luaType.Float32 },
        mOnBungeeState = { offset = 328, type = luaType.Float32 },
        mImitaterType = { offset = 332, type = luaType.Float32 },
        mPottedPlantIndex = { offset = 336, type = luaType.Float32 },
        mAnimPing = { offset = 340, type = luaType.Boolean },
        mDead = { offset = 341, type = luaType.Boolean },
        mSquished = { offset = 342, type = luaType.Boolean },
        mIsAsleep = { offset = 343, type = luaType.Boolean },
        mIsOnBoard = { offset = 344, type = luaType.Boolean },
        mHighlighted = { offset = 345, type = luaType.Boolean },
        mIsChinese = { offset = 346, type = luaType.Boolean },
        mIsCursed = { offset = 347, type = luaType.Boolean },
        mUnknown348 = { offset = 348, type = luaType.Int32 },
        -- int mPlaceHolder[40]; --Expanded
    },
    functions = {
        CobCannonFire = { offset = 0x70C4A8, type = funcType.DirCall, sign = "v*ii" },
        IsUpgradableTo = { offset = 0x707E48, type = funcType.DirCall, sign = "z*i" },
        Die = { offset = 0x6FEBB8, type = funcType.DirCall, sign = "v*" },
        SetSleeping = { offset = 0x6FDD74, type = funcType.DirCall, sign = "v*z" },
    },
})

corex.Zombie = corex.bind({
    name = "Zombie",
    size = 512,
    extends = corex.GameObject,
    properties = {
        mZombieType = { offset = 56, type = luaType.Int32 },
        mZombiePhase = { offset = 60, type = luaType.Int32 },
        mPosX = { offset = 64, type = luaType.Float32 },
        mPosY = { offset = 68, type = luaType.Float32 },
        mVelX = { offset = 72, type = luaType.Float32 },
        mAnimCounter = { offset = 76, type = luaType.Int32 },
        mGroanCounter = { offset = 80, type = luaType.Int32 },
        mAnimTicksPerFrame = { offset = 84, type = luaType.Int32 },
        mAnimFrames = { offset = 88, type = luaType.Int32 },
        mFrame = { offset = 92, type = luaType.Int32 },
        mPrevFrame = { offset = 96, type = luaType.Int32 },
        mVariant = { offset = 100, type = luaType.Boolean },
        mIsEating = { offset = 101, type = luaType.Boolean },
        mIsChinese = { offset = 102, type = luaType.Boolean },
        mJustGotShotCounter = { offset = 104, type = luaType.Int32 },
        mShieldJustGotShotCounter = { offset = 108, type = luaType.Int32 },
        mShieldRecoilCounter = { offset = 112, type = luaType.Int32 },
        mZombieAge = { offset = 116, type = luaType.Int32 },
        mZombieHeight = { offset = 120, type = luaType.Int32 },
        mPhaseCounter = { offset = 124, type = luaType.Int32 },
        mFromWave = { offset = 128, type = luaType.Int32 },
        mDroppedLoot = { offset = 132, type = luaType.Boolean },
        mIsModifiedLittle = { offset = 133, type = luaType.Boolean },
        mIsModifiedBig = { offset = 134, type = luaType.Boolean },
        mZombieFade = { offset = 136, type = luaType.Int32 },
        mFlatTires = { offset = 140, type = luaType.Boolean },
        mUseLadderCol = { offset = 144, type = luaType.Int32 },
        mTargetCol = { offset = 148, type = luaType.Int32 },
        mAltitude = { offset = 152, type = luaType.Float32 },
        mHitUmbrella = { offset = 156, type = luaType.Boolean },
        -- Sexy::Rect mZombieRect;
        -- Sexy::Rect mZombieAttackRect;
        mChilledCounter = { offset = 192, type = luaType.Int32 },
        mButteredCounter = { offset = 196, type = luaType.Int32 },
        mIceTrapCounter = { offset = 200, type = luaType.Int32 },
        mMindControlled = { offset = 204, type = luaType.Boolean },
        mBlowingAway = { offset = 205, type = luaType.Boolean },
        mHasHead = { offset = 206, type = luaType.Boolean },
        mHasArm = { offset = 207, type = luaType.Boolean },
        mHasObject = { offset = 208, type = luaType.Boolean },
        mInPool = { offset = 209, type = luaType.Boolean },
        mOnHighGround = { offset = 210, type = luaType.Boolean },
        mYuckyFace = { offset = 211, type = luaType.Boolean },
        mYuckyFaceCounter = { offset = 212, type = luaType.Int32 },
        mHelmType = { offset = 216, type = luaType.Int32 },
        mBodyHealth = { offset = 220, type = luaType.Int32 },
        mBodyMaxHealth = { offset = 224, type = luaType.Int32 },
        mHelmHealth = { offset = 228, type = luaType.Int32 },
        mHelmMaxHealth = { offset = 232, type = luaType.Int32 },
        mShieldType = { offset = 236, type = luaType.Int32 },
        mShieldHealth = { offset = 240, type = luaType.Int32 },
        mShieldMaxHealth = { offset = 244, type = luaType.Int32 },
        mFlyingHealth = { offset = 248, type = luaType.Int32 },
        mFlyingMaxHealth = { offset = 252, type = luaType.Int32 },
        mDead = { offset = 256, type = luaType.Boolean },
        mRelatedZombieID = { offset = 260, type = luaType.Int32 },
        -- ZombieID mFollowerZombieID[MAX_ZOMBIE_FOLLOWERS];
        mPlayingSong = { offset = 280, type = luaType.Boolean },
        mParticleOffsetX = { offset = 284, type = luaType.Int32 },
        mParticleOffsetY = { offset = 288, type = luaType.Int32 },
        mAttachmentID = { offset = 292, type = luaType.Int32 },
        mSummonCounter = { offset = 296, type = luaType.Int32 },
        mBodyReanimID = { offset = 300, type = luaType.Int32 },
        mScaleZombie = { offset = 304, type = luaType.Float32 },
        mVelZ = { offset = 308, type = luaType.Float32 },
        mOriginalAnimRate = { offset = 312, type = luaType.Float32 },
        mTargetPlantID = { offset = 316, type = luaType.Int32 },
        mBossMode = { offset = 320, type = luaType.Int32 },
        mTargetRow = { offset = 324, type = luaType.Int32 },
        mBossBungeeCounter = { offset = 328, type = luaType.Int32 },
        mBossStompCounter = { offset = 332, type = luaType.Int32 },
        mBossHeadCounter = { offset = 336, type = luaType.Int32 },
        mBossFireBallReanimID = { offset = 340, type = luaType.Int32 },
        mSpecialHeadReanimID = { offset = 344, type = luaType.Int32 },
        mFireballRow = { offset = 348, type = luaType.Int32 },
        mIsFireBall = { offset = 352, type = luaType.Boolean },
        mMoweredReanimID = { offset = 356, type = luaType.Int32 },
        mLastPortalX = { offset = 360, type = luaType.Int32 },
        mHasGroundTrack = { offset = 364, type = luaType.Boolean },
        mSummonedDancers = { offset = 365, type = luaType.Boolean },
        mUnknown368 = { offset = 368, type = luaType.Int32 },
        mUnknown372 = { offset = 372, type = luaType.Int32 },
        -- int mPlaceHolder[34];
    },
})

corex.Coin = corex.bind({
    name = "Coin",
    size = 240,
    extends = corex.GameObject,
    properties = {
        mPosX = { offset = 56, type = luaType.Float32 },
        mPosY = { offset = 60, type = luaType.Float32 },
        mVelX = { offset = 64, type = luaType.Float32 },
        mVelY = { offset = 68, type = luaType.Float32 },
        mScale = { offset = 72, type = luaType.Float32 },
        mDead = { offset = 76, type = luaType.Boolean },
        mButtonHighlighted = { offset = 77, type = luaType.Boolean },
        mFadeCount = { offset = 80, type = luaType.Int32 },
        mButtonCounter = { offset = 84, type = luaType.Int32 },
        mCollectX = { offset = 88, type = luaType.Float32 },
        mCollectY = { offset = 92, type = luaType.Float32 },
        mGroundY = { offset = 96, type = luaType.Int32 },
        mCoinAge = { offset = 100, type = luaType.Int32 },
        mUnknown104 = { offset = 104, type = luaType.Int32 },
        mIsBeingCollected = { offset = 108, type = luaType.Boolean },
        mDisappearCounter = { offset = 112, type = luaType.Int32 },
        mType = { offset = 116, type = luaType.Int32 },
        mCoinMotion = { offset = 120, type = luaType.Int32 },
        mAttachmentID = { offset = 124, type = luaType.Int32 },
        mCollectionDistance = { offset = 128, type = luaType.Float32 },
        mUsableSeedType = { offset = 132, type = luaType.Int32 },
        -- PottedPlant mPottedPlantSpec;
        mNeedsBouncyArrow = { offset = 204, type = luaType.Boolean },
        mHasBouncyArrow = { offset = 205, type = luaType.Boolean },
        mHitGround = { offset = 206, type = luaType.Boolean },
        mTimesDropped = { offset = 208, type = luaType.Int32 },
        mButton = { offset = 224, type = luaType.Pointer },
        mOrigin = { offset = 232, type = luaType.Pointer },
    },
})

corex.Projectile = corex.bind({
    name = "Projectile",
    size = 240,
    extends = corex.GameObject,
    properties = {
        mFrame = { offset = 56, type = luaType.Int32 },
        mNumFrames = { offset = 60, type = luaType.Int32 },
        mAnimCounter = { offset = 64, type = luaType.Int32 },
        mPosX = { offset = 68, type = luaType.Float32 },
        mPosY = { offset = 72, type = luaType.Float32 },
        mPosZ = { offset = 76, type = luaType.Float32 },
        mVelX = { offset = 80, type = luaType.Float32 },
        mVelY = { offset = 84, type = luaType.Float32 },
        mVelZ = { offset = 88, type = luaType.Float32 },
        mAccZ = { offset = 92, type = luaType.Float32 },
        mShadowY = { offset = 96, type = luaType.Float32 },
        mDead = { offset = 100, type = luaType.Boolean },
        mAnimTicksPerFrame = { offset = 104, type = luaType.Int32 },
        mMotionType = { offset = 108, type = luaType.Int32 },
        mProjectileType = { offset = 112, type = luaType.Int32 },
        mProjectileAge = { offset = 116, type = luaType.Int32 },
        mClickBackoffCounter = { offset = 120, type = luaType.Int32 },
        mRotation = { offset = 124, type = luaType.Float32 },
        mRotationSpeed = { offset = 128, type = luaType.Float32 },
        mOnHighGround = { offset = 132, type = luaType.Boolean },
        mDamageRangeFlags = { offset = 136, type = luaType.Int32 },
        mHitTorchwoodGridX = { offset = 140, type = luaType.Int32 },
        mAttachmentID = { offset = 144, type = luaType.Int32 },
        mCobTargetX = { offset = 148, type = luaType.Float32 },
        mCobTargetRow = { offset = 152, type = luaType.Int32 },
        mTargetZombieID = { offset = 156, type = luaType.Int32 },
        mLastPortalX = { offset = 160, type = luaType.Int32 },
        mUnknown164 = { offset = 164, type = luaType.Int32 },
        -- int mPlaceHolder[18];
    },
})

corex.SeedBank = corex.bind({
    name = "SeedBank",
    size = 1016,
    extends = corex.GameObject,
    properties = {
        mNumPackets = { offset = 56, type = luaType.Int32 },
        -- SeedPacket mSeedPackets[SEEDBANK_MAX];
        mCutSceneDarken = { offset = 1000, type = luaType.Int32 },
        mConveyorBeltCounter = { offset = 1004, type = luaType.Int32 },
        mSlotMachineHeight = { offset = 1008, type = luaType.Int32 },
        mConveyorBeltSpeed = { offset = 1012, type = luaType.Int32 },
    },
})

corex.SeedPacket = corex.bind({
    name = "SeedPacket",
    size = 104,
    extends = corex.GameObject,
    properties = {
        mRefreshCounter = { offset = 56, type = luaType.Int32 },
        mRefreshTime = { offset = 60, type = luaType.Int32 },
        mIndex = { offset = 64, type = luaType.Int32 },
        mOffsetY = { offset = 68, type = luaType.Int32 },
        mPacketType = { offset = 72, type = luaType.Int32 },
        mImitaterType = { offset = 76, type = luaType.Int32 },
        mSlotMachineCountDown = { offset = 80, type = luaType.Int32 },
        mSlotMachiningNextSeed = { offset = 84, type = luaType.Int32 },
        mSlotMachiningPosition = { offset = 88, type = luaType.Float32 },
        mActive = { offset = 92, type = luaType.Boolean },
        mRefreshing = { offset = 93, type = luaType.Boolean },
        mTimesUsed = { offset = 96, type = luaType.Int32 },
        mAdStatus = { offset = 100, type = luaType.Int32 },
    },
    functions = {
        WasPlanted = { offset = 0x7D8C50, type = funcType.DirCall, sign = "v*" },
        Deactivate = { offset = 0x7D8BFC, type = funcType.DirCall, sign = "v*" },
    },
})

corex.LawnMower = corex.bind({
    name = "LawnMower",
    size = 96,
    properties = {
        mApp = { offset = 0, type = luaType.Pointer },
        mBoard = { offset = 8, type = luaType.Pointer },
        mPosX = { offset = 16, type = luaType.Float32 },
        mPosY = { offset = 20, type = luaType.Float32 },
        mRenderOrder = { offset = 24, type = luaType.Int32 },
        mRow = { offset = 28, type = luaType.Int32 },
        mAnimTicksPerFrame = { offset = 32, type = luaType.Int32 },
        mReanimID = { offset = 36, type = luaType.Int32 },
        mChompCounter = { offset = 40, type = luaType.Int32 },
        mRollingInCounter = { offset = 44, type = luaType.Int32 },
        mSquishedCounter = { offset = 48, type = luaType.Int32 },
        mMowerState = { offset = 52, type = luaType.Int32 },
        mDead = { offset = 56, type = luaType.Boolean },
        mVisible = { offset = 57, type = luaType.Boolean },
        mMowerType = { offset = 60, type = luaType.Int32 },
        mAltitude = { offset = 64, type = luaType.Float32 },
        mMowerHeight = { offset = 68, type = luaType.Int32 },
        mLastPortalX = { offset = 72, type = luaType.Int32 },
        mKilledZombies = { offset = 76, type = luaType.Int32 },
        mUnknown80 = { offset = 80, type = luaType.Boolean },
        mUnknown81 = { offset = 81, type = luaType.Boolean },
        mIsSuper = { offset = 82, type = luaType.Boolean },
        mShowFireParticle = { offset = 83, type = luaType.Boolean },
        mUnknown84 = { offset = 84, type = luaType.Int32 },
        mUnknown88 = { offset = 88, type = luaType.Int32 },
        mExplodeCounter = { offset = 92, type = luaType.Int32 },
    },
})

corex.GridItem = corex.bind({
    name = "GridItem",
    size = 320,
    properties = {
        mApp = { offset = 0, type = luaType.Pointer },
        mBoard = { offset = 8, type = luaType.Pointer },
        mGridItemType = { offset = 16, type = luaType.Int32 },
        mGridItemState = { offset = 20, type = luaType.Int32 },
        mGridX = { offset = 24, type = luaType.Int32 },
        mGridY = { offset = 28, type = luaType.Int32 },
        mGridItemCounter = { offset = 32, type = luaType.Int32 },
        mRenderOrder = { offset = 36, type = luaType.Int32 },
        mDead = { offset = 40, type = luaType.Boolean },
        mPosX = { offset = 44, type = luaType.Float32 },
        mPosY = { offset = 48, type = luaType.Float32 },
        mGoalX = { offset = 52, type = luaType.Float32 },
        mGoalY = { offset = 56, type = luaType.Float32 },
        mGridItemReanimID = { offset = 60, type = luaType.Int32 },
        mGridItemParticleID = { offset = 64, type = luaType.Int32 },
        mZombieType = { offset = 68, type = luaType.Int32 },
        mSeedType = { offset = 72, type = luaType.Int32 },
        mScaryPotType = { offset = 76, type = luaType.Int32 },
        mHighlighted = { offset = 80, type = luaType.Boolean },
        mTransparentCounter = { offset = 84, type = luaType.Int32 },
        mSunCount = { offset = 88, type = luaType.Int32 },
        -- MotionTrailFrame mMotionTrailFrames[NUM_MOTION_TRAIL_FRAMES];
        mMotionTrailCount = { offset = 236, type = luaType.Int32 },
        -- int mPlaceHolder[20];
    },
})

corex.TouchInfo = corex.bind({
    name = "TouchInfo",
    size = 40,
    properties = {
        mUnknown0 = { offset = 0, type = luaType.Boolean },
        mX = { offset = 4, type = luaType.Int32 },
        mY = { offset = 8, type = luaType.Int32 },
        mCursorObject = { offset = 16, type = luaType.Pointer },
        mCursorPreview = { offset = 24, type = luaType.Pointer },
        mIdEnt = { offset = 32, type = luaType.Pointer },
    },
    functions = {
        TouchInfo = { offset = 0x6234A4, type = funcType.DirCall, sign = "v*" },
        Init = { offset = 0x6234D8, type = funcType.DirCall, sign = "v*" },
    },
})

return corex