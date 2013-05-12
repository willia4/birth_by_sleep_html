#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <locale>
#include <algorithm>

using namespace std;

string requestedCommand, lowercaseCommands[160];

const string commandNames[160] = {"Quick Blitz", "Blitz", "Meteor Crash", "Magic Hour", "Sliding Dash","Fire Dash", "Dark Haze", "Sonic Blade",
"Chaos Blade", "Zantetsuken", "Strike Raid", "Freeze Raid", "Treasure Raid", "Spark Raid", "Wind Raid", "Fire Surge","Barrier Surge", "Thunder Surge",
"Aerial Slam", "Ars Solum", "Ars Arcanum", "Time Splicer", "Poison Edge", "Wishing Edge", "Blizzard Edge", "Stun Edge", "Slot Edge",  "Fire Strike",
"Confusion Strike", "Binding Strike", "Brutal Blast", "Tornado Strike", "Magnet Spiral", "Windcutter", "Limit Storm", "Salvation", "Collision Magnet",
"Geo Impact", "Sacrifice", "Break Time", "Fire", "Fira", "Firaga", "Dark Firaga", "Fission Firaga", "Triple Firaga", "Crawling Fire", "Blizzard",
"Blizzara", "Blizzaga", "Triple Blizzaga", "Thunder", "Thundara", "Thundaga", "Thundaga Shot", "Cure", "Cura", "Curaga", "Esuna", "Mine Shield",
"Mine Square", "Seeker Mine", "Zero Gravity", "Zero Gravira", "Zero Graviga", "Magnet", "Magnera", "Magnega", "Munny Magnet", "Energy Magnet",
"D-Link Magnet", "Aero", "Aerora", "Aeroga", "Warp", "Faith", "Deep Freeze", "Glacier", "Ice Barrage", "Firaga Burst", "Raging Storm", "Mega Flare",
"Quake", "Meteor", "Tornado", "Transcendence", "Mini", "Blackout", "Ignite", "Confuse", "Bind", "Poison", "Slow", "Stop", "Stopra", "Stopga", "Sleep",
"Group Cure", "Group Cura", "Group Curaga", "Group Esuna", "Confetti", "Fireworks", "Taunt", "Victory Pose", "Vanish", "Trinity Limit", "Unison Rush",
"Voltage Stack", "Jump", "High Jump", "Dodge Roll", "Thunder Roll", "Cartwheel", "Firewheel", "Air Slide", "Ice Slide", "Sonic Impact", "Slide",
"Reversal", "Glide", "Superglide", "Fire Glide", "Homing Slide", "Teleport", "Doubleflight", "Block", "Renewal Block", "Focus Block", "Stun Block",
"Poison Block", "Barrier", "Renewal Barrier", "Focus Barrier", "Confuse Barrier", "Stop Barrier", "Counter Hammer", "Payback Fang", "Counter Rush",
"Reversal Slash", "Payback Raid", "Counter Blast", "Payback Surge", "Meteor Shower", "Flame Salvo", "Chaos Snake", "Bubble Blaster", "Dark Volley",
"Ragnarok", "Thunderstorm", "Bio Barrage", "Pulse Bomb", "Prism Rain", "Photon Charge", "Absolute Zero", "Lightning Ray", "Sonic Shadow", "Ultima Cannon",
"Multivortex", "Lightbloom"};

const string abilityNames[30] = {"Treasure Magnet", "HP Prize Plus", "Link Prize Plus", "Lucky Strike", "HP Boost", "Fire Boost", "Blizzard Boost",
"Thunder Boost", "Cure Boost", "Item Boost", "Attack Haste", "Magic Haste", "Combo F Boost", "Finish Boost", "Fire Screen", "Blizzard Screen",
"Thunder Screen", "Dark Screen", "Reload Boost", "Defender", "Zero EXP", "Combo Plus", "Air Combo Plus", "EXP Chance", "EXP Walker", "Damage Syphon",
"Second Chance", "Once More", "Scan", "Leaf Bracer"};

const string crystalNames[7] = {"Shimmering", "Fleeting", "Pulsing", "Wellspring", "Soothing", "Hungry", "Abounding"};

const int quickBlitz = 0, blitz = 1, meteorCrash = 2, magicHour = 3, slidingDash = 4, fireDash = 5, darkHaze = 6, sonicBlade = 7, chaosBlade = 8,
zantetsuken = 9, strikeRaid = 10, freezeRaid = 11, treasureRaid = 12, sparkRaid = 13, windRaid = 14, fireSurge = 15, barrierSurge = 16,
thunderSurge = 17, aerialSlam = 18, arsSolum = 19, arsArcanum = 20, timeSplicer = 21, poisonEdge = 22, wishingEdge = 23, blizzardEdge = 24,
stunEdge = 25, slotEdge = 26, fireStrike = 27, confusionStrike = 28, bindingStrike = 29, brutalBlast = 30, tornadoStrike = 31, magnetSpiral = 32,
windcutter = 33, limitStorm = 34, salvation = 35, collisionMagnet = 36, geoImpact = 37, sacrifice = 38, breakTime = 39, fire = 40, fira = 41,
firaga = 42, darkFiraga = 43, fissionFiraga = 44, tripleFiraga = 45, crawlingFire = 46, blizzard = 47, blizzara = 48, blizzaga = 49,
tripleBlizzaga = 50, thunder = 51, thundara = 52, thundaga = 53, thundagaShot = 54, cure = 55, cura = 56, curaga = 57, esuna = 58, mineShield = 59,
mineSquare = 60, seekerMine = 61, zeroGravity = 62, zeroGravira = 63, zeroGraviga = 64, magnet = 65, magnera = 66, magnega = 67, munnyMagnet = 68,
energyMagnet = 69, dLinkMagnet = 70, aero = 71, aerora = 72, aeroga = 73, warp = 74, faith = 75, deepFreeze = 76, glacier = 77, iceBarrage = 78,
firagaBurst = 79, ragingStorm = 80, megaFlare = 81, quake = 82, meteor = 83, tornado = 84, transcendence = 85, mini = 86, blackout = 87, ignite = 88,
confuse = 89, bind = 90, poison = 91, slow = 92, stop = 93, stopra = 94, stopga = 95, my_sleep = 96, groupCure = 97, groupCura = 98, groupCuraga = 99,
groupEsuna = 100, confetti = 101, fireworks = 102, taunt = 103, victoryPose = 104, vanish = 105, trinityLimit = 106, unisonRush = 107, voltageStack = 108,
jump = 109, highJump = 110, dodgeRoll = 111, thunderRoll = 112, cartwheel = 113, firewheel = 114, airSlide = 115, iceSlide = 116, sonicImpact = 117,
slide = 118, reversal = 119, glide = 120, superglide = 121, fireGlide = 122, homingSlide = 123, teleport = 124, doubleflight = 125, block = 126,
renewalBlock = 127, focusBlock = 128, stunBlock = 129, poisonBlock = 130, barrier = 131, renewalBarrier = 132, focusBarrier = 133, confuseBarrier = 134,
stopBarrier = 135, counterHammer = 136, paybackFang = 137, counterRush = 138, reversalSlash = 139, paybackRaid = 140, counterBlast = 141, paybackSurge = 142,
meteorShower = 143, flameSalvo = 144, chaosSnake = 145, bubbleBlaster = 146, darkVolley = 147, ragnarok = 148, thunderstorm = 149, bioBarrage = 150,
pulseBomb = 151, prismRain = 152, photonCharge = 153, absoluteZero = 154, lightningRay = 155, sonicShadow = 156, ultimaCannon = 157, multivortex = 158,
lightbloom = 159, treasureMagnet = 0, hpPrizePlus = 1, linkPrizePlus = 2, luckyStrike = 3, hpBoost = 4, fireBoost = 5, blizzardBoost = 6,
thunderBoost = 7, cureBoost = 8, itemBoost = 9, attackHaste = 10, magicHaste = 11, comboFBoost = 12, finishBoost = 13, fireScreen = 14,
blizzardScreen = 15, thunderScreen = 16, darkScreen = 17, reloadBoost = 18, defender = 19, zeroEXP = 20, comboPlus = 21, airComboPlus = 22,
expChance = 23, expWalker = 24, damageSyphon = 25, secondChance = 26, onceMore = 27, scan = 28, leafBracer = 29, shimmering = 0, fleeting = 1,
pulsing = 2, wellspring = 3, soothing = 4, hungry = 5, abounding = 6, tva = 0, tvx = 1, txa = 2, txx = 3, xva = 4, xvx = 5, xxa = 6, a = 10, b = 11,
c = 12, d = 13, e = 14, f = 15, g = 16, null = 0;

// Command, Ingredient 1, LVL of ing1, Ingredient 2, LVL of ing2,  Rate, TVA, Ability
const int commandFormulae[296][8] = {
	{aerialSlam, aero, 3, fireSurge, 3, 100, tva, c}, 
	{aerialSlam, aerora, 3, fireStrike, 3, 90, tva, b},
	{aerialSlam, highJump, 3, fireDash, 3, 100, tva, 9}, 
	{aeroga, aero, 3, aerora, 3, 90, tva, 5}, 
	{aeroga, aerora, 3, aerora, 3, 90, tva, 6},
{aeroga, aerora, 3, quickBlitz, 3, 90, tva, 7}, {aerora, aero, 2, aero, 2, 95, tva, 1}, {aerora, aero, 2, quickBlitz, 2, 95, tva, 3},
{aerora, aero, 2, thunder, 2, 95, tva, d}, {arsArcanum, aerialSlam, 4, blitz, 4, 100, xvx, 2}, {arsArcanum, aerora, 3, fireStrike, 3, 10, xvx, b},
{arsArcanum, cura, 2, blizzardEdge, 2, 5, xvx, 3}, {arsArcanum, cura, 2, poisonEdge, 2, 5, xvx, 8}, {arsArcanum, quickBlitz, 2, blizzara, 2, 5, xvx, 4},
{arsArcanum, quickBlitz, 2, blizzard, 2, 5, xvx, 3}, {arsArcanum, quickBlitz, 3, slotEdge, 3, 10, xvx, 7}, {arsArcanum, slidingDash, 2, blizzara, 2, 5, xvx, 3},
{arsArcanum, slidingDash, 2, blizzard, 2, 5, xvx, 1}, {arsSolum, confusionStrike, 3, thundara, 3, 5, txx, d}, {arsSolum, sonicBlade, 5, darkHaze, 4, 20, txx, a},
{arsSolum, stopga, 4, darkHaze, 4, 20, txx, a}, {arsSolum, stopga, 4, sonicBlade, 5, 20, txx, 2}, {arsSolum, thundara, 3, strikeRaid, 3, 5, txx, f},
{arsSolum, thunder, 2, slidingDash, 2, 5, txx, g}, {arsSolum, thunder, 2, strikeRaid, 2, 5, txx, f}, {barrierSurge, fireDash, 3, barrier, 3, 100, xxa, c},
{barrierSurge, stunEdge, 3, barrier, 3, 100, xxa, f}, {bindingStrike, quickBlitz, 2, bind, 2, 100, tva, f}, {bindingStrike, strikeRaid, 2, bind, 2, 100, tva, 7},
{bindingStrike, stunEdge, 2, zeroGravity, 2, 100, tva, d}, {bioBarrage, poison, 3, block, 1, 20, tvx, null}, {bioBarrage, poisonEdge, 3, block, 1, 20, tvx, null},
{bioBarrage, quickBlitz, 2, poison, 2, 5, tva, null}, {bioBarrage, slidingDash, 2, poison, 2, 5, tva, null}, {bioBarrage, strikeRaid, 2, poison, 2, 5, tva, null},
{blackout, confuse, 3, zeroGravira, 3, 100, tva, 6}, {blackout, confuse, 3, zeroGravity, 3, 100, tva, 5}, {blackout, zeroGravira, 3, poison, 3, 100, tva, 8},
{blitz, barrierSurge, 3, wishingEdge, 3, 90, xxa, 8}, {blitz, quickBlitz, 3, slotEdge, 3, 90, tva, 7}, {blitz, stunEdge, 3, slotEdge, 3, 90, tva, f},
{blizzaga, blizzara, 3, blizzara, 3, 100, tva, 2}, {blizzaga, blizzard, 3, blizzara, 3, 100, tva, 1}, {blizzaga, blizzardEdge, 3, blizzara, 3, 100, tva, 3},
{blizzara, aero, 2, blizzard, 2, 100, tva, 4}, {blizzara, blizzard, 2, blizzard, 2, 100, tva, 4}, {blizzara, blizzard, 2, blizzardEdge, 2, 100, tva, 3},
{blizzara, strikeRaid, 2, blizzard, 2, 100, tva, 3}, {blizzardEdge, quickBlitz, 2, blizzara, 2, 95, tva, 4}, {blizzardEdge, quickBlitz, 2, blizzard, 2, 95, tva, 3},
{blizzardEdge, slidingDash, 2, blizzara, 2, 95, tva, 3}, {blizzardEdge, slidingDash, 2, blizzard, 2, 95, tva, 1}, {breakTime, curaga, 2, focusBarrier, 2, 10, xxa, 8},
{breakTime, curaga, 2, focusBlock, 2, 10, tvx, 8}, {breakTime, curaga, 2, renewalBarrier, 2, 10, xxa, 6}, {breakTime, curaga, 2, renewalBlock, 2, 10, tvx, 6},
{brutalBlast, mineSquare, 3, bindingStrike, 3, 70, txx, g}, {brutalBlast, stunEdge, 3, mineShield, 3, 70, txx, 7}, {chaosBlade, sonicBlade, 5, darkHaze, 4, 80, txx, a},
{collisionMagnet, quickBlitz, 3, magnera, 3, 80, tva, f}, {collisionMagnet, stunEdge, 3, magnera, 3, 80, tva, g}, {collisionMagnet, zeroGravira, 3, magnet, 3, 80, tva, d},
{confuseBarrier, confuse, 3, barrier, 1, 100, xxa, g}, {confuseBarrier, confusionStrike, 3, barrier, 1, 100, xxa, b}, {confusionStrike, confuse, 2, strikeRaid, 2, 100, tva, 3},
{confusionStrike, quickBlitz, 2, confuse, 2, 100, tva, 7}, {confusionStrike, slidingDash, 2, zeroGravity, 2, 100, tva, f}, {crawlingFire, slow, 3, firaga, 3, 80, tva, 9},
{crawlingFire, stopga, 3, firaga, 3, 80, tva, a}, {crawlingFire, stopra, 3, firaga, 3, 80, tva, c}, {cura, aero, 2, cure, 2, 100, tva, 7}, {cura, cure, 2, cure, 2, 100, tva, 5},
{cura, cure, 2, thunder, 2, 100, tva, d}, {curaga, cura, 3, cura, 3, 100, tva, 6}, {curaga, cura, 3, cure, 3, 100, tva, 5}, {dLinkMagnet, stopra, 3, magnera, 3, 100, xxa, d},
{dLinkMagnet, zeroGravira, 3, magnera, 3, 100, xxa, g}, {darkFiraga, darkHaze, 4, firaga, 4, 100, txx, c}, {darkFiraga, firaga, 4, blackout, 3, 100, txx, a},
{darkHaze, fireDash, 3, blackout, 3, 100, txx, 9}, {darkHaze, zeroGravira, 3, fireDash, 3, 100, txx, c}, {darkHaze, zeroGravity, 3, fireSurge, 3, 100, txx, b},
{deepFreeze, bindingStrike, 3, blizzaga, 4, 100, tva, 4}, {deepFreeze, freezeRaid, 4, blizzaga, 4, 100, tva, 3}, {deepFreeze, tripleBlizzaga, 4, blizzaga, 4, 100, xxa, 2},
{energyMagnet, cura, 3, magnera, 3, 100, xxa, 6}, {energyMagnet, cure, 3, magnera, 3, 100, xxa, 5}, {faith, windRaid, 5, breakTime, 4, 100, xvx, 6}, {fira, fire, 2, fire, 2, 100, tva, 9},
{fira, fire, 2, fireDash, 2, 100, tva, c}, {fira, fire, 2, fireStrike, 2, 100, tva, c}, {fira, ignite, 2, fire, 2, 100, tva, b}, {firaga, fira, 3, fira, 3, 90, tva, a},
{firaga, fire, 3, fira, 3, 90, tva, 9}, {firaga, fira, 3, fireDash, 3, 90, tva, c}, {firagaBurst, aeroga, 3, fira, 3, 20, xxa, 9}, {firagaBurst, aeroga, 3, firaga, 3, 20, xxa, a},
{firagaBurst, aerora, 3, firaga, 3, 20, xxa, 9}, {firagaBurst, slow, 3, firaga, 3, 20, xxa, 9}, {firagaBurst, stopga, 3, firaga, 3, 20, xxa, a}, {firagaBurst, stopra, 3, firaga, 3, 20, xxa, c},
{fireDash, confusionStrike, 2, fire, 2, 100, tva, c}, {fireDash, slidingDash, 2, fire, 2, 100, tva, c}, {fireDash, slidingDash, 2, fira, 2, 100, tva, b},
{fireGlide, glide, null, firaga, 4, 100, xvx, a}, {fireGlide, glide, null, fireSurge, 3, 100, xvx, b}, {firewheel, firaga, 4, cartwheel, 4, 100, xxa, a},
{firewheel, fireSurge, 3, cartwheel, 4, 90, xxa, b}, {firewheel, fissionFiraga, 4, cartwheel, 4, 100, xxa, a}, {fireStrike, fira, 2, poisonEdge, 2, 100, tva, c},
{fireStrike, stunEdge, 2, fire, 2, 100, tva, f}, {fireStrike, wishingEdge, 2, ignite, 2, 100, xxa, 9}, {fireSurge, bindingStrike, 3, fira, 3, 100, tva, f},
{fireSurge, confusionStrike, 3, fira, 3, 100, tva, 7}, {fireSurge, fireStrike, 3, fira, 3, 100, tva, 9}, {fireSurge, ignite, 3, fireDash, 3, 100, tva, c},
{fissionFiraga, aeroga, 3, fira, 3, 80, tva, 9}, {fissionFiraga, aeroga, 3, firaga, 3, 80, tva, a}, {fissionFiraga, aerora, 3, firaga, 3, 80, tva, 9},
{freezeRaid, bindingStrike, 3, blizzardEdge, 3, 100, tva, f}, {freezeRaid, strikeRaid, 3, blizzara, 3, 100, tva, d}, {geoImpact, brutalBlast, 4, brutalBlast, 4, 70, txx, 6},
{glacier, deepFreeze, 5, blizzaga, 4, 100, xxa, 1}, {glacier, tripleBlizzaga, 4, deepFreeze, 5, 100, xxa, 2}, {homingSlide, airSlide, 3, magnet, 3, 100, xva, g},
{homingSlide, airSlide, 3, slidingDash, 3, 100, xva, b}, {homingSlide, slidingDash, 3, magnera, 3, 100, xva, 8}, {iceBarrage, mineShield, 4, blizzaga, 4, 100, xxa, 2},
{iceBarrage, mineSquare, 4, blizzaga, 4, 100, xxa, 4}, {iceSlide, airSlide, 4, blizzaga, 4, 100, tva, 4}, {iceSlide, airSlide, 4, blizzardEdge, 3, 100, tva, 2},
{ignite, bind, 3, fira, 3, 100, tva, b}, {ignite, bind, 3, fire, 3, 100, tva, 9}, {lightningRay, airSlide, 4, blitz, 4, 10, tva, null}, {lightningRay, barrierSurge, 3, aeroga, 4, 10, xxa, null},
{lightningRay, darkHaze, 4, blitz, 4, 10, txx, null}, {lightningRay, thundara, 3, bindingStrike, 3, 10, tva, null}, {lightningRay, thundara, 3, thundara, 3, 10, tva, null},
{lightningRay, thunder, 3, thundara, 3, 10, tva, null}, {lightningRay, thunderSurge, 4, fireDash, 4, 10, tva, null}, {limitStorm, bindingStrike, 3, brutalBlast, 4, 100, txx, 9},
{limitStorm, confusionStrike, 3, brutalBlast, 4, 100, txx, 3}, {magicHour, barrierSurge, 3, aeroga, 4, 90, xxa, 6}, {magicHour, zeroGraviga, 4, blitz, 4, 90, xxa, 7},
{magnega, magnera, 3, magnera, 3, 100, tva, e}, {magnega, magnet, 3, magnera, 3, 100, tva, d}, {magnera, magnet, 2, magnet, 2, 100, tva, 5}, {magnera, stunEdge, 2, magnet, 2, 100, tva, f},
{magnera, thunder, 2, magnet, 2, 100, tva, d}, {magnetSpiral, bindingStrike, 3, collisionMagnet, 4, 100, tva, f}, {magnetSpiral, bindingStrike, 3, magnega, 4, 100, tva, e},
{magnetSpiral, quickBlitz, 3, magnera, 3, 20, tva, f}, {magnetSpiral, stunEdge, 3, magnera, 3, 20, tva, g}, {magnetSpiral, zeroGravira, 3, magnet, 3, 20, tva, d},
{megaFlare, fissionFiraga, 4, crawlingFire, 4, 100, tva, a}, {meteor, brutalBlast, 4, magnega, 4, 10, txx, b}, {meteor, geoImpact, 5, quake, 5, 100, txx, a},
{meteor, zeroGraviga, 4, brutalBlast, 4, 10, txx, a}, {meteorCrash, fireStrike, 3, brutalBlast, 4, 100, txx, c}, {meteorCrash, quake, 5, blitz, 4, 100, txx, 6},
{meteorShower, thundaga, 3, firaga, 3, 15, xxa, null}, {meteorShower, thundaga, 3, freezeRaid, 3, 15, xxa, null}, {meteorShower, thundaga, 3, strikeRaid, 3, 15, xxa, null},
{meteorShower, zeroGraviga, 4, blitz, 4, 10, xxa, null}, {mineShield, fira, 3, block, 1, 100, tvx, b}, {mineShield, stop, 3, ignite, 3, 100, tva, c}, {mineShield, stopra, 3, block, 1, 100, tvx, 5},
{mineShield, zeroGravity, 3, fira, 3, 100, tva, 9}, {mineSquare, aerora, 3, ignite, 3, 100, tva, c}, {mineSquare, fira, 3, barrier, 1, 100, xxa, b}, {mineSquare, stop, 3, fira, 3, 100, tva, 9},
{mineSquare, stopra, 3, barrier, 1, 100, xxa, 5}, {mini, bind, 3, magnega, 4, 100, tva, d}, {mini, magnega, 4, magnera, 4, 100, tva, e}, {mini, warp, 4, magnera, 3, 100, xxa, 6},
{munnyMagnet, thundara, 3, magnera, 3, 100, xxa, d}, {munnyMagnet, wishingEdge, 3, magnera, 3, 100, xxa, f}, {paybackFang, slidingDash, 2, counterHammer, 2, 100, txx, 8},
{paybackRaid, strikeRaid, 2, slidingDash, 2, 100, xvx, 8}, {paybackSurge, slidingDash, 2, fireSurge, 2, 100, xxa, b}, {paybackSurge, thunderSurge, 2, slidingDash, 2, 100, xxa, g},
{poisonBlock, poison, 3, block, 1, 80, tvx, 8}, {poisonBlock, poisonEdge, 3, block, 1, 80, tvx, 4}, {poisonEdge, quickBlitz, 2, poison, 2, 95, tva, 7}, {poisonEdge, slidingDash, 2, poison, 2, 95, tva, f},
{poisonEdge, strikeRaid, 2, poison, 2, 95, tva, c}, {quake, brutalBlast, 4, brutalBlast, 4, 30, txx, 6}, {quake, brutalBlast, 4, magnega, 4, 90, txx, b}, {quake, mineSquare, 3, bindingStrike, 3, 30, txx, g},
{quake, stunEdge, 3, mineShield, 3, 30, txx, 7}, {quake, zeroGraviga, 4, brutalBlast, 4, 90, txx, a}, {ragingStorm, fira, 3, fira, 3, 10, xxa, a}, {ragingStorm, firaga, 3, blitz, 3, 10, xxa, c},
{ragingStorm, fira, 3, firaga, 3, 10, xxa, 9}, {ragingStorm, firaga, 3, firaga, 3, 10, xxa, a}, {ragingStorm, fire, 3, fira, 3, 10, xxa, 9}, {ragingStorm, fira, 3, fireDash, 3, 10, xxa, c},
{ragingStorm, fireSurge, 3, cartwheel, 4, 10, xxa, b}, {ragingStorm, fissionFiraga, 4, firagaBurst, 5, 100, xxa, a}, {renewalBarrier, curaga, 4, barrier, 1, 100, xxa, 8},
{renewalBarrier, esuna, null, barrier, 1, 100, xxa, 6}, {renewalBlock, curaga, 4, block, 1, 100, tvx, 8}, {renewalBlock, esuna, null, block, 1, 100, tvx, b}, {sacrifice, darkHaze, 4, warp, 5, 100, txx, a},
{sacrifice, poisonEdge, 3, warp, 5, 100, txx, c}, {salvation, windRaid, 5, curaga, 4, 100, xvx, 6}, {seekerMine, mineShield, 4, magnega, 4, 100, xxa, b}, {seekerMine, mineShield, 4, mineSquare, 4, 100, xxa, a},
{seekerMine, mineSquare, 4, magnega, 4, 100, xxa, c}, {slotEdge, cura, 2, blizzardEdge, 2, 95, tva, 3}, {slotEdge, cura, 2, poisonEdge, 2, 95, tva, 8}, {slotEdge, curaga, 2, focusBarrier, 2, 90, xxa, 8},
{slotEdge, curaga, 2, focusBlock, 2, 90, tvx, 8}, {slotEdge, curaga, 2, renewalBarrier, 2, 90, xxa, 6}, {slotEdge, curaga, 2, renewalBlock, 2, 90, tvx, 6}, {slotEdge, wishingEdge, 2, cure, 2, 100, xxa, 7},
{sonicBlade, airSlide, 4, blitz, 4, 90, tva, 6}, {sonicBlade, darkHaze, 4, blitz, 4, 90, txx, c}, {sonicBlade, thunderSurge, 4, fireDash, 4, 90, tva, f}, {sparkRaid, freezeRaid, 4, magnega, 4, 100, xvx, e},
{sparkRaid, stunBlock, 3, dodgeRoll, 4, 20, xvx, g}, {sparkRaid, thundaga, 4, dodgeRoll, 4, 20, xvx, g}, {sparkRaid, thunderSurge, 4, dodgeRoll, 4, 20, xvx, 8},
{sparkRaid, treasureRaid, 4, magnega, 4, 100, xvx, 6}, {stopBarrier, stopga, 3, barrier, 1, 80, xxa, b}, {stopga, stop, 3, stopra, 3, 100, tva, d}, {stopga, stopra, 3, stopra, 3, 100, tva, e},
{stopra, slow, 2, slow, 2, 100, tva, g}, {stopra, stop, 2, slow, 2, 100, tva, f}, {stopra, stop, 2, stop, 2, 100, tva, d}, {strikeRaid, quickBlitz, 2, slidingDash, 2, 100, tva, 7},
{stunBlock, stunEdge, 3, block, 1, 100, tvx, g}, {stunBlock, thundaga, 4, block, 1, 100, tvx, d}, {stunEdge, thundara, 3, strikeRaid, 3, 95, tva, f}, {stunEdge, thunder, 2, slidingDash, 2, 95, tva, f},
{stunEdge, thunder, 2, strikeRaid, 2, 95, tva, g}, {thundaga, thundara, 3, bindingStrike, 3, 90, tva, f}, {thundaga, thundara, 3, thundara, 3, 90, tva, e}, {thundaga, thunder, 3, thundara, 3, 90, tva, d},
{thundagaShot, thundaga, 3, firaga, 3, 85, xxa, 9}, {thundagaShot, thundaga, 3, freezeRaid, 3, 85, xxa, 1}, {thundagaShot, thundaga, 3, strikeRaid, 3, 85, xxa, d},
{thundara, thunder, 2, stunEdge, 2, 100, tva, f}, {thundara, thunder, 2, thunder, 2, 100, tva, d}, {thundara, zeroGravity, 2, magnet, 2, 100, tva, g}, {thunderRoll, stunBlock, 3, dodgeRoll, 4, 80, xvx, g},
{thunderRoll, thundaga, 4, dodgeRoll, 4, 80, xvx, g}, {thunderRoll, thunderSurge, 4, dodgeRoll, 4, 80, xvx, 8}, {thunderSurge, confusionStrike, 3, thundara, 3, 95, tva, d},
{thunderSurge, thundara, 3, fireDash, 3, 100, tva, c}, {thunderSurge, thundara, 3, freezeRaid, 3, 100, tva, 3}, {thunderSurge, thundara, 3, stunEdge, 3, 100, tva, d},
{timeSplicer, aerialSlam, 4, stopga, 4, 100, xva, 2}, {timeSplicer, barrierSurge, 3, wishingEdge, 3, 10, xxa, 8}, {timeSplicer, stopga, 3, barrier, 1, 20, xxa, b},
{timeSplicer, stunEdge, 3, slotEdge, 3, 10, xva, f}, {tornado, aero, 2, aero, 2, 5, xvx, 1}, {tornado, aero, 3, aerora, 3, 10, xvx, 5}, {tornado, aero, 2, quickBlitz, 2, 5, xvx, 3},
{tornado, aero, 2, thunder, 2, 5, xvx, d}, {tornado, aeroga, 4, magnega, 4, 100, xvx, 6}, {tornado, aerora, 3, aerora, 3, 10, xvx, 6}, {tornado, aerora, 3, quickBlitz, 3, 10, xvx, 7},
{tornadoStrike, aeroga, 4, bindingStrike, 3, 100, xvx, 2}, {tornadoStrike, aeroga, 4, confusionStrike, 3, 100, xvx, 3}, {transcendence, zeroGraviga, 4, magnetSpiral, 5, 100, tva, e},
{treasureRaid, slotEdge, 3, magnera, 3, 100, xvx, f}, {treasureRaid, slotEdge, 3, magnet, 3, 100, xvx, c}, {treasureRaid, slotEdge, 3, strikeRaid, 3, 100, xvx, 7},
{tripleBlizzaga, blizzaga, 3, blitz, 3, 100, xxa, 3}, {tripleBlizzaga, blizzaga, 3, blizzaga, 3, 100, xxa, 2}, {tripleBlizzaga, blizzara, 3, blizzaga, 3, 100, xxa, 1},
{tripleFiraga, fira, 3, firaga, 3, 90, xxa, 9}, {tripleFiraga, firaga, 3, blitz, 3, 90, xxa, c}, {tripleFiraga, firaga, 3, firaga, 3, 90, xxa, a}, {warp, aero, 2, magnet, 2, 10, txx, 8},
{warp, thundara, 3, zeroGravira, 3, 20, txx, d}, {warp, thunder, 2, zeroGravity, 2, 10, txx, d}, {warp, zeroGravira, 3, zeroGravira, 3, 20, txx, 6}, {warp, zeroGravity, 2, zeroGravira, 3, 20, txx, 5},
{warp, zeroGravity, 2, zeroGravity, 2, 10, txx, 5}, {windRaid, aeroga, 4, freezeRaid, 4, 100, xvx, a}, {windRaid, aeroga, 4, treasureRaid, 4, 100, xvx, 2}, {windcutter, aeroga, 4, bindingStrike, 3, 100, txx, 2},
{windcutter, aeroga, 4, confusionStrike, 3, 100, txx, 3}, {wishingEdge, barrierSurge, 2, strikeRaid, 2, 100, xxa, 7}, {wishingEdge, barrierSurge, 2, stunEdge, 2, 100, xxa, f},
{wishingEdge, stunEdge, 2, bindingStrike, 2, 100, xxa, e}, {zantetsuken, stopga, 4, darkHaze, 4, 80, txx, a}, {zantetsuken, stopga, 4, sonicBlade, 5, 80, txx, 2},
{zeroGraviga, thundara, 3, zeroGravira, 3, 80, tva, d}, {zeroGraviga, zeroGravira, 3, zeroGravira, 3, 80, tva, 6}, {zeroGraviga, zeroGravity, 3, zeroGravira, 3, 80, tva, 5},
{zeroGravira, aero, 2, magnet, 2, 90, tva, 8}, {zeroGravira, thunder, 2, zeroGravity, 2, 90, tva, d}, {zeroGravira, zeroGravity, 2, zeroGravity, 2, 90, tva, 5}};

const int abilityFormulae[16][7] = {{blizzardBoost, magicHaste, leafBracer, comboPlus, itemBoost, hpPrizePlus, luckyStrike},
{blizzardBoost, reloadBoost, secondChance, airComboPlus, damageSyphon, hpPrizePlus, luckyStrike},
{blizzardScreen, attackHaste, leafBracer, airComboPlus, itemBoost, hpPrizePlus, luckyStrike},
{blizzardScreen, magicHaste, comboFBoost, airComboPlus, itemBoost, hpPrizePlus, expWalker},
{cureBoost, magicHaste, comboFBoost, comboPlus, itemBoost, treasureMagnet, luckyStrike},
{cureBoost, reloadBoost, secondChance, comboPlus, defender, treasureMagnet, luckyStrike},
{darkScreen, attackHaste, finishBoost, airComboPlus, itemBoost, treasureMagnet, luckyStrike},
{darkScreen, magicHaste, comboFBoost, airComboPlus, itemBoost, treasureMagnet, expWalker},
{fireBoost, magicHaste, leafBracer, airComboPlus, hpBoost, hpPrizePlus, linkPrizePlus},
{fireBoost, reloadBoost, finishBoost, onceMore, damageSyphon, hpPrizePlus, expChance},
{fireScreen, attackHaste, finishBoost, comboPlus, hpBoost, hpPrizePlus, linkPrizePlus},
{fireScreen, attackHaste, leafBracer, comboPlus, hpBoost, hpPrizePlus, linkPrizePlus},
{thunderBoost, magicHaste, comboFBoost, airComboPlus, hpBoost, treasureMagnet, linkPrizePlus},
{thunderBoost, reloadBoost, comboFBoost, onceMore, defender, treasureMagnet, expChance},
{thunderScreen, attackHaste, finishBoost, comboPlus, hpBoost, treasureMagnet, linkPrizePlus},
{thunderScreen, attackHaste, finishBoost, comboPlus, hpBoost, treasureMagnet, luckyStrike}};

void fill_lowercaseCommands(),melding_calculator(const string &), columnize_list(const vector<string> &), input_output(), generate_list(),
make_lowercase(string &), more_info(const int &, const vector<int> &), program_info();

int main()
{
    fill_lowercaseCommands();

    cout << "------KINGDOM HEARTS: BIRTH BY SLEEP COMMAND MELDING QUICK-REFERENCE GUIDE------"
            "Enter \"about\" for program information." << endl << endl << endl;

    for(;;)
    {
        input_output();
    }

    return 0;
}

void input_output()
{
    string command;
    bool noMatchFound = true;

    cout << "Enter a command name or enter \"list\" for a list of acceptable inputs:" << endl;
    getline(cin, command);
    make_lowercase(command);
    cout << endl;

    if(command == "list" || command == "about")
    {
        noMatchFound = false;
    }
    else
    {
        for(int x = 0; x < 160; x++)
        {
            if(command == lowercaseCommands[x])
            {
                requestedCommand = commandNames[x];
                noMatchFound = false;
                break;
            }
        }
    }

    if(noMatchFound)
    {
        cout << "*** No match found. Retry input or enter \"list\" to view acceptable inputs. ***" << endl << endl;
    }
    else if(command == "list")
    {
        generate_list();
    }
    else if(command == "about")
    {
        program_info();
    }
    else
    {
        melding_calculator(command);
    }
}

void fill_lowercaseCommands()
{
    for(int x = 0; x < 160; x++)
    {
        lowercaseCommands[x] = commandNames[x];

        for(unsigned int y = 0; y < commandNames[x].length(); y++)
        {
            lowercaseCommands[x][y] = tolower(commandNames[x][y]);
        }
    }
}

void generate_list()
{
    vector <string> commandList(160);

    for(int x = 0; x < 160; x++)
    {
        commandList[x] = commandNames[x];
    }

    sort(commandList.begin(), commandList.end());

    cout << "--------------------------------------------------------------------------------";

    cout << "---List of Commands" << endl << endl;

    columnize_list(commandList);

    cout << endl << "Enter all command names as they appear in this list, with the exception of \ncase. "
            "Inputs are not case-sensitive, i.e. \"fira\", \"Fira\", and \"FIRA\" are all \nacceptable." <<
            endl << "--------------------------------------------------------------------------------" << endl;
}

void columnize_list(const vector<string> & list)
{
    for(unsigned int x = 0; x < list.size(); x++)
    {
        cout << list[x];

        if(x % 3 != 2)
        {
            if(list[x].length() < 8)
            {
                cout << "\t\t\t";
            }

            else if(list[x].length() >= 8 && list[x].length() < 16)
            {
                cout << "\t\t";
            }
            else
            {
                cout << "\t";
            }
        }
        else
        {
            cout << endl;
        }

        if(x == list.size() - 1 && x % 3 != 2)
        {
            cout << endl;
        }
    }
}

void melding_calculator(const string & command)
{
    vector <int> formulaHolder;
    int formulaOrder = 1;
    bool results = false;

    cout << "--------------------------------------------------------------------------------"
            "---Formulae involving " << requestedCommand << endl << endl;

    for(int x = 0; x < 296; x++)
    {
        if(lowercaseCommands[commandFormulae[x][0]] == command || lowercaseCommands[commandFormulae[x][1]] == command || lowercaseCommands[commandFormulae[x][3]] == command)
        {
            cout << "<" << formulaOrder << "> ";
            cout << commandNames[commandFormulae[x][0]] << " = " << commandNames[commandFormulae[x][1]] << " + " << commandNames[commandFormulae[x][3]] << endl;
            formulaHolder.push_back(x);
            formulaOrder++;
            results = true;
        }
    }


    if(results)
    {
        unsigned int formulaInfoWanted;
        string input = "";

        cout << "--------------------------------------------------------------------------------" << endl;

        for(;;)
        {
            cout << "Enter a formula's corresponding number to view more information about it or \nenter a new command name:" << endl;
            getline(cin, input);
            make_lowercase(input);
            cout << endl;

            if(input == "list")
            {
                generate_list();
                return;
            }

            if(input == "about")
            {
                program_info();
                return;
            }

            for(int x = 0; x < 160; x++)
            {
                if(lowercaseCommands[x] == input)
                {
                    requestedCommand = commandNames[x];
                    melding_calculator(input);
                    return;
                }
            }

            stringstream sstreamObj(input);
            if (sstreamObj >> formulaInfoWanted)
            {
                if(formulaInfoWanted > 0 && formulaInfoWanted <= formulaHolder.size())
                {
                    more_info(formulaInfoWanted, formulaHolder);
                    cout << endl;
                    melding_calculator(command);
                    return;
                }
                else
                {
                    if(formulaHolder.size() == 1)
                    {
                        cout << "*** Enter \'1\' or a new command name. ***" << endl << endl;
                    }
                    else
                    {
                        cout << "*** Enter a number between 1 and " << formulaHolder.size() << ". ***" << endl << endl;
                    }
                }
            }
            else
            {
                cout << "*** No match found. Retry input or enter \"list\" to view acceptable inputs. ***" << endl << endl;
                return;
            }

        }
    }
    else
    {
        cout << "This command cannot be melded." << endl << "--------------------------------------------------------------------------------" << endl;
    }
}

void make_lowercase(string & command)
{
    for(unsigned int x = 0; x < command.length(); x++)
    {
        command[x] = tolower(command[x]);
    }
}

void more_info(const int & formulaInfoWanted, const vector<int> & formulaHolder)
{
    cout <<"--------------------------------------------------------------------------------"
            "---Formula details" << endl << endl;

    cout << commandNames[commandFormulae[formulaHolder[formulaInfoWanted - 1]][1]] << " + " <<
            commandNames[commandFormulae[formulaHolder[formulaInfoWanted - 1]][3]] << " = " <<
            commandNames[commandFormulae[formulaHolder[formulaInfoWanted - 1]][0]] << endl << endl;

    cout << "Formula success rate: " << commandFormulae[formulaHolder[formulaInfoWanted - 1]][5] << "%";

    for(int x = 0; x < 296; x++)
    {
        if(commandFormulae[x][1] == commandFormulae[formulaHolder[formulaInfoWanted - 1]][1] &&
           commandFormulae[x][3] == commandFormulae[formulaHolder[formulaInfoWanted - 1]][3] &&
           commandFormulae[x][0] != commandFormulae[formulaHolder[formulaInfoWanted - 1]][0] &&
           commandFormulae[x][5] != 100)
        {
            cout << ", " << 100 - commandFormulae[formulaHolder[formulaInfoWanted - 1]][5] << "% chance of creating " <<
                    commandNames[commandFormulae[x][0]];
            break;
        }
    }

    cout << endl;

    cout << "Usable by: ";

    switch(commandFormulae[formulaHolder[formulaInfoWanted - 1]][6])
    {
        case tva:
        {
            cout << "Terra, Ventus, and Aqua" << endl;
            break;
        }
        case tvx:
        {
            cout << "Terra and Ventus" << endl;
            break;
        }
        case txa:
        {
            cout << "Terra and Aqua" << endl;
            break;
        }
        case txx:
        {
            cout << "Terra" << endl;
            break;
        }
        case xva:
        {
            cout << "Ventus and Aqua" << endl;
            break;
        }
        case xvx:
        {
            cout << "Ventus" << endl;
            break;
        }
        case xxa:
        {
            cout << "Aqua" << endl;
            break;
        }
    }

    if(commandFormulae[formulaHolder[formulaInfoWanted - 1]][2] != null)
    {
        cout << "Minimum required level of " << commandNames[commandFormulae[formulaHolder[formulaInfoWanted - 1]][1]] << ": " <<
                commandFormulae[formulaHolder[formulaInfoWanted - 1]][2] << endl;
    }

    if(commandFormulae[formulaHolder[formulaInfoWanted - 1]][4] != null && commandFormulae[formulaHolder[formulaInfoWanted - 1]][1] != commandFormulae[formulaHolder[formulaInfoWanted - 1]][3])
    {
        cout << "Minimum required level of " << commandNames[commandFormulae[formulaHolder[formulaInfoWanted - 1]][3]] << ": " <<
                commandFormulae[formulaHolder[formulaInfoWanted - 1]][4] << endl;
    }

    cout << "Potential abilities:" << endl << endl;

    if(commandFormulae[formulaHolder[formulaInfoWanted - 1]][7] == null)
    {
        cout << "   Not available for shotlock commands." << endl;
    }
    else
    {
        for(int x = 0; x < 7; x++)
        {
            cout << "   " << crystalNames[x] << " -> " << abilityNames[abilityFormulae[commandFormulae[formulaHolder[formulaInfoWanted - 1]][7] - 1][x]] << endl;
        }
    }
}

void program_info()
{
    cout << "--------------------------------------------------------------------------------"
            "-----About this program\n\n---Source" << endl << endl << "All information and statistics were taken from noz3r0's awesome FAQ/Walkthrough" << endl <<
            "http://www.gamefaqs.com/psp/943347-kingdom-hearts-birth-by-sleep/faqs/60901" << endl << endl <<
            "---Legal" << endl << endl << "   Kingdom Hearts: Birth By Sleep and all its components are the property of \nSquare Enix and Disney. "
            "All trademarks and copyrights contained in this program are owned by their respective trademark and copyright holders. " << endl << endl <<
            "---Appreciation" << endl << endl << "   Thanks to noz3r0 for his excellent FAQ, gamefaqs.com for hosting said FAQ, "
            "\nSquare Enix for developing and publishing this fantastic game, Sony for making \nthe great Playstation Portable system, and, of "
            "course, you for having wonderful taste in games." <<
            endl << "--------------------------------------------------------------------------------" << endl;
}