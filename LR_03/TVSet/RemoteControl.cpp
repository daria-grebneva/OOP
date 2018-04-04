#include "stdafx.h"

#include "CTVSet.h"
#include "RemoteControl.h"

CRemoteControl::CRemoteControl(CTVSet& tv, std::istream& input, std::ostream& output)
	: m_tv(tv)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "TurnOn", bind(&CRemoteControl::TurnOn, this, std::placeholders::_1) },
		  { "TurnOff", bind(&CRemoteControl::TurnOff, this, std::placeholders::_1) },
		  { "Info", bind(&CRemoteControl::Info, this, std::placeholders::_1) },
		  { "SelectChannel", bind(&CRemoteControl::SelectChannel, this, std::placeholders::_1) },
		  { "SelectPreviousChannel", bind(&CRemoteControl::SelectPreviousChannel, this, std::placeholders::_1) } })
{
}

bool CRemoteControl::HandleCommand()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CRemoteControl::TurnOn(std::istream&)
{
	m_tv.TurnOn();
	m_output << "TV is turned on\n";

	return true;
}

bool CRemoteControl::TurnOff(std::istream&)
{
	m_tv.TurnOff();
	m_output << "TV is turned off\n";

	return true;
}

bool CRemoteControl::Info(std::istream&)
{
	std::string info = (m_tv.IsTurnedOn())
		? ("TV is turned on\nChannel is: " + std::to_string(m_tv.GetChannel()) + "\n")
		: "TV is turned off\nChannel is: 0\n";
	m_output << info;

	return true;
}

bool CRemoteControl::SelectChannel(std::istream& args)
{
	int channel;
	args >> channel;
	if (!m_tv.IsTurnedOn())
	{
		m_output << "Can't select channel because TV is turned off\n";
	}
	if (m_tv.IsTurnedOn() && ((channel < 1) || (channel > 99)))
	{
		m_output << "Invalid channel\n";
	}
	return true;
}

bool CRemoteControl::SelectPreviousChannel(std::istream&)
{
	if (m_tv.IsTurnedOn())
	{
		m_tv.SelectPreviousChannel();
		m_output << "Previous channel selected\n";
	}
	else
	{
		m_output << "Can't select previous channel\n";
	}

	return true;
}
