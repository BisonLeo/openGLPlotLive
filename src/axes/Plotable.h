//
// Created by tbatt on 24/06/2020.
//

#ifndef OPENGLPLOTLIVE_PROJ_PLOTABLE_H
#define OPENGLPLOTLIVE_PROJ_PLOTABLE_H

// Standard Includes
#include <numeric>

// Project Includes
#include "../rendering/ConstantXYDrawable.h"


namespace GLPL {
    class Plotable : public ConstantXYDrawable {
    public:
        // Constructor
        Plotable(std::shared_ptr<ParentDimensions> parentDimensions);

        // Functions
        virtual std::vector<float> getMinMax(bool onlyPositiveX = false, bool onlyPositiveY = false) = 0;
        void setAxesViewportTransform(std::shared_ptr<glm::mat4> newAxesViewportTransform);
        void setPlotableId(int newPlotableId);

        std::pair<std::vector<unsigned int>, std::vector<unsigned int>> genIndicesSortedVector(std::vector<float>* unsortedVector);
        std::vector<float> sortVectorByIndices(std::vector<float>* unsortedVector, std::vector<unsigned int> indices);

        virtual std::tuple<float, float> getClosestPoint(float xVal) = 0;
        virtual std::tuple<float, float> getClosestPoint(float xVal, float xmin, float xmax, float ymin, float ymax) = 0;

        virtual void drawLegendEntry(glm::mat4 rectOverallTransform) = 0;

        void setLogModes(bool newLogX, bool newLogY);
        void setLogXBase(unsigned int newLogXBase);
        void setLogYBase(unsigned int newLogYBase);

        void setLabel(std::string newLabel);
        std::string getLabel();

    protected:
        std::shared_ptr<glm::mat4> axesViewportTransform = std::make_shared<glm::mat4>(glm::mat4(1.0f));
        std::string label = "";
        int plotableId = -1;
        bool logX = false;
        bool logY = false;
        unsigned int logXBase = 10;
        unsigned int logYBase = 10;

    };
}


#endif //OPENGLPLOTLIVE_PROJ_PLOTABLE_H
