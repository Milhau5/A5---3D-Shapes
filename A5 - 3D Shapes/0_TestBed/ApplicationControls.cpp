#include "ApplicationClass.h"
void ApplicationClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.1f;

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		//To correctly terminate the application releasing memory
		PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL); 
		//exit(0); //will not terminate cleanly at this point
	}

	//Static flags to know if the key was pressed
	static bool bF1_WasPressed = false;
	static bool bF2_WasPressed = false;
	static bool bF3_WasPressed = false;
	static bool bF4_WasPressed = false;
	static bool bF5_WasPressed = false;


	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) bF1_WasPressed = true;
	else
	{
		//If the key is currently not pressed, but was pressed last cycle...
		if(bF1_WasPressed == true) m_pMesh->GenerateCube( 1.0f, MERED);
		bF1_WasPressed = false;//Set the flag back to false
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) bF2_WasPressed = true;
	else
	{
		if(bF2_WasPressed == true) m_pMesh->GenerateCone( 1.0f, 1.0f, 3, MEGREEN);
		bF2_WasPressed = false;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F3)) bF3_WasPressed = true;
	else
	{
		if(bF3_WasPressed == true) m_pMesh->GenerateCylinder( 1.0f, 2.0f, 5, MEBLUE);
		bF3_WasPressed = false;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) bF4_WasPressed = true;
	else
	{
		if(bF4_WasPressed == true) m_pMesh->GenerateTube( 1.0f, 0.7f, 2.0f, 6, MEYELLOW);
		bF4_WasPressed = false;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5)) bF5_WasPressed = true;
	else
	{
		if(bF5_WasPressed == true) m_pMesh->GenerateSphere( 1.0f, 3, MEBROWN);
		bF5_WasPressed = false;
	}

	//Modifiers
#pragma region Modifiers

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		fSpeed += 1.0f;
		bModifier = true;
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
	{
		fSpeed += 1.0f;
		bModifier = true;
	}
	
#pragma endregion

	//Model Positioning
#pragma region Model Positioning
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_m4Mesh = glm::translate( m_m4Mesh, vector3(-0.1f,0.0f,0.0f));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_m4Mesh = glm::translate( m_m4Mesh, vector3(0.1f,0.0f,0.0f));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if(bModifier)
			m_m4Mesh = glm::translate( m_m4Mesh, vector3(0.0f,-0.1f,0.0f));
		else
			m_m4Mesh = glm::translate( m_m4Mesh, vector3(0.0f,0.0f,-0.1f));
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if(bModifier)
			m_m4Mesh = glm::translate( m_m4Mesh, vector3(0.0f,0.1f,0.0f));
		else
			m_m4Mesh = glm::translate( m_m4Mesh, vector3(0.0f,0.0f,0.1f));
	}
#pragma endregion

	//Camera
#pragma region Camera
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_pCamera->MoveForward(fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pCamera->MoveForward(-fSpeed);
	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_pCamera->MoveSideways(-fSpeed);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pCamera->MoveSideways(fSpeed);
	m_pCamera->CalculateView();
#pragma endregion
}
void ApplicationClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;

	static bool bLeft_Released = false;
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		bLeft_Released = true;
	}
	else
	{
		if(bLeft_Released == true)
		{
		}
		bLeft_Released = false;
	}
}
void ApplicationClass::ProcessJoystick(void)
{
	sf::Joystick::update();

	int nPad = 0;
	if(sf::Joystick::isConnected(nPad))
	{
		if(sf::Joystick::isButtonPressed(nPad, 4) && sf::Joystick::isButtonPressed(nPad, 5))
			exit(0);

		static float fAngleX = 0.0f;
		static float fAngleY = 0.0f;

		if(sf::Joystick::isButtonPressed(nPad, 8) && sf::Joystick::isButtonPressed(nPad, 9))	
		{
			fAngleX = 0.0f;
			fAngleY = 0.0f;
			m_pCamera->SetPosition(glm::vec3( 0.0f, 0.0f, 10.0f));
		}

		float fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::Y);
		if(fDelta > 20 || fDelta < -20)
		{
			fDelta /= 1000.0f;
			m_pCamera->MoveForward(-fDelta);
		}
		
		fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::X);
		if(fDelta > 20 || fDelta < -20)
		{
			fDelta /= 1000.0f;
			m_pCamera->MoveSideways(fDelta);
		}

		fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::Z);
		if(fDelta > 20 || fDelta < -20)
		{
			fDelta /= 1000.0f;
			m_pCamera->MoveVertical(fDelta);
		}

		fDelta = -sf::Joystick::getAxisPosition(nPad, sf::Joystick::R);
		if(fDelta > 25 || fDelta < -25)
		{
			fAngleX -= fDelta/10000.0f;
		}
		
		fDelta = sf::Joystick::getAxisPosition(nPad, sf::Joystick::U);
		if(fDelta > 25 || fDelta < -25)
		{
			fAngleY -= fDelta/10000.0f;
		}

		m_pCamera->Rotate(fAngleX, fAngleY);
		m_pCamera->CalculateView();
		
	}
}
void ApplicationClass::CameraRotation(float a_fSpeed)
{
	UINT	MouseX, MouseY;		// Coordinates for the mouse
	UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

	CenterX = m_pSystem->WindowX + m_pSystem->WindowWidth / 2;
	CenterY = m_pSystem->WindowY + m_pSystem->WindowHeight / 2;
	
	float DeltaMouse;
	POINT pt;

	GetCursorPos(&pt);
	
	MouseX = pt.x;
	MouseY = pt.y;

	SetCursorPos(CenterX, CenterY);

	static float fAngleX = 0.0f;
	static float fAngleY = 0.0f;

	if(MouseX < CenterX)
	{
		DeltaMouse = static_cast<float>(CenterX - MouseX);
		fAngleY += DeltaMouse * a_fSpeed;
	}
	else if(MouseX > CenterX)
	{
		DeltaMouse = static_cast<float>(MouseX - CenterX);
		fAngleY -= DeltaMouse * a_fSpeed;
	}

	if(MouseY < CenterY)
	{
		DeltaMouse = static_cast<float>(CenterY - MouseY);
		fAngleX -= DeltaMouse * a_fSpeed;
	}
	else if(MouseY > CenterY)
	{
		DeltaMouse = static_cast<float>(MouseY - CenterY);
		fAngleX += DeltaMouse * a_fSpeed;
	}
	m_pCamera->Rotate(fAngleX, fAngleY);
}
void ApplicationClass::ArcBall(float a_fSensitivity)
{
	static matrix4 arcball = matrix4(1.0);
	UINT	MouseX, MouseY;		// Coordinates for the mouse
	UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

	CenterX = m_pSystem->WindowX + m_pSystem->WindowWidth / 2;
	CenterY = m_pSystem->WindowY + m_pSystem->WindowHeight / 2;
	
	float DeltaMouse;
	POINT pt;

	GetCursorPos(&pt);
	
	MouseX = pt.x;
	MouseY = pt.y;

	SetCursorPos(CenterX, CenterY);

	static float fVerticalAngle = 0.0f;
	static float fHorizontalAngle = 0.0f;

	float fSpeed = 0.001f;

	if(MouseX < CenterX)
	{
		DeltaMouse = static_cast<float>(CenterX - MouseX);
		arcball = glm::rotate(arcball, a_fSensitivity * DeltaMouse, vector3(0.0f, 1.0f, 0.0f));
	}
	else if(MouseX > CenterX)
	{
		DeltaMouse = static_cast<float>(MouseX - CenterX);
		arcball = glm::rotate(arcball, -a_fSensitivity * DeltaMouse, vector3(0.0f, 1.0f, 0.0f));
	}

	if(MouseY < CenterY)
	{
		DeltaMouse = static_cast<float>(CenterY - MouseY);
		arcball = glm::rotate(arcball, a_fSensitivity * DeltaMouse, vector3(1.0f, 0.0f, 0.0f));
	}
	else if(MouseY > CenterY)
	{
		DeltaMouse = static_cast<float>(MouseY - CenterY);
		arcball = glm::rotate(arcball, -a_fSensitivity * DeltaMouse, vector3(1.0f, 0.0f, 0.0f));
	}
	m_m4Mesh = arcball;
}