// (c) Copyright Shem Taylor 2021 all rights reserved
// Author: Shem Taylor
// Company: DodgeeSoftware
// Contact Info: dodgeesoftware@gmail.com
// Youtube: youtube.com/dodgeesoftware

#include "Game.h"

Game* Game::pInstance = NULL;

Game* Game::getInstance()
{
    // If there is a singleton instance
    if (Game::pInstance != NULL)
    {
        // Return pointer to singleton
        return Game::pInstance;
    }
    // Create Singleton
    Game::pInstance = new Game();
    // Return pointer to singleton
    return Game::pInstance;
}

Game::Game()
{
    // ***************
    // * CONSTRUCTOR *
    // ***************

    // running flag
    this->running = false;
    // paused flag
    this->paused = false;
    // Irrlicht device
    this->pIrrlichtDevice = 0;
    // video driver
    this->pVideoDriver = 0;
    // scene mangaer
    this->pSceneManager = 0;
    // pGUI environment
    this->pGUIEnvironment = 0;
    // gpu programming services
    this->pGPUProgrammingServices = 0;
    // cursor control
    this->pCursorControl = 0;
    // Pointer the GUISKin
    this->pSkin = 0;
    // Pointer to the FileSystem
    this->pFileSystem = 0;
    // Pointer to the CursorControl
    this->pCursorControl = 0;
    // Pointer to the EventReceiver
    this->pEventReceiver = 0;
    // Pointer to the Scene Collision Manager
    this->pSceneCollisionManager = 0;
    // Pointer to the Logger
    this->pLogger = 0;
    // Pointer to the Mesh Manipulator
    this->pMeshManipulator = 0;
    // Pointer to the Default GeometryCreator
    this->pDefaultGeometryCreator = 0;
    // Pointer to the Default SceneLoader
    this->pDefaultSceneLoader = 0;
    // Pointer to the Default SceneNodeAnimatorFactory
    this->pDefaultSceneNodeAnimatorFactory = 0;
    // Pointer to the Default SceneNodeFacotry
    this->pDefaultSceneNodeFactory = 0;

    // DEMO
    // Window
    this->xResolution = 1920;
    this->yResolution = 1080;
    this->fullScreen = true;
    // Fonts
    this->pGUIFont = 0;
    // lihgts
    this->pLight01 = 0;
    this->pLight02 = 0;
    this->pLight03 = 0;
    this->pLight04 = 0;
    this->pLight05 = 0;
    // shader handles
    this->shaderMaterial01 = -1;
    this->shaderMaterial02 = -1;
    this->shaderMaterial03 = -1;

    this->pTexture = 0;
}

Game::~Game()
{
    // **************
    // * DESTRUCTOR *
    // **************

    // if there is an instance of the game class then destroy it.
    if (Game::pInstance != 0)
    {
        // destroy the instance of the GameEngine class
        delete Game::pInstance;
        // ensure that the instance pointer is set to point to nothing
        Game::pInstance = 0;
    }
}

int Game::run(int argc, char* argv[])
{
    // *******
    // * RUN *
    // *******

    // Process Command Lines Arguments
    this->processCommandLineArguments(argc, argv);
    // Init the Game
    if (this->init() == true)
    {
        // Start the engine
        this->start();
                // While the is Running flag is true keep running
        while (this->pIrrlichtDevice->run())
        {
            // Handle events such as keypresses, mouse movements and gamepad input
            this->handleEvents();
            // Process logic
            this->think();
            // Update
            this->update();
            // Draw all graphics
            this->draw();
        }
        // Stop the engine
        this->stop();
    }
    // Quit the Game
    this->quit();

    // Exit Success
    return EXIT_SUCCESS;
}

void Game::processCommandLineArguments(int argc, char* argv[])
{
    // **********************************
    // * PROCESS APPLICATION PARAMETERS *
    // **********************************

    // Send parameters ot the console
    for(int i = 0; i < argc; i++)
        std::cout << argv[i] << std::endl;

    // TODO: Parse command line parameters here
}

bool Game::init()
{
    // ********
    // * INIT *
    // ********

    // Init irrlicht Device
    if (this->initIrrlichtDevice() == false)
        return false;
    // Init Window
    if (this->initWindow() == false)
        return false;
    // Init Fonts
    if (this->initFonts() == false)
        return false;
    // Init Input System
    if (this->initInputSystem() == false)
        return false;
    // Init light manager
    if (this->initLightManager() == false)
        return false;
    // Init Camera
    if (this->initCamera() == false)
        return false;
    // Init Lights
    if (this->initLights() == false)
        return false;
    // Init Demo System
    if (this->initDemo() == false)
        return false;
    // Init GUI
    if (this->initGUI() == false)
        return false;
    // Init Sky
    if (this->initSky() == false)
        return false;

    // Success
    return true;
}

bool Game::initIrrlichtDevice()
{
    // ************************
    // * INIT IRRLICHT DEVICE *
    // ************************

    // Send a message to the console
    std::cout << "Game::initIrrlichtDevice()" << std::endl;

    // create Irrlicht Device
    this->pIrrlichtDevice = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(this->xResolution, this->yResolution), 32, this->fullScreen, false, false, 0);
    // If null return false
    if (this->pIrrlichtDevice == NULL)
        return false;

    // Register this  class as the event receiver
    this->pIrrlichtDevice->setEventReceiver(this);

    // Grab helpful pointers
        // Set the handle to the VideoDriver
    this->pVideoDriver = this->pIrrlichtDevice->getVideoDriver();
    // Set the handle to the SceneManager
    this->pSceneManager = this->pIrrlichtDevice->getSceneManager();
    // Set the handle to the GUIEnvironment
    this->pGUIEnvironment = this->pIrrlichtDevice->getGUIEnvironment();
    // Set the handle to the FileSystem
    this->pFileSystem = this->pIrrlichtDevice->getFileSystem();
    // Set the handle to the CursorControl
    this->pCursorControl = this->pIrrlichtDevice->getCursorControl();
    // Set the handle to the EventReceiver
    this->pEventReceiver = this->pIrrlichtDevice->getEventReceiver();
    // Set the handle to the Logger
    this->pLogger = this->pIrrlichtDevice->getLogger();
    // Set the handle to the GPU
    this->pGPUProgrammingServices = this->pIrrlichtDevice->getVideoDriver()->getGPUProgrammingServices();
    // Set the handle to the SceneCollisionManager
    this->pSceneCollisionManager = this->pIrrlichtDevice->getSceneManager()->getSceneCollisionManager();
    // Set the handle to the Mesh Manipulator
    this->pMeshManipulator = this->pIrrlichtDevice->getSceneManager()->getMeshManipulator();
    // Set the handle to the Default Geometry Creator
    this->pDefaultGeometryCreator = this->pIrrlichtDevice->getSceneManager()->getGeometryCreator();
    // Set the handle to the Default Scene Loader
    this->pDefaultSceneLoader = this->pIrrlichtDevice->getSceneManager()->getSceneLoader(0); // TODO: Review this to make sure that 0 is the default Scene Loader
    // Set the handle to the Default Scene Node Animator Factory
    this->pDefaultSceneNodeAnimatorFactory = this->pIrrlichtDevice->getSceneManager()->getDefaultSceneNodeAnimatorFactory();
    // Set the handle to the Default Scene Node Factory
    this->pDefaultSceneNodeFactory = this->pIrrlichtDevice->getSceneManager()->getDefaultSceneNodeFactory();

    // Set the Log level
    this->pIrrlichtDevice->getLogger()->setLogLevel(irr::ELL_DEBUG);

    // Send a message to the console
    std::cout << "Game::initIrrlichtDevice() success" << std::endl;

    // Success
    return true;
}

bool Game::initWindow()
{
    // ****************
    // * INIT WINDOW  *
    // ****************

    // Send a message to the console
    std::cout << "Game::initWindow()" << std::endl;

    // Set Window Caption
    this->pIrrlichtDevice->setWindowCaption(L"IrrlichtShaders");

    // Send a message to the console
    std::cout << "Game::initWindow() successs" << std::endl;

    // Success
    return true;
}

bool Game::initInputSystem()
{
    // *********************
    // * INIT INPUT SYSTEM *
    // *********************

    // Send a message to the console
    std::cout << "Game::initInputSystem()" << std::endl;

    // Set the Event handle
    this->pIrrlichtDevice->setEventReceiver(this);

    // Send a message to the console
    std::cout << "Game::initInputSystem() success" << std::endl;

    // Success
    return true;
}

bool Game::initLightManager()
{
    // **********************
    // * INIT LIGHT MANAGER *
    // **********************

    // send a message to the console
    std::cout << "Game::initLightManager()" << std::endl;

    // Set the light manager
    this->pSceneManager->setLightManager(this);

    // send a message to the console
    std::cout << "Game::initLightManager() success" << std::endl;

    // Success
    return true;
}

bool Game::initCamera()
{
    // ***************
    // * INIT CAMERA *
    // ***************

    // send a message to the console
    std::cout << "Game::initCamera()" << std::endl;

    // Make a Default Camera
    irr::SKeyMap keyMap[8];
    keyMap[0].Action = irr::EKA_MOVE_FORWARD;
    keyMap[0].KeyCode = irr::KEY_UP;
    keyMap[1].Action = irr::EKA_MOVE_FORWARD;
    keyMap[1].KeyCode = irr::KEY_KEY_W;
    keyMap[2].Action = irr::EKA_MOVE_BACKWARD;
    keyMap[2].KeyCode = irr::KEY_DOWN;
    keyMap[3].Action = irr::EKA_MOVE_BACKWARD;
    keyMap[3].KeyCode = irr::KEY_KEY_S;
    keyMap[4].Action = irr::EKA_STRAFE_LEFT;
    keyMap[4].KeyCode = irr::KEY_LEFT;
    keyMap[5].Action = irr::EKA_STRAFE_LEFT;
    keyMap[5].KeyCode = irr::KEY_KEY_A;
    keyMap[6].Action = irr::EKA_STRAFE_RIGHT;
    keyMap[6].KeyCode = irr::KEY_RIGHT;
    keyMap[7].Action = irr::EKA_STRAFE_RIGHT;
    keyMap[7].KeyCode = irr::KEY_KEY_D;
    irr::scene::ICameraSceneNode* pCamera = this->pSceneManager->addCameraSceneNodeFPS(0, 100.0f, 0.5f, -1, keyMap, 8);
        pCamera->setPosition(irr::core::vector3df(0.0, 50.0f, -250.0f));
        pCamera->setRotation(irr::core::vector3df(0.0f, 0.0f, 0.0f));
        this->pSceneManager->setActiveCamera(pCamera);

    // send a message to the console
    std::cout << "Game::initCamera() success" << std::endl;

    // Success
    return true;
}

bool Game::initFonts()
{
    // send a message to the console
    std::cout << "bool Game::initFonts()" << std::endl;

    // Load a font
    this->pGUIFont = this->pGUIEnvironment->getFont("media/fonts/ConsoleFont.png");

    // send a message to the console
    std::cout << "bool Game::initFonts() success" << std::endl;
    // Success
    return true;
}

bool Game::initLights()
{
    // ***************
    // * INIT LIGHTS *
    // ***************

    // send a message to the console
    std::cout << "Game::initLights()" << std::endl;

    irr::scene::ISceneNode* pNode = 0;
    irr::scene::ILightSceneNode* pLightNode = 0;
    irr::video::ITexture* pTexture = 0;
    irr::scene::IBillboardSceneNode* pBillboardNode = 0;

    // LIGHTING
    irr::video::SLight lightData;
    // Ambient Light
    this->pSceneManager->setAmbientLight(irr::video::SColorf(0.2f, 0.2f, 0.2f, 1.0f));
    // Shadow Colour
    this->pSceneManager->setShadowColor(irr::video::SColor(0.0f, 0.0f, 0.0f, 1.0f));

    // DIRECTIONAL LIGHT
    lightData = irr::video::SLight();
    pLight01 = this->pSceneManager->addLightSceneNode();
        lightData.Type = irr::video::ELT_DIRECTIONAL;
        lightData.DiffuseColor = irr::video::SColorf(.23f, .23f, 0.25f, 1.0f);
        //lightData.SpecularColor = irr::video::SColorf(.5f, .5f, 0.45f, 1.0f);
        pLight01->setLightData(lightData);
        pLight01->setRotation(irr::core::vector3df(0.0f, 90.0f - 45, 45.0f + 45));

    // POINT LIGHT
    // Light Properties
    lightData = irr::video::SLight();
    lightData.Type = irr::video::ELT_POINT;
    lightData.AmbientColor = irr::video::SColorf(0.0f, 0.0f, 0.0f, 1.0f);
    lightData.DiffuseColor = irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f);
    lightData.SpecularColor = irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f);
    lightData.Attenuation = irr::core::vector3df(0.0f, 0.2f, 0.000f);
    //lightData.Attenuation = irr::core::vector3df(1.0f, 0.0f, 0.000f);
    lightData.Radius = 100.0f;
    // Add Light
    this->pLight02 = this->pSceneManager->addLightSceneNode();
        this->pLight02->setLightData(lightData);
        this->pLight02->setPosition(irr::core::vector3df(-150.0f, 50.0f, 0.0f));
    // Light Marker
    pNode = this->pSceneManager->addSphereSceneNode(5.0f);
        //this->pNode->setPosition(this->pLight02->getPosition());
        pNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        pNode->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
        // Parent the Marker to the Light
        pNode->setParent(this->pLight02);
    pBillboardNode = this->pSceneManager->addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(20.0f, 20.0f), irr::core::vector3df(0, 0, 0));
        pBillboardNode->setParent(this->pLight02);
        pBillboardNode->setMaterialTexture(0, pVideoDriver->getTexture("media/particles/white.png"));
        pBillboardNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        pBillboardNode->setMaterialType(irr:: video::EMT_TRANSPARENT_ADD_COLOR);

    // POINT LIGHT
    // Light Properties
    lightData = irr::video::SLight();
    lightData.Type = irr::video::ELT_POINT;
    lightData.AmbientColor = irr::video::SColorf(0.0f, 0.0f, 0.0f, 1.0f);
    lightData.DiffuseColor = irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f);
    lightData.SpecularColor = irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f);
    lightData.Attenuation = irr::core::vector3df(0.0f, 0.2f, 0.000f);
    //lightData.Attenuation = irr::core::vector3df(1.0f, 0.0f, 0.000f);
    lightData.Radius = 100.0f;
    // Add Light
    pLight03 = this->pSceneManager->addLightSceneNode();
        pLight03->setLightData(lightData);
        pLight03->setPosition(irr::core::vector3df(0.0f, 50.0f, 0.0f));
    // Light Marker
    pNode = this->pSceneManager->addSphereSceneNode(5.0f);
        //pNode->setPosition(pLight03->getPosition());
        pNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        pNode->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
        // Parent the Marker to the Light
        pNode->setParent(this->pLight03);
    pBillboardNode = this->pSceneManager->addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(20.0f, 20.0f), irr::core::vector3df(0, 0, 0));
        pBillboardNode->setParent(this->pLight03);
        pBillboardNode->setMaterialTexture(0, pVideoDriver->getTexture("media/particles/white.png"));
        pBillboardNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        pBillboardNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        pBillboardNode->setMaterialType(irr:: video::EMT_TRANSPARENT_ADD_COLOR);

    // POINT LIGHT
    // Light Properties
    lightData = irr::video::SLight();
    lightData.Type = irr::video::ELT_POINT;
    lightData.AmbientColor = irr::video::SColorf(0.0f, 0.0f, 0.0f, 1.0f);
    lightData.DiffuseColor = irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f);
    lightData.SpecularColor = irr::video::SColorf(1.0f, 1.0f, 1.0f, 1.0f);
    lightData.Attenuation = irr::core::vector3df(0.0f, 0.2f, 0.000f);
    //lightData.Attenuation = irr::core::vector3df(1.0f, 0.0f, 0.000f);
    lightData.Radius = 100.0f;
    // Add Light
    pLight04 = this->pSceneManager->addLightSceneNode();
        pLight04->setLightData(lightData);
        pLight04->setPosition(irr::core::vector3df(150.0f, 50.0f, 0.0f));
    // Light Marker
    pNode = this->pSceneManager->addSphereSceneNode(5.0f);
        //pNode->setPosition(pLight04->getPosition());
        pNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        pNode->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
        // Parent the Marker to the Light
        pNode->setParent(this->pLight04);
    pBillboardNode = this->pSceneManager->addBillboardSceneNode(0, irr::core::dimension2d<irr::f32>(20.0f, 20.0f), irr::core::vector3df(0, 0, 0));
        pBillboardNode->setParent(this->pLight04);
        pBillboardNode->setMaterialTexture(0, pVideoDriver->getTexture("media/particles/white.png"));
        pBillboardNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        pBillboardNode->setMaterialType(irr:: video::EMT_TRANSPARENT_ADD_COLOR);

    // send a message to the console
    std::cout << "Game::initLights() success" << std::endl;

    // Success
    return true;
}

bool Game::initDemo()
{
    // *************
    // * INIT DEMO *
    // *************

    irr::scene::IMesh* pMesh = 0;
    irr::scene::IAnimatedMesh* pAnimatedMesh = 0;
    irr::scene::IMeshSceneNode* pMeshSceneNode = 0;
    irr::scene::IAnimatedMeshSceneNode* pAnimatedmeshSceneNode = 0;
    irr::scene::ISceneNode* pNode = 0;

    // LOAD SHADERS
    this->shaderMaterial01 = this->loadShader("media/shaders/BasicVertexShader.glsl", "media/shaders/BasicFragmentShader.glsl");
    this->shaderMaterial02 = this->loadShader("media/shaders/LambertVertexShader.glsl", "media/shaders/LambertFragmentShader.glsl");
    this->shaderMaterial03 = this->loadShader("media/shaders/PhongVertexShader.glsl", "media/shaders/PhongFragmentShader.glsl");

    // SHADER 1 TEST
    // Load a Mesh
    pAnimatedMesh = pSceneManager->getMesh("media/meshes/Doominator.x");
    if (pAnimatedMesh == 0)
        return false;
    // Add the mesh to a scene node
    pAnimatedmeshSceneNode = this->pSceneManager->addAnimatedMeshSceneNode(pAnimatedMesh);
        pAnimatedmeshSceneNode->setPosition(irr::core::vector3df(-150.0f, 0.0f, 0.0f));
        pAnimatedmeshSceneNode->setScale(irr::core::vector3df(0.1f, 0.1f, 0.1f));
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_BLEND_OPERATION, true);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_ANISOTROPIC_FILTER, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_ANTI_ALIASING, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_TRILINEAR_FILTER, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_USE_MIP_MAPS, false);
        pAnimatedmeshSceneNode->setMaterialType((irr::video::E_MATERIAL_TYPE)this->shaderMaterial01);
        pAnimatedmeshSceneNode->getMaterial(0).Shininess = 200.0f;
    pNode = this->pSceneManager->addTextSceneNode(pGUIFont, L"Basic Shader");
        pNode->setPosition(irr::core::vector3df(0.0f, 150.0f, 0.0f));
        pNode->setParent(pAnimatedmeshSceneNode);

//    // Add the mesh to a scene node
//    pMeshSceneNode = this->pSceneManager->addSphereSceneNode(200.0f, 32);
//        pMeshSceneNode->setPosition(irr::core::vector3df(-150.0f, 0.0f, 0.0f));
//        pMeshSceneNode->setScale(irr::core::vector3df(0.1f, 0.1f, 0.1f));
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_BLEND_OPERATION, true);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_ANISOTROPIC_FILTER, false);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_ANTI_ALIASING, false);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_TRILINEAR_FILTER, false);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_USE_MIP_MAPS, false);
//        pMeshSceneNode->setMaterialType((irr::video::E_MATERIAL_TYPE)this->shaderMaterial01);
//        pMeshSceneNode->getMaterial(0).Shininess = 800.0f;
//        pMeshSceneNode->getMaterial(0).SpecularColor = irr::video::SColor(255, 255, 255, 255);
//        pMeshSceneNode->getMaterial(0).DiffuseColor = irr::video::SColor(255, 255, 255, 255);
//        pMeshSceneNode->getMaterial(0).AmbientColor = irr::video::SColor(255, 255, 255, 255);
//        pMeshSceneNode->setMaterialTexture(0, 0);
//        pMeshSceneNode->setMaterialTexture(1, 0)
//        pMeshSceneNode->setMaterialTexture(2, 0);
//        pMeshSceneNode->setMaterialTexture(3, 0);

    // SHADER 2 TEST
    // Load a Mesh
    pAnimatedMesh = pSceneManager->getMesh("media/meshes/Doominator.x");
    if (pAnimatedMesh == 0)
        return false;
    // Add the mesh to a scene node
    pAnimatedmeshSceneNode = this->pSceneManager->addAnimatedMeshSceneNode(pAnimatedMesh);
        pAnimatedmeshSceneNode->setPosition(irr::core::vector3df(0.0f, 0.0f, 0.0f));
        pAnimatedmeshSceneNode->setScale(irr::core::vector3df(0.1f, 0.1f, 0.1f));
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_BLEND_OPERATION, true);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_ANISOTROPIC_FILTER, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_ANTI_ALIASING, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_TRILINEAR_FILTER, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_USE_MIP_MAPS, false);
        pAnimatedmeshSceneNode->setMaterialType((irr::video::E_MATERIAL_TYPE)this->shaderMaterial02);
        pAnimatedmeshSceneNode->getMaterial(0).Shininess = 800.0f;
    pNode = this->pSceneManager->addTextSceneNode(pGUIFont, L"Lambert Shader");
        pNode->setPosition(irr::core::vector3df(0.0f, 150.0f, 0.0f));
        pNode->setParent(pAnimatedmeshSceneNode);

//    // Add the mesh to a scene node
//    pMeshSceneNode = this->pSceneManager->addSphereSceneNode(200.0f, 32);
//        pMeshSceneNode->setPosition(irr::core::vector3df(0.0f, 0.0f, 0.0f));
//        pMeshSceneNode->setScale(irr::core::vector3df(0.1f, 0.1f, 0.1f));
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_BLEND_OPERATION, true);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_ANISOTROPIC_FILTER, false);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_ANTI_ALIASING, false);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_TRILINEAR_FILTER, false);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_USE_MIP_MAPS, false);
//        pMeshSceneNode->setMaterialType((irr::video::E_MATERIAL_TYPE)this->shaderMaterial02);
//        pMeshSceneNode->getMaterial(0).Shininess = 800.0f;
//        pMeshSceneNode->getMaterial(0).SpecularColor = irr::video::SColor(255, 255, 255, 255);
//        pMeshSceneNode->getMaterial(0).DiffuseColor = irr::video::SColor(255, 255, 255, 255);
//        pMeshSceneNode->getMaterial(0).AmbientColor = irr::video::SColor(255, 255, 255, 255);
//        pMeshSceneNode->setMaterialTexture(0, 0);
//        pMeshSceneNode->setMaterialTexture(1, 0);
//        pMeshSceneNode->setMaterialTexture(2, 0);
//        pMeshSceneNode->setMaterialTexture(3, 0);

    // SHADER 3 TEST
    // Load a Mesh
    pAnimatedMesh = pSceneManager->getMesh("media/meshes/Doominator.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/Basic.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/BoneTest1.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/Arm.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/NormalTest.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/BoneTest1 - Expected Values.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/BoneTest2.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/BoneTest3.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/BoneTest5.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/NewMatrixTest.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/BigGun.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/UVMappedObject.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/uvmapped.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/TempleOilLamp.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/Scientist.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/PersonModel.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/Battery.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/Icecream.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/flower.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/BlenderSimpleExtrude.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/Doominator.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/untitled.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/TexCube.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/ChickenCoupe.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/Facehugger.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/FencedSpot.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/SpecialTest.x");
    //pAnimatedMesh = pSceneManager->getMesh("media/meshes/LevelTest.x");
    if (pAnimatedMesh == 0)
    {
        std::cout << "AnimatedMesh was null" << std::endl;
        return false;
    }
    // Add the mesh to a scene node
    pAnimatedmeshSceneNode = this->pSceneManager->addAnimatedMeshSceneNode(pAnimatedMesh);
        pAnimatedmeshSceneNode->setPosition(irr::core::vector3df(150.0f, 0.0f, 0.0f));
        pAnimatedmeshSceneNode->setRotation(irr::core::vector3df(0.0f, 0.0f, 0.0f));
        pAnimatedmeshSceneNode->setScale(irr::core::vector3df(0.1f, 0.1f, 0.1f));
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_FRONT_FACE_CULLING, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_BLEND_OPERATION, true);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_ANISOTROPIC_FILTER, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_ANTI_ALIASING, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_TRILINEAR_FILTER, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_USE_MIP_MAPS, false);
        pAnimatedmeshSceneNode->setMaterialType((irr::video::E_MATERIAL_TYPE)this->shaderMaterial03);
    pNode = this->pSceneManager->addTextSceneNode(pGUIFont, L"Phong Shader");
        pNode->setPosition(irr::core::vector3df(0.0f, 150.0f, 0.0f));
        pNode->setParent(pAnimatedmeshSceneNode);

//    // Add the mesh to a scene node
//    pMeshSceneNode = this->pSceneManager->addSphereSceneNode(200.0f, 32);
//        pMeshSceneNode->setPosition(irr::core::vector3df(150.0f, 0.0f, 0.0f));
//        pMeshSceneNode->setScale(irr::core::vector3df(0.1f, 0.1f, 0.1f));
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_BLEND_OPERATION, true);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_ANISOTROPIC_FILTER, false);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_ANTI_ALIASING, false);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_TRILINEAR_FILTER, false);
//        pMeshSceneNode->setMaterialFlag(irr::video::EMF_USE_MIP_MAPS, false);
//        pMeshSceneNode->setMaterialType((irr::video::E_MATERIAL_TYPE)this->shaderMaterial03);
//        pMeshSceneNode->getMaterial(0).Shininess = 800.0f;
//        pMeshSceneNode->getMaterial(0).SpecularColor = irr::video::SColor(255, 255, 255, 255);
//        pMeshSceneNode->getMaterial(0).DiffuseColor = irr::video::SColor(255, 255, 255, 255);
//        pMeshSceneNode->getMaterial(0).AmbientColor = irr::video::SColor(255, 255, 255, 255);
//        pMeshSceneNode->setMaterialTexture(0, 0);
//        pMeshSceneNode->setMaterialTexture(1, 0);
//        pMeshSceneNode->setMaterialTexture(2, 0);
//        pMeshSceneNode->setMaterialTexture(3, 0);

    // SHADER 4 TEST
    // Load a Mesh
    pAnimatedMesh = pSceneManager->getMesh("media/meshes/plane.x");
    if (pAnimatedMesh == 0)
    {
        std::cout << "Mesh was null" << std::endl;
        return false;
    }
    // Add the mesh to a scene node
    pAnimatedmeshSceneNode = this->pSceneManager->addAnimatedMeshSceneNode(pAnimatedMesh);
        pAnimatedmeshSceneNode->setPosition(irr::core::vector3df(0.0f, -25.0f, 0.0f));
//        pAnimatedmeshSceneNode->setScale(irr::core::vector3df(0.1f, 0.1f, 0.1f));
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_BACK_FACE_CULLING, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_BLEND_OPERATION, true);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_ANISOTROPIC_FILTER, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_ANTI_ALIASING, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_BILINEAR_FILTER, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_TRILINEAR_FILTER, false);
        pAnimatedmeshSceneNode->setMaterialFlag(irr::video::EMF_USE_MIP_MAPS, false);
        pAnimatedmeshSceneNode->setMaterialType((irr::video::E_MATERIAL_TYPE)this->shaderMaterial03);
        pAnimatedmeshSceneNode->getMaterial(0).Shininess = 800.0f;
        pAnimatedmeshSceneNode->getMaterial(0).SpecularColor = irr::video::SColor(255, 255, 255, 255);
        pAnimatedmeshSceneNode->getMaterial(0).DiffuseColor = irr::video::SColor(255, 255, 255, 255);
        pAnimatedmeshSceneNode->getMaterial(0).AmbientColor = irr::video::SColor(255, 255, 255, 255);
        pAnimatedmeshSceneNode->setMaterialTexture(0, 0);
        pAnimatedmeshSceneNode->setMaterialTexture(1, 0);
        pAnimatedmeshSceneNode->setMaterialTexture(2, 0);
        pAnimatedmeshSceneNode->setMaterialTexture(3, 0);

    // Success
    return true;
}

bool Game::initGUI()
{
    // ************
    // * INIT GUI *
    // ************

    // SETUP GUI ELEMENTS
    this->pCursorControl->setVisible(false);
    // Apply Dodgee Software Logo
    irr::gui::IGUIImage* pLogo = this->pGUIEnvironment->addImage(this->pVideoDriver->getTexture("media/logos/Dodgee Software.jpg"), irr::core::position2d<int>(0.0f, 0.0f));
    if (pLogo != 0)
    {
        pLogo->setRelativePosition(irr::core::position2di((int)(this->xResolution - pLogo->getAbsolutePosition().getWidth() - 10.0f), (int)this->yResolution - pLogo->getAbsolutePosition().getHeight() - 10.0f));
        pLogo->setUseAlphaChannel(true);
        pLogo->setColor(irr::video::SColor(255,255,255,255));
    }

    // Success
    return true;
}

bool Game::initSky()
{
    // ************
    // * INIT SKY *
    // ************

    // Add Sky
    irr::scene::ISceneNode* pSkyBox = this->pSceneManager->addSkyBoxSceneNode(this->pVideoDriver->getTexture("media/sky/space1.jpg"),
                                                                              this->pVideoDriver->getTexture("media/sky/space1.jpg"),
                                                                              this->pVideoDriver->getTexture("media/sky/space1.jpg"),
                                                                              this->pVideoDriver->getTexture("media/sky/space1.jpg"),
                                                                              this->pVideoDriver->getTexture("media/sky/space1.jpg"),
                                                                              this->pVideoDriver->getTexture("media/sky/space1.jpg"));

    // Success
    return true;
}

void Game::handleEvents()
{
    // *****************
    // * HANDLE EVENTS *
    // *****************

}

void Game::think()
{
    // *********
    // * THINK *
    // *********

}

void Game::update()
{
    // **********
    // * UPDATE *
    // **********

    // ANIMATE THE POINT LIGHTS
    static float theta = 0.0f;
    theta = theta + 0.001f;
    this->pLight02->setPosition(irr::core::vector3df(-150.0f + cos(theta * 2.0f) * 25.0f, sin(theta) * 25.0f, cos(theta) * 25.0f));
    this->pLight03->setPosition(irr::core::vector3df(0.0f + cos(theta * 2.0f) * 25.0f, sin(theta) * 25.0f, cos(theta) * 25.0f));
    this->pLight04->setPosition(irr::core::vector3df(150.0f + cos(theta * 2.0f) * 25.0f, sin(theta) * 25.0f, cos(theta) * 25.0f));

}

void Game::draw()
{
    // ********
    // * DRAW *
    // ********

    // Being the Scene
    this->pVideoDriver->beginScene(true, true, irr::video::SColor(255, 0, 0, 0));
        // Draw everything in the scene
        this->pSceneManager->drawAll();
        // Cache the current camera matrix and the current world matrix
        irr::core::matrix4 previous_camera = getCamera()->getViewMatrix();
        irr::core::matrix4 previous_world = pIrrlichtDevice->getVideoDriver()->getTransform(irr::video::ETS_WORLD);
        // Cache the old material
        irr::video::SMaterial previousMaterial = pIrrlichtDevice->getVideoDriver()->getMaterial2D();
        // Build a view matrix so that lines are drawn correctly
        irr::core::matrix4 mat;
        mat.setScale(irr::core::vector3df(1.0f, 1.0f, 1.0f));
        mat.setRotationDegrees(getCamera()->getViewMatrix().getRotationDegrees());
        mat.setTranslation(getCamera()->getViewMatrix().getTranslation());
        // Set the world view projection matrix
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, irr::core::matrix4());
        //pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, mat);
        // Build default material settings
        irr::video::SMaterial material;
        material.setFlag(irr::video::EMF_LIGHTING, false);
        material.setFlag(irr::video::EMF_ZWRITE_ENABLE, true);
        material.setFlag(irr::video::EMF_ZBUFFER, true);
        material.setFlag(irr::video::EMF_ANTI_ALIASING, false);
        // Set the Material
        pIrrlichtDevice->getVideoDriver()->setMaterial(material);

        // restore the veiw matrix and the world matrix
        //pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_VIEW, previous_camera);
        pIrrlichtDevice->getVideoDriver()->setTransform(irr::video::ETS_WORLD, previous_world);
        // restore the previous material
        pIrrlichtDevice->getVideoDriver()->setMaterial(previousMaterial);

        // If there is a font loaded
        if (this->pGUIFont != 0)
        {
            // When we are in fullscreen mode
            if (this->fullScreen == true)
            {
                // Calculate text position
                irr::core::rect<irr::s32> rect;
                    rect.UpperLeftCorner.X = 0;
                    rect.UpperLeftCorner.Y = 0;
                // Draw text at positions
                this->pGUIFont->draw(L"Irrlicht Shader Tutorial 01 (GLSL) (c) Dodgee Software 2021", rect, irr::video::SColor(255, 255, 255, 255), false, false, 0);
            }
        }
        // Draw the GUI
        this->pGUIEnvironment->drawAll();
    // Swap the buffers
    this->pVideoDriver->endScene();
}

void Game::quit()
{
    // ********
    // * QUIT *
    // ********

    // Shutdown Lights
    this->shutdownLights();
    // Shutdown Camera
    this->shutdownCamera();
    // Shutdown Demo
    this->shutdownDemo();
    // Shutdown LightManager
    this->shutdownLightManager();
    //  Shutdown InputSystem
    this->shutdownInputSystem();
    // Shutdown Fonts
    this->shutdownFont();
    // Shutdown Window
    this->shutdownWindow();
    // Shutdown Device
    this->shutdownDevice();
}

void Game::shutdownDevice()
{
    // *******************
    // * SHUTDOWN DEVICE *
    // *******************

    // Send a message to the console
    std::cout << "void Game::shutdownDevice()" << std::endl;

    // Drop the Irrlicht device
    this->pIrrlichtDevice->drop();
    this->pIrrlichtDevice = 0;
    // video driver
    this->pVideoDriver = 0;
    // scene mangaer
    this->pSceneManager = 0;
    // pGUI environment
    this->pGUIEnvironment = 0;
    // gpu programming services
    this->pGPUProgrammingServices = 0;
    // cursor control
    this->pCursorControl = 0;
    // Pointer the GUISKin
    this->pSkin = 0;
    // Pointer to the FileSystem
    this->pFileSystem = 0;
    // Pointer to the CursorControl
    this->pCursorControl = 0;
    // Pointer to the EventReceiver
    this->pEventReceiver = 0;
    // Pointer to the Scene Collision Manager
    this->pSceneCollisionManager = 0;
    // Pointer to the Logger
    this->pLogger = 0;
    // Pointer to the Mesh Manipulator
    this->pMeshManipulator = 0;
    // Pointer to the Default GeometryCreator
    this->pDefaultGeometryCreator = 0;
    // Pointer to the Default SceneLoader
    this->pDefaultSceneLoader = 0;
    // Pointer to the Default SceneNodeAnimatorFactory
    this->pDefaultSceneNodeAnimatorFactory = 0;
    // Pointer to the Default SceneNodeFacotry
    this->pDefaultSceneNodeFactory = 0;

    // Send a message to the console
    std::cout << "void Game::shutdownDevice() success" << std::endl;
}

void Game::shutdownLightManager()
{
    // **************************
    // * SHUTDOWN LIGHT MANAGER *
    // **************************

    // Send message to the console
    std::cout << "void Game::shutdownLightManager()" << std::endl;

    // NOTE: there is no way I know to shut down the light factory, this function exists for design symmetry (for now anyway)

    // Send message to the console
    std::cout << "void Game::shutdownLightManager() success" << std::endl;
}

void Game::shutdownFont()
{
    // ***********************
    // * CLEAN UP FONTS HERE *
    // ***********************

    // Send message to the console
    std::cout << "void Game::shutdownLightManager()" << std::endl;

    // Clean up fonts here
    this->pGUIEnvironment->removeFont(this->pGUIFont);
    this->pGUIFont = 0;

    // Send message to the console
    std::cout << "void Game::shutdownLightManager() success" << std::endl;
}

void Game::shutdownWindow()
{
    // *******************
    // * SHUTDOWN WINDOW *
    // *******************

    // Send a message to the console
    std::cout << "void Game::shutdownWindow()" << std::endl;

    // Set Window Caption
    this->pIrrlichtDevice->setWindowCaption(L"");

    // Send a message to the console
    std::cout << "void Game::shutdownWindow() success" << std::endl;
}

void Game::shutdownInputSystem()
{
    // *************************
    // * SHUTDOWN INPUT SYSTEM *
    // *************************

    // Send a message to the console
    std::cout << "void Game::shutdownInputSystem()" << std::endl;

    // Set the Event handle
    this->pIrrlichtDevice->setEventReceiver(0);

    // Send a message to the console
    std::cout << "void Game::shutdownInputSystem() success" << std::endl;
}

void Game::shutdownLights()
{
    // *******************
    // * SHUTDOWN LIGHTS *
    // *******************

    // Send a message to the console
    std::cout << "void Game::shutdownLights()" << std::endl;

    // If necessary clean up lights here mainly global lights like a global directinal light

    // Send a message to the console
    std::cout << "void Game::shutdownLights() success" << std::endl;
}

void Game::shutdownCamera()
{
    // Send a message to the console
    std::cout << "void Game::shutdownCamera()" << std::endl;

    // Remove the Camera
    this->pSceneManager->getActiveCamera()->remove();

    // Send a message to the console
    std::cout << "void Game::shutdownCamera() success" << std::endl;
}

void Game::shutdownDemo()
{
    // *****************
    // * SHUTDOWN DEMO *
    // *****************

    // TODO: clean up the demo stuff here
}

void Game::start()
{
    // *********
    // * START *
    // *********
}

void Game::stop()
{
    // ********
    // * STOP *
    // ********

}

void Game::pause()
{
    // *********
    // * PAUSE *
    // *********

}

void Game::resume()
{
    // **********
    // * RESUME *
    // **********

}

bool Game::OnEvent(const irr::SEvent& event)
{
    // LOG ALL EVENTS TO THE CONSOLE
    if (event.EventType  == irr::EET_LOG_TEXT_EVENT)
    {
        std::cout << event.LogEvent.Text << std::endl;
    }
    // HANDLE KEY INPUT
    if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        this->keys[event.KeyInput.Key] = event.KeyInput.PressedDown;
        this->keyboardEvent(event);
    }
    // HANDLE MOUS INPUT
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
    {
        this->mouseEvent(event);
    }
    // HANDLE GUI EVENTS
    else if (event.EventType == irr::EET_GUI_EVENT)
    {
        this->mouseGUIEvent(event);
    }
    // PASS EVENTS TO THE CAMERA
    irr::scene::ICameraSceneNode* pCamera = this->pSceneManager->getActiveCamera();
    if (pCamera != 0)
        pCamera->OnEvent(event);

    // Return true because the event was handled
    return true;
}

void Game::OnSetMaterial(const irr::video::SMaterial& material)
{
    /* NOTE: All the shaders we write should have these available. When you load the shader
        we pass the Game class in as the callback. The Game class has access to everything
        our game uses, cameras, gameobjects, player positions. This is where we pass parameters
        to our shader. I designed this set as a basic idea I call it a schema probably not the
        right word for it. */

    // *****************
    // * ONSETMATERIAL *
    // *****************

    /* This function deserves a little documentation. Basically the Game Class is a shadercallback
        and this is an optional method which irrlicht calls as it sets a material for use for drawing.
        By implementing this our shader callback knows what material is in use and we can pass
        material properties like diffuse, ambient, emmissive colours to the shader :) */
    this->pShaderMaterial = &material;
}

void Game::OnSetConstants(irr::video::IMaterialRendererServices* pServices, irr::s32 userData)
{
    // ******************
    // * ONSETCONSTANTS *
    // ******************

    // GET SOME HANDY GLOBALS
    // Get the VideoDriver
    irr::video::IVideoDriver* pVideoDriver = Game::getInstance()->getVideoDriver();
    // Get the type of Video Driver (OpenGL / DirectX etc)
    irr::video::E_DRIVER_TYPE driverType = Game::getInstance()->getVideoDriver()->getDriverType();

    // SET THE SHADER'S SCREEN DIMENSIONS
    // Get the ScreenWidth
    irr::f32 screenWidth = (irr::f32)pVideoDriver->getScreenSize().Width;
    // Set the vertex shader's ScreenWidth
    pServices->setVertexShaderConstant("ScreenWidth", reinterpret_cast<irr::f32*>(&screenWidth), 1);
    // Set the pixel shader's ScreenWidth
    pServices->setPixelShaderConstant("ScreenWidth", reinterpret_cast<irr::f32*>(&screenWidth), 1);
    // Get the ScreenHeight
    irr::f32 screenHeight = (irr::f32)pVideoDriver->getScreenSize().Height;
    // Set the vertex shader's ScreenHeight
    pServices->setVertexShaderConstant("ScreenHeight", reinterpret_cast<irr::f32*>(&screenHeight), 1);
    // Set the pixel shader's ScreenHeight
    pServices->setPixelShaderConstant("ScreenHeight", reinterpret_cast<irr::f32*>(&screenHeight), 1);

    // SET THE SHADER'S WORLDVIEWPROJECTMATRIX
    // Set the shader's WorldViewProjection Matrix
    irr::core::matrix4 WorldViewProjection;
    // Calculate the WorldViewProjection Matrix
    WorldViewProjection = pVideoDriver->getTransform(irr::video::ETS_PROJECTION) * pVideoDriver->getTransform(irr::video::ETS_VIEW) * pVideoDriver->getTransform(irr::video::ETS_WORLD);
    //WorldViewProjection = pVideoDriver->getTransform(irr::video::ETS_WORLD) * pVideoDriver->getTransform(irr::video::ETS_VIEW) * pVideoDriver->getTransform(irr::video::ETS_PROJECTION); // This calc is incorrect
    // Pass the WorldViewProjection Matrix to the Vertex Shader
    pServices->setVertexShaderConstant("WorldViewProjectionMatrix", WorldViewProjection.pointer(), 16);
    // Pass the WorldViewProjection Matrix to the Pixel Shader
    pServices->setPixelShaderConstant("WorldViewProjectionMatrix", WorldViewProjection.pointer(), 16);

    // SET THE SHADER's WORLDMATRIX
    irr::core::matrix4 WorldMatrix;
    // Get the world matrix
    WorldMatrix = pVideoDriver->getTransform(irr::video::ETS_WORLD);
    // Pass the WorldViewProjection Matrix to the Vertex Shader
    pServices->setVertexShaderConstant("WorldMatrix", WorldMatrix.pointer(), 16);
    // Pass the WorldViewProjection Matrix to the Pixel Shader
    pServices->setPixelShaderConstant("WorldMatrix", WorldMatrix.pointer(), 16);

    // SET THE SHADER's INVERSEWORLDMATRIX
    irr::core::matrix4 InverseWorldMatrix;
    // Calculate the InverseWorldMatrix
    InverseWorldMatrix = pVideoDriver->getTransform(irr::video::ETS_WORLD);
        InverseWorldMatrix.makeInverse();
    // Pass the WorldViewProjection Matrix to the Vertex Shader
    pServices->setVertexShaderConstant("InverseWorldMatrix", InverseWorldMatrix.pointer(), 16);
    // Pass the WorldViewProjection Matrix to the Pixel Shader
    pServices->setPixelShaderConstant("InverseWorldMatrix", InverseWorldMatrix.pointer(), 16);

    // SET THE SHADER'S WORLDVIEW MATRIX
    // Grab the ViewMatrix
    irr::core::matrix4 ViewMatrix = pVideoDriver->getTransform(irr::video::ETS_VIEW);
    // Set the vertex shader's View Matrix
    pServices->setVertexShaderConstant("ViewMatrix", ViewMatrix.pointer(), 16);
    // Set the pixel shader's View Matrix
    pServices->setPixelShaderConstant("ViewMatrix", ViewMatrix.pointer(), 16);

    // SET THE SHADERS INVERSEWORLDVIEW
    // Calculate the InverseWorldViewMatrix
    irr::core::matrix4 InverseViewMatrix = pVideoDriver->getTransform(irr::video::ETS_VIEW);
        // Invert the World Matrix
        InverseViewMatrix.makeInverse();
    // Set the vertex shader's InverseView Matrix
    pServices->setVertexShaderConstant("InverseViewMatrix", InverseViewMatrix.pointer(), 16);
    // Set the pixel shader's InverseView Matrix
    pServices->setPixelShaderConstant("InverseViewMatrix", InverseViewMatrix.pointer(), 16);

    // SET THE SHADER'S PROJECTIONMATRIX
    // Create the ProjectionMatrix
    irr::core::matrix4 ProjectionMatrix;
    // Grab the ProjectionMatrix
    ProjectionMatrix = pVideoDriver->getTransform(irr::video::ETS_PROJECTION);
    // Pass the ProjectionMatrix Matrix to the Vertex Shader
    pServices->setVertexShaderConstant("ProjectionMatrix", ProjectionMatrix.pointer(), 16);
    // Pass the ProjectionMatrix Matrix to the Pixel Shader
    pServices->setPixelShaderConstant("ProjectionMatrix", ProjectionMatrix.pointer(), 16);

    // SET THE SHADER'S INVERSEPROJECTIONMATRIX
    // Create the InverseProjectionMatrix
    irr::core::matrix4 InverseProjectionMatrix;
    // Calculate the InverseProjectionMatrix
    InverseProjectionMatrix = pVideoDriver->getTransform(irr::video::ETS_PROJECTION);
        InverseProjectionMatrix.makeInverse();
    // Pass the InverseProjectionMatrix Matrix to the Vertex Shader
    pServices->setVertexShaderConstant("InverseProjectionMatrix", InverseProjectionMatrix.pointer(), 16);
    // Pass the InverseProjectionMatrix Matrix to the Pixel Shader
    pServices->setPixelShaderConstant("InverseProjectionMatrix", InverseProjectionMatrix.pointer(), 16);

    // SET THE SHADER's NORMAL MATRIX
    irr::core::matrix4 NormalMatrix = pVideoDriver->getTransform(irr::video::ETS_WORLD);
    /* We calculate the Normal Matrix here using the 'World' Matrix (this is a meshes transformation
        matrix). To convert this to a normal matrix what I do is remove the translation part of the
        matrix viola, the correct normal matrix. */
        // Remove Translation from the World Matrix
        NormalMatrix.setTranslation(irr::core::vector3df(0.0f, 0.0f, 0.0f));
    // Pass the WorldViewProjection Matrix to the Vertex Shader
    pServices->setVertexShaderConstant("NormalMatrix", NormalMatrix.pointer(), 16);
    // Pass the WorldViewProjection Matrix to the Pixel Shader
    pServices->setPixelShaderConstant("NormalMatrix", NormalMatrix.pointer(), 16);

    // SET THE SHADER'S TIMER
    // Set the shader's time value
    irr::f32 time = ((irr::f32)(pIrrlichtDevice->getTimer()->getTime()) / 1000.0f);
    // Set the vertex shader's timer
    pServices->setVertexShaderConstant("Time", reinterpret_cast<irr::f32*>(&time), 1);
    // Set the pixel shader's timer
    pServices->setPixelShaderConstant("Time", reinterpret_cast<irr::f32*>(&time), 1);

    // SET THE SHADER'S CAMERA PROPERTIES
    if (pIrrlichtDevice->getSceneManager()->getActiveCamera() != 0)
    {
        // Get the camera position
        irr::core::vector3df cameraPosition = pIrrlichtDevice->getSceneManager()->getActiveCamera()->getPosition();
        // Get the camera target normal
        irr::core::vector3df cameraTarget = (pIrrlichtDevice->getSceneManager()->getActiveCamera()->getTarget() - pIrrlichtDevice->getSceneManager()->getActiveCamera()->getAbsolutePosition()).normalize();
        // Get the camera view matrix
        irr::core::matrix4 cameraViewMatrix = pIrrlichtDevice->getSceneManager()->getActiveCamera()->getViewMatrix();
        // Calculate camera inverse view matrix
        irr::core::matrix4 inverseCameraViewMatrix;
            cameraViewMatrix.getInverse(inverseCameraViewMatrix);
        // Get the camera projection matrix
        irr::core::matrix4 cameraProjectionMatrix = pIrrlichtDevice->getSceneManager()->getActiveCamera()->getProjectionMatrix();
        // Calculate camera inverse projection matrix
        irr::core::matrix4 inverseCameraProjectionMatrix;
            cameraProjectionMatrix.getInverse(inverseCameraProjectionMatrix);
        // Get Camera Near Plane
        float cameraNearPlane = pIrrlichtDevice->getSceneManager()->getActiveCamera()->getNearValue();
        // Get Camera Far Plane
        float cameraFarPlane = pIrrlichtDevice->getSceneManager()->getActiveCamera()->getFarValue();
        // Get Camera FOV
        float cameraFOV = pIrrlichtDevice->getSceneManager()->getActiveCamera()->getFOV();

        // Set vertex shader's camera position
        pServices->setVertexShaderConstant("CameraPosition", reinterpret_cast<irr::f32*>(&cameraPosition), 3);
        // Set pixel shader's camera position
        pServices->setPixelShaderConstant("CameraPosition", reinterpret_cast<irr::f32*>(&cameraPosition), 3);
        // Set vertex shader's camera target
        pServices->setVertexShaderConstant("CameraTarget", reinterpret_cast<irr::f32*>(&cameraTarget), 3);
        // Set pixel shader's camera target
        pServices->setPixelShaderConstant("CameraTarget", reinterpret_cast<irr::f32*>(&cameraTarget), 3);
        // Set vertex shader's camera view matrix
        pServices->setVertexShaderConstant("CameraViewMatrix", cameraViewMatrix.pointer(), 16);
        // Set pixel shader's camera view matrix
        pServices->setPixelShaderConstant("CameraViewMatrix", cameraViewMatrix.pointer(), 16);
        // Set vertex shader's inverse camera view matrix
        pServices->setVertexShaderConstant("InverseCameraViewMatrix", inverseCameraViewMatrix.pointer(), 16);
        // Set pixel shader's inverse camera view matrix
        pServices->setPixelShaderConstant("InverseCameraViewMatrix", inverseCameraViewMatrix.pointer(), 16);
        // Set vertex shader's camera view matrix
        pServices->setVertexShaderConstant("CameraProjectionMatrix", cameraProjectionMatrix.pointer(), 16);
        // Set pixel shader's camera view matrix
        pServices->setPixelShaderConstant("CameraProjectionMatrix", cameraProjectionMatrix.pointer(), 16);
        // Set vertex shader's inverse camera view matrix
        pServices->setVertexShaderConstant("InverseCameraProjectionMatrix", inverseCameraProjectionMatrix.pointer(), 16);
        // Set pixel shader's inverse camera view matrix
        pServices->setPixelShaderConstant("InverseCameraProjectionMatrix", inverseCameraProjectionMatrix.pointer(), 16);
        // Set vertex shader's cameraNearPlane
        pServices->setVertexShaderConstant("CameraNearPlane", &cameraNearPlane, 1);
        // Set pixel shader's cameraNearPlane
        pServices->setPixelShaderConstant("CameraNearPlane", &cameraNearPlane, 1);
        // Set vertex shader's cameraFarPlane
        pServices->setVertexShaderConstant("CameraFarPlane", &cameraFarPlane, 1);
        // Set pixel shader's cameraFarPlane
        pServices->setPixelShaderConstant("CameraFarPlane", &cameraFarPlane, 1);
        // Set vertex shader's cameraFOV
        pServices->setVertexShaderConstant("CameraFOV", &cameraFOV, 1);
        // Set pixel shader's cameraFOV
        pServices->setPixelShaderConstant("CameraFOV", &cameraFOV, 1);
    }

    // PASS IRRLICHT MATERIAL PROPERTIES TO THE SHADER
    // Grab the Material (this is set in OnSetMaterial callback local to the Game:: class)
    const irr::video::SMaterial& material = *(this->pShaderMaterial);
    /* TODO: We are going to need to pass more properties from the material, such as EMF_LIGHTING for a lighting flag
    and anything else we think could be of relevance to a shader */
    // Set the shader variables for this material
    irr::f32 specularPower = material.Shininess;

    // Is lighting enabled?
    int lightingEnabled = material.Lighting;
    // Is lighting enabled?
    int zWriteEnabled = material.ZWriteEnable;
    // Get the material Type Param
    float materialTypeParam = material.MaterialTypeParam;
    // Get the material Type Param2
    float materialTypeParam2 = material.MaterialTypeParam2;
    // Get the material's thickness
    float thickness = material.Thickness;
    // Get the material's ambient color
    irr::video::SColorf ambientMaterialColor = material.AmbientColor;
    // Get the material's diffuse color
    irr::video::SColorf diffuseMaterialColor = material.DiffuseColor;
    // Get the material's specular color
    irr::video::SColorf specularMaterialColor = material.SpecularColor;
    // Get the material's emissive color
    irr::video::SColorf emissiveMaterialColor = material.EmissiveColor;
    // Set the LightingEnabled Flag for the Vertex Shader
    pServices->setVertexShaderConstant("LightingEnabled", &lightingEnabled, 1);
    // Set the LightingEnabled Flag for the Pixel Shader
    pServices->setPixelShaderConstant("LightingEnabled", &lightingEnabled, 1);
    // Set the LightingEnabled Flag for the Vertex Shader
    pServices->setVertexShaderConstant("ZWriteEnable", &zWriteEnabled, 1);
    // Set the LightingEnabled Flag for the Pixel Shader
    pServices->setPixelShaderConstant("ZWriteEnable", &zWriteEnabled, 1);
    // Set the Specular Power for the Vertex Shader
    pServices->setVertexShaderConstant("SpecularPower", reinterpret_cast<irr::f32*>(&specularPower), 1);
    // Set the Specular Power for the Pixel Shader
    pServices->setPixelShaderConstant("SpecularPower", reinterpret_cast<irr::f32*>(&specularPower), 1);
    // Set the Ambient Material Color for the Vertex Shader
    pServices->setVertexShaderConstant("AmbientMaterialColor", reinterpret_cast<irr::f32*>(&ambientMaterialColor), 4);
    // Set the Ambient Material Color for the Pixel Shader
    pServices->setPixelShaderConstant("AmbientMaterialColor", reinterpret_cast<irr::f32*>(&ambientMaterialColor), 4);
    // Set the Diffuse Material Color for the Vertex Shader
    pServices->setVertexShaderConstant("DiffuseMaterialColor", reinterpret_cast<irr::f32*>(&diffuseMaterialColor), 4);
    // Set the Diffuse Material Color for the Pixel Shader
    pServices->setPixelShaderConstant("DiffuseMaterialColor", reinterpret_cast<irr::f32*>(&diffuseMaterialColor), 4);
    // Set the Specular Material Color for the Vertex Shader
    pServices->setVertexShaderConstant("SpecularMaterialColor", reinterpret_cast<irr::f32*>(&specularMaterialColor), 4);
    // Set the Specular Material Color for the Pixel Shader
    pServices->setPixelShaderConstant("SpecularMaterialColor", reinterpret_cast<irr::f32*>(&specularMaterialColor), 4);
    // Set the Emissive Material Color for the Vertex Shader
    pServices->setVertexShaderConstant("EmissiveMaterialColor", reinterpret_cast<irr::f32*>(&emissiveMaterialColor), 4);
    // Set the Emissive Material Color for the Pixel Shader
    pServices->setPixelShaderConstant("EmissiveMaterialColor", reinterpret_cast<irr::f32*>(&emissiveMaterialColor), 4);
    // Set the MaterialTypeParam for the Vertex Shader
    pServices->setVertexShaderConstant("MaterialTypeParam", reinterpret_cast<irr::f32*>(&materialTypeParam), 1);
    // Set the MaterialTypeParam for the Pixel Shader
    pServices->setPixelShaderConstant("MaterialTypeParam", reinterpret_cast<irr::f32*>(&materialTypeParam), 1);
    // Set the MaterialTypeParam2 for the Vertex Shader
    pServices->setVertexShaderConstant("MaterialTypeParam2", reinterpret_cast<irr::f32*>(&materialTypeParam2), 1);
    // Set the MaterialTypeParam2 for the Pixel Shader
    pServices->setPixelShaderConstant("MaterialTypeParam2", reinterpret_cast<irr::f32*>(&materialTypeParam2), 1);

    // Assign texture IDs to variables
    int textureNULL = -1;
    int texture0 = 0;  // Irrlicht automatically binds 'material.getTexture(0)' to location 0
    int texture1 = 1;  // Irrlicht automatically binds 'material.getTexture(1)' to location 1
    int texture2 = 2;  // Irrlicht automatically binds 'material.getTexture(2)' to location 2
    int texture3 = 3;  // Irrlicht automatically binds 'material.getTexture(3)' to location 3
    int texture4 = 4;  // Irrlicht automatically binds 'material.getTexture(4)' to location 4
    int texture5 = 5;  // Irrlicht automatically binds 'material.getTexture(5)' to location 5
    int texture6 = 6;  // Irrlicht automatically binds 'material.getTexture(6)' to location 6
    int texture7 = 7;  // Irrlicht automatically binds 'material.getTexture(7)' to location 7
    /* A default compilation of irrlicht will only allow 0 - 3 texture numbers
        or a total of four textures. To change this up to a maximum of 8 textures per material
        you will need to build irrlicht with the _IRR_MATERIAL_MAX_TEXTURES_ flag set to 8.
        DirectX Model Importer: the format contrains one texture per material, this means
        that texture 0 will always be present and unless you use it otherwise will be the the diffuse map.
    *   Textures are passed by texture slot on the graphics card in HLSL and GLSL and CG*/
    if (_IRR_MATERIAL_MAX_TEXTURES_ > 0)
    {
        // Is Texutre0 in use?
        float texture0InUse = ((material.getTexture(0) == 0) ? 0.0f : 1.0f);
        // Pass the texture into the Vertex Shader
        pServices->setVertexShaderConstant("Texture0InUse", &texture0InUse, 1);
        // Pass the texture into the Pixel Shader
        pServices->setPixelShaderConstant("Texture0InUse", &texture0InUse, 1);
        // Pass the texture into the Vertex Shader
        pServices->setVertexShaderConstant("Texture0", &texture0, 1);
        // Pass the texture into the Pixel Shader
        pServices->setPixelShaderConstant("Texture0", &texture0, 1);
        // Get the Texture0Matrix
        irr::core::matrix4 Texture0Matrix = material.getTextureMatrix(0);
        // Set the vertex shader's Texture0Matrix Matrix
        pServices->setVertexShaderConstant("Texture0Matrix", Texture0Matrix.pointer(), 16);
        // Set the pixel shader's Texture0Matrix Matrix
        pServices->setPixelShaderConstant("Texture0Matrix", Texture0Matrix.pointer(), 16);
    }
    if (_IRR_MATERIAL_MAX_TEXTURES_ > 1)
    {
        // Is Texutre1 in use?
        float texture1InUse = ((material.getTexture(1) == 0) ? 0.0f : 1.0f);
        // Pass the texture into the Vertex Shader
        pServices->setVertexShaderConstant("Texture1InUse", &texture1InUse, 1);
        // Pass the texture into the Pixel Shader
        pServices->setPixelShaderConstant("Texture1InUse", &texture1InUse, 1);
        // Pass the texture into the Vertex Shader
        pServices->setVertexShaderConstant("Texture1", &texture1, 1);
        // Pass the texture into the Pixel Shader
        pServices->setPixelShaderConstant("Texture1", &texture1, 1);
        // Get the Texture1Matrix
        irr::core::matrix4 Texture1Matrix = material.getTextureMatrix(1);
        // Set the vertex shader's Texture1Matrix Matrix
        pServices->setVertexShaderConstant("Texture1Matrix", Texture1Matrix.pointer(), 16);
        // Set the pixel shader's Texture1Matrix Matrix
        pServices->setPixelShaderConstant("Texture1Matrix", Texture1Matrix.pointer(), 16);
    }
    if (_IRR_MATERIAL_MAX_TEXTURES_ > 2)
    {
        // Is Texutre2 in use?
        float texture2InUse = ((material.getTexture(2) == 0) ? 0.0f : 1.0f);
        // Pass the texture into the Vertex Shader
        pServices->setVertexShaderConstant("Texture2InUse", &texture2InUse, 1);
        // Pass the texture into the Pixel Shader
        pServices->setPixelShaderConstant("Texture2InUse", &texture2InUse, 1);
        // Pass the texture into the Vertex Shader
        pServices->setVertexShaderConstant("Texture2", &texture2, 1);
        // Pass the texture into the Pixel Shader
        pServices->setPixelShaderConstant("Texture2", &texture2, 1);
        // Get the Texture2Matrix
        irr::core::matrix4 Texture2Matrix = material.getTextureMatrix(2);
        // Set the vertex shader's Texture2Matrix Matrix
        pServices->setVertexShaderConstant("Texture2Matrix", Texture2Matrix.pointer(), 16);
        // Set the pixel shader's Texture2Matrix Matrix
        pServices->setPixelShaderConstant("Texture2Matrix", Texture2Matrix.pointer(), 16);
    }
    if (_IRR_MATERIAL_MAX_TEXTURES_ > 3)
    {
        // Is Texutre3 in use?
        float texture3InUse = ((material.getTexture(3) == 0) ? 0.0f : 1.0f);
        // Pass the texture into the Vertex Shader
        pServices->setVertexShaderConstant("Texture3InUse", &texture3InUse, 1);
        // Pass the texture into the Pixel Shader
        pServices->setPixelShaderConstant("Texture3InUse", &texture3InUse, 1);
        // Pass the texture into the Vertex Shader
        pServices->setVertexShaderConstant("Texture3", &texture3, 1);
        // Pass the texture into the Pixel Shader
        pServices->setPixelShaderConstant("Texture3", &texture3, 1);
        // Get the Texture3Matrix
        irr::core::matrix4 Texture3Matrix = material.getTextureMatrix(3);
        // Set the vertex shader's Texture3Matrix Matrix
        pServices->setVertexShaderConstant("Texture3Matrix", Texture3Matrix.pointer(), 16);
        // Set the pixel shader's Texture3Matrix Matrix
        pServices->setPixelShaderConstant("Texture3Matrix", Texture3Matrix.pointer(), 16);
    }
    if (_IRR_MATERIAL_MAX_TEXTURES_ > 4)
    {
        // Is Texutre4 in use?
        float texture4InUse = ((material.getTexture(4) == 0) ? 0.0f : 1.0f);
        // Pass the texture into the Vertex Shader
        pServices->setVertexShaderConstant("Texture4InUse", &texture4InUse, 1);
        // Pass the texture into the Pixel Shader
        pServices->setPixelShaderConstant("Texture4InUse", &texture4InUse, 1);
        // Pass the texture into the Vertex Shader
        pServices->setVertexShaderConstant("Texture4", &texture4, 1);
        // Pass the texture into the Pixel Shader
        pServices->setPixelShaderConstant("Texture4", &texture4, 1);
        // Get the Texture4Matrix
        irr::core::matrix4 Texture4Matrix = material.getTextureMatrix(4);
        // Set the vertex shader's Texture4Matrix Matrix
        pServices->setVertexShaderConstant("Texture4Matrix", Texture4Matrix.pointer(), 16);
        // Set the pixel shader's Texture4Matrix Matrix
        pServices->setPixelShaderConstant("Texture4Matrix", Texture4Matrix.pointer(), 16);
    }
    if (_IRR_MATERIAL_MAX_TEXTURES_ > 5)
    {
        // Is Texutre5 in use?
        float texture5InUse = ((material.getTexture(5) == 0) ? 0.0f : 1.0f);
        // Pass the texture into the Vertex Shader
        pServices->setVertexShaderConstant("Texture5InUse", &texture5InUse, 1);
        // Pass the texture into the Pixel Shader
        pServices->setPixelShaderConstant("Texture5InUse", &texture5InUse, 1);
        // Pass the texture into the Vertex Shader
        pServices->setVertexShaderConstant("Texture5", &texture5, 1);
        // Pass the texture into the Pixel Shader
        pServices->setPixelShaderConstant("Texture5", &texture5, 1);
        // Get the Texture5Matrix
        irr::core::matrix4 Texture5Matrix = material.getTextureMatrix(5);
        // Set the vertex shader's Texture5Matrix Matrix
        pServices->setVertexShaderConstant("Texture5Matrix", Texture5Matrix.pointer(), 16);
        // Set the pixel shader's Texture5Matrix Matrix
        pServices->setPixelShaderConstant("Texture5Matrix", Texture5Matrix.pointer(), 16);
    }
    if (_IRR_MATERIAL_MAX_TEXTURES_ > 6)
    {
        // Is Texutre6 in use?
        float texture6InUse = ((material.getTexture(6) == 0) ? 0.0f : 1.0f);
        // Pass the texture into the Vertex Shader
        pServices->setVertexShaderConstant("Texture6InUse", &texture6InUse, 1);
        // Pass the texture into the Pixel Shader
        pServices->setPixelShaderConstant("Texture6InUse", &texture6InUse, 1);
        // Pass the texture into the Vertex Shader
        pServices->setVertexShaderConstant("Texture6", &texture6, 1);
        // Pass the texture into the Pixel Shader
        pServices->setPixelShaderConstant("Texture6", &texture6, 1);
        // Get the Texture6Matrix
        irr::core::matrix4 Texture6Matrix = material.getTextureMatrix(6);
        // Set the vertex shader's Texture6Matrix Matrix
        pServices->setVertexShaderConstant("Texture6Matrix", Texture6Matrix.pointer(), 16);
        // Set the pixel shader's Texture6Matrix Matrix
        pServices->setPixelShaderConstant("Texture6Matrix", Texture6Matrix.pointer(), 16);
    }
    if (_IRR_MATERIAL_MAX_TEXTURES_ > 7)
    {
        // Is Texutre7 in use?
        float texture7InUse = ((material.getTexture(7) == 0) ? 0.0f : 1.0f);
        // Pass the texture into the Vertex Shader
        pServices->setVertexShaderConstant("Texture7InUse", &texture7InUse, 1);
        // Pass the texture into the Pixel Shader
        pServices->setPixelShaderConstant("Texture7InUse", &texture7InUse, 1);
        // Pass the texture into the Vertex Shader
        pServices->setVertexShaderConstant("Texture7", &texture7, 1);
        // Pass the texture into the Pixel Shader
        pServices->setPixelShaderConstant("Texture7", &texture7, 1);
        // Get the Texture7Matrix
        irr::core::matrix4 Texture7Matrix = material.getTextureMatrix(7);
        // Set the vertex shader's Texture7Matrix Matrix
        pServices->setVertexShaderConstant("Texture7Matrix", Texture7Matrix.pointer(), 16);
        // Set the pixel shader's Texture7Matrix Matrix
        pServices->setPixelShaderConstant("Texture7Matrix", Texture7Matrix.pointer(), 16);
    }
    // PASS LIGHTS TO THE SHADER
    // Get Ambient Light
    irr::video::SColorf ambientLight = this->pSceneManager->getAmbientLight();
    // Array for the ambient light
    float ambientLightArray[4] = {ambientLight.getRed(), ambientLight.getGreen(), ambientLight.getBlue(), ambientLight.getAlpha()};
    // Set vertex shader's AmbientLight
    pServices->setVertexShaderConstant("AmbientLight", reinterpret_cast<irr::f32*>(&ambientLightArray[0]), 4);
    // Set pxiel shader's AmbientLight
    pServices->setPixelShaderConstant("AmbientLight", reinterpret_cast<irr::f32*>(&ambientLightArray[0]), 4);

    // Get the Shadow Colour
    irr::video::SColorf shadowColour = this->pSceneManager->getShadowColor();
    // Array for the shadow colour
    float shadowColourArray[4] = {shadowColour.getRed(), shadowColour.getGreen(), shadowColour.getBlue(), shadowColour.getAlpha()};
    // Set vertex shader's AmbientLight
    pServices->setVertexShaderConstant("ShadowColor", reinterpret_cast<irr::f32*>(&shadowColourArray[0]), 4);
    // Set pxiel shader's AmbientLight
    pServices->setPixelShaderConstant("ShadowColor", reinterpret_cast<irr::f32*>(&shadowColourArray[0]), 4);

    // 8888888888888 Work in progress - Start 888888888888888888
        // The Fog Colour
        irr::video::SColor fogColour;
        // The Fog Type
        irr::video::E_FOG_TYPE fogType; // EFT_FOG_EXP=0, EFT_FOG_LINEAR, EFT_FOG_EXP2
        // Start of the Fog
        float fogStart = 0.0f; // Used in Linear Fog (ignored in exponential fog)
        // End of the Fog
        float fogEnd = 0.0f; // Used in Linear Fog (ignored in exponential fog)
        // Density of the Fog
        float fogDensity = 0.0f; // Only used in Exponential Fog (ignored in linear fog)
        // TODO: Comment me
        bool fogPixel = false; // false for vertex based fog true for pixel fog (for the sake of our shader (pixel shader) this is irrelevant
        // TODO: Comment me
        bool fogRange = false; // Ignore this parameter it is not cross platform
        // Get Information about the fog
        this->pVideoDriver->getFog(fogColour, fogType, fogStart, fogEnd, fogDensity, fogPixel, fogRange);
        // Array for the shadow colour
        float fogColourArray[4] = {(float)fogColour.getRed() / 255.0f, (float)fogColour.getGreen() / 255.0f, (float)fogColour.getBlue() / 255.0f, (float)fogColour.getAlpha() / 255.0f };
        // Set vertex shader's AmbientLight
        pServices->setVertexShaderConstant("FogColor", reinterpret_cast<irr::f32*>(&shadowColourArray[0]), 4);
        // Set pxiel shader's AmbientLight
        pServices->setPixelShaderConstant("FogColor", reinterpret_cast<irr::f32*>(&shadowColourArray[0]), 4);
        // Set the vertex shader's timer
        pServices->setVertexShaderConstant("FogStart", reinterpret_cast<irr::f32*>(&fogStart), 1);
        // Set the pixel shader's timer
        pServices->setPixelShaderConstant("FogStart", reinterpret_cast<irr::f32*>(&fogStart), 1);
        // Set the vertex shader's timer
        pServices->setVertexShaderConstant("FogEnd", reinterpret_cast<irr::f32*>(&fogEnd), 1);
        // Set the pixel shader's timer
        pServices->setPixelShaderConstant("FogEnd", reinterpret_cast<irr::f32*>(&fogEnd), 1);
        // Set the vertex shader's timer
        pServices->setVertexShaderConstant("FogDensity", reinterpret_cast<irr::f32*>(&fogDensity), 1);
        // Set the pixel shader's timer
        pServices->setPixelShaderConstant("FogDensity", reinterpret_cast<irr::f32*>(&fogDensity), 1);
    // 8888888888888 Work in progress - End 888888888888888888

    // DO DIRECTIONAL LIGHTS
    // Get the DirectionalLightCount
    int directionalLightCount = this->directionalLights.size();
    // Set Directional Light Count for the Vertex Shader
    pServices->setVertexShaderConstant("DirectionalLightCount", &directionalLightCount, 1);
    // Set Directional Light Count for the Pixel Shader
    pServices->setPixelShaderConstant("DirectionalLightCount", &directionalLightCount, 1);
    // Make a container for the DirectionalLightDirections
    float DirectionalLightDirectionArray[3 * 25];
    // Make a container for the DirectionalLightColor
    float DirectionalLightColorArray[3 * 25];
    // Make the list of point lights for the scene node
    for (int i = 0; i < directionalLightCount; i++)
    {
        // Get a light from the list
        irr::scene::ILightSceneNode* pLightSceneNode = this->directionalLights.at(i);
        irr::core::matrix4 matrix = pLightSceneNode->getAbsoluteTransformation();
        irr::core::vector3df directionVector = irr::core::vector3df(0.0f, 0.0f, 1.0f);
        matrix.rotateVect(directionVector);
        // Build DirectionalLightDirectionArray
        DirectionalLightDirectionArray[3 * i + 0] = directionVector.X;
        DirectionalLightDirectionArray[3 * i + 1] = directionVector.Y;
        DirectionalLightDirectionArray[3 * i + 2] = directionVector.Z;
        // Build DirectionalLightColorArray
        DirectionalLightColorArray[3 * i + 0] = pLightSceneNode->getLightData().DiffuseColor.r;
        DirectionalLightColorArray[3 * i + 1] = pLightSceneNode->getLightData().DiffuseColor.g;
        DirectionalLightColorArray[3 * i + 2] = pLightSceneNode->getLightData().DiffuseColor.b;
    }
    // Set the vertex Shader's Point Light Positions
    pServices->setVertexShaderConstant("DirectionalLightDirection[0]", reinterpret_cast<irr::f32*>(&DirectionalLightDirectionArray[0]), directionalLightCount * 3);
    // Set the pixel Shader's Point Light Positions
    pServices->setPixelShaderConstant("DirectionalLightDirection[0]", reinterpret_cast<irr::f32*>(&DirectionalLightDirectionArray[0]), directionalLightCount * 3);
    // Set the vertex Shader's Point Light Positions
    pServices->setVertexShaderConstant("DirectionalLightColor[0]", reinterpret_cast<irr::f32*>(&DirectionalLightColorArray[0]), directionalLightCount * 3);
    // Set the pixel Shader's Point Light Positions
    pServices->setPixelShaderConstant("DirectionalLightColor[0]", reinterpret_cast<irr::f32*>(&DirectionalLightColorArray[0]), directionalLightCount * 3);
    // DO POINT LIGHTS
    // Get the PointLightCount
    int pointLightCount = this->pointLights.size();
    // Set Point Light Count for the Vertex Shader
    pServices->setVertexShaderConstant("PointLightCount", &pointLightCount, 1);
    // Set Point Light Count for the Pixel Shader
    pServices->setPixelShaderConstant("PointLightCount", &pointLightCount, 1);
    // Make a container for the PointLightPositions
    float PointLightPositionArray[3 * 50];
    // Make a container for the PointLight DiffuseColors
    float PointLightDiffuseArray [3 * 50];
    // Make a container for the PointLightAttenuation
    float PointLightAttenuationArray[3 * 50];
    // Make the list of point lights for the scene node
    for (int i = 0; i < pointLightCount; i++)
    {
        // Get a light from the list
        irr::scene::ILightSceneNode* pLightSceneNode = this->pointLights.at(i);
        // Build the PointLightPositionArray
        PointLightPositionArray[3 * i + 0] = pLightSceneNode->getPosition().X;
        PointLightPositionArray[3 * i + 1] = pLightSceneNode->getPosition().Y;
        PointLightPositionArray[3 * i + 2] = pLightSceneNode->getPosition().Z;
        //PointLightPositionArray[4 * i + 3] = 1.0f;
        //std::cout << "LightPosition" << "(" << PointLightPositionArray[4 * i + 0] << ", " << PointLightPositionArray[4 * i + 1] << ", " << PointLightPositionArray[4 * i + 2] << std::endl;
        //// Build the PointAmbientLightArray
        //PointLightAmbientArray[4 * i + 0] = pLightSceneNode->getLightData().AmbientColor.r;
        //PointLightAmbientArray[4 * i + 1] = pLightSceneNode->getLightData().AmbientColor.g;
        //PointLightAmbientArray[4 * i + 2] = pLightSceneNode->getLightData().AmbientColor.b;
        //PointLightAmbientArray[4 * i + 3] = 1.0f;
        //std::cout << "AmbientLight" << "(" << pPointLightAmbientArray[4 * i + 0] << ", " << pPointLightAmbientArray[4 * i + 1] << ", " << pPointLightAmbientArray[4 * i + 2] << std::endl;
        // Build the PointLightSpecularArray
        PointLightDiffuseArray[3 * i + 0] = pLightSceneNode->getLightData().DiffuseColor.r;
        PointLightDiffuseArray[3 * i + 1] = pLightSceneNode->getLightData().DiffuseColor.g;
        PointLightDiffuseArray[3 * i + 2] = pLightSceneNode->getLightData().DiffuseColor.b;
        //PointLightDiffuseArray[4 * i + 3] = 1.0f;
        //std::cout << "DiffuseLight" << "(" << pPointLightDiffuseArray[4 * i + 0] << ", " << pPointLightDiffuseArray[4 * i + 1] << ", " << pPointLightDiffuseArray[4 * i + 2] << std::endl;
        //// Build the PointLightSpecularArray
        //PointLightSpecularArray[4 * i + 0] = pLightSceneNode->getLightData().SpecularColor.r;
        //PointLightSpecularArray[4 * i + 1] = pLightSceneNode->getLightData().SpecularColor.g;
        //PointLightSpecularArray[4 * i + 2] = pLightSceneNode->getLightData().SpecularColor.b;
        //PointLightSpecularArray[4 * i + 3] = 1.0f;
        //std::cout << "SpecularLight" << "(" << pPointLightSpecularArray[4 * i + 0] << ", " << pPointLightSpecularArray[4 * i + 1] << ", " << pPointLightSpecularArray[4 * i + 2] << std::endl;\
        // Build the Attenuation Array
        PointLightAttenuationArray[3 * i + 0] = pLightSceneNode->getLightData().Attenuation.X; // Constant Attenuation
        PointLightAttenuationArray[3 * i + 1] = pLightSceneNode->getLightData().Attenuation.Y; // Linear Attenuation
        PointLightAttenuationArray[3 * i + 2] = pLightSceneNode->getLightData().Attenuation.Z; // Quadratic Attenuation
    }
    // Set the vertex Shader's Point Light Positions
    pServices->setVertexShaderConstant("PointLightPosition[0]", reinterpret_cast<irr::f32*>(&PointLightPositionArray[0]), pointLightCount * 3);
    // Set the pixel Shader's Point Light Positions
    pServices->setPixelShaderConstant("PointLightPosition[0]", reinterpret_cast<irr::f32*>(&PointLightPositionArray[0]), pointLightCount * 3);
    //// Set the vertex Shader's Point Light Ambient Colors
    //pServices->setVertexShaderConstant("PointLightAmbientColor[0]", reinterpret_cast<irr::f32*>(&PointLightAmbientArray[0]), pointLightCount * 4);
    //// Set the pixel Shader's Point Light Positions
    //pServices->setPixelShaderConstant("PointLightAmbientColor[0]", reinterpret_cast<irr::f32*>(&PointLightAmbientArray[0]), pointLightCount * 4);
    // Set the vertex Shader's Point Light Diffuse Colors
    pServices->setVertexShaderConstant("PointLightDiffuseColor[0]", reinterpret_cast<irr::f32*>(&PointLightDiffuseArray[0]), pointLightCount * 3);
    // Set the pixel Shader's Point Light Positions
    pServices->setPixelShaderConstant("PointLightDiffuseColor[0]", reinterpret_cast<irr::f32*>(&PointLightDiffuseArray[0]), pointLightCount * 3);
    //// Set the vertex Shader's Point Light Specular Colors
    //pServices->setVertexShaderConstant("PointLightSpecularColor[0]", reinterpret_cast<irr::f32*>(&PointLightSpecularArray[0]), pointLightCount * 4);
    //// Set the pixel Shader's Point Light Specular Colors
    //pServices->setPixelShaderConstant("PointLightSpecularColor[0]", reinterpret_cast<irr::f32*>(&PointLightSpecularArray[0]), pointLightCount * 4);
    // Set the vertex Shader's Point Light Specular Colors
    pServices->setVertexShaderConstant("PointLightAttenuation[0]", reinterpret_cast<irr::f32*>(&PointLightAttenuationArray[0]), pointLightCount * 3);
    // Set the pixel Shader's Point Light Specular Colors
    pServices->setPixelShaderConstant("PointLightAttenuation[0]", reinterpret_cast<irr::f32*>(&PointLightAttenuationArray[0]), pointLightCount * 3);
    // DO SPOT LIGHTS
    // Get the SpotLightCount
    int spotLightCount = this->spotLights.size();
    //std::cout << "spotLightCount: " << spotLightCount << std::endl;
    // Set Spot Light Count for the Vertex Shader
    pServices->setVertexShaderConstant("SpotLightCount", &spotLightCount, 1);
    // Set Spot Light Count for the Pixel Shader
    pServices->setPixelShaderConstant("SpotLightCount", &spotLightCount, 1);
    // Make a container for the SpotLightPositions
    float SpotLightPositionArray[3 * 25];
    // Make a container for the SpotLightDirections
    float SpotLightDirectionArray[3 * 25];
    //// Make a container for the SpotLightAmbientColors
    //float SpotLightAmbientArray[4 * 25];
    // Make a container for the SpotLightDiffuseColors
    float SpotLightDiffuseArray[3 * 25];
    //// Make a container for the SpotLightSpecularColors
    //float SpotLightSpecularArray[4 * 25];
    // Make a container for the SpotLightAttenuations
    float SpotLightAttenuationArray[3 * 25];
    // Make a container for the Inner Cones
    float SpotLightInnerCone[25];
    // Make a container for the Outer Cones
    float SpotLightOuterCone[25];
    // Make a container for the Falloffs
    float SpotLightFalloff[25];
    //std::cout << "spotLightCount: " << spotLightCount << std::endl;
    // Make the list of spot lights for the scene node
    for (int i = 0; i < spotLightCount; i++)
    {
        irr::scene::ILightSceneNode* pLightSceneNode = this->spotLights.at(i);
        // Build the SpotLightPositionArray
        SpotLightPositionArray[i * 3 + 0] = pLightSceneNode->getPosition().X;
        SpotLightPositionArray[i * 3 + 1] = pLightSceneNode->getPosition().Y;
        SpotLightPositionArray[i * 3 + 2] = pLightSceneNode->getPosition().Z;
        // Build the SpotLightDirectionArray
        irr::core::matrix4 matrix = pLightSceneNode->getAbsoluteTransformation();
        irr::core::vector3df directionVector = irr::core::vector3df(0.0f, 0.0f, 1.0f);
        matrix.rotateVect(directionVector);
        SpotLightDirectionArray[i * 3 + 0] = directionVector.X;
        SpotLightDirectionArray[i * 3 + 1] = directionVector.Y;
        SpotLightDirectionArray[i * 3 + 2] = directionVector.Z;
        //// Build the SpotAmbientLightArray
        //SpotLightAmbientArray[4 * i + 0] = pLightSceneNode->getLightData().AmbientColor.r;
        //SpotLightAmbientArray[4 * i + 1] = pLightSceneNode->getLightData().AmbientColor.g;
        //SpotLightAmbientArray[4 * i + 2] = pLightSceneNode->getLightData().AmbientColor.b;
        //SpotLightAmbientArray[4 * i + 3] = 1.0f;
        // Build the SpotLightSpecularArray
        SpotLightDiffuseArray[3 * i + 0] = pLightSceneNode->getLightData().DiffuseColor.r;
        SpotLightDiffuseArray[3 * i + 1] = pLightSceneNode->getLightData().DiffuseColor.g;
        SpotLightDiffuseArray[3 * i + 2] = pLightSceneNode->getLightData().DiffuseColor.b;
        //// Build the SpotLightSpecularArray
        //SpotLightSpecularArray[4 * i + 0] = pLightSceneNode->getLightData().SpecularColor.r;
        //SpotLightSpecularArray[4 * i + 1] = pLightSceneNode->getLightData().SpecularColor.g;
        //SpotLightSpecularArray[4 * i + 2] = pLightSceneNode->getLightData().SpecularColor.b;
        //SpotLightSpecularArray[4 * i + 3] = 1.0f;
        // Build the Attenuation Array
        SpotLightAttenuationArray[3 * i + 0] = pLightSceneNode->getLightData().Attenuation.X; // Constant Attenuation
        SpotLightAttenuationArray[3 * i + 1] = pLightSceneNode->getLightData().Attenuation.Y; // Linear Attenuation
        SpotLightAttenuationArray[3 * i + 2] = pLightSceneNode->getLightData().Attenuation.Z; // Quadratic Attenuation
        // Build the InnerConeArray
        SpotLightInnerCone[i] = pLightSceneNode->getLightData().InnerCone * M_PI / 180.0f;
        // Build the OuterConeArray
        SpotLightOuterCone[i] = pLightSceneNode->getLightData().OuterCone * M_PI / 180.0f;
        // Build the FalloffArray
        SpotLightFalloff[i] = pLightSceneNode->getLightData().Falloff;
    }
    // Set the vertex Shader's Spot Light Positions
    pServices->setVertexShaderConstant("SpotLightPosition[0]", reinterpret_cast<irr::f32*>(&SpotLightPositionArray[0]), spotLightCount * 3);
    // Set the pixel Shader's Spot Light Positions
    pServices->setPixelShaderConstant("SpotLightPosition[0]", reinterpret_cast<irr::f32*>(&SpotLightPositionArray[0]), spotLightCount * 3);
    // Set the vertex Shader's Spot Light Directions
    pServices->setVertexShaderConstant("SpotLightDirection[0]", reinterpret_cast<irr::f32*>(&SpotLightDirectionArray[0]), spotLightCount * 3);
    // Set the pixel Shader's Spot Light Directions
    pServices->setPixelShaderConstant("SpotLightDirection[0]", reinterpret_cast<irr::f32*>(&SpotLightDirectionArray[0]), spotLightCount * 3);
//            // Set the vertex Shader's Spot Light Ambient Colors
//            pServices->setVertexShaderConstant("SpotLightAmbientColor[0]", reinterpret_cast<irr::f32*>(&SpotLightAmbientArray[0]), spotLightCount * 4);
//            // Set the pixel Shader's Spot Light Positions
//            pServices->setPixelShaderConstant("SpotLightAmbientColor[0]", reinterpret_cast<irr::f32*>(&SpotLightAmbientArray[0]), spotLightCount * 4);
    // Set the vertex Shader's Spot Light Diffuse Colors
    pServices->setVertexShaderConstant("SpotLightDiffuseColor[0]", reinterpret_cast<irr::f32*>(&SpotLightDiffuseArray[0]), spotLightCount * 3);
    // Set the pixel Shader's Spot Light Positions
    pServices->setPixelShaderConstant("SpotLightDiffuseColor[0]", reinterpret_cast<irr::f32*>(&SpotLightDiffuseArray[0]), spotLightCount * 3);
//            // Set the vertex Shader's Spot Light Specular Colors
//            pServices->setVertexShaderConstant("SpotLightSpecularColor[0]", reinterpret_cast<irr::f32*>(&SpotLightSpecularArray[0]), spotLightCount * 4);
//            // Set the pixel Shader's Spot Light Specular Colors
//            pServices->setPixelShaderConstant("SpotLightSpecularColor[0]", reinterpret_cast<irr::f32*>(&SpotLightSpecularArray[0]), spotLightCount * 4);
    //bool results = false;
    // Set the vertex Shader's Spot Light Specular Colors
    pServices->setVertexShaderConstant("SpotLightAttenuation[0]", reinterpret_cast<irr::f32*>(&SpotLightAttenuationArray[0]), spotLightCount * 3);
    //std::cout << ((results == true) ? "TRUE" : "FALSE") << std::endl;
    // Set the pixel Shader's Spot Light Specular Colors
    pServices->setPixelShaderConstant("SpotLightAttenuation[0]", reinterpret_cast<irr::f32*>(&SpotLightAttenuationArray[0]), spotLightCount * 3);
    // Set the vertex shader's Spot Light Inner Cones
    pServices->setVertexShaderConstant("SpotLightInnerCone[0]", reinterpret_cast<irr::f32*>(&SpotLightInnerCone[0]), spotLightCount);
    // Set the pixel shader's Spot Light Inner Cones
    pServices->setPixelShaderConstant("SpotLightInnerCone[0]", reinterpret_cast<irr::f32*>(&SpotLightInnerCone[0]), spotLightCount);
    // Set the vertex shader's Spot Light Outer Cones
    pServices->setVertexShaderConstant("SpotLightOuterCone[0]", reinterpret_cast<irr::f32*>(&SpotLightOuterCone[0]), spotLightCount);
    // Set the pixel shader's Spot Light Outer Cones
    pServices->setPixelShaderConstant("SpotLightOuterCone[0]", reinterpret_cast<irr::f32*>(&SpotLightOuterCone[0]), spotLightCount);
    // Set the vertex shader's Spot Light Falloffs
    pServices->setVertexShaderConstant("SpotLightFalloff[0]", reinterpret_cast<irr::f32*>(&SpotLightFalloff[0]), spotLightCount);
    // Set the pixel shader's Spot Light Falloffs
    pServices->setPixelShaderConstant("SpotLightFalloff[0]", reinterpret_cast<irr::f32*>(&SpotLightFalloff[0]), spotLightCount);
}

void Game::mouseGUIEvent(const irr::SEvent& event)
{
    // HANDLE GUI EVENTS
}

void Game::mouseEvent(const irr::SEvent& event)
{
    // HANDLE MOUSE EVENTS

    if(event.MouseInput.Event == irr::EMIE_MOUSE_WHEEL)
    {
        if(event.MouseInput.Wheel > 0.0f)
        {

        }
        if(event.MouseInput.Wheel < 0.0f)
        {

        }
    }

    if(event.MouseInput.Event == irr::EMIE_RMOUSE_PRESSED_DOWN)
    {

    }

    if(event.MouseInput.Event == irr::EMIE_RMOUSE_LEFT_UP)
    {

    }
}

void Game::keyboardEvent(const irr::SEvent& event)
{
    // HANDLE KEYBOARD EVENTS

    // if a key down event takes place - only one per key press
    if (event.KeyInput.PressedDown)
    {
        switch(event.KeyInput.Key)
        {
            case irr::KEY_ESCAPE:
            {
                this->pIrrlichtDevice->closeDevice();
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

void Game::OnPreRender(irr::core::array<irr::scene::ISceneNode*>& lightList)
{
    /* NOTES:
        - Can use this callback to exclude lights that are a certain distance away from the camera
        - This is where I should search some form of quadtree datastructure to exlude certain lights
        - Only add lights to the list if they are visible
    */
    // Ambient Light Magnitude
    float ambientLightMagnitude = sqrt(this->pIrrlichtDevice->getSceneManager()->getAmbientLight().r * this->pIrrlichtDevice->getSceneManager()->getAmbientLight().r + this->pIrrlichtDevice->getSceneManager()->getAmbientLight().g * this->pIrrlichtDevice->getSceneManager()->getAmbientLight().g + this->pIrrlichtDevice->getSceneManager()->getAmbientLight().b * this->pIrrlichtDevice->getSceneManager()->getAmbientLight().b);
    // Clear the list of directional lights
    this->directionalLights.clear();
    // Clear the list of point lights
    this->pointLights.clear();
    // Clear the list of spot lights
    this->spotLights.clear();
    // Grab the Camera
    irr::scene::ICameraSceneNode* pCamera = this->pIrrlichtDevice->getSceneManager()->getActiveCamera();
    // There must be a camera
    if (pCamera == 0) return;
    // TODO: Only include lights which are infront of the Camera (that is visible to the cameras Frustrum
    // Build the list of light sources
    for (int i = 0; i < lightList.size(); i++)
    {
        // Grab a light
        irr::scene::ILightSceneNode* pLightSceneNode = (irr::scene::ILightSceneNode*)lightList[i];
        // Now lets build lists of lights based on type
        switch (pLightSceneNode->getLightType())
        {
            case irr::video::ELT_DIRECTIONAL:
            {
                this->directionalLights.push_back(pLightSceneNode);
                break;
            }
            case irr::video::ELT_POINT:
            {
                this->pointLights.push_back(pLightSceneNode);
                break;
            }
            case irr::video::ELT_SPOT:
            {
                this->spotLights.push_back(pLightSceneNode);
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

void Game::OnPostRender()
{

}

void Game::OnRenderPassPreRender(irr::scene::E_SCENE_NODE_RENDER_PASS renderPass)
{
    // Nothing needs to be done for each pass
}

void Game::OnRenderPassPostRender(irr::scene::E_SCENE_NODE_RENDER_PASS renderPass)
{
    // Nothing needs to be done after each pass
}

void Game::OnNodePreRender(irr::scene::ISceneNode* node)
{
    /* NOTES: Produce a list of lights within distance of this node and
        Find lights within boundaries of the camera (if this wasn't done in the
        'virtual void OnPreRender(irr::core::array<irr::scene::ISceneNode*>& lightList)' callback

        VERY IMPORTANT: The list is passed to the shader!!!
        */

    // 88888 As a test lets just pass in all the lights work in progress as I'd like to do some culling

    // Make the list of directional lights for the scene node
    for (std::vector<irr::scene::ILightSceneNode*>::iterator i = this->directionalLights.begin(); i != this->directionalLights.end(); i++)
    {
        irr::scene::ILightSceneNode* pLightSceneNode = *i;
        this->tempDirectionalLights.push_back(pLightSceneNode);
    }
    // Make the list of point lights for the scene node
    for (std::vector<irr::scene::ILightSceneNode*>::iterator i = this->pointLights.begin(); i != this->pointLights.end(); i++)
    {
        irr::scene::ILightSceneNode* pLightSceneNode = *i;
        this->tempPointLights.push_back(pLightSceneNode);
    }
    // Make the list of spot lights for the scene node
    for (std::vector<irr::scene::ILightSceneNode*>::iterator i = this->spotLights.begin(); i != this->spotLights.end(); i++)
    {
        irr::scene::ILightSceneNode* pLightSceneNode = *i;
        this->tempSpotLights.push_back(pLightSceneNode);
    }
    // 88888
}

void Game::OnNodePostRender(irr::scene::ISceneNode* node)
{
    // Clear the list of lights used when rendering this scene node
    this->tempDirectionalLights.clear();
    this->tempPointLights.clear();
    this->tempSpotLights.clear();
}

irr::s32 Game::loadShader(std::string vertexShader, std::string fragmentShader)
{
    // Load a shader
    irr::s32 shaderHandle = pGPUProgrammingServices->addHighLevelShaderMaterialFromFiles(vertexShader.c_str(), "main", irr::video::EVST_VS_1_1,
                                                                                            fragmentShader.c_str(), "main", irr::video::EPST_PS_1_1,
                                                                                            this, irr::video::EMT_SOLID, irr::video::EGSL_DEFAULT);
    // If there was a problem send an error to the log
    if (shaderHandle == -1)
    {
        // Send Error Message to the console
        std::cout << "ERROR: Unable to load " << vertexShader << " " << fragmentShader << std::endl;
    }

    // Return shader handle or -1 if error
    return shaderHandle;
}
