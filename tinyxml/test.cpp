#include "tinyxml.h"

int main(int argc, char *argv[]) {
    	TiXmlDocument doc("test.xml");
	bool loadOkay = doc.LoadFile();
}
