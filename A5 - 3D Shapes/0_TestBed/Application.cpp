#include "ApplicationClass.h"
void ApplicationClass::InitAppVariables()
{
	// Create a new grid initializing its properties and compiling it
	m_pGrid = new GridClass(MEAXIS::XY | MEAXIS::YZ);
	m_pGrid->CompileGrid();

	m_m4Mesh = matrix4(IDENTITY);

	m_pMesh = new MyPrimitiveClass();
	//m_pMesh->GenerateCube( 1.0f, MERED);
	//m_pMesh->GenerateCone( 1.0f, 1.0f, 8, MEBLUE);
	//m_pMesh->GenerateCylinder( 1.0f, 2.0f, 8, MEGREEN); //originally 5
	m_pMesh->GenerateTube( 1.0f, 0.6f, 2.0f, 8, MERED); //INNER radius is 0.7f
	//m_pMesh->GenerateSphere( 1.0f, 6, MERED);
}
void ApplicationClass::Display (void) //for OpenGL 3.X Applications
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clear the window

	m_pGrid->Render(10.0f); //renders the grid with a 100 scale

	//Renders the mesh using the specified position given by the matrix and in the specified color
	m_pMesh->Render( m_m4Mesh );
	//m_pMesh->RenderWire( m_m4Mesh, MEBLACK);//Helpful to visualize but the buffer form for this line to work is different so its not accurate 

	m_pGLSystem->GLSwapBuffers(); //Swaps the opengl buffers
}