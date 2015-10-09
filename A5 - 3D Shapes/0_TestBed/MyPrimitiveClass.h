/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) 02/22/2015
--------------------------------------------------------------------------------------------------*/
#ifndef __MYPRIMITIVECLASS_H_
#define __MYPRIMITIVECLASS_H_

#include "ME\Mesh\MeshClass.h"

using namespace MyEngine;

class MyPrimitiveClass : public MeshClass
{
	typedef MeshClass super;

public:
	/* Constructor */
	MyPrimitiveClass();
	/* Copy Constructor */
	MyPrimitiveClass(const MyPrimitiveClass& other);
	/* Copy Assignment Operator */
	virtual MyPrimitiveClass& operator=(const MyPrimitiveClass& other);

	/* Destructor */
	~MyPrimitiveClass(void);

	/* Generates a cube shape */
	void GenerateCube(float a_fSize, vector3 a_vColor);
	/* Generates a cone shape */
	void GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_vColor);
	/* Generates a cylinder shape */
	void GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_vColor);
	/* Generates a tube shape */
	void GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_vColor);
	/* Generates a Sphere shape */
	void GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_vColor);
	
	/* Renders the primitive asking for its rendering mode (default is GL_TRIANGLES)*/
	virtual void Render(void);
	/* Renders the primitive asking for the model matrix and the color */
	virtual void Render(matrix4 a_mModelMatrix, vector3 a_vColor = MEDEFAULT);
	/* Renders the primitive in wireframe mode asking for the model matrix and the color */
	virtual void RenderWire(matrix4 a_mModelMatrix, vector3 a_vColor = MEDEFAULT);

private:
	/* Compiles the object with an specific color and name */
	void CompileObject(vector3 a_vColor, String a_sName);
	/* Adds a quad to the list points in the buffer to be compiled*/
	void AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight);
};

#endif //__MYPRIMITIVECLASS_H_