#include "stdafx.h"

#include "CTVSet.h"

bool CTVSet::IsTurnedOn() const
{
	return m_isOn;
}

bool CTVSet::SelectChannel(int channel)
{
	bool isAviableChannel = ((channel <= 99) && (channel >= 1));
	if (m_isOn && isAviableChannel)
	{
		m_previousChannel = m_selectedChannel;
		m_selectedChannel = channel;
		return true;
	}
	return false;
}

int CTVSet::GetChannel() const
{
	return m_isOn ? m_selectedChannel : 0;
}

void CTVSet::TurnOn()
{
	m_isOn = true;
}

void CTVSet::TurnOff()
{
	m_isOn = false;
}

bool CTVSet::SelectPreviousChannel()
{
	if (m_isOn)
	{
		std::swap(m_previousChannel, m_selectedChannel);
		return true;
	}

	return false;
}
