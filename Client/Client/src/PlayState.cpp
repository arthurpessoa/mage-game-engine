#include "stdafx.h"
#include "PlayState.hpp"

using namespace Ogre;


PlayState::PlayState()
{
    m_MoveSpeed			= 0.1f;
    m_RotateSpeed		= 0.3f;

    m_bLMouseDown       = false;
    m_bRMouseDown       = false;
    m_bQuit             = false;
    m_bSettingsMode     = false;

    m_pDetailsPanel		= 0;
}

void PlayState::enter()
{
    Core::getSingletonPtr()->mLog->logMessage("Entering GameState...");

    mSceneManager = Core::getSingletonPtr()->mRoot->createSceneManager(ST_GENERIC, "GameSceneMgr");
    mSceneManager->setAmbientLight(Ogre::ColourValue(0.7f, 0.7f, 0.7f));

    mSceneManager->addRenderQueueListener(Core::getSingletonPtr()->mOverlaySystem);

    m_pRSQ = mSceneManager->createRayQuery(Ray());
    m_pRSQ->setQueryMask(OGRE_HEAD_MASK);

    mCamera = mSceneManager->createCamera("GameCamera");
    mCamera->setPosition(Vector3(5, 60, 60));
    mCamera->lookAt(Vector3(5, 20, 0));
    mCamera->setNearClipDistance(5);

    mCamera->setAspectRatio(Real(Core::getSingletonPtr()->mViewport->getActualWidth()) /
        Real(Core::getSingletonPtr()->mViewport->getActualHeight()));

    Core::getSingletonPtr()->mViewport->setCamera(mCamera);
    m_pCurrentObject = 0;

    buildGUI();

    createScene();
}

bool PlayState::pause()
{
    Core::getSingletonPtr()->mLog->logMessage("Pausing GameState...");

    return true;
}

void PlayState::resume()
{
    Core::getSingletonPtr()->mLog->logMessage("Resuming GameState...");

    buildGUI();

    Core::getSingletonPtr()->mViewport->setCamera(mCamera);
    m_bQuit = false;
}

void PlayState::exit()
{
    Core::getSingletonPtr()->mLog->logMessage("Leaving GameState...");

    mSceneManager->destroyCamera(mCamera);
    mSceneManager->destroyQuery(m_pRSQ);
    if(mSceneManager)
        Core::getSingletonPtr()->mRoot->destroySceneManager(mSceneManager);
}


void PlayState::createScene()
{
    mSceneManager->createLight("Light")->setPosition(75,75,75);

    DotSceneLoader* pDotSceneLoader = new DotSceneLoader();
    pDotSceneLoader->parseDotScene("CubeScene.xml", "General", mSceneManager, mSceneManager->getRootSceneNode());
    delete pDotSceneLoader;

    mSceneManager->getEntity("Cube01")->setQueryFlags(CUBE_MASK);
    mSceneManager->getEntity("Cube02")->setQueryFlags(CUBE_MASK);
    mSceneManager->getEntity("Cube03")->setQueryFlags(CUBE_MASK);

    m_pOgreHeadEntity = mSceneManager->createEntity("OgreHeadEntity", "ogrehead.mesh");
    m_pOgreHeadEntity->setQueryFlags(OGRE_HEAD_MASK);
    m_pOgreHeadNode = mSceneManager->getRootSceneNode()->createChildSceneNode("OgreHeadNode");
    m_pOgreHeadNode->attachObject(m_pOgreHeadEntity);
    m_pOgreHeadNode->setPosition(Vector3(0, 0, -25));

    m_pOgreHeadMat = m_pOgreHeadEntity->getSubEntity(1)->getMaterial();
    m_pOgreHeadMatHigh = m_pOgreHeadMat->clone("OgreHeadMatHigh");
    m_pOgreHeadMatHigh->getTechnique(0)->getPass(0)->setAmbient(1, 0, 0);
    m_pOgreHeadMatHigh->getTechnique(0)->getPass(0)->setDiffuse(1, 0, 0, 0);
}


bool PlayState::keyPressed(const OIS::KeyEvent &keyEventRef)
{
    return true;
}

bool PlayState::keyReleased(const OIS::KeyEvent &keyEventRef)
{
    Core::getSingletonPtr()->keyPressed(keyEventRef);
    return true;
}

bool PlayState::mouseMoved(const OIS::MouseEvent &evt)
{
    
    return true;
}

bool PlayState::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    return true;
}

bool PlayState::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    return true;
}

void PlayState::onLeftPressed(const OIS::MouseEvent &evt)
{
    if(m_pCurrentObject)
    {
        m_pCurrentObject->showBoundingBox(false);
        m_pCurrentEntity->getSubEntity(1)->setMaterial(m_pOgreHeadMat);
    }

    Ogre::Ray mouseRay = mCamera->getCameraToViewportRay(Core::getSingletonPtr()->mMouse->getMouseState().X.abs / float(evt.state.width),
        Core::getSingletonPtr()->mMouse->getMouseState().Y.abs / float(evt.state.height));
    m_pRSQ->setRay(mouseRay);
    m_pRSQ->setSortByDistance(true);

    Ogre::RaySceneQueryResult &result = m_pRSQ->execute();
    Ogre::RaySceneQueryResult::iterator itr;

    for(itr = result.begin(); itr != result.end(); itr++)
    {
        if(itr->movable)
        {
            Core::getSingletonPtr()->mLog->logMessage("MovableName: " + itr->movable->getName());
            m_pCurrentObject = mSceneManager->getEntity(itr->movable->getName())->getParentSceneNode();
            Core::getSingletonPtr()->mLog->logMessage("ObjName " + m_pCurrentObject->getName());
            m_pCurrentObject->showBoundingBox(true);
            m_pCurrentEntity = mSceneManager->getEntity(itr->movable->getName());
            m_pCurrentEntity->getSubEntity(1)->setMaterial(m_pOgreHeadMatHigh);
            break;
        }
    }
}

void PlayState::moveCamera()
{
    if(Core::getSingletonPtr()->mKeyboard->isKeyDown(OIS::KC_LSHIFT))
        mCamera->moveRelative(m_TranslateVector);
    mCamera->moveRelative(m_TranslateVector / 10);
}


void PlayState::getInput()
{
    if(m_bSettingsMode == false)
    {
        if(Core::getSingletonPtr()->mKeyboard->isKeyDown(OIS::KC_A))
            m_TranslateVector.x = -m_MoveScale;

        if(Core::getSingletonPtr()->mKeyboard->isKeyDown(OIS::KC_D))
            m_TranslateVector.x = m_MoveScale;

        if(Core::getSingletonPtr()->mKeyboard->isKeyDown(OIS::KC_W))
            m_TranslateVector.z = -m_MoveScale;

        if(Core::getSingletonPtr()->mKeyboard->isKeyDown(OIS::KC_S))
            m_TranslateVector.z = m_MoveScale;
    }
}

void PlayState::update(double timeSinceLastFrame)
{
 
}


void PlayState::buildGUI()
{
}


void PlayState::itemSelected(OgreBites::SelectMenu* menu)
{
    switch(menu->getSelectionIndex())
    {
    case 0:
        mCamera->setPolygonMode(Ogre::PM_SOLID);break;
    case 1:
        mCamera->setPolygonMode(Ogre::PM_WIREFRAME);break;
    case 2:
        mCamera->setPolygonMode(Ogre::PM_POINTS);break;
    }
}