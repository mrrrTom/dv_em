#include "configuration.hpp"

configuration::configuration(const char *path) {
	rapidxml::file<> xmlFile(path);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

}
