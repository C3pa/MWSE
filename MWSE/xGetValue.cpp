/************************************************************************
	
	xGetValue.cpp - Copyright (c) 2008 The MWSE Project
	http://www.sourceforge.net/projects/mwse

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

**************************************************************************/

#include "VMExecuteInterface.h"
#include "Stack.h"
#include "InstructionInterface.h"
#include "TES3Util.h"
#include "Reference.h"

using namespace mwse;

namespace mwse {
	class xGetValue : mwse::InstructionInterface_t {
	public:
		xGetValue();
		virtual float execute(VMExecuteInterface &virtualMachine);
		virtual void loadParameters(VMExecuteInterface &virtualMachine);
	};

	static const mwse::mwOpcode_t xGetValueOpcode = 0x3F61;
	static xGetValue xGetValueInstance;

	xGetValue::xGetValue() : mwse::InstructionInterface_t(xGetValueOpcode) {}

	void xGetValue::loadParameters(mwse::VMExecuteInterface &virtualMachine) {}

	float xGetValue::execute(mwse::VMExecuteInterface &virtualMachine) {
		// Get reference.
		REFRRecord_t* reference = virtualMachine.getReference();
		if (reference == NULL) {
			mwse::log::getLog() << "xGetValue: No reference provided." << std::endl;
			mwse::Stack::getInstance().pushLong(0);
			return 0.0f;
		}

		// Get value.
		mwLong_t value = 0;
		try {
			value = tes3::getValue(reference, true);
		}
		catch (std::exception& e) {
			mwse::log::getLog() << "xGetValue: " << e.what() << std::endl;
			mwse::Stack::getInstance().pushLong(0);
			return 0.0f;
		}

		mwse::Stack::getInstance().pushLong(value);

		return 0.0f;
	}
}