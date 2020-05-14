#pragma once

//for use by JSEngin applications 
#include "JSEngine/Application.h"
#include "JSEngine/Core/LayerStack.h"
#include "JSEngine/Core/Layer.h"


//----------------Graphics---------------------
#include "JSEngine/Graphics/Renderer.h"
#include "JSEngine/Graphics/RenderCommand.h"
#include "JSEngine/Graphics/RendererAPI.h"
#include "JSEngine/Graphics/Shader.h"
#include "JSEngine/Graphics/Camera.h"
#include "JSEngine/Graphics/Meterial.h"
#include "JSEngine/Graphics/SubTexture2D.h"
#include "JSEngine/Graphics/Animation.h"
#include "JSEngine/Platform/CameraController.h"
#include "JSEngine/Platform/Opengl/Mesh.h"
#include "JSEngine/Platform/Opengl/Light.h"
//--------------------------------------------

//----------------Physics---------------------
#include "JSEngine/Physics/Physics2D.h"
#include "JSEngine/Physics/Box2D.h"
//--------------------------------------------


//----------------Resources---------------------
#include "JSEngine/Managers/ResourceManager.h"
//--------------------------------------------

//-------------- --UI---------------------
#include "JSEngine/imGui/imguiLayer.h"
#include "imgui.h"
#include "imconfig.h"
//----------------------------------------------

//--------------Event---------------------
#include "JSEngine/Event/Event.h"
#include "JSEngine/Event/ApplicationEvent.h"
#include "JSEngine/Event/KeyEvent.h"
#include "JSEngine/Event/MouseEvent.h"
//----------------------------------------------

//--------------Logging---------------------
#include "JSEngine/Core/Log.h"
//----------------------------------------------

//--------------Debug---------------------------
#include "JSEngine/Debug/SimpleProfiler.h"
//--------------------------------------------


//--------------Input---------------------
#include "JSEngine/Managers/InputManager.h"
//----------------------------------------------

//--------------Math--------------------------
#include "JSEngine/Math/Random.h"
#include <math.h>
//----------------------------------------------





