#ifndef _S2LOADER_TEXTBOX_LOADER_H_
#define _S2LOADER_TEXTBOX_LOADER_H_

#include <cu/uncopyable.h>

#include <json/json.h>

namespace pt2 { class Textbox; }
namespace simp { class NodeLabel; }

namespace s2loader
{

class TextboxLoader : private cu::Uncopyable
{
public:
	TextboxLoader(pt2::Textbox& tb);

	void LoadJson(const Json::Value& val);
	void LoadBin(const simp::NodeLabel* node);

private:
	pt2::Textbox& m_tb;

}; // TextboxLoader

}

#endif // _S2LOADER_TEXTBOX_LOADER_H_
