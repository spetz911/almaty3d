//
// Created by Oleg Baskakov on 4/20/15.
//

#ifndef OGL_ENGINE_HPP
#define OGL_ENGINE_HPP


#include "png.hpp"
#include <glm/gtc/matrix_transform.hpp>


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
#include <glm/gtc/round.hpp>
#include <glm/gtx/color_space.hpp>
#include <glm/gtx/integer.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

#include <gli/gli.hpp>


#include <memory>
#include <array>




inline std::string vendor()
{
    std::string ss(reinterpret_cast<char const *>(glGetString(GL_VENDOR)));

#		ifdef __APPLE__
    std::string os("apple-");
#		elif __linux__
		std::string os("linux-");
#		else
    std::string os;
#		endif

    if(ss.find("NVIDIA") != std::string::npos)
        return os + "nvidia/";
    else if(ss.find("ATI") != std::string::npos || ss.find("AMD") != std::string::npos)
        return os + "amd/";
    else if(ss.find("Intel") != std::string::npos)
        return os + "intel/";
    else
        return os + "unknown/";
}


inline std::string
getDataDirectory()
{
    return std::string(OGL_SAMPLES_SOURCE_DIR) + "/data/";
}

inline std::string getBinaryDirectory()
{
    return std::string(OGL_SAMPLES_BINARY_DIR) + "/";
}


class Engine
{

public:
    int init();


public:
    enum Vendor
    {
        DEFAULT,
        AMD,
        INTEL,
        NVIDIA,
        VENDOR_MAX
    };

    enum Profile
    {
        CORE = GLFW_OPENGL_CORE_PROFILE,
        COMPATIBILITY = GLFW_OPENGL_COMPAT_PROFILE,
        ES = 0x0004
    };

    enum SyncMode
    {
        VSYNC,
        ASYNC,
        TEARING
    };

    enum Success
    {
        RUN_ONLY,
        GENERATE_ERROR,
        MATCH_TEMPLATE
    };

protected:

    Engine(
            int argc, char* argv[], char const * Title,
            Profile profile, int Major, int Minor,
            glm::uvec2 const & WindowSize = glm::uvec2(640, 480),
            glm::vec2 const & Orientation = glm::vec2(0, 0),
            glm::vec2 const & Position = glm::vec2(0, 4),
            std::size_t FrameCount = 2,
            Success success = MATCH_TEMPLATE,
            bool sRGB = false);
    Engine(
            int argc, char* argv[], char const * Title,
            Profile profile, int Major, int Minor,
            bool sRGB);

    virtual ~Engine();

    glm::uvec2
    getWindowSize() const
    {
        glm::ivec2 WindowSize(0);
        glfwGetFramebufferSize(this->window, &WindowSize.x, &WindowSize.y);
        return glm::uvec2(WindowSize);
    }

    bool
    isExtensionSupported(char const * String)
    {
        GLint ExtensionCount(0);
        glGetIntegerv(GL_NUM_EXTENSIONS, &ExtensionCount);
        for(GLint i = 0; i < ExtensionCount; ++i)
            if(std::string((char const*)glGetStringi(GL_EXTENSIONS, i)) == std::string(String))
                return true;
        //printf("Failed to find Extension: \"%s\"\n",String);
        return false;
    }



private:
    int version(int Major, int Minor) const{return Major * 100 + Minor * 10;}
    bool checkGLVersion(GLint MajorVersionRequire, GLint MinorVersionRequire) const;

    static void cursorPositionCallback(GLFWwindow* Window, double x, double y);
    static void mouseButtonCallback(GLFWwindow*window, int button, int action, int mods);
    static void keyCallback(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);

public:
    static void APIENTRY debugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam);

protected:
    GLFWwindow *window;

private:
    Success const success;
    std::string const title;
    Profile const profile;
    int const Major;
    int const Minor;
    GLuint TimerQueryName;
    std::size_t const FrameCount;
    glm::vec2 mouseOrigin;
    glm::vec2 mouseCurrent;
    glm::vec2 tranlationOrigin;
    glm::vec2 tranlationCurrent;
    glm::vec2 rotationOrigin;
    glm::vec2 rotationCurrent;
    int mouseButtonFlags;
    std::array<bool, 512> keyPressed;
    bool Error;

private:
    double TimeSum, TimeMin, TimeMax;

protected:

    enum MouseButton
    {
        MOUSE_BUTTON_NONE = 0,
        MOUSE_BUTTON_LEFT = (1 << 0),
        MOUSE_BUTTON_RIGHT = (1 << 1),
        MOUSE_BUTTON_MIDDLE = (1 << 2)
    };

    enum KeyAction
    {
        KEY_PRESS = GLFW_PRESS,
        KEY_RELEASE = GLFW_RELEASE,
        KEY_REPEAT = GLFW_REPEAT
    };

    bool isKeyPressed(int Key) const
    {
        return this->keyPressed[Key];
    }

    virtual bool begin() = 0;
    virtual bool end() = 0;
    virtual bool render() = 0;

    void swap()
    {
        glfwSwapBuffers(this->window);
    }

    void sync(SyncMode const & Sync)
    {
        switch(Sync)
        {
            case ASYNC:
                glfwSwapInterval(0);
                break;
            case VSYNC:
                glfwSwapInterval(1);
                break;
            case TEARING:
                glfwSwapInterval(-1);
                break;
            default:
                assert(0);
        }
    }

    void stop() {
        glfwSetWindowShouldClose(this->window, GL_TRUE);
    }

    bool checkError(const char* Title) const;

    bool checkTemplate(GLFWwindow* pWindow, char const *title1);

};




//======================================================================================================
//======================================================================================================
//======================================================================================================




Engine::Engine
        (
                int argc, char* argv[], char const * Title,
                Profile profile, int Major, int Minor,
                bool sRGB
        ) :
        Engine(argc, argv, Title, profile, Major, Minor, glm::uvec2(640, 480), glm::vec2(0), glm::vec2(0, 4), 2, MATCH_TEMPLATE, true)
{}

Engine::Engine
        (
                int argc, char* argv[], char const * Title,
                Profile profile, int Major, int Minor,
                glm::uvec2 const & WindowSize, glm::vec2 const & Orientation, glm::vec2 const & Position,
                std::size_t FrameCount, Success success, bool sRGB
        ) :
        window(nullptr),
        success(success),
        title(Title),
        profile(profile),
        Major(Major),
        Minor(Minor),
        TimerQueryName(0),
        FrameCount(FrameCount),
        TimeSum(0.0),
        TimeMin(std::numeric_limits<double>::max()),
        TimeMax(0.0),
        mouseOrigin(WindowSize >> 1u),
        mouseCurrent(WindowSize >> 1u),
        tranlationOrigin(Position),
        tranlationCurrent(Position),
        rotationOrigin(Orientation),
        rotationCurrent(Orientation),
        mouseButtonFlags(0),
        Error(false)
{
    assert(WindowSize.x > 0 && WindowSize.y > 0);

    memset(&keyPressed[0], 0, sizeof(keyPressed));

    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
    glfwWindowHint(GLFW_SRGB_CAPABLE, GL_FALSE);
    glfwWindowHint(GLFW_DECORATED, GL_TRUE);
    glfwWindowHint(GLFW_CLIENT_API, profile == ES ? GLFW_OPENGL_ES_API : GLFW_OPENGL_API);

    if(version(this->Major, this->Minor) >= version(3, 2) || (profile == ES))
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, this->Major);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, this->Minor);
//#		if defined(__APPLE__)
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }

//#	if defined(__APPLE__)
    int const DPI = 2;

    this->window = glfwCreateWindow(WindowSize.x / DPI, WindowSize.y / DPI, argv[0], nullptr, nullptr);

    if(this->window)
    {
        glfwSetWindowPos(this->window, 64, 64);
        glfwSetWindowUserPointer(this->window, this);
        glfwSetMouseButtonCallback(this->window, Engine::mouseButtonCallback);
        glfwSetCursorPosCallback(this->window, Engine::cursorPositionCallback);
        glfwSetKeyCallback(this->window, Engine::keyCallback);
        glfwMakeContextCurrent(this->window);

        glewExperimental = GL_TRUE;
        glewInit();
        glGetError();

#		if defined(GL_KHR_debug)
			if(this->isExtensionSupported("GL_KHR_debug"))
			{
				glEnable(GL_DEBUG_OUTPUT);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
				glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
				glDebugMessageCallback(&Engine::debugOutput, this);
			}
#		endif

        glGenQueries(1, &this->TimerQueryName);
    }
}

void APIENTRY Engine::debugOutput
        (
                GLenum source,
                GLenum type,
                GLuint id,
                GLenum severity,
                GLsizei length,
                const GLchar* message,
                const GLvoid* userParam
        )
{
    assert(userParam);
    Engine* Test = static_cast<Engine*>(const_cast<GLvoid*>(userParam));

    char debSource[32], debType[32], debSev[32];

    if(source == GL_DEBUG_SOURCE_API_ARB)
        strcpy(debSource, "OpenGL");
    else if(source == GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB)
        strcpy(debSource, "Windows");
    else if(source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)
        strcpy(debSource, "Shader Compiler");
    else if(source == GL_DEBUG_SOURCE_THIRD_PARTY_ARB)
        strcpy(debSource, "Third Party");
    else if(source == GL_DEBUG_SOURCE_APPLICATION_ARB)
        strcpy(debSource, "Application");
    else if (source == GL_DEBUG_SOURCE_OTHER_ARB)
        strcpy(debSource, "Other");
    else
        assert(0);

    if(type == GL_DEBUG_TYPE_ERROR)
        strcpy(debType, "error");
    else if(type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR)
        strcpy(debType, "deprecated behavior");
    else if(type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR)
        strcpy(debType, "undefined behavior");
    else if(type == GL_DEBUG_TYPE_PORTABILITY)
        strcpy(debType, "portability");
    else if(type == GL_DEBUG_TYPE_PERFORMANCE)
        strcpy(debType, "performance");
    else if(type == GL_DEBUG_TYPE_OTHER)
        strcpy(debType, "message");
    else if(type == GL_DEBUG_TYPE_MARKER)
        strcpy(debType, "marker");
    else if(type == GL_DEBUG_TYPE_PUSH_GROUP)
        strcpy(debType, "push group");
    else if(type == GL_DEBUG_TYPE_POP_GROUP)
        strcpy(debType, "pop group");
    else
        assert(0);

    if(severity == GL_DEBUG_SEVERITY_HIGH_ARB)
    {
        strcpy(debSev, "high");
        if(Test->success == GENERATE_ERROR || source != GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)
            Test->Error = true;
    }
    else if(severity == GL_DEBUG_SEVERITY_MEDIUM_ARB)
        strcpy(debSev, "medium");
    else if(severity == GL_DEBUG_SEVERITY_LOW_ARB)
        strcpy(debSev, "low");
    else if (severity == GL_DEBUG_SEVERITY_NOTIFICATION)
        strcpy(debSev, "notification");
    else
        assert(0);

    fprintf(stderr,"%s: %s(%s) %d: %s\n", debSource, debType, debSev, id, message);

    if(Test->success != GENERATE_ERROR && source != GL_DEBUG_SOURCE_SHADER_COMPILER_ARB)
        assert(!Test->Error);
}

Engine::~Engine()
{
    if(this->TimerQueryName)
        glDeleteQueries(1, &this->TimerQueryName);

    if(this->window)
    {
        glfwDestroyWindow(this->window);
        this->window = 0;
    }

    glfwTerminate();
}

bool Engine::checkGLVersion(GLint MajorVersionRequire, GLint MinorVersionRequire) const
{
    GLint MajorVersionContext = 0;
    GLint MinorVersionContext = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &MajorVersionContext);
    glGetIntegerv(GL_MINOR_VERSION, &MinorVersionContext);
    printf("OpenGL Version Needed %d.%d ( %d.%d Found )\n",
           MajorVersionRequire, MinorVersionRequire,
           MajorVersionContext, MinorVersionContext);
    return version(MajorVersionContext, MinorVersionContext)
           >= version(MajorVersionRequire, MinorVersionRequire);
}


void Engine::cursorPositionCallback(GLFWwindow* window, double x, double y)
{
    Engine *ctx = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window));
    assert(ctx);

    ctx->mouseCurrent = glm::ivec2(x, y);
    ctx->tranlationCurrent = (ctx->mouseButtonFlags & Engine::MOUSE_BUTTON_LEFT) ?
                             ctx->tranlationOrigin + (ctx->mouseCurrent - ctx->mouseOrigin) / 10.f :
                             ctx->tranlationOrigin;

    ctx->rotationCurrent = (ctx->mouseButtonFlags & Engine::MOUSE_BUTTON_RIGHT) ?
                           ctx->rotationOrigin + glm::radians(ctx->mouseCurrent - ctx->mouseOrigin) :
                           ctx->rotationOrigin;
}


void Engine::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    Engine *ctx = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(window));
    assert(ctx);

    switch(action)
    {
        case GLFW_PRESS:
        {
            ctx->mouseOrigin = ctx->mouseCurrent;
            switch(button)
            {
                case GLFW_MOUSE_BUTTON_LEFT:
                {
                    ctx->mouseButtonFlags |= Engine::MOUSE_BUTTON_LEFT;
                    ctx->tranlationOrigin = ctx->tranlationCurrent;
                }
                    break;
                case GLFW_MOUSE_BUTTON_MIDDLE:
                {
                    ctx->mouseButtonFlags |= Engine::MOUSE_BUTTON_MIDDLE;
                }
                    break;
                case GLFW_MOUSE_BUTTON_RIGHT:
                {
                    ctx->mouseButtonFlags |= Engine::MOUSE_BUTTON_RIGHT;
                    ctx->rotationOrigin = ctx->rotationCurrent;
                }
                    break;
            }
        }
            break;
        case GLFW_RELEASE:
        {
            switch(button)
            {
                case GLFW_MOUSE_BUTTON_LEFT:
                {
                    ctx->tranlationOrigin += (ctx->mouseCurrent - ctx->mouseOrigin) / 10.f;
                    ctx->mouseButtonFlags &= ~Engine::MOUSE_BUTTON_LEFT;
                }
                    break;
                case GLFW_MOUSE_BUTTON_MIDDLE:
                {
                    ctx->mouseButtonFlags &= ~Engine::MOUSE_BUTTON_MIDDLE;
                }
                    break;
                case GLFW_MOUSE_BUTTON_RIGHT:
                {
                    ctx->rotationOrigin += glm::radians(ctx->mouseCurrent - ctx->mouseOrigin);
                    ctx->mouseButtonFlags &= ~Engine::MOUSE_BUTTON_RIGHT;
                }
                    break;
            }
        }
            break;
    }
}

void Engine::keyCallback(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
    if (Key < 0)
        return;

    Engine * Test = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(Window));
    assert(Test);

    Test->keyPressed[Key] = Action == KEY_PRESS;

    if(Test->isKeyPressed(GLFW_KEY_ESCAPE))
        Test->stop();
}



bool Engine::checkError(const char* Title) const
{
    int Error;
    if((Error = glGetError()) != GL_NO_ERROR)
    {
        std::string ErrorString;
        switch(Error)
        {
            case GL_INVALID_ENUM:
                ErrorString = "GL_INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                ErrorString = "GL_INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                ErrorString = "GL_INVALID_OPERATION";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                ErrorString = "GL_INVALID_FRAMEBUFFER_OPERATION";
                break;
            case GL_OUT_OF_MEMORY:
                ErrorString = "GL_OUT_OF_MEMORY";
                break;
            default:
                ErrorString = "UNKNOWN";
                break;
        }
        fprintf(stdout, "OpenGL Error(%s): %s\n", ErrorString.c_str(), Title);
        assert(0);
    }
    return Error == GL_NO_ERROR;
}



bool Engine::checkTemplate(GLFWwindow* pWindow, char const *title1)
{
    GLint colorType = GL_UNSIGNED_BYTE;
    GLint colorFormat = GL_RGBA;

    if (profile == ES)
    {
        glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_TYPE, &colorType);
        glGetIntegerv(GL_IMPLEMENTATION_COLOR_READ_FORMAT, &colorFormat);
    }

    GLint windowSizeX(0);
    GLint windowSizeY(0);
    glfwGetFramebufferSize(pWindow, &windowSizeX, &windowSizeY);

    gli::texture2D TextureRead(1, colorFormat == GL_RGBA ? gli::RGBA8_UNORM : gli::RGB8_UNORM,
                               gli::texture2D::dim_type(windowSizeX, windowSizeY));

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glReadPixels(0, 0, windowSizeX, windowSizeY, colorFormat, colorType, TextureRead.data());

    gli::texture2D TextureRGB(1, gli::RGB8_UNORM, gli::texture2D::dim_type(windowSizeX, windowSizeY));

    if(TextureRead.format() == gli::RGBA8_UNORM)
    {
        for(gli::size_t y = 0; y < TextureRGB.dimensions().y; ++y)
            for(gli::size_t x = 0; x < TextureRGB.dimensions().x; ++x)
            {
                gli::texture2D::dim_type TexelCoord(x, y);

                glm::u8vec3 Color(gli::texelFetch<glm::u8vec4>(TextureRead, TexelCoord, 0));
                gli::texelWrite(TextureRGB, TexelCoord, 0, Color);
            }
    }
    else
    {
        TextureRGB = TextureRead;
    }

    bool Success = true;

    if(Success)
    {
        gli::texture2D Template(load_png((getDataDirectory() + "templates/" + ::vendor() + title1 + ".png").c_str()));

        if(Success)
            Success = Success && (!Template.empty());

        if(Success)
            Success = Success && (Template == TextureRGB);
    }

    if(!Success)
        save_png(TextureRGB, (getBinaryDirectory() + title1 + ".png").c_str());

    return Success;
}


int Engine::init()
{
    if (this->window == 0)
        return EXIT_FAILURE;

    int Result = EXIT_SUCCESS;

    if (version(this->Major, this->Minor) >= version(3, 0))
        Result = checkGLVersion(this->Major, this->Minor) ? EXIT_SUCCESS : EXIT_FAILURE;

    if (Result == EXIT_SUCCESS)
        Result = this->begin() ? EXIT_SUCCESS : EXIT_FAILURE;

    std::size_t FrameNum = 0;
    bool Automated = false;

    while(Result == EXIT_SUCCESS && !this->Error)
    {
        Result = this->render() ? EXIT_SUCCESS : EXIT_FAILURE;
        Result = Result && this->checkError("render");

        glfwPollEvents();
        if(glfwWindowShouldClose(this->window) || (Automated && FrameNum == 0))
        {
            if(this->success == MATCH_TEMPLATE)
            {
                if(!checkTemplate(this->window, this->title.c_str()))
                    Result = EXIT_FAILURE;
                this->checkError("checkTemplate");
            }
            break;
        }

        this->swap();

    }

    Result = this->end() && (Result == EXIT_SUCCESS) ? EXIT_SUCCESS : EXIT_FAILURE;

    if(this->success == GENERATE_ERROR)
        return (Result != EXIT_SUCCESS || this->Error) ? EXIT_SUCCESS : EXIT_FAILURE;
    else
        return (Result == EXIT_SUCCESS && !this->Error) ? EXIT_SUCCESS : EXIT_FAILURE;
}



#endif //OGL_ENGINE_HPP
