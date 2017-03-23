#include "ArtistText.h"



ArtistText::ArtistText() :
	m_active{false},
	m_frameNo{ 0 },
	m_maxFrames{30}

{
}


ArtistText::~ArtistText()
{
}

void ArtistText::m_nextFrame()
{
	if (++m_frameNo > m_maxFrames)
	{
		m_active = false;
	}
}
