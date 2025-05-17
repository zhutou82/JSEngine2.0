# JSEngine2.0
Update the Engine Structure from JSEnigne1.0, there are two layers (2D Layer and 3D Layer) being created from this Engine.

2D Layer: A simple physics and particle simulation scene, including basic camera movement and interactivity with ImGui-powered control.

3D Layer: A basic rendering scene with dynamic lighting, Textured models, ImGui-powered entity control, and transform manipulation. Includes directional and point light support for real-time lighting effects.

Checkout:
git clone --recursive https://github.com/zhutou82/JSEngine2.0.git

To generate SLN:
Double click "GenerateProject.bat" (but this is running for visual studio 2019, you might need to retarget the SLN)

To start:
Under SandBox.cpp
- Uncomment "PushLayer(new Game2DLayer())" to run 2D world
  * Controls:
      WSAD - to move the camera
      Left Mouse Click - emit particles
      Mouse scroll - zoom in/out camera
  * UI (hold left mouse on the value and drag)
      Adjust Particle properties to set the size and lifetime
  

- Uncomment "PushLayer(new Game3DLayer());" to run 3D world
  * Controls:
	   Alt + Left Mouse Click - rotate camera
	   Mouse scroll - zoom in/out camera
  * UI (hold left mouse on the value and drag)
      Adjust Light properties to adjust the directional light direction
	  Adjust Mesh properties to move the objects around
