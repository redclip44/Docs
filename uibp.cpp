// Utility Interface Byte Picker
// Eben Taljaard 2022/07/17 
// Interprocess Communication betweeen NServ/Proc and Program/App

//##################################################scie###
//###########################------------#pause#######th1##
//###########################|-----------#resum#######th1##
//###########################||############################
//##################---------||----------#pause#######th2##
//##################|--------||----------#resum#######th2##
//##################||#######||############################
//##################||##-----||----------#pause#######thN##
//##################||##|----||----------#resum#######thN##
//##################||##||###||############################
//##################||##||###||############################
//##rc1##func####-------------|############################
//##rc1##resu####--------------############################
//##################||##||#################################
//##rc2##func####--------|#################################
//##rc2##resu####---------#################################
//##################||#####################################
//##rcN##func####----|#####################################
//##rcN##func####-----#####################################
//####################################################app##
//#########################################################

// Interested in return_codes (Use the End-User)
// 1. program start click/enter
// 2. this, me, self, eip, etc programatic "127/8" ENT (Test)
// 3. pop-up or status-bar transaction sucess
// ?. Loaded Libs, varios return_codes
// 

#include "Timer.h"  // Temporary use timer until sleep intervals
#include <iostream>
#include "event.h"

string fields[9]

// zero in desc uom ctg hour qty value hundred
int cstring[8] = {3, 6, 50, 3, 2, 4, 3, 10, 3} 

// threads
int return_code = 4;   // Byte FFFFFF9A
switch(return_code) {
  case x:
    // code block
    break;
  case y:
    // code block
    break;
  default:
    // code block
}

cout << cstring[0];

// Can be implemented to be more thread safe. But, it's only for the example.
// If the interval is too big, the Stop function will be affected too.

#define DEFAULT_TIMER_INTERVAL 1000

Timer::Timer()
	: m_isRunning(false), m_millisecondsInterval(DEFAULT_TIMER_INTERVAL)
{
}


Timer::~Timer()
{
}

bool Timer::Start(unsigned int millisecondsInterval)
{
	if (m_isRunning)
	{
		return false;
	}

	m_isRunning = true;
	m_millisecondsInterval = millisecondsInterval > 0 ? millisecondsInterval : DEFAULT_TIMER_INTERVAL;
	m_timerThread = std::thread([this]() { TimerFunc(); });

	return true;
}

bool Timer::Stop()
{
	if (!m_isRunning)
	{
		return false;
	}
	m_isRunning = false;
	if (m_timerThread.joinable())
	{
		m_timerThread.join();
	}
	return true;
}

void Timer::TimerFunc()
{
	while (m_isRunning)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(m_millisecondsInterval));
		if (m_isRunning)
		{
			Tick();
		}
	}
}

// Sample Main 
int main()
{
	InitializeWindowsEscSequnces();

	EventsPublisher ep;
	std::mutex printLocker;

	std::cout << sz::with_color("93", "Press <Enter> to stop.") << std::endl;
	
	sz::event_handler<unsigned int> timerHandler1([&ep, &printLocker](unsigned int counter) {
		if ((counter % 5) == 0)
		{
			ep.SomethingHappened.call_async("Something happened from timer handler 1", 1);
		}

		std::lock_guard<std::mutex> lock(printLocker);

		std::cout << sz::with_color("31", "Timer handler1: Timer tick ")
			<< sz::with_color("41;97", counter) << std::endl;
	});

	sz::event_handler<unsigned int> timerHandler2([&ep, &printLocker](unsigned int counter) {
		if ((counter % 7) == 0)
		{
			ep.SomethingHappened.call_async("Something happened from timer handler 2", 2);
		}

		std::lock_guard<std::mutex> lock(printLocker);

		std::cout << sz::with_color("32", "Timer handler2: Timer tick ")
			<< sz::with_color("42;97", counter) << std::endl;
	});

	// We can create an event_handler also for this handler. 
	// But, we want to demonstrate the use without it.
	auto somethingHappenedHandlerId = ep.SomethingHappened.add(
		[&printLocker](const std::string& message, int publisherId) {
		std::lock_guard<std::mutex> lock(printLocker);
		
		std::cout << "Something happened. Message: " 
			<< sz::with_color(publisherId == 1 ? "91" : "92", message.c_str())
			<< std::endl;
	});

	ep.TimerTick += timerHandler1;
	ep.TimerTick += timerHandler2;
	ep.Start();

	getchar();

	ep.SomethingHappened.remove_id(somethingHappenedHandlerId);
	ep.TimerTick -= timerHandler1;
	ep.TimerTick -= timerHandler2;
	ep.Stop();

	return 0;
}
