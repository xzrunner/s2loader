#include "s2loader/GlyphStyleID.h"

#include <boost/functional/hash.hpp>

namespace s2loader
{

CU_SINGLETON_DEFINITION(GlyphStyleID);

GlyphStyleID::GlyphStyleID()
	: m_next_id(0)
{
}

int GlyphStyleID::Gen(const GlyphStyle& style)
{
 	if (style == m_last.first) {
 		return m_last.second;
 	}

	int hash = Hash(style) % HASH_CAP;
	auto& list = m_hash[hash];
	for (int i = 0, n = list.size(); i < n; ++i) {
		if (list[i].first == style) {
			m_last = list[i];
			return list[i].second;
		}
	}

	int id = m_next_id++;

	list.push_back(std::make_pair(style, id));

	m_last.first = style;
	m_last.second = id;

	return id;
}

size_t GlyphStyleID::Hash(const GlyphStyle& gs)
{
	size_t hash = 0;
	boost::hash_combine(hash, gs.font);
	boost::hash_combine(hash, gs.font_size);
	boost::hash_combine(hash, gs.font);
	HashColor(hash, gs.font_color);
	boost::hash_combine(hash, gs.edge);
	if (gs.edge)
	{
		boost::hash_combine(hash, gs.edge_size);
		HashColor(hash, gs.edge_color);
	}
	return hash;
}

void GlyphStyleID::HashColor(size_t& seed, const pt2::GradientColor& color)
{
	if (color.items.empty()) {
		return;
	}
	if (color.items.size() == 1) 
	{
		boost::hash_combine(seed, color.items[0].col.ToRGBA());
	}
	else
	{
		boost::hash_combine(seed, color.angle);
		boost::hash_combine(seed, color.items.size());
		for (auto& item : color.items) {
			boost::hash_combine(seed, item.col.ToRGBA());
			boost::hash_combine(seed, item.pos);
		}
	}
}

}