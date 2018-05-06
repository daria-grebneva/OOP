#include "stdafx.h"
#include "../TVSet/CTVSet.h"
#include "../TVSet/RemoteControl.h"

using namespace std;

TEST_CASE(" ", "[Remote_Control]")
{
	struct RemoteControlDependencies
	{
		CTVSet tv;
		std::stringstream input;
		std::stringstream output;
	};

	struct RemoteControlFixture : RemoteControlDependencies
	{
		CRemoteControl remoteControl;

		RemoteControlFixture()
			: remoteControl(tv, input, output)
		{
		}
		void VerifyCommandHandling(const string& command, const boost::optional<int>& expectedChannel, const string& expectedOutput)
		{
			output = stringstream();
			input = stringstream();
			REQUIRE(input << command);
			REQUIRE(remoteControl.ProcessCommand());
			REQUIRE(tv.IsTurnedOn() == expectedChannel.is_initialized());
			REQUIRE(tv.GetChannel() == expectedChannel.get_value_or(0));
			REQUIRE(input.eof());
			REQUIRE(output.str() == expectedOutput);
		}
	};

	RemoteControlFixture fixture;
	SECTION("can handle TurnOn command")
	{
		fixture.VerifyCommandHandling("TurnOn", 1, "TV is turned on\n");
	}

	SECTION("can turn off tv which is on")
	{
		fixture.tv.TurnOn();
		fixture.VerifyCommandHandling("TurnOff", boost::none, "TV is turned off\n");
	}

	SECTION("can print tv info")
	{
		fixture.VerifyCommandHandling("Info", boost::none, "TV is turned off\nChannel is: 0\n");

		fixture.tv.TurnOn();
		fixture.tv.SelectChannel(42);
		fixture.VerifyCommandHandling("Info", 42, "TV is turned on\nChannel is: 42\n");
	}

	SECTION("cant select channel when tv is turned off")
	{
		fixture.VerifyCommandHandling("SelectChannel 42", boost::none, "Can't select channel because TV is turned off\n");
		fixture.VerifyCommandHandling("SelectChannel 100", boost::none, "Can't select channel because TV is turned off\n");
	}

	SECTION("can't select an invalid channel when tv is on")
	{
		fixture.tv.TurnOn();
		fixture.tv.SelectChannel(42);
		fixture.VerifyCommandHandling("SelectChannel 100", 42, "Invalid channel\n");
		fixture.VerifyCommandHandling("SelectChannel 0", 42, "Invalid channel\n");
	}

	SECTION("select a previous channel when tv is on")
	{
		fixture.tv.TurnOn();
		fixture.tv.SelectChannel(2);
		fixture.tv.SelectChannel(42);
		fixture.VerifyCommandHandling("SelectPreviousChannel 30", 2, "Previous channel selected\n");
	}

	SECTION("restores last selected channel")
	{
		fixture.tv.TurnOn();
		fixture.tv.SelectChannel(2);
		fixture.tv.SelectChannel(42);
		fixture.tv.TurnOff();
		fixture.tv.TurnOn();
		fixture.VerifyCommandHandling("SelectPreviousChannel 30", 2, "Previous channel selected\n");
	}
}
