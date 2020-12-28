/*
 * window.h
 *
 *  Created on: 29Mar.,2017
 *      Author: bcub3d-desktop
 */

#ifndef P_WINDOW_H_
#define P_WINDOW_H_

// GLAD - Multi Language GL Loader-Generator
#include <glad/glad.h>

// GLFW (Multi-platform library for OpenGL)
#include <GLFW/glfw3.h>

// Standard Includes
#include <iostream>
#include <array>

// Project Includes
#include "IWindow.h"
#include "../rendering/IDrawable.h"
#include "../plot/plot.h"
#include "../rendering/TopLevelDrawable.h"


namespace GLPL {
	// Define Fonts
	#ifdef _WIN32
		#define FONTPATH "C:/Windows/Fonts/Arial.ttf"
	#elif __linux__
		#define FONTPATH "/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf"
	#endif

	class Window : public IWindow, TopLevelDrawable {
	public:
	    // Constructor
        Window(int windowWidth, int windowHeight, bool transparentBackground = GLFW_FALSE, bool focusOnShow = GLFW_FALSE);
        ~Window();
	    // Functions
	    void setKeysByIndex(int index, bool boolean);
	    void setToggleKeysByIndex(int index, bool boolean);
	    bool getToggleKeyStateByIndex(int index);
	    GLFWwindow* getWindow();
	    void preLoopDraw(bool clearBuffer);
	    void postLoopDraw();
	    void setFrameless(bool framelessOn);
	    void setAlwaysOnTop(bool alwaysOnTop);
	    void setBackgroundColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	    std::shared_ptr<ShaderSet> getShaderSet();
	    std::shared_ptr<ParentDimensions> getParentDimensions();
	    void updateStoredSize(int newWidth, int newHeight);
        void handleMouseMovement(double xpos, double ypos);
        void handleMouseRelease();
        void handleMouseScroll(double xoffset, double yoffset);
        void updateSelection();
        void handleRightMouseHeld(bool buttonHeld);
	    void updateSizePx();
	    void Draw();
        std::string getID();

	    void addPlot(const std::shared_ptr<IDrawable>& plotPt);

	private:
	    // Functions
        void initGLFW();
        void updateStoredSize();
        void initGLAD();

	    // Data
	    // Base Window
        GLFWwindow* window;
	    std::array<GLfloat, 4> backgroundColor = {0.0f, 0.0f, 0.0f, 1.0f};
	    bool transparentBackground;
	    bool focusOnShow;
	    glm::mat4 transform = glm::mat4(1.0f);
	    std::shared_ptr<ShaderSet> shaderSetPt;

	    // Selection
	    std::shared_ptr<std::vector<std::shared_ptr<GLPL::IDrawable>>> mousedOverObjs = std::make_shared<std::vector<std::shared_ptr<GLPL::IDrawable>>>();;
        std::shared_ptr<std::vector<std::shared_ptr<GLPL::IDrawable>>> hoverableObjs = std::make_shared<std::vector<std::shared_ptr<GLPL::IDrawable>>>();;
        std::shared_ptr<GLPL::IDrawable> selected = {};

        // Cursor
        int lastCursorType = 0;
        GLFWcursor* lastCursor = NULL;

        // Keys
        bool keys[1024];
        bool toggleKeys[1024];
	};

}


#endif /* P_WINDOW_H_ */
