/**
 * Titanium Windows Native Module - testwinci
 *
 * Copyright (c) 2015 by Appcelerator, Inc. All Rights Reserved.
 * Licensed under the terms of the Apache Public License.
 * Please see the LICENSE included with this distribution for details.
 */
#include "ComTest.hpp"
#include "Titanium/detail/TiImpl.hpp"
#include "TitaniumWindows/LogForwarder.hpp"

using namespace Windows::ApplicationModel::Background;

namespace ComTest
{
	/*
	 * @class
	 * @discussion This is background task for BackgroundService.
	 *             EntryPoint: ComTest.BackgroundServiceTask
	 *
	 *   Don't remove this class because Windows Store submission process requires
	 *   at least one C++/CX class in winmd. (TIMOB-20192)
	 * 
	 *   ## Usage: (JavaScript) ##
	 *     var task = Ti.App.Windows.BackgroundService.registerTimerTask(
	 *                'ComTest.BackgroundServiceTask', 15, false);
	 *
	 *   ## tiapp.xml ##
	 *   <windows>
	 *     <manifest>
	 *       <Extensions>
	 *         <Extension Category="windows.backgroundTasks" EntryPoint="ComTest.BackgroundServiceTask">
	 *           <BackgroundTasks>
	 *             <Task Type="timer" />
	 *           </BackgroundTasks>
	 *         </Extension>
	 *       </Extensions>
	 *     </manifest>
	 *   </windows>
	 *
	 */
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class BackgroundServiceTask sealed : public Windows::ApplicationModel::Background::IBackgroundTask
	{
	public:
		virtual void Run(Windows::ApplicationModel::Background::IBackgroundTaskInstance^ taskInstance);
	};

	/*
	 * BackgroundServiceTask::Run implementation
	 */
	void BackgroundServiceTask::Run(IBackgroundTaskInstance^ taskInstance)
	{
		const auto deferral = taskInstance->GetDeferral();

		//
		// BACKGROUND TASK: IMPLEMENT SOMETHING USEFUL HERE :)
		//

		// Inform this task has finished
		deferral->Complete();
	}
}

namespace Com
{
	Test::Test(const JSContext& js_context) TITANIUM_NOEXCEPT
		: Titanium::Module(js_context, "com.test")
	{
		TITANIUM_LOG_DEBUG("Test::ctor Initialize");
	}

	void Test::postInitialize(JSObject& js_object)
	{
	}

	void Test::postCallAsConstructor(const JSContext& js_context, const std::vector<JSValue>& arguments)
	{
	}

	void Test::JSExportInitialize()
	{
		JSExport<Test>::SetClassVersion(1);
		JSExport<Test>::SetParent(JSExport<Titanium::Module>::Class());
		TITANIUM_ADD_PROPERTY(Test, exampleProp);
		TITANIUM_ADD_FUNCTION(Test, example);
	}

	TITANIUM_PROPERTY_GETTER(Test, exampleProp)
	{
		// example property getter
		// 
		// Getter should return JavaScript value (JSValue).
		// 
		// For more information on how to use JSContext / JSValue / JSObject, check out HAL:
		//      https://github.com/appcelerator/HAL
		// 
		return get_context().CreateString("hello world");
	}

	TITANIUM_PROPERTY_SETTER(Test, exampleProp)
	{
		// example property setter
		// 
		// There are a variable expanded from TITANIUM_PROPERTY_SETTER macro here:
		//     JSValue argument ... JavaScript value that is passed to this setter
		// 
		// Example:
		//   # Check if it's a string
		//      auto _0 = argument.IsString();
		// 
		//   # Convert argument to std::string
		//      auto _0 = static_cast<std::string>(argument);    
		// 
		//   For more information on how to use JSContext / JSValue / JSObject, check out HAL:
		//      https://github.com/appcelerator/HAL
		// 
		// Setter should return true if the property was set, otherwise false.
		// 
		return true;
	}

	TITANIUM_FUNCTION(Test, example)
	{
		// example method
		// 
		// There are variables expanded from TITANIUM_FUNCTION macro here:
		//     std::vector<JSValue> arguments ... list of arguments that is passed to this function
		//     JSObject this_object           ... "this" JavaScript object
		// 
		// Example: 
		//    # Get first argument and convert to std::string
		//      auto _0 = static_cast<std::string>(arguments.at(0));    
		// 
		//    # Get first argument and convert to double
		//      auto _0 = static_cast<double>(arguments.at(0));    
		// 
		//    # Get first argument and convert to std::uint32_t
		//      auto _0 = static_cast<std::uint32_t>(arguments.at(0));    
		// 
		//   Function should return JSValue.
		//   For more information on how to use JSContext / JSValue / JSObject, check out HAL:
		//      https://github.com/appcelerator/HAL
		// 
		return get_context().CreateString("hello world");
	}

}
