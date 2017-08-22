/**
 * Titanium Windows Native Module - testwinci
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */


#ifndef _COMTEST_HPP_
#define _COMTEST_HPP_

#include "ComTest_EXPORT.h"
#include "Titanium/detail/TiBase.hpp"
#include "Titanium/Module.hpp"

namespace Com
{
	using namespace HAL;

	class COMTEST_EXPORT Test : public Titanium::Module, public JSExport<Test>
	{
		public:
			Test(const JSContext&) TITANIUM_NOEXCEPT;
			virtual void postInitialize(JSObject& js_object) override;
			virtual void postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments) override;

			virtual ~Test()              = default;
			Test(const Test&)            = default;
			Test& operator=(const Test&) = default;
#ifdef TITANIUM_MOVE_CTOR_AND_ASSIGN_DEFAULT_ENABLE
			Test(Test&&)                 = default;
			Test& operator=(Test&&)      = default;
#endif

			static void JSExportInitialize();

			TITANIUM_PROPERTY_DEF(exampleProp);
			TITANIUM_FUNCTION_DEF(example);
	};
}
#endif // _COMTEST_HPP_
