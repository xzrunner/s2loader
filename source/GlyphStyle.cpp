#include "s2loader/GlyphStyle.h"

#include <gtxt_glyph.h>

namespace
{

void CopyColor(pt2::GradientColor& dst, const gtxt_glyph_color& src)
{
	switch (src.mode_type)
	{
	case 0:
		{
			dst.items.resize(1);
			dst.items[0].col.FromRGBA(src.mode.ONE.color.integer);
		}
		break;
	case 1:
		{
			dst.items.resize(2);
			dst.items[0].col.FromRGBA(src.mode.TWO.begin_col.integer);
			dst.items[1].col.FromRGBA(src.mode.TWO.end_col.integer);
			dst.items[0].pos = src.mode.TWO.begin_pos;
			dst.items[1].pos = src.mode.TWO.end_pos;
			dst.angle = src.mode.TWO.angle;
		}
		break;
	case 2:
		{
			dst.items.resize(3);
			dst.items[0].col.FromRGBA(src.mode.THREE.begin_col.integer);
			dst.items[1].col.FromRGBA(src.mode.THREE.mid_col.integer);
			dst.items[2].col.FromRGBA(src.mode.THREE.end_col.integer);
			dst.items[0].pos = src.mode.THREE.begin_pos;
			dst.items[1].pos = src.mode.THREE.mid_pos;
			dst.items[2].pos = src.mode.THREE.end_pos;
			dst.angle = src.mode.THREE.angle;
		}
		break;
	}
}

}

namespace s2loader
{

GlyphStyle::GlyphStyle()
	: font(-1)
	, font_size(-1)
	, edge(-1)
	, edge_size(-1)
{
}

GlyphStyle::GlyphStyle(const gtxt_glyph_style* gs)
	: font(gs->font)
	, font_size(gs->font_size)
	, edge(gs->edge)
	, edge_size(static_cast<int>(gs->edge_size))
{
	CopyColor(font_color, gs->font_color);
	CopyColor(edge_color, gs->edge_color);
}

bool GlyphStyle::operator == (const GlyphStyle& style) const
{
	return font       == style.font 
		&& font_size  == style.font_size
		&& font_color == style.font_color
		&& edge       == style.edge
		&& edge_size  == style.edge_size
		&& edge_color == style.edge_color;
}

}