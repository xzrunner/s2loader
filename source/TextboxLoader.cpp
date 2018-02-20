#include "s2loader/TextboxLoader.h"

#include <painting2/Textbox.h>
#include <simp/NodeLabel.h>
#include <bs/FixedPointNum.h>
#include <gum/trans_color.h>

#include <fstream>

namespace s2loader
{

TextboxLoader::TextboxLoader(pt2::Textbox& m_tb)
	: m_tb(m_tb)
{
}

void TextboxLoader::LoadJson(const Json::Value& val)
{
	m_tb.width				= val["width"].asInt();
	m_tb.height				= val["height"].asInt();

	m_tb.font_type			= val["font"].asInt();
	m_tb.font_size			= val["font_size"].asInt();
	m_tb.font_color			= gum::str2color(val["font_color"].asString().c_str(), s2s::RGBA);

	m_tb.has_edge			= val["edge"].asBool();
	m_tb.edge_size			= static_cast<float>(val["edge_size"].asDouble());
	m_tb.edge_color			= gum::str2color(val["edge_color"].asString().c_str(), s2s::RGBA);

	m_tb.space_hori			= static_cast<float>(val["space_hori"].asDouble());
	m_tb.space_vert			= static_cast<float>(val["space_vert"].asDouble());

	m_tb.align_hori			= (pt2::Textbox::HoriAlign)(val["align_hori"].asInt());
	m_tb.align_vert			= (pt2::Textbox::VertAlign)(val["align_vert"].asInt());

	m_tb.overflow			= true;
	if (val.isMember("overflow")) {
		m_tb.overflow		= val["overflow"].asBool();
	}

	m_tb.richtext			= true;
	if (val.isMember("richtext")) {
		m_tb.richtext		= val["richtext"].asBool();
	}
}

void TextboxLoader::LoadBin(const simp::NodeLabel* node)
{
	m_tb.width      = node->width;
	m_tb.height     = node->height;

	m_tb.font_type  = node->font;
	m_tb.font_size  = node->font_size;
	m_tb.font_color.FromRGBA(node->font_color);

	m_tb.has_edge   = bs::int2bool(node->edge);
	m_tb.edge_size  = node->edge_size;
	m_tb.edge_color.FromRGBA(node->edge_color);

	m_tb.align_hori = pt2::Textbox::HoriAlign(node->align_hori);
	m_tb.align_vert	= pt2::Textbox::VertAlign(node->align_vert);

	m_tb.space_hori = node->space_hori;
	m_tb.space_vert = node->space_vert;

	m_tb.richtext   = bs::int2bool(node->richtext);
	m_tb.overflow   = bs::int2bool(node->overflow);
}

}