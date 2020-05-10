#include "debug.hpp"

using namespace std;

void out_event(const bt_debug_event_msg &event){
	cout << "Event from PID " << event.pid << ", thread " << event.thread << ":" << endl;
	cout << "Event type: ";
	switch(event.event){
		case bt_debug_event::ProgramStart:
			cout << "ProgramStart" << endl;
			break;
		case bt_debug_event::ProgramEnd:
			cout << "ProgramEnd" << endl;
			break;
		case bt_debug_event::Breakpoint:
			cout << "Breakpoint" << endl;
			break;
		case bt_debug_event::Exception:
			cout << "Exception" << endl;
			break;
		case bt_debug_event::ThreadStart:
			cout << "ThreadStart" << endl;
			break;
		case bt_debug_event::ThreadEnd:
			cout << "ThreadEnd" << endl;
			break;
	}
	if(event.event == bt_debug_event::Exception){
		cout << "Exception type: ";
		switch(event.error){
			case bt_exception::NoError:
				cout << "NoError" << endl;
				break;
			case bt_exception::DivideByZero:
				cout << "DivideByZero" << endl;
				break;
			case bt_exception::BoundsError:
				cout << "BoundsError" << endl;
				break;
			case bt_exception::InvalidOpCode:
				cout << "InvalidOpCode" << endl;
				break;
			case bt_exception::SegmentFault:
				cout << "SegmentFault" << endl;
				break;
			case bt_exception::ProtectionFault:
				cout << "ProtectionFault" << endl;
				break;
			case bt_exception::UnresolvedPageFault:
				cout << "UnresolvedPageFault" << endl;
				break;
			case bt_exception::BadLocking:
				cout << "BadLocking" << endl;
				break;
			case bt_exception::SelfAbort:
				cout << "SelfAbort" << endl;
				break;
			case bt_exception::InvalidArg:
				cout << "InvalidArg" << endl;
				break;
			case bt_exception::SecurityException:
				cout << "SecurityException" << endl;
				break;
		}
	}
}