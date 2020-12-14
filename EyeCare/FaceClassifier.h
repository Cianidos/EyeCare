#pragma once
#include "Classifier.h"
#include <string>

class FaceClassifier :
    public Classifier<>
{
public:
    FaceClassifier(const std::string& path =
	    R"(.\haarcascade_frontalface_alt.xml)")
        : Classifier(path) {}
};

