#include "pch.h"
#include "MatrixMultiplicationViewModel.h"
#include "..\..\CppLoops\MatrixMultiplication.h"
#include "..\..\CppLoops\SimpleTimer.h"
#include "..\..\CppLoops\helpers.h"
#include "DelegateCommand.h"

using namespace concurrency;
using namespace Platform::Collections;

namespace ModernCppHubApp
{
	MatrixMultiplicationViewModel::MatrixMultiplicationViewModel(shared_ptr<ExceptionPolicy> exceptionPolicy) :
		ViewModelBase(exceptionPolicy)
	{
		RunCommand = ref new DelegateCommand(
			ref new ExecuteDelegate(this, &MatrixMultiplicationViewModel::Run),
			ref new CanExecuteDelegate(this, &MatrixMultiplicationViewModel::CanRun));

		IsRunning = false;
		
		Results = ref new Vector<String^>();
	}

	bool MatrixMultiplicationViewModel::CanRun(Object^ )
	{
		return !IsRunning;
	}

	static String^ RunTest()
	{
		SimpleTimer timer;

		MatrixMultiplication().Test();

		auto value = printwstring(L"%.2f sec", timer.Millisec() / 1000.0f);

		return ref new String(value.data());
	}

	void MatrixMultiplicationViewModel::Run(Object^ parameter)
	{
		IsRunning = true;

		OnPropertyChanged("IsRunning");
		RunCommand->CanExecute(nullptr);

		auto async = create_async([] { return RunTest(); });
		create_task(async)
			.then([this](task<String ^> t)
		{
			Results->Append(t.get());
			IsRunning = false;

			OnPropertyChanged("IsRunning");
			RunCommand->CanExecute(nullptr);
		});
	}

}