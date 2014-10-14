RSH_LNG = {};

-------------------------------------------------------------------------------
-- English localization (Default)
-------------------------------------------------------------------------------
RSH_LNG = {
	DivineSpirit      = "Divine Spirit",
	Disease           = "Disease",
	DispelMagic       = "Dispel Magic",
	Entangling_Roots  = "Entangling Roots",
	FearWard          = "Fear Ward",
	FlashHeal         = "Flash Heal",
	Fortitude         = "Power Word: Fortitude",
	GiftWild          = "Gift of the Wild",
	GreaterHeal       = "Greater Heal",
	Heal              = "Heal",
	HealingTouch      = "Healing Touch",
	HealingWave       = "Healing Wave",
	Hibernate         = "Hibernate",
	HolyCandle        = "Holy Candle",
	InnerFire         = "Inner Fire",
	LesserHeal        = "Lesser Heal",
	LesserHealingWave = "Lesser Healing Wave",
	Magic             = "Magic",
	MarkWild          = "Mark of the Wild",
	MindControl       = "Mind Control",
	NaturesGrasp      = "Nature's Grasp",
	OmenClarity       = "Omen of Clarity",
	PrayerFortitude   = "Prayer of Fortitude",
	PrayerHealing     = "Prayer of Healing",
	PsychicScream     = "Psychic Scream",
	Rank              = "Rank",
	Regrowth          = "Regrowth",
	Rejuvenation      = "Rejuvenation",
	Renew             = "Renew",
	SacredCandle      = "Sacred Candle",
	ShackleUndead     = "Shackle Undead",
	ShadowProtection  = "Shadow Protection",
	Thorns            = "Thorns",
	TouchWeakness     = "Touch of Weakness",
	WildBerries       = "Wild Berries",
	WildThornRoot     = "Wild Thorn Root",
	WillForsaken      = "Will of the Forsaken",
}

-------------------------------------------------------------------------------
-- German localization
-------------------------------------------------------------------------------
if ( GetLocale() == "deDE" ) then

	RSH_LNG = {
		DivineSpirit      = "G\195\182ttlicher Willen",
		Disease           = "Krankheit",
		DispelMagic       = "",
		Entangling_Roots  = "",
		FearWard          = "",
		Fortitude         = "Machtwort: Seelenst\195\164rke",
		GiftWild          = "",
		FlashHeal         = "Blitzheilung",
		GreaterHeal       = "Gro\195\159e Heilung",
		Heal              = "Heilen",
		HealingTouch      = "",
		HealingWave       = "",
		Hibernate         = "",
		HolyCandle        = "",
		InnerFire         = "",
		LesserHeal        = "Geringes Heilen",
		LesserHealingWave = "",
		Magic             = "Magie",
		MarkWild          = "",
		MindControl       = "",
		NaturesGrasp      = "",
		OmenClarity       = "",
		PrayerFortitude   = "Gebet der Seelenst\195\164rke",
		PrayerHealing     = "Gebet der Heilung",
		PsychicScream     = "",
		Rank              = "Rang",
		Regrowth          = "",
		Rejuvenation      = "",
		Renew             = "Erneuerung",
		SacredCandle      = "",
		Shacle_Undead     = "",
		ShadowProtection  = "Schattenschutz",
		Thorns            = "",
		TouchWeakness     = "",
		WillForsaken      = "",
	}

-------------------------------------------------------------------------------
-- French localization
-------------------------------------------------------------------------------
elseif ( GetLocale() == "frFR" ) then

	RSH_LNG = {
		DivineSpirit      = "Esprit divin",
		Disease           = "Maladie",
		DispelMagic       = "",
		Entangling_Roots  = "",
		FearWard          = "",
		Fortitude         = "Mot de pouvoir : Robustesse",
		GiftWild          = "",
		FlashHeal         = "Soins rapides",
		GreaterHeal       = "Soins sup\195\169rieurs",
		Heal              = "Soins",
		HealingTouch      = "Healing Touch",
		HealingWave       = "",
		Hibernate         = "",
		HolyCandle        = "",
		InnerFire         = "",
		LesserHeal        = "Soins inf\195\169rieurs",
		LesserHealingWave = "",
		Magic             = "Magie",
		MarkWild          = "",
		MindControl       = "",
		NaturesGrasp      = "",
		OmenClarity       = "",
		PrayerFortitude   = "Pri\195\168re de robustesse",
		PrayerHealing     = "Pri\195\168re de soins",
		PsychicScream     = "",
		Rank              = "Rang",
		Regrowth          = "",
		Rejuvenation      = "",
		Renew             = "R\195\169novation",
		SacredCandle      = "",
		Shacle_Undead     = "",
		ShadowProtection  = "Protection contre les t\195\169n\195\168bres",
		Thorns            = "",
		TouchWeakness     = "",
		WillForsaken      = "",
	}
	
end


-------------------------------------------------------------------------------
-- SPELLS ARRAY
--  Format: Speal with rank, Min Lvl, Min Tg Lvl, Max Tg Lvl
-------------------------------------------------------------------------------

RSH_SPELLS = {
    DispelMagic = {
		{ RSH_LNG['DispelMagic'].."("..RSH_LNG['Rank'].." 1)",18,0,999 },
		{ RSH_LNG['DispelMagic'].."("..RSH_LNG['Rank'].." 2)",36,0,999 },
	},
    DivineSpirit = {
		{ RSH_LNG['DivineSpirit'].."("..RSH_LNG['Rank'].." 1)",40,40,999 },
		{ RSH_LNG['DivineSpirit'].."("..RSH_LNG['Rank'].." 2)",42,42,999 },
		{ RSH_LNG['DivineSpirit'].."("..RSH_LNG['Rank'].." 3)",54,54,999 },
	},
	Entangling_Roots = {
		{ RSH_LNG['Entangling_Roots'].."("..RSH_LNG['Rank'].." 1)",8,0,999 },
		{ RSH_LNG['Entangling_Roots'].."("..RSH_LNG['Rank'].." 2)",18,0,999 },
		{ RSH_LNG['Entangling_Roots'].."("..RSH_LNG['Rank'].." 3)",28,0,999 },
		{ RSH_LNG['Entangling_Roots'].."("..RSH_LNG['Rank'].." 4)",38,0,999 },
		{ RSH_LNG['Entangling_Roots'].."("..RSH_LNG['Rank'].." 5)",48,0,999 },
		{ RSH_LNG['Entangling_Roots'].."("..RSH_LNG['Rank'].." 6)",58,0,999 },
	},
	FearWard = {
		{ RSH_LNG['FearWard'],20,0,999 },
	},
    FlashHeal = {
		{ RSH_LNG['FlashHeal'].."("..RSH_LNG['Rank'].." 1)",20,0,999 },
		{ RSH_LNG['FlashHeal'].."("..RSH_LNG['Rank'].." 2)",26,0,999 },
		{ RSH_LNG['FlashHeal'].."("..RSH_LNG['Rank'].." 3)",32,0,999 },
		{ RSH_LNG['FlashHeal'].."("..RSH_LNG['Rank'].." 4)",38,0,999 },
		{ RSH_LNG['FlashHeal'].."("..RSH_LNG['Rank'].." 5)",44,0,999 },
		{ RSH_LNG['FlashHeal'].."("..RSH_LNG['Rank'].." 6)",50,0,999 },
		{ RSH_LNG['FlashHeal'].."("..RSH_LNG['Rank'].." 7)",56,0,999 },
	},
    Fortitude = {
		{ RSH_LNG['Fortitude'].."("..RSH_LNG['Rank'].." 1)",1,1,999 },
		{ RSH_LNG['Fortitude'].."("..RSH_LNG['Rank'].." 2)",12,12,999 },
		{ RSH_LNG['Fortitude'].."("..RSH_LNG['Rank'].." 3)",24,24,999 },
		{ RSH_LNG['Fortitude'].."("..RSH_LNG['Rank'].." 4)",36,36,999 },
		{ RSH_LNG['Fortitude'].."("..RSH_LNG['Rank'].." 5)",48,48,999 },
		{ RSH_LNG['Fortitude'].."("..RSH_LNG['Rank'].." 6)",60,60,999 },
	},
	GiftWild = {
		{ RSH_LNG['GiftWild'].."("..RSH_LNG['Rank'].." 1)",50,50,999, RSH_LNG['WildBerries'] },
		{ RSH_LNG['GiftWild'].."("..RSH_LNG['Rank'].." 2)",60,60,999, RSH_LNG['WildThornRoot'] },
	},
    GreaterHeal = {
		{ RSH_LNG['GreaterHeal'].."("..RSH_LNG['Rank'].." 1)",40,0,999 },
		{ RSH_LNG['GreaterHeal'].."("..RSH_LNG['Rank'].." 2)",46,0,999 },
		{ RSH_LNG['GreaterHeal'].."("..RSH_LNG['Rank'].." 3)",52,0,999 },
		{ RSH_LNG['GreaterHeal'].."("..RSH_LNG['Rank'].." 4)",58,0,999 },
		{ RSH_LNG['GreaterHeal'].."("..RSH_LNG['Rank'].." 5)",58,0,999 },
	},
    Heal = {
		{ RSH_LNG['Heal'].."("..RSH_LNG['Rank'].." 1)",16,0,999 },
		{ RSH_LNG['Heal'].."("..RSH_LNG['Rank'].." 2)",22,0,999 },
		{ RSH_LNG['Heal'].."("..RSH_LNG['Rank'].." 3)",28,0,999 },
		{ RSH_LNG['Heal'].."("..RSH_LNG['Rank'].." 4)",34,0,999 },
	},
	HealingTouch = {
		{ RSH_LNG['HealingTouch'].."("..RSH_LNG['Rank'].." 1)",1,0,999 },
		{ RSH_LNG['HealingTouch'].."("..RSH_LNG['Rank'].." 2)",8,0,999 },
		{ RSH_LNG['HealingTouch'].."("..RSH_LNG['Rank'].." 3)",14,0,999 },
		{ RSH_LNG['HealingTouch'].."("..RSH_LNG['Rank'].." 4)",20,0,999 },
		{ RSH_LNG['HealingTouch'].."("..RSH_LNG['Rank'].." 5)",26,0,999 },
		{ RSH_LNG['HealingTouch'].."("..RSH_LNG['Rank'].." 6)",32,0,999 },
		{ RSH_LNG['HealingTouch'].."("..RSH_LNG['Rank'].." 7)",38,0,999 },
		{ RSH_LNG['HealingTouch'].."("..RSH_LNG['Rank'].." 8)",44,0,999 },
		{ RSH_LNG['HealingTouch'].."("..RSH_LNG['Rank'].." 9)",50,0,999 },
		{ RSH_LNG['HealingTouch'].."("..RSH_LNG['Rank'].." 10)",56,0,999 },
		{ RSH_LNG['HealingTouch'].."("..RSH_LNG['Rank'].." 11)",60,0,999 },
	},
    HealingWave = {
		{ RSH_LNG['HealingWave'].."("..RSH_LNG['Rank'].." 1)",1,0,999 },
		{ RSH_LNG['HealingWave'].."("..RSH_LNG['Rank'].." 2)",6,0,999 },
		{ RSH_LNG['HealingWave'].."("..RSH_LNG['Rank'].." 3)",12,0,999 },
		{ RSH_LNG['HealingWave'].."("..RSH_LNG['Rank'].." 4)",18,0,999 },
		{ RSH_LNG['HealingWave'].."("..RSH_LNG['Rank'].." 5)",24,0,999 },
		{ RSH_LNG['HealingWave'].."("..RSH_LNG['Rank'].." 6)",32,0,999 },
		{ RSH_LNG['HealingWave'].."("..RSH_LNG['Rank'].." 7)",40,0,999 },
		{ RSH_LNG['HealingWave'].."("..RSH_LNG['Rank'].." 8)",48,0,999 },
		{ RSH_LNG['HealingWave'].."("..RSH_LNG['Rank'].." 9)",56,0,999 },
		{ RSH_LNG['HealingWave'].."("..RSH_LNG['Rank'].." 10)",60,0,999 },
	},
	Hibernate = {
		{ RSH_LNG['Hibernate'].."("..RSH_LNG['Rank'].." 1)",18,0,999 },
		{ RSH_LNG['Hibernate'].."("..RSH_LNG['Rank'].." 2)",38,0,999 },
		{ RSH_LNG['Hibernate'].."("..RSH_LNG['Rank'].." 3)",58,0,999 },
	},
	InnerFire = {
		{ RSH_LNG['InnerFire'].."("..RSH_LNG['Rank'].." 1)",12,12,999 },
		{ RSH_LNG['InnerFire'].."("..RSH_LNG['Rank'].." 2)",20,20,999 },
		{ RSH_LNG['InnerFire'].."("..RSH_LNG['Rank'].." 3)",30,30,999 },
		{ RSH_LNG['InnerFire'].."("..RSH_LNG['Rank'].." 4)",40,40,999 },
		{ RSH_LNG['InnerFire'].."("..RSH_LNG['Rank'].." 5)",50,50,999 },
		{ RSH_LNG['InnerFire'].."("..RSH_LNG['Rank'].." 6)",60,60,999 },
	},
    LesserHeal = {
		{ RSH_LNG['LesserHeal'].."("..RSH_LNG['Rank'].." 1)",1,0,999 },
		{ RSH_LNG['LesserHeal'].."("..RSH_LNG['Rank'].." 2)",4,0,999 },
		{ RSH_LNG['LesserHeal'].."("..RSH_LNG['Rank'].." 3)",10,0,999 },
	},
    LesserHealingWave = {
		{ RSH_LNG['LesserHealingWave'].."("..RSH_LNG['Rank'].." 1)",20,0,999 },
		{ RSH_LNG['LesserHealingWave'].."("..RSH_LNG['Rank'].." 2)",28,0,999 },
		{ RSH_LNG['LesserHealingWave'].."("..RSH_LNG['Rank'].." 3)",36,0,999 },
		{ RSH_LNG['LesserHealingWave'].."("..RSH_LNG['Rank'].." 4)",44,0,999 },
		{ RSH_LNG['LesserHealingWave'].."("..RSH_LNG['Rank'].." 5)",52,0,999 },
		{ RSH_LNG['LesserHealingWave'].."("..RSH_LNG['Rank'].." 6)",60,0,999 },
	},
	MarkWild = {
		{ RSH_LNG['MarkWild'].."("..RSH_LNG['Rank'].." 1)",1,1,999 },
		{ RSH_LNG['MarkWild'].."("..RSH_LNG['Rank'].." 2)",10,10,999 },
		{ RSH_LNG['MarkWild'].."("..RSH_LNG['Rank'].." 3)",20,20,999 },
		{ RSH_LNG['MarkWild'].."("..RSH_LNG['Rank'].." 4)",30,30,999 },
		{ RSH_LNG['MarkWild'].."("..RSH_LNG['Rank'].." 5)",40,40,999 },
		{ RSH_LNG['MarkWild'].."("..RSH_LNG['Rank'].." 6)",50,50,999 },
		{ RSH_LNG['MarkWild'].."("..RSH_LNG['Rank'].." 7)",60,60,999 },
	},
    MindControl = {
		{ RSH_LNG['MindControl'].."("..RSH_LNG['Rank'].." 1)",30,0,44 },
		{ RSH_LNG['MindControl'].."("..RSH_LNG['Rank'].." 2)",44,0,60 },
		{ RSH_LNG['MindControl'].."("..RSH_LNG['Rank'].." 3)",60,0,64 },
	},
	NaturesGrasp = {
		{ RSH_LNG['NaturesGrasp'].."("..RSH_LNG['Rank'].." 1)",10,10,999 },
		{ RSH_LNG['NaturesGrasp'].."("..RSH_LNG['Rank'].." 2)",18,18,999 },
		{ RSH_LNG['NaturesGrasp'].."("..RSH_LNG['Rank'].." 3)",28,28,999 },
		{ RSH_LNG['NaturesGrasp'].."("..RSH_LNG['Rank'].." 4)",38,38,999 },
		{ RSH_LNG['NaturesGrasp'].."("..RSH_LNG['Rank'].." 5)",48,48,999 },
		{ RSH_LNG['NaturesGrasp'].."("..RSH_LNG['Rank'].." 6)",58,58,999 },
	},
	OmenClarity = {
		{ RSH_LNG['OmenClarity'],20,20,999 },
	},
    PrayerFortitude = {
		{ RSH_LNG['PrayerFortitude'].."("..RSH_LNG['Rank'].." 1)",48,48,999, RSH_LNG['HolyCandle'] },
		{ RSH_LNG['PrayerFortitude'].."("..RSH_LNG['Rank'].." 2)",60,60,999, RSH_LNG['SacredCandle'] },
	},
    PrayerHealing = {
		{ RSH_LNG['PrayerHealing'].."("..RSH_LNG['Rank'].." 1)",30,0,999 },
		{ RSH_LNG['PrayerHealing'].."("..RSH_LNG['Rank'].." 2)",40,0,999 },
		{ RSH_LNG['PrayerHealing'].."("..RSH_LNG['Rank'].." 3)",50,0,999 },
		{ RSH_LNG['PrayerHealing'].."("..RSH_LNG['Rank'].." 4)",60,0,999 },
		{ RSH_LNG['PrayerHealing'].."("..RSH_LNG['Rank'].." 5)",60,0,999 },
	},
	PsychicScream = {
		{ RSH_LNG['PsychicScream'].."("..RSH_LNG['Rank'].." 1)",14,0,999 },
		{ RSH_LNG['PsychicScream'].."("..RSH_LNG['Rank'].." 2)",28,0,999 },
		{ RSH_LNG['PsychicScream'].."("..RSH_LNG['Rank'].." 3)",42,0,999 },
		{ RSH_LNG['PsychicScream'].."("..RSH_LNG['Rank'].." 4)",56,0,999 },	
	},
	Regrowth = {
		{ RSH_LNG['Regrowth'].."("..RSH_LNG['Rank'].." 1)",12,0,999 },
		{ RSH_LNG['Regrowth'].."("..RSH_LNG['Rank'].." 2)",18,0,999 },
		{ RSH_LNG['Regrowth'].."("..RSH_LNG['Rank'].." 3)",24,0,999 },
		{ RSH_LNG['Regrowth'].."("..RSH_LNG['Rank'].." 4)",30,0,999 },
		{ RSH_LNG['Regrowth'].."("..RSH_LNG['Rank'].." 5)",36,0,999 },
		{ RSH_LNG['Regrowth'].."("..RSH_LNG['Rank'].." 6)",42,0,999 },
		{ RSH_LNG['Regrowth'].."("..RSH_LNG['Rank'].." 7)",48,0,999 },
		{ RSH_LNG['Regrowth'].."("..RSH_LNG['Rank'].." 8)",54,0,999 },
		{ RSH_LNG['Regrowth'].."("..RSH_LNG['Rank'].." 9)",60,0,999 },
	},
    Rejuvenation = {
		{ RSH_LNG['Rejuvenation'].."("..RSH_LNG['Rank'].." 1)",4,0,999 },
		{ RSH_LNG['Rejuvenation'].."("..RSH_LNG['Rank'].." 2)",10,0,999 },
		{ RSH_LNG['Rejuvenation'].."("..RSH_LNG['Rank'].." 3)",16,0,999 },
		{ RSH_LNG['Rejuvenation'].."("..RSH_LNG['Rank'].." 4)",20,0,999 },
		{ RSH_LNG['Rejuvenation'].."("..RSH_LNG['Rank'].." 5)",28,0,999 },
		{ RSH_LNG['Rejuvenation'].."("..RSH_LNG['Rank'].." 6)",34,0,999 },
		{ RSH_LNG['Rejuvenation'].."("..RSH_LNG['Rank'].." 7)",40,0,999 },
		{ RSH_LNG['Rejuvenation'].."("..RSH_LNG['Rank'].." 8)",46,0,999 },
		{ RSH_LNG['Rejuvenation'].."("..RSH_LNG['Rank'].." 9)",52,0,999 },
		{ RSH_LNG['Rejuvenation'].."("..RSH_LNG['Rank'].." 10)",58,0,999 },
		{ RSH_LNG['Rejuvenation'].."("..RSH_LNG['Rank'].." 11)",60,0,999 },
	},
    Renew = {
		{ RSH_LNG['Renew'].."("..RSH_LNG['Rank'].." 1)",8,0,999 },
		{ RSH_LNG['Renew'].."("..RSH_LNG['Rank'].." 2)",14,0,999 },
		{ RSH_LNG['Renew'].."("..RSH_LNG['Rank'].." 3)",20,0,999 },
		{ RSH_LNG['Renew'].."("..RSH_LNG['Rank'].." 4)",26,0,999 },
		{ RSH_LNG['Renew'].."("..RSH_LNG['Rank'].." 5)",32,0,999 },
		{ RSH_LNG['Renew'].."("..RSH_LNG['Rank'].." 6)",38,0,999 },
		{ RSH_LNG['Renew'].."("..RSH_LNG['Rank'].." 7)",44,0,999 },
		{ RSH_LNG['Renew'].."("..RSH_LNG['Rank'].." 8)",50,0,999 },
		{ RSH_LNG['Renew'].."("..RSH_LNG['Rank'].." 9)",56,0,999 },
		{ RSH_LNG['Renew'].."("..RSH_LNG['Rank'].." 10)",60,0,999 },
	},
    ShackleUndead = {
		{ RSH_LNG['ShackleUndead'].."("..RSH_LNG['Rank'].." 1)",20,0,999 },
		{ RSH_LNG['ShackleUndead'].."("..RSH_LNG['Rank'].." 2)",40,0,999 },
		{ RSH_LNG['ShackleUndead'].."("..RSH_LNG['Rank'].." 3)",60,0,999 },
	},
	ShadowProtection = {
		{ RSH_LNG['ShadowProtection'].."("..RSH_LNG['Rank'].." 1)",30,30,999 },
		{ RSH_LNG['ShadowProtection'].."("..RSH_LNG['Rank'].." 2)",42,42,999 },
		{ RSH_LNG['ShadowProtection'].."("..RSH_LNG['Rank'].." 3)",56,56,999 },
	},
	Thorns = {
		{ RSH_LNG['Thorns'].."("..RSH_LNG['Rank'].." 1)",6,6,999 },
		{ RSH_LNG['Thorns'].."("..RSH_LNG['Rank'].." 2)",14,14,999 },
		{ RSH_LNG['Thorns'].."("..RSH_LNG['Rank'].." 3)",24,24,999 },
		{ RSH_LNG['Thorns'].."("..RSH_LNG['Rank'].." 4)",34,34,999 },
		{ RSH_LNG['Thorns'].."("..RSH_LNG['Rank'].." 5)",44,44,999 },
		{ RSH_LNG['Thorns'].."("..RSH_LNG['Rank'].." 6)",54,54,999 },
	},
	TouchWeakness = {
		{ RSH_LNG['TouchWeakness'].."("..RSH_LNG['Rank'].." 1)",10,10,999 },
		{ RSH_LNG['TouchWeakness'].."("..RSH_LNG['Rank'].." 2)",20,20,999 },
		{ RSH_LNG['TouchWeakness'].."("..RSH_LNG['Rank'].." 3)",30,30,999 },
		{ RSH_LNG['TouchWeakness'].."("..RSH_LNG['Rank'].." 4)",40,40,999 },
		{ RSH_LNG['TouchWeakness'].."("..RSH_LNG['Rank'].." 5)",50,50,999 },
		{ RSH_LNG['TouchWeakness'].."("..RSH_LNG['Rank'].." 6)",60,60,999 },
	},
	WillForsaken = {
		{ RSH_LNG['WillForsaken'],0,0,999 },
	}
}

RSH_ATTACK_SPELLS = {
	-- Dispel Magic Array
	DispelMagic = {
	    RSH_SPELLS['DispelMagic'][2],
		RSH_SPELLS['DispelMagic'][1],
	},
	-- Psychic Scream
	PsychicScream = {
		RSH_SPELLS['PsychicScream'][4],
	    RSH_SPELLS['PsychicScream'][3],
	    RSH_SPELLS['PsychicScream'][2],
	    RSH_SPELLS['PsychicScream'][1],
	},
}

RSH_DEBUFF_SPELLS = {
	-- Will of the Forsaken
	WillForsaken = {
	    RSH_SPELLS['WillForsaken'][1],
	},
}

RSH_BUFF_SPELLS = {
	DivineSpirit = {
		RSH_SPELLS['DivineSpirit'][3],
		RSH_SPELLS['DivineSpirit'][2],
		RSH_SPELLS['DivineSpirit'][1],
	},
	FearWard = {
		RSH_SPELLS['FearWard'][1],
	},
	Fortitude = {
		RSH_SPELLS['Fortitude'][6],
		RSH_SPELLS['Fortitude'][5],
		RSH_SPELLS['Fortitude'][4],
		RSH_SPELLS['Fortitude'][3],
		RSH_SPELLS['Fortitude'][2],
		RSH_SPELLS['Fortitude'][1],
	},
	GiftWild = {
		RSH_SPELLS['GiftWild'][2],
		RSH_SPELLS['GiftWild'][1],
	},
	InnerFire = {
		RSH_SPELLS['InnerFire'][6],
		RSH_SPELLS['InnerFire'][5],
		RSH_SPELLS['InnerFire'][4],
		RSH_SPELLS['InnerFire'][3],
		RSH_SPELLS['InnerFire'][2],
		RSH_SPELLS['InnerFire'][1],	
	},
	MarkWild = {
		RSH_SPELLS['MarkWild'][7],
		RSH_SPELLS['MarkWild'][6],
		RSH_SPELLS['MarkWild'][5],
		RSH_SPELLS['MarkWild'][4],
		RSH_SPELLS['MarkWild'][3],
		RSH_SPELLS['MarkWild'][2],
		RSH_SPELLS['MarkWild'][1],
	},
	NaturesGrasp = {
		RSH_SPELLS['NaturesGrasp'][6],
		RSH_SPELLS['NaturesGrasp'][5],
		RSH_SPELLS['NaturesGrasp'][4],
		RSH_SPELLS['NaturesGrasp'][3],
		RSH_SPELLS['NaturesGrasp'][2],
		RSH_SPELLS['NaturesGrasp'][1],
	},
	OmenClarity = {
		RSH_SPELLS['OmenClarity'][1],
	},
	PrayerFortitude = {
		RSH_SPELLS['PrayerFortitude'][2],
		RSH_SPELLS['PrayerFortitude'][1],
		RSH_SPELLS['Fortitude'][6],
		RSH_SPELLS['Fortitude'][5],
		RSH_SPELLS['Fortitude'][4],
		RSH_SPELLS['Fortitude'][3],
		RSH_SPELLS['Fortitude'][2],
		RSH_SPELLS['Fortitude'][1],
	},
	ShadowProtection = {
		RSH_SPELLS['ShadowProtection'][3],
		RSH_SPELLS['ShadowProtection'][2],
		RSH_SPELLS['ShadowProtection'][1],	
	},
	Thorns = {
		RSH_SPELLS['Thorns'][6],
		RSH_SPELLS['Thorns'][5],
		RSH_SPELLS['Thorns'][4],
		RSH_SPELLS['Thorns'][3],
		RSH_SPELLS['Thorns'][2],
		RSH_SPELLS['Thorns'][1],
	},
	TouchWeakness = {
		RSH_SPELLS['TouchWeakness'][6],
		RSH_SPELLS['TouchWeakness'][5],
		RSH_SPELLS['TouchWeakness'][4],
		RSH_SPELLS['TouchWeakness'][3],
		RSH_SPELLS['TouchWeakness'][2],
		RSH_SPELLS['TouchWeakness'][1],	
	},
}

RSH_CC_SPELLS = {
	Druid = {
		Entangling_Roots = {
			RSH_SPELLS['Entangling_Roots'][6],
			RSH_SPELLS['Entangling_Roots'][5],
			RSH_SPELLS['Entangling_Roots'][4],
			RSH_SPELLS['Entangling_Roots'][3],
			RSH_SPELLS['Entangling_Roots'][2],
			RSH_SPELLS['Entangling_Roots'][1],
		},
		Beast = {
			RSH_SPELLS['Hibernate'][3],
			RSH_SPELLS['Hibernate'][2],
			RSH_SPELLS['Hibernate'][1],
		},
		Dragonkin = {
			RSH_SPELLS['Hibernate'][3],
			RSH_SPELLS['Hibernate'][2],
			RSH_SPELLS['Hibernate'][1],
		},
	},
	Priest = {
		-- Mind Control Array
		Humanoid = {
		    RSH_SPELLS['MindControl'][3],
		    RSH_SPELLS['MindControl'][2],
		    RSH_SPELLS['MindControl'][1],
		},
		-- Shackle Undead Array
		Undead = {
		    RSH_SPELLS['ShackleUndead'][3],
		    RSH_SPELLS['ShackleUndead'][2],
		    RSH_SPELLS['ShackleUndead'][1],
		},
	},
}

RSH_HEAL_SPELLS = {
	Druid = {
		Max_Heal = {
			RSH_SPELLS['HealingTouch'][11],
			RSH_SPELLS['HealingTouch'][10],
			RSH_SPELLS['HealingTouch'][9],
			RSH_SPELLS['HealingTouch'][8],
			RSH_SPELLS['HealingTouch'][7],
			RSH_SPELLS['HealingTouch'][6],
			RSH_SPELLS['HealingTouch'][5],
			RSH_SPELLS['HealingTouch'][4],
			RSH_SPELLS['HealingTouch'][3],
			RSH_SPELLS['HealingTouch'][2],
			RSH_SPELLS['HealingTouch'][1],
			RSH_SPELLS['Regrowth'][9],
			RSH_SPELLS['Regrowth'][8],
			RSH_SPELLS['Regrowth'][7],
			RSH_SPELLS['Regrowth'][6],
			RSH_SPELLS['Regrowth'][5],
			RSH_SPELLS['Regrowth'][4],
			RSH_SPELLS['Regrowth'][3],
			RSH_SPELLS['Regrowth'][2],
			RSH_SPELLS['Regrowth'][1],
		},
		Quick_Heal = {
			RSH_SPELLS['Regrowth'][9],
			RSH_SPELLS['Regrowth'][8],
			RSH_SPELLS['Regrowth'][7],
			RSH_SPELLS['Regrowth'][6],
			RSH_SPELLS['Regrowth'][5],
			RSH_SPELLS['Regrowth'][4],
			RSH_SPELLS['Regrowth'][3],
			RSH_SPELLS['Regrowth'][2],
			RSH_SPELLS['Regrowth'][1],
			RSH_SPELLS['HealingTouch'][11],
			RSH_SPELLS['HealingTouch'][10],
			RSH_SPELLS['HealingTouch'][9],
			RSH_SPELLS['HealingTouch'][8],
			RSH_SPELLS['HealingTouch'][7],
			RSH_SPELLS['HealingTouch'][6],
			RSH_SPELLS['HealingTouch'][5],
			RSH_SPELLS['HealingTouch'][4],
			RSH_SPELLS['HealingTouch'][3],
			RSH_SPELLS['HealingTouch'][2],
			RSH_SPELLS['HealingTouch'][1],			
		},
		Renew = {
			RSH_SPELLS['Rejuvenation'][11],
			RSH_SPELLS['Rejuvenation'][10],
			RSH_SPELLS['Rejuvenation'][9],
			RSH_SPELLS['Rejuvenation'][8],
			RSH_SPELLS['Rejuvenation'][7],
			RSH_SPELLS['Rejuvenation'][6],
			RSH_SPELLS['Rejuvenation'][5],
			RSH_SPELLS['Rejuvenation'][4],
			RSH_SPELLS['Rejuvenation'][3],
			RSH_SPELLS['Rejuvenation'][2],
			RSH_SPELLS['Rejuvenation'][1],
		},
	},
	Priest = {
		Max_Heal = {
			RSH_SPELLS['GreaterHeal'][5],
			RSH_SPELLS['GreaterHeal'][4],
		    RSH_SPELLS['GreaterHeal'][3],
		    RSH_SPELLS['GreaterHeal'][2],
		    RSH_SPELLS['GreaterHeal'][1],
			RSH_SPELLS['Heal'][4],
		    RSH_SPELLS['Heal'][3],
		    RSH_SPELLS['Heal'][2],
			RSH_SPELLS['Heal'][1],
			RSH_SPELLS['FlashHeal'][7],
			RSH_SPELLS['FlashHeal'][6],
			RSH_SPELLS['FlashHeal'][5],
		    RSH_SPELLS['FlashHeal'][4],
		    RSH_SPELLS['FlashHeal'][3],
		    RSH_SPELLS['FlashHeal'][2],
		    RSH_SPELLS['FlashHeal'][1],
		    RSH_SPELLS['LesserHeal'][3],
		    RSH_SPELLS['LesserHeal'][2],
		    RSH_SPELLS['LesserHeal'][1],
		},
		Party_Heal = {
			RSH_SPELLS['PrayerHealing'][5],
			RSH_SPELLS['PrayerHealing'][4],
			RSH_SPELLS['PrayerHealing'][3],
			RSH_SPELLS['PrayerHealing'][2],
			RSH_SPELLS['PrayerHealing'][1],
		},
		Quick_Heal = {
		    RSH_SPELLS['FlashHeal'][7],
		    RSH_SPELLS['FlashHeal'][6],
		    RSH_SPELLS['FlashHeal'][5],
		    RSH_SPELLS['FlashHeal'][4],
		    RSH_SPELLS['FlashHeal'][3],
		    RSH_SPELLS['FlashHeal'][2],
		    RSH_SPELLS['FlashHeal'][1],
		    RSH_SPELLS['LesserHeal'][3],
		    RSH_SPELLS['LesserHeal'][2],
		    RSH_SPELLS['LesserHeal'][1],
		},
		Renew = {
			RSH_SPELLS['Renew'][10],
			RSH_SPELLS['Renew'][9],
			RSH_SPELLS['Renew'][8],
			RSH_SPELLS['Renew'][7],
			RSH_SPELLS['Renew'][6],
			RSH_SPELLS['Renew'][5],
			RSH_SPELLS['Renew'][4],
			RSH_SPELLS['Renew'][3],
			RSH_SPELLS['Renew'][2],
			RSH_SPELLS['Renew'][1],
		},
	},
	Shaman = {
		Quick_Heal = {
		    RSH_SPELLS['LesserHealingWave'][6],
			RSH_SPELLS['LesserHealingWave'][5],
			RSH_SPELLS['LesserHealingWave'][4],
			RSH_SPELLS['LesserHealingWave'][3],
			RSH_SPELLS['LesserHealingWave'][2],
			RSH_SPELLS['LesserHealingWave'][1],
			RSH_SPELLS['HealingWave'][10],
			RSH_SPELLS['HealingWave'][9],
			RSH_SPELLS['HealingWave'][8],
			RSH_SPELLS['HealingWave'][7],
			RSH_SPELLS['HealingWave'][6],
			RSH_SPELLS['HealingWave'][5],
			RSH_SPELLS['HealingWave'][4],
			RSH_SPELLS['HealingWave'][3],
			RSH_SPELLS['HealingWave'][2],
			RSH_SPELLS['HealingWave'][1],
		},
		Max_Heal = {
			RSH_SPELLS['HealingWave'][10],
			RSH_SPELLS['HealingWave'][9],
			RSH_SPELLS['HealingWave'][8],
			RSH_SPELLS['HealingWave'][7],
			RSH_SPELLS['HealingWave'][6],
			RSH_SPELLS['HealingWave'][5],
			RSH_SPELLS['HealingWave'][4],
			RSH_SPELLS['HealingWave'][3],
			RSH_SPELLS['HealingWave'][2],
			RSH_SPELLS['HealingWave'][1],
		    RSH_SPELLS['LesserHealingWave'][6],
			RSH_SPELLS['LesserHealingWave'][5],
			RSH_SPELLS['LesserHealingWave'][4],
			RSH_SPELLS['LesserHealingWave'][3],
			RSH_SPELLS['LesserHealingWave'][2],
			RSH_SPELLS['LesserHealingWave'][1],
		},	
	},
}