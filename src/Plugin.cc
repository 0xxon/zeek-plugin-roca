// See the file "COPYING" in the main distribution directory for copyright.

#include "Plugin.h"

extern "C" {
	void init_roca();
}

namespace plugin { namespace Johanna_ROCA { Plugin plugin; } }

using namespace plugin::Johanna_ROCA;

plugin::Configuration Plugin::Configure()
	{
	plugin::Configuration config;
	config.name = "Johanna::ROCA";
	config.description = "ROCA: Vulnerable RSA generation (CVE-2017-15361) key tester";
	config.version.major = 0;
	config.version.minor = 1;
	return config;
	}

void Plugin::InitPreScript()
	{
	init_roca();
	::plugin::Plugin::InitPreScript();
	}
