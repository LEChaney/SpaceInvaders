//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name	: clock.h
// Description	: clock header file
// Authors		: Lance Chaney & Sebastian Tengdahl
// Mail			: lance.cha7337@mediadesign.school.nz
//                sebastian.ten7230@mediadesign.school.nz
//

#pragma once

#if !defined(__CLOCK_H__)
#define __CLOCK_H__

// Library Includes
#include <Windows.h>

// Local Includes

// Types

// Constants

// Prototypes
class CClock
{
    // Member Functions
public:
    CClock();
    ~CClock();

    bool Initialise();

    void Process();

    float GetDeltaTick();

	int CountFramesPerSecond(float _DeltaTick);

protected:

private:
    CClock(const CClock& _kr);
    CClock& operator= (const CClock& _kr);

    // Member Variables
public:

protected:
    double m_fTimeElapsed;
	double m_fDeltaTime;
	double m_fLastTime;
	double m_fCurrentTime;
	double m_SecondsPerCount;
	int m_iFrameCount = 0;

private:

};


#endif    // __CLOCK_H__
