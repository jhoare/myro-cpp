#include "Filter.h"

Filter::Filter(){
}

Filter::~Filter() {
}

void Filter::applyFilter(Picture * image) {
	this->filter(image);
}

void Filter::filter(Picture* image) {
	return;
}
