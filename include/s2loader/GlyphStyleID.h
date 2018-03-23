#ifndef _S2LOADER_GLYPH_STYLE_ID_H_
#define _S2LOADER_GLYPH_STYLE_ID_H_

#include "s2loader/GlyphStyle.h"

#include <cu/cu_macro.h>
#include <cu/cu_stl.h>

namespace s2loader
{

class GlyphStyle;

class GlyphStyleID
{
public:
	int Gen(const GlyphStyle& style);

private:
	static size_t Hash(const GlyphStyle& style);
	static void HashColor(size_t& seed, const pt2::GradientColor& color);

private:
	static const int HASH_CAP = 197;

private:
	int m_next_id;
	CU_VEC<std::pair<GlyphStyle, int> > m_hash[HASH_CAP];

 	std::pair<GlyphStyle, int> m_last;
	
	CU_SINGLETON_DECLARATION(GlyphStyleID)

}; // GlyphStyleID

}

#endif // _S2LOADER_GLYPH_STYLE_ID_H_
