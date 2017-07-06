#include <gds/geom.hpp>
#include "gds/libgds.h"

namespace btos_api{
namespace gds{

	std::string Font::GetName(){
		return Info().name;
	}

	gds_FontStyle::Enum Font::GetStyle(){
		return static_cast<gds_FontStyle::Enum>(Info().fontStyle);
	}

	gds_FontInfo Font::Info(){
		return GDS_GetFontInfo(id);
	}

}
}
