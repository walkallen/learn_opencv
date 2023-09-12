#pragma once

#include <ittnotify.h>

class Trace_function
{
public:
	Trace_function(char* func_sig);
	~Trace_function();
private:
	__itt_string_handle* handle_cv;

};

static __itt_domain* trace_domain = NULL;

static void isITTEnabled()
{
	static volatile bool isInitialized = false;
	if (!isInitialized)
	{
		trace_domain = __itt_domain_create("OpenCVTrace");
		isInitialized = true;
	}
}

Trace_function::Trace_function(char* func_sig)
{
	isITTEnabled();
	handle_cv = __itt_string_handle_create(func_sig);
	__itt_task_begin(trace_domain, __itt_null, __itt_null, handle_cv);
}

//Trace_function::~Trace_function() {
//	__itt_task_end(trace_domain, __itt_null, __itt_null, handle_cv);
//}

Trace_function::~Trace_function() {
	__itt_task_end(trace_domain );
}