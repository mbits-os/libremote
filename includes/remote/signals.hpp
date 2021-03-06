/*
 * Copyright (C) 2013 midnightBITS
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __LIBREMOTE_SIGNALS_HPP__
#define __LIBREMOTE_SIGNALS_HPP__

#include <memory>
#include <functional>
#include "logger.hpp"

namespace remote
{
	using signal_t = std::function<void()>;

	namespace os
	{
		struct signals;
		using signals_ptr = std::shared_ptr<signals>;
		struct signals
		{
			static signals_ptr create(const logger_ptr& log);
			virtual ~signals() {}
			virtual bool set(const char* sig, const signal_t& fn) = 0;
			virtual bool signal(const char* sig, int pid) = 0;
			virtual void cleanup() {}
		};
	}

	class signals
	{
		os::signals_ptr os_sig;
	public:
		explicit signals(const logger_ptr& log) : os_sig{ os::signals::create(log) } {}
		~signals() { os_sig->cleanup(); }
		bool set(const char* sig, const signal_t& fn) { return os_sig->set(sig, fn); }
		bool signal(const char* sig, int pid) { return os_sig->signal(sig, pid); }
	};
}

#endif // __LIBREMOTE_SIGNALS_HPP__
