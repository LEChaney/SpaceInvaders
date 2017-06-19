//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "Clock.h"
#include "Level.h"
#include "BackBuffer.h"
#include "Utils.h"
#include "MainMenu.h"

// This Include
#include "Game.h"

// Static Variables
CGame* CGame::s_pGame = 0;

// Static Function Prototypes

// Implementation

CGame::CGame()
	: m_pLevel(0)
	, m_pClock(0)
	, m_hApplicationInstance(0)
	, m_hMainWindow(0)
	, m_pBackBuffer(0)
	, m_eCurrentLevel(LEVEL)
{

}

CGame::~CGame()
{
	delete m_pLevel;
	m_pLevel = 0;

	delete m_pBackBuffer;
	m_pBackBuffer = 0;

	delete m_pClock;
	m_pClock = 0;
}

bool
CGame::Initialise(HINSTANCE _hInstance, HWND _hWnd, int _iWidth, int _iHeight)
{
	m_hApplicationInstance = _hInstance;
	m_hMainWindow = _hWnd;

	m_pClock = new CClock();
	VALIDATE(m_pClock->Initialise());
	m_pClock->Process();

	m_pBackBuffer = new CBackBuffer();
	VALIDATE(m_pBackBuffer->Initialise(_hWnd, _iWidth, _iHeight));

	m_pLevel = new CLevel();
	VALIDATE(m_pLevel->Initialise(_iWidth, _iHeight));

	m_pMenu = &CMainMenu::GetInstance();
	VALIDATE(m_pMenu->Initialise(_iWidth, _iHeight, _hWnd));

	ShowCursor(false);

	return (true);
}

void
CGame::Draw()
{
	m_pBackBuffer->Clear();

	switch (m_eCurrentLevel)
	{
	case CGame::MENU:
		m_pMenu->Draw();
		break;
	case CGame::LEVEL:
		m_pLevel->Draw();
		break;
	case CGame::GAMEOVER:
		break;
	default:
		break;
	}

	m_pBackBuffer->Present();
}

void
CGame::Process(float _fDeltaTick)
{
	switch (m_eCurrentLevel)
	{
	case CGame::MENU:
		m_pMenu->Process(_fDeltaTick);
		break;
	case CGame::LEVEL:
		m_pLevel->Process(_fDeltaTick);
		break;
	case CGame::GAMEOVER:
		break;
	default:
		break;
	}
}

void
CGame::ExecuteOneFrame()
{
	float fDT = m_pClock->GetDeltaTick();

	Process(fDT);
	Draw();

	m_pClock->Process();

	Sleep(1);
}

CGame&
CGame::GetInstance()
{
	if (s_pGame == 0)
	{
		s_pGame = new CGame();
	}

	return (*s_pGame);
}

void
CGame::GameOverWon()
{
	MessageBox(m_hMainWindow, L"Winner!", L"Game Over", MB_OK);
	PostQuitMessage(0);
}

void
CGame::GameOverLost()
{
	MessageBox(m_hMainWindow, L"Loser!", L"Game Over", MB_OK);
	PostQuitMessage(0);
}

void
CGame::DestroyInstance()
{
	delete s_pGame;
	s_pGame = 0;
}

CBackBuffer*
CGame::GetBackBuffer()
{
	return (m_pBackBuffer);
}

CLevel*
CGame::GetLevel()
{
	return (m_pLevel);
}

HINSTANCE
CGame::GetAppInstance()
{
	return (m_hApplicationInstance);
}

HWND
CGame::GetWindow()
{
	return (m_hMainWindow);
}

void CGame::SetLevel(ELEVEL _eNewLevel)
{
	m_eCurrentLevel = _eNewLevel;
}

