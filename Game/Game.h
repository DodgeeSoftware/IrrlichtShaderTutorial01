// (c) Copyright Shem Taylor 2021 all rights reserved
// Author: Shem Taylor
// Company: DodgeeSoftware
// Contact Info: dodgeesoftware@gmail.com
// Youtube: youtube.com/dodgeesoftware

#ifndef GAME_H
#define GAME_H

// C/C++ Includes
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <vector>
#include <iomanip>

// Irrlicht Includes
#include <Irrlicht.h>

/** The Game Class is based on the singleton pattern which wraps up
    the games main loop. It follows a microkernel archetecture in that
    engine wide functions and data are stored here and made available
    to game states via a pGame pointer **/
class Game : public irr::IEventReceiver, irr::video::IShaderConstantSetCallBack, irr::scene::ILightManager
{
    // ***********
    // * FRIENDS *
    // ***********

    // Each new state added friends game so that it
    // can access the game objects private members

    // ***********************
    // * SINGLETON FUNCTIONS *
    // ***********************

    public:
        //! Get the singleton Instance
        static Game* getInstance();

    protected:
        // Singleton Poitner
        static Game* pInstance;

    // **************************
    // * COMMAND LINE ARGUMENTS *
    // **************************

    public:
        //! Process Command Line Args
        virtual void processCommandLineArguments(int argc, char* argv[]);

    protected:
        // Command line params go here

    // ***************
    // * CONSTRUCTOR *
    // ***************

    public:
        // Methods and members

    protected:
        //! Constructor
        Game();
        //! Destructor
        virtual ~Game();

    // *********************
    // * GENERAL FUNCTIONS *
    // *********************

    public:
        //! Run the Games Main Loop
        virtual int run(int argc, char* argv[]);

    public:
        //! Initialise the Game
        virtual bool init();
        //! Init the IrrlichtDevice
        virtual bool initIrrlichtDevice();
        //! Init Window
        virtual bool initWindow();
        //! Initialise InputSystem
        virtual bool initInputSystem();
        //! Initialise the LightFactory
        virtual bool initLightManager();
        //! Init Camera
        virtual bool initCamera();
        //! Init Fonts
        virtual bool initFonts();
        //! Init Lights
        virtual bool initLights();
        //! Init Demo
        virtual bool initDemo();
        //! Init GUI
        virtual bool initGUI();
        //! Init Sky
        virtual bool initSky();

    public:
        //! Handle events
        virtual void handleEvents();
        //! Think
        virtual void think();
        //! Update
        virtual void update();
        //! Draw
        virtual void draw();
        //! Quit the Game
        virtual void quit();

    public:
        //! Start the Game
        virtual void start();
        //! Stop the Game
        virtual void stop();
        //! Pause the game
        virtual void pause();
        //! Resume the game
        virtual void resume();
        //! Is the game engine paused
        virtual bool isPaused() { return this->paused; }
        //! Get Paused flag for the game engine
        virtual bool getPaused() { return this->paused; }
        //! Set Paused flag for the game engine
        virtual void setPaused(bool state) { this->paused = state; }
        //! Is the game engine running
        virtual bool isRunning() { return this->running; }
        //! Get Game Engine Running
        virtual bool getRunning() { return this->running; }
        //! Set the running state
        virtual void setRunning(bool running) { this->running = running; }

    public:
        //! Shutdown Light Factory
        virtual void shutdownLightManager();
        //! Shutdown Font
        virtual void shutdownFont();
        //! Shutdown Window
        virtual void shutdownWindow();
        //! Shutdown Device
        virtual void shutdownDevice();
        //! Shutdown Input System
        virtual void shutdownInputSystem();
        //! Shutdown Lights
        virtual void shutdownLights();
        //! Shutdown Camera
        virtual void shutdownCamera();
        //! Shutdown Demo
        virtual void shutdownDemo();

    protected:
        // Keep track of whether or not the game engine running
        bool running;
        // Keep track of whether or not the game engine is paused
        bool paused;


    // ********************
    // * IRRLICHT HANDLES *
    // ********************
    /* NOTE: Provde external access to our essential irrlicht cores */

    public:
        //! Get the IrrlichtDevice
        virtual irr::IrrlichtDevice* getIrrlichtDevice() { return this->pIrrlichtDevice; }
        //! Get the Irrlicht Driver
        virtual irr::video::IVideoDriver* getVideoDriver() { return this->pVideoDriver; }
        //! Get the SceneManager
        virtual irr::scene::ISceneManager* getSceneManager() { return this->pSceneManager; }
        //! Get the GUIEnvironment
        virtual irr::gui::IGUIEnvironment* getGUIEnvironment() { return this->pGUIEnvironment; }
        //! Get the GUISKin
        irr::gui::IGUISkin* getSkin() { return this->pSkin; }
        //! Get the FileSystem
        virtual irr::io::IFileSystem* getFileSystem() { return this->pFileSystem; }
        //! Get the CursorControl
        virtual irr::gui::ICursorControl* getCursorControl() { return this->pCursorControl; }
        //! Get the EventReceiver
        virtual irr::IEventReceiver* getEventReceiver() { return this->pEventReceiver; }
        //! Get the Logger
        virtual irr::ILogger* getLogger() { return this->pLogger; }
        //! Get the GPU
        virtual irr::video::IGPUProgrammingServices* getGPUProgrammingServices() { return this->pGPUProgrammingServices; }
        //! Get the Scene Collision Manager
        virtual irr::scene::ISceneCollisionManager* getSceneCollisionManager() { return this->pSceneCollisionManager; }
        //! Get the Mesh Manipulator
        virtual irr::scene::IMeshManipulator* getMeshManipulator() { return this->pMeshManipulator; }
        //! Get the Default SceneNodeAnimatorFactory
        virtual irr::scene::ISceneNodeAnimatorFactory* getDefaultSceneNodeAnimatorFactory() { return this->pDefaultSceneNodeAnimatorFactory; }
        //! Get the Default SceneNodeFactory
        virtual irr::scene::ISceneNodeFactory* getDefaultSceneNodeFactory() { return this->pDefaultSceneNodeFactory; }
        //! Get the Default GeometryCreator
        virtual const irr::scene::IGeometryCreator* getDefaultGeometryCreator() { return this->pDefaultGeometryCreator; }
        //! Get SceneLoader
        virtual irr::scene::ISceneLoader* getDefaultSceneLoader() { return this->pDefaultSceneLoader; }

    protected:
        // Pointer to the IrrlichtDevice
        irr::IrrlichtDevice* pIrrlichtDevice;
        // Pointer to the IrrlichtDriver
        irr::video::IVideoDriver* pVideoDriver;
        // Pointer to the SceneManager
        irr::scene::ISceneManager* pSceneManager;
        // Pointer to the GUIEnvironment
        irr::gui::IGUIEnvironment* pGUIEnvironment;
        // Pointer the GUISKin
        irr::gui::IGUISkin* pSkin;
        // Pointer to the FileSystem
        irr::io::IFileSystem* pFileSystem;
        // Pointer to the CursorControl
        irr::gui::ICursorControl* pCursorControl;
        // Pointer to the EventReceiver
        irr::IEventReceiver* pEventReceiver;
        // Pointer to the Scene Collision Manager
        irr::scene::ISceneCollisionManager* pSceneCollisionManager;
        // Pointer to the Logger
        irr::ILogger* pLogger;
        // Pointer to the GPU
        irr::video::IGPUProgrammingServices* pGPUProgrammingServices;
        // Pointer to the Mesh Manipulator
        irr::scene::IMeshManipulator* pMeshManipulator;
        // Pointer to the Default GeometryCreator
        const irr::scene::IGeometryCreator* pDefaultGeometryCreator;
        // Pointer to the Default SceneLoader
        irr::scene::ISceneLoader* pDefaultSceneLoader;
        // Pointer to the Default SceneNodeAnimatorFactory
        irr::scene::ISceneNodeAnimatorFactory* pDefaultSceneNodeAnimatorFactory;
        // Pointer to the Default SceneNodeFacotry
        irr::scene::ISceneNodeFactory* pDefaultSceneNodeFactory;

    // ******************
    // * IEVENTRECIEVER *
    // ******************
    // NOTE: This section handles input messages sent by the Operating System

    public:
        //! Callback to handle all Irrlicht events
        virtual bool OnEvent(const irr::SEvent& event);
        //! Function which handles keyboard events
        virtual void keyboardEvent(const irr::SEvent& event);
        //! Function which handles mouse events
        virtual void mouseEvent(const irr::SEvent& event);
        //! Function which handles mouse events
        virtual void mouseGUIEvent(const irr::SEvent& event);

    protected:
        // Members and methods

    // ******************************
    // * ISHADERCONSTANTSETCALLBACK *
    // ******************************
    /* NOTE: Irrlicht Provides two call backs one for when the material changes (OnSetMaterial)
        then the other when it passes variables to the shaders (OnSetConstants).*/

    public:
        //! This function is called by Irrlicht when setting the material for a shader to use
        virtual void OnSetMaterial(const irr::video::SMaterial& material);
        //! OnSetConstants
        virtual void OnSetConstants(irr::video::IMaterialRendererServices* pServices, irr::s32 userData);

    protected:
        // A local reference for the current material in use by the shader
        const irr::video::SMaterial* pShaderMaterial;

    // ********************
    // * LIGHT MANAGEMENT *
    // ********************
    /* NOTE: This section is the backend for the Irrlicht Light manager */
    /* TODO: Ok, so this is how things need to work, we need to sort and build lists of ONLY
        the lights visible on the screen (based on attenuation and position ect)
        that way we can optimise our deferred lighting model */

    public:
        /* TODO: For everyframe we need to add/remove lights from nodes inside a quadtree because
            some lights might have moved in the last frame */
        //! Called after the scene's light list has been built, but before rendering has begun.
        /** As actual device/hardware lights are not created until the
        ESNRP_LIGHT render pass, this provides an opportunity for the
        light manager to trim or re-order the light list, before any
        device/hardware lights have actually been created.
        \param lightList: the Scene Manager's light list, which
        the light manager may modify. This reference will remain valid
        until OnPostRender().
        */
        virtual void OnPreRender(irr::core::array<irr::scene::ISceneNode*>& lightList);
        //! Called after the last scene node is rendered.
        /** After this call returns, the lightList passed to OnPreRender() becomes invalid. */
        virtual void OnPostRender();
        //! Called before a render pass begins
        /** \param renderPass: the render pass that's about to begin */
        virtual void OnRenderPassPreRender(irr::scene::E_SCENE_NODE_RENDER_PASS renderPass);
        //! Called after the render pass specified in OnRenderPassPreRender() ends
        /** \param[in] renderPass: the render pass that has finished */
        virtual void OnRenderPassPostRender(irr::scene::E_SCENE_NODE_RENDER_PASS renderPass);
        //! Called before the given scene node is rendered
        /** \param[in] node: the scene node that's about to be rendered */
        virtual void OnNodePreRender(irr::scene::ISceneNode* node);
        //! Called after the the node specified in OnNodePreRender() has been rendered
        /** \param[in] node: the scene node that has just been rendered */
        virtual void OnNodePostRender(irr::scene::ISceneNode* node);

    protected:
        // List of Directional Lights
        std::vector<irr::scene::ILightSceneNode*> directionalLights;
        // List of Point Lights
        std::vector<irr::scene::ILightSceneNode*> pointLights;
        // List of Spot Lights
        std::vector<irr::scene::ILightSceneNode*> spotLights;
        // Temporary List of Directional Lights affecting a scene node (no access is provided to this list its used internally to the shader setup)
        std::vector<irr::scene::ILightSceneNode*> tempDirectionalLights;
        // Temporary List of Point Lights affecting a scene node (no access is provided to this list its used internally to the shader setup)
        std::vector<irr::scene::ILightSceneNode*> tempPointLights;
        // Temporary List of Spot Light saffecting a scene node (no access is provided to this list its used internally to the shader setup)
        std::vector<irr::scene::ILightSceneNode*> tempSpotLights;

    // **********
    // * CAMERA *
    // **********

    public:
        //! Get Camera
        virtual irr::scene::ICameraSceneNode* getCamera() { return this->pSceneManager->getActiveCamera(); }

    protected:
        // Methods and members

    // ****************
    // * INPUT SYSTEM *
    // ****************

    public:
        // Methods and members

    protected:
        // Keys array
        bool keys[irr::KEY_KEY_CODES_COUNT];

    // ***********
    // * SHADERS *
    // ***********

    public:
        //! Load Shader
        virtual irr::s32 loadShader(std::string vertexShader, std::string fragmentShader);

    protected:
        // Methods and memebers

    // ********
    // * DEMO *
    // ********

    public:
        // Methods and memebers

    protected:
        int xResolution;
        int yResolution;
        bool fullScreen;

    protected:
        // Fonts
        irr::gui::IGUIFont* pGUIFont;
        // Lights
        irr::scene::ILightSceneNode* pLight01;
        irr::scene::ILightSceneNode* pLight02;
        irr::scene::ILightSceneNode* pLight03;
        irr::scene::ILightSceneNode* pLight04;
        irr::scene::ILightSceneNode* pLight05;
        // shader handle
        irr::s32 shaderMaterial01;
        // shader handle
        irr::s32 shaderMaterial02;
        // shader handle
        irr::s32 shaderMaterial03;
        // Texture
        irr::video::ITexture* pTexture;
};

#endif // GAME_H
