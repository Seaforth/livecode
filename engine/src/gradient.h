/* Copyright (C) 2003-2013 Runtime Revolution Ltd.

This file is part of LiveCode.

LiveCode is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License v3 as published by the Free
Software Foundation.

LiveCode is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with LiveCode.  If not see <http://www.gnu.org/licenses/>.  */

#ifndef __MC_GRADIENT__
#define __MC_GRADIENT__

enum MCGradientFillKind
{
	kMCGradientKindNone,
	kMCGradientKindLinear = 3,
	kMCGradientKindRadial,
	kMCGradientKindConical,
	kMCGradientKindDiamond,
	kMCGradientKindSpiral,
	kMCGradientKindXY,
	kMCGradientKindSqrtXY
};

enum MCGradientFillQuality
{
	kMCGradientQualityNormal,
	kMCGradientQualityGood
};

enum MCGradientFillProperty
{
	P_GRADIENT_FILL_TYPE,
	P_GRADIENT_FILL_RAMP,
	P_GRADIENT_FILL_ORIGIN,
	P_GRADIENT_FILL_PRIMARY_POINT,
	P_GRADIENT_FILL_SECONDARY_POINT,
	P_GRADIENT_FILL_QUALITY,
	P_GRADIENT_FILL_MIRROR,
	P_GRADIENT_FILL_REPEAT,
	P_GRADIENT_FILL_WRAP,
};

struct MCGradientFillStop
{
	uint4 offset;
	uint4 color;
	uint4 hw_color;
	uint4 difference;
};

struct MCGradientFill
{
	unsigned kind : 4;
	unsigned quality : 2;
	unsigned mirror : 1;
	unsigned wrap : 1;
	uint1 repeat;
	uint1 ramp_length;
	MCPoint origin;
	MCPoint primary;
	MCPoint secondary;
	MCPoint old_origin;
	MCPoint old_primary;
	MCPoint old_secondary;
	MCRectangle old_rect;
	MCGradientFillStop *ramp;
};

#define GRADIENT_HEADER_SIZE (1 + 1 + 1 + 3 * sizeof(MCPoint))

class MCString;
class MCExecPoint;
struct MCGradientCombiner;

void MCGradientFillInit(MCGradientFill *&r_gradient, MCRectangle p_rect);
void MCGradientFillFree(MCGradientFill *gradient);
MCGradientFill *MCGradientFillCopy(const MCGradientFill *p_gradient);

Exec_stat MCGradientFillGetProperty(MCGradientFill* p_gradient, MCExecPoint &ep, MCNameRef prop);
Exec_stat MCGradientFillSetProperty(MCGradientFill* &p_gradient, MCExecPoint &ep, MCNameRef prop, Boolean &dirty, MCRectangle rect);

Boolean MCGradientFillRampParse(MCGradientFillStop* &r_stops, uint1 &r_stop_count, const MCString &r_data);
void MCGradientFillRampUnparse(MCGradientFillStop* p_stops, uint1 p_stop_count, MCExecPoint &p_ep);

MCGradientCombiner *MCGradientFillCreateCombiner(MCGradientFill *p_gradient, MCRectangle &p_clip);
uint1 *MCGradientFillSerialize(MCGradientFill *p_gradient, uint4 &r_length);
void MCGradientFillUnserialize(MCGradientFill *p_gradient, uint1 *p_data, uint4 &r_length);

IO_stat MCGradientFillSerialize(MCGradientFill *p_gradient, MCObjectOutputStream& p_stream);
IO_stat MCGradientFillUnserialize(MCGradientFill *p_gradient, MCObjectInputStream& p_stream);
uint4 MCGradientFillMeasure(MCGradientFill *p_gradient);

#endif
