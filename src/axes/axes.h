//
// Created by tbatt on 19/04/2020.
//

#ifndef OPENGLPLOTLIVE_PROJ_AXES_H
#define OPENGLPLOTLIVE_PROJ_AXES_H

// Project Includes
#include "../texts/textString.h"
#include "../rendering/ConstantScaleDrawable.h"
#include "AxesArea.h"


namespace GLPL {
    class Axes : public ConstantScaleDrawable {
    public:
        // Constructor
        Axes(float x, float y, float width, float height, std::shared_ptr<ParentDimensions> parentDimensions);

        // Functions
        void createAxesArea();
        // Text
        void addText(const char* textString, float x, float y, float fontSize);
        std::shared_ptr<TextString> getText(unsigned int textStringId);
        void removeTextString(unsigned int textStringId);
        // Line
        void addLine(std::vector<float>* dataPtX, std::vector<float>* dataPtY);

        void Draw();

    private:
        // Data
        // Axes Area
        std::shared_ptr<AxesArea> axesArea;
        // Text String
        unsigned int textStringCount = 0;
        std::unordered_map<unsigned int, std::shared_ptr<TextString>> textStringMap;
    };
}


#endif //OPENGLPLOTLIVE_PROJ_AXES_H
